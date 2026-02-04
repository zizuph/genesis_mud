/*
 * chain.c
 *
 */
inherit "/d/Terel/std/chain";

#include "/d/Terel/include/Terel.h"
#include <stdproperties.h>
#include "/d/Terel/LoD/dungeon/quest.h"

public void
create_rope()
{
    set_name("chain");
    add_name("chains");
    add_name(DQ_HYDRA_CHAIN);
    set_adj("iron");
    
    set_long("It's an iron chain. It seems to be of high-quality. " +
             "It has a chain-lock on it.\n");
    
    add_item(({"lock", "chain lock", "chain-lock"}),
             "To remove the chain one needs a key.\n");
    
    add_prop(OBJ_I_WEIGHT, 15000);
    add_prop(OBJ_I_VOLUME, 5000);
    add_prop(OBJ_I_VALUE, 74);
}
