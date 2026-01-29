#pragma strict_types

inherit "/d/Ansalon/guild/dragonarmy/npc/da_monster";

#include <macros.h>
#include <std.h>
#include "/d/Ansalon/common/defs.h"

object *plist = ({});

void
create_da_monster()
{
    
    if (random(3))
	set_race_name("human");
    else
	set_race_name("goblin");

    set_random_name();
}

void
do_hunt_enemy(object who, string cmd)
{
    if (objectp(who) && wildmatch("/d/Ansalon/balifor/flotsam/*", file_name(E(who))))
	::do_hunt_enemy(who, cmd);
}

void
react_da_encounter()
{
    int i, t;
    object *da = ({});    /* these are DA members */
    object *fight = ({}); /* these fight blue */
    object *attack = ({});/* these we attack - ignored warning */
    object *warned = ({});/* these were warned recently */
    object *warn = ({});  /* these we should warn */
    object *rest = ({});  /* these we do not care much */
    object env = E(TO);
    string sss;

    for (i=0; i<sizeof(plist); i++)
    {
	if (objectp(plist[i]) && E(plist[i]) == env)
	{
	    if (plist[i]->query_dragonarmy_occ_member())
		da += ({ plist[i] });
	    else if ((plist[i]->query_attack())->query_color() == "blue")
		fight += ({ plist[i] });
	    else if (t = plist[i]->query_prop("_ordered_to_leave_flotsam"))
	    {
		if (time() - t > 100)
		    attack += ({ plist[i] });
		else
		    warned += ({ plist[i] });
	    }
	    else
	    {
		sss = plist[i]->query_guild_name_occ();
		if (sss == "Calian warrior's guild" ||
		    sss == "Solamnian Knights" ||
		    sss == "Gondorian Rangers Guild" ||
		    sss == "Dwarven Warriors of the Neidar Clan")
		    warn += ({ plist[i] });
		else
		    rest += ({ plist[i] });
	    }
	}
	plist = ({});	
    }

    if (i = sizeof(da))
    {
	if (i == 1)
	    command("dsalute "+OB_NAME(da[0]));
	else
	    command("dsalute all");
	if (sizeof(fight))
	    command("dsay I have strict orders from Lady Kitiara "+
			"to assist immediately.");
	else if (sizeof(attack))
	    command("dsay Our warnings are not to be taken lightly.");
    }
    if (i = sizeof(fight))
    {
	command("kill "+OB_NAME(fight[random(i)]));
	set_alarm(1.0, 0.0, &command("say No blue killing is allowed here!"));
	return;
    }
    if (i = sizeof(attack))
    {
	command("kill "+OB_NAME(attack[random(i)]));
	set_alarm(1.0, 0.0, &command("say You have been properly warned!"));
	return;
    }
    if (i = sizeof(warned))
    {
	command("dglare "+OB_NAME(warned[random(i)]));
	set_alarm(1.0, 0.0, &command("say Hey! You should be running out of here!"));
    }
    if (i = sizeof(warn))
    {
	warn->add_prop("_ordered_to_leave_flotsam", time());
	command("dhalt");
	command("say By order of Lady Kitiara no knight, neidar or "+
		"any of their helpers are acceptable withing Flotsam walls.");
	set_alarm(1.0, 0.0, &command("say Leave while I let you in peace."));
    }
/*
In the name of Kitiara, Highlord of the Blue Dragonarmy, I request you leave Flotsam at once!
Dwarven scum, didn't i ask you to leave? Get out of here before I smash you!
So! You think you can defy the Blue Dragonarmy! Then taste my steel!
*/
}

void
init_living()
{
    ::init_living();
    if (query_leader() || !interactive(TP) || query_attack() ||
	!TP->check_seen(TO))
	return;
    if (!sizeof(plist))
	set_alarm(1.0, 0.0, &react_da_encounter());
    if (member_array(TP, plist) < 0)
	plist += ({ TP });
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
	    command("dsay Ha! Going to chase him around Flotsam for a while");
	    break;
	case 1:
	    command("dsay Does he expects me to introduce back?");
	    break;
	case 2:
	    command("dsay There is always some fun while patroling Flotsam");
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

