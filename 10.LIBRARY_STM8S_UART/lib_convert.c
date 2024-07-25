#include <lib_convert.h>

uint8_t *Convert_From_Float_To_Bytes(float data)
{
    static data_format_float_bytes input_convert;
    input_convert.data_float = data;
    return input_convert.bytes;
}

float Convert_From_Bytes_To_Float(uint8_t data0, uint8_t data1, uint8_t data2, uint8_t data3)
{
    data_format_float_bytes input_convert;
    input_convert.bytes[3] = data0;
    input_convert.bytes[2] = data1;
    input_convert.bytes[1] = data2;
    input_convert.bytes[0] = data3;
    return input_convert.data_float;
}

uint8_t *Convert_From_Int_To_Bytes(int data)
{
    static data_format_int_bytes input_convert;
    input_convert.data_int = data;
    return input_convert.bytes;
}

uint32_t Convert_From_Bytes_To_Int(uint8_t data1, uint8_t data2, uint8_t data3, uint8_t data4)
{
    data_format_int_bytes input_convert;
    input_convert.bytes[0] = data1;
    input_convert.bytes[1] = data2;
    input_convert.bytes[2] = data3;
    input_convert.bytes[3] = data4;

    return input_convert.data_int;
}

uint8_t *Convert_From_Uint16_To_Bytes(int data)
{
    static data_format_uint8_16_t input_convert;
    input_convert.data_uint16 = data;
    return input_convert.bytes;
}

uint16_t Convert_From_Bytes_To_Uint16(uint8_t data1, uint8_t data2)
{
    data_format_uint8_16_t input_convert;
    input_convert.bytes[0] = data1;
    input_convert.bytes[1] = data2;

    return input_convert.data_uint16;
}