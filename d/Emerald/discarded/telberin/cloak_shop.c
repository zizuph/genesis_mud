inherit "/std/room";

#include "default.h"
#include <stdproperties.h>

void create_room()
{
    string sign;

    set_short("Cloak shop");
    set_long("   Judging from the sign near the entrance, this is a " +
        "soon-to-open cloak shop.  The stylish interior of the " +
        "shop hints at the high quality and fashion of the clothing " +
        "which will soon be sold here.\n");


    sign = "\n" +
           "              Cloaks of Telberin\n" +
           "              ==================\n" +
           "\n" +
           "                Opening Soon\n";

    add_item("sign", sign);
    add_cmd_item("sign", "read", sign);

    add_item("entrance", "The entrance leads in from the streets of " +
        "Telberin.\n");

    add_item(({ "interior", "stylish interior" }), "The shop is " +
        "decorated with elegant furniture and lovely paintings.  Soft " +
        "music plays in the background.\n");

    add_item(({ "furniture", "elegant furniture" }), "Fine antique " +
        "furniture.  It looks quite valuable.\n");

    add_item(({ "paintings", "lovely paintings", "painting" }),
        "Several oil paintings of Telberin and surrounding lands " +
        "hang on the walls.\n");

    add_prop(ROOM_I_INSIDE, 1);

    add_exit(AVENUE_DIR + "ave23", "east");
}
