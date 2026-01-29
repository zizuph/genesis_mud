/* This s a magic necklace that belongs to Van Helsing. */
/* coded by Calonderiel 930906                          */

#pragma save_binary

inherit "/std/armour";

#include "/sys/wa_types.h"
#include <stdproperties.h>
#include <macros.h>
#include "/d/Roke/common/defs.h"

create_armour()
{
    set_name("necklace");
    set_adj("silvery");
    set_short("silvery necklace");
    set_long("A broad band woven of a silvery material.\n"); 

    set_default_armour(41, A_NECK, ({-1,1,0}), 0);
    add_prop(MAGIC_AM_MAGIC,({ 20, "enchantment" }));
    add_prop(MAGIC_AM_ID_INFO,({ "The necklace seems to be magical.\n", 1,
                                 "This necklace has been enchanted to"+
                                 " give better protection.\n",15 }));

    add_prop(OBJ_I_WEIGHT,300);
    add_prop(OBJ_I_VOLUME,145);
}

query_recover()
{
    return MASTER + ":" + query_arm_recover();
}

init_recover(arg)
{
    init_arm_recover(arg);
}


