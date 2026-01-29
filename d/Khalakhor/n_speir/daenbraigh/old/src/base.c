/*
 * Basic common functions for the entire speir.
 * TAPAKAH, 04/2005
 */
#pragma strict_types

inherit "/d/Khalakhor/std/monster";

#include "daenbraigh.h"
#include "/d/Khalakhor/sys/defs.h";

int
check_aggression()
{
  int align = TP->query_alignment();
  string race = TP->query_race_name();
  
  if(TP->query_wiz_level())
    return 0;
  if(align > 0)
    return 1;
  if(TP->query_prop(GV_ENEMY))
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

void
attacked_by(object enemy)
{
  ::attacked_by(enemy);
  enemy->add_prop(GV_ENEMY,1);
}
