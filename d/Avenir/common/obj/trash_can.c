// creator(s):  Lilith Aug 1999
// last update: 
// purpose:     Rubbish bin that empties itself.
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
    randadj = ({"sturdy", "tall", "narrow", "circular", "deep", 
                "small", "round", "square", "stone"});
    
    set_adj(randadj[random(sizeof(randadj))]);
    add_adj("rubbish");
    set_name("bin"); 
    set_long("This "+ short() +" looks like a good place to put "+
        "all of those items you no longer have a use for.\n");

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
        "A small child scurries in, gets an armload from the "+ 
        short() +" and hustles back out.\n");
    all_inventory()->remove_object();
    alarm_id = 0;
}

public void
enter_inv(object obj, object from)
{
    ::enter_inv(obj, from);

    if (alarm_id)
        return;

    alarm_id = set_alarm(120.0, 0.0, do_empty);
}


