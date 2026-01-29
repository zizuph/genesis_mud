/*
   Wayreth tower base.

   tower_base.c
   -------------

   Coded ........: 95/06/02
   By ...........: Jeremiah

   Latest update : 16/08/27
   By ...........: Arman

*/


#include <stdproperties.h>
#include <ss_types.h>
#include <macros.h>
#include "/d/Krynn/common/defs.h"
#include "/d/Krynn/wayreth/local.h"
#include "/d/Krynn/guilds/wohs/defs.h"
#include <composite.h>
#define RESET  "reset_tower_room"

inherit WAYINROOM;

public mixed prevent_teleport();

string  *banish_locs = ({"/d/Krynn/darkenwd/road/forest6.c", 
                       "/d/Krynn/wild/field3.c", 
                       "/d/Krynn/tant/room/forest4.c", 
                       "/d/Krynn/xak/marsh8.c", 
                       "/d/Krynn/qualinesti/forest/forest49",
                       "/d/Krynn/qualinesti/forest/forest30" });

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
   add_item("tower", "The Tower of High Sorcery in Wayreth. " +
            "You are standing somewhere inside it.\n");
   add_prop(ROOM_M_NO_TELEPORT_FROM, 0);
   add_prop(ROOM_M_NO_TELEPORT_TO, prevent_teleport);
   add_prop(ROOM_M_NO_ATTACK, "Magical runes of tranquility have been incorporated " +
       "into the Tower of High Magic. There will be no violence inside " +
       "the walls of the Tower.\n");
   add_prop(ROOM_M_NO_SCRY, "Powerful protective magics foil your attempt at " +
       "scrying.\n");
    add_prop(ROOM_I_LIGHT, 5);
    add_prop(ROOM_M_NO_STEAL, "Magical runes of tranquility have been incorporated " +
       "into the Tower of High Magic. There will be no thievery inside " +
       "the walls of the Tower.\n");
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

int
check_entry_ban()
{
    if(WOHS_MANAGER->query_wohs_train_rack_ban(TP))
    {
       write("You have been restricted from entering this room.\n");
       return 1;
    }
 
    return 0;
}

public mixed
prevent_teleport()
{
    if(!this_player())
	return 0;

    if(WOHS_MANAGER->query_renegade_wohs(TP))
        return "Something prevents you from teleporting there.";

    if(this_player()->query_guild_name_occ() == "Wizards of High Sorcery")
	return 0;

    return "Something prevents you from teleporting there.";
}

void
expel_banished_member(object ob)
{
   string random_room = banish_locs[random(sizeof(banish_locs))];

   tell_object(ob, "The Tower of Wayreth recognises you as being banished, " +
         "and expels you from its walls.");
   tell_room(E(ob), QCTNAME(ob) + " is magically expelled from the grounds of the " +
         "Tower of Wayreth!\n", ({ ob }) );

   ob->move_living("M", random_room, 1, 0);
   tell_room(E(ob), QCTNAME(ob)+ " suddenly appears before you!\n", ({ ob }) );
    return;
}

void
expel_non_wohs_member(object ob)
{
   string random_room = banish_locs[random(sizeof(banish_locs))];

   tell_object(ob, "The Tower of Wayreth recognises you as not being of the Orders, " +
         "and expels you from its walls.");
   tell_room(E(ob), QCTNAME(ob) + " is magically expelled from the grounds of the " +
         "Tower of Wayreth!\n", ({ ob }) );

   ob->move_living("M", random_room, 1, 0);
   tell_room(E(ob), QCTNAME(ob)+ " suddenly appears before you!\n", ({ ob }) );
    return;
}

void
enter_inv(object ob, object from)
{
    ::enter_inv(ob, from);

    // DEBUG("Something has entered this room.");

    if(!ob->query_humanoid())
    {
      return;
    }

    if(ob->query_npc())
    {
      return;
    }

    // DEBUG("Pre-renegade check.");

    if(WOHS_MANAGER->query_renegade_wohs(ob))
    {
      DEBUG("Expel banished member called.");
      set_alarm(1.0, 0.0, &expel_banished_member(ob));
      return;
    }

   if(ob->query_guild_name_occ() != "Wizards of High Sorcery" &&
      ob->query_guild_name_occ() != "School of High Magic" &&
      !ob->query_prop("_live_i_am_invited") && !ob->query_wiz_level())
    {
      set_alarm(1.0, 0.0, &expel_non_wohs_member(ob));
      return;
    }
}
