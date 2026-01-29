/*
* Created by: Luther
* Date: 19 August 2001
*
* File: /d/Cirath/ridge/valley/v12.c
* Comments: Valley outside of Tyr
*/

#pragma strict_types
#pragma save_binary
#include "defs.h"
inherit BASE_VALLEY;

void
create_valley()
{

  set_short("Sand Valley");
  set_long("You are standing in the belly of the valley. It runs about 100 feet "
  	+"wide before its sides start to climb up. In this area of the valley "
  	+"are some ruins. You can easily walk around them. Looking up the valley "
  	+"edges you see movement.\n");

  add_item("ruins", "Taking a better look into the ruins you can make out a few"
  	+"old building in a advanced state of decay. The ruins span about 60 "
  	+"feet wide and about that in length. You can make out some movement in the "
  	+"ruins.\n");

  add_item(({"movement", "edge"}), "Looking to the side of the valley "
  	+"you can make out something shimmering around, almost like a ghost...\n");

  add_exit(RIDGE_VALLEY+"v08.c","north",0,8,0);
  add_exit(RIDGE_VALLEY+"v09.c","northeast",0,8,0);
  add_exit(RIDGE_VALLEY+"v13.c","east",0,8,0);
  add_exit(RIDGE_VALLEY+"v16.c","south",0,8,0);
  add_exit(RIDGE_VALLEY+"v15.c","southwest",0,8,0);
  add_exit(RIDGE_VALLEY+"v11.c","west",0,8,0);
  add_exit(RIDGE_VALLEY + "ruin_1.c", "ruins", 0, 1, 1);
  reset_room();
}

void
init()
{
    ::init();
    add_action("enter_ruins", "enter");
}

int
enter_ruins(string str)
{	
   	notify_fail("Enter what?\n");
    	if(str!="ruins")
        	return 0;
       	
  	if (str == "ruins" && (TP->query_base_stat(SS_DIS) > 75))
     	{     		
        TP->catch_msg("You bravely enter the ruins.\n");
        TP->move_living("bravely into the ruins..", RIDGE_VALLEY + "ruin_1.c",1);
        return 1;
        }
        else
        {
        	if (this_player()->query_wiz_level())
      		{
      			TP->catch_msg("You walk into the ruins.\n");
      			TP->move_living("walking into the ruins..", RIDGE_VALLEY + "ruin_1.c",1);
      			return 1;	
      		}
        TP->catch_msg("The ruins look abit to scary for you to enter right now.\n");
        return 1;
        }
    return 0;
}
