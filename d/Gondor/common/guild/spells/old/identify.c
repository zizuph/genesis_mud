#pragma save_binary

/*
 * The identify spell, coded by Mercade, 23 October 1993
 */
#define SP_IDENTIFY_MANA            100
#define SP_IDENTIFY_FAIL_MANA        25
#define IDENTIFY_SPELL_BASIC_SKILL   35

mixed
do_identify_spell(string str)
{
    object tp = this_player();
    object target, *targets;
    string fail;
    string result = "";
    int skill, i;
    mixed magical_info;

    if (!strlen(str))
    {
        NFN0("Identify what?");
    }

    targets = FIND_STR_IN_OBJECT(str, tp) +
        FIND_STR_IN_OBJECT(str, environment(tp));
    if (!sizeof(targets))
    {
        NFN0("Identify what?");
    }
    else
    {
        target = targets[0];
    }

    if (strlen(fail = check_player(tp, 0, SP_IDENTIFY_MANA)))
    {
        write(fail);
        return 1;
    }

    /* those bloody wizards always have an advantage. */
    if ((!(tp->query_wiz_level())) &&
        (tp->resolve_task((TASK_ROUTINE, 
        ({ TS_WIS,
           SS_LANGUAGE,
           SS_SPELLCRAFT,
           SS_FORM_DIVINATION,
           SS_APPR_OBJ }) ) <= 0))
    {
        tp->add_mana(-SP_IDENTIFY_FAIL_MANA);
        write("You fail to cast the spell properly.\n");
        SAY(" fails to cast a spell properly.");
        return 1;
    }

    if (!(tp->query_wiz_level()))
    {
        tp->add_mana(-SP_IDENTIFY_MANA);
    }
    SAY(" casts a spell on " +
        ((ENV(target) == TP) ? "something" :
            "the " + check_call(target->short())) +
        " to discover more about " +
        ((living(target)) ? OBJECTIVE(target) : "it") + ".");

    /*
     * In his example of an object that does magical identification, Nick
     * gives only one element in the array MAGIC_AM_ID_INFO whereas I think
     * that you should get all messages below the value of your magic.
     */
    skill = IDENTIFY_SPELL_BASIC_SKILL +
            (tp->query_stat(SS_WIS) / 5) +
            (tp->query_skill(SS_LANGUAGE) / 5) +
            (tp->query_skill(SS_SPELLCRAFT) / 5) +
            (tp->query_skill(SS_FORM_DIVINATION) / 5) +
            (tp->query_skill(SS_FORM_ILLUSION) / 5) -
            (target->query_prop(MAGIC_I_RES_IDENTIFY));
    if (skill < 0)
    {
        skill = 0;
    }

    magical_info = target->query_prop(MAGIC_AM_ID_INFO);
    for (i = 0; i < sizeof(magical_info); i += 2)
    {
        if (magical_info[i + 1] <= skill)
        {
            result += (string)magical_info[i];
        }
    }

    if (strlen(result))
    {
        WRITE("You successfully cast a spell on the " +
            check_call(target->short()) + " to discover more about it.");
        write(result); /* the "\n" should be in the result string. */
    }
    else
    {
        WRITE("You cast the spell successfully. However, you did not manage " +
            "to obtain any information about the " + check_call(target->short()) +
            ", other than a better appraisal of it.");
        target->appraise_object(skill + 100);
    }

    return 1;
}