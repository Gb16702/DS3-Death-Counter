#pragma once

#include <unordered_map>
#include <string>
#include <cstdint>

inline const std::unordered_map<uint32_t, std::string> ZONE_NAMES = {
    {0, "None"},

    // High Wall of Lothric
    {300001, "High Wall of Lothric"},
    {300002, "Darkwraith Chamber"},
    {300003, "Tower on the Wall"},
    {300004, "Lower High Wall"},
    {300006, "Dancer of the Boreal Valley"},
    {300007, "Vordt of the Boreal Valley"},
    {300008, "High Wall of Lothric"},
    {300009, "High Wall of Lothric"},

    // Consumed King's Garden
    {300020, "Consumed King's Garden"},
    {300021, "Consumed King's Garden"},
    {300022, "Consumed King's Garden"},
    {300023, "Oceiros, the Consumed King"},
    {300024, "Consumed King's Garden"},

    // Lothric Castle
    {301000, "Lothric Castle"},
    {301001, "Dragon Barracks"},
    {301002, "Lothric Castle"},
    {301003, "Altar of Sunlight"},
    {301010, "Dragonslayer Armour"},
    {301011, "Lothric Castle"},

    // Undead Settlement
    {310000, "Foot of the High Wall"},
    {310001, "Dilapidated Bridge"},
    {310002, "Cliff Underside"},
    {310003, "Undead Settlement"},
    {310004, "Undead Settlement"},
    {310020, "Curse-rotted Greatwood"},
    {310021, "Undead Settlement"},

    // Archdragon Peak
    {320001, "Archdragon Peak"},
    {320002, "Archdragon Peak"},
    {320010, "Ancient Wyvern"},
    {320011, "Dragon-kin Mausoleum"},
    {320012, "Archdragon Peak"},
    {320013, "Archdragon Peak"},
    {320020, "Great Belfry"},

    // Road of Sacrifices / Farron Keep
    {330000, "Mausoleum Lift"},
    {330001, "Crystal Sage"},
    {330002, "Halfway Fortress"},
    {330010, "Abyss Watchers"},
    {330011, "Keep Ruins"},
    {330012, "Farron Keep"},
    {330013, "Old Wolf of Farron"},
    {330014, "Farron Keep"},
    {330015, "Farron Keep Perimeter"},
    {330020, "Road of Sacrifices"},
    {330021, "Road of Sacrifices"},
    {330022, "Crucifixion Woods"},

    // Grand Archives
    {341000, "Grand Archives"},
    {341001, "Grand Archives"},
    {341002, "Grand Archives"},
    {341003, "Grand Archives"},
    {341010, "Twin Princes"},
    {341011, "Grand Archives"},

    // Cathedral of the Deep
    {350000, "Deacons of the Deep"},
    {350001, "Cleansing Chapel"},
    {350002, "Cathedral of the Deep"},
    {350003, "Cathedral of the Deep"},
    {350004, "Cathedral of the Deep"},
    {350005, "Cathedral of the Deep"},
    {350010, "Rosaria's Bed Chamber"},
    {350011, "Cathedral of the Deep"},
    {350020, "Cathedral of the Deep"},

    // Irithyll of the Boreal Valley
    {370001, "Central Irithyll"},
    {370002, "Church of Yorshka"},
    {370003, "Distant Manor"},
    {370004, "Irithyll of the Boreal Valley"},
    {370005, "Irithyll of the Boreal Valley"},
    {370006, "Pontiff Sulyvahn"},
    {370007, "Irithyll of the Boreal Valley"},
    {370008, "Irithyll of the Boreal Valley"},
    {370010, "Irithyll of the Boreal Valley"},
    {370011, "Darkmoon Tomb"},
    {370012, "Anor Londo"},
    {370013, "Aldrich, Devourer of Gods"},

    // Catacombs of Carthus / Smouldering Lake
    {380000, "High Lord Wolnir"},
    {380001, "Catacombs of Carthus"},
    {380002, "Catacombs of Carthus"},
    {380003, "Catacombs of Carthus"},
    {380010, "Old Demon King"},
    {380011, "Smouldering Lake"},
    {380012, "Abandoned Tomb"},
    {380013, "Smouldering Lake"},
    {380014, "Smouldering Lake"},
    {380015, "Old King's Antechamber"},
    {380016, "Smouldering Lake"},
    {380020, "Catacombs of Carthus"},
    {380021, "Catacombs of Carthus"},

    // Irithyll Dungeon / Profaned Capital
    {390000, "Irithyll Dungeon"},
    {390001, "Irithyll Dungeon"},
    {390002, "Irithyll Dungeon"},
    {390003, "Profaned Capital"},
    {390004, "Profaned Capital"},
    {390005, "Yhorm the Giant"},
    {390006, "Profaned Capital"},

    // Untended Graves / Cemetery of Ash / Firelink Shrine
    {400000, "Champion Gundyr"},
    {400001, "Untended Graves"},
    {400002, "Dark Firelink Shrine"},
    {400010, "Untended Graves"},
    {400100, "Iudex Gundyr"},
    {400101, "Cemetery of Ash"},
    {400102, "Firelink Shrine"},
    {400110, "Firelink Shrine"},

    // Kiln of the First Flame
    {410000, "Soul of Cinder"},
    {410001, "Kiln of the First Flame"},
    {410002, "Flameless Shrine"},

    // Ashes of Ariandel
    {450000, "Sister Friede"},
    {450001, "Snowfield"},
    {450002, "Corvian Settlement"},
    {450003, "Snowy Mountain Pass"},
    {450004, "Snowfield"},
    {450005, "Ariandel Chapel"},
    {450006, "Ariandel Chapel"},
    {450010, "Champion's Gravetender"},
    {450011, "Depths of the Painting"},
    {450020, "Painted World of Ariandel"},

    // Arenas
    {460000, "Hollow Arena"},
    {470000, "Hollow Arena"},
    {530000, "Hollow Arena"},
    {540000, "Hollow Arena"},

    // TRC
    {500000, "Demon Prince"},
    {500001, "The Dreg Heap"},
    {500002, "Earthen Peak Ruins"},
    {500003, "Earthen Peak Ruins"},
    {500020, "The Dreg Heap"},
    {510000, "Spear of the Church"},
    {510001, "Mausoleum Lookout"},
    {510002, "Ringed Inner Wall"},
    {510003, "Ringed City Streets"},
    {510004, "Shared Grave"},
    {510005, "The Ringed City"},
    {510010, "Darkeater Midir"},
    {510011, "The Ringed City"},
    {510020, "Church of Filianore"},
    {511000, "Slave Knight Gael"},
    {511001, "Filianore's Rest"},
    {511010, "Filianore's Rest"},
    {511020, "Filianore's Rest"},
};

inline std::string GetZoneName(uint32_t zoneId) {
	auto it = ZONE_NAMES.find(zoneId);
	if (it != ZONE_NAMES.end()) {
		return it->second;
	}

	return "Unknown Area";
}
