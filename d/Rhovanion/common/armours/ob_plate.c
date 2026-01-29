/*
 * ob_plate.c
 * Obsidian platemail
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
    set_name(({ "mail", "platemail" }));
    set_pname(({ "mails", "platemails" }));
    set_adj("black");
    add_adj("obsidian");
    set_short("black obsidian platemail");
    set_pshort("black obsidian platemails");
    set_long("@@query_long");
    set_ac(35);
    set_at(A_BODY);
    set_am( ({ 0, 0, 0 }) );
    update_prop_settings();
}

string query_long()
{

    /* Vampires shouldn't see their reflections. */

    if ( this_player()->query_guild_name_occ() == "Vampyr guild" )
    {
        return (break_string("You stare into the blackness of the obsidian "+
                "platemail but see only emptiness.\n",65));
    }
    return (break_string("You stare into the blackness of the obsidian "+
            "platemail and see your own reflection looking back at "+
            "you.\n",65));
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
