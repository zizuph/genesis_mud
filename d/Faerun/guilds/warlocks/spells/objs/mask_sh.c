/*
 * Support Shadow for the Warlock Mask of Many Faces spell
 *
 * Originally created by Petros, modified by Arman (8/2016)
 * and refitted to be used for the warlocks, Nerull 2017
 * 
 * Updated to inherit from /d/Genesis/specials/new/magic/
 * Arman (AoB) December 2021
 */

#include <stdproperties.h>
#include <ss_types.h>
#include <macros.h>
#include <wa_types.h>
#include <files.h>
#include "../../guild.h"

#ifndef LIVE_I_NEVERKNOWN     
#define LIVE_I_NEVERKNOWN     ("_live_i_neverknown")
#endif

#include "/d/Genesis/specials/local.h"
inherit SPELL_DIR + "objs/propchange_base_sh";

int neverknown_boost;
string adj1 = 0;
string adj2 = 0;
string adjes;


string * s_adj1x = ({"blue-bearded",
                  "brown-eyed",
                  "noble"});
                  
string * s_adj2x = ({"barrel-chested",
                  "young",
                  "crook-nosed"});

                  
string
s_adj1()
{
    int i;
    i = random(9);
    
    switch (i)
    {
        case 0:
        return "handsome";
        break;
        case 1:
        return "bow-legged";
        break;
        case 2:
        return "brown-bearded";
        break;
        case 3:
        return "clean-shaved";
        break;
        case 4:
        return "determined";
        break;
        case 5:
        return "green-eyed";
        break;
        case 6:
        return "adolescent";
        break;
        case 7:
        return "ageless";
        break;
        case 8:
        return "slant-eyed";
        break;
        default:
        return "crook-nosed";
        break;
    }
}


string
s_adj2()
{
    int i;
    i = random(9);
    
    switch (i)
    {
        case 0:
        return "blue-eyed";
        break;
        case 1:
        return "muscular";
        break;
        case 2:
        return "raven-haired";
        break;
        case 3:
        return "green-eyed";
        break;
        case 4:
        return "long-bearded";
        break;
        case 5:
        return "blond-haired";
        break;
        case 6:
        return "big";
        break;
        case 7:
        return "mysterious";
        break;
        case 8:
        return "pouty-lipped";
        break;
        default:
        return "ancient";
        break;
    }
}
         
         
/*
 * Function:    initialize_shadow
 * Description: Called after first cloned. Should do all the initialization
 *              effects for this particular shadow.
 */
public void
initialize_shadow(object spell_object, mapping spell_input)
{
    ::initialize_shadow(spell_object, spell_input);
    spell_object->set_spell_effect_desc("Mask of Many Faces");
    spell_object->set_short("mask of many faces spell object");

    int power = spell_object->query_spell_effect_power();
    neverknown_boost = max(1, min(100, power / 3));
}


/* 
 * Function:    query_prop
 * Description: This is the primary function that you should override to
 *              implement the propchange shadow. Make sure to return
 *              the shadow_who->query_prop(prop) result if you don't
 *              want to handle that particular prop.
 */
public mixed
query_prop(string prop)
{
    mixed result = shadow_who->query_prop(prop);
    
    if (adj1 == 0)
    {
        adj1 = s_adj1();
    }
       
    if (adj2 == 0)
    {
        adj2 = s_adj2();
    }
    
    if (prop != LIVE_I_NEVERKNOWN)
    {
        return result;
    }
    
    if (intp(result))
    {
        return max(1, result + neverknown_boost);
    }
    else 
    {
        return 1;
    }
}


/*
 * Function:    hook_spell_effect_started
 * Description: Override this to customize the message when this spell effect
 *              is added to th target.
 */
public void
hook_spell_effect_started(object spell_object)
{
    object target = spell_object->query_effect_target();
    
    

    if (objectp(target))
    {
        object enemy;
        
        enemy = target->query_attack();
        
        //if (!present(enemy, environment(target)))
        //{
            //enemy->stop_fight(target);
            //target->stop_fight(enemy);     
        //}
        
        target->catch_tell("Your appearance magically changes!\n");

        //tell_room(environment(target), QCTNAME(target) 
        //+ " suddenly changes appearance!\n",
        //({ target }));
    }
}


/*
 * Function:    hook_spell_effect_ended
 * Description: Override this to customize the message when this spell effect
 *              is dispelled.
 */
public void
hook_spell_effect_ended(object spell_object)
{
    object target = spell_object->query_effect_target();

    if (objectp(target))
    {
        target->catch_tell("You return to your normal "
        +"appearance.\n");
        
        tell_room(environment(target), QCTNAME(target) 
        + " returns to "+target->query_possessive()
        +" normal appearance.\n", ({ target }));
    }

}


/*
* Function:    hook_spell_effect_warn_fading
* Description: Override this to customize the message for when
*              the effect has only a minute left.
*/
public void
hook_spell_effect_warn_fading(object spell_object)
{
    object target = spell_object->query_effect_target();

    if (objectp(target))
    {
        target->catch_tell("You sense your Urchem spell "
        +"begins to fade.\n");
    }
}


/*
* Function:    hook_spell_effect_not_maintained
* Description: Override this to describe the effect when the caster
*              cannot maintain the effect.
*/
public void
hook_spell_effect_not_maintained(object spell_object)
{
    object caster = spell_object->query_effect_caster();

    
    if (objectp(caster))
    {
        caster->catch_tell("You are mentally unable to maintain "
        + "the Urchem spell.\n");
    }
}


private mixed
query_list(mixed list, int arg)
{
    if (!pointerp(list))
        return 0;
    if (!arg && sizeof(list))
        return list[0];
    else
        return list + ({});
}


varargs public mixed
query_adj(int arg) 
{
    return query_list(({adj1, adj2}), arg);
}


public string *
query_adjs() 
{ 
    return query_list(({adj1, adj2}), 1);
}


public int
adjectiv_id(string str)
{
    return (member_array(str, ({adj1, adj2})) >= 0);
}


public string *
parse_command_adjectiv_id_list()
{
    return ({adj1, adj2}) + ({ query_shadow_who()->query_gender_string() });
}


