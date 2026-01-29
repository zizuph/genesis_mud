#include </stdproperties.h>

inherit "/std/arrow";
inherit "/lib/keep";

public void
create_arrow()
{
    set_adj("sheaf");

    set_projectile_id("sheaf_headed_arrow");
    set_short("sheaf arrow");
    set_pshort("sheaf arrows");

    set_hit(40);
    set_pen(40);
    set_keep(1);

}

string
get_projectile_long(string str, object for_obj, int num)
{
    return ((num == 1) ? "This arrow is" : "These arrows are") + 
      " designed for war. Heavier and with less range than hunting " +
      "or flight arrows, it is capable of piercing thick armours and " +
      "causing considerably more damage. " + 
      ((num == 1) ? "Its steel arrowhead is" : "Their steel arrowheads are") +
      " well crafted and unbarbed.\n"; 
}

