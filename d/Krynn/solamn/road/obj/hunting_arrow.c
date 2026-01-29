#include </stdproperties.h>

inherit "/std/arrow";

public void
create_arrow()
{
    set_adj("grey-feathered");

    set_projectile_id("grey_feathered_arrow");
    set_hit(30);
    set_pen(30);

}

string
get_projectile_long(string str, object for_obj, int num)
{
    return ((num == 1) ? "This arrow is" : "These arrows are") + 
      " made of the wood hornbeam, and fletched with grey feathers.\n";
}

