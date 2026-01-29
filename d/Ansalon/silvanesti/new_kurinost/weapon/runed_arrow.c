#include </stdproperties.h>

inherit "/std/arrow";
inherit "/lib/keep";

public void
create_arrow()
{
    set_adj("rune-covered");

    set_projectile_id("rune_covered_arrow");
    set_short("rune-covered arrow");
    set_pshort("rune-covered arrows");

    set_hit(58);
    set_pen(54);
    add_prop(OBJ_I_IS_MAGIC_WEAPON, 1);
    add_prop(MAGIC_AM_MAGIC, ({20, "enchantment"}));
    add_prop(OBJ_S_WIZINFO, "The arrows made by Silvanesti elves and " +
        "guarded by an ancient green dragon as a loot item, " +
        "best quality and deadly and thus they have so high and pen.\n");
    add_prop(MAGIC_AM_ID_INFO,
        ({"These arrows were crafted by the Silvanesti elves, and " +
        "enchanted by their wizards to be incredibly accurate and " +
        "deal massive damage.\n", 20 }));
    set_keep(1);

}

string
get_projectile_long(string str, object for_obj, int num)
{
    return ((num == 1) ? "This arrow is" : "These arrows are") + 
      " beautifully crafted and inscribed with runes of powerful elven " +
      "magicks. Well balanced and straight, with fins made from griffin " +
      "feathers and " + ((num == 1) ? "a flanged arrowhead" : "flanged " +
      "arrowheads") + " made of blue star metal, " + ((num == 1) ? "this " +
      "arrow provides" : "these arrows provide") + " incredible accuracy " +
      "and damage.\n"; 

}

