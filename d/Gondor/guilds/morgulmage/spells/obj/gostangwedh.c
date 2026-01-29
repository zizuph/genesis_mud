#pragma strict_types
#pragma save_binary

#include <macros.h>

#define ONE_OF(x) (x[random(sizeof(x))])


#include "/d/Genesis/specials/local.h"
inherit SPELL_OBJ_DIR + "slow_obj";

public void 
create_spell_object()
{
    set_name("_gostangwedh_object_");
    set_short("slow spell object");    
    set_long("This is the standard slow spell's object.\n");

    add_prop(OBJ_S_WIZINFO, "This is a spell object " +
                            "created by the morgul mage gostangwedh spell.\n");
    set_spell_effect_desc("gostangwedh");    
}

/*
 * Function:    hook_spell_effect_started
 * Description: Override this to customize the message when this spell effect
 *              is added to th target.
 */
public void
hook_spell_effect_started()
{
    object target = query_effect_target();

    if (objectp(target))
    {
        target->catch_tell("An intense feeling of hopelessness and despair "
            + "suddenly overwhelms you, draining your will to do much of "
            + "anything.\n");
        tell_room(environment(target), "You see " + QTNAME(target) 
            + " suddenly slump " + target->query_possessive() + " shoulders "
            + "as a resigned look of hopelessness fills "
            + target->query_possessive() + " eyes.\n", ({ target }));
    }    
}

/*
 * Function:    hook_spell_effect_ended
 * Description: Override this to customize the message when this spell effect
 *              is dispelled.
 */
public void
hook_spell_effect_ended()
{
    object target = query_effect_target();

    if (objectp(target))
    {
        target->catch_tell("Summoning your last ounce of will, you finally "
            + "banish that overwhelming feeling of despair and suddenly feel "
            + "fresh and re-energized.\n");
        tell_room(environment(target), QCTNAME(target) + " suddenly "
            + "straightens up, with a fierce look of determination blazing "
            + "in " + target->query_possessive() + " eyes.\n", ({ target }));
    }
}

/*
 * Function:    hook_spell_effect_warn_fading
 * Description: Override this to customize the message for when
 *              the effect has only a minute left.
 */
public void
hook_spell_effect_warn_fading()
{    
    // Alert the caster that the effect is about to expire.
    object caster = query_effect_caster();
    object target = query_effect_target();
    
    if (objectp(caster) && objectp(target))
    {
        caster->catch_tell("You can feel the struggles of " + QTNAME(target)
            + "as the worm attempts to reject the crushing grip your have "
            + "upon " + target->query_possessive() + " mind.\n");
    }
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
    object target = query_effect_target();
    
    if (objectp(caster))
    {
        caster->catch_tell("Despite your best efforts, you no longer "
            + "have enough energy to continue to dominate the mind "
            + "of "+ QTNAME(target) + ".\n");
    }    
}

/*
 * Function:    hook_slow_start_moving
 * Description: Hook that gets called when the person starts to move with
 *              the slow effect.
 */
public void
hook_slow_start_moving(object player, string direction)
{
    player->catch_tell(ONE_OF(({ 
        "You feel the oppressive weight of despair hanging around "
        + "your shoulders as you attempt to force yourself towards "
        + "the " + direction + " exit.\n",

        "The black shadow of despair, which clings tightly to every "
        + "fibre of your being, fights against every step you make "
        + "towards the " + direction + " exit.\n",

        "It seems that every step you take towards the " + direction 
        + " exit feels heavier than the last. It can only be a matter "
        + "of time before you give into despair completely.\n",

        "With the heavy, black chains of despair dragging upon your "
        + "every muscle, it takes every ounce of will you still posess "
        + "to place one foot in front of the other towards the " 
        + direction + " exit.\n",

        "You slowly place one foot in front of the other towards the " 
        + direction + " exit, as you struggle against this overwhelming "
        + "feeling of despair.\n"
    })));

    tell_room(environment(player), ONE_OF(({ 
        QCTNAME(player) + " inexplicably seems to be struggling "
        + "as " + player->query_pronoun()  + " slowly makes " 
        + player->query_possessive() + " way towards the " + direction 
        + " exit.\n", 

        "With lost, vacant looking eyes " + QTNAME(player) + " stumbles "
        + "slowly towards the " + direction + " exit.\n",

        "You watch as " + QTNAME(player) + " slowly struggles to make "
        + player->query_possessive() + " way towards the " + direction 
        + " exit.\n",

        "It appears that " + QTNAME(player) + " seems to be having some "
        + "sort of internal struggle as " + player->query_pronoun() 
        + " slogs " + player->query_possessive() + " way towards "
        + "the " + direction + " exit.\n",

        "Dead looking eyes dominate the face of " + QTNAME(player)
        + "as " + player->query_pronoun() + " sluggishly shuffles off "
        + "in the direction of the " + direction + " exit.\n",
    })), ({ player }));
}

/*
 * Function:    hook_slow_change_direction
 * Description: Hook that gets called when the person changes direction while
 *              already trying to move.
 */
public void
hook_slow_change_direction(object player, string direction)
{
    player->catch_tell(ONE_OF(({
        "Your brain feels overwhelmed and confused as you change your mind "
        + "and now decide to use the " + direction + " exit.\n",

        "You feel more than a little confused about where you are and where "
        + "you are going, but you now decide that it would be best if you "
        + "moved towards the " + direction + " exit.\n",

        "As the black fog of despair clouds your mind, you are not really "
        + "sure where you are going, but it now seems like a better idea "
        + "to move towards the " + direction + " exit.\n",

        "With all of these black thoughts of despair weighing on your mind, "
        + "it really is quite hard to think straight! Upon some reflection, "
        + "you decide it might be best if you now moved towards the " 
        + direction + " exit.\n"
    })));

    tell_room(environment(player), ONE_OF(({ 
        QCTNAME(player) + " appears sort of  befuddled and confused as "
        + player->query_pronoun() + " suddenly turns around and slowly "
        + "makes " + player->query_possessive() + " way towards the " 
        + direction + " exit.\n", 

        QCTNAME(player) + " suddenly pauses in confusion, as if uncertain "
        + "as to where they are, or where they wish to go. Eventually, they "
        + "begin to make their way towards the " + direction + " exit.\n",

        QCTNAME(player) + " stops for a moment and stares around with a "
        + "blank, confused expression on " + player->query_possessive() 
        + " face. " + capitalize(player->query_pronoun()) + " then turns "
        + " around and begin moving towards the " + direction + " exit.\n",

        QCTNAME(player) + " appears to be extremely confused as " 
        + player->query_pronoun() + " turns around in mid-stride and now "
        + "begin to struggle towards the " + direction + " exit.\n",

        QCTNAME(player) + " suddenly spins " + player->query_objective() 
        + "self around in a moment of confusion before eventually deciding "
        + "to slowly walk towards the " + direction + " exit.\n"
    })), ({ player }));
}

/*
 * Function:    hook_slow_already_moving
 * Description: Hook that gets called when the person continues to try to break 
 *              free in the same direction that they already were trying.
 */
public void
hook_slow_already_moving(object player, string direction)
{
    player->catch_tell(ONE_OF(({ 
        "Your will feels as if it has been drained completely and despair "
        + "threatens to completely overwhelm you. As a result, you are unable "
        + "to move toward the " + direction + " exit any faster than you are "
        + "already going.\n",

        "You struggle with the need to get away from here, but cannot seem "
        + "to figure out how to get to the " + direction + " exit any quicker.\n",

        "You pause for a moment in confusion as you attempt to orient yourself "
        + "and turn towards the proper exit. However, you realize that you were "
        + "already heading in that direction!\n",

        "It is very difficult to think clearly right now, but you decide to "
        + "stop and turn yourself around to begin moving towards the " + direction 
        + " exit. It takes a few moments, but you suddenly notice that you were "
        + "already going that way!\n",

        "You struggle mightily to steer yourself towards the " + direction 
        + "exit, only to discover that you were already heading in that "
        + "direction!\n"
    })));
}

/*
 * Function:    hook_slow_move_succeeded
 * Description: Hook that gets called when the person completes the move
 *              that they wanted to and are allowed to move to the next
 *              room.
 */
public void
hook_slow_move_succeeded(object player, string direction)
{
    player->catch_tell(ONE_OF(({ 
        "After what has felt like a monumental struggle, you have finally "
        + "made your way out the " + direction + " exit.\n",

        "Finally! It was a struggle, but you have now made your way out "
        + "through the " + direction + " exit.\n",

        "It was not easy focusing on getting out through the " + direction 
        + " exit, but you finally made it!\n",

        "It took some time, but you eventually stumble your way through the " 
        + direction + " exit.\n",

        "Your mind was so clouded that you almost forgot where you were "
        + "going! But you now make your way through the " + direction 
        + "exit.\n"
    })));

    tell_room(environment(player), ONE_OF(({
        QCTNAME(player) + " eventually makes " + player->query_possessive() 
        + " way to the " + direction + " exit.\n", 

        "After what seemed to be an enormous internal struggle, " 
        + QTNAME(player) + " makes " + player->query_effect_caster() 
        + " way to the " + direction + " exit.\n",

        "It took some time, but " + QTNAME(player) + " has finally made "
        + "it to the " + direction + " exit.\n",

        "Despite the confused look upon their face, " + QTNAME(player) 
        + " finally stumbles " + player->query_possessive() + " way out "
        + "through the " + direction + " exit.\n",

        "With what appears to be a momumental effort, " + QTNAME(player)
        + "eventually wanders out through the " + direction + " exit.\n"
    })), ({ player }));
}
