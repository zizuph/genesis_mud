 /* The desert, just west of Tyr.
  * Dethraine, March 1998. Code (c) Damian Horton
  */

#pragma strict_types
#pragma save_binary

#include "defs.h"

inherit BASE_DESERT;

void
create_desert()
{

  set_short("At the base of a cliff.");
  set_long("At the base of a red stone cliff. The landscape is "+
      "harsh and desolate. There is not a trace of vegetation to "+
      "be found anywhere in sight. Stretching away from the cliff "+
      "is an endless sea of bare rock and earth. Gusts of wind "+
      "raise clouds of red dirt which sweep their way across the "+
      "barren landscape. You are at about the point where the "+
      "cliff makes a bit of a corner. It extends in the "+
      "northwesterly and southerly directions, as far as the eye "+
      "can see. To the southeast, you discern massive dunes of "+
      "reddish sand.\n");

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
      "40 metres in height, while no easy way up the cliff can be "+ 
      "found at this point. Since you have no reason to believe "+
      "that anything interesting can be found at the top, you "+
      "decide that it would not be worth the risk of climbing it, "+
      "at least at this point.\n");

  add_item(({"dunes","sand dunes","sand"}),
      "They begin not far to the southeast of here, and are composed "+
      "of a reddish sand. They extend as far as the eye can see "+
      "in an easterly direction. Travel across the Athasian "+
      "wastes is never easy, but travelling across sand dunes "+
      "is especially tiresome.\n");
  
  add_cmd_item(({"cliff","stone cliff","red cliff","red stone cliff"}),
      ({"climb up","climb"}),"You decide against that, owing to the "+
      "dangerous nature of such a climb, and the fact that you have "+
      "no reason to expect to find anything of interest up there "+
      "anyhow.\n");

 
  add_exit(RIDGE_DESERT+"d15.c","north",0,8,0);
  add_exit(RIDGE_VALLEY+"v01.c","south",0,8,0);

}


