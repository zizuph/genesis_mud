/*******************************************************************
 * pack.c                                                        - *
 * Damaris 04/24/03                                              - *
 ******************************************************************/
inherit "/d/Genesis/std/wearable_pack";
inherit "/lib/keep"; 
#include <stdproperties.h>

void
create_wearable_pack()
{
    set_name("pack");
    add_adj(({"leather"}));
    set_short("leather pack");
    set_long("It is made of softened leather that is in very good "+
      "condition. It can hold a large number of items. Use 'keep' "+
      "to keep it from being sold and 'fill pack' and 'empty pack' "+
      "to store and retrieve items from it.\n");

    set_mass_storage(1); 

    set_keep(1); 

    add_prop(CONT_I_WEIGHT, 5000);
    add_prop(CONT_I_MAX_WEIGHT, 175000);
    add_prop(CONT_I_VOLUME, 9000);
    add_prop(CONT_I_MAX_VOLUME, 175000);

    add_prop(OBJ_I_VALUE, 450);
}
