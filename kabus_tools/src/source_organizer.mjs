// ///////////////////////////////////////////////// //
// 3D GameStudio A6 - WRS Unpacker/Organizer for Kabus 22
// by https://github.com/iseeeva
// ///////////////////////////////////////////////// //

import fs from 'fs'
import path from 'path'
import { callExCom, generate_paths } from './lib/c_lib.mjs'
import { dirNameFileURL } from './utils.mjs'
const __dirname = dirNameFileURL(import.meta.url)

const depend_paths = {
  quick_bms: path.join(__dirname, './ext_lib/quickbms.exe'),
  gamestudio_bms: path.join(__dirname, './ext_lib/gamestudio.bms'),
}

if (!fs.existsSync(depend_paths.gamestudio_bms) || !fs.existsSync(depend_paths.quick_bms)) {
  console.log('Dependent files', Object.keys(depend_paths), 'are missing please re-download tools.')
  process.exit()
}

if (process.argv[2] === 'help' || process.argv[2] === undefined) {
  console.log('\nThis tool can unpack and organize wrs files for Kabus22. by iseeeva\n\nUSING: source_organizer.exe <files>')
  process.exit()
}

for (let i = 2; i < process.argv.length; i++) {
  const input_path = generate_paths(__dirname, process.argv[i])
  const output_path = generate_paths(input_path.path, input_path.name.split('.')[0])

  if (!fs.existsSync(input_path.full_path)) {
    console.log(input_path.name, 'is missing in-game folder.')
    process.exit()
  }

  if (!fs.existsSync(output_path.full_path)) {
    fs.mkdirSync(output_path.full_path, {
      recursive: true,
    })
  }

  callExCom(`${depend_paths.quick_bms} -o ${depend_paths.gamestudio_bms} ${input_path.full_path.replaceAll(/\\/g, '\\\\')} ${output_path.full_path.replaceAll(/\\/g, '\\\\')}`)

  fs.readdirSync(output_path.full_path).forEach((_file) => {
    const file = generate_paths(output_path.full_path, _file)

    if (!fs.lstatSync(file.full_path).isDirectory()) {
      const file_extname = file.name.split('.').pop()
      if (file_extname !== 'wdl' && file_extname !== file.name && file_extname != null) {
        const file_extpath = path.join(output_path.full_path, file_extname)
        if (!fs.existsSync(file_extpath))
          fs.mkdirSync(file_extpath, { recursive: true })
        fs.renameSync(file.full_path, path.join(file_extpath, file.name), (err) => {
          if (err)
            throw err
        })
      }
    }
  })
  console.log(`${output_path.name} is finished (${i - 1}/${process.argv.length - 2})`)
}
