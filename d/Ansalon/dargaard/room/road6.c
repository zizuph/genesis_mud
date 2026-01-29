/**  DARGAARD OUTSIDE ROOM **/ 

#include "../local.h" 
#include "/d/Ansalon/common/defs.h" 
#include <stdproperties.h> 
#include <ss_types.h>

inherit DARGAARD_OUT; 

void 
reset_dargaard_room() 
{ 
} 

void 
create_dargaard_room() 
{ 
    set_short("In an alcove in the Dargaard Mountains"); 
    set_long(tod_descr()+ "" +season_descr()+ "You are standing "+ 
             "in an alcove, halfway up a tall cliff in the Dargaard "+ 
             "mountains. Far below you, the vast Nightlund plains "+ 
             "cover the land and continues as far as you can see.\n"); 

    add_item(({"cliff", "rock", "stones"}), 
      "The tall cliff looks very steep, but an experienced climber "+ 
      "might make be able to climb up or down.\n"); 

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
      "darkness seems to radiate from it. The tall towers and walls are "+
      "twisted in the form of a rose rising to the heavens.\n");

    add_exit(DROOM + "entrance","up",0); 
    add_exit(DROOM + "road5","down",0); 
    reset_dargaard_room(); 
} 
