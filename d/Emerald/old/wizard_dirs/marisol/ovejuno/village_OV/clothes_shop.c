
// Laurent's Silken Pillow (/d/Avenir/common/bazaar/intr/silkshop.c)
// creator(s):   Grace Nov 15 1995
// last update:
// purpose:      Provides women's clothing, esp for Dancers
// note:
// bug(s):
// to-do:
/* Modified by Marisol to be used as the weaver_shop for Fan in 
 * the new Re Albi. (2/24/98) */
/* Modified by Marisol for the tailor in the town of Ovejuno in
 * Emerald (07/13/98)*/


inherit "/d/Emerald/std/room";
inherit "/d/Emerald/lib/shop_room";

#include "defs.h"

#define STORE_ROOM   OV_DIR_VIL + "clothes_store"

object gorgi;

void
reset_room()
{
    if (!gorgi)
    {
        setuid();
        seteuid(getuid());

        gorgi = clone_object(OV_VILLAGE_NPC + "gorgi");
        gorgi->move(this_object(), 1);
        tell_room(this_object(), "The shopkeeper arrives.\n", gorgi);
    }
}

void
create_emerald_room()
{
    string str;

    set_short("clothes shop");
    set_em_long("This is the shop of Gorgi the Clothier. He really "+
        "doesn't weave or sew but he has a seamtress that does "+
        "that kind of job for him. He gets materials mainly by trading "+
        "with gypsies and other merchants that visit the village when "+
        "using the mountain pass. He sells from simple textiles like "+
        "wool to more exotic fabrics like silk. His shop is a functional "+
        "structure with little adorn besides the bolts of colorful "+
        "fabrics here and there. Gorgi attends the store by himself "+
        "and doesn't talk too much. If you want to buy some clothes "+
        "from him, you should read the wooden sign in the wall.\n");


    add_item(({"bolts of colorful fabrics", "fabrics", "bolts"}),
        "Light colored silks and gauze adorn the white walls of "+
        "shop. Like a pastel rainbow, yellow, red, orange, green, "+
        "violet and blue silks and gauze hang from wall to floor, "+
        "leaving small patches of white, like clouds on the sky.\n");

    add_item(({"wall", "walls"}),
        "White wooden walls are covered with bolts of colorful "+
        "fabrics, giving the room a cheery look.\n");

    str = "              Gorgi's Clothes Shop\n"+
        "              ^^^^^^^^^^^^^^^^^^^^^^^^\n"+
        "  Gorgi is proudly known as the best clothier in all Ovejuno.\n"+
        "  Beautiful silks and warm wool are his specialty. Also he\n"+
        "  sells elegant and useful leather clothes from the best\n"+
        "  tanners. This shop operates like any other. To see what\n"+
        "  items are for sale at this time, please use <list>.\n"+
        "     Thank you for your patronage of Gorgi's Clothes Shop.\n";
  
    add_item("sign", str);
    add_cmd_item("sign", "read", str);

    reset_room();

    setuid();
    seteuid(getuid());
    clone_object(DOORS+"weaver_in.c")->move(this_object());
}

/*
 * Function name:   init
 * Description:     Is called for each living that enters this room
 * Returns:
*/

void
init()
{
    ::init();
    init_shop_room();
}
                                                                       
