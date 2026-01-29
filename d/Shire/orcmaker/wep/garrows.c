/*
 * Orcmaker arrows
 * --Finwe, June 2004
 */

#include </stdproperties.h>

inherit "/std/arrow";

public void
create_arrow()
{
    set_adj(({"wooden"}));
    
    set_projectile_id("shire_orc_arrow");
    set_hit(25);
    set_pen(35);
}

string
get_projectile_long(string str, object for_obj, int num)
{
    if (num == 1)
    {
	return "This is a wooden arrow suitable for bows. It was made by " +
        "orcs and looks deadly. The shaft is made from sticks, and the " +
        "fins are made from the feathers of a black bird. The arrowhead " +
        "is made of blackened iron, hammered into a crude but efficent edge.\n";
    }
    else
    {
	return "These are wooden arrows suitable for bows. They were made by " +
        "orcs and look deadly. The shafts are made from sticksand the " +
        "fins are made from feathers of a black bird. The arrowheads " +
        "are made of blackened iron, that has been hammered into crude " +
        "but efficent edges.\n";
    }
}

