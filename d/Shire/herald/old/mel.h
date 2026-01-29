
#define SP_ADORE_INGR	({ })
#define SP_ADORE_MANA	5
#define SP_ADORE_MIN	0
#define SP_ADORE_TASK	TASK_SIMPLE
#define SP_ADORE_LIST	({ SKILL_WEIGHT, 50, SS_SPELLCRAFT, \
		SKILL_WEIGHT, 90, SKILL_AVG, SS_WIS, SS_INT, SKILL_END, \
		SS_FORM_CONJURATION, SS_ELEMENT_EARTH })




/*
 * Function name:   do_adore_spell
 * Description:	    Cast the adore spell
 * Arguments:       str: better == "lorien", else error message.
 * Returns:	    1 if spell was cast, 0 or the errorstring otherwise.
 */
mixed
do_adore_spell(string str)
{
    int is_wiz, success;
    object flower, *ingr_arr;
    string fail;

    if (!str || lower_case(str) != "lorien")
        return "Mel whom?\n";


    is_wiz = this_player()->query_wiz_level();

    /* Check the player for ingredients and mana */
    if (fail = check_player(this_player(), SP_ADORE_INGR, SP_ADORE_MANA, SP_ADORE_MIN))
        return fail;

    /* Get the object array of all ingredients */
    ingr_arr = find_ingr(SP_ADORE_INGR, this_player());

    /* Let's see how successful she is */
    if (!is_wiz &&
        (success = this_player()->resolve_task(SP_ADORE_TASK, SP_ADORE_LIST)) <= 0)
    {
	fail_cast(this_player(),ingr_arr);
        return 1;
    }

    this_player()->catch_msg("You kneel down and sing an elven song to please Lorien.\n"
	+ "When you get up again, you notice that beautiful flower has\n"
	+ "started to grow here, as a sign of Lorien's approval of your song.\n");
    tell_room(environment(this_player()), QCTNAME(this_player()) + " kneels down and starts to sing some "
     + "ancient song.\n"
     + "While " + this_player()->query_pronoun() + " is singing, a beautiful flower appears from "
     + "nowhere...\nYou gasp in astonishment!\n", this_player());
#if DEBUG
    this_player()->catch_msg("<Cloned flower>\n");
#endif
    seteuid(getuid());
    flower = clone_object(HERALD_DIR + "flower");
    flower->move(environment(environment()));

    /* Remove the ingredients and make her pay for it */
    if (!is_wiz)
    {
	remove_ingr(ingr_arr);
	this_player()->add_mana(-SP_ADORE_MANA);
    }
    return 1;
}


