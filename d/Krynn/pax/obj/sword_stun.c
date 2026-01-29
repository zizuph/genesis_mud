/*
 Stun object for Verminaard's sword.

 Idea from dragon fear coded by Erine & Jeremiah.

 Coded : 4/97 by Arman
 Modified by: Blizzard, 24/06/2003
*/


inherit "/std/object";
#include <macros.h>
#include <ss_types.h>
#include <stdproperties.h>
#include <cmdparse.h>
#include "/d/Krynn/common/defs.h"
#include "/d/Krynn/pax/local.h"

public   int no_command();
mixed    mouth_prop;
int      time;

object victim;


create_object() 
{
    seteuid(getuid());
    set_name("war_sword_stun");

    add_prop(OBJ_I_VOLUME, 0);
    add_prop(OBJ_I_WEIGHT, 0);
    add_prop(OBJ_I_NO_DROP, 1);
    add_prop(OBJ_I_NO_GIVE, 1);
    add_prop(OBJ_I_VALUE, 0);
    set_no_show();
}

init()
{
    ::init();
    add_action("do_all_commands", "", 1);
}


public int
do_all_commands(string str)
{
    string verb;
    string *not_allowed;

    not_allowed = ({"n", "north", "s", "south", "w", "west", "e", "east",
      "nw", "northwest", "sw", "southwest", "se", "southeast",
      "northeast", "ne", "u", "up", "d", "down", "teleport",
      "goto", "home", "ponder", "project", "play", "perform",
      "say", "rsay", "dsay", "ksay" });

    if (TP->query_wiz_level())
	return 0;

    verb = query_verb();
    if (member_array(verb, not_allowed) == -1)
	return 0;
    else
	return no_command();

    return 1;
}


int
no_command()
{
    write("You are still stunned by the force of the attack.\n");
    return 1;
}


void
remove_sword_stun(object victim)
{
    object vict = victim; 

    vict->catch_msg("You slowly recover your balance...\n");
    
    vict->remove_prop(LIVE_M_MOUTH_BLOCKED);
    vict->add_prop(LIVE_M_MOUTH_BLOCKED, mouth_prop);
    
    tell_room(E(vict), QCTNAME(vict) + " slowly recovers " + HIS(vict) +
        " balance...\n", vict, TO);

    vict->remove_stun();
    remove_object();
}

void
do_sword_stun()
{
    int time, undead;

    time       = 4 + random(4);
    undead     = 8 + random(4);
    mouth_prop = victim->query_prop(LIVE_M_MOUTH_BLOCKED);

    if ( !victim->query_wiz_level() )
    {
        victim->add_prop(LIVE_M_MOUTH_BLOCKED, "You wince in pain, since " +
            "the wound is really painful.\n");
        victim->add_stun();
    }

    if(victim->query_wiz_level())
	victim->catch_msg("As a wizard, you firmly stand on your feet.\n");

    if ( victim->query_prop(LIVE_I_UNDEAD) )
        set_alarm(itof(undead), 0.0, &remove_sword_stun(victim));
    else 
        set_alarm(itof(time), 0.0, &remove_sword_stun(victim));
        
    time = 0;
    undead = 0;
}


void
enter_env(object to, object from)
{
    ::enter_env(to, from);
    if(!objectp(to))
    {
	remove_object();
	return;
    }

    if(!living(to))
    {
	remove_object();
	return;
    }

    victim = to;
    do_sword_stun();
}
