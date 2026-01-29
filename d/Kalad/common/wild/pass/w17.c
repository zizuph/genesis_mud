/* 
 * /d/Kalad/common/wild/pass/w17.c
 * Purpose    : Road
 * Located    : Hespyre Mountains
 * Created By : Antharanos 
 * Modified By: 
 */ 

/* 
 * /d/Kalad/common/wild/pass/w17.c
 * Purpose    : Road
 * Located    : Caravan Route out of Kabal
 * Created By : Antharanos  
 * Modified By: 
 */ 

/* 
 * /d/Kalad/common/wild/pass/w17.c
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
   set_long("A wide valley spreads out before you, mighty redwoods blanket "+
      "the valley floor and the lower slopes of the Hespyre mountains. The rest "+
      "of the vale continues to the northwest while southeast, past the "+
      "sheer walls of the range lies the Caravan Route.\n");
   add_item(({"mighty redwoods","redwoods","mighty redwood","redwood"}),
      "As wide as twenty feet at the base these immense trees seem to scrape "+
      "the very sky itself, so great is their height.\n");
   add_item(({"slopes","slope"}),"The lower reaches of the mountains are "+
      "covered by a forest of giant redwoods.\n");
   add_item(({"hespyre mountains","mountains","mountain"}),"Towering above "+
      "you are the peaks of the Hespyre range, probably the greatest range of "+
      "mountains in all of Kalad, and certainly the greatest barrier between "+
      "the city of Kabal and the great Kabal waste.\n");
   add_exit("/d/Kalad/common/wild/pass/w18", "northwest",0,2);
   add_exit("/d/Kalad/common/wild/pass/w6", "southeast",0,3);
}
