// ===== Settings ===== //
const uint8_t channels[] = { 1, 6, 11 };  // used Wi-Fi channels (available: 1-14)
const bool wpa2 = false;                  // WPA2 networks
const bool appendSpaces = false;          // makes all SSIDs 32 characters long to improve performance

/*
  SSIDs:
  - don't forget the \n at the end of each SSID!
  - max. 32 characters per SSID
  - don't add duplicates! You have to change one character at least
*/
const char ssids[] PROGMEM = {
  "FBI Surveillance Van #119871\n"
  "DEA Surveillance #4188AEC2D\n"
  "I am the Internet, AMA\n"
  "Silence of the LANs\n"
  "House LANnister\n"
  "Winternet is Coming\n"
  "Ping's Landing\n"
  "This LAN is My LAN\n"
  "Get off My LAN!\n"
  "The Promised LAN\n"
  "The Internet is Assur\n"
  "Pretty Fly for a Wi-Fi\n"
  "This is Not Free Either\n"
  "God Save the Wi-Fi\n"
  "Help, I’m Trapped in a Router!\n"
  "A Song of Ice and Firewall\n"
  "Searching...\n"
  "404 Wi-Fi Unavailable\n"
  "Porque-Fi\n"
  "Titanic Syncing\n"
  "WeCanHearYouHavingSe\n"
  "Drop It Like It's Hotspot\n"
  "Text ###-#### for Password\n"
  "Wu-Tang LAN\n"
  "Keep it on the Download\n"
  "I Believe Wi Can Fi\n"
  "New England Clam Router\n"
  "FBI Van\n"
  "Futurama Planet Express\n"
  // The additional names
  "LANnisters Always Repay\n"
  "One Does Not Simply Log Into Mordor\n"
  "LANsterdam\n"
  "Connect and Die\n"
  "Wi Believe I Can Fi\n"
  "Keep It On The Download\n"
  "LAN Down Under\n"
  "Password Is Gullible\n"
  "Winternet is Coming\n"
  "The Mad Ping\n"
  "Everyday I'm Buffering\n"
  "Unprotected CeX\n"
  "Lord Voldemodem\n"
  "Accio Internet!\n"
  "The Triwizard Network\n"
  "Wi-Fi Guardium Leviosa\n"
  "LAN Solo\n"
  "Not A Pokestop\n"
  "Accio Wi-Fi!\n"
  "YerAWiFiHarry\n"
  "Connecto Patronum\n"
  "Hogwarts School Network\n"
  "Wi-Fi Is In The Air\n"
  "Quit Using My Wi-Fi!\n"
  "A LANnister Always Surfs\n"
  "Only For Zombies\n"
  "Virus Distribution Center\n"
  "FBI Surveillance Wagon\n"
  "Silence of the LAN\n"
  "Wi believe I can Fi\n"
  "Use The Force!\n"
  "I Can Haz Wireless?\n"
  "LAN of Milk and Honey\n"
  "The Promised LAN\n"
  "The Internet Is Lava\n"
  "Here's The Password Clue\n"
  "Network Not Found\n"
  "Connect and Die\n"
  "Trojan Virus\n"
  "Unprotected CeX\n"
  "Silence of the LANs\n"
  "No Free Wi-Fi For You\n"
  "The Whomping Wi-Fi\n"
  "Wu-Tang Wireless Clan\n"
  "Is This The Krusty Krab?\n"
  "The Not-So-Secret Room\n"
  "The Chamber of Wi-Fi\n"
  "This Is Not For You\n"
  "Your Wi-Fi Is In Another Castle\n"
  "Dunder Wi-Flinn\n"
  "Connect and Behave\n"
  "This LAN Is My LAN\n"
  "No Internet For You\n"
  "I Did Your Wi-Fi Last Night\n"
  "Unprotected Wi-Fi\n"
  "Bill Wi, The Science Fi\n"
  "Wi of the Tiger\n"
  "I’m RickJamesNetwork\n"
  "TellMyWiFiWantMyOwn\n"
  "Thou Shalt Not Connect\n"
  "Connect and Pay\n"
  "Your Session Has Expired\n"
  "99 problems but Wi-Fi ain't one\n"
  "The Password Is Nachos\n"
  "Wi-Fry Chicken\n"
  "Please Pay For Service\n"
  "Wi-Fi So Serious\n"
  "Hide Yo Wi-Fi\n"
  "Revenge of the Wi-Fi\n"
  "Use Beggars Can't Be Choosers\n"
  "No Free Wi-Fi For Moochers\n"
  "Call ### for Password\n"
  "Connection Impossible\n"
  "Password Wrong\n"
  "Your Grandma Likes My Wi-Fi\n"
  "Get Off My LAN Kid\n"
  "I Know Where U Live\n"
  "Sweet Victory\n"
  "Modem Family\n"
  "Wi-Fight The Inevitable\n"
  "Pretty Fly for a Wi-Fi\n"
  "LAN of the Free\n"
  "This LAN was Made for You and Me\n"
  "Breaking Wi-Fi\n"
  "Safehouse Network\n"
  "I Hate My Neighbor\n"
  "Quit Stealing My Paper\n"
  "Get Your Own\n"
  "Your Dog Poops In My Yard\n"
  "Clean Up Your Dog Poop\n"
  "Password Is Taco\n"
  "Your Music Is Annoying\n"
  "Your Snoring Is So Loud\n"
  "Shaken, Not Stirred\n"
  "Martin Router King Jr.\n"
  "NetFlix Streaming!\n"
  "Wi-Fry Chicken Again\n"
  "Your Girlfriend Noisy Too\n"
  "Your YouTube Ad Isn’t Original\n"
  "Changed The Password\n"
};


// ==================== //

// ===== Includes ===== //
#include <ESP8266WiFi.h>

extern "C" {
#include "user_interface.h"
  typedef void (*freedom_outside_cb_t)(uint8 status);
  int wifi_register_send_pkt_freedom_cb(freedom_outside_cb_t cb);
  void wifi_unregister_send_pkt_freedom_cb(void);
  int wifi_send_pkt_freedom(uint8* buf, int len, bool sys_seq);
}
// ==================== //

// run-time variables
char emptySSID[32];
uint8_t channelIndex = 0;
uint8_t macAddr[6];
uint8_t wifi_channel = 1;
uint32_t currentTime = 0;
uint32_t packetSize = 0;
uint32_t packetCounter = 0;
uint32_t attackTime = 0;
uint32_t packetRateTime = 0;

// beacon frame definition
uint8_t beaconPacket[109] = {
  /*  0 - 3  */ 0x80, 0x00, 0x00, 0x00,              // Type/Subtype: managment beacon frame
  /*  4 - 9  */ 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,  // Destination: broadcast
  /* 10 - 15 */ 0x01, 0x02, 0x03, 0x04, 0x05, 0x06,  // Source
  /* 16 - 21 */ 0x01, 0x02, 0x03, 0x04, 0x05, 0x06,  // Source

  // Fixed parameters
  /* 22 - 23 */ 0x00, 0x00,                                      // Fragment & sequence number (will be done by the SDK)
  /* 24 - 31 */ 0x83, 0x51, 0xf7, 0x8f, 0x0f, 0x00, 0x00, 0x00,  // Timestamp
  /* 32 - 33 */ 0xe8, 0x03,                                      // Interval: 0x64, 0x00 => every 100ms - 0xe8, 0x03 => every 1s
  /* 34 - 35 */ 0x31, 0x00,                                      // capabilities Tnformation

  // Tagged parameters

  // SSID parameters
  /* 36 - 37 */ 0x00, 0x20,  // Tag: Set SSID length, Tag length: 32
  /* 38 - 69 */ 0x20, 0x20, 0x20, 0x20,
  0x20, 0x20, 0x20, 0x20,
  0x20, 0x20, 0x20, 0x20,
  0x20, 0x20, 0x20, 0x20,
  0x20, 0x20, 0x20, 0x20,
  0x20, 0x20, 0x20, 0x20,
  0x20, 0x20, 0x20, 0x20,
  0x20, 0x20, 0x20, 0x20,  // SSID

  // Supported Rates
  /* 70 - 71 */ 0x01, 0x08,  // Tag: Supported Rates, Tag length: 8
  /* 72 */ 0x82,             // 1(B)
  /* 73 */ 0x84,             // 2(B)
  /* 74 */ 0x8b,             // 5.5(B)
  /* 75 */ 0x96,             // 11(B)
  /* 76 */ 0x24,             // 18
  /* 77 */ 0x30,             // 24
  /* 78 */ 0x48,             // 36
  /* 79 */ 0x6c,             // 54

  // Current Channel
  /* 80 - 81 */ 0x03, 0x01,  // Channel set, length
  /* 82 */ 0x01,             // Current Channel

  // RSN information
  /*  83 -  84 */ 0x30, 0x18,
  /*  85 -  86 */ 0x01, 0x00,
  /*  87 -  90 */ 0x00, 0x0f, 0xac, 0x02,
  /*  91 -  92 */ 0x02, 0x00,
  /*  93 - 100 */ 0x00, 0x0f, 0xac, 0x04, 0x00, 0x0f, 0xac, 0x04, /*Fix: changed 0x02(TKIP) to 0x04(CCMP) is default. WPA2 with TKIP not supported by many devices*/
  /* 101 - 102 */ 0x01, 0x00,
  /* 103 - 106 */ 0x00, 0x0f, 0xac, 0x02,
  /* 107 - 108 */ 0x00, 0x00
};

// Shift out channels one by one
void nextChannel() {
  if (sizeof(channels) > 1) {
    uint8_t ch = channels[channelIndex];
    channelIndex++;
    if (channelIndex > sizeof(channels)) channelIndex = 0;

    if (ch != wifi_channel && ch >= 1 && ch <= 14) {
      wifi_channel = ch;
      wifi_set_channel(wifi_channel);
    }
  }
}

// Random MAC generator
void randomMac() {
  for (int i = 0; i < 6; i++) {
    macAddr[i] = random(256);
  }
}

void setup() {
  // create empty SSID
  for (int i = 0; i < 32; i++)
    emptySSID[i] = ' ';

  // for random generator
  randomSeed(os_random());

  // set packetSize
  packetSize = sizeof(beaconPacket);
  if (wpa2) {
    beaconPacket[34] = 0x31;
  } else {
    beaconPacket[34] = 0x21;
    packetSize -= 26;
  }

  // generate random mac address
  randomMac();

  // start serial
  Serial.begin(115200);
  Serial.println();

  // get time
  currentTime = millis();

  // start WiFi
  WiFi.mode(WIFI_OFF);
  wifi_set_opmode(STATION_MODE);

  // Set to default WiFi channel
  wifi_set_channel(channels[0]);

  // Display all saved WiFi SSIDs
  Serial.println("SSIDs:");
  int i = 0;
  int len = sizeof(ssids);
  while (i < len) {
    Serial.print((char)pgm_read_byte(ssids + i));
    i++;
  }

  Serial.println();
  Serial.println("Started \\o/");
  Serial.println();
}

void loop() {
  currentTime = millis();

  // send out SSIDs
  if (currentTime - attackTime > 100) {
    attackTime = currentTime;

    // temp variables
    int i = 0;
    int j = 0;
    int ssidNum = 1;
    char tmp;
    int ssidsLen = strlen_P(ssids);
    bool sent = false;

    // Go to next channel
    nextChannel();

    while (i < ssidsLen) {
      // Get the next SSID
      j = 0;
      do {
        tmp = pgm_read_byte(ssids + i + j);
        j++;
      } while (tmp != '\n' && j <= 32 && i + j < ssidsLen);

      uint8_t ssidLen = j - 1;

      // set MAC address
      macAddr[5] = ssidNum;
      ssidNum++;

      // write MAC address into beacon frame
      memcpy(&beaconPacket[10], macAddr, 6);
      memcpy(&beaconPacket[16], macAddr, 6);

      // reset SSID
      memcpy(&beaconPacket[38], emptySSID, 32);

      // write new SSID into beacon frame, skipping quotes
      memcpy_P(&beaconPacket[38], &ssids[i], ssidLen);

      // set channel for beacon frame
      beaconPacket[82] = wifi_channel;

      // send packet
      if (appendSpaces) {
        for (int k = 0; k < 3; k++) {
          packetCounter += wifi_send_pkt_freedom(beaconPacket, packetSize, 0) == 0;
          delay(1);
        }
      }

      // remove spaces
      else {

        uint16_t tmpPacketSize = (packetSize - 32) + ssidLen;                 // calc size
        uint8_t* tmpPacket = new uint8_t[tmpPacketSize];                      // create packet buffer
        memcpy(&tmpPacket[0], &beaconPacket[0], 38 + ssidLen);                // copy first half of packet into buffer
        tmpPacket[37] = ssidLen;                                              // update SSID length byte
        memcpy(&tmpPacket[38 + ssidLen], &beaconPacket[70], wpa2 ? 39 : 13);  // copy second half of packet into buffer

        // send packet
        for (int k = 0; k < 3; k++) {
          packetCounter += wifi_send_pkt_freedom(tmpPacket, tmpPacketSize, 0) == 0;
          delay(1);
        }

        delete tmpPacket;  // free memory of allocated buffer
      }

      i += j;
    }
  }

  // show packet-rate each second
  if (currentTime - packetRateTime > 1000) {
    packetRateTime = currentTime;
    Serial.print("Packets/s: ");
    Serial.println(packetCounter);
    packetCounter = 0;
  }
}
