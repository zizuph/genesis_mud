/* creator(s):  Lilith Aug 1999
 * purpose:     Rubbish bin that empties itself.
 *
 * Revisions:
 * 	Lucius, Jan 2018: Some re-writes to make more generic.
 *
 * Borrowed by Nerull.
 */
#pragma strict_types

inherit "/std/container";
#include <stdproperties.h>

public static int alarm_id;

public void
create_container()
{
    set_adj("magical");
    add_adj("rubbish");
    set_name("bin"); 
	
	set_short("magical rubbish bin");
    set_long("This "+ short() +" was once gifted to the "
	+"Vampires by the lich "
	+"Szass Tam as a reward for a well executed assignment. "
    +"Anything put into it will be regulary "
	+"teleported to some unknown outer plane, never to be "
	+"seen again.\n");

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
    tell_room(environment(this_object()), 
        "A weird white flash errupts from a small gap "
        +"between the lid and the "+short() +".\n");
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
	alarm_id = set_alarm(300.0, 0.0, do_empty);
}
