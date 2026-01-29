/*
 * Sector O - Okiyan, the ocean around Nyreese and Carisca
 * Tapakah, 10/2021
 */

#pragma strict_types

#include <language.h>
#include <ss_types.h>
#include "defs.h"

inherit ROOM_BASE;
inherit SEA_SECTOR;

string
long_descr ()
{
  string descr = "You find yourself upon the waters of the Okiyan, " +
    "the second, smaller ocean of Khalakhor, that surrounds the lands of " +
    "Nyreese and Carisca. " + query_sailing_difficulty_desc();

  if (Yy == 0) {
    descr += " The waters to the north seem to be swirling wildly, as if "+
      "encountering something completely foreign.";
    if (Xx !=0 || Xx != 33)
      descr += " Your eyes seem to perceive some vague contours to the "+
        "north, which remind you of Kalad.";
  }
  else if (Yy == 32) {
    descr += " The waters to the south seem to be swirling wildly, as if "+
      "encountering something completely foreign.";
    if (Xx !=0 || Xx != 33)
      descr += " Your eyes seem to perceive some vague contours to the "+
        "north, which remind you of Earthsea.";
  }
  else if (Xx == 0) {
    descr += " The waters to the west seem to be swirling wildly, as if "+
      "encountering something completely foreign.";
    if (Yy !=0 || Xx != 32)
      descr += " Your eyes seem to perceive some vague contours to the "+
        "north, which remind you of Calia.";
  }
  else if (Xx == 33) {
    descr += " The waters to the east seem to be swirling wildly, as if "+
      "encountering something completely foreign.";
    if (Yy !=0 || Yy != 33)
      descr += " Your eyes seem to perceive some vague contours to the "+
        "north, which remind you of Terel.";
  }
  return descr + "\n";
}

int
has_high_exits ()
{
  string *ciorruidh_exits = regexp(row_exits_path, "-[C]$");
  string *sea_exits = regexp(row_exits_path, "-[csr]$");

  return sizeof(ciorruidh_exits) && ! sizeof(sea_exits) ? 1 : 0;
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
      distance_direction_point[1] + " about " + leagues + " leagues away.\n";
    break;
  }
  return continents_description;
}

void
create_sea_room ()
{
  ::create_sea_room();
  ::create_sea_sector();
  
  // Set the sailing skill required to sail to this room.
  set_sailing_difficulty(has_high_exits()
                         ? HIGH_SEAS_DIFFICULTY
                         : ROUGH_SEAS_DIFFICULTY);

  // Set the optional message when sailing into this room.
  set_sailing_fail_message("The open waters of the rough seas are highly " +
                           "dangerous, with only great navigators capable "+
                           "of sailing!\n");
  set_sailing_difficulty_message("You navigate skillfully " +
                                 "into the Okiyan!\n");

  set_short("Deep in the Okiyan");
  set_long(long_descr);

  add_item(({"high sea","ocean","sea","high seas of khalakhor","seas",
             "water"}),
           "The waters of the Okiyan, the ocean surrounding the lands "+
           "of Nyreese and Carisca, lap at your vessel.\n");
  add_item(({"continents","landmasses"}),
           get_continents);

}
