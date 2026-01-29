/*
   Wayreth.

   study.c
   -------

   Coded ........: 95/06/02
   By ...........: Jeremiah

   Latest update : 95/07/14
   By ...........: Jeremiah

*/

#include "../guild.h"
inherit TOWERROOM;


void
create_tower_room()
{
   set_short("Central study room");
   set_long("You are standing in a very quiet room. The walls are " +
            "decorated with heavy tapestries and the floor with a " +
            "thick carpet, muffling any sounds made in here. A large " +
            "plaque on the wall reads : 'Please fare quiet in this " +
            "area, people are studying here.'\n"); 

   set_wall_type(1);

   add_item(({"tapestry", "tapestries"}), "Large and heavy tapestries " +
            "covering most of the walls in here, muffling the sounds " +
            "made in this room. The tapestries are simple and kept in " +
            "soft colours.\n");
 
   add_item("carpet", "A thick carpet, muffling the footsteps made " +
             "when people walk across the room.\n");
   
   add_item("plaque", "A nice wooden plaque reminding you to be " +
            "quiet in here, as this is an area where people study.\n");

   add_exit("studyroomn", "north", 0);
   add_exit("stairwell07", "east", 0);
   add_exit("post", "south", 0);
   add_exit("mage_library", "west", 0);

   clone_object(OBJ + "policy_board")->move(this_object());
}
