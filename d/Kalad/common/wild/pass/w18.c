/* 
 * /d/Kalad/common/wild/pass/w18.c
 * Purpose    : Valley setting
 * Located    : Hespyre Mountains
 * Created By : Antharanos  
 * Modified By: 
 */ 

inherit "/d/Kalad/room_std";
#include "/d/Kalad/defs.h"
/* by Antharanos */
create_room()
{
   ::create_room();
   add_prop(ROOM_NO_TIME_DESC,1);
   set_short("Valley");
   set_long("A wide valley stretches out before you. Along the floor of "+
      "the valley and the lower slopes of the Hespyre mountains a mighty "+
      "forest of redwoods grow. The vale continues towards the west and to "+
      "the southeast, where it eventually meets the Caravan Route.\n");
   add_item(({"floor","slopes","mighty forest","forest","redwoods","redwood"}),
      "Gigantic trees with a diameter of at least twenty feet at the base, "+
      "they rise hundreds of feet into the sky, as if in challenge to the "+
      "mountains upon which they depend.\n");
   add_item(({"hespyre mountains","mountains","mountain"}),"Immense mountains "+
      "rise up around you, forming the confines of this forested valley. "+
      "The sheer size of the mountains is so great, that they cast a great "+
      "shadow upon the land.\n");
   add_exit("/d/Kalad/common/wild/pass/w19", "west",0,2);
   add_exit("/d/Kalad/common/wild/pass/w17", "southeast",0,2);
}
