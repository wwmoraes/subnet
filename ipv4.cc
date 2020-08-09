#include "ipv4.hh"

const unsigned int IPv4::MAX;

IPv4::IPv4() {
  this->ipAddress = 0;
}

IPv4::IPv4(const std::string& ipString) {
  this->setIP(ipString);
}

IPv4::IPv4(const unsigned int& ipValue) {
  this->setIP(ipValue);
}

void IPv4::setIP(const std::string& ipString) {
  int octets[4];
  size_t current, index = 0, previous = 0;

  current = ipString.find_first_of('.');
  while(current != std::string::npos) {
    if (index >= 4) throw "invalid IP";

    std::sscanf(ipString.substr(previous, current - previous).c_str(), "%d", &octets[index]);

    if (octets[index] > 255) throw std::runtime_error("invalid IP - octet higher than 255");
    if (octets[index] < 0) throw std::runtime_error("invalid IP - octet lower than 0");

    previous = current + 1;
    current = ipString.find_first_of('.', previous);
    index++;
  };
  std::sscanf(ipString.substr(previous).c_str(), "%d", &octets[index]);

  this->ipAddress = 0;
  this->ipAddress += octets[0] << 24;
  this->ipAddress += octets[1] << 16;
  this->ipAddress += octets[2] << 8;
  this->ipAddress += octets[3];
}

void IPv4::setIP(const unsigned int& ipValue) {
  if (ipValue > IPv4::MAX) throw std::runtime_error("invalid IP - value is greater than max IPv4");
  this->ipAddress = ipValue;
}

const unsigned int& IPv4::getInt() {
  return this->ipAddress;
}

const std::string IPv4::str() const {
  unsigned short octets[4];

  octets[0] = (this->ipAddress & (255 << 24)) >> 24;
  octets[1] = (this->ipAddress & (255 << 16)) >> 16;
  octets[2] = (this->ipAddress & (255 << 8)) >> 8;
  octets[3] = this->ipAddress & 255;

  size_t size = std::snprintf(nullptr, 0, "%hu.%hu.%hu.%hu", octets[0], octets[1], octets[2], octets[3]) + 1;
  if (size <= 0) throw std::runtime_error("unable to format IP");

  char* buf = new char[size];
  std::snprintf(buf, size, "%hu.%hu.%hu.%hu", octets[0], octets[1], octets[2], octets[3]);
  std::string str(buf, size - 1);

  delete[] buf;
  return str;
}

IPv4 operator &(const IPv4& lhs, const IPv4& rhs) {
  return IPv4(lhs.ipAddress & rhs.ipAddress);
}

IPv4 operator |(const IPv4& lhs, const unsigned int& rhs) {
  return IPv4(lhs.ipAddress | rhs);
}

IPv4 operator ^(const IPv4& lhs, const IPv4& rhs) {
  return IPv4(lhs.ipAddress ^ rhs.ipAddress);
}

IPv4 operator ^(const IPv4& lhs, const unsigned int& rhs) {
  return IPv4(lhs.ipAddress ^ rhs);
}
