/*
 * Hammerhands emotes. For inclusion, not standalone usage.
 * TAPAKAH, 11/2005
 */

#include <macros.h>

#include "/d/Khalakhor/sys/defs.h"
#include "../../daenbraigh.h"
#include "../hhands.h"
#include "hh_guild.h"

inherit HHANDS_DIR + "hh_common";

int
hh_swing(string str)
{
  object *swarg, weapon,target;
  string wep,targetdesc;
  int i,sws;

  swarg = hh_parse_command(str);
  sws = sizeof(swarg);

  if(! sws)
    return 0;

  weapon = swarg[0];
  if(sws == 1)
    target = 0;
  else
    target = swarg[1];

  if(target) {
    if(! CAN_SEE(TP,target) ||
       ! CAN_SEE_IN_ROOM(TP))
      return 0;
    targetdesc = living(target) ? target->query_The_name(TP) : target->short();
    if(targetdesc == TP->query_The_name())
      return 0;
    write("You mightily swing your " + weapon->short() + " a hair away from "+
	  targetdesc + ".\n");
    if(interactive(target))
      tell_object(target,
		  TP->query_The_name(target) + " mightily swings his " + weapon->short() + " a "+
		  "hair away from you.\n");
    tell_room(ENV(TP),
	      QCTNAME(TP) + " mightily swings his " + weapon->short() + " a "+
	      "hair away from " + targetdesc + ".\n",
	      ({TP,target}));
    return 1;
  }
  else {
    write("You mightily swing your " + weapon->short() + " around.\n");
    tell_room(ENV(TP),
	      QCTNAME(TP) + " mightily swings his " + weapon->short() +
	      " around.\n",
	      TP);
    return 1;
  }
}


