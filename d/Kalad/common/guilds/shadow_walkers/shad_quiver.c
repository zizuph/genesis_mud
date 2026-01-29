inherit "/std/container";

#include "/d/Kalad/defs.h"

/* 
 * The quiver for arrows. Can also be a case for quarrels.
 * Sarr 20.Jul.97 
 *
 */

object get_arrow(object ob);

void
create_container()
{
    set_name("quiver");
    set_adj(({"black","leather"}));
    set_short("black leather quiver");
    set_long("This is a quiver for storing arrows, or quarrels, made "+
    "out of fine leather that has been dyed black.\n");
    
    add_prop(CONT_I_WEIGHT,150);
    add_prop(CONT_I_MAX_WEIGHT,850);
    add_prop(CONT_I_VOLUME,200);
    add_prop(CONT_I_MAX_VOLUME,1000);
}

object
get_arrow(object me)
{
    int i;
    object *obs,ob;
    obs = all_inventory(TO);
    if(!sizeof(obs))
        return ob;
    ob = obs[0];
    return ob;
}

