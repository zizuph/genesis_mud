inherit "/std/room";
inherit "/w/stark/celtcamp/rooms/training/trainingbase";
#include "/w/stark/defs.h"
#include <macros.h>
#include "/d/Krynn/haven/local.h"


int enter_tent(string str);


void
 create_room()
 {
  ::create_room();
  set_long("You stand at the entrance to a large open space, "
	  +"where the vegetation and trees are cleared around. "
	  +"The air is filled with sharp sounds of swordplay as "
	  +"a large number of trainees are praciticing "
	  +"their skills in the hopes of joining the Clan "
	  +"Baran. The harsh wind bites into your side as "
	  +"the unrelenting sun beats down upon you relentlessly "
	  +"The grass under your feet is trampled, as the many "
	  +"aspiring warriors attempt to further their physical strength. "
	  +"There is a large war tent here.\n");
  
  add_item(({"vegetation","trees","forest","grass","space","clearing"}),
       "Surrounding you are the stumps of trees that once had great "
	  +"height.\n");
  add_item(({"sounds","swordplay","trainees","hopefuls","applicants","warriors"}),
	   "The sounds of swordplay are so numerous that the noises "
	  +"ring loudly in your ears. The clansman hopefuls work day "
	  +"after day to hone their skill with the swords. This is "
	  +"obviously the recruitment outreach in Port Macdunn.\n");
  add_item(({"wind","harsh wind"}),
	   "The wind here is so fierce, that it almost causes "
  	  +"you to fall over. As your time here progresses it "
	  +"bites deeper and deeper into your side.\n");
  add_item(({"sun","unrelenting sun"}),
	   "The sun is blazing down on the clearing. Without any "
	  +"treecover, there seems to be little respite or shade.\n");
  add_item(({"tent","large war tent"}),
	   "Before you stands a large war tent standing in defiance "
	  +"of the harsh weather, perhaps some relief is offered inside.\n");
	  
	  
	    
  summon_ktrain();
  summon_ktrain();
  summon_ktrain();
  summon_ktrain();
  summon_ktrain();
  
  add_exit(CAMP_DIR+"path13","northeast",0,1);
  add_exit(CAMP_DIR3+"training3","southwest",0,1);
  add_exit(CAMP_DIR3+"training4","south",0,1);
  add_exit(CAMP_DIR4+"training5","southeast",0,1);

  
}

int
enter_tent(string str)
{
   notify_fail("Enter what? The tent?\n");
   
   if((!str) || (!strlen(str)) || (str !="tent" && str != "large tent" &&
   str != "war tent" && str !="large war tent"))
      return 0;
   
   write("You enter the large war tent.\n");
   tell_room(this_object(), QCTNAME(TP)+" enters the large war tent.\n", TP);
   TP->move_living("M",CAMP_DIR4+"trainingtent0",0,0);
   return 1;
}
void
init()
{
::init();
add_action(enter_tent, "enter");
}