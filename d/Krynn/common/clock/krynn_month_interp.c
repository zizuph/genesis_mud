#include "/d/Krynn/common/clock/clock.h"

static mapping gRaceIdx = ([ "ergothian":0, "elf":1, "kender":2, "human":3, "dwarf":4, "goblin":5 ]);

static mixed gMonthNames =
 ({ ({ "Aelmont", "Winter-Night", "Snowfun", "Newkolt", "Cold Lode", "Reward" }), \
    ({ "Rannmont", "Winter-Deep", "Darktime", "Deepkolt", "Dark Crypt", "Famine" }), \
    ({ "Mishamont", "Spring-Dawning", "Windsong", "Brookgreen", "Dark Keep", "Madness" }), \
    ({ "Chislmont", "Spring-Rain", "Raindrum", "Yurthgreen", "Damp Mood", "Girding" }), \
    ({ "Bran", "Spring-Blossom", "Flowerfield", "Fleurgreen", "Damp Chisel", "Scouting" }), \ 
    ({ "Corij", "Summer-Home", "Homefriends", "Holmswelth", "Dry Anvil", "Campaign" }), \
    ({ "Argon", "Summer-Run", "Wandertime", "Fierswelt", "Dry Axe", "Siege" }), \
    ({ "Sirrimont", "Summer-End", "Summerlaze", "Paleswelt", "Dry Heat", "Flame" }), \
    ({ "Reorxmont", "Autumn-Harvest", "Harvestfete", "Reapember", "Dry Forge", "Sack" }), \
    ({ "Hiddumont", "Autumn-Twilight", "Leafplay", "Gildember", "Cold Hammer", "Loot" }), \
    ({ "H'rarmont", "Autumn-Dark", "Bleakcold", "Darkember", "Cold Steel", "Betrayal" }), \
    ({ "Phoenix", "Winter-Come", "Blessings", "Frostkolt", "Cold Rust", "Pestilence" }) });

public string 
query_race_month( object player )
{
    int raceindex;
    if ( !(raceindex = gRaceIdx[player->query_race_name()]) ) raceindex = 0;
    return gMonthNames[CLOCK->query_month()][raceindex];
}
