/* A pair of quilt leggings - Tulix III, recoded 13/07/95 */
/* This armour is used by  */

inherit "/std/armour";
#include <stdproperties.h>
#include <wa_types.h>
                               
void
create_armour()
{
    set_name("leggings");
    set_pname("pairs of leggings");
    add_pname("armours");
    set_short("pair of quilt leggings");
    set_pshort("pairs of quilt leggings");
    set_long("It's a pair of quilt leggings that is made from "  
        + "two layers of thick cloth, with a layer of filling material " 
        + "to separate them.\n");

    set_adj("quilt");
    add_adj("pair of");
    
    set_ac(12); /* standard quilt leggings, no mod. */

    /* Set slash,impale,bludgeon, modifiers.  */
    set_am(({  -1,  -1,    2}));
    set_at(A_LEGS);
    
    add_prop(OBJ_I_WEIGHT, 1500);
    add_prop(OBJ_I_VOLUME, 1000);
}
