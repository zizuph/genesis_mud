/*
 * ob_shield.c
 * An obsidian shield
 * Written by Trenix@Genesis, 8-15-93
 *
 */

#pragma save_binary

inherit "/std/armour";
inherit "/lib/keep";
 
#include <stdproperties.h>
#include <macros.h>
#include <formulas.h>

create_armour()
{
    set_name(({ "shield" }));
    set_pname(({ "shields" }));
    set_adj("black");
    add_adj("obsidian");
    set_short("black obsidian shield");
    set_pshort("black obsidian shields");
    set_long("@@query_long");
    set_ac(35);
    set_at(A_SHIELD);
    set_am( ({ 0, 0, 0 }) );
    update_prop_settings();
}

string query_long()
{
    return (break_string("You stare deep into the obsidian shield "+
            "but fail to focus your eyes on the surface. All you "+
            "see is continuing darkness within.\n",65));
}

init()
{
    ::init();
}

query_recover()
{
    return MASTER+":"+query_arm_recover();
}

init_recover(str)
{
    init_arm_recover(str);
}

/* EOF */
