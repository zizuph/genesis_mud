/*
 * All things sinking from the surface end up here.
 *
 * We just remove the stuff for now.
 * Adapted into Khalakhor by Tapakah, 11/2021
 */
#include <filter_funs.h>
#include "../defs.h"

inherit "/std/room";

static int clean_alarm;

void
reset_room ()
{
   return;
}

void
create_room ()
{
   set_short("Darkness");
   set_long("Darkness.\n");
   
   reset_room();
}

void
clean_room ()
{
    object *arr;

    tell_room(this_object(), "A wave of destruction descends upon the " +
        "bottom of the sea.\n");
    
    arr = FILTER_DEAD(all_inventory());
    arr->remove_object();
}

void
enter_inv (object ob, object from)
{
    ::enter_inv(ob, from);

    if (!interactive(ob) && !get_alarm(clean_alarm))
      clean_alarm = set_alarm(5.0, 0.0, &clean_room());
}

void
die_seq ()
{  
   return;  
}
