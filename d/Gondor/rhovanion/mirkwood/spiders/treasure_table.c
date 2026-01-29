#include "../defs.h"

inherit "/std/object";

/*
#define TREASURE_MINOR_CONSUME  "minor consume"
#define TREASURE_MAJOR_CONSUME  "major consume"
#define TREASURE_MINOR_ITEM1    "minor item 1"
#define TREASURE_MINOR_ITEM2    "minor item 2"
#define TREASURE_MINOR_ITEM3    "minor item 3"
#define TREASURE_MINOR_ITEM4    "minor item 4"
#define TREASURE_MINOR_ITEM5    "minor item 5"
#define TREASURE_MAJOR_ITEM1    "major item 1"
#define TREASURE_MAJOR_ITEM2    "major item 2"
#define TREASURE_MAJOR_ITEM3    "major item 3"
#define TREASURE_MAJOR_ITEM4    "major item 4"
#define TREASURE_MAJOR_ITEM5    "major item 5"
#define TREASURE_TOP_ITEM       "top item"
#define TREASURE_JUNK           "junk"
*/

public string 
determine_treasure_group(int nest_level) 
{
    switch(nest_level) 
    {
        case 1:
            switch(random(100) + 1) 
            {
                case 100:    return TREASURE_MAJOR_ITEM2;
                case 96..99: return TREASURE_MINOR_ITEM2;
                case 90..95: return TREASURE_MAJOR_ITEM1;
                case 80..89: return TREASURE_MINOR_ITEM1;
                case 68..79: return TREASURE_MAJOR_CONSUME;
                case 53..67: return TREASURE_MINOR_CONSUME;
                case 37..52: return TREASURE_JUNK;
                case 20..36: return TREASURE_JUNK;
                case  1..19: return TREASURE_JUNK;
            }
            break;
    }

    return TREASURE_JUNK;
}

public string
determine_treasure_chart(object player)
{
    switch(player->query_average_stat())
    {
        case   0.. 14: return "treasure_chart_novice";
        case  15.. 23: return "treasure_chart_greenhorne";
        case  24.. 32: return "treasure_chart_beginnner";
        case  33.. 42: return "treasure_chart_apprentice";
        case  43.. 52: return "treasure_chart_wanderer";
        case  53.. 63: return "treasure_chart_adventurer";
        case  64.. 74: return "treasure_chart_adept";
        case  75.. 86: return "treasure_chart_great_adventurer";
        case  87.. 98: return "treasure_chart_veteran";
        case  99..111: return "treasure_chart_expert";
        case 112..124: return "treasure_chart_rising_hero";
        case 125..139: return "treasure_chart_hero";
        case 140..154: return "treasure_chart_titan";
        case 155..169: return "treasure_chart_champion";
        case 170..189: return "treasure_chart_legend";
        case 190..500: return "treasure_chart_myth";
    }
}

public object *
create_treasure_for_player(object player, int nest_level)
{    
    string treasure_group = determine_treasure_group(nest_level);
    if (!stringp(treasure_group)) return ({ });

    string chart_file = determine_treasure_chart(player);
    if (!stringp(chart_file)) return ({ });

    setuid();
    seteuid(getuid());
    catch((MIRKWOOD_SPIDER_DIR + chart_file)->teleledningsanka());
    object chart = find_object(MIRKWOOD_SPIDER_DIR + "chart_file");
    if (!objectp(chart)) return ({ });

    object *result = chart->create_treasure_for_type(treasure_group, player);

    int junk_item_count = random(5) - sizeof(result);    
    for(int i = 0; i < junk_item_count; i++) 
    {
        result += chart->create_treasure_for_type(TREASURE_JUNK, player);
    }

    return result;
}