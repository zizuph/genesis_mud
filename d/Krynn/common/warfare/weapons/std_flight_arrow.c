#include </stdproperties.h>

inherit "/std/arrow";
inherit "/lib/keep";

public void
create_arrow()
{
    set_adj("flight");

    set_projectile_id("flight_headed_arrow");
    set_short("flight arrow");
    set_pshort("flight arrows");

    set_hit(30);
    set_pen(30);
    set_keep(1);

}

string
get_projectile_long(string str, object for_obj, int num)
{
    return ((num == 1) ? "This arrow is" : "These arrows are") + 
      " designed for hunting. Light and capable of incredible range, " +
      ((num == 1) ? "it" : "they") + " can cause quite a bit of damage " +
      "from a distance.\n"; 
}

