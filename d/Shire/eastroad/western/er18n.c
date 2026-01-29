#pragma save_binary
#pragma strict_types

#include "local.h"

inherit EAST_ROAD;

#define BOMB_DIR "/d/Shire/bombadil/npc/"
static object pheasant;

void
create_er_room()
{
   area = "close to";
   areaname = "Frogmorton";
   land = "the Shire";
   areatype = 8;
   areadesc = "rolling plain";
   grass = "green";
   
   extraline = "You are walking along the road to Scary, somewhere "+
   "between Frogmorton and Bywater in the East Farthing. Just off "+
   "to the north, a small wooden bridge lays across the thin stream "+
   "that the Hobbits know as 'The Water'. To the south lies the "+
   "East Road; if you were to follow this path north however, you would "+
   "come to many Hobbit villages of the North Farthing, such as Oatbarton "+
   "or Scary.";
   add_item(({"frogmorton"}),"   The small Hobbit village of Frogmorton lies "+
      "only about five miles distant in the east. From here, the village "+
      "seems to sprawl out on a narrow plain where the East "+
      "Road and the Water seem to touch togeather.\n");
   add_item(({"bywater"}),"The Hobbit village of Bywater is just off to the "+
      "west, past the Three Farthing Stone. Set on the junction of the East Road "+
      "and the road to Hobbiton, Bywater still maintains the appearance of a "+
      "peaceful Hobbit village. You would judge that it lies almost "+
      "fifteen miles off to the west.\n");
   
   add_item(({"water","the water","baraduin","river"}),"At this distance, "+
      "'The Water' only appears as a thin, narrow river, running across the "+
      "gentle hills of the Shire.\n");
   add_item(({"path","oatbarton"}),"A narrow, dirt path seems to "+
      "off from the East Road here, running across the Water to the "+
      "north, towards the Hobbit town of Oatbarton in the North "+
      "Farthing.\n");
   reset_shire_room();

   add_exit(EAST_R_DIR + "er18n2","north",0,2);
   add_exit(EAST_R_DIR + "er18","south",0,2);
   add_exit(EAST_R_DIR + "er17n2","west",0,2,1);
   
}



void
reset_shire_room()
{
    setuid();
    seteuid(getuid());

    if(!objectp(pheasant))
    {
        pheasant = clone_object(BOMB_DIR + "pheasant");
        pheasant->set_restrain_path("/d/Shire/eastroad/western");
        pheasant->set_random_move(2);
        pheasant->move(TO);
    }
}
