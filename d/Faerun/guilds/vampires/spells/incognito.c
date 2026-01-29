/*
 * Incognito - alter appearance
 * By Nerull, June 2021
 */
#include "/d/Genesis/specials/local.h"
inherit SPELL_DIR + "propchange_base";

#include <macros.h>
#include <tasks.h>
#include <stdproperties.h>
#include <flags.h>
#include <ss_types.h>
#include <files.h>
#include "../guild.h"


/*
 * Function:    config_propchange_spell
 * Description: Config function for propchange spell. Redefine this in your
 *              own propchange spells to override the defaults.
 */
public void
config_propchange_spell()
{
    set_spell_name("incognito");
    set_spell_desc(" - Change your appearance to "
    +"something else");

    set_spell_element(SS_ELEMENT_WATER, 50);
    set_spell_form(SS_FORM_ILLUSION, 50);
    set_spell_task(TASK_DIFFICULT);

    set_ability_stats(STAT_WEIGHTING);
    set_spell_class(SPELL_CLASS_3);

    set_spell_target(spell_target_caster);

    // Set the effect object filename
    set_shadow_filename(VAMPIRES_GUILD_DIR + "spells/objs/incognito_sh.c");
}


public string *
query_propchange_ingredients(object caster)
{
    return ({ });
}


/*
* Function:    query_spell_can_be_learned
* Description: Place restrictions on whether this spell can be used
*              by the guild member.
*/
public int
query_spell_can_be_learned(object player)
{
    setuid();
    seteuid(getuid());

    if (!objectp(player))
    {
        return 0;
    }

    if (player->query_npc())
    {
        // npcs can always learn the spell.
        return 1;
    }
    
    if (VAMPIRES_MAPPINGS->query_vampire_ability_occ_1(this_player()->query_name()) > 0)
    {
         return 1;
    }

    return 0;
}


public int
check_valid_action(object caster, mixed * targets, string arg, 
int execute = 0)
{
    if (!::check_valid_action(caster, targets, arg, execute))
    {
        return 0;
    }
    
    if (!present("_vampire_powers_unlock_ob", caster))
    {
        caster->catch_tell("You are too weak! You "
        +"need to rise from a coffin in order to use this gift.\n");
        
        return 0;
    }
    
    int check = VAMPIRES_MAPPINGS->query_thirst_gauge(caster->query_real_name());
    
    if (check < ABILITY_THRESHOLD)
    {
        caster->catch_tell("The thirst is too overwhelming for you to "
        +"concentrate. Aquire more blood!\n");
        
        return 0;
    }
    
    if (caster->query_ethereal() == 1)
    {
        caster->catch_tell("You are in the ethereal realm. This spell "
        +"doesn't work there.\n");
        
        return 0;
    }

    return 1;
}


public void
hook_describe_cast_propchange(object caster, object* targets)
{
    caster->tell_watcher(QCTNAME(caster) 
    + " changes appearance!\n", ({}) );
}


/*
* Function name: concentrate_msg
* Description:   Give messages indicating that spell concentration has begun
* Arguments:     1. (object)   The caster
*                2. (mixed *) The targets
*                3. (string)   The arguments passed to the "cast" command
*/
public void
concentrate_msg(object caster, mixed * targets, string arg)
{
    string caster_message, watcher_message;
    
    // Blood-drain
    int bloodamount = VAMPIRES_MAPPINGS->query_thirst_gauge(caster->query_real_name());     
    bloodamount = bloodamount - INCOGNITO_COST;   
    VAMPIRES_MAPPINGS->set_thirst_gauge(caster->query_name(), bloodamount);

    caster_message = "You begin to concentrate momentarily on the "
    +"virtues of blood and the maleability of flesh.\n";
    
    watcher_message = QCTNAME(caster)
    +" concentrates on something.\n";

    caster->catch_tell(caster_message);
    tell_room(environment(caster), watcher_message, ({ caster }), caster);

    setuid();
    seteuid(getuid());
}


public void
hook_already_has_spell_object(object caster, object target)
{
    write("You are already maintaining the Incognito spell.\n");
}


