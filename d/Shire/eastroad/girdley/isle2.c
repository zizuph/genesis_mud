inherit "/d/Shire/eastroad/std/er_base";
inherit "/d/Gondor/common/lib/drink_water.c";

#include "/d/Shire/common/herbs/herb_list.h"
#include "/d/Shire/common/defs.h"
#include "/sys/stdproperties.h"
#include "/sys/macros.h"
#include <ss_types.h>


#include "local.h"
#define EXIT1 ER_BASE_DIR + "girdley/isle1","south",0,1
#define EXIT2 ER_BASE_DIR + "girdley/isle3","east",0,1
void add_stuff();

object rock;

void
create_er_room()
{

    area = "in the middle of";
    areaname = "Girdley Island";
    land = "the Shire";
    areatype = 7;
    areadesc = "freshly-cut clearing";
    grass = "green";

    extraline = "The clearing has been recently cut from "+
    "the medium and large birch trees whose stumps still "+
    "remain in the ground, though they are now charred and scarred. "+
    "Large sharp rocks prevent travel west, but to the east and south, "+
    "paths lead from the clearing.";

    add_item(({"rock","rocks","large rocks","large sharp rocks","sharp rocks"}),
      "At the edge of the clearing is a large pile of sharp rocks, almost the size "+
      "of boulders.  They effectively block the view of the river to the west.\n");
    add_item(({"path"}),"Which path do you wish to see, the east path or the "+
      "south path?\n");
    add_item("east path","The east path leads into some dense bushes just "+
      "outside of the clearing.\n");
    add_item("south path","The south path leads back to the sandy bank.\n");
    add_item(({"tree","trees","medium birch trees","large birch trees","stumps"}),
      "The stumps are all that remain of very wide birch trees which must have "+
      "been several decades old.  Some stumps are charred by fire and others "+
      "notched by a sharp edge.\n");
    add_item("ground","The ground has been recently turned over, as if "+
      "something were planted here.\n");


    add_exit(EXIT1);
    add_exit(EXIT2);
    add_stuff();

     set_up_herbs( ({   GONDOR_HERB_DIR + "suranie",
                        GONDOR_HERB_DIR + "lothore",
                        SHIRE_HERB_DIR  + "bilberry", 
                        SHIRE_HERB_DIR  + "hensbane",
                        GONDOR_HERB_DIR + "saffron",
                        
                        }),
                  ({"river","ground","riverbank","flowers","path","track"}), 3);


    set_drink_from( ({ "river", "brandywine", "baranduin", }) );
}

void
reset_shire_room()
{
    add_stuff();
}

void
add_stuff()
{
    object ranger;
    if (!objectp(present("ranger")))
    {
	ranger = clone_object("/d/Gondor/common/npc/n_ranger");
	ranger->arm_me();
	ranger->set_random_move(20);
	tell_room(TO,"A silent man steps out of the bushes.\n");
	ranger->move(TO);

	ranger = clone_object("/d/Gondor/common/npc/n_ranger");
	ranger->add_prop(OBJ_I_HIDE, random(ranger->query_skill(SS_HIDE)));
	ranger->arm_me();
	ranger->move(TO);

    rock = clone_object(ROCK_DIR + "rock");
    rock->move(TO);
    }

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
