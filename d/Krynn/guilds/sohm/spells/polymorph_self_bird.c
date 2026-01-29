/*
 * Polymorph self travel cantrip 
 *
 * Coded by Arman 2016.
 */
 
#pragma strict_types

#include <ss_types.h>
#include <macros.h>
#include <tasks.h>
#include <stdproperties.h>
#include <flags.h>
#include "defs.h"
#include "/d/Krynn/common/defs.h"
#include CLOCKH

#include "/d/Genesis/specials/local.h"
inherit SPELL_DIR + "shapeshift";

public mapping  polymorph_mapping = ([
    "bird" : "/d/Genesis/race/shapeshift/wohs_polymorph_self_bird", 
]);

/*
 * Function:    config_shapeshift_spell
 * Description: Config function for shapeshift spells. Redefine this in your
 *              own shapeshift spells to override the defaults.
 * Arguments:   Same as config_spell
 * Returns:     Same as config spell
 */
public void
config_shapeshift_spell()
{
    set_spell_name("thirkualtiui");
    set_spell_desc("Polymorph self - bird form");

    set_spell_vocal(1);
    set_spell_visual(1);
    set_spell_stationary(1);
    set_spell_peaceful(1);
    set_spell_offensive(0);
    set_spell_fail("You attempt to polymorph yourself, but are unable to harness " +
        "the powers of transmutation adequately and the spell fails.\n");
    set_spell_element(SS_ELEMENT_EARTH, 50);
    set_spell_form(SS_FORM_TRANSMUTATION, 60);

    set_ability_stats(STAT_WEIGHTING);

    set_spell_class(SPELL_CLASS_3);
    set_spell_task(TASK_HARD);    

    set_shape_mapping(polymorph_mapping);

    // Spell effect object
    set_spell_object(SOHM_SPELL_OBJS + "polymorph_self_obj");
}

/*
 * Function:    query_shapeshift_ingredients
 * Description: This function defines what components are required for
 *              this shapeshift spell.
 */
public string *
query_shapeshift_ingredients(object caster)
{
    return ({ "wari wing" });
}


public int 
check_valid_action(object caster, mixed * targets, string arg, int execute = 0)
{
    if (!::check_valid_action(caster, targets, arg, execute))
    {
        return 0;
    }

    if(environment(caster)->query_prop(ROOM_I_INSIDE))
    {
        caster->catch_tell("You can only polymorph yourself in to " +
            "a bird outside.\n");
        return 0;
    }
        
    return 1;
}

public int
query_spell_can_be_learned(object player)
{
    if (!objectp(player))
    {
        return 0;
    }
    
    if (player->query_npc() || player->query_wiz_level())
    {
        // npcs can always learn the spell.
        return 1;
    }
    
    setuid();
    seteuid(getuid());
    return SOHM_MANAGER->query_memorised_spell(player,"thirkualtiui_memorised");
}

// HOOKS TO BE DEFINED

/*
 * Function:    resolve_shapeshift_spell
 * Description: Called at the beginning of resolve_spell in order to perform
 *              spell specific actions.
 * Arguments:   Same as resolve_spell
 */
public void
resolve_shapeshift_spell(object caster, mixed * targets, int * resist, int result)
{

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

    string align = SOHM_MANAGER->query_wohs_order_colour(caster);
    string chant;

    switch(align)
    {
        case "black":
            chant = "    The plain light in the east\n" +
                    "    Contrives out of the dark\n" +
                    "    The machinery of day\n" +
                    "    The diminished song of the lark.\n\n" +
                    "    But the ravens ride the night\n" +
                    "    And the darkness west,\n" +
                    "    The wing beat of their hearts\n" +
                    "    Large in a buried nest.\n\n";
            break;
        case "white":
            chant = "    The light in the eastern skies\n" +
                    "    Is still and always morning,\n" +
                    "    It alters the renewing air\n" +
                    "    Into belief and yearning.\n\n" +
                    "    And larks rise up like angels,\n" +
                    "    Like angels larks ascend\n" +
                    "    From sunlit grass as bright as gems\n" +
                    "    Into the cradling wind.\n\n";
             break;
         default:
            chant = "    Through night the season ride into the dark,\n" +
                    "    The years surrender in the changing lights,\n" +
                    "    The breath turns vacant on the dusk or dawn\n" +
                    "    Between the abstract days and nights.\n\n" +
                    "    For there is always corpselight in the fields\n" +
                    "    And corposants above the slaughterhouse,\n" +
                    "    And at deep noon the shadowy vallenwoods\n" +
                    "    Are bright at the topmost boughs.\n\n";
             break;
    }

    if(E(caster)->query_prop(ROOM_IN_AIR))
    {
        caster_message = "You extend yourself horizontally in the air, arms extended, " +
            "and incant the Song of Wayreth Forest:\n\n" + chant;
        watcher_message = QCTNAME(caster) + " extends " + HIM(caster) + "self horizontally " +
           "in the air, arms extended, incanting the Song of Wayreth Forest:\n\n" + chant;
    }
    else
    {
        caster_message = "You lower yourself to one knee and incant the Song " +
            "of Wayreth Forest:\n\n" + chant;
        watcher_message = QCTNAME(caster) + " lowers " + HIM(caster) + "self to one knee " +
           "while incanting the Song of Wayreth Forest:\n\n" + chant;
    }
        
    caster->catch_tell(caster_message);
    tell_room(environment(caster), watcher_message, ({ caster }), caster);

    setuid();
    seteuid(getuid());    
}

public void
hook_already_has_spell_object(object caster, object target)
{
    write("You have already changed forms!\n");
}

/*
 * Function:    hook_invalid_shape_specified
 * Description: Called when the user specifies an invalid shape name. The
 *              shapes should be specified in the shape_mapping.
 */
public void 
hook_invalid_shape_specified(object actor, string str) 
{
    if (!strlen(str))
    {
        actor->catch_tell("You need to specify a form that you wish to "
            + "polymorph into.\n");
        return;
    }
    actor->catch_tell("You cannot polymorph into a " + str + ".\n");
}

/*
 * Function name: hook_no_ingredients_fail
 * Description:   Return the message that should be printed when the caster
 *                doesn't have the right ingredients
 * Returns:       The message to print.
 */
public void
hook_no_ingredients_fail(mixed * ingredients_needed)
{
    write("You are missing a component to call upon the polymorph self transmutation!\n");
}

