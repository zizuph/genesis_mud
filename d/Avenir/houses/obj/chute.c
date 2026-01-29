// creator(s):  Lilith Feb 2022
// purpose:     A garbage chute 


#pragma strict_types
inherit "/std/container";

#include <macros.h>
#include <cmdparse.h>
#include <stdproperties.h>

public int alarm_id;

public void
create_container()
{
    set_adj(({"small", "trash", "garbage", "rubbish"}));
    set_name("chute");
    add_name(({"bin", "can"}));	
    set_short("small chute");
    set_long("This "+ short() +" looks like it goes quite a ways "+
	"down. A faint reddish-orange glow can be seen somewhere "+
	"inside it. This is where useless items are given to "+
	"the fiery bowels of the earth.\n");

    add_prop(OBJ_I_VALUE,  87); // no one can get it anyway..
    add_prop(CONT_I_WEIGHT, 1500000);    // 1500 kilos
    add_prop(CONT_I_VOLUME, 40000);      // 40 litres
    add_prop(CONT_I_MAX_VOLUME, 90000);  // 90 litres
    add_prop(CONT_I_MAX_WEIGHT, 2500000); // 250 kilos
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
