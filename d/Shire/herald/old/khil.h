#include <cmdparse.h>

#define SP_ALIGN_INGR    ({ })
#define SP_ALIGN_MANA 30
#define SP_ALIGN_MIN 30
#define SP_ALIGN_TASK  TASK_ROUTINE
#define SP_ALIGN_LIST  ({ SKILL_WEIGHT, 50, SS_SPELLCRAFT, \
		SKILL_WEIGHT, 90, SKILL_AVG, SS_WIS, SS_INT, SKILL_END, \
		SS_FORM_DIVINATION, SS_ELEMENT_LIFE })

/*
 * Function name:   do_align_spell
 * Decription:	    Cast the align spell.
 * Arguments:	    who: The person to check alignment of
 * Returns:	    1 if spell was cast, 0 or the errorstring otherwise.
 */
mixed
do_align_spell(string who)
{
    object target, *oblist, *ingr_arr;
    int i, success, is_wiz, result;
    string fail;

    is_wiz = this_player()->query_wiz_level();

    if (!who)
	return "Check the alignment of whom?\n";

    oblist = PARSE_THIS(who, "[the] %l");

    if (!sizeof(oblist))
    {
	write("You find no "+who+" to make your prayer for.\n");
	return 1;
    }

    if (sizeof(oblist) > 1)
    {
	write("You can only make your prayer for one person at a time.\n");
	return 1;
    }

    target = oblist[0];

    fail = check_player(this_player(), SP_ALIGN_INGR, SP_ALIGN_MANA, SP_ALIGN_MIN);

    if (fail && fail != "One of the ingredients is missing!\n")
	return fail;

    /* Get the object array of all ingredients */
    ingr_arr = find_ingr(SP_ALIGN_INGR, this_player());

    /* Let's see how successful she is */
    if (!is_wiz && this_player()->resolve_task(SP_ALIGN_TASK, SP_ALIGN_LIST) <= 0)
    {
	fail_cast(this_player(),ingr_arr);
	return 1;
    }

    result = target->query_alignment();

    switch(result)
    {
    case -1200..-800:
	write("Your target is lost in the darkness of Melkor.\n");
	break;
    case -799..-300:
	write("Your target knows darkness well.\n");
	break;
    case -299..-1:
	write("Your target is beginning to gather shadows.\n");
	break;
    case 0..300:
	write("Your target is not captured by the darkness.\n");
	break;
    case 301..799:
	write("Your target seems to know something of the Valar.\n");
	break;
    case 800..1200:
	write("Your target is a true enemy of Melkor.\n");
	break;
    default:
	write("Your target baffles you.\n");
	break;

    }


    /* Remove the ingredients and make her pay for it */
    remove_ingr(ingr_arr);
    this_player()->add_mana(-SP_ALIGN_MANA);

    return 1;
}

