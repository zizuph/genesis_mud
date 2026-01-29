#define SP_PROT_INGR    ({ "_prot_spell_ingr1_" })
#define SP_PROT_MANA    50
#define SP_PROT_MIN     30
#define SP_PROT_TASK    TASK_DIFFICULT
#define SP_PROT_LIST    ({ SKILL_WEIGHT, 50, SS_SPELLCRAFT, \
                SKILL_WEIGHT, 90, SKILL_AVG, SS_WIS, SS_INT, SKILL_END, \
                SS_FORM_ABJURATION, SS_ELEMENT_EARTH })

void
wear_off(object player)
{
    object arm;
    arm = present("_herald_robe_", player);
    if(!arm) return;
    arm->set_ac(1);
    arm->remove_prop("_ondo_spell_");
    player->update_armour(arm);
    player->catch_msg("Your flawless flowing white robe glimmers "+
      "again, then grows lighter.\n");
}

/*
 * Function name:   do_protect_spell
 * Decription:      Cast the protect spell.
 * Arguments:       str: just in case they try to protect someone else.
 * Returns:         1 if spell was cast, 0 or the error string otherwise.
 */
mixed
do_protect_spell(string str)
{
    object tp, arm, *ingr_arr;
    int i, success, val, is_wiz;
    string fail;
    tp = this_player();
    is_wiz = tp->query_wiz_level();
    arm = present("_herald_robe_",tp);
    if(!arm)
	return "You have no robe to strengthen!\n";
    if (!arm->query_worn())
	return "You must wear your "+arm->short()+" for this spell "+
	"to work.\n";

    if (str != "myself" && str != "me")
	return "You can only protect yourself.\n";

    if (arm->query_prop("_ondo_spell_"))
	return "Your robe is already strengthened.\n";

    if (fail = check_player(tp, SP_PROT_INGR, SP_PROT_MANA, SP_PROT_MIN))
	return fail;

    /* Get the object array of all ingredients */
    ingr_arr = find_ingr(SP_PROT_INGR, tp);

    i = tp->resolve_task(SP_PROT_TASK, SP_PROT_LIST);

    /* Let's see how successful she is */
    if (!is_wiz && i <= 0)
    {
	fail_cast(tp, ingr_arr);
	return 1;
    }
    val = tp->query_stat(SS_LAYMAN);
    val = val/2;

    if(val < 10)
    {
	val = 10;
    }

    if(val > 35)
    {
	val = 35;
    }
    set_alarm(240.0,0.0,"wear_off",tp);
    arm->set_ac(val);
    arm->add_prop("_ondo_spell_",1);
    tp->update_armour(arm);
    tp->catch_msg("You kneel and touch your hands to the ground, and "+
      "gain strength from the rock and the earth.\n"+
      "Your robe shimmers and then dims slightly, growing heavier.\n");
    tell_room(environment(tp), QCTNAME(tp) + " kneels and touches "+
      HIS_HER(tp)+" hands to the ground.  When "+HE_SHE(tp)+" stands "+
      HE_SHE(tp)+" is visibly strengthened.\n", ({ tp }));

    /* Remove the ingredients and make her pay for it */
    if (!is_wiz)
    {
	remove_ingr(ingr_arr);
	tp->add_mana(-SP_PROT_MANA);
    }
    return 1;
}
