#include <composite.h>
#include <ss_types.h>

/*
 * MINSTREL_SKILL_DESC
 *
 * Description, Costfactor(0-100) Limiting Stat, Limit Weight, Max adv guild
 *
 */
#define MINSTREL_SKILL_DESC ([ \
/* Minstrel skills */                                                \
    130050:      ({ "playing instrument",     50, SS_DEX, 150, 0 }), \
    130051:      ({ "singing",                50, SS_WIS, 150, 0 }), \
    130052:      ({ "reading music",          50, SS_INT, 150, 0 }), \
    130053:      ({ "tune/repair instrument", 50, SS_DEX, 150, 0 }), \
])

/*
 * Function:    query_spell_weapon_class_stat_influencer
 * Description: Allows for the customisation of the stat or stats
 *              that influence the strength of spells. This function
 *              should not be masked without approval by the AoB,
 *              and the use of multiple stats as influencer need to
 *              be averaged as if it were a single stat.
 */
public int
query_spell_weapon_class_stat_influencer()
{
   object caster = this_player();
   int stat_influencer;

   // masked from centralized spell, Minstrel spell power will be
   // influenced by a combination of SS_DEX and SS_DIS rather than SS_INT

   stat_influencer = (caster->query_stat(SS_DEX) + caster->query_stat(SS_DIS)) / 2;

   return stat_influencer;
}

void
damage_minstrel_instrument()
{
    object instrument = present("minstrel_instrument", this_player());

    instrument->add_damage(min(1, random(5)));

    if(!instrument->query_damage())
    {
        return;
    }
    else if(instrument->query_damage() < 6)
    {
        this_player()->catch_tell("Your " +instrument->query_name()+ 
            " sounds like it needs tuning.\n");
        tell_room(environment(this_player()), QCTPNAME(this_player())+
            " " +instrument->query_name()+ " sounds like it needs tuning.\n", 
            ({ this_player() }), this_player());
    }
    else
    {    
        this_player()->catch_tell("You seem to have damaged your " + 
            instrument->query_name()+ "!\n");
        tell_room(environment(this_player()), QCTNAME(this_player())+
            " seems to have damaged " +this_player()->query_possessive()+
            " "+ instrument->query_name()+ "!\n", 
            ({ this_player() }), this_player());
    }


}

string
minstrel_perform_fail()
{
    if(query_spell_form_skill() == SG_INSTRUMENTAL ||
       query_spell_element() == SG_INSTRUMENTAL)
    {
        //if (random(10) == 1)
        //{    
            set_alarm(0.1, 0.0, &damage_minstrel_instrument());
        //}
    }

    return "You fail in your efforts to perform " +
        "the Song of Power.\n";
}

public int
query_active_lost_muse_effect(object caster, string song)
{
    object * maintained_effects;

    if(!caster->query_prop("_live_o_maintained_effects"))
        return 0;

    maintained_effects = caster->query_prop("_live_o_maintained_effects");

    foreach(mixed spell: maintained_effects)
    {
        if(!objectp(spell))
            continue;

        string spell_name = file_name(spell);

        // DEBUG("maintained spell: " +spell_name+ ".");

        if((wildmatch("/d/Terel/guilds/minstrels/spells/obj/accelerando_obj*", 
            spell_name)) && song != "accelerando")
        {
            // DEBUG("accelerando detected.");
            return 1;
        }
        if((wildmatch("/d/Terel/guilds/minstrels/spells/obj/lento_obj*", 
            spell_name)) && song != "lento")
        {
            // DEBUG("lento detected.");
            return 1;
        }
        if(caster->query_has_concerto_shadow() && song != "concerto")
        {
            return 1;
        }
        if((wildmatch("/d/Terel/guilds/minstrels/spells/obj/animato_obj*", 
            spell_name)) && song != "animato")
        {
            // DEBUG("animato detected.");
            return 1;
        }
        if((wildmatch("/d/Terel/guilds/minstrels/spells/obj/bellicoso_obj*", 
            spell_name)) && song != "bellicoso")
        {
            // DEBUG("bellicoso detected.");
            return 1;
        }
    }

    // DEBUG("no maintained spell detected.");
    return 0;
}

/*
 * Function name: hook_no_magic_fail
 * Description:   Return the message that should be printed when noone
 *                is supplied with ROOM_M_NO_MAGIC.
 * Arguments:     obj - The room object.
 * Returns:       The message to print.
 */
public void
hook_room_no_magic_fail(mixed reason, object room)
{
    if (stringp(reason))
    {
        write(reason);
    }
    else
    {
        write("You can't perform the Song of Power, as if resisted by the " + 
            "very air around you.\n");
    }
}
/*
 * Function name: hook_no_magic_attack_fail
 * Description:   Return the message that should be printed when noone
 *                is supplied with ROOM_M_NO_MAGIC_ATTACK.
 * Arguments:     obj - The room object.
 * Returns:       The message to print.
 */
public void
hook_room_no_magic_attack_fail(mixed reason, object room)
{
    if (stringp(reason))
    {
        write(reason);
    }
    else
    { 
        write("You can't perform the Song of Power, as if resisted by the " + 
            "very air around you.\n");
    }
}
/*
 * Function name: hook_no_mana_fail
 * Description:   Return the message that should be printed when the caster
 *                doesn't have enough mana.
 * Returns:       The message to print.
 */
public void
hook_no_mana_fail(object ability)
{
    write("You are mentally drained. That Song of Power is beyond your " +
        "abilities right now.\n");
}

/*
 * Function name: hook_targets_gone
 * Description:   Return the string that will be printed to the caster when
 *                the targets has disappeared during the prepartion of the
 *                spell.
 * Returns:       The message to print
 */
public void
hook_targets_gone()
{
    write("Nobody here to perform that Song of Power on!\n");
}

/*
 * Function name: hook_living_no_magic_attack_fail
 * Description:   This function should return the string that will be printed
 *                to the caster, when trying to attack a living that has the
 *                property OBJ_M_NO_MAGIC_ATTACK set.
 * Arguments:     target - The intended targer
 * Returns:       The message to print
 */
public void
hook_living_no_magic_attack_fail(object target,object ability)
{
    write("You can't perform that Song of Power on " +
        target->query_the_name(this_player()) + ".\n");
}

public void
hook_cannot_see_fail(object ability)
{
    write("You cannot see well enough to perform that Song of Power!\n");
}

public void
hook_cannot_speak_fail(object ability)
{
    write("You cannot speak, so cannot perform that Song of Power!\n");
}

public void
hook_resist_spell_object(object *spell_objects, object caster, object *targets)
{
    caster->catch_msg("Your Song of Power was resisted by "
    + FO_COMPOSITE_LIVE(targets, caster) + ".\n");
}

/*
 * Function:    hook_insufficient_skill
 * Description: This gets called when the player doesn't have the minimum
 *              skill requirements to cast the spell.
 */
public varargs void
hook_insufficient_skill(object caster, int * needed_skills)
{
    string sMessage = "You do not have the required skills to perform this "
        + "song. You will need to receive more training in ";
    
    string * skill_names = ({ });
    mapping skmap = MINSTREL_SKILL_DESC;
    foreach (int skillnum : needed_skills)
    {
        skill_names += ({ skmap[skillnum][0] });
    }
    sMessage += (COMPOSITE_WORDS(skill_names) + ".\n");
    caster->catch_tell(sMessage);
}

/*
 * Function:    hook_casting_shield_failure
 * Description: This gets called when the player fails to cast
 * 		the spell due to interference from worn shields.
 */
public void
hook_casting_shield_failure(object caster, object *shields)
{
    caster->catch_tell("You sense that "+
	FO_COMPOSITE_DEAD(shields, caster) +
	(sizeof(shields) == 1 ? " has " : " have ") +
	"interfered with your Song of Power performance.\n");
}

/*
 * Override the spellpower enhancer lookup, because we
 * use a custom element, but will depend on air enhancers.
*/
public object
get_best_spellpower_enhancer(object actor)
{
    object* tools = ({ actor->query_tool(W_LEFT), 
                       actor->query_tool(W_RIGHT) });
    int highest_power = 0;
    object best_tool;
    foreach (object tool : tools)
    {
        if (!tool->query_spellpower_enhancer())
            continue;
        if (!tool->query_spellpower_elements())
            continue;
        if (member_array(SS_ELEMENT_AIR,
            tool->query_spellpower_elements()) < 0)
            continue;
        if (tool->query_magic_spellpower() > highest_power)
        {
            best_tool = tool;
            highest_power = tool->query_magic_spellpower();            
        }
    }
    return best_tool;
}

public int is_minstrel_spell() {
    return 1;
}