// creator(s):  Lilith Aug 1999
// last update: 
// purpose:     Hole in the ground to put trash in.
// bug(s):
// to-do:

inherit "/std/container";

#include "/d/Avenir/common/common.h"
#include <stdproperties.h>
#include <cmdparse.h>
#include <macros.h>

int alarm_id;

string *randadj;

void
create_container()
{
    
    set_adj(({"small", "irregular"}));
    set_name("hole"); 
    set_short("small dark hole");
    set_long("This "+ short() +" looks like it goes quite a way "+
        "down.  You can hear the sounds of water gurgling somewhere "+
        "inside it.\n");

    add_prop(OBJ_I_VALUE,  87); // no one can get it anyway..
    add_prop(CONT_I_WEIGHT, 1500000);    // 1500 kilos
    add_prop(CONT_I_VOLUME, 40000);      // 40 litres
    add_prop(CONT_I_MAX_VOLUME, 90000);  // 90 litres
    add_prop(CONT_I_MAX_WEIGHT, 2500000); // 250 kilos
    add_prop(CONT_I_RIGID, 1);

    seteuid(getuid(TO));
}

void
do_empty()
{
    tell_room(environment(this_object()), 
        "A sucking rush of air pulls through the "+ short() +
        " and flushes its contents away.\n");
    all_inventory()->remove_object();
    alarm_id = 0;
}

public void
enter_inv(object obj, object from)
{
    ::enter_inv(obj, from);

    if (alarm_id)
        return;

    alarm_id = set_alarm(80.0, 0.0, do_empty);
}


