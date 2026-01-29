/*
 * Summoning Object for the Choma (summoning) Spell of the Elementalists 
 * of Calia
 *
 * This is a derivation of the spell object for the standard Genesis 
 * Magic System Summon spell. It creates a summoned npc. This spell 
 * object will be a maintained spell effect, so will drain the caster's 
 * mana while it is in effect.
 *
 * Created by Petros, February 2013
 */

#pragma strict_types
#pragma save_binary

#include <stdproperties.h>
#include <ss_types.h>
#include <composite.h>
#include <macros.h>

#include "defs.h"

inherit "/d/Genesis/specials/std/spells/obj/summon_obj";

/*
 * Function:    create_spell_object
 * Description: Override this to customize properties for the spell object
 */
public void 
create_spell_object()
{
    set_name("_choma_summoning_object_");
    set_short("choma spell object");    
    set_long("This is the choma elemental summoning spell's object. It exists "
        + "to keep track of the caster's maintained effects.\n");

    add_prop(OBJ_S_WIZINFO, "This is a spell object " +
                            "created by the summon spell.\n");
    set_spell_effect_desc("summoned elemental");
    
    set_dispel_time(7200); // by default, a summoned npc can last for up to 
                           // 2 hours
}

/*
 * Function:    customize_summoned_creature
 * Description: Called after the creature has been cloned and summoned, this
 *              allows inheriting spells to customize the summoned creature.
 */
public void
customize_summoned_object(object summon_object, mapping input)
{
    // We set the elemental type here
    summon_object->set_elemental_type(input["element"]);
    summon_object->set_summoner(query_effect_caster());
}

/*
 * Function:    hook_spell_effect_started
 * Description: Override this to customize the message when this spell effect
 *              is added to the target.
 */
public void
hook_spell_effect_started()
{
    object caster = query_effect_caster();
    string caster_message, watcher_message = "";
    switch (summon_object->query_elemental_type())
    {
    case "fire":
        caster_message = "You complete the prayer and sense that "
            + "Lord Pyros has heard your request. ";
        watcher_message = "A wave of heat suddenly blows into the area, "
            + "oppressing and fearful. " + QCTNAME(summon_object) + " forms "
            + "from a massive swirl of smoke and ash.\n";
        break;
        
    case "earth":
        caster_message = "You complete the prayer and sense that "
            + "Lady Gu has heard your request. ";
        watcher_message = "The earth shakes and groans, and suddenly it parts "
            + "as " + QTNAME(summon_object) + " forms from the clay.\n";
        break;
        
    case "water":
        caster_message = "You complete the prayer and sense that "
            + "Lord Diabrecho has heard your request. ";
        watcher_message = "A small puddle begins to grow on the ground, "
            + "gaining volume quickly. " + QCTNAME(summon_object) 
            + " forms from the water.\n";
        break;
        
    case "air":
        caster_message = "You complete the prayer and sense that "
            + "Lady Aeria has heard your request. ";
        watcher_message = "A great wind arises, blowing into the area and "
            + "forming a swirling zephyr. " + QCTNAME(summon_object) 
            + " forms from the winds.\n";
        break;
        
    case "life":
    	caster_message = "You complete the prayer and sense that "
            + "Psuchae has heard your request. ";
        watcher_message = "Swirling masses begin to form in the shadows "
            + "around you. " + QCTNAME(summon_object) + " forms from the "
            + "masses.\n";
        break;
        
    }
    caster->catch_msg(caster_message);
    tell_room(environment(caster), watcher_message);
}

/*
 * Function:    hook_spell_effect_ended
 * Description: Override this to customize the message when this spell effect
 *              is dispelled.
 */
public void
hook_spell_effect_ended()
{
    object caster = query_effect_caster();
    if (!objectp(caster))
    {
        return;
    }
    
    if (!objectp(summon_object))
    {
        caster->catch_tell("You sense that the servant of the Elementals "
            + "has returned to its realm.\n");
        return;
    }
    
    // Force the summoned object to drop everything in the room that
    // the caster is in.
    summon_object->move(environment(caster));
    summon_object->command("drop all");
    
    caster->catch_msg("Your sense the summoned servant of the Elementals, " 
        + QTNAME(summon_object) + ", return to its native realm.\n");
    tell_room(environment(summon_object), QCTNAME(summon_object)
        + " disappears.\n", ({ caster }));
}

/*
 * Function:    hook_spell_effect_warn_fading
 * Description: Override this to customize the message for when
 *              the effect has only a minute left.
 */
public void
hook_spell_effect_warn_fading()
{
    object caster = query_effect_caster();
    if (!objectp(caster) || !objectp(summon_object))
    {
        return;
    }
    
    caster->catch_tell("You sense that the summoned servant of the "
        + "Elementals, " + COMPOSITE_LIVE(summon_object) 
        + ", begins to yearn for its native realm.\n");    
}

/* 
 * Function:    hook_spell_effect_not_maintained
 * Description: Override this to describe the effect when the caster
 *              cannot maintain the effect.
 */
public void
hook_spell_effect_not_maintained()
{
    object caster = query_effect_caster();
    
    if (objectp(caster) && objectp(summon_object))
    {
        caster->catch_msg("You are mentally unable to maintain "
            + "the gift of choma, " + QTNAME(summon_object) + ".\n");
    }    
}
