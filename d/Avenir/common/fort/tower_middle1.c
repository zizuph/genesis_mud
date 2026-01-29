// file name: d/Avenir/common/outpost/tower_middle1.c
// creator(s):  Kazz    Feb '95
// purpose:     1st floor above ground level
// note:        This room connects to the privvy (toilet)
// revisions:    Lilith, Apr 2022: rejiggered for Fort makeover.
//              Lilith, Apri 2022: updated for fort makeover
//                 This room looks like it should go up to 
//                 tower_middle2 but due to all of the 
//                 quest-related code, keeping the file-names.   	

#include "/d/Avenir/common/outpost/outpost.h"

inherit "/d/Avenir/common/outpost/fort_base";

void
create_fort_room()
{
    set_short("First floor with privvy access");
    set_long("This is the first floor of the tallest tower at Fort Sybarus. "+ 
       "The walls here are thick and dark, with narrow slits for windows. "+
	   "It is mostly quiet, save for the muted roar of the flaming pools "+
       "outside the gates. "+
	   "Some crystal and copper wall lamps gently illuminate the room. "+
       "The tower bumps out to the southwest, where a privvy seems "+
       "to be set up. "+ 
	   "A couple of benches have been placed here for those "+
       "awaiting their turn to use the facilities. "+
       "Two black stone stairways exit the room, one leading up and "+
	   "the other leading down.\n");

    add_exit("tower_middle3", "up",0);
    add_exit("tower_floor",   "down",0);
	add_exit("tower_privvy",  "southwest", 0);

    room_add_object(OBJ +"seats/basalt_bench", 1);
    room_add_object(OBJ +"seats/obsidian_bench", 1);
	add_npc(MON +"dw_guard", 1);
	
//    add_exit(OUTPOST + "shop", "east", 0);  moved up a level by Lilith
    add_fort_room();   
    add_exit_views();

    add_item(({"stairs", "stair"}), 
      "Stairs made of basalt stone hug the walls. "+
      "One set rises up and the other, goes down.\n" );

    add_item(({"slit", "slits", "window", "window slits", "windows"}),
      "There are window slits on the east and west sides of the room, good "+
      "for keeping watch and firing arrows through. They are too small for "+
      "even a halfling to fit through.\n");	  
	add_item( ({ "west window", "west facing window", "west slit"}), 
      "@@exa_window|You look through the window.\n|" + OUTPOST +"cave2@@");
	add_item( ({ "east window", "east facing window", "east slit"}), 
      "@@exa_window|You look through the window.\n|" + OUTPOST +"fort2@@");
    add_item(({"tower", "black tower"}), 
      "The tower is made of the same black rock as much of the "+
      "fort. The bottom floor is below, and another is above.\n" );
    add_item(({"stone", "black stone"}),
      "The stone is very smooth and black. Little light reflects "+
      "from it.\n" );
    add_item(({"privvy", "southwest"}), "There is a doorway to a "+
      "privvy here, where people do their bodily eliminations.\n");
    add_item(({"pool", "pools", "flaming pools"}), 
       "You can't see them without examining a window, but you "+
       "can see the wavering light and hear the roar coming from "+
       "them.\n");	   

} // create_room()


/*
 * Function name: exa_window
 * Description  : This lets people see the adjacent outside room.
 */
#define FILTER_SHOWN_COMPOSITE(x) \
    filter((x), &not() @ &->query_no_show_composite())
public string
exa_window(string desc, string room_file)
{
    object room = find_object(room_file),
    *in_room_p, *in_room_o;

    in_room_p = FILTER_CAN_SEE(
      FILTER_SHOWN_COMPOSITE(FILTER_LIVE(all_inventory(room))),
      this_player());
    in_room_o = FILTER_CAN_SEE(
      FILTER_SHOWN_COMPOSITE(FILTER_DEAD(all_inventory(room))),
      this_player());

    write((room_file)->long());

    if (sizeof(in_room_p))
        this_player()->catch_msg(capitalize(COMPOSITE_LIVE(in_room_p)) + 
          ".\n");

    if (sizeof(in_room_o))   
        this_player()->catch_msg(capitalize(COMPOSITE_DEAD(in_room_o))+ 
          ".\n");

    tell_room(ENV(TP), QCTNAME(TP) + " gazes through the window.\n", TP);

    return "";
} 

