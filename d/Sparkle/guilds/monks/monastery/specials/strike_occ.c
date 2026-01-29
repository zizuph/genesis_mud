/*
 * This is a modernization of the Monk special to
 * use the standard damage combat special library.
 *
 * Combat descriptions lifted from original Monk
 * special combat code by Arandir.
 *
 * Created by Ckrik, July 2015
 * 
 */
#pragma strict_types

#include "defs.h"

inherit STRIKE_BASE;

#include <ss_types.h>
#include <tasks.h>
#include <composite.h>
#include <macros.h>
#include <wa_types.h>
#include "/std/combat/combat.h"

public void config_ability()
{
    ::config_ability();
    set_combat_aid(M_STRIKE_OCC_AID);
    set_tohit(M_STRIKE_OCC_HIT);
    set_guild_stat_modifier(SS_OCCUP, 20, 100);
}

public void
report_resolve_ability(int pen, int dt, int damage)
{
    string name, logfile;
    
    if (interactive(this_player()))
    {
        name = capitalize(this_player()->query_real_name());
    }
    else
    {
        name = MASTER_OB(this_player());
    }

    logfile = implode(explode(MASTER_OB(this_object()), "/")[..-2], "/") + "/";
    logfile += short() + "_occ_damage";
    logfile = implode(explode(logfile, " "), "");
    
    setuid();
    seteuid(getuid());
    
    send_debug_message(short(), 
                    name + " hits with Pen of " + pen + ", "
                    + "Damage of " + damage,
                       logfile);  
}

