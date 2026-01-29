#include </stdproperties.h>

inherit "/std/arrow";
inherit "/lib/keep";

public void
create_arrow()
{
    set_adj("leaf-headed");

    set_projectile_id("leaf_headed_arrow");
    set_short("leaf-headed arrow");
    set_pshort("leaf-headed arrows");

    set_hit(43);
    set_pen(43);
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
      ((num == 1) ? "Its flanged arrowhead" : "Their flanged arrowheads") +
      " made of blue tempered steel " + ((num == 1) ? "allows" : "allow") +
      " you to inflict great damage.\n"; 

}

