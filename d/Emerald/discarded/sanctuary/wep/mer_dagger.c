/* Dagger created by Stexan 1/97 for Wandering Mercenaries */

inherit "/std/weapon";

#include <wa_types.h>
#include <formulas.h>
#include <stdproperties.h>
#include <macros.h>

void
create_weapon()

{

    set_name("dagger");
    set_adj("sharp");
    set_adj("long");
    set_long("This ornate dagger is as long as your forearm and is " +
      "extremely sharp. Obviously made by a master craftsman, " +
      "shadows dance across the hilt and the blade.\n");

    add_item("hilt", "It seems to reflect shadows.\n");
    add_item("blade", "Very sharp with words inscripted on it.\n");
    add_cmd_item(({"blade", "inscription"}), ({"read"}), "@@dagger_desc@@");
    set_hit(10);
    set_pen(15);
    set_wt(W_KNIFE);
    set_dt(W_SLASH | W_IMPALE);
    set_hands(W_ANYH);

    add_prop(OBJ_I_VALUE, F_VALUE_WEAPON(10,15) + random(20) -10);
    add_prop(OBJ_I_WEIGHT, F_WEIGHT_DEFAULT_WEAPON(10,15) + random(50) - 25);
    add_prop(OBJ_I_VOLUME, query_prop(OBJ_I_WEIGHT)/5);

}

string
dagger_desc()
{
    return "     The inscription reads :\n\n" +
    "Beware all who wield this weapon, darkness shall only " +
    "follow those that do.\n";
}

