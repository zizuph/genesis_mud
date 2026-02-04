inherit "/d/Terel/std/wearable_item";

#include "/d/Terel/include/Terel.h"
#include <wa_types.h>
#include <ss_types.h>
#include <stdproperties.h>
#include <macros.h>
#define DRAGONFIRE "_terel_dragonfire"

void
create_terel_wearable_item()
{
    set_name("amulet");
    set_adj(({"red", "dragon"}));
    set_short("red circular amulet");
    set_long("A red circular amulet, with a design of a red dragon on it's face. "+
        "A chain of steel links holds the amulet around your neck."+
        " Careful work went into the details of the dragon design."+
        " The amulet is surely worth a good deal of money.\n");
    set_terel_wearable_item_size(ANY_SIZE);
    set_slots(A_NECK);
    set_looseness(0);
    set_layers(0);
    add_prop(OBJ_I_IS_MAGIC_ARMOUR, 1);
    add_prop(MAGIC_AM_MAGIC,({100,"enchantment"}));
    add_prop(OBJ_S_WIZINFO,"This amulet only works in Terel. "+
                   "It protects the wearer from the breath of the red "+
                   "dragon of Terel.\n");

    add_prop(MAGIC_AM_ID_INFO,({
             "The amulet will protect you from the flames of the dragon "+
             "it was crafted to combat.\n",70}));

    add_prop(OBJ_I_WEIGHT, 50);
    add_prop(OBJ_I_VOLUME, 25);
    add_prop(OBJ_I_VALUE, 1728);
}

public mixed
wear_terel_item(object item)
{
    TP->add_prop(DRAGONFIRE,1);
    TO->add_prop(OBJ_I_INVIS, 1);
    return 0;
}

public mixed
remove_terel_item(object item)
{
    TP->remove_prop(DRAGONFIRE);
    TO->remove_prop(OBJ_I_INVIS);
    return 0;
}

public string
query_recover()
{
    return 0;
}
