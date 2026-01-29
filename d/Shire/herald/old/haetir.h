#include <language.h>
#include <composite.h>
#include <filter_funs.h>


#define SP_CLV_INGR	({ "_clv_spell_ingr_" })
#define SP_CLV_MANA	40
#define SP_CLV_MIN	16
#define SP_CLV_TASK	TASK_ROUTINE
#define SP_CLV_LIST	({ SKILL_WEIGHT, 50, SS_SPELLCRAFT, \
		SKILL_WEIGHT, 90, SKILL_AVG, SS_WIS, SS_INT, SKILL_END, \
		SS_FORM_DIVINATION, SS_ELEMENT_LIFE })



/*
 * Function name:   do_clairvoyance_spell
 * Decription:	    Cast the clairvoyance spell, which allows a player
 *		    to see what another player sees.
 * Arguments:	    The person to "clairvoyance".
 * Returns:	    1 if spell was cast, 0 or the errorstring otherwise.
 */
mixed
do_clv_spell(string who)
{
    object target, *ingr_arr, lastloc, tp, *items;
    int i, success, is_wiz;
    string fail;

    tp = this_player();
    is_wiz = this_player()->query_wiz_level();

    if (!who)
	return "Call for haetir on who?\n";
    lastloc = environment(this_player());

    target = find_living(lower_case(who));
    //     tp->catch_msg("DEBUG: object who decided on: "+who+".\n");
    if (target->query_wiz_level())
	return "That person is too powerful to cast the spell on.\n";

    if (!tp->query_met(target))
	return "Because you do not know "+who+" your spell fails.";
    if (fail = check_player(this_player(), SP_CLV_INGR, SP_CLV_MANA, SP_CLV_MIN))
	return fail;

    /* Get the object array of all ingredients */
    ingr_arr = find_ingr(SP_CLV_INGR, this_player());
    //    tp->catch_msg("DEBUG: Found ingredients, apparently.\n");
    /* Let's see how successful she is */
    if (!is_wiz && this_player()->resolve_task(SP_CLV_TASK,SP_CLV_LIST) <= 0)
    {
	//     tp->catch_msg("DEBUG: Going to fail the cast!\n");
	fail_cast(this_player(),ingr_arr);
	return 1;
    }

    if (target == this_player())
    {
	this_player()->catch_msg("You open your eyes wide and peer quizzically "
	  + "around.\n");
	tell_room(environment(this_player()), QCTNAME(this_player()) + " opens "
	  + this_player()->query_possessive() + " eyes wide.\n"
	  + capitalize(this_player()->query_pronoun()) + " peers around "
	  + "quizzically.\n",this_player());
    }
    else
    {
	//      this_player()->catch_msg("DEBUG: we should have a clairvoyance\n");
	this_player()->catch_msg("You shift your mind into " + capitalize(who)
	  + " and look with " + target->query_possessive()
	  + " eyes.\n");
	write("You open your new eyes and see:\n");
	if (!objectp(target))
	    write("A dark room.\n");
	else if (!objectp(environment(target)))
	    write("A dark void.\n");
	else if (environment(target)->query_prop(OBJ_I_LIGHT) < 1)
	    write("A dark room.\n");
	else {
	    write(environment(target)->long());
	    items = FILTER_CAN_SEE(all_inventory(environment(target)), this_player());
	    if (items) {
		if (sizeof(FILTER_DEAD(items)))
		    write(capitalize(COMPOSITE_DEAD(FILTER_DEAD(items))) + ".\n");
		if (sizeof(FILTER_LIVE(items)))
		    write(capitalize(COMPOSITE_LIVE(FILTER_LIVE(items))) + ".\n");
	    }
	}

	tell_room(environment(this_player()), QCTNAME(this_player()) + " seems to look "
	  + "intently at something far away.\n", ({ this_player() }));
	if (objectp(target))
	    target->catch_msg("You feel a weird magical presence inside...\n"
	      + "You sense the aura of "
	      + QNAME(this_player()) + ".\n"
	      + "The sensation goes away again.\n");
    }

    /* Remove the ingredients and make her pay for it */
    remove_ingr(ingr_arr);
    this_player()->add_mana(-SP_CLV_MANA);
    return 1;
}

