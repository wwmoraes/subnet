#ifndef __CIDR_HH
#define __CIDR_HH

#include "ipv4.hh"

class CIDR {
  public:
    CIDR();
    CIDR(const std::string&);

    void set(const std::string&);

    operator std::string() const {
      return this->str();
    };

    const std::string str() const;
    const IPv4& IP();
    const IPv4& MaskAddress();
    const unsigned short& MaskSize();
    const IPv4& SubnetID();
    const IPv4& StartAddress();
    const IPv4& EndAddress();
    const IPv4& BroadcastAddress();
    const unsigned int& MaxSubnets();
    const unsigned int& MaxHostsPerSubnet();
    bool overlaps(CIDR* subnet);

  private:
    IPv4 ipAddress;
    IPv4 maskAddress;
    IPv4 subnetIDAddress;
    IPv4 startAddress;
    IPv4 endAddress;
    IPv4 broadcastAddress;
    unsigned short maskSize;
    unsigned int maxSubnets;
    unsigned int maxHostsPerSubnet;
};

#endif
