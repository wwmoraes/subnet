#ifndef __IPV4_HH
#define __IPV4_HH

#include <string>

class IPv4 {
  public:
    const static unsigned int MAX = 4294967295u; // 2**32 - 1

    IPv4();
    IPv4(const std::string&);
    IPv4(const unsigned int&);

    void setIP(const std::string&);
    void setIP(const unsigned int&);
    const unsigned int& getInt();
    const std::string str() const;

    friend IPv4 operator &(const IPv4&, const IPv4&);
    friend IPv4 operator |(const IPv4&, const unsigned int&);
    friend IPv4 operator ^(const IPv4&, const IPv4&);
    friend IPv4 operator ^(const IPv4&, const unsigned int&);

    operator std::string() const {
      return this->str();
    };

  protected:
    unsigned int ipAddress;
};

#endif
