/*
 * This dragon is used as dragonsteed in dragonarmies
 *
 * Navarre June 17th 2007 : Changed leave_area_fight to
 *                          be sure to pass object in to
 *                          alarms.
 * Navarre July 22nd 2007 : Removed alarm before alarm is set
 *      
 */
#pragma strict_types
#pragma save_binary

inherit "/d/Krynn/std/dragon_base";

#include "../guild.h"

#include <macros.h>
#include <composite.h>
#include <cmdparse.h>
#include <stdproperties.h>
#include <ss_types.h>
#include <filter_funs.h>

static object back, summoner, msg_relay;
int size, fight = 0, restless = 0, alarm = 0;
int leaving_alarm = 0;

object
query_msg_relay()
{
    return msg_relay;
}

void
set_summoner(object ob)
{
    summoner = ob;
    set_colour(ob->query_dragonarmy_division());
    switch(ob->query_dragonarmy_promotions() - 2)
    {
    case 2:
	size = 2;
	set_age("ancient");
	break;
    case 1:
	size = 1;
	set_age("adult");
	break;
    default:
	size = 0;
	set_age("young");
    }
}

object
query_summoner()
{
    return summoner;
}

int
query_dragon_size()
{
    return size;
}

public object *
query_dragon_occupied()
{
    return back->query_dragon_occupied();
}

private int
check_fighting(object ob)
{
    return !!ob->query_attack();
}

public void
leave_area()
{
    int i;
    object *arr = query_dragon_occupied();

    if ((member_array(summoner, arr) > -1) && !restless)
    {
	restless = 1;
	summoner->catch_tell("Your dragon is growing restless.\n"+
	  "It will fly away soon alone if you do not command him to destination.\n");
	alarm = set_alarm(15.0, 0.0, leave_area);
	return;
    }

    for (i = 0; i < sizeof(arr); i++)
    {
	if (!living(arr[i]))
	    continue;

	if (interactive(arr[i]) || arr[i]->query_npc())
	{
	    arr[i]->command("$dismount dragon");
	    continue;
	}

	arr[i]->move_living("M", OWN_STATUE, 1);
	OWN_STATUE->set_revive_dest(arr[i], file_name(E(TO)));
    }

    move_living("into the sky", TEMP_DRAGON_ROOM, 1, 1);
    remove_object();
}

public void
leave_area_fight(object me)
{
    int i;
    object* arr;


    if(!me)
    {
	return;
    }
    arr = filter(FILTER_LIVE(all_inventory(E(TO))), check_fighting);

    if (!sizeof(arr))
    {
	fight = 0;
	remove_alarm(leaving_alarm);
	leaving_alarm = set_alarm(5.0, 0.0, &leave_area_fight(me));
	return;
    }

    arr = query_dragon_occupied();
    if ((member_array(summoner, arr) > -1) && !fight)
    {
	fight = 1;
	remove_alarm(leaving_alarm);
	leaving_alarm = set_alarm(5.0, 0.0, &leave_area_fight(me));
	return;
    }

    for (i = 0; i < sizeof(arr); i++)
    {
	if (!living(arr[i]))
	    continue;

	if (interactive(arr[i]) || arr[i]->query_npc())
	{
	    arr[i]->command("$dismount dragon");
	    continue;
	}

	arr[i]->move_living("M", OWN_STATUE, 1);
	OWN_STATUE->set_revive_dest(arr[i], file_name(E(TO)));
    }

    move_living("into the sky", TEMP_DRAGON_ROOM, 1, 1);
    remove_object();
}

void
check_back()
{
    if (!back)
    {
	setuid();
	seteuid(getuid());
	back = clone_object(DRAGONARMY_DRAGON + "dragon_back");
	back->set_dragon(TO);
    }
}

object
query_back()
{
    return back;
}

string
passenger_desc()
{
    int i;
    object *pas = query_dragon_occupied();

    switch(sizeof(pas))
    {
    case 0:
	return "";
    default:
	return " with "+COMPOSITE_LIVE(pas)+" mounted on it";
    }
}

mixed
dragonsteed_no_attack()
{
    if(back->query_flying())
	return "Attack flying dragon? How???\n";
    return 0;
}

void
create_dragon_npc()
{
    setuid();
    seteuid(getuid());

    add_prop(LIVE_I_NEVERKNOWN, 1);

    setup_dragon();
    add_prop(OBJ_M_NO_ATTACK, "@@dragonsteed_no_attack");
    msg_relay = clone_object(DRAGONARMY_DRAGON + "msg_relay2");
    msg_relay->set_dragon(TO);
    //  set_alarm(45.0, 0.0, leave_area);
    set_alarm(0.0, 0.0, check_back);
    set_alarm(0.0, 0.0, &leave_area_fight(this_object()));
}

string
long_desc()
{
    return "Looming over you is one of the children of " +
    "Takhisis, "+LANG_ADDART(short()) +". This " +
    "massive reptile is covered with thick scales from its " +
    "sinuous tail to its sinister head, a formidable defense " +
    "overshadowed only by its awesome destructive capability. " +
    "You notice a large leather saddle, large enough for two, "+
    "on its back"+passenger_desc()+".\n";
}

public int
mount(string str)
{
    mixed *oblist;

    if (!strlen(str) ||
      !parse_command(str, all_inventory(E(TP)),	"[the] %i", oblist) ||
      !sizeof(oblist = NORMAL_ACCESS(oblist, 0, 0)))
    {
	NF(C(query_verb()) + " what?\n");
	return 0;
    }

    if (sizeof(oblist) > 1)
    {
	NF(C(query_verb()) + " what?  Be more specific.\n");
	return 0;
    }

    if(!oblist[0]->dragonarmy_dragon_mount())
    {
	NF("You can't seem to mount that.\n");
	return 0;
    }

    return 1;
}

public int
dragonarmy_dragon_mount()
{
    check_back();

    if (TP->query_prop("_wolf_i_riding"))
    {
	write("Mount dragon while riding wolf? Nonsense!\n");
	return 1;
    }

    if (TP != summoner && !present(summoner, back))
    {
	write("The "+short()+" turns to you and snarls as you attempt " +
	  "to mount it, making it very clear that you are not a " +
	  "welcome passenger without its summoner.\n");
	return 1;
    }
    if (sizeof(query_dragon_occupied()) > 1)
    {
	write("There is no space left for you on the "+short()+".\n");
	return 1;
    }
    if (TP != summoner &&
      member_array(TP, summoner->query_team_others()) < 0 &&
      TP->query_prop("_da_can_mount_dragon") != TO)
    {
	write("The "+short()+" turns to you and snarls as you attempt " +
	  "to mount it, making it very clear that only " +
	  "its riders teammates and invited guests are welcome passengers.\n");
	return 1;
    }

    say(({METNAME+ " mounts the "+short()+".\n",
	NONMETNAME+ " mounts the "+short()+".\n",
	"" }));
    write("You mount the "+short()+".\n");
    TP->move_living("M", back, 1);
    return 1;
}

void
init_living()
{
    ::init_living();
    add_action(mount, "mount");
}

public void
remove_object()
{
    msg_relay->remove_object();
    back->remove_object();
    ::remove_object();
}

public int
query_dragonarmy_dragon()
{
    return 1;
}

int
move(mixed dest, mixed subloc)
{
    int result = ::move(dest, subloc);
    msg_relay->move(E(TO), 1);

    restless = 0;
    if (alarm)
    {
	remove_alarm(alarm);
	alarm = 0;
    }
    if (MASTER_OB(E(TO)) != TEMP_DRAGON_ROOM)
    {
	alarm = set_alarm(45.0, 0.0, leave_area);
    }
    return result;
}

public object
clone_dragon_fear_object()
{
    setuid();
    seteuid(getuid());
    return clone_object(DRAGONARMY_DRAGON + "dragon_fear_obj");
}
