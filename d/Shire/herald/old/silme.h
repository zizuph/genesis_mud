
#define SP_SILME_INGR  ({ })
#define SP_SILME_MANA  7
#define SP_SILME_MIN   0
#define SP_SILME_TASK  TASK_ROUTINE
#define SP_SILME_LIST  ({ SKILL_WEIGHT, 50, SS_SPELLCRAFT, \
                SKILL_WEIGHT, 90, SKILL_AVG, SS_WIS, SS_INT, SKILL_END, \
                SS_FORM_CONJURATION, SS_ELEMENT_EARTH })


/*
 * Function name:   do_silme_spell
 * Description:     Cast the silme spell
 * Arguments:       str: *shrug*  not used in the code!
 * Returns:         1 if spell was cast, 0 or the errorstring otherwise.
 */
mixed
do_silme_spell(string str)
{
    object aura, *ingr_arr;
    string fail;
    int is_wiz, success;

    is_wiz = this_player()->query_wiz_level();

    /* Check the player for ingredients and mana */
    if (fail = check_player(this_player(), SP_SILME_INGR, SP_SILME_MANA, SP_SILME_MIN))
        return fail;

    /* Get the object array of all ingredients */
    ingr_arr = find_ingr(SP_SILME_INGR, this_player());

    /* Let's see how successful she is */
    if (!is_wiz && (success = this_player()->resolve_task(SP_SILME_TASK, SP_SILME_LIST)) <= 0)
    {
        fail_cast(this_player(),ingr_arr);
        return 1;
    }

    if (is_wiz)
        success = 250;

    tell_room(environment(this_player()),QCTNAME(this_player()) + " raises "+
    HIS_HER(this_player())+ " hands in the air, chanting softly to Varda.\n"+
    capitalize(HIS_HER(this_player()))+ " flowing white robe begins to shimmer with a "
            + "steady glow.\n", this_player());
    this_player()->catch_msg("You chant a prayer to Elbereth, and your "+
    "flowing white robe begins to shine.\n");
   FIXEUID
    aura = clone_object(HERALD_DIR + "aura");
    /* The aura limits to a minimum of 30 and a maximum of 900 seconds */
    aura->set_max(4*success);
    aura->move(this_player(), 1); /* Move, ignoring the warnings */
    aura->ignite();

    /* Remove the ingredients */

    /* Make her pay for it */
        remove_ingr(ingr_arr);
        this_player()->add_mana(-SP_SILME_MANA);

    return 1;
}

