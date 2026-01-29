#pragma save_binary
#pragma strict_types

inherit "/std/monster.c";

#include <ss_types.h>
#include "../ship.h"

#define TO this_object()

string occ;

string
random_color()
{
    switch (random(4))
    {
    case 0:
	occ = "rower";
	return "gondorian";
	break;
    case 1:
	occ = "prisoner";
	return "haradrim";
	break;
    case 2:
	occ = "prisoner";
	return "dunlending";
	break;
    case 3:
	occ = "convict";
	return "gondorian";
	break;
    }
}

public void
create_monster()
{
    string  color = random_color();
    
    set_name(occ);
    add_name( ({ color, "slave", }) );
    set_race_name("human");
    add_adj("strong");
    add_adj(color);
    set_long("He is a strong, "+color+" "+occ+".\n");

    default_config_npc(50);
    set_alignment(100);

    set_base_stat(SS_STR, 70);
    set_base_stat(SS_CON, 60);
}

public void
arm_me()
{
    seteuid(getuid());
    clone_object(OAR)->move(TO);
    command("wield oar");
}

/* solemnian prestige */
int query_knight_prestige() { return -2; }
