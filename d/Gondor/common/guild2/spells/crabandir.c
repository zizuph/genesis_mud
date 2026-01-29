/*
 * /d/Gondor/common/guild2/spells/crabandir.c
 *
 * Summon a crow to watch a living target.
 *
 * December 1995
 * (craban-tir - crow-watcher)
 * 
 * Class 3 information spell
 * Element Air; Form Conjuration
 * Area of effect: living target and its environment
 *
 * Ingredient: corcosunk potion effect, holly berry
 * Mana: 100, one third of that on failure.
 * Skills: SS_ELEMENT_AIR, SS_FORM_CONJURATION, SS_SPELLCRAFT
 * Description:  Summons a crow that will spy on a living target.
 * Requirements: Morgul Mage, guild level >= 18
 *               mage robe must be present
 *               no combat, no weapon wielded
 *
 * December 1995
 * Modification log:
 */

#undef DEBUG

#define MS_CRABA_INGR     ({ "crabandir_ingr1", "crabandir_ingr2", })
#define MS_CRABA_MANA	   100
#define MS_CRABA_TASK     TASK_FORMIDABLE
#define MS_CRABA_TASK_DIFF 300
#define MS_CRABA_LIST     ({ SS_ELEMENT_AIR, SS_SPELLCRAFT, SS_FORM_CONJURATION })

#define MORGUL_TOWER_TOP	(GUILD_DIR + "tower/tower_6c")

public void    move_craban(object tp, object target, int result);
public void    send_craban(object tp, int result, object craban);

mixed
do_crabandir(string str)
{
    object  tp = this_player(),
            env = ENV(tp),
            dummy,
           *ingr_arr,
            target;
    string  fail;
    int     is_wiz = tp->query_wiz_level(),
            diff,
            result;

#if DEBUG
    is_wiz = 0;
#endif

    if (!strlen(str))
        return "Summon a craban to watch whom?\n";

    if (env->query_prop(ROOM_I_INSIDE) && (file_name(env) != MORGUL_TOWER_TOP))
        return "You cannot summon a craban here.\n";

    target = find_living(LOW(str));

    if (!objectp(target))
        return "There is no creature of that name within the realms!\n";

    if (!is_wiz && (target->query_wiz_level() ||
        (target->query_morgul_level(-1) >= tp->query_morgul_level(-1))))
        return "You do not dare to send a craban to spy on "+CAP(str)+"!\n";

    // is the spell legal for this target, for this target environment?
    if (RNMAGIC(env) || NPMAGIC(target) ||
        (objectp(dummy = ENV(target)) && RNTELEPORT(dummy)))
        return MORGUL_S_SPELL_FAIL;

    if (objectp(dummy = tp->query_attack()) && present(dummy, env))
        return "You cannot cast a spell while in combat!\n";
    if (sizeof(tp->query_weapon(-1)))
        return "You cannot cast a spell while wielding a weapon!\n";
    if (!present(MORGUL_S_GUILD_OBJECT, tp))
        return "Without your robe, you cannot cast this spell!\n";
    if (stringp(fail = check_player(tp, 0, MS_CRABA_MANA, MS_CRABA_MIN)))
        return fail;

    ingr_arr = find_ingr(MS_CRABA_INGR, tp);
    diff = MS_CRABA_TASK - sizeof(ingr_arr) * MS_CRABA_TASK_DIFF;
    if (tp->query_npc())
        diff = TASK_ROUTINE;
    if (diff < 0)
        diff = 0;
#if DEBUG
    write("DEBUG: difficulty = " + diff + ".\n"
        + "       ingredients: "+COMPOSITE_DEAD(ingr_arr)+"\n");
#endif

    if ((!(is_wiz)) && ((result =
        tp->resolve_task(diff, MS_CRABA_LIST)) <= 0))
    {
#if DEBUG
    write("DEBUG: crabandir fail result: " + result + "\n");
#endif
        tp->add_mana(-(MS_CRABA_MANA/3));
        fail_cast(tp, ingr_arr);
        return 1;
    }
#if DEBUG
    write("DEBUG: crabandir result: " + result + "\n");
#endif

    tell_room(ENV(tp), "Employing Dark Sorcery, " + QTNAME(tp)
      + " summons a winged servant from the realm of shadows.\n"
      + CAP(HE(tp)) + " takes something and places it in "+HIS(tp)+" right "
      + "hand, extending it skyward, as if beckoning something.\n", tp);
    // I command thee, crow! Hear my word and come.
    tp->catch_msg(BSN("Using the power the Dark Lord has bestowed upon you, "
      + "you summon one of the crebain to spy on "+CAP(str)+" for you. "
      + (((sizeof(ingr_arr) == 2) ||
         ((sizeof(ingr_arr) == 1) && (ingr_arr[0]->id("crabandir_ingr1")))) ?
        "Taking your berry in your right hand and extending it skyward, " :
        "Extending your hands skyward, ")
      + "you beckon your servant with the words "
      + "\"Yalanlye craban! Gimo nin kweth a telo!\"!"));

    if (result <  60)
        result =  60;
    // effective max is 180!
    if (result > 180)
        result = 180;

    set_alarm(5.0, 0.0, &move_craban(tp, target, result));

    if (!is_wiz)
    {
        tp->add_mana(-(MS_CRABA_MANA));
        remove_ingr(ingr_arr);
    }

    return 1;
}

public void
move_craban(object tp, object target, int result)
{
    object  craban,
            env = ENV(tp);

    // Now do your stuff!
    craban = clone_object((MORGUL_SPELL_OBJS + "craban"));
    craban->set_target(target);
    craban->set_duration(result * 2 + 60);
    tell_room(env, "A dark cloud appears out of nowhere.\n"
      + "Out of the cloud flies "+LANG_ADDART(craban->short())+".\n"
      + "The "+craban->short()+" lands on the ground, "
      + "and the cloud disappears again.\n");
    craban->move_living("M", env);
    craban->command("emote croaks harshly.");

    set_alarm(5.0, 0.0, &send_craban(tp, result, craban));
}

public void
send_craban(object tp, int result, object craban)
{
    object  paralyze;

    // paralyze mage
    paralyze = clone_object("/std/paralyze");
    paralyze->set_stop_fun("remove_craban");
    paralyze->set_stop_object(craban);
    paralyze->set_stop_message("You are in control of your undead body again.\n");
    paralyze->set_fail_message("You can only watch through the eyes of the "
      + "craban, but you have no control over it.\n"
      + "You can steer your awareness back to your undead body "
      + "by using the command \"peluvo\".\n");
    paralyze->set_stop_verb("peluvo");
    // Play it safe, add a remove time, even though the effect should be
    // ended through the alarm in the craban.
    paralyze->set_remove_time(result * 2 + 60);

    craban->set_paralyze(paralyze);
    craban->set_mage(tp);

    tell_room(ENV(tp), QCTNAME(tp) + " slumps to the ground.\n"
      + CAP(HIS(tp)) + " undead body is like an empty vessel, left behind "
      + "by a spirit that departed elsewhere.\n", ({ tp, craban }), tp);
    tp->catch_msg("Your awareness enters the craban which you summoned.\n"
                + "You lose the control over your undead body and start "
                + "seeing with the eyes of the craban.\n");
    if (paralyze->move(tp))
        paralyze->move(tp, 1);
    tp->add_stun();

    craban->start_watch();
}

#undef DEBUG

