/*
Stun attack used by Serion
Idea from dragon fear coded by Erine & Jeremiah.
Coded : 4/97 by Arman
Altered to fit the race change done by a witch
in the forest of Mithas.
*/


inherit "/std/object";
#include <macros.h>
#include <ss_types.h>
#include <stdproperties.h>
#include <cmdparse.h>
#include "/d/Krynn/common/defs.h"
#include "/d/Krynn/pax/local.h"

int time;

object victim;

string real_race;

create_object() 
{
    seteuid(getuid());
    set_name("_toad_");
    
    add_prop(OBJ_I_VOLUME, 0);
    add_prop(OBJ_I_WEIGHT, 0);
    add_prop(OBJ_I_NO_DROP, 1);
    add_prop(OBJ_I_NO_GIVE, 1);
    add_prop(OBJ_I_VALUE, 0);

    set_no_show();
}

string
give_real_race(string real_race)
{
    return real_race;
}


string
query_auto_load()
{
    return "/d/Ansalon/goodlund/nethosak/forest/obj/toad_object:";
}

public void
init_arg(string arg)
{
    string ct;

    if (sscanf(arg, "%d", ct) == 1)
    {
        give_real_race(real_race);
    }
}


init()
{
    ::init();
}

void
become_normal(object victim)
{
    object vict = victim; 

    vict->catch_msg("You feel strange, as you body returns to "+
                    "it's original shape.\n");

    tell_room(E(vict), QCTNAME(vict) + " suddenly changes shape!.\n", vict, TO);

    vict->set_race_name(real_race);
    remove_object();
}


void
become_toad()
{
    int time;

    time = 100;
    real_race = victim->query_race_name();
    victim->catch_msg("You feel your body is suddenly "+
                      "changing.\n");
    victim->set_race_name("toad");

    tell_room(E(victim), QCTNAME(victim) + " is changed into "+
                           "a toad!\n", victim, TO);

    set_alarm(itof(time), 0.0, "become_normal", victim);
    time = 0;
}


void
enter_env(object to, object from)
{
    ::enter_env(to, from);
    if(!objectp(to))
    {
        become_normal(victim);
        remove_object();
        return;
    }

    if(!living(to))
    {
        become_normal(victim);
        remove_object();
        return;
    }

    victim = to;
    become_toad();
}

