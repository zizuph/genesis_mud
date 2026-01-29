
 /* Spell Level Necklace for the Windwalkers   */
 /* The number of rings surrounding the        */
 /* pendant is the level of spells this player */
 /* has obtained in the guild                  */

#pragma strict_types
#pragma save_binary
inherit "/std/armour";

#include <stdproperties.h>
#include <language.h>
#include <macros.h>
#include <tasks.h>
#include <ss_types.h>
#include <wa_types.h>
#include "defs.h"
#include WIND_HEADER

int
is_wind(object living)
{
    return living->query_guild_name_occ() == GUILD_NAME;
}

string
query_recover()
{
    return 0;
}

string
query_auto_load()
{
    return MASTER;
}

string
long_func()
{
    int rings;
    string desc, l_rings;

    rings = TP->query_windwalker_level();
    if (rings < 2)
        l_rings = "is a single ring";
    else
        l_rings = "are "+LANG_WNUM(rings)+" inter-twined rings";

    desc = "The necklace consists of a leather string with a spherical "+
        "pendant hanging from it.  Inside the pendant you see a small "+
        "whirlwind, spinning frantically.  Surrounding "+
        "the pendant " + l_rings + " made of sparkling diamond.  "+
        "\n";
    if (TP->query_skill(SS_WALKER_CHOSEN))
        desc += "You may use 'help windwalker' to get help.\n";

    return desc;
}

void
create_armour()
{
    set_name("necklace");
    add_name("WI_Necklace");
    set_short("glowing necklace");
    set_adj("glowing");
    set_long(long_func);
    add_prop(OBJ_I_VALUE, 0);
    add_prop(OBJ_I_WEIGHT, 0);
    add_prop(OBJ_I_VOLUME, 0);
    add_prop(OBJ_M_NO_STEAL, 1);
    add_prop(OBJ_M_NO_DROP,1);
    add_prop(OBJ_M_NO_SELL,1);
    set_ac(0);
    set_at(A_NECK);
    set_am( ({ 0, 0, 0}) );
}
