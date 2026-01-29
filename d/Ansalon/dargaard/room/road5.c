/**  DARGAARD OUTSIDE ROOM **/ 

#include "../local.h" 
#include "/d/Ansalon/common/defs.h" 
#include <ss_types.h>
#include <stdproperties.h> 

inherit DARGAARD_OUT; 

void 
reset_dargaard_room() 
{ 
} 

void 
create_dargaard_room() 
{ 
    set_short("Stone path in the Dargaard Mountains"); 
    set_long(tod_descr()+ "" +season_descr()+ "You have come to "+ 
             "a dead end. A tall cliff stands before you to the east making "+
             "it impossible to continue in that direction. The path is filled "+
             "with rocks and boulders that have fallen down from above. The way to "+ 
             "the southwest and northwest takes you back to the stone path.\n"); 

    add_exit(DROOM + "road3","northwest",0); 
    add_exit(DROOM + "road4","southwest",0); 
    add_exit(DROOM + "road6","up",0); 

    add_item(({"road", "path"}), 
      "A few bones lies scattered on the path.\n"); 

    add_item(({"stones"}), 
      "The road is made out of flat gray stones of various sizes. "+ 
      "Small patches of moss fill the cracks between the stones.\n"); 

    add_item(({"plants", "moss", "vegetation"}), 
      "The vegetation here consists most of dried grass and plants. "+ 
      "Small green moss spots cover some of the rocks.\n"); 

    add_item(({"boulders", "huge boulders"}), 
      "A few huge boulders lies next to the road, they have been gently "+ 
      "pushed aside to make way for the stone road.\n"); 

    add_item(({"plains", "nightlund plains"}), 
      "The Nightlund plains lies before the Dargaard Mountains, the green "+ 
      "plain continues far into the distance.\n"); 

    add_item(({"bushes", "trees", "log", "logs"}), 
      "Dead trees and dried bushes fill the area, the cold winds and dry "+ 
      "weather might have killed them.\n"); 

    add_item(({"dargaard keep", "keep"}), 
      "The fortress high up in the mountains is known as Dargaard Keep. "+
      "It appears blackened as if it had been burnt, and an unnatural "+
      "darkness seems to radiate from it. You cannot make out any details, "+
      "since the keep is too far away.\n");

    add_item(({"cliff", "rock", "stones"}), 
      "The tall cliff looks very steep, however a few niches in the stone "+ 
      "cliff might make it climbable.\n"); 

    reset_dargaard_room(); 
} 


