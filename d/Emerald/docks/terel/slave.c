/* lake/npc/slave.c cloned by lake/slavedeck.c */
inherit "/d/Emerald/std/emerald_monster";

#include <ss_types.h>
#include "../defs.h"

static string
random_color()
{
    int i;
	
    i = random(27);
    if (i < 3)
	return "tall";
    else if (i < 6)
	return "muscular";
    else if (i < 7)
	return "mean";
    else if (i < 8)
	return "aggressive";
    else if (i < 9)
	return "agile";
    else if (i < 10)
	return "rough";
    else if (i < 11)
	return "tough";
    else if (i < 12)
	return "scarred";
    else if (i < 13)
	return "slow";
    else if (i < 14)
	return "steady";
    else if (i < 15)
	return "joking";
    else if (i < 16)
	return "powerful";
    else if (i < 17)
	return "sturdy";
    else if (i < 18)
	return "swift";
    else if (i < 19)
	return "cunning";
    else if (i < 20)
	return "sneaky";
    else if (i < 21)
	return "dominating";
    else if (i < 22) 
	return "intelligent";
    else if (i < 23)
	return "sexy";
    else if (i < 24)
	return "cold";
    else if (i < 25)
	return "methodical";
    else
	return "hellfire";
}

public void
create_emerald_monster()
{
    set_name("slave");
    add_adj("strong");
    add_adj(random_color());
    set_race_name("human");
    set_long("He is a very strong, " + query_adj(1)[1] + " slave.\n");

    default_config_npc(20);

    set_base_stat(SS_STR, 120);
    set_base_stat(SS_CON, 120);
    refresh_mobile();

    seq_new("do_stuff");
    seq_addfirst("do_stuff", ({ "@@get_oar", "say Let's get this ship moving, shall we?"}));
}

public void
get_oar()
{
    reset_euid();
    clone_object(DOCK_DIR + "terel/oar")->move(this_object());
    command("hold oar");
}

int query_slave() { return 1; }
