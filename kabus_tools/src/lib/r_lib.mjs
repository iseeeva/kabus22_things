import * as fs from 'fs'
import _ from 'lodash-es'
import { hasOwn, isPlainObject } from '../utils.mjs'
import { DataViewEX } from './c_lib.mjs'

// Reverse Engineering Library //

/**
 * Endian Swapping Function
 * @param {string} hexStr Hex String
 * @returns {Buffer} Hex Buffer
 */
export function endian(hexStr) {
  const newHexStr = (hexStr.length % 2 ? `0${hexStr}` : hexStr)
  const reversedHex = _.chunk(newHexStr, 2).reverse().flat().join('')
  return Buffer.from(reversedHex, 'hex')
}

/**
 * Value Converter Function
 * @param {Buffer|number} value
 * @param {string} type
 * @param {{swap_endian:boolean}} options
 * @returns {Buffer|null}
 */
export function readAs(value, type, options) {
  const getHex = i => (`00${i.toString(16)}`).slice(-2)
  let ocean = null

  if (typeof value === 'number') {
    if (type === 'int_hex16') { // Integer to Hex Buffer
      const view = new DataViewEX(new ArrayBuffer(2))
      view.setInt16(0, value)
      ocean = Buffer.from(Array.from({ length: 2 }, (_, i) => getHex(view.getUint8(i))).join(''), 'hex')
    }

    if (type === 'float_hex') { // Float32 to Hex Buffer
      const view = new DataViewEX(new ArrayBuffer(4))
      view.setFloat32(0, value)
      ocean = Buffer.from(Array.from({ length: 4 }, (_, i) => getHex(view.getUint8(i))).join(''), 'hex')
    }

    if (type === 'uint32_hex') { // Uint32 to Hex Buffer
      const view = new DataViewEX(new ArrayBuffer(4))
      view.setUint32(0, value)
      ocean = Buffer.from(Array.from({ length: 4 }, (_, i) => getHex(view.getUint8(i))).join(''), 'hex')
    }
  }

  if (isPlainObject(options)) {
    if (hasOwn(options, 'swap_endian') && options.swap_endian === true)
      ocean = endian(ocean.toString('hex'))
  }

  return ocean
}

export function XOR(input, key) {
  let c = ''
  input = input.toString('binary')
  while (key.length < input.length)
    key += key

  for (let i = 0; i < input.length; i++) {
    const inputA = input[i].charCodeAt(0)
    const keyA = key[i].charCodeAt(0)
    const xorValue = inputA ^ keyA
    let xorHex = xorValue.toString('16')
    if (xorHex.length < 2)
      xorHex = `0${xorHex}`
    c += xorHex
  }
  return Buffer.from(c, 'hex')
}
