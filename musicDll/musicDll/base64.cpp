#include "base64.h"

static const char e_tab[65] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";

static const unsigned char d_tab[] = {
    255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,
    255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,
    255,255,255,255,255,255,255,255,255,255,255,255,255,62, 255,
    255,255,63, 52, 53, 54, 55, 56, 57, 58, 59, 60, 61, 255,255,
    255,255,255,255,255, 0,  1,  2,  3,  4,  5,  6,  7,  8,  9,
    10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24,
    25, 255,255,255,255,255,255,26, 27, 28, 29, 30, 31, 32, 33,
    34, 35, 36, 37, 38, 39, 40, 41, 42, 43, 44, 45, 46, 47, 48,
    49, 50, 51, 255,255,255,255,255,255,255,255,255,255,255,255,
    255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,
    255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,
    255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,
    255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,
    255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,
    255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,
    255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,
    255,255,255,255,255,255,255,255,255,255,255,255,255,255,255
};

base64::base64()
{
}

base64::~base64()
{
}

std::string base64::encode(const std::string& str, bool is_is_chunked /* = false*/,  bool is_file /* = false */)
{
    return encode_c((unsigned char*)str.c_str(), str.size(), is_is_chunked);
}

std::string base64::decode(const std::string& str, bool is_file /* = false */)
{
    return decode_c((unsigned char*)str.c_str(), str.size());
}

std::string base64::encode_c(const unsigned char* p_in, unsigned long u_len, bool is_is_chunked /* = false*/)
{
    std::string str_out;

    unsigned char in[3] = {0};
    unsigned int ent_size = 0;
    unsigned long i = 0;
    for (; i < (u_len / 3); i++)
    {
        in[0] = p_in[i*3];
        in[1] = p_in[i*3+1];
        in[2] = p_in[i*3+2];

        str_out += e_tab[(in[0] >> 2)];
        str_out += e_tab[((in[0] << 4) & 0x30 | (in[1] >> 4))];
        str_out += e_tab[((in[1] << 2) & 0x3C | (in[2] >> 6))];
        str_out += e_tab[(in[2] & 0x3F)];

        ent_size += 4;
        if (is_is_chunked && ent_size == 76)
        {
            str_out += "\r\n";
            ent_size = 0;
        }
    }

    unsigned int mod = u_len % 3;
    if (mod == 0)
    {
        if (ent_size == 0 && !str_out.empty())
        {
            //str_out.pop_back();
            //str_out.pop_back();
            if (str_out.size() > 2)
            {
                str_out = str_out.erase(str_out.size()-2);
            }
            else if(str_out.size() > 1)
            {
                str_out = str_out.erase(str_out.size()-1);
            }
        }
    }
    else if (mod == 1)
    {
        in[0] = p_in[i*3];
        str_out += e_tab[(in[0] >> 2)];
        str_out += e_tab[((in[0] << 4) & 0x30)];
        str_out += "==";
    }
    else if ( mod == 2)
    {
        in[0] = p_in[i*3];
        in[1] = p_in[i*3+1];

        str_out += e_tab[(in[0] >> 2)];
        str_out += e_tab[((in[0] << 4) & 0x30 | (in[1] >> 4))];
        str_out += e_tab[((in[1] << 2) & 0x3C)];
        str_out += "=";
    }

    return str_out;
}

std::string base64::decode_c(const unsigned char* p_in, unsigned long u_len)
{
    std::string str_out;

    unsigned char in[4] = {0};
    unsigned int ent_size = 0;
    unsigned long i = 0;

    const unsigned char* p = p_in;
    for (; i < u_len; i += 4)
    {
        if (i % 76 == 0 && i != 0)
        {
            if (*p == '\r')
            {
                p++;
            }
            if (*p == '\n')
            {
                p++;
            }
        }

        memset(in, 255, 4);
        in[0] = d_tab[*p++];
        if (i + 1 < u_len)
        {
            in[1] = d_tab[*p++];
        }
        if (i + 2 < u_len)
        {
            in[2] = d_tab[*p++];
        }
        if (i + 3 < u_len)
        {
            in[3] = d_tab[*p++];
        }

        if (in[0] != 255 & in[1] != 255)
        {
            str_out += (unsigned char)((in[0] << 2) | (in[1] >> 4));

            if (in[2] != 255)
            {
                str_out += (unsigned char)((in[1] << 4) | (in[2] >> 2));

                if (in[3] != 255)
                {
                    str_out += (unsigned char)((in[2] << 6) | in[3]);
                }
            }
        }
    }

    return str_out;
}
