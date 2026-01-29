#pragma strict_types;

#include "defs.h"
#include <config.h>

inherit SHIRE_ROOM;
inherit PARTY_COMMANDS;


void kick_out(object person);
void create_party_room();

void
create_shire_room()
{
    set_short("A Party Room");
    set_long("This is the base room long description.  Be "+
      "creative and actually make a long description for "+
      "this room you lazy dolt!\n");

    add_prop(ROOM_M_NO_ATTACK,"@@my_no_attack@@");
    add_prop(ROOM_M_NO_STEAL,"@@my_no_attack@@");
    create_party_room();
}

void
create_party_room() {}

nomask int
query_shire_party_room()
{
    return 1;
}

string
my_no_attack()
{
    if (!TP->query_prop("_i_was_warned"))
    {
	TP->add_prop("_i_was_warned" ,1);
	return "A hobbit taps you on your shoulder and whispers to you: "+
	"Behave yourself at the party. Actions like these are not "+
	"tolerated. Consider yourself warned.\n";
    }
    set_alarm(0.5,0.0,&kick_out(TP));
    return "A nearby hobbit, notices that you are up to trouble "+
    "and prevents you from starting any. The party is a peaceful "+
    "place to be enjoyed by all, and people like you aren't welcome.\n";
}

void
kick_out(object person)
{

    tell_room(TO,"A group of hobbits arrive in the room, and one of them "+
      "point a finger at "+QTNAME(person)+".  The hobbits then grab "+
      QTNAME(person)+" and proptly throw "+HIM_HER(person)+" out of the "+
      "party for behaving poorly.\n",person);
    person->catch_msg("A group of hobbits arrive in the room, and one "+
      "of them point a finger at you!  The hobbits then grab you and "+
      "promptly oust you from the party for your bad behavour.\n");
    person->add_prop(PARTY_BANISHED_PROP,1);
    if (!person->query_prop(LIVE_O_ROOM_BEFORE_PARTY))
	person->move_living("M",person->query_defualt_start_location());
    else
	person->move_living("M",person->query_prop(LIVE_O_ROOM_BEFORE_PARTY));
    person->remove_prop(LIVE_O_ROOM_BEFORE_PARTY);
    boot_log(CAP(person->query_real_name())+" was booted from the party "+
      "for trying to attack or steal from a guest!\n");
}

void
init()
{
    ::init();
    init_party_commands();
}

void
enter_inv(object ob,object from)
{
    ::enter_inv(ob,from);
    if (!interactive(ob))
	return;

    if (ob->query_prop(PARTY_BANISHED_PROP))
    {
	ob->catch_msg("You've been banished from the party for "+
	  "bad behavoir!\n");
	ob->move(from,1);
	return;
    }


    if (!ob->query_wiz_level() && !PARTY_MASTER->query_is_party())
    {
	if (!ob->query_prop(LIVE_O_ROOM_BEFORE_PARTY))
	{
	    if (file_name(from) != OWN_STATUE)
		ob->move(from, 1);
	    else
		ob->move(ob->query_default_start_location(), 1);
	}
	else
	    ob->move(ob->query_prop(LIVE_O_ROOM_BEFORE_PARTY), 1);
    }

    if (ob->query_prop(LIVE_O_ROOM_BEFORE_PARTY))
	return;
    ob->add_prop(LIVE_O_ROOM_BEFORE_PARTY,from);
    ob->catch_tell("\n\nWelcome to the party!!  Type 'help party' for more "+
      "information about the party.\n\n\n");
}
