/* Tantallon coded by Nick */

#include "/d/Krynn/common/defs.h"
#include "local.h"
inherit TANTALLON_INSIDE;

void
reset_tantallon_room() 
{
    if (!present("salamic"))
      set_alarm(1.0,0.0,"load_sal");
    if (!present("sal_guard"))
      set_alarm(1.0,0.0,"load_guard");
}

void
create_tantallon_room()
{
    object door;

    set_short("In a cell");
    set_long(BS(
    	"You are in a damp cell. It's cold and wet here. You don't suppose " +
    	"anyone could stay alive in here for more than a few days." +
	"", SL));

    add_item("walls", "The walls are cold, wet and covered with slime, Yuk.\n");

    add_exit(TDIR + "hole13", "north", 0);

    DARK;

    reset_room();
}


void
load_sal()
{ 
    clone_object(MON + "salamic")->move(TO);
    tell_room(TO, "Something is moving in the corner.\n");
}

void
load_guard()
{
    clone_object(MON + "sal_guard")->move_living("xx", TO);
}


