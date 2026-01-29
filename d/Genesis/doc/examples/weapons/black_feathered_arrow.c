#include </stdproperties.h>

inherit "/std/arrow";

public void
create_arrow()
{
    set_adj("black-feathered");

    set_projectile_id("black_feathered_arrow");
    set_hit(55);
    set_pen(60);
}

string
get_projectile_long(string str, object for_obj, int num)
{
    return ((num == 1) ? "This arrow is" : "These arrows are") + 
      " obviously of good making. Well balanced, straight and with " + 
      "fins made from feathers that gleam in a spectrum of colours. " + 
      "Tipped with " + ((num == 1) ? "a head" : "heads") +
      " of blue tempered steel the " + ((num == 1) ? "arrow" : "arrows") +
      " look both graceful and beautiful, but above all else; lethal.\n";
}

