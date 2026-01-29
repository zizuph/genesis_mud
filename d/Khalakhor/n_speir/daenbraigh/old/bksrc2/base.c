/*
 * Basic common functions for the entire speir.
 * TAPAKAH, 04/2005
 */
inherit "/d/Khalakhor/std/monster";

#include "nspeir.h"
#include "/d/Khalakhor/sys/defs.h";
int
check_aggression()
{
  int align = TP->query_alignment();
  string race = TP->query_race_name();
  
  if(align > 0)
    return 1;
  switch(race)
    {
    case "elf":
    case "hobbit":
      return 1;
      break;
    case "goblin":
      return 0;
      break;
    default:
      if(align > SUFFALIGN)
	return 1;
      else
	return 0;
    }
}
