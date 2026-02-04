/*
 * spells/obj/clone
 *
 * This is a pretend clone of a vampire in the game.  It will
 * follow the caster around, and appear to all but those that are
 * quite astute to be able to determine that is is fake.
 *
 * Author: Novo 4/2008
 *
 *
*/

#include "../../guild.h"

inherit SPELLOBJ_DIR+"spell_obj";
inherit "/std/npc";
 
#include <tasks.h>     /* For difficulty and stat defines */
#include <ss_types.h>  /* For skill defines */
#include <stdproperties.h> /* For standard properties */
#include <macros.h> /* For macros */
#include <filter_funs.h> /* For easy filters */
#include <composite.h> /* Composie words */

#include "../../defs.h"

//Skills for seeing clues of this being an image.
#define TASK_SKILLS ({ SS_AWARENESS, SS_INT, SS_FORM_ILLUSION })

public void create_npc()
{
    set_name("image");
    
    add_name("_image_clone");
    
    set_race_name("image");
    
    set_short("faded blurry image");
    
    set_long("This appears to be a simple illusion.\n");

    set_spell_effect_desc("imitate other vampires");
    
    default_config_npc(10);
    
    set_skill(SS_AWARENESS,100);
    
    remove_prop(NPC_M_NO_ACCEPT_GIVE);
    
    add_prop(OBJ_S_WIZINFO,"This is a fake illusion simulating "+
    "a vampire elsewhere in the realms. It is only visible when "+
    "the image is not present.  Attacking it will dissipate it.\n");
    
}


public void fade()
{
    remove_object();    
}

/*
 * Description: This function is used by the efun parse_command()
 * Return the original's IDs if possible
 */
public string *
parse_command_id_list()         
{ 
    if (!objectp(effect_target) || !objectp(effect_caster))    
    {
        return ::parse_command_id_list();
    }
    return effect_target->parse_command_id_list();
}

/*
 * Description: This function is used by the efun parse_command()
 * Return the original's IDs if possible
 */
public string *
parse_command_plural_id_list() 
{ 
    if (!objectp(effect_target) || !objectp(effect_caster))    
    {
        return ::parse_command_plural_id_list();
    }
    return effect_target->parse_command_plural_id_list();
}

/*
 * Description: This function is used by the efun parse_command()
 * Return the original's IDs if possible
 */
public string *
parse_command_adjectiv_id_list() 
{
    if (!objectp(effect_target) || !objectp(effect_caster))    
    {
        return ::parse_command_adjectiv_id_list();
    }
    return effect_target->parse_command_adjectiv_id_list();
}


public int see_through_illusion()
{
    int i=0;
    
    object target=previous_object(i);
    
    while (objectp(target))
    {
        if (target->query_vampire())
            return 1;
    
        if (living(target) && target->query_wiz_level())
        {
            return 1;
        }
        
        if (living(target) && target->resolve_task(TASK_FORMIDABLE, 
                        TASK_SKILLS)>0)
        {
            return 1;
        }
        
        i--;        
        target=previous_object(i);
    }
    return 0;
}

public string query_race_name()
{
    if (!objectp(effect_target) || !objectp(effect_caster))    
    {
        set_alarm(0.1,0.0,fade);
        return ::short();
    }
    return effect_target->query_race_name();
}

public string short()
{
    if (!objectp(effect_target) || !objectp(effect_caster))    
    {
        set_alarm(0.1,0.0,fade);
        return ::short();
    }
    
    
    string short=effect_target->short();
    
    if (see_through_illusion())
    {
        short="illusion of "+short;
    }

    return short;
}






public object query_combat_object()
{
    if (!objectp(effect_target) || !objectp(effect_caster))    
    {
        return ::query_combat_object();
    }
    
    return effect_target->query_combat_object();
    
}

public string long()
{
    if (!objectp(effect_target) || !objectp(effect_caster))    
    {
        set_alarm(0.1,0.0,fade);
        return ::long();
    }

    string long=effect_target->long();
    
    if (see_through_illusion())
    {
        long+="Something does not look quite right here.\n";
    }
    
    return long;
}

public string plural_short()
{
    if (!objectp(effect_target) || !objectp(effect_caster))    
    {
        set_alarm(0.1,0.0,fade);
        return ::plural_short();
    }

    string short=effect_target->plural_short();
    
    if (see_through_illusion())
    {
        short="illusion of "+short;
    }

    return short;
}

public string query_mm_out()
{
    if (!objectp(effect_target) || !objectp(effect_caster))    
    {
        set_alarm(0.1,0.0,fade);
        return ::query_mm_out();
    }
    return effect_target->query_mm_out();
}    

public string query_m_out()
{
    if (!objectp(effect_target) || !objectp(effect_caster))    
    {
        set_alarm(0.1,0.0,fade);
        return ::query_m_out();
    }
    return effect_target->query_m_out();
}    

public string query_mm_in()
{
    if (!objectp(effect_target) || !objectp(effect_caster))    
    {
        set_alarm(0.1,0.0,fade);
        return ::query_mm_in();
    }
    return effect_target->query_mm_in();
}    

public string query_m_in()
{
    if (!objectp(effect_target) || !objectp(effect_caster))    
    {
        set_alarm(0.1,0.0,fade);
        return ::query_m_in();
    }
    return effect_target->query_m_in();
}    

public int query_skill(int skill)
{
    if (!objectp(effect_target) || !objectp(effect_caster))    
    {
        return ::query_skill(skill);
    }
    return effect_target->query_skill(skill);
}    

varargs public mixed query_armour(int which)
{
    if (!objectp(effect_target) || !objectp(effect_caster))    
    {
        return ::query_armour(which);
    }
    return effect_target->query_armour(which);
}

varargs public mixed query_weapon(int which)
{
    if (!objectp(effect_target) || !objectp(effect_caster))    
    {
        return ::query_weapon(which);
    }
    return effect_target->query_weapon(which);
}

public string query_met_name()
{
    if (!objectp(effect_target) || !objectp(effect_caster))    
    {
        return ::query_met_name();
    }
    return effect_target->query_met_name();
}

public string query_name()
{
    if (!objectp(effect_target) || !objectp(effect_caster))    
    {
        return ::query_name();
    }
    return effect_target->query_name();
}


public string query_nonmet_name()
{
    if (!objectp(effect_target) || !objectp(effect_caster))    
    {
        return ::query_nonmet_name();
    }
    return effect_target->query_nonmet_name();
}

public int query_stat(int stat)
{
    if (!objectp(effect_target) || !objectp(effect_caster))    
    {
        return ::query_stat(stat);
    }
    return effect_target->query_stat(stat);
}

public int query_fatigue()
{
    return query_max_fatigue();
}

public int check_seen(object for_obj)
{
    if (!objectp(effect_target))
    {
        set_alarm(0.1,0.0,fade);
        return 1;
    }
    if (environment(effect_target)==environment(TO))
    {
        return 0;
    }
    if (!interactive(effect_target))
    {
        return 0;
    }
    return ::check_seen(for_obj);
}

/* Disappear if attacked */
public attack_object(object ob)
{
    set_alarm(0.1,0.0,fade);
    ::attack_object(ob);
}

/* Disappear if attacked */
public void attacked_by(object ob)
{
    set_alarm(0.1,0.0,fade);
    ::attacked_by(ob);
}

/* Disappear if attacked */
varargs public mixed hit_me(int wcpen, int dt, object attacker, int 
            attack_id, int target_hitloc = -1)
{
    set_alarm(0.1,0.0,fade);
    ::hit_me(wcpen,dt,attacker,attack_id,target_hitloc);
}


public int
start()
{

    if (!::start())
    {
        effect_caster->catch_msg("You find the single image a sufficient "+
        "mental tax to maintain.\n");
        remove_spell_effect_object();
        return 0;
    }
    
    effect_caster->set_clone(this_object());

    effect_caster->catch_msg("Focusing on your kin, you visualize " +
    "the image of "+SHORT(effect_target)+" in every nuanced detail. "+
    "You close your eyes for a moment, and as you open them you feel "+
    "comfortable in knowing you will not appear alone.\n");

    effect_target->catch_msg(QCTNAME(effect_caster) + " studies you " +
    "closely, watching your gestures and motions with an intent to " +
    "imitate your presence. As "+PRO(effect_caster) + " closes " +
    POSS(effect_caster) + " eyes you know that your kin will be safe " +
    "with an illusion of you protecting " + OBJ(effect_caster) + ".\n");

    move(environment(effect_caster),1);

    return 1;
}


varargs public int
dispel_spell_effect(object dispeller)
{
	if (effect_caster && objectp(effect_caster))
	{
        effect_caster->catch_tell("You relax your mind as the illusion" +
        " dissipates.\n");
        effect_caster->set_clone(0);
        fade();
	}
    if (!effect_target[0] || !objectp(effect_target[0]) || 
            environment(effect_target[0])!=environment(TO))
    {
        tell_room(environment(TO),
        "The image fades to nothingness.\n", ({ }) );
    }
    return 1;
}

public void init_living()
{
    ::init_living();
    add_action(stop,"stop");
}
