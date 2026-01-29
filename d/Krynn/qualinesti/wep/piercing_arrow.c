#include </stdproperties.h>

inherit "/std/arrow";
inherit "/lib/keep";

public void
create_arrow()
{
    set_adj("narrow-headed");
    set_short("narrow-headed arrow");
    set_pshort("narrow-headed arrows");

    set_projectile_id("armour_piercing_arrow");
    set_hit(48);
    set_pen(48);
    add_prop(OBJ_I_IS_MAGIC_WEAPON, 1);
    add_prop(MAGIC_AM_MAGIC, ({20, "enchantment"}));
    add_prop(OBJ_S_WIZINFO, "The arrows made by Qualinesti elves, " +
        "best quality and deadly and thus they have so high and pen.\n");
    add_prop(MAGIC_AM_ID_INFO,
        ({"These lethal arrows were made by Qualinesti elves.\n", 20,
        "All you can say about those arrows is that they are lethal and " +
        "that you feel some form of enchantment from them. However, you " +
        "can not recognize it.\n", 40 }));
    set_keep(1);
 
}

string
get_projectile_long(string str, object for_obj, int num)
{
    return ((num == 1) ? "This arrow is" : "These arrows are") + 
      " obviously of good making. Well balanced, straight and with " + 
      "fins made from white feathers. " + 
      ((num == 1) ? "It has a narrow spiked head, made from prime"+
      " quality steel, which increases" : "They have" +
      " narrow spiked heads made from prime quality steel, which" +
      " increase") +
      " the chance of piercing through armour.\n";

}

