
#define SP_LAMMEN_INGR  ({ })
#define SP_LAMMEN_MANA  20
#define SP_LAMMEN_MIN   20
#define SP_LAMMEN_TASK  TASK_ROUTINE
#define SP_LAMMEN_LIST  ({ SKILL_WEIGHT, 50, SS_SPELLCRAFT, \
                SKILL_WEIGHT, 90, SKILL_AVG, SS_WIS, SS_INT, SKILL_END, \
                SS_FORM_CONJURATION, SS_ELEMENT_EARTH })


/*
 * Function name:   do_lammen_spell
 * Description:     Cast the lammen spell
 * Arguments:      
 * Returns:         1 if spell was cast, 0 or the errorstring otherwise.
 */
mixed
do_lammen_spell()
{
    object mic, *ingr_arr;
    string fail;
    int is_wiz, success;

    is_wiz = this_player()->query_wiz_level();

    /* Check the player for ingredients and mana */
    if (fail = check_player(this_player(), SP_LAMMEN_INGR, SP_LAMMEN_MANA, SP_LAMMEN_MIN))
        return fail;

    /* Get the object array of all ingredients */
    ingr_arr = find_ingr(SP_LAMMEN_INGR, this_player());

    /* Let's see how successful she is */
    if (!is_wiz && (success = this_player()->resolve_task(SP_LAMMEN_TASK, SP_LAMMEN_LIST)) <= 0)
    {
        fail_cast(this_player(),ingr_arr);
        return 1;
    }

    if (is_wiz)
        success = 250;

    tell_room(environment(this_player()),QCTNAME(this_player()) + " raises "+
    HIS_HER(this_player())+ " hands to the sky, calling on Manwe for power.\n"+
    capitalize(HIS_HER(this_player()))+ " voice rises to a "
            + "tremendous crescendo.\n", this_player());
    this_player()->catch_msg("You call upon Manwe for his voice, and you feel "+
    "your voice begin to strengthen.\n");
   FIXEUID
    mic = clone_object(HERALD_DIR + "mic");
    /* The aura limits to a minimum of 30 and a maximum of 900 seconds */
    mic->set_max(4*success);
    mic->move(this_player(), 1); /* Move, ignoring the warnings */
    mic->silence();

    /* Remove the ingredients */

    /* Make her pay for it */
        remove_ingr(ingr_arr);
        this_player()->add_mana(-SP_LAMMEN_MANA);

    return 1;
}

