#include <iostream>
#include <iomanip>
#include "ipv4.hh"
#include "cidr.hh"

void printCIDRInfo(CIDR* cidr) {
  std::cout << std::left << std::setfill(' ') << std::setw(11) << "CIDR: " << cidr->str() << std::endl;
  std::cout << std::left << std::setfill(' ') << std::setw(11) << "IP: " << cidr->IP().str() << std::endl;
  std::cout << std::left << std::setfill(' ') << std::setw(11) << "Mask: " << cidr->MaskAddress().str() << std::endl;
  std::cout << std::left << std::setfill(' ') << std::setw(11) << "Subnet ID: " << cidr->SubnetID().str() << std::endl;
  std::cout << std::left << std::setfill(' ') << std::setw(11) << "Begin: " << cidr->StartAddress().str() << std::endl;
  std::cout << std::left << std::setfill(' ') << std::setw(11) << "End: " << cidr->EndAddress().str() << std::endl;
  std::cout << std::left << std::setfill(' ') << std::setw(11) << "Broadcast: " << cidr->BroadcastAddress().str() << std::endl;
  std::cout << std::left << std::setfill(' ') << std::setw(11) << "Subnets: " << cidr->MaxSubnets() << std::endl;
  std::cout << std::left << std::setfill(' ') << std::setw(11) << "Hosts: " << cidr->MaxHostsPerSubnet() << std::endl;
}

int main(int argc, char* argv[]) {
  if ((argc < 2) || (argc > 3)) {
    std::cout << "usage: " << argv[0] << " <CIDR> [<CIDR>]" << std::endl;
    return 2;
  }

  auto cidr = new CIDR(argv[1]);
  printCIDRInfo(cidr);

  if (argc == 3) {
    auto secondCIDR = new CIDR(argv[2]);

    std::cout << std::endl;
    printCIDRInfo(secondCIDR);
    std::cout << std::endl;
    std::cout << cidr->str() << " x " << secondCIDR->str() << ": " << (cidr->overlaps(secondCIDR) ? "overlaps" : "does not overlap") << std::endl;

    delete secondCIDR;
  }

  delete cidr;

  return 0;
}
