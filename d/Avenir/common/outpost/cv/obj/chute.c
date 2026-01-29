// creator(s):  Lilith Aug 1999
// purpose:     Hole in the ground to put trash in.
#pragma strict_types
inherit "/std/container";

#include <macros.h>
#include <cmdparse.h>
#include <stdproperties.h>

public int alarm_id;
public string *randadj;

public void
create_container()
{
    set_adj(({"square"}));
    set_name("chute"); 
    set_short("square chute");
    set_long("This "+ short() +" looks like it goes quite a ways "+
	"down. A faint reddish-orange glow can be seen somewhere "+
	"inside it, and a draft of warm air emanates from it. This is "+
	"where useless items are given to the fiery bowels of the earth.\n");

    add_prop(OBJ_I_VALUE,  10); // no one can get it anyway..
    add_prop(CONT_I_WEIGHT, 1500000);    // 1500 kilos
    add_prop(CONT_I_VOLUME, 400000);      // 400 litres
    add_prop(CONT_I_MAX_VOLUME, 900000);  // 900 litres
    add_prop(CONT_I_MAX_WEIGHT, 2500000); //2500 kilos
    add_prop(CONT_I_RIGID, 1);

    set_no_show_composite(1);
}

private void
do_empty()
{
    alarm_id = 0;
    all_inventory()->remove_object();

    tell_room(environment(),
	"A sucking rush of heated air blows up through the "+
	short() +".\n");

}

public void
enter_inv(object obj, object from)
{
    ::enter_inv(obj, from);

    if (alarm_id)
	return;

    alarm_id = set_alarm(80.0, 0.0, do_empty);
}
