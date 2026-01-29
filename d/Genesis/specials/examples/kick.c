#pragma strict_types

#include "../defs.h"

inherit DAMAGE_LIB;

#include <ss_types.h>
#include <tasks.h>
#include <composite.h>
#include <macros.h>
#include <wa_types.h>
#include "/std/combat/combat.h"



public void config_ability()
{
    ::config_ability();
    set_combat_aid(200);
    set_tohit(75);
    set_stats(({ TS_STR }) );
    set_skills(({ SS_UNARM_COMBAT }) );
    set_ability_time(10);
    set_dt(W_BLUDGEON);
    set_ability_name("kick");
}


public void special_did_hit(int aid, string hdesc, int hid, 
                int phurt, object enemy, int dt,int phit, 
                int dam,object * items)
{
    if (dam<=0)
    {
        this_player()->catch_msg
        ("You try to kick the "+hdesc+" of "+QTNAME(enemy) +
        " but miss.\n");
        
        this_player()->tell_watcher(
        QCTNAME(this_player())+" tries to kick the "+hdesc+" of "+
        QTNAME(enemy) + " but misses.\n", ({ enemy }) );
        
        enemy->catch_msg(QTNAME(this_player())+" tries to kick you "+
        "in the "+hdesc+ " but you avoid the blow.\n");
        return;
    }
    
    string dtype;
    
    switch (phurt)
    {
        case 0..4:
            dtype="barely ";
            break;
        case 5..9:
            dtype="";
            break;
        case 10..19:
            dtype="soundly ";
            break;
        case 20..50:
            dtype="thoroughly ";
            break;
        default:
            dtype="devastatingly ";
    }

    this_player()->catch_msg
    ("You kick the "+hdesc+" of "+QTNAME(enemy) + ", "+ dtype +
      "injuring " +enemy->query_objective()+".\n");

    this_player()->tell_watcher(QCTNAME(this_player())+" kicks the "+
        hdesc+" of "+ QTNAME(enemy) + ", "+ dtype +   "injuring " + 
        enemy->query_objective()+".\n", ({ enemy }));

    enemy->catch_msg(QCTNAME(this_player())+" kicks your "+hdesc +
        ", "+ dtype + "injuring you.\n");

    
    if (enemy->query_hp()<=0)
    {
        enemy->do_die(this_player());
    }
    
}

