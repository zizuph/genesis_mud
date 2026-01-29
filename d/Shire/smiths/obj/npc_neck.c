/* NPC necklace - guild item for the smiths guild */

#pragma save_binary;

inherit "/std/armour";
#include "/sys/wa_types.h"
#include "/sys/stdproperties.h"
#include "smiths.h"

void
create_armour()
{
    set_name("necklace");
    set_long("A nice necklace for the ones who work are the Smiths Guild.\n");

    set_ac(0);
    set_am(({ 0, 0, 0 }));

    set_at(A_NECK);

    add_prop(OBJ_I_VALUE, 0);
    add_prop(OBJ_I_VOLUME, 20);
    add_prop(OBJ_I_WEIGHT, 50);
    add_prop(OBJ_I_NO_DROP,1);
}
