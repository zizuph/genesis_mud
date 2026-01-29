// -*-C++-*-
// file name:    bronze arrows
// creator(s):   Lilith  Jun 2004
// last update:
// purpose:      Something to help out the fledgling archers 
// note:         
// bug(s):
// to-do: 

inherit "/std/arrow";
inherit "/lib/keep";

#include </stdproperties.h>

string
get_projectile_long(string str, object for_obj, int num)
{
    return "Considerably shorter than the arrows normally used for "+
        "longbows, "+ ((num == 1) ? "this arrow is" : "these arrows are")+ 
        " only about as long as your arm from elbow to wrist. "+
        "The shaft of "+ ((num == 1) ? "each" : "this")+ " arrow is "+
        "made of spiral-patterned yark wood, tipped with bronze, and "+
        "fletched with feathers from a dove.\n";
}

void
create_arrow()
{
    set_adj(({"short", "bronze-tipped"}));
    set_projectile_id("dove_fletched_arrow");

    add_item(({"shaft", "wood", "yarkwood", "yark", "yark wood"}),
        "The wood is from the yark bush that is native to parts of "+
        "the Sybarun Isles. It has a spiral pattern along its length.\n");
    add_item(({"pattern", "spiral", "spiral pattern"}),
        "The spiral pattern results from the removal of the thorns "+
        "that normally grow on this wood. It helps set the arrow "+
        "spinning toward its target.\n");

    set_hit(35);
    set_pen(35);
    set_keep();
}

