inherit "/d/Shire/eastroad/std/er_base";
inherit "/d/Gondor/common/lib/drink_water.c";

#include "/d/Shire/common/herbs/herb_list.h"
#include "/d/Shire/common/defs.h"
#include "/sys/stdproperties.h"
#include "/sys/macros.h"
#include "local.h"

#define EXIT1 ER_BASE_DIR + "girdley/girpath3","west","@@give_message"
#define EXIT2 ER_BASE_DIR + "girdley/isle2","north",0,1
#define EXIT3 ER_BASE_DIR + "girdley/isle4","east",0,1
void add_stuff();
object rock;


int
give_message()
{
    write("You splash out into the slow-moving water and make your way "+
      "across the river to the western bank.\n");
    return 0;
}


void
create_er_room()
{

    area = "on the western shore of";
    areaname = "Girdley Island";
    land = "the Shire";
    areatype = 7;
    areadesc = "grassy sandy bank";
    grass = "green";
    treetype = "fruit";

    extraline = "The western bank of Girdley Island in the middle of "+
    "the Brandywine is grassy and sandy, collecting silt that washes "+
    "downstream.  To the east, a forest grove clusters around a small "+
    "hill, and northwards a path leads into a clearing.  West the ford "+
    "goes to the other side of the river.";

    add_item(({"bank","western bank","sand","grass","silt"}),
      "The bank is a light brown, covered mostly by the silt that "+
      "finds its way here from the north, though a few hardy strains "+
      "of wild grasses grow in clumps several feet from the water.\n");
    add_item(({"grove","forest","forest grove"}),
      "The forest grove is made of small fruit trees, probably pear trees, "+
      "though it is impossible to be certain from this distance.\n");
    add_item(({"small hill","hill"}),
      "The small hill is ringed with newly planted fruit trees.\n");
    add_item(({"path","north path"}),
      "The northern path is made of dirt and some water-smoothed rocks.\n");
    add_item(({"clearing","northern clearing"}),
      "The clearing to the north seems to have been made recently.\n");
    add_item(({"west","ford","other side"}),
      "The ford leads west to the other side of the river-where the water is "+
      "not too deep to walk across.\n");
    add_item(({"water","river","brandywine","baranduin"}),
      "The brown muddy water of the Brandywine ripples as it flows "+
      "downstream.\n");

    add_exit(EXIT1);
    add_exit(EXIT2);
    add_exit(EXIT3);
    add_stuff();

     set_up_herbs( ({   GONDOR_HERB_DIR + "attanar",
                        GONDOR_HERB_DIR + "lothore",
                        SHIRE_HERB_DIR  + "tansy", 
                        SHIRE_HERB_DIR  + "parsley",
                        GONDOR_HERB_DIR + "gonion",
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
    object ranger, ranger2;
    if(!present("ranger"))
    {
	ranger = clone_object("/d/Gondor/common/npc/n_ranger");
	tell_room(TO,"A silent man steps out of the bushes.\n");
	ranger->add_prop(OBJ_I_HIDE, 45);
	ranger->arm_me();
	ranger->move(TO);

	ranger2 = clone_object("/d/Gondor/common/npc/n_ranger");
	ranger2->set_restrain_path(({"/d/Shire/eastroad/girdley"}));
	ranger2->set_random_move(20);
	ranger2->arm_me();
	tell_room(TO,"A silent man steps out of the bushes.\n");
	ranger2->move(TO);

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
