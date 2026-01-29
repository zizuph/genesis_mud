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
  set_short("Amongst shrivelled crops and abundant briars.");
  set_long("Amongst shrivelled crops and abundant briars. It "+
      "would appear that this land was farmed in the recent "+
      "past. However, when care of the land ceased, the natural "+
      "elements took over. A few specimenes of the crops once "+
      "harvested here still grow, but most of the vegetation "+
      "consists of thorny weeds and brambles. Thats where there "+
      "is any vegetation left at all. Already, the wastes seem "+
      "to be taking their grip on this once productive parcel "+
      "of land.\n");

  add_item(({"crops","crop"}),
      "A few plants of the hardier species grown for agricultural "+
      "purposes can still be found growing in these fields. They "+
      "are in the minority however.\n");

  add_item(({"briars","brambles","weeds"}),
      "Most of the vegetation to be found here consists of "+
      "a variety of weeds. Many of them have thorns, and its "+
      "quite likely that some of those thorns contain poisonous "+
      "fluids. For that reason, you have carefully avoided all the "+
      "patches of briars which have grown up here. Even these "+
      "weeds are yellowing under the heat of the Athasian sun.\n");

  add_cmd_item(({"food","crop","crops",}),
      ({"pick","take","harvest"}),"The edible plants are too few "+
      "and far between to be worth harvesting, given the "+
      "number of thorn bushes.\n");

  add_exit(RIDGE_DESERT+"d13.c","northwest",0,9,0);
  add_exit(RIDGE_DESERT+"d17.c","west",0,6,0);
/*
  add_exit(RIDGE_DESERT+"d21.c","southwest",0,12,0);
  add_exit(RIDGE_DESERT+"d22.c","south",0,8,0);
*/
}


