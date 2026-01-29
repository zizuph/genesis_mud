inherit "/d/Shire/eastroad/std/er_base";
inherit "/d/Gondor/common/lib/drink_water.c";

#include "/d/Shire/common/herbs/herb_list.h"
#include "/d/Shire/common/defs.h"
#include "/sys/stdproperties.h"
#include "/sys/macros.h"
 
#include "local.h"

#define EXIT1 ER_BASE_DIR + "girdley/girpath3","north",0,1
#define EXIT2 ER_BASE_DIR + "girdley/girpath1","south",0,1
 
 
void
create_er_room()
{
 
   area = "south of";
   areaname = "Girdley Island";
   land = "the Shire";
   areatype = 7;
   areadesc = "overgrown river path";
   grass = "green";
 
   extraline = "This narrow overgrown path leads north and south along "+
   "the west bank of the Brandywine river.  Here the river is still a bit "+
   "too deep to walk across, but to the north the path widens and a ford "+
   "seems to be present there.  South the path leads back towards the "+
   "Bridge of Stonebows.";
 
   add_item(({"path","narrow path"}),
   "The narrow path is made considerably thinner by the influx of underbrush "+
   "and small bushes and tangling vines.\n");
   add_item(({"vine","vines","tangling vines"}),
   "The tangling vines are long but curly, perfect for catching an ankle in.\n");
   add_item(({"bush","bushes","small bushes","underbrush"}),
   "The underbrush is a continuous line of various green and flowering "+
   "bushes trying to peek out under the canopy of trees that line the "+
   "riverside path.\n");
   add_item(({"tree","trees","canopy","canopy of trees"}),
   "The trees are mostly willows and tall birch trees which lean out "+
   "across the water to feed in all the available sunlight.\n");
   add_item("water","The water is brown and muddy, flowing slowly by.\n");
   add_item(({"bank","river","brandywine river","ford"}),
   "The bank on this side is narrow and slightly muddy along the river, which "+
   "flows southward towards Sarn Ford.  The ford to the north seems to be "+
   "large enough to get a wagon and horse-team across to the island on.\n");
   add_item(({"island","girdley island"}),
   "The island is roughly triangular in shape and nearer to this bank than the "+
   "far bank of the Baranduin.\n");
     set_up_herbs( ({   GONDOR_HERB_DIR + "attanar",
                        GONDOR_HERB_DIR + "suranie",
                        SHIRE_HERB_DIR  + "lamia", 
                        SHIRE_HERB_DIR  + "nasturtium",
                        GONDOR_HERB_DIR + "oregano",
                        
                        }),
                  ({"river","ground","riverbank","flowers","path","track"}), 3);


    set_drink_from( ({ "river", "brandywine", "baranduin", }) );
    
   add_exit(EXIT1);
   add_exit(EXIT2);
}

/*
* Function name: drink_message
* Description : do the msgs for drinking from river
*/
public void
drink_message(string from)
{
    write("You drink some of the yellow water of the Brandywine river.\n"
    + "It tastes dirty and muddy.\n");
    say(QCTNAME(TP) + " drinks some water from the river.");
} 
