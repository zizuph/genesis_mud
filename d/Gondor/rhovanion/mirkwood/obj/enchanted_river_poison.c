/*
 *  Enchanted river poison, will put a player to sleep (paralyze them)
 *
 *  Created by Eowul, June 6th, 2015
 */

#include <poison_types.h>
#include <stdproperties.h>

inherit "/std/poison_effect";

 
 void
 create_poison_effect()
 {
     set_interval(20);
     set_time(500);
     set_damage( ({ }) );
     set_strength(100);
     set_poison_type("magic");
     set_silent(2);

     add_prop(OBJ_S_WIZINFO, "Special poison, used to put players to sleep "
        + "after touching the enchanted river.");
 }

public varargs void
start_poison(object poisoner)
{
    ::start_poison(poisoner);

    tell_object(poisonee, "Need to add paralyze\n");
}

public void
timeout()
{
    tell_object(poisonee, "Need to remove paralyze\n");   
    ::timeout();
}