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

    set_spell_element(SS_ELEMENT_FIRE, 50);
    set_spell_form(SS_FORM_ILLUSION, 50);
    set_spell_task(TASK_DIFFICULT);

    set_ability_stats(STAT_WEIGHTING);
    set_spell_class(SPELL_CLASS_3);

    set_spell_target(spell_target_caster);

    // Set the effect object filename
    set_shadow_filename(BF_GUILD_DIR + "spells/objs/polymorph_sh.c");
}


public string *
query_propchange_ingredients(object caster)
{
    return ({ "_polymorph_charge" });
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
    
	if (player->query_guild_level_lay() >= GIFT_2)
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
    
    caster_message = "You invoke the power of Kossuth!\n";
    
    watcher_message = QCTNAME(caster)
    +" invokes the power of Kossuth!\n";

    caster->catch_tell(caster_message);
    tell_room(environment(caster), watcher_message, ({ caster }), caster);

    setuid();
    seteuid(getuid());
}


public void
hook_already_has_spell_object(object caster, object target)
{
    write("You are already maintaining the Polymorh spell.\n");
}


