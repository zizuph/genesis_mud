/*
 * A round wicker basket for flowers.
 * Finwe, February 2005
 */

inherit "/std/receptacle";

#include "/d/Faerun/defs.h"
#include "flowers.h"
#include <macros.h>
#include <money.h>
#include <stdproperties.h>
#include <filter_funs.h>
#include <composite.h>

void
create_receptacle()
{
    int i;

    setuid(); seteuid(getuid());

    set_name("basket");
    add_name("round basket");
    set_pname("round baskets");
    add_pname("baskets");
    set_adj( ({"round", "wooden" }) );
    set_short("round wooden basket");
    set_pshort("round wooden baskets");
    set_long("This is a round wooden basket. It is made of braided, " +
        "flexible, strips of wood. The basket is plain and water-tight.\n");
    for(i=0; i<12; i++)
    {
        clone_object(FLOWERS_DIR + "rose_red_bud")->move(this_object(), 1);
    }
    add_prop(CONT_I_WEIGHT,     1200); 
    add_prop(CONT_I_MAX_VOLUME,  100);  
    add_prop(CONT_I_MAX_WEIGHT, 3000);      
    add_prop(CONT_I_RIGID, 1);            
    add_prop(OBJ_M_NO_SELL,"@@no_sell");
    add_prop(OBJ_I_VALUE, 150);
    add_prop(CONT_I_TRANSP,    0);
    add_prop(CONT_I_CLOSED,0);      /* starts opened */

}


mixed
no_sell()
{
  if(sizeof(all_inventory(this_object())))
    return "The "+short()+" still has something in it.\n";
  return 0;
}
