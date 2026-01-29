/* bronze crozier        /d/Avenir/common/city/obj/wield/crozier_sh.c
 * creator(s):           Zizuph, August 2021
 * purpose:              To be held by the dej-minha.
 * notes:                
 *                       This provides the unarmed combat messaging, where
 *                       the crozier causes extra unarmed foot attacks to take
 *                       place.  It modifies the attack use as well.  The amount
 *                       of attack use is provided by the weapon (as there are
 *                       both a magic and non-magic version).
 *     Associated files: /d/Avenir/common/city/obj/wep/crozier.c
 *                       Weapon which involves this shadow.
 */
inherit "/std/shadow";

#include "/std/combat/combat.h"
#include <macros.h>
#include <ss_types.h>
#include <wa_types.h>


#ifndef SCROLLING_LOG
#define SCROLLING_LOG(file, entry)   ((file_size(file) > 90000) ? \
    (rm(file) && write_file(file, ctime(time()) + ": " + entry + "\n")) : \
    (write_file(file, ctime(time()) + ": " + entry + "\n")))
#endif

#define CROZIER_LOG   "/d/Avenir/log/crozier"


object player;
object crozier;
int use_bonus;

int last_time = 0;
int last_attackuse = 0;


public void remove_crozier_shadow()
{
    object combat = player->query_combat_object();
    if (objectp(combat))
    {
        combat->cb_set_attackuse(combat->cb_query_attackuse() - use_bonus);
    }
    remove_shadow();
}

public varargs int
cr_did_hit(int aid, string hdesc, int phurt, object enemy, int dt,
           int phit, int dam, int hid)
{

    // Perform sanity checks that the crozier is still being used.
    if (!objectp(crozier))
    {
        SCROLLING_LOG(CROZIER_LOG,
          sprintf("%s had crozier shadow but crozier no longer exists",
            shadow_who->query_real_name()));
        set_alarm(0.1, 0.0, remove_crozier_shadow);
    }
    else if (environment(crozier) != player)
    {
        SCROLLING_LOG(CROZIER_LOG,
          sprintf("%s had crozier shadow but crozier not in inventory",
            shadow_who->query_real_name()));
        set_alarm(0.1, 0.0, remove_crozier_shadow);
    }
    else if (!crozier->query_held())
    {
        SCROLLING_LOG(CROZIER_LOG,
          sprintf("%s had crozier shadow but crozier not held",
            shadow_who->query_real_name()));
        set_alarm(0.1, 0.0, remove_crozier_shadow);
    }
    else if (crozier->query_holder() != player)
    {
        SCROLLING_LOG(CROZIER_LOG,
          sprintf("%s had crozier shadow but crozier held by %s",
            shadow_who->query_real_name(),
            crozier->query_holder()->query_real_name()));
        set_alarm(0.1, 0.0, remove_crozier_shadow);
    }

    if (aid != W_FOOTR && aid != W_FOOTL)
    {
        return shadow_who->cr_did_hit(aid, hdesc, phurt, enemy, dt,
          phit, dam, hid);
    }

    // Show how the tool is being used to elevate their feet.
    object combat = player->query_combat_object();
    if (!objectp(combat)) 
    {
        return shadow_who->cr_did_hit(aid, hdesc, phurt, enemy, dt,
          phit, dam, hid);
    }
    
    int current_attackuse = combat->cb_query_attackuse();
    if (current_attackuse != last_attackuse)
    {
        SCROLLING_LOG(CROZIER_LOG,
          sprintf("%s had unexpected attackuse change from %d to %d",
            shadow_who->query_real_name(), last_attackuse, current_attackuse));
        
        last_attackuse = current_attackuse;
    }
    
    if (time() - last_time < 1)
    {
        switch (random(3))
        {
            case 0:
            player->catch_msg("You vault into the air using your " +
                crozier->short() + ", creating an opportunity to kick at " +
                QTNAME(enemy) + ".\n");
            enemy->catch_msg(QCTNAME(player) + " uses " + 
                player->query_possessive() + " " +
                crozier->short() + " to vault into the air in your " +
                "direction.\n");
            player->tell_watcher(QCTNAME(player) + " uses " + 
                player->query_possessive() + 
                " " + crozier->short() + " to vault into the air towards " +
                QTNAME(enemy) + ".\n", ({ enemy }));
            break;
            case 1:
            player->catch_msg("You lean your weight into the " 
                + crozier->short() + ", enabling a swift kick at " +
                QTNAME(enemy) + ".\n");
            enemy->catch_msg(QCTNAME(player) + " leans back against " + 
                player->query_possessive() + " " +
                crozier->short() + " and stretches to kick at you.\n");
            player->tell_watcher(QCTNAME(player) + " leans back against " + 
                player->query_possessive() + 
                " " + crozier->short() + " and stretches to kick at " +
                QTNAME(enemy) + ".\n", ({ enemy }));
            break;
            default:
            player->catch_msg("You take a quick hop forwards, " +
                "launched higher with your " +
                crozier->short() + ", kicking out at " +
                QTNAME(enemy) + ".\n");
            enemy->catch_msg(QCTNAME(player) + " takes a quick hop with " + 
                player->query_possessive() + " " +
                crozier->short() + " and kicks out at you.\n");
            player->tell_watcher(QCTNAME(player) + " takes a quick hop " +
                "with " + player->query_possessive() + 
                " " + crozier->short() + " and kicks at " +
                QTNAME(enemy) + ".\n", ({ enemy }));
            break;
        }
    }
    last_time = time();
    return shadow_who->cr_did_hit(aid, hdesc, phurt, enemy, dt,
        phit, dam, hid);
}

public int set_skill(int skill, int val)
{
    int result;
    if (skill == SS_2H_COMBAT)
    {
        // Changes to two-handed skill will override the attackuse.
        // Catch these and revert it, so our bonus remains.
        int current_attackuse;
        object combat = player->query_combat_object();
        if (objectp(combat))
        {
            current_attackuse = combat->cb_query_attackuse();
        }
        result = shadow_who->set_skill(skill, val);
        if (objectp(combat))
        {
            combat->cb_set_attackuse(current_attackuse);
        }
        return result;
    }
    return shadow_who->set_skill(skill, val);
}

public void set_skill_extra(int skill, int val)
{
    int result;
    if (skill == SS_2H_COMBAT)
    {
        // Changes to two-handed skill will override the attackuse.
        // Catch these and revert it, so our bonus remains.
        int current_attackuse;
        object combat = player->query_combat_object();
        if (objectp(combat))
        {
            current_attackuse = combat->cb_query_attackuse();
        }
        shadow_who->set_skill_extra(skill, val);
        if (objectp(combat))
        {
            combat->cb_set_attackuse(current_attackuse);
        }
        return;
    }
    shadow_who->set_skill_extra(skill, val);
}

public void remove_skill(int skill)
{
    int result;
    if (skill == SS_2H_COMBAT)
    {
        // Changes to two-handed skill will override the attackuse.
        // Catch these and revert it, so our bonus remains.
        int current_attackuse;
        object combat = player->query_combat_object();
        if (objectp(combat))
        {
            current_attackuse = combat->cb_query_attackuse();
        }
        shadow_who->remove_skill(skill);
        if (objectp(combat))
        {
            combat->cb_set_attackuse(current_attackuse);
        }
        return;
    }
    shadow_who->remove_skill(skill);
}

public void add_crozier_shadow(object recipient, object weapon, int bonus)
{
    player = recipient;
    use_bonus = bonus;
    crozier = weapon;
    object combat = player->query_combat_object();
    if (objectp(combat))
    {
        combat->cb_set_attackuse(bonus + combat->cb_query_attackuse());
        last_attackuse = combat->cb_query_attackuse();
    }
    else
    {
        // No combat object, so we cannot add a value.
        use_bonus = 0;
    }
    shadow_me(recipient);
}
