/* Bag of holding. ~solace/puzzle/objects/bag_holding */

inherit "/std/receptacle";

#include "../defs.h"
#include "/sys/stdproperties.h"

#define ITEMS ({ "objects/gold_bar",     \
                 "armour/str_amulet",    \
                 "weapons/sword_fire",   \
                 "armour/pearl_necklace" })

void fill_me_with_treasure()
{
    int i;

    seteuid(getuid(TO));
    remove_prop(CONT_M_NO_INS);
    change_prop(CONT_I_CLOSED, 0);

    for(i = 0; i < sizeof(ITEMS); i++)
        clone_object(PUZZLE_QUEST + ITEMS[i])->move(TO);

    change_prop(CONT_I_CLOSED, 1);
    add_prop(CONT_M_NO_INS, "The bag seems to be cursed! You can't put "+
                            "things in it.\n");
}

void create_receptacle()
{
    set_name("bag of holding");
    add_name("bag");

    add_prop(CONT_I_RIGID, 0);
    add_prop(CONT_I_TRANSP, 0);

    add_prop(OBJ_M_NO_SELL, 1);

    add_prop(CONT_I_WEIGHT, 50);  // 20th of a kilo weight.
    add_prop(CONT_I_VOLUME, 500); // Half of a litre volume.

    add_prop(CONT_I_MAX_WEIGHT, 100000); // 100 kilos basic capacity.
    add_prop(CONT_I_MAX_VOLUME, 500000); // 500 litres basic capacity.

    fill_me_with_treasure();
}

/* Do not adjust weight when objects
 * enter or leave the bag of holding.
 */
void leave_inv(object ob, object to) { }
void enter_inv(object dest, object old) { }

string long(object for_obj)
{
    return "A large satchel-like bag made of tough black leather. You "+
        "notice that it is surprisingly light for its size. "+
        ((query_prop(CONT_I_CLOSED)) ? "The straps on it have been buckled "+
        "shut.\n" : "It is open, to allow objects to be taken from it.\n");
}
