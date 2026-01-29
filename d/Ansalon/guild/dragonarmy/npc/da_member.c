/*
 * This is dragonarmy member basefile for the warfare system.
 * Milan
 */

#pragma strict_types

inherit "/d/Ansalon/guild/dragonarmy/npc/da_monster";
inherit "/d/Krynn/open/auto_teaming";

#include <macros.h>
#include <std.h>
#include "/d/Ansalon/common/defs.h"

int
query_not_accept_member(object ob)
{
    if (ob->query_color() != query_color())
	return 1;
    return 0;
}

mixed
random_da_move()
{
    mixed exits;
    string *cmd, area_name;
    int i;

    if (query_leader())
	return 100;

    exits = E(TO)->query_exit();
    if (!sizeof(exits))
    {
	set_alarm(1.0, 0.0, &stop_patrol());
	return 100;
    }

    area_name = E(TO)->query_area_name();
    cmd = ({ });
    for (i=0; i<sizeof(exits); i+=3)
	if ((objectp(exits[i]) || find_object(exits[i])) &&
	    (exits[i]->query_area_name() == area_name))
	    cmd += ({ exits[i+1] });

    if (!sizeof(cmd))
    {
	set_alarm(1.0, 0.0, &stop_patrol());
	return 100;
    }

    return cmd[random(sizeof(cmd))];
}

void
create_da_monster()
{
    
    if (random(3))
	set_race_name("human");
    else
	set_race_name("goblin");

    set_random_name();
    set_hunt_enemy();

    add_name("_da_member_");
    set_pick_up_team(({"_da_member_", "aurak", "sivak", "bozak", "kapak", "baaz"}));

    set_patrol_path(({ &random_da_move() }));
    set_alarm(20.0, 0.0, &start_patrol());
}

void
do_hunt_enemy(object who, string cmd)
{
    if (objectp(who) && !query_leader() &&
	E(TO)->query_area_name() == E(who)->query_area_name())
	::do_hunt_enemy(who, cmd);
}

void
init_living()
{
    /* Allow auto join */
    init_team_pickup();

    ::init_living();
}

void
react_introduce(string who)
{
    string sss;
    object tp = find_player(L(who));

    if (!tp || E(tp) != E(TO))
	return;

    switch(tp->query_guild_name_occ())
    {
    case "Calian warrior's guild":
    case "Solamnian Knights":
    case "Gondorian Rangers Guild":
    case "Dwarven Warriors of the Neidar Clan":
	switch(random(5))
	{
	case 0:
	    command("dsay Ha! Going to chase him around for a while");
	    break;
	case 1:
	    command("dsay Does he expects me to introduce back?");
	    break;
	default:
	}
	switch(random(5))
	{
	case 0:
	    command("dglare "+OB_NAME(tp));
	    break;
	case 1:
	    command("point "+OB_NAME(tp));
	    break;
	case 2:
	    command("grin "+OB_NAME(tp));
	    break;
	default:
	}
	break;
    case "Dragonarmy":
	if (!tp->query_met(TO))
	    command("introduce me to "+OB_NAME(tp));
	break;
    default: /* other guilds */
	if (tp->query_met(TO))
	    return;
	switch(random(6))
	{
	case 0:
	    command("dsalute "+OB_NAME(tp));
	    break;
	case 1:
	    command("dnod "+OB_NAME(tp));
	    break;
	case 2:
	    command("bow "+OB_NAME(tp));
	    break;
	case 3:
	    command("dsay Nice to meet you!");
	    break;
	default:
	    command("introduce me to "+OB_NAME(tp));
	}
    }
}

void
add_introduced(string who)
{
    set_alarm(itof(2 + random(4)), 0.0, &react_introduce(who));
}

public void
help_friend(object ob)
{
    if (ob && !query_attack() && E(ob) == E(TO))
	command("kill " + OB_NAME(ob));
}

