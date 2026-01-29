/*  /d/Raumdor/common/beach/bountiful/chest_rewards/c_toy_soldiers.c
 *
 *  Money Drop Item - Common.
 *
 *  Nerull, 2021
 *
 */


inherit "/std/object";
#include "../defs.h";
#include <stdproperties.h>
#include <macros.h>


void
create_object()
{
    set_name("soldiers");
    add_name("set");
    set_adj("ivory");
    add_adj("toy");

    set_short("set of ivory toy soldiers");
    set_pshort("sets of ivory toy soldiers");
    
    set_long("Some with shields and swords, others with pikes or "
    +"bows, and some upon horseback, this toy soldier set is "
    +"meticuliously crafted down to the hats worn.\n");
    
    add_prop(OBJ_I_WEIGHT, 600);
    add_prop(OBJ_I_VOLUME, 1000);
    add_prop(OBJ_I_VALUE, 12000);
}