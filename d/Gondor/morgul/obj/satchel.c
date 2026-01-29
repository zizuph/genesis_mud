/* Alteration of the common gondor satchel, allows for a bit
   more potions, as mages go through them quite fast.

   Eowul, August 2013
*/
#include <stdproperties.h>
   
inherit "/d/Gondor/common/potions/satchel";

public void
create_container()
{
    ::create_container();
    add_adj("black");
    set_short("black leather satchel");
    set_pshort("black leather satchels");  

    add_prop(CONT_I_MAX_WEIGHT,  80000);
    add_prop(CONT_I_MAX_VOLUME,  80000);  

}