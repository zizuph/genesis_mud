inherit "/d/Shire/eastroad/std/er_base";
inherit "/d/Gondor/common/lib/drink_water.c";

#include "/d/Shire/common/herbs/herb_list.h"
#include "/d/Shire/common/defs.h"
#include <stdproperties.h>
#include <macros.h>
#include "local.h"

#define EXIT1 ER_BASE_DIR +"girdley/girpath2","north",0,1

object ranger;

int do_climb(string str);
void add_stuff();
public void drink_message(string from);

void
create_er_room()
{
    int i;
    area = "just north of";
    areaname = "the Brandywine Bridge";
    land = "the Shire";
    areatype = 1;
    areadesc = "overgrown river path";
    grass = "green";
    extraline = "This narrow path leading along the Brandywine "+
    "river is overgrown and obviously in disuse.  It leads north from "+
    "here towards an island in the distance and south to the narrowing "+
    "of the river at the Bridge of Stonebows.  Here the Bridge towers "+
    "high above, its pillars vast and trunked like a tree.";
    add_item(({"island","girdley island","triangular island"}),
      "The triangular island in the distance is Girdley island, and "+
      "it marks the point of last navigation up the Brandywine to "+
      "the north.\n");
    add_exit(EXIT1);
    add_exit(ER_BASE_DIR + "girdley/underbridge","south",0,1);
    add_stuff();
     set_up_herbs( ({   GONDOR_HERB_DIR + "attanar",
                        GONDOR_HERB_DIR + "redweed",
                        SHIRE_HERB_DIR  + "huckleberry", 
                        SHIRE_HERB_DIR  + "lianor_berry",
                        GONDOR_HERB_DIR + "strawberry",
                        
                        }),
                  ({"river","ground","riverbank","flowers","path","track"}), 3);

    set_drink_from( ({ "river", "brandywine", "baranduin", }) );
}
void
init()
{
    ::init();
    add_action("do_climb","climb");
    init_drink();

}
int
do_climb(string str)
{
    if(!str)
    {
	write("Climb what?\n");
	return 1;
    }
    if((str != "bridge") && (str != "onto bridge") && (str != "up bridge"))
    {     write("Climb where?\n");
	return 1;
    }
    write("You climb, with great effort, up the side of the slick stone "+
      "bridge.\n");
    SAYBB(" climbs laboriously up the side of the bridge.");
    TP->move_living("M",ER_DIR + "stonebows",1,0);
    SAYBB(" arrives climbing from underneath the bridge.");
    return 1;
}


void
add_stuff()
{
    if (!objectp(ranger))
    {
	ranger = clone_object("/d/Gondor/common/npc/n_ranger");
	ranger->arm_me();
	ranger->add_prop(OBJ_I_HIDE, 50);
	ranger->move(TO);
    }
}

void
reset_shire_room()
{
    add_stuff();
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