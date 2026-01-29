/* creator(s):  Lilith Aug 1999
 * purpose:     Rubbish bin that empties itself.
 *
 * Revisions:
 * 	Lucius, Jan 2018: Some re-writes to make more generic.
 */
#pragma strict_types

inherit "/std/container";
#include <stdproperties.h>

public static int alarm_id;
public static string *randadj = ({
    "sturdy", "tall", "narrow", "circular", "deep",
    "small", "round", "square", "stone"
});
    

public void
create_container()
{
    set_adj(one_of_list(randadj));
    add_adj("rubbish");
    set_name("bin"); 
    set_long("This "+ short() +" looks like a good place to put "+
        "all of those items you no longer have a use for.\n");

    add_prop(OBJ_M_NO_GET, 1);
    add_prop(OBJ_I_VALUE,  87); // no one can get it anyway..
    add_prop(CONT_I_WEIGHT, 1500000);    // 1500 kilos
    add_prop(CONT_I_VOLUME, 40000);      // 40 litres
    add_prop(CONT_I_MAX_VOLUME, 90000);  // 90 litres
    add_prop(CONT_I_MAX_WEIGHT, 2500000); // 250 kilos
    add_prop(CONT_I_RIGID, 1);
}

public void
hook_do_empty(object *inv)
{
/*
    tell_room(environment(this_object()), 
        "A small child scurries in, gets an armload from the "+ 
        short() +" and hustles back out.\n");
 */
}

private void
do_empty(void)
{
    object *inv = all_inventory();

    alarm_id = 0;

    if (sizeof(inv))
    {
	hook_do_empty(inv);
	inv->remove_object();
    }
}

public void
enter_inv(object obj, object from)
{
    ::enter_inv(obj, from);

    if (!alarm_id)
	alarm_id = set_alarm(120.0, 0.0, do_empty);
}
