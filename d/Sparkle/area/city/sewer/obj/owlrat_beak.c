/* A beak meant to be a leftover
 * from owlrats
 * FEB 2009, Aeg
 */
 
inherit "/std/object";
#include <stdproperties.h>
#include <macros.h>
 
void
create_object()
{
    set_name("beak");
    add_name("part");
    set_pname("beaks");
    set_adj("pointed");
    set_adj("owlrat");
    set_long("This beak is very sharp and made of a hard material.\n");
    
    add_prop(OBJ_I_VALUE, 150);
    add_prop(OBJ_I_WEIGHT, 100);
    add_prop(OBJ_I_VOLUME, 40);
}
