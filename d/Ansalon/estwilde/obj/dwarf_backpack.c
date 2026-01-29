#pragma save_binary

inherit "/d/Genesis/std/wearable_pack";
inherit "/lib/keep";

#include <stdproperties.h>
#include <macros.h>
#include <composite.h>
#include "/d/Ansalon/common/defs.h"

object this;

void
create_wearable_pack()
{
    set_name("backpack");
    set_pname("backpacks");
    set_short("large dwarven backpack");
    set_pshort("dwarven backpacks");
    add_name("pack");
    set_adj(({"dwarven","large"}));
    set_long("This is a very large backpack, skillfully made " +
      "by dwarven craftsmen of Iron Delving. You may <fill> and <empty> " +
      "the backpack as you wish.\n");

    set_mass_storage(1); 

    set_keep(1); 

    add_prop(CONT_I_WEIGHT, 4800);
    add_prop(CONT_I_MAX_WEIGHT, 300000); /* grams */
    add_prop(CONT_I_VOLUME, 10000);  
    add_prop(CONT_I_MAX_VOLUME, 300000);

    add_prop(OBJ_I_VALUE, 900);

}


string
query_recover()
{
    return MASTER + ":" + query_container_recover() + query_keep_recover();
}

void
init_recover(string arg)
{
    init_container_recover(arg);
    init_keep_recover(arg); 
}

