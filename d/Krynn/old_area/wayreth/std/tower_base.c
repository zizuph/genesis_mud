/*
   Wayreth tower base.

   tower_base.c
   -------------

   Coded ........: 95/06/02
   By ...........: Jeremiah

   Latest update : 95/07/14
   By ...........: Jeremiah

*/


#include <stdproperties.h>
#include <ss_types.h>
#include <macros.h>
#include "/d/Krynn/common/defs.h"
#include "/d/Krynn/wayreth/local.h"
#include "/d/Krynn/wayreth/guild/local.h"
#include <composite.h>
#define RESET  "reset_tower_room"

inherit WAYINROOM;

public mixed prevent_teleport();

int wall_type = 0; /* 0 : No walls. Default.           */
                   /* 1 : Walls in center of tower.    */
                   /* 2 : Curving outer walls.         */
                   /* 3 : Walls in stairwell.          */


/*
 * This function is called from the main Krynn room.
 */
nomask public void
reset_wayreth_room()
{
    call_other(TO, RESET);
}

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
   if(TP->query_guild_name_occ() == "Wizards of High Sorcery")
      return 0;

   write("A strange invisible barrier blocks this exit. A deep voice " +
         "sounding from somewhere within your mind tells you: You are " +
         "not a member of the Wizards of High Sorcery. You are not " +
         "allowed to enter this area.\n");
   
   if(TP->query_wiz_level())
   {
      write("You however, as a wizard, may enter for a while.\n");
      return 0;
   }

   return 1;
}

/*
 * Make it possible to start here.
 */
public int
do_start(string str)
{
    if (!str || !strlen(str))
        return NF("Where do you want to start?\n");

    if (L(str) != "here")
        return NF("You can't start at that place.\n");

    if (!IS_MEMBER(TP))
        return NF("Only a Wizard of High Sorcery can start here.\n");
    
    if (ADMIN->add_starting_room(RNAME(TP), MASTER_OB(TO)))
    {
        if (!TP->set_default_start_location(START_ROOM))
        {
            return NF("Failed to set the starting location, make a bug report!\n");
        }
        write("You will be starting here from now on.\n");

        return 1;
    }
    return NF("Failed to set the starting location, internal error.\n");
}

public mixed
prevent_teleport()
{
    if(!this_player())
	return 0;

    if(this_player()->query_is_wohs())
	return 0;

    return "Something prevents you from teleporting there.";
}

public void
init()
{
     if (TO->query_start_room())
        add_action(do_start, "start");

     ::init();
}
