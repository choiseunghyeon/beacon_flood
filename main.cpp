#include <tins/tins.h>
#include <thread>
#include <chrono>

using namespace Tins;

Dot11Beacon setbeacon(std::string wfname);

Dot11Beacon setbeacon(std::string wfname){
    Dot11Beacon beacon;
    beacon.addr1(Dot11::BROADCAST);
    beacon.addr2("00:01:02:03:04:05");
    beacon.addr3(beacon.addr2());
    beacon.ssid(wfname);
    beacon.ds_parameter_set(8); // channel 8
    beacon.supported_rates({ 1.0f, 5.5f, 11.0f });
    beacon.rsn_information(RSNInformation::wpa2_psk());
    return beacon;
}

int main() {
    PacketSender sender;
    RadioTap rt1,rt2,rt3; // radio protocol
    rt1.inner_pdu(setbeacon("길길짱잘생김"));
    rt2.inner_pdu(setbeacon("choi"));
    rt3.inner_pdu(setbeacon("hard"));
    // rt.inner_pdu(setbeacon(d));

    while(1){
    sender.send(rt1,"wlx18a6f717a1e6");
    sender.send(rt2,"wlx18a6f717a1e6");
    sender.send(rt3,"wlx18a6f717a1e6");
    std::this_thread::sleep_for(std::chrono::milliseconds(100)); //beacon frame send 100ms
    }
}
