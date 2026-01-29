/*******************************************************************
 * backpack.c                                                    - *
 * changed this backpack to something more simplier hopefully to - *
 * removed the recent bug reports by this.                       - *
 * Damaris 11/19/02                                              - *
 *                                                               - *
 * Modified - Januay 7, 2021 - Added recovery - Mirandus         - *
 ******************************************************************/
#include "defs.h"
inherit "/d/Genesis/std/wearable_pack";
inherit "/lib/keep"; 

void
create_wearable_pack()
{
    set_name("backpack");
    add_adj(({"enormous", "leather"}));
    set_long("It is made of luxuriant leather that appears to have been "+
      "weathered by long exposure to the sun. It is enormous in size so "+
      "can hold a large number of items. Use 'keep' to keep it from being "+
      "sold and 'fill pack' and 'empty pack' to store and retrieve items "+
      "from it.\n");

    set_mass_storage(1); 

    set_keep(1); 

    add_prop(CONT_I_WEIGHT, 5000);
    add_prop(CONT_I_MAX_WEIGHT, 175000);
    add_prop(CONT_I_VOLUME, 9000);
    add_prop(CONT_I_MAX_VOLUME, 175000);

    add_prop(OBJ_I_VALUE, 450);
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
