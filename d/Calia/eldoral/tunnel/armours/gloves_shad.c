/*   gloves_shad.c
 *
 * The shadow for the snake-skin gloves, this
 * is where the actual damage take place by 
 * masking cr_did_hit().
 * 
 * Baldacin@Genesis, Sep 2003
 *
 * Updates:
 *   Fixed the use of say and write, which was causing runtime errors
 *   because this_player() was incorrect - Petros July 2008
 */
 
inherit "/std/shadow";

#include "snake_gloves.h"
#include <macros.h>
#include <wa_types.h>
#include <ss_types.h>

/*
 * Function name: got_gloves_shadow
 * Description  : Always return true, used to check
 *                if a player got the shadow.
 */
public int
got_gloves_shadow()
{
    return 1;
}

/*
 * Function name: start_gloves
 * Description  : Shadows the player with the shadow.
 * Arguments    : object me - The player to shadow.
 */	
public void
start_gloves(object me)
{ 
    if (!objectp(me) || !shadow_me(me))
    {
        return;
    }
    
    me->catch_msg(
      "As you wear the snake-skin gloves, a sense of ease and self-"+
      "control falls over you and you feel very secure and focused.\n");
    tell_room(environment(me),
      "As "+QTNAME(me)+" wears the snake-skin gloves, a sense "+
      "of ease and self-control falls over "+HIM(me)+" and "+
      HE(me)+" looks very secure and focused.\n",
              ({ me }), me);
}

/*
 * Function name: stop_gloves
 * Description  : Removes the shadow.
 */
public void
stop_gloves()
{
    if (interactive(shadow_who))
    {
        shadow_who->catch_msg(
            "As you remove the snake-skin gloves, the sense of ease and self-"+
            "control fades away from you and you feel less secure and focused.\n");
        tell_room(environment(shadow_who),
            "As "+QTNAME(shadow_who)+" removes the snake-skin gloves, the sense "+
            "of ease and self-control fades away from "+HIM(shadow_who)+" and "+
            HE(shadow_who)+" looks less secure and focused.\n",
                  ({ shadow_who }), shadow_who);
    }
    remove_shadow();
}

public varargs int
cr_did_hit(int aid, string hdesc, int phurt, object enemy,
           int dt, int phit, int dam, int hid)
{
    mixed* hitres;
    int pdam, damage = 1;
    string attack_desc, damage_desc, other_damage_desc;

    if (shadow_who->query_weapon(aid))
    {
        return shadow_who->cr_did_hit(aid, hdesc, phurt, enemy, dt, phit, dam, hid);        
    }

    if (phurt <= 0)
    {
        return shadow_who->cr_did_hit(aid, hdesc, phurt, enemy, dt, phit, dam, hid);
    }
   
    if (aid & W_BOTH)
    {    	 
        damage = (dam * 3 / 2) + random(dam * 3 / 4);
        attack_desc = (shadow_who->query_combat_object())->cb_attack_desc(aid);
        hitres = enemy->hit_me(damage, dt, shadow_who, aid, hid);
        pdam = (100 * dam) / enemy->query_max_hp();
        shadow_who->add_panic(-3 - (phurt / 5));        

        switch (pdam)
        {
            case 0..2:
              damage_desc = "lightly bruise";
              other_damage_desc = "lightly bruises";
            break;

            case 3..5:
              damage_desc = "batter";
              other_damage_desc = "batters";
            break;

            case 6..9:
              damage_desc = "pound";
              other_damage_desc = "pounds";
            break;

            case 10..19:
              damage_desc = "beat";
              other_damage_desc = "beats";
            break;

            case 20..39:
              damage_desc = "seriously beat";
              other_damage_desc = "seriously beats";
            break;

            case 40..59:
              damage_desc = "soundly beat";
              other_damage_desc = "soundly beats";
            break;

            case 60..90:
              damage_desc = "hammer";
              other_damage_desc = "hammers";
            break;

            default:
              damage_desc = "brutally pummel";
              other_damage_desc = "brutally pummels";
            break;
        }        

        /* Wearer */
        if (interactive(shadow_who))
        {
           shadow_who->catch_msg("You "+damage_desc+" "+QTPNAME(enemy)+
               " "+hdesc+" with your snake-skin armoured "+attack_desc+".\n");
        }

        /* Enemy */
        if (interactive(enemy))
        {
           enemy->catch_msg(QCTNAME(shadow_who)+" "+other_damage_desc+
               " your "+hdesc+" with "+HIS(shadow_who)+" snake-skin armoured "+
               attack_desc+".\n");
        }
    
        /* Watchers */
        shadow_who->tell_watcher(QCTNAME(shadow_who)+" "+other_damage_desc+
            " "+QTPNAME(enemy)+" "+hdesc+" with "+HIS(shadow_who)+" snake-skin "+
            "armoured "+attack_desc+".\n", ({enemy}));
        return 1;
    }
}
