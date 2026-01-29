inherit "/d/Shire/eastroad/std/er_base";
inherit "/d/Gondor/common/lib/drink_water.c";

#include "/d/Shire/common/herbs/herb_list.h"

#include "/d/Shire/common/defs.h"
#include "/sys/stdproperties.h"
#include "/sys/macros.h"


#include "local.h"

#define EXIT1 ER_BASE_DIR + "girdley/isle1","west",0,1
#define EXIT2 ER_BASE_DIR + "girdley/isle3","north",0,1


void
create_er_room()
{

    area = "in the middle of";
    areaname = "Girdley Island";
    land = "the Shire";
    areatype = 7;
    areadesc = "freshly-cut path";
    grass = "green";
    treetype = "birch";

    extraline = "The path that leads this way from the west here "+
    "curves to the north, making a semi-circle.  The trees are not "+
    "cleared here and the path is fairly narrow, though not overgrown "+
    "as it has been recently cleared.  The path leads north and west.";

    add_item(({"path","narrow path"}),
      "The path has been recently made, seemingly cut from the youngest and "+
      "smallest growth, as it meanders greatly through the trees.\n");

    add_exit(EXIT1);
    add_exit(EXIT2);

     set_up_herbs( ({   GONDOR_HERB_DIR + "tuo",
                        GONDOR_HERB_DIR + "tyelka",
                        SHIRE_HERB_DIR  + "oreste", 
                        SHIRE_HERB_DIR  + "marshmallow",
                        GONDOR_HERB_DIR + "bean_green",
                        
                        }),
                  ({"river","ground","riverbank","flowers","path","track"}), 3);

    set_drink_from( ({ "river", "brandywine", "baranduin", }) );
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
