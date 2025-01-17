#ifndef START_STATS_CLASS_H
#define START_STATS_CLASS_H

#include <vector>

#include "BaseDataClass.h"

#include ".\include\ItemsClass.h"

struct StartStatsStruct {

	uint32_t exp = 0;
	uint16_t weapon = 0;
	uint16_t armour = 0;
	uint16_t headgear = 0;
	uint16_t footwear = 0;
	uint16_t accessory = 0;
	uint16_t manaEgg = 0;
	int16_t stamina = 0;
	uint16_t unknown1 = 0;
	uint16_t unknown2 = 0;
	uint16_t unknown3 = 0;
	uint16_t unknown4 = 0;
	uint16_t unknown5 = 0;
	uint16_t unknown6 = 0;
	uint16_t unknown7 = 0;
	uint16_t unknown8 = 0;
	uint16_t unknown9 = 0;
	uint16_t unknown10 = 0;
	int16_t ipStun = 0;
	int16_t ipCancelStun = 0;
	uint8_t comboSpRegen = 0;
	uint8_t critSpRegen = 0;
	uint8_t unknown11 = 0;
	uint8_t hitSpRegen = 0;
	uint8_t unknown12 = 0;
	int8_t evasionStillRate = 0;
	int8_t evasionMovingRate = 0;
	int8_t ResistKnockback = 0;		// R KB from DreamCast Debug Menu
	uint16_t unknown13 = 0;
	int16_t TREC = 0;					// T REC from DreamCast Debug Menu
	int16_t TDMG = 0;					// T DMG from DreamCast Debug Menu
	uint16_t unknown14 = 0;
	int16_t THEAL = 0;				// T HEAL from DreamCast Debug Menu
	int16_t size = 0;
	uint16_t unknown15 = 0;
	uint16_t unknown16 = 0;
	uint16_t unknown17 = 0;
	uint16_t unknown18 = 0;
	uint16_t unknown19 = 0;
	uint16_t unknown20 = 0;
	uint16_t unknown21 = 0;
	uint16_t unknown22 = 0;
	uint16_t unknown23 = 0;

};

class StartStatsClass : public BaseDataClass {

public:
	StartStatsClass() {};
	void write();
	void read(std::string);
	void draw();
	void outputToCSV();
	void randomize();

	void storeItems(ItemStruct* items, size_t numItems) { _items = items; _numItems = numItems; };
	StartStatsStruct* getStartStats() {

		if (_startStats.size())
			return &_startStats.at(0);
		else
			return nullptr;

	};
	size_t getNumStartStats() { return _startStats.size(); };

private:
	std::vector<StartStatsStruct> _startStats;
	size_t _statIndex = 0;

	ItemStruct* _items = nullptr;
	size_t _numItems = 0;
};

#endif