/*
  A path east of the Anduin near Lorien.
*/
 
#pragma strict_types

inherit "/d/Gondor/common/lib/area_room.c";
inherit "/d/Gondor/anduin/lib/and_funcs.c";
inherit "/d/Gondor/common/lib/drink_water.c";

#include <ss_types.h>
#include <macros.h>
#include <stdproperties.h>
#include "/d/Gondor/defs.h"
#include "/d/Gondor/std/tell.c"
#include "/d/Gondor/anduin/lib/and_defs.h"

public string  swim_river();

public void
create_gondor()
{
    set_short("In the shallows of a wide river");

    set_long(&long_desc());

    drinkable();

    set_tell_time(200);

    set_no_exit_msg(({"northeast", "southeast", "north"}), 
        "The banks of the river are too slippery in that direction.\n");
    set_no_exit_msg(({"southwest", "northwest"}), 
        "The swift flow of the river is too deep to cross in "
        + "that direction.\n");
    set_no_exit_msg(({"west"}), 
        "It may be possible to swim in that direction.\n");

    add_item(({"room", "area", "surroundings", "place"}), long_desc);
    add_item(({"bank", "banks", "west bank", "east bank"}), "The east "
        + "bank of the river is just a few yards away, but the west bank "
        + "is far across the river.\n");
	add_item(({"river", "mighty river", "anduin", "Anduin", "mighty anduin",
        "mighty Anduin", "flow", "swift flow", "water", "waters"}), "The "
        + "swift waters of the mighty Anduin churn all around you. The "
        + "water is only about a yard deep here.");

    add_tell("The swift flow of the river swirls around you.\n");
    add_tell("The river gurgles as it flows by.\n");
    add_tell("The river gurgles as it flows by.\n");
    add_tell("The moist, fresh scent of the river drifts on the air.\n");

    add_cmd_item(({"river", "anduin", "river anduin", "across", 
        "across river", "in river", "across anduin", "across the river", 
        "across the anduin", "across the river anduin", "Anduin", "west"}), 
        "swim", "@@swim_river");

    set_drink_from(({"river", "anduin", "Anduin", "river anduin", 
        "River Anduin", "flow", "swift flow", "mighty anduin", 
        "Mighty Anduin"}));

    add_prop(ROOM_I_NO_ALLOW_STEED, 1);

    add_exit(AND_PATH + "ap48", "east", 0, 3, 1);
    add_exit(AND_PATH + "ap48d", "south", 0, 3, 1);
}

string
long_desc()
{
    return "In the shallow water near the east bank of the river Anduin. "
        + sky_desc() + "the river as it flows swiftly south. The water "
        + "is fairly shallow here, and across it to the northwest a "
        + "dense forest of tall trees rises high above the river" 
        + mallorn_desc() +".\n"; 
}

public string
swim_river()
{
    if (TP->query_stat(SS_STR) > 40)
    {
        write("You swim out into the middle of the river.\n");
        say(QCTNAME(TP)+" swims out into the river.\n");
        TP->move_living("M", AND_PATH + "ap48c", 100);
        say(QCNAME(TP) + " arrives swimming across the river.\n");
    }
    return "";
}

public void
drink_message(string from)
{
    write("You drink some water from the River Anduin.\n"
        + "You feel refreshed.\n");
    say(QCTNAME(TP) + " drinks some water from the River Anduin.\n");
}

public void
drop_item(object ob, int silent)
{
    string down_room;

    down_room = "/d/Gondor/anduin/path/room/ap48bottom";
    if (ob && present(ob))
    {
        if (!silent)
        {
	    switch( ob->num_heap() )
	        {
	         case 0:
	             tell_room(TO,
		             "The "+ob->short()+" is swept downstream by the "
                      + "current.\n");
                 ob->move(down_room);
                 tell_room(down_room, CAP(LANG_ADDART(ob->query_short())) 
                     + " is swept in by the current.\n");
                 down_room->drop_item(ob);
	             break;
	         case 1:
	             tell_room(TO,
		         CAP(ob->short())+" is swept downstream by the current.\n");
                 ob->move(down_room);
                 tell_room(down_room, CAP(ob->short())+" is swept in by the "
                     + "current.\n");
                 down_room->drop_item(ob);
	             break;
	         default:
	            tell_room(TO,
		        CAP(ob->short())+" are swept downstream by the current.\n");
                ob->move(down_room);
                tell_room(down_room, CAP(ob->short())+" are swept in by the "
                    + "current.\n");
                down_room->drop_item(ob);
	            break;
	        }
        }
    }
}

public void
enter_inv(object ob, object from)
{
    ::enter_inv(ob, from);

    if(interactive(ob))
        start_room_tells();
        sky_add_items();
        lorien_add_items();

    if(!living(ob))
        set_alarm(1.0, 0.0, &drop_item(ob));
}

public void
init()
{
    ::init();
    init_drink();
}
