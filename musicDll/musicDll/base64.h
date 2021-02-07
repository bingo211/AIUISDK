#ifndef BASE64_H
#define BASE64_H

#include <string.h>
#include <string>

class base64
{
public:

    base64();
    ~base64();

public:
    static std::string encode(const std::string& str, bool is_is_chunked = false, bool is_file = false);

    static std::string decode(const std::string& str, bool is_file = false);

private:

    static std::string encode_c(const unsigned char* p_in, unsigned long u_len, bool is_is_chunked = false);

    static std::string decode_c(const unsigned char* p_in, unsigned long u_len);
};
#endif // BASE64_H
