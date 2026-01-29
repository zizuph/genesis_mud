/* Modified August 11, 2001 by Serif:
 * set_long changed to allow for varying screen widths;
 * set_long edited slightly for syntax and grammar (standard, archaic
 *    instead of modern, metric);
 * pragma added
 */

#pragma strict_types

inherit "/std/object";

#include "/sys/stdproperties.h";

void
create_object() 
{
    set_name("tusk");
    add_name("ivory");
    add_name("horn");
    set_adj("ivory");
    set_adj("large");
    set_short("large ivory tusk");
    set_pshort("large ivory tusks");
    set_long("This is the large ivory tusk from an oliphaunt! It is yellowish "
        + "white in colour and smooth to the touch, though rough in some "
        + "places where scars from battle have marked it. Its length is "
        + "impressive at about ten feet. It seems valuable, and it is bound "
        + "with gold, making it worth even more.\n"); 
    add_prop(OBJ_I_WEIGHT,25700);
    add_prop(OBJ_I_VOLUME,15000);
    add_prop(OBJ_I_VALUE,2500);
}
