inherit "/std/room";
#include "/d/Cirath/common/defs.h"
#include "/d/Cirath/common/teamer.h"
#include "wbt.h"

void
reset_room()
{
        bring_room_team(WWORK+"guard.c", 1, 1, WWORK+"guard.c", 1);
}

void
create_room()
{
   set_short("Path to Training Yard");
   set_long("You are on a small dirt path that leads towards "
   	+"the training courtyard of the Warrior's School of "
   	+"Tyr.  It is a simple path of dirt, lined with some "
   	+"sort of desert plant that looks to be anything but "
   	+"flourishing.  You can see young men training up "
   	+"ahead while instructors look on.\n");
   add_item("gate","This large marble gate is wide open "
        +"giving a good view of what appears to be a school of "
        +"some sort.\n");
   add_item("building","The building resembles a two story "
        +"barracks basically.\n");
  add_item("courtyard","The courtyard seems to be hard packed "
        +"earth, on which young men are practicing with "
        +"weapons.\n");
   add_item(({"men","young men"}),"They are practicing with "
        +"weapons in the courtyard.\n");
   add_item(({"person","older person","instructor"}),"They "
        +"are patrolling the courtyard and watching over the "
        +"young people that are practicing.\n");

        ADD_SUN_ITEM;
        OUTSIDE;

        add_exit(WWORK+"sq1.c", "north");
        add_exit(WWORK+"ent","east");
	set_alarm(1.0,0.0,"reset_room");
}

