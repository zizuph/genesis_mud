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
    // Since layman only get to train up to 60 levels of
    // strike, we adjust the skill weight to 100/60 = 1.67
    // so that the correct combat aid is applied.
    set_skills(({ SKILL_WEIGHT, 167, M_SKILL_STRIKE }) );
    
    set_combat_aid(M_STRIKE_LAY_AID);
    set_tohit(M_STRIKE_LAY_HIT);
    set_guild_stat_modifier(SS_LAYMAN, 20, 100);
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
    logfile += short() + "_lay_damage";
    logfile = implode(explode(logfile, " "), "");
    
    setuid();
    seteuid(getuid());
    
    send_debug_message(short(), 
                    name + " hits with Pen of " + pen + ", "
                    + "Damage of " + damage,
                       logfile);  
}

