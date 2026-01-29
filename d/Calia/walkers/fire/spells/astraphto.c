
 /* Astraphto (Tell Line) spell for the Firewalkers of Thalassia
  * by Jaacar 
  * Description changed and form skill required changed from 
  * channeling to conjuration. 22.2.99, by Bishop of Calia.
  */


#pragma strict_types

inherit "/d/Genesis/magic/spells/tell";

#include <options.h>
#include <ss_types.h>
#include <macros.h>
#include "defs.h"
#include FIRE_HEADER

public object *
tell_target_one_distant_guild_member_by_skill_or_known_living(object caster,
    string str)
{
    object living;

    if (!strlen(str))
    {
        caster->catch_tell("Target whom?\n");
        return ({});
    }

    living = find_living(str);

    if (!objectp(living) ||
        caster->query_met(living) || 
        (living->query_wiz_level() && living->query_invis()))
    {
	caster->catch_tell("You do not sense " + LANG_POSS(str) +
            " presence in the realms.\n");
	return ({ });
    }

    return ({ living });     
}

public object *
find_tell_targets(object caster, string name)
{
    return tell_target_one_distant_guild_member_by_skill_or_known_living(caster,
        name);
}

public void
tell(object caster, object *targets, int *resist, int result)
{
    write("You complete the Astraphto spell.\n");

    if (caster->query_option(OPT_ECHO))
    {
        caster->catch_tell("You gesture quickly and snap a command" +
            " word." +
            " A small fire elemental appears, and you whisper this" +
            " message to it: " + query_tell_message() + "\n" +
            "The elemental then disappears to deliver your message" +
            " to " + targets[0]->query_met_name() + ".\n");
    }

    tell_room(environment(caster),QCTNAME(caster)+" makes a sudden" +
        " gesture, and snaps an unintelligible command word. A" +
        " small fire elemental appears, " + QTNAME(caster) +
        " whispers a message to it, and the elemental disappears" +
        " in a puff of smoke.\n", caster);
    tell_room(environment(targets[0]), "A small fire elemental" +
        " appears with a crackling sound. It moves towards " +
        QCTNAME(targets[0]) + " and whispers something in " +
        targets[0]->query_possessive() + " ear.\n" +
        "The fire elemental disappears as suddenly as it came.\n",
        targets[0]);

    targets[0]->catch_tell("A small fire elemental appears with" +
        " a crackling sound. It moves towards you and whispers" +
        " a message from " + 
        caster->query_met_name() +
        " in your ear: " + query_tell_message() + "\n" +
        "The fire elemental disappears as suddenly as it came.\n");
}

public int
create_spell_tell(object caster, object *targets, string argument)
{
    ::create_spell_tell(caster, targets, argument);
    set_spell_element(SS_ELEMENT_FIRE, 10);
    set_spell_form(SS_FORM_CONJURATION, 10);
    set_spell_ingredients(({ }));
}
