/* The normal guards by Percy. */
/* Navarre April 2007: Updated stats on knights, they are too small */

#include "../../local.h"

inherit NPCSTD + "vin_knight_base";

#define OUTKEEP    VROOM + "gate"
#define KILL_FILE VLOG + "gateguard"
#define WRITE_THIS_LOG(file, msg) \
(write_file(file, ctime(time()) + " " + \
        this_player()->query_name() + "(" + \
        this_player()->query_average_stat() + ") " + \
        (msg)))          

int i_am_alarmed = 0;
private int alarm_id;  

void
create_knight_npc()
{
    set_level(3);
    set_alarm(0.1,0.0, "do_stats");
}

void do_stats()
{
    int i;
    for (i = 0; i < 6; i++)
	set_base_stat(i, 180 + random(6 * level));

    TO->set_hp(TO->query_max_hp());
}

public int
query_max_hp()
{
    return 7500;
}

int
alarm_me(string str)
{
    NF("What?\n");
    if(!(TP->id("knight") || TP->query_guild_name_occ() == "Solamnian Knights"))
	return 0;
    if (E(TO) == find_object(OUTKEEP))
	return 0;
    if (i_am_alarmed)
	return 0;
    if (str == "guard" || str == "guards")
    {
	i_am_alarmed = 1;
	NF("You alarm the guards.\n");
	if (str == "guards")
	    command("alarm guards");
	else
	    write("You alarm a guard.\n");
	command("out");
	command("south");
	command("south");
	do_rescue();
	return 1;
    }
    return 0;
}

void
set_me_alarmed(int i)
{
    i_am_alarmed = i;
}

void
fetch_help(object ob)
{
    E(TO)->alarm_guards(ob);
}

void
hook_attacked(object ob)
{
    set_alarm(rnd(), 0.0, &fetch_help(ob));
    
    if (ob->query_average_stat() > 130 && block_dir)
	set_alarm(2.0, 0.0, "@@do_block");

    if (ob->query_race_name() != "draconian")
	TO->do_rescue();
    TO->command("shout Vingaard has never fallen to Evil, and that will not change now!");
    WRITE_THIS_LOG( KILL_FILE, "attacked gateguard.\n" );

}

void
init_living()
{
    ::init_living();
    ADD(alarm_me,"alarm");
    if (interactive(TP) && TP->query_prop("_i_attacked_in_vingaard"))
	set_alarm(0.5, 0.0, &attack_func(TP));
}
