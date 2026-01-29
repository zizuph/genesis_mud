/*
 * Lucius, Apr 2018:  Fixed duplicate messages.
 * Zizuph, Aug 2021:  Moved NPC actions to an alarm, as "steal"
                      depends on query_verb, which is lost when
                      the NPC does a command.
 */
#pragma strict_types

inherit "/std/container";
#include "../infidel.h"

private int alarm;

object *
infidels()
{
    if (!ENV(TO))
       return ({});

    return filter(all_inventory(ENV(TO)), &->id("avenir_infidel_id"));
}

void
reset_alarm()	{ alarm = 0; }

mixed
check_table()
{
    object *inf = infidels();

    if (!ENV(TO) || !present(TP, ENV(TO)))
	return 0;

    if (!sizeof(inf))
    {
	TP->add_prop("avenir_got_plans_from_table", 1);
	return 0;
    }

    foreach(object npc: inf)
    {
	if (!alarm && CAN_SEE(npc, TP) && CAN_SEE_IN_ROOM(npc))
	{
	    alarm = set_alarm(0.5, 0.0, reset_alarm);
        set_alarm(0.0, 0.0, &
	    npc->command("say Hey! Keep away from there."));
        say(QCTNAME(npc) + " blocks " + QTNAME(TP) +
		" from approaching the table.\n");
        }
	if (alarm)
	{
	    return npc->query_The_name(TP) + " blocks you " +
		"from approaching the table.\n";
	}
    }

    TP->add_prop("avenir_got_plans_from_table", 1);
    return 0;
}

void
create_container()
{
    set_name("table");
    set_short("table");
    set_adj(({"heavy","oak","oaken","scarred","old"}));
    set_long("It is a heavy, scarred oak table that seems to "
       + "have been here for a very long time. Scattered along "
       + "the surface are deep cuts, wine stains, and dust "
       + "filling the crevices.\n");

    set_no_show_composite(1);
    add_prop(CONT_M_NO_REM, VBFC_ME("check_table"));
    add_prop(CONT_M_NO_INS, VBFC_ME("check_table"));
    add_prop(CONT_I_RIGID, 1);
    add_prop(CONT_I_MAX_VOLUME, 50000);
    add_prop(CONT_I_MAX_WEIGHT, 50000);
    add_prop(CONT_I_VOLUME, 10000);
    add_prop(CONT_I_WEIGHT, 10000);
    add_prop(OBJ_M_NO_GET, "It is too big.\n");
}
