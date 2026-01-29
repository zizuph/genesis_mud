/* Guild Item for Orc Racial Guild
 * Finwe, Nov 2000
 */
#pragma save_binary
#pragma strict_types

inherit "/std/object";

#include <macros.h>
#include <stdproperties.h>
#include <composite.h>
#include "/d/Shire/sys/defs.h"
#include "/d/Shire/guild/orcr/orcr_guild.h"

int armband;
    
void
create_object()
{
    set_name("armband");
    add_adj(({"dirty","ragged"}));
    add_name("_orc_race_guild_armband_");
    set_short("dirty, ragged armband");
    set_long("This is a strip of coarse material that orcs use " +
        "to tie around their arms and identify themselves. The " +
        "armband is dirty and stained with dried blood. The " +
        "ends are ragged and frayed.\n");

    add_prop(OBJ_I_WEIGHT,  20);
    add_prop(OBJ_I_VOLUME,   5);
    remove_prop(OBJ_I_VALUE);
    add_prop(OBJ_M_NO_DROP,  1);
    add_prop(OBJ_M_NO_STEAL, 1);
    armband = 0;
}


/*
void
init()
{
    ::init();
    add_action(armband_on, "tie");
    add_action(armband_on, "untie");
}
*/
