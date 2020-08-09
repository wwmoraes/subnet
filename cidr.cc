#include "cidr.hh"

CIDR::CIDR() {
  this->set("0.0.0.0/0");
}

CIDR::CIDR(const std::string& cidrStr) {
  this->set(cidrStr);
}

void CIDR::set(const std::string& cidrStr) {
  size_t separatorPos = cidrStr.find_first_of('/');

  if (separatorPos == std::string::npos) throw "invalid CIDR";

  this->ipAddress.setIP(cidrStr.substr(0, separatorPos));
  std::sscanf(cidrStr.substr(separatorPos + 1).c_str(), "%hu", &this->maskSize);

  if (this->maskSize == 32)
    this->maskAddress.setIP(IPv4::MAX);
  else this->maskAddress.setIP(IPv4::MAX - (2u << (31u - this->maskSize)) + 1);

  this->subnetIDAddress.setIP(this->ipAddress & this->maskAddress);
  this->startAddress.setIP(this->subnetIDAddress | 1u);
  this->broadcastAddress.setIP(this->subnetIDAddress | ((2u << (31u - this->maskSize))-1));
  this->endAddress.setIP(this->broadcastAddress ^ 1u);
  this->maxSubnets = 2 << (this->maskSize - 9);

  if (this->maskSize <= 30)
    this->maxHostsPerSubnet = (2 << std::max(0, 31 - this->maskSize)) - 2;
  else this->maxHostsPerSubnet = 1;
}

const std::string CIDR::str() const {
  size_t size = std::snprintf(nullptr, 0, "%s/%hu", this->ipAddress.str().c_str(), this->maskSize) + 1;
    if (size <= 0) throw std::runtime_error("unable to format CIDR");

  char* buf = new char[size];
  std::snprintf(buf, size, "%s/%hu", this->ipAddress.str().c_str(), this->maskSize);
  std::string str(buf, size - 1);

  delete[] buf;
  return str;
}

const IPv4& CIDR::IP() {
  return this->ipAddress;
}

const IPv4& CIDR::MaskAddress() {
  return this->maskAddress;
}

const unsigned short& CIDR::MaskSize() {
  return this->maskSize;
}

const IPv4& CIDR::SubnetID() {
  return this->subnetIDAddress;
}

const IPv4& CIDR::StartAddress() {
  return this->startAddress;
}

const IPv4& CIDR::EndAddress() {
  return this->endAddress;
}

const IPv4& CIDR::BroadcastAddress() {
  return this->broadcastAddress;
}

const unsigned int& CIDR::MaxSubnets() {
  return this->maxSubnets;
}

const unsigned int& CIDR::MaxHostsPerSubnet() {
  return this->maxHostsPerSubnet;
}

bool CIDR::overlaps(CIDR* subnet) {
  unsigned short commonMask = std::min(this->maskSize, subnet->maskSize);

  IPv4 firstSignificantBits = this->ipAddress & (IPv4::MAX + 1 - (2 << (31 - commonMask)));
  IPv4 secondSignificantBits = subnet->ipAddress & (IPv4::MAX + 1 - (2 << (31 - commonMask)));

  IPv4 overlapBits = firstSignificantBits ^ secondSignificantBits;
  bool overlapResult = overlapBits.getInt() == 0;

  return overlapResult;
}
