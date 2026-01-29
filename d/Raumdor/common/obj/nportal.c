inherit "/std/object";

#include <ss_types.h>
#include <stdproperties.h>
#include <macros.h>
#include "/d/Faerun/guilds/nov/nov.h"


void
destroy_port()
{
	tell_room(environment(this_object()), "The "+this_object()->query_short() + " suddenly " +
	"collapses into itself and vanishes!\n");
        remove_object();
}

void
arrive_port()
{
	tell_room(environment(this_object()), "A huge black pentagram-shaped portal suddenly " +
	"materializes from nowhere!\n");

	this_object()->remove_name("pentagram");
	this_object()->set_name("portal");

	this_object()->set_adj("huge");
        this_object()->remove_name("rune");
        this_object()->remove_adj("floating");

	set_short("huge black pentagram-shaped portal");
        set_long("This is a huge black pentagram-shaped portal of black negative " +
        "energy. The huge black portal has a peculiar two-dimensional surface rising from the " +
        "ground resembling the shape of a pentagram. It is simply black, no variation " +
        "in colour and no dirt clinging to it.\n");

}


create_object()
{
    set_name("pentagram");
    add_name("drawing");
    set_adj("magical");
    add_adj("orange-glowing");
    set_short("magical orange-glowing pentagram");
    set_long("This is an orange-glowing drawing of a pentagram floating in mid air, created by " +
               "someone skilled in the arts of conjuration magic.\n");
    add_prop(OBJ_I_VALUE, 80000);
    add_prop(OBJ_I_WEIGHT, 2000);
    add_prop(OBJ_M_NO_SELL, 1);
    add_prop(OBJ_I_NO_STEAL, "This is just a drawing of a pentagram. Your hands pass through it " +
    "harmlessly.\n");
    add_prop(OBJ_M_NO_GET, "This is just a drawing of a pentagram. Your hands pass through it " +
    "harmlessly.\n");
    add_prop(OBJ_I_RES_MAGIC, 100);

    set_alarm(0.1,0.0, &arrive_port());
    set_alarm(120.0,0.0, &destroy_port());
}

int
do_port(string str)
{

	if (str == "portal" && this_object()->query_prop(IAMHEXRUNE))
	{
        write("What ?\n");
        return 1;
        }


        if(str != "portal")
        {
        write("What ?\n");
        return 1;
        }

        tell_room(NOV_DIR + "temple/nport", QCNAME(this_player()) + " suddenly arrives out of " +
        "nowhere!\n", this_player());

        tell_room(environment(this_object()), QCTNAME(this_player()) + " enters " +
        "the "+short()+"!\n", this_player());

        this_player()->move_living("M", NOV_DIR + "temple/nport", 1);

        return 1;
}



void
init()
{
    ::init();
    add_action(do_port, "enter");
}
