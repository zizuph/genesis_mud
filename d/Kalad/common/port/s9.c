#include "default.h"
inherit PORT_ROOM;

#include "/sys/stdproperties.h"
#include "/sys/macros.h"
#include "/sys/filter_funs.h"
int pres,i;
object *ob;
object ob1;

void
create_port_room()
{
    set_short("Narrow Street");
    set_long("You find yourself at the base of a huge cliff that towers "+
      "far above you to the north, and continues east and west into the "+
      "distance. You are travelling along a narrow street along the base of "+
      "the cliff. The cobblestones beneath you are moist and covered with "+
      "greenish grime. To the south is a large wooden building.\n");
    add_item(({"base","huge cliff","cliff"}),"The sheer rock walls of the "+
      "cliff look extremely hard, if not impossible to climb.\n");
    add_item(({"narrow street","street"}),"A small cobblestoned roadway at the "+
      "base of the cliff.\n");
    add_item(({"cobblestones","cobblestone"}),"The pavement is worn and cracked, "+
      "and seems to be covered in a thin film of moisture.\n");
    add_item(({"greenish grime","grime"}),"Rootless plants, such as moss "+
      "and lichen cover the pavement, apparently sustained by the constant "+
      "amount of water present.\n");
    add_item(({"large wooden building","large building","wooden building","building"}),
      "A rather large structure made out of hardwood planks. It is most "+
      "likely some sort of warehouse.\n");
    add_exit(PORT + "s8", "west");
    add_exit(PORT + "s25", "south", "@@query_move");
    add_exit(PORT + "s10", "east");
    reset_room();
}

reset_room()
{
    if(!ob1)
    {
	ob1 = clone_object(PORT + "npc/portguard_w");
	ob1 -> move_living("xxx", TO);
    }

}

query_move()
{
    object *ob;
    int pres,i;
    ob = FILTER_LIVE(all_inventory(this_object()));
    pres = 0;
    for(i = 0; i < sizeof(ob); i++){
	if(ob[i]->query_name() == "Aylmer"){
	    pres = 1;
	}

    }

    if (pres == 1){
	write("You are stopped by the militiaman.\n");
	say(QCTNAME(TP) + " tries to go south but is stopped by the militiaman.\n");
    }

    return pres;
}

