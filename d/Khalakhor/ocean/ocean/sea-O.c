/*
 * Sector O - Okiyan, the ocean around Nyreese and Carisca
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
  string descr = "You find yourself upon the waters of the Okiyan, " +
    "the second, smaller ocean of Khalakhor, that surrounds the lands of " +
    "Nyreese and Carisca.";

  return descr;
}

int
get_difficulty ()
{
  string *ciorruidh_exits = regexp(row_exits_path, "-[C]$");
  string *sea_exits = regexp(row_exits_path, "-[csr]$");

  return sizeof(ciorruidh_exits) && ! sizeof(sea_exits)
    ? HIGH_SEAS_DIFFICULTY
    : ROUGH_SEAS_DIFFICULTY;
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
  case 0..40: continents_description =
      "You are far from any continent or landmass, and can only see the " +
      "the waters of the Okiyan all around you.\n";
    break;
  case 41..70: continents_description =
      "You are far from any continent, but you realize the nearest "+
      "landmass to you would be " + distance_direction_point[2] + ".\n";
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
  ::create_sea_sector("Okiyan", -1);
  add_item(({"high sea","ocean","sea","high seas of khalakhor","seas",
             "water"}),
           "The waters of the Okiyan, the ocean surrounding the lands "+
           "of Nyreese and Carisca, lap at your vessel.\n");

}
