/* 
 * /w/aeg/gnome/obj/dowel_s.c
 *
 * A dowel meant to be a leftover
 * from mechanical creatures
 * 
 * Created March 2008, by Aeg (Matthew Morin)
 */
 
inherit "/std/object";
#include <stdproperties.h>
#include <macros.h>
 
void
create_object()
{
    set_name("dowel");
    add_name("part");
    set_pname("dowels");
    set_adj( ({"thin", "wooden"}) );
    set_long("This is a cylindrical rod of wood that appears to "
        + "be much thinner than 1 centemeter in diameter. "
        + "It is quite flimsy and very light.\n");
    add_prop(OBJ_I_VALUE, 10);
    add_prop(OBJ_I_WEIGHT, 5);
    add_prop(OBJ_I_VOLUME, 10);
}
