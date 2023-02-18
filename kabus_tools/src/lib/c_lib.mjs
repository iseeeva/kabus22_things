import path from 'path'
import { execSync } from 'child_process'
import { getFloat16, setFloat16 } from '@petamoriken/float16'

// Class & Function Library //

export class DataViewEX extends DataView {
  /**
   * @param {number} byteOffset
   */
  getFloat16(byteOffset, littleEndian = false) {
    return getFloat16(this, byteOffset, littleEndian)
  }

  /**
   * @param {number} byteOffset
   * @param {number} value
   * @param {boolean} littleEndian
   */
  setFloat16(byteOffset, value, littleEndian = false) {
    return setFloat16(this, byteOffset, value, littleEndian)
  }
}

/**
 * Generate Path Alternatives
 * @param {string} __dirname
 * @param {string} __filename
 * @returns
 */
export function generate_paths(__dirname, __filename) {
  if (__dirname == null || __filename == null) {
    console.log('Path Generator Parameters a NULL', __dirname, __filename)
    process.exit()
  }

  return {
    full_path: path.join(__dirname, __filename),
    path: path.dirname(path.join(__dirname, __filename)),
    name: path.basename(path.join(__dirname, __filename)),
  }
}

/**
 * Call execSync command
 * @param {string} cmd
 */
export function callExCom(cmd) {
  try {
    execSync(cmd, {
      stdio: ['pipe', 'pipe', 'ignore'],
    })
  }
  catch (error) {
    console.log(error.message)
    console.log('error', error.stdout.toString())
    process.exit()
  }
}
