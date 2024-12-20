#pragma once

#include <random>
#include <deque>
#include <unordered_map>
#include <utils/constants.hpp>

// hash function for unordered map of SpellType
struct SpellTypeHash {
	std::size_t operator()(const SpellType& spell) const {
		std::hash<int> hasher; 	// create hash function 
		int spellInt = static_cast<int>(spell); // convert enum to int
		return hasher(spellInt);	// return hash of int
	}
};

class SpellQueue
{
public:
	SpellQueue();
	~SpellQueue();
	void collectSpell(SpellType spell);
	std::pair<SpellType, int> useSpell(bool is_first);
	void discardSpell(bool is_first);
	void replaceSpell(int position, SpellType spell);
	const std::deque<SpellType>& getQueue() const;
	void unlockSpell(SpellType type);
	const std::vector<SpellType> getMissingSpells();

	SpellType getLeftSpell() const { return firstSpell; }
	SpellType getRightSpell() const { return secondSpell; }

	// Used for relodability
	void setLeftSpell(SpellType spell) { firstSpell = spell; }
	void setRightSpell(SpellType spell) { secondSpell = spell; }

	void levelSpell(SpellType spell);
	const std::vector<std::pair<SpellType, int>> getCollectedSpells();
	const int getSpellLevel(SpellType spell);
	const int getSpellUpgradeTrack(SpellType spell);
	void addProgressSpell(SpellType spell, int count);
	bool hasSpell(SpellType spell);
	void doPlasmaSacrifice();
	bool isAbleToSacrifice();

private:
	SpellType firstSpell;
	SpellType secondSpell;
	void addSpell();
	SpellType getRandomSpell();

	std::deque<SpellType> queue;
	std::unordered_map<SpellType, int, SpellTypeHash> collectedSpells;
	std::mt19937 rng;

	std::unordered_map<SpellType, int, SpellTypeHash> upgradeTracker;
};
