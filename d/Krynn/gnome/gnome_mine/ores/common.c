/*  
    Common listing for Ores and others

    Made by: Maelstrom, 2016/01

*/

#include "money.h"

mapping ORE_COPPER=	([
						"name"   : MONEY_TYPES[MONEY_CC_INDEX],
						"desc"   : "Some " + MONEY_TYPES[MONEY_CC_INDEX] + " ore, enough to make one coin.\n",
						"value"  : MONEY_VALUES[MONEY_CC_INDEX],
						"rarity" : 60,
						"weight" : MONEY_WEIGHT[MONEY_CC_INDEX],
						"volume" : MONEY_VOLUME[MONEY_CC_INDEX]
					]);

mapping ORE_SILVER=	([
						"name"   : MONEY_TYPES[MONEY_SC_INDEX],
						"desc"   : "Some " + MONEY_TYPES[MONEY_SC_INDEX] + " ore, enough to make one coin.\n",
						"value"  : MONEY_VALUES[MONEY_SC_INDEX],
						"rarity" : 20,
						"weight" : MONEY_WEIGHT[MONEY_SC_INDEX],
						"volume" : MONEY_VOLUME[MONEY_SC_INDEX]
					]);

mapping ORE_GOLD=	([
						"name"   : MONEY_TYPES[MONEY_GC_INDEX],
						"desc"   : "Some " + MONEY_TYPES[MONEY_GC_INDEX] + " ore, enough to make one coin.\n",
						"value"  : MONEY_VALUES[MONEY_GC_INDEX],
						"rarity" : 10,
						"weight" : MONEY_WEIGHT[MONEY_GC_INDEX],
						"volume" : MONEY_VOLUME[MONEY_GC_INDEX]
					]);

mapping ORE_PLATINUM=([
						"name"   : MONEY_TYPES[MONEY_PC_INDEX],
						"desc"   : "Some " + MONEY_TYPES[MONEY_PC_INDEX] + " ore, enough to make one coin.\n",
						"value"  : MONEY_VALUES[MONEY_PC_INDEX],
						"rarity" : 5,
						"weight" : MONEY_WEIGHT[MONEY_PC_INDEX],
						"volume" : MONEY_VOLUME[MONEY_PC_INDEX]
					]);

mapping ORE_MITHRIL=([
						"name"   : "mithril",
						"desc"   : "Some mithril ore.\n",
						"value"  : 2000,
						"rarity" : 1,
						"weight" : 20,
						"volume" : 1
					]);

mapping ORE_COAL=	([
						"name"   : "coal",
						"desc"   : "Some coal.\n",
						"value"  : 10,
						"rarity" : 60,
						"weight" : 25,
						"volume" : 2
					]);

mapping ORE_NITRE=	([
						"name"   : "nitre",
						"desc"   : "Some nitre.\n",
						"value"  : 10,
						"rarity" : 60,
						"weight" : 20,
						"volume" : 2
					]);

mapping ORE_SULFUR=	([
						"name"   : "sulfur",
						"desc"   : "Some sulfur.\n",
						"value"  : 10,
						"rarity" : 60,
						"weight" : 15,
						"volume" : 2
					]);

mapping ORE_IRON=	([
						"name"   : "iron",
						"desc"   : "Some iron ore.\n",
						"value"  : 40,
						"rarity" : 30,
						"weight" : 30,
						"volume" : 2
					]);

mapping ORE_ZINC=	([
						"name"   : "zinc",
						"desc"   : "Some zinc ore.\n",
						"value"  : 20,
						"rarity" : 50,
						"weight" : 20,
						"volume" : 1
					]);

mapping ORE_LEAD=	([
						"name"   : "lead",
						"desc"   : "Some lead ore.\n",
						"value"  : 10,
						"rarity" : 60,
						"weight" : 40,
						"volume" : 2
					]);

mapping ORES= 		([
						"copper"	: ORE_COPPER,
						"silver"	: ORE_SILVER,
						"gold"		: ORE_GOLD,
						"platinum"	: ORE_PLATINUM,
						"mithril"	: ORE_MITHRIL,
						"coal"		: ORE_COAL,
						"nitre"		: ORE_NITRE,
						"sulfur"	: ORE_SULFUR,
						"iron"		: ORE_IRON,
						"zinc"		: ORE_ZINC,
						"lead"		: ORE_LEAD
					]);


mapping STONE_ROCK=	([
						"name"   : "rock",
						"desc"   : "Some rock.\n",
						"value"  : 5,
						"rarity" : 80,
						"weight" : 50,
						"volume" : 2
					]);

mapping STONES=		([
						"rock"		: STONE_ROCK
					]);

mapping CRYSTAL_ENERGY=	([
							"name"   : "energy crystal",
							"desc"   : "An energy crystal!\n",
							"value"  : 3000,
							"rarity" : 1,
							"weight" : 10,
							"volume" : 1
						]);

mapping CRYSTALS=	([
						"energy"	: CRYSTAL_ENERGY
					]);

//select key randomly, using percentages.
//negative percents are ignored.
string
random_by_percent(int seed, mapping key_value_pair, string value_percent)
{
    int random_select;
    int sum_values = 0;
    int rnd_chance = 0;

    foreach(mixed key, mixed value: key_value_pair)
    {
    	if (value[value_percent] > 0)
    	{
	        sum_values += value[value_percent];
    	}
    }

    if (seed == 0)
    {
        random_select = random(sum_values);
    }
    else
    {
        random_select = random(sum_values, seed);
    }

    foreach(mixed key, mixed value: key_value_pair)
    {
    	if (value[value_percent] > 0)
    	{
	        rnd_chance += value[value_percent];
	    }

        if (rnd_chance >= random_select)
        {
            return key;
        }
    }
}