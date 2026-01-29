#pragma save_binary
#pragma strict_types

#include "/d/Shire/sys/defs.h"
#include "local.h"
#include H_MAKER

inherit EAST_ROAD;

#define MAX_CITIZENS 3
 
static object *hobbits = allocate(MAX_CITIZENS);

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
   "find many Hobbit villages of the North Farthing, such as Oatbarton "+
   "or Scary. The road however is closed temporarily, because "+
   "The Water has overflowed its banks.";
   
   add_item ("frogmorton","This small hobbit village lies about "+
      "five miles to the east.\n");
   
   add_item(({"water","the water","baraduin","river"}),"From here, "+
      "'The Water' only appears as a thin, narrow river, running across "+
      "the gentle hills of the Shire.\n");
   
   add_item(({"path","oatbarton"}),"A narrow, dirt path seems to "+
      "off from the East Road here, running across the Water to the "+
      "north, towards the Hobbit town of Oatbarton in the North "+
      "Farthing.\n");

reset_shire_room();
   
   add_exit(EAST_R_DIR + "er17n3","west",0,2,1);
   add_exit(EAST_R_DIR + "er18n","south",0,2);   
}

void
reset_shire_room()
{
    int index;

    /* Do this first, since we may need to clone. */
    setuid();
    seteuid(getuid());
 
    /* Loop over all elements in the array. */
    for(index = 0; index < MAX_CITIZENS; index++)
    {
        if (!objectp(hobbits[index]))
        {
            hobbits[index] = clone_object(HOBBITMAKER);
            hobbits[index]->set_type(CITIZEN);
            hobbits[index]->set_power(100);
            hobbits[index]->set_restrain_path(({"/d/Shire/eastroad/western", 
                "/d/Shire/eastroad/village/whit",
                "/d/Shire/common/hobbiton",
                "/d/Shire/michel" }));
            hobbits[index]->set_random_move(3);
            hobbits[index]->set_monster_home(EAST_R_DIR + "er18n2");
            hobbits[index]->move(TO);
 
        }
    }

}
