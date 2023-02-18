// ///////////////////////////////////////////////// //
// 3D GameStudio A6 - WRS Builder for Kabus 22
// by https://github.com/iseeeva
// ///////////////////////////////////////////////// //

import fs from 'fs'
import path from 'path'
import { XOR, readAs } from './lib/r_lib.mjs'
import { callExCom, generate_paths } from './lib/c_lib.mjs'
import { dirNameFileURL } from './utils.mjs'
const __dirname = dirNameFileURL(import.meta.url)

const input = generate_paths(__dirname, process.argv[2])

const depend_paths = {
  quick_bms: path.join(__dirname, './ext_lib/quickbms.exe'),
  lzssBig_bms: path.join(__dirname, './ext_lib/lzssBig.bms'),
}

if (!fs.existsSync(depend_paths.quick_bms)
 || !fs.existsSync(depend_paths.lzssBig_bms)) {
  console.log('Dependent files', Object.keys(depend_paths), ' are missing please re-download tools.')
  process.exit()
}
if (process.argv[2] === '--help' || process.argv[2] === undefined) {
  console.log('\nThis tool can create Kabus 22 WRS Archive. by iseeeva \nUSING: source_builder.exe <dir_name> \n\nNote: WRS Archives not support path-based archive system.\n')
  process.exit()
}
if (!fs.existsSync(input.full_path) || fs.readdirSync(input.full_path).length === 0) {
  console.log(`${input.name} directory was not found or empty`)
  process.exit()
}

const output_fname = generate_paths(input.path, `${input.name}.wrs`) // Output file name

const xorKey = Buffer.from('A5', 'hex') // XOR key of file name for file header
const header_version = Buffer.from('57525332', 'hex') // Archive Header ID
fs.writeFileSync(output_fname.full_path, header_version)

fs.readdirSync(input.full_path).forEach((_file) => {
  const file = generate_paths(input.full_path, _file)

  if (fs.lstatSync(file.full_path).isDirectory()) {
    console.log('WRS Archives cannot be support path-based system please delete all directory in', process.argv[2])
    process.exit()
  }

  const uncompressed_fread = Buffer.from(fs.readFileSync(file.full_path, 'hex'), 'hex')

  callExCom(`${depend_paths.quick_bms} -o ${depend_paths.lzssBig_bms} "${file.full_path.replaceAll(/\\/g, '\\\\')}" "${input.full_path.replaceAll(/\\/g, '\\\\')}"`)

  //#region Edit Compressed File for Adding Header

  const file_header = Buffer.alloc(40) // File Header

  // fileHeader xorred_file_name
  const xorred_file_name = XOR(Buffer.from(file.name, 'binary'), xorKey.toString('binary'))
  file_header.fill(Buffer.from(xorred_file_name, 'hex'), 0, xorred_file_name.length)

  // fileHeader compressed_fsize
  const compressed_fread = Buffer.from(fs.readFileSync(file.full_path, 'hex'), 'hex')
  const compressed_fsize = readAs(compressed_fread.length, 'uint32_hex')

  // fileHeader uncompressed_fsize
  // uncompressed_fread line:48 (should be loaded before compress)
  const uncompressed_fsize = readAs(uncompressed_fread.length, 'uint32_hex')

  file_header.fill(uncompressed_fsize, 36, 40) // uncompressed size
  file_header.fill(compressed_fsize, 32, 36) // compressed size
  // end file-size

  fs.appendFileSync(output_fname.full_path, file_header)
  fs.appendFileSync(output_fname.full_path, compressed_fread)
  //#endregion end Edit Compressed File for Adding Header

  console.log(`[${output_fname.name}/${header_version.toString()}] - ADDED: ${file.name}`)
})
