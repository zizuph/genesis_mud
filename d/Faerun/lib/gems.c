
/*
 * Gem cloning function
 * Inherit this into the file you want the gems cloned for
 * then call:
 *
 *      make_gems(number of gems to clone);
 *
 * -- Finwe, July 2006

19:19 Mercade tells you: The ranks are in SD_AV_TITLES definition.
19:19 Mercade tells you: So to transform the rank into a number, I guess you can do member_array(title, SD_AV_TITLES); or so.
19:19 Mercade tells you: The corresponding stat levels are in SD_AV_LEVELS.
/sys/state_desc.h
 */


#include "/d/Genesis/gems/gem.h"

#define PO  previous_object()

void make_gems(mixed dest, int num_of_gems)
{
    int index, counter, npc_stat, gem_type,
        clone_gems = 1, chance = random(9);
    string gem_name;
    object gem;

    npc_stat = dest->query_average_stat();

// Determine what gems for what npcs based on their stat size
// No gems for wanderer or smaller. players can sell their loot.
    switch(npc_stat)
    {
        case 0..52:
            clone_gems = 0;
            break;
        case 53..63:
            gem_type = GEM_EXTREMELY_COMMON;
            break;
        case 64..74:
            gem_type = GEM_VERY_COMMON;
            break;
        case 75..86:
            gem_type = GEM_COMMON;
            break;
        case 87..98:
            gem_type = GEM_SOMEWHAT_COMMON;
            break;
        case 99..124:
            gem_type = GEM_SLIGHTLY_COMMON;
            break;
        case 125..139:
            gem_type = GEM_SLIGHTLY_RARE;
            break;
        case 140..154:
            gem_type = GEM_SOMEWHAT_RARE;
            break;
        case 155..169:
            gem_type = GEM_RARE;
            break;
        case 170..189:
            gem_type = GEM_VERY_RARE;
            break;
        case 190..500:
            gem_type = GEM_EXTREMELY_RARE;
            break;
        default:
            gem_type = GEM_ALL;
    }

// determines % of how often gems are cloned into npcs
        if(clone_gems = 1)
        {
            for (counter = 0; counter < num_of_gems; counter++)
            {
    // randomly chooses a gem based on the gem type.
    // chooses a gem as good or less than the gem type.
                gem=RANDOM_GEM_BY_RARITY(gem_type);
                gem->move(this_object());
            }
        }
}

