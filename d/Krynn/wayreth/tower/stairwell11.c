/*
   Wayreth. Stairwell in tower.

   stairwell11.c
   -------------

   Coded ........: 95/06/02
   By ...........: Jeremiah

   Latest update : October 2016
   By ...........: Arman

*/

#include "/d/Krynn/wayreth/local.h"
#include "/d/Krynn/common/defs.h"
#include "/d/Krynn/guilds/wohs/defs.h"
inherit TOWERROOM;

// object    dranin;


void
reset_tower_room()
{

/*    
    if (dranin)
      return;
    
    dranin = clone_object("/d/Krynn/wayreth/npc/walk_red.c");
    dranin->move_living("xx",TO);
    dranin->seq_new("do_thing");
    dranin->seq_addfirst("do_thing","@@start_patrol");

*/    
}

void
create_tower_room()
{
    set_short("Stairwell on the eleventh level in the tower");
    set_long("You are standing at the top of a spiral stair in a small " +
	     "circular stairwell. The spiral stair spins downwards " +
	     "around the center of the stairwell, thus each step reaches " +
	     "from the wall and to the center of the room. A large " +
	     "doorway leads west. The stair leads down towards the " +
	     "lower levels of the tower.\n");
    
    set_wall_type(3);
    
    add_item(({"stair", "stairs"}), "The stairs are carved from the same " +
	     "dark obsidian as the tower itself. Each step reaches from " +
	     "the wall and to the center of the stairwell, around which " +
	     "the spiral stair rotates.\n");
    
    add_item(({"step", "steps"}), "Steps carved of dark obsidian. The " +
	     "steps are very wide at the wall and narrows towards the " +
	     "center of the room.\n");
    
    add_item(({"doorway", "large doorway"}), "A doorway leading west, " +
	     "giving access to whatever lies on this level of the tower. " +
	     "There is a very vague shimmering in the air, screening the " +
	     "doorway.\n");
    
    add_exit(WTOWER + "laboratory", "west", "@@enter_lab");
    add_exit(WTOWER + "stairwell10", "down", 0);
    reset();
}

int
enter_lab()
{
   if(WOHS_MANAGER->query_wohs_train_rack_ban(TP))
   {
       write("You have been restricted from entering this room.\n");
       return 1;
   }

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
