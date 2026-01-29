/*
 * Sector C - Cian Siorruidh, the big ocean
 * Tapakah, 10/2021
 */

#pragma strict_types

#include <language.h>
#include <ss_types.h>
#include "defs.h"

inherit SEA_SECTOR;

string
long_descr ()
{
  return "You find yourself upon the vast waters of the Cuan Siorruidh, " +
    "the vast ocean that washes the shores of the continent of Khalakhor " +
    "and the islands adjacent to it.";
}

int
get_difficulty ()
{
  string *ocean_exits = regexp(row_exits_path, "-[OC]$");
  return sizeof(ocean_exits) == sizeof(row_exits_path) 
    ? ROUGH_SEAS_DIFFICULTY
    : HIGH_SEAS_DIFFICULTY;
}

string
get_continents ()
{
  int skill = (
               TP->query_skill(SS_LOC_SENSE)+
               TP->query_skill(SAILING_SKILL)
               ) / 2;
  string leagues;
  string continents_description;
  mixed *distance_direction_point = get_distance_direction(Xx, Yy);

  switch(skill) {
  case 0..30: continents_description =
      "You are far from any continent or landmass, and can only see the " +
      "the ocean of Cuan Siorruidh all around you.\n";
    break;
  case 31..50: continents_description =
      "You are far from any continent, but you realize the nearest"+
      "landmass to you would be " + distance_direction_point[2] + ".\n";
    break;
  case 51..70: continents_description =
      "You are far from any continent, but you realize the nearest "+
      "landmass to you would be " + distance_direction_point[2] + " to the " +
      distance_direction_point[1] + ".\n";
    break;
  case 71..100:
    leagues = LANG_NUM2WORD(ftoi(distance_direction_point[0]));
    continents_description =
      "You are far from any continent, but you realize the nearest "+
      "landmass to you would be " + distance_direction_point[2] + " to the " +
      distance_direction_point[1] + " about " + leagues + " hundred miles away.\n";
    break;
  }
  return continents_description;
}

void
create_sea_room ()
{
  ::create_sea_sector("Cuan Siorruidh", -1);
  
  add_item(({"high sea","ocean","sea","high seas of khalakhor","seas",
             "water"}),
           "Around you stretch the depths of Cuan Siorruidh, a vast body "+
           "of water that extends around the continent of Khalakhor and "+
           "its surrounding islands.\n");
}
