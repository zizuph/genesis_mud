/*     Created by:     	Sir Toby, 97-06-23
 *     Location:       	North end of sewers. The lizards lair 
 *     Modified:	97-06-24, Toby
 */

inherit "/d/Kalad/room_std";
#include "/d/Kalad/defs.h"
#include "/d/Kalad/common/sewers/lizards_lair/path.h"

object bat;

void
reset_room()
{

   if (!bat)
      {
      bat = clone_object("/d/Kalad/common/sewers/npc/bat.c");
      bat -> move_living("M",TO);
      }
}


void
create_room()
{
::create_room();

    hear_bell = 1;

    set_short("Inside a tunnel");
    set_long("You are walking in a roughly cut and bending tunnel. " +
	     "It is very dark and narrow and smells from the dust. " +
	     "The walls and ceiling are all made of mud and " +
	     "supported by wooden beams. " + "@@dwarf_check");

    add_item( ({"wall","walls","mud wall","mud walls"}),
	     "The walls are cut directly out of the mud.\n");
    add_item("ceiling","The ceiling is cut directly out of the mud and " +
	     "supported by wooden beams.\n");
    add_item( ({"beam","beams","wooden beam","wooden beams"}),
	     "The beams are made out of fresh wood and supports the " +
	     "ceiling safely.\n");
    add_item("ground","The ground is made of mud. You notice many " +
             "strange tracks.\n");

    add_cmd_item("air",({"smell","sniff"}),
		 "The air smells of mud.\n");

    add_prop(ROOM_I_INSIDE,1);
    add_prop(ROOM_I_LIGHT,-1);

    add_exit(PATH + "ll2.c","east",0,1);
    add_exit(PATH + "ms_s1.c","west",0,1);
    set_noshow_obvious(1);

reset_room();

}


string
dwarf_check()
{
    if(TP->query_race() == "dwarf")
        return"The tunnel bends to the west and " +
	      "it slopes downwards to the east.\n";

    return"The tunnel stretches in an east western direction.\n";
}
