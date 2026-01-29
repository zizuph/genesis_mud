#pragma strict_types

#include "/d/Khalakhor/sys/defs.h"
#include <macros.h>
#include <ss_types.h>
#define  PARALYZE_NAME   "_banshee_paralyzer"

inherit "/std/paralyze";

public void
create_paralyze()
{
    add_name(PARALYZE_NAME);
    fail_message = "Your mind is too overcome with terror " +
        "to have any conscious control over your actions!\n";
    remove_time = 60;
}

public void
stop_paralyze()
{
    if (!objectp(environment()))
    {
        remove_object();
        return;
    }

    set_this_player(environment());
    
    write("You finally manage to shake off the fear of the " +
        "banshee which paralyzes you!\n");
    say(QCTNAME(TP) + " suddenly shakes "+ HIS_HER(TP) + 
        " head, as if suddenly coming to " + HIS_HER(TP) +
        " senses.\n");
    remove_object();
}

public void
init()
{
    ::init();
    environment()->add_stun();
}

public void
remove_object()
{
    environment()->remove_stun();
    ::remove_object();
}

public int
dispel_magic(int strength)
{
    int to_beat;

    to_beat = 100 + random(100);
    to_beat -= environment()->query_base_stat(SS_DIS);
    if (strength > to_beat)
    {
        environment()->catch_tell("You feel the fear of " +
            "the banshee wrenched away from you!\n");
        stop_paralyze();
        return 1;
    }
    return 0;
}
  
      
