/*
	*Orcs outside the orc race guild
	*Altrus, May 2005
* Cotillion - 2020-09-29
* - Fixed type confusion
*/
#include <stdproperties.h>
#include <ss_types.h>
#include "/d/Shire/sys/defs.h"

#define ORCGLD_DIR "/d/Shire/guild/orc_guild/"

inherit SHIRE_MONSTER;

string get_adjective_one();
string get_adjective_two();

void create_shire_monster()
{
	set_name("orc");
	set_race_name("orc");
	set_adj(({get_adjective_one(), get_adjective_two()}));
	set_long("This orc looks like it is keeping watch over the area. What is it watching for?\n");

	set_gender(0);
	set_appearance(-95);
	set_alignment(-900 + random(100));
	set_stats(({120 + random(20), 155 + random(50), 180 + random(25), 50 + random(10), 25 + random(10), 70 + random(10)}));
	add_prop(CONT_I_WEIGHT, 35000 +random(500));
	add_prop(CONT_I_HEIGHT, 800 + random(20));

	set_skill(SS_DEFENCE, 65);
	set_skill(SS_PARRY, 35);
	set_skill(SS_UNARM_COMBAT, 60);
	set_skill(SS_WEP_SWORD, 75);
	set_skill(SS_WEP_KNIFE, 75);
	set_skill(SS_WEP_CLUB, 75);

	set_act_time(7);
	add_act("grumble");
	add_act("spit");
	add_act("curse");
	add_act("emote scratches his filth-encrusted body.");
	add_act("emote mutters something about dead elves.");
	add_act("emote curses the sun.");

	set_introduce(0);

    equip(({
    	ORCGLD_DIR + ({"iron_chainmail", "leather_armour", "leather_shirt"})[random(3)],
    	ORCGLD_DIR + ({"iron_greaves", "dented_greaves", "shin_guards"})[random(3)],
    	ORCGLD_DIR + ({"rusty_blade", "chipped_knife", "studded_club"})[random(3)],
    }));

    // changes messages for moving in and out of rooms
	set_m_out("stalks");
    set_m_in("stalks in");

}

public string get_adjective_one()
{
	string *adjectives, adj;

	adjectives = ({"ruthless", "smelly", "rude", "stinky", "muscular", "weak", "bold", "cowardly", "big-nosed", "gap-toothed", "long-haired"});

	adj = adjectives[random(sizeof(adjectives))];

	return adj;
}

public string get_adjective_two()
{
	string *adjectives, adj;

	adjectives = ({"sneaky", "stupid", "cunning", "long-armed", "grey-skinned", "green-skinned", "black-skinned", "loud", "quiet"});

	adj = adjectives[random(sizeof(adjectives))];

	return adj;
}
