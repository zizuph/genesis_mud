/*
 * All things sinking from the surface end up here.
 *
 * We just remove the stuff for now.
 */
#include <filter_funs.h>

#include "/d/Ansalon/common/defs.h"
#include "/d/Ansalon/balifor/flotsam/local.h"

inherit FLOTSAM_OUT;

static int clean_alarm;

void
reset_flotsam_room()
{
   return;
}

create_flotsam_room()
{
   set_short("Darkness");
   set_long("Darkness \n");
   
   reset_flotsam_room();
}

void
clean_room()
{
    object *arr;

    tell_room(this_object(), "A wave of despair decends upon the " +
        "bottom of the bay.\n");
    
    arr = FILTER_DEAD(all_inventory());
    arr->remove_object();
}

void
enter_inv(object ob, object from)
{
    ::enter_inv(ob, from);

    if (!interactive(ob) && !get_alarm(clean_alarm))
    {
        clean_alarm = set_alarm(5.0, 0.0, &clean_room());
    }
}

void
die_seq()
{
   
   return;
   
}
