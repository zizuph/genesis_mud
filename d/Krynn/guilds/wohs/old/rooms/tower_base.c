/*
   Wayreth tower base.

   tower_base.c
   -------------
   Coded ........: 95/06/02
   By ...........: Jeremiah

*/


#include <stdproperties.h>
#include <ss_types.h>
#include <macros.h>

#include "/d/Krynn/common/defs.h"
#include "../guild.h"

#include <composite.h>

inherit "/d/Krynn/wayreth/std/in_room";

public mixed prevent_teleport();

int wall_type = 0; /* 0 : No walls. Default.           */
                   /* 1 : Walls in center of tower.    */
                   /* 2 : Curving outer walls.         */
                   /* 3 : Walls in stairwell.          */


void
create_tower_room() { }


void
create_wayreth_room()
{
   INSIDE;

   create_tower_room();

   add_item(({"wall", "walls"}),"@@wall_descr");
   add_item("tower", "The Tower of High Sorceryin Wayreth. " +
            "You are standing somewhere inside it.\n");
   add_prop(ROOM_M_NO_TELEPORT, prevent_teleport);
}


void
set_wall_type(int type)
{
   wall_type = type;
}


string
wall_descr()
{
   string ret_str;

   switch(wall_type)
   {
      case 0: 
         ret_str = "You see no walls.\n";
      break;

      case 1:
         ret_str = "Although the outside walls of the tower are dark, the " +
                   "walls here, inside the tower, are bright and they " +
                   "seem to somehow give of a strangely bright, but " +
                   "pleasant, light, illuminating the room.\n";
      break;
      case 2:
         ret_str = "Although the outside walls of the tower are of a " +
                   "dark material, the walls in here are bright and " +
                   "gives of a strange, but pleasant, light. The wall " +
                   "opposite the exit curves slightly, indicating " +
                   "that this room must be at the outer perimeter of " +
                   "the tower. The walls to each side slants inwards from " +
                   "the outer wall towards the center of the tower, " +
                   "narrowing the room towards the exit.\n";
      break;
      case 3:
         ret_str = "Even though the outside walls of the tower are made " +
                   "of a dark material, the walls in here seems brighter, " +
                   "illuminating the stairwell in a strange, but pleasant, " +
                   "light.\n";
      break ;
   }

   return ret_str;
}


int
pass_check()
{
    if (MEMBER(TP))
        return 0;

   write("A strange invisible barrier blocks this exit. A deep voice " +
         "sounding from somewhere within your mind tells you: You are " +
         "not a member of the Wizards of High Sorcery. You are not " +
         "allowed to enter this area.\n");
   
   if (TP->query_wiz_level())
   {
      write("You however, as a wizard, may enter for a while.\n");
      return 0;
   }

   return 1;
}

public mixed
prevent_teleport()
{
    if (!TP)
	return 0;
    
    if (!MEMBER(TP))
	return 0;
    
    return "Something prevents you from teleporting there.";
}

