/*
* Created by: Luther
* Date: 19 August 2001
*
* File: /d/Cirath/ridge/valley/v01.c
* Comments: Valley outside of Tyr
*/

#pragma strict_types
#pragma save_binary
inherit "/d/Cirath/std/room";
#include "defs.h"


void
create_room()
{

  set_short("At the base of a cliff.");
  set_long("At the base of a red stone cliff. The landscape is "+
      "harsh and desolate. There is not a trace of vegetation to "+
      "be found anywhere in sight. Stretching away from the cliff "+
      "is an endless sea of bare rock and earth. Gusts of wind "+
      "raise clouds of red dirt which sweep their way across the "+
      "barren landscape. The cliff stretches gradually becomes "+
      "less imposing to the northwest, and extends as far as the "+
      "eye can see to the southwest.\n");

  add_item(({"vegetation","plants"}), "You see none!");

  add_item(({"dirt","ground","rock","bare rock"}),
      "You examine the ground, but, not surprisingly, find nothing "+
      "of interest.\n");

  add_item(({"clouds of dirt","wind","clouds"}),
      "Across this more or less flat portion of Athas, the wind "+
      "blows almost constantly, raising great clouds of reddish "+
      "brown dirt. These clouds sting the eyes and nose, "+
      "and obscure vision signifigantly wherever they arise.\n");

  add_item(({"cliff","stone cliff","red cliff","red stone cliff"}),
      "It is an imposing cliff composed of the same reddish-brown "+
      "stone which makes up the Ringing Mountains and the baserock "+
      "in these parts of Athas. At this point the cliff is over "+
      "30 metres in height, while no easy way up the cliff can be "+ 
      "found at this point. Since you have no reason to believe "+
      "that anything interesting can be found at the top, you "+
      "decide that it would not be worth the risk of climbing it, "+
      "at least at this point. At the base of cliff, you notice "+
      "an indentation. Its not quite big enough to be a cave, "+
      "but it would provide substantial shelter from the "+
      "elements.\n");

  add_item("indentation",
      "You take a closer look at the indentation in the cliff face. "+
      "You find nothing noteworthy until you take a look at the "+
      "ground. You notice a couple of footprints stamped into a "+
      "small pile of dirt which the sheltered nature of the "+
      "location had protected from the wind.\n");
  
  add_item(({"prints","footprints"}),
      "The footprints were made by someone or something wearing boots. "+
      "The feet would seem to be about the same size as those of a "+
      "large man ... \n");

  add_cmd_item(({"cliff","stone cliff","red cliff","red stone cliff"}),
      ({"climb up","climb"}),"You decide against that, owing to the "+
      "dangerous nature of such a climb, and the fact that you have "+
      "no reason to expect to find anything of interest up there "+
      "anyhow.\n");
      
       	OUTSIDE
  	LIGHT
  	ADD_SUN_ITEM

  add_exit(RIDGE_DESERT+"d19.c","north",0,8,0);
  add_exit(RIDGE_VALLEY+"v02.c","south",0,8,0);
  reset_room();
}


