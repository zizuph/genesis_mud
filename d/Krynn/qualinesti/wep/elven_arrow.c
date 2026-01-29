#include </stdproperties.h>

inherit "/std/arrow";
inherit "/lib/keep";

public void
create_arrow()
{
    set_adj("white-feathered");
    set_short("white-feathered arrow");
    set_pshort("white-feathered arrows");
    set_projectile_id("white_feathered_arrow");
    set_hit(40);
    set_pen(40);
    set_keep(1);

}

string
get_projectile_long(string str, object for_obj, int num)
{
    return ((num == 1) ? "This arrow is" : "These arrows are") + 
      " obviously of good making. Well balanced, straight and with " + 
      "fins made from white feathers. " + 
      "Tipped with " + ((num == 1) ? "a head" : "heads") +
      " of blue tempered steel the " + ((num == 1) ? "arrow" : "arrows") +
      " look both graceful and beautiful, but above all else; lethal.\n";
}

