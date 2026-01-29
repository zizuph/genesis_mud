/*
 *   The storage room of the Calathin Armour Shop
 */

#include <files.h>

inherit "/d/Terel/std/room";
inherit "/lib/store_support";

#include <stdproperties.h>
#include "/d/Terel/include/Terel.h"
#define GON_JAR "/d/Gondor/common/guild/obj/herbjar"
#define GON_POUCH "/d/Gondor/common/guild/obj/herbpouch"
#define SHIRE_LEATHER "/d/Shire/guild/smiths/obj/sm_leath.c"
#define SHIRE_POLE "/d/Shire/guild/smiths/obj/sm_wood.c"

/* prototype */



public void
enter_inv(object ob, object from)
{
    ::enter_inv(ob, from);
    store_update(ob);
}

void
create_room() 
{
    set_short("The store room of Sturdy Shield Armour Shop");
    set_long("This is the store room for the Sturdy Shield Armour Shop.\n");
    add_prop(ROOM_I_INSIDE, 1);  /* This is an inside room */

    set_default_stock(({ 
        POTION_VIAL_OBJECT, 4,
        CALATHIN_DIR + "obj/saddlebag", 4,
        CALATHIN_DIR + "obj/backpack",4,
        CALATHIN_DIR + "obj/caisson",3,
        CALATHIN_DIR + "obj/powaghen",3,
        SHIRE_LEATHER, 100,
        SHIRE_POLE, 10,
        CALATHIN_DIR + "obj/diddie",3}));

    reset_store();
}

void reset_room()
{
    reset_store();
}
