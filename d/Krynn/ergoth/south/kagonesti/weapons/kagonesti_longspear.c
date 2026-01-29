#include <wa_types.h>
#include <stdproperties.h>
#include <formulas.h>

#define ADJ     ({ "Kagonesti", "hefty", "tasseled", "sturdy" })
#define COLORS  ({ "yellow", "green", "blue", "white" }) 

inherit "/std/weapon";

void create_weapon()
{
    int hit = 15 + random(15),
        pen = 25 + random(10);
    string adj = one_of_list(ADJ),
           col = one_of_list(COLORS);
           
    set_name(({"longspear", "spear"}));
    set_adj(adj);
    set_short(adj + " longspear");
    set_long("This long-shafted spear is a Kagonesti weapon, adapted for "
        + "success in hunting and fighting. It it weighty for a spear, "
        + "enabling it to take down larger prey and penetrate thicker "
        + "armour. A bright " + col + " tassel is attached near the tip.\n");
    add_item("shaft", "The shaft is made of a dark, sturdy wood and is much "
        + "longer than most spear shafts.\n");
    add_item("tassel", "The " + col + " tassel is attached to the tip of the "
        + "spear, helping to disguise quick jab attempts in a flurry of "
        + "color.\n");
    add_item("tip", "The tip is elongated with a crossguard near where the "
        + "tip meets the shaft.\n");
    add_item("crossguard", "The crossguard prevents the weapon from "
        + "penetrating too deeply, making subsequent removal much easier.\n");
    set_default_weapon(hit, pen, W_IMPALE, W_BOTH);
    set_wt(W_POLEARM);
    add_prop(OBJ_I_VOLUME, 4000);
    add_prop(OBJ_I_WEIGHT, 8000);
    add_prop(OBJ_I_VALUE, F_VALUE_WEAPON(hit,pen));
}
