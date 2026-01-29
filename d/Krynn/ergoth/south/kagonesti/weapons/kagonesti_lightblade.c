#include <wa_types.h>
#include <stdproperties.h>
#include <formulas.h>

#define ADJ  ({ "Kagonesti", "engraved", "well-crafted", "unpolished", \
            "rustic" })

inherit "/std/weapon";

void create_weapon()
{
    int hit = 20 + random(15),
        pen = 15 + random(10);
    string adj = one_of_list(ADJ);
           
    set_name(({"lightblade", "blade", "sword"}));
    set_adj(adj);
    set_short(adj + " lightblade");
    set_long("About the length of a shortsword, this weapon has a thin and "
        + "flexible blade for quick penetration and control. A fuller runs "
        + "its length, engraved with elaborate Kagonesti artwork.\n");
    add_item("fuller", "A groove that runs down the length of the blade, it "
        + "reduces the amount of metal in the weapon, keeping it light and "
        + "flexible. It is engraved with Kagonesti artwork.\n");
    add_item(({"artwork", "Kagonesti artwork"}), "The fuller of the blade is "
        + "engraved with a flowing floral motif.\n");
    add_item(({"motif", "floral motif"}), "The floral motif is intricately "
        + "engraved into the fuller of the blade.\n");
    set_default_weapon(hit, pen, W_IMPALE | W_SLASH, W_ANYH);
    set_wt(W_SWORD);
    add_prop(OBJ_I_VOLUME, 2200);
    add_prop(OBJ_I_WEIGHT, 5000);
    add_prop(OBJ_I_VALUE, F_VALUE_WEAPON(hit,pen));
}
