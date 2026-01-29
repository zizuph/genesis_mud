// file name: square_rm.c
// creator(s): Farlong
// last update: Ilyian (8 March, 1995)
// purpose:
// note: removed entrance to fall1, for now
// bug(s):
// to-do:

inherit "/std/room";
#include "/sys/stdproperties.h"
#include "park.h"
#include <macros.h>
#include "/d/Avenir/common/holm/wolf.h"

int check_vines();

int found;

void
reset_room()
{
	 found = 1;

}


/* Room 6 */


// init()
// {
//         ::init();
//         add_action("vines","search");
//         add_action("vines","investigate");
// }

create_room()
{
set_short("Square room");
set_long("This area is roughly square in shape, bordered"
		  +" by low stone walls which show the wear and tear of many"
		  +" years of erosion. Many small plants and brush dot the clearing."
		  +" In the center of this area sits an intriguing and rather"
		  +" odd-looking group of strangely-colored vines. You may follow"
		  +" a narrow path back to the west. There also appear to be two small"
		  +" rooms to the northeast and southeast.\n");

AE(PK+"slope","west",0);
AE(PK+"cell1","northeast",0);
AE(PK+"cell2","southeast",0);

add_prop(ROOM_I_LIGHT,1);
		  IN_IN
add_prop(OBJ_S_SEARCH_FUN,"do_search");
add_prop(OBJ_I_SEARCH_TIME,2);

add_item("path","The path leads away to"
		  +" the northeast, east and south. It is narrow and overgrown with"
		  +" weeds and other growth. The path was apparently made by"
		  +" humanoid hands, though in a time long past.\n");
add_item(({"stone","walls","wall","dust","stones"}),"The"
		  +" narrow path is lined by low stone walls that have begun to crumble"
		  +" away under time's great influence.\n");
add_item(({"growth","plants","undergrowth","brush","underbrush",
		  "canopy"}),"The vines, brush and other plant life"
		  +" are all around you, constantly impeding your progress. They"
		  +" seem almost driven to the task by some dark power.\n");

reset_room();

}

string
do_search(object player, string str)
{
	 object bone;

	 if (str == "vines")
	 {
	  if(found<1)
	  return "";

	  found--;

	  bone = clone_object(WOLF_BONE + "mandible.c");
	  bone->move(this_player(), 1);

	  return "You find a mandible bone!\n";
	  }

	  return "";
}

void
init()
{
	 ::init();
	 check_vines();
}

int
check_vines()
{
	 if(found<1)
	 {
		add_item(({"vine","vines","group"}),"The pile of vines"
		  +" is certainly different from any you've seen before.\n");
		return 1;
	 }

	 add_item(({"vine","vines","group"}),"The pile of vines"
		  +" is certainly different from any you've seen before. "
		  +"You see something white glittering in their midst.\n");

	 return 1;
}




//vines(string str)
//{
//  object *stuff;
//   int i;
//
//        notify_fail("What do you wish to look more closely at?\n");
//        if ((str=="vine")||(str=="vines")||(str=="group")||(str=="pile"))
//                {
//        write("As you approach the pile of vines in the center"
//        +" of the room, the floor falls through beneath you, and you find"
//        +" yourself and everything else falling through thin air,"
//        +" until at last you land hard on the floor of a"
//        +" deep pit!\n");
//    say("Suddenly, the floor gives way beneath you, and you"
//        +" are falling, along with everything else from the room above,"
//        +" until you at last come crashing down on the floor of"
//        +" a deep pit!\n");
//   stuff = all_inventory();
//     for (i = 0; i<sizeof(stuff); i ++)
//stuff[i]->move(PK+"fall1");
//                   return 1;
//                }
//        return 1;
//
//}


