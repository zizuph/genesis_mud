#include </stdproperties.h>

inherit "/d/Shire/abandoned/greyhavens/wep/rock_base";

public void
create_arrow()
{
    set_adj("black");

    set_projectile_id("black_rock");
    set_hit(45);
    set_pen(24);
}

string
get_projectile_long(string str, object for_obj, int num)
{
    return ((num == 1) ? "This rock is" : "These rocks are") +
      " black, shiny, and well balanced.\n";
}

