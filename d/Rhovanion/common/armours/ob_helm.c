/*
 * ob_helm.c
 * An obsidian helmet
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
    set_name(({ "helmet" }));
    set_pname(({ "helmets" }));
    set_adj("black");
    add_adj("obsidian");
    set_short("black obsidian helmet");
    set_pshort("black obsidian helmets");
    set_long("@@query_long");
    set_ac(30);
    set_at(A_HEAD);
    set_am( ({ 0, 0, 0 }) );
    update_prop_settings();
}

string query_long()
{
    return (break_string("You look into the obsidian helmet only to find "+
            "total darkness.\n",65));
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
