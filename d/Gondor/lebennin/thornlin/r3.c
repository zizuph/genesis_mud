#include "/d/Gondor/defs.h"
inherit (THORN_DIR + "out_door_master.c");

#include <language.h>
#include <macros.h>
#include "locals.h"

/*
object *farmer = allocate(2);
*/

void
create_area_room()
{
    set_areatype(4);
    set_areadesc("well travelled");
    set_whereis("in");
    set_treetype("oak");
    set_area("Thornlin");
    set_areaname("Lossarnach");
    set_land("Gondor");

    set_extraline("North of here you see some "+treetype+" trees. A trail "
      + "is disappearing between the trees, while the main road continues "
      + "east-west. To the south, there are fields.");

    add_item(({treetype+" trees",treetype+" tree","trees","tree"}),
      "The "+treetype+" trees are tall and proud.\n");
    add_item(({"trail", "path", }), BSN("The trail can only just be seen. "
	+ "It does not look like it is used frequently, but it does not seem "
	+ "to be abandoned either."));
    add_item(({"field", "fields", }), BSN("The fields spread south "
	+ "of the main road. There is not much to see on them and from "
	+ "where you are standing, it looks as if they continue to the "
	+ "horizon."));

    add_exit(THORN_DIR + "r2b","west",0,1);
    add_exit(THORN_DIR + "r4","east",0,1);
    add_exit(THORN_DIR + "f3","south",0,1);
    add_exit(THORN_DIR + "f4","southeast",0,1);

}

void
init()
{
    ::init();
    add_action("go_north","n");
    add_action("go_north","north");
}

int
go_north() 
{
    write("You follow the trail into the forest.\n");
    say(QCTNAME(TP)+" seems to follow the trail north.\n",TP);

    this_player()->move_living("north", THORN_DIR + "t1");
    this_player()->init_command("$look");
    return 1;
}




/*
void add_npcs() {
    int     ifa = sizeof(farmer);

    while (ifa--)
    {
	 if (!objectp(farmer[ifa]))
	 {
	 farmer[ifa] = clone_object(NPC_DIR + "farmer");
	 farmer[ifa]->arm_me();
	 farmer[ifa]->move_living("from the void", TO);
	 }
    }
}


void
reset_room()
{
    set_alarm(1.0, 0.0, "add_npcs");
}
*/
