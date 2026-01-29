// file name: d/Avenir/common/outpost/tower_middle2.c
// creator(s):  Kazz    March '95
// purpose:     3rd floor/room of the tower, to drop tomatoes from in
//		        the tomato-drop quest.
// last update: April 1995
//              Nov 1995: Added missing 'You feel experienced...'
//              Feb 1996: Cirion: Redid reward with reward_quest function.
//		May 1996: Denis: Removed the usage of tomato_misc log and
//				 started using statserv instead.
//				 Also corrected some 'wrong things'.
//		Jun 1996: Denis: Corrected bug that arised with blind
//				 substitution of this_room() with this_object()
//		Denis, Jul'96:   Removed all traces of quest code whatsoever,
//				 Left just inheriting /d/Avenir/inherit/room
//              Lilith, Apri 2022: updated for fort makeover
//                 This room looks like it  
//                 should be tower_middle3 but due to all of the 
//                 quest-related code, keeping the file-names.
# pragma strict_types
#include "/d/Avenir/common/outpost/outpost.h"
inherit "/d/Avenir/common/outpost/fort_base";

void create_fort_room()
{
    set_short("the third floor with big window and Barber");
    set_long("This is the third floor of the largest tower "+
      "in Fort Sybarus. "+
      "Basalt stairs wind their way up and down along "+
      "the stone walls. "+
      "There is a very large window here that provides light "+
      "and a great view overlooking the interior of the fortress. "+
      "Wall lamps add even more illumination to the room. "+
      "There is a basalt bench for people to sit on while they "+
      "wait their turn with the barber who set up shop just "+
      "south of here.\n");

    add_exit("tower_office","up",0);
    add_exit("tower_middle3","down",0);
	add_exit("/d/Avenir/common/vanity/barber_shop", "south", 0);
	add_exit("/d/Avenir/common/vanity/barber_shop", "barber", 0, 0, 1);	

    room_add_object(OUTPOST +"obj/seats/basalt_bench", 1);
	add_npc(MON +"dw_guard", 1);

    add_fort_room();
    add_exit_views();

    add_item(({"window", "tower window", "opening", "large opening"}), 
      "The window is a large opening in the wall of thw tower, "+
	  "with a railing that prevents people from falling. "+
	  "It provides a view of the fort. If you <lean out window> "+
      "you can see the ground beneath the tower.\n" );
	  
    add_item(({"railing", "wrought iron railing"}),
      "There is a wrought iron railing placed across the lower "+
      "portion of the window to prevent people from falling when "+
      "they <lean out window> to have a better look around.\n");
	  
    add_item(({"stairs", "stair"}), 
      "Stairs made of basalt stone hug the walls. "+
      "One set rises up and the other, goes down.\n" );
	  
    add_item(({"tower", "black tower"}), 
      "The tower is made of the same black rock as much of the "+
      "fort. The bottom floor is below, and another is above.\n" );

	  
}
