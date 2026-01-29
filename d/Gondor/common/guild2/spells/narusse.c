/*
 * /d/Gondor/common/guild2/spells/narusse.c
 *
 * Enchant a weapon to be engulfed in magical flames.
 *
 * December 1995
 * (narusse - flame-blade)
 * 
 * Class 3 enchantment spell
 * Element Fire; Form Enchantment
 * Area of effect: one weapon wielded by caster
 *
 * Ingredient: red pepper, one potion effect.
 *             Ingredients for potion: thyme, tyelka, snake meat, alcohol
 * Mana: 100, one third of that on failure.
 * Skills: SS_ELEMENT_FIRE, SS_FORM_ENCHANTMENT, SS_SPELLCRAFT
 * Description:  Engulfs a wielded weapon in magical flames which inflict
 *               extra damage; weapon may be damaged or destroyed when
 *               spell ends.
 * Requirements: Morgul Mage, guild level >= 10
 *               mage robe must be present
 *               target weapon must be wielded
 *               not during combat
 *
 * February, 1996
 *
 *	Copyright (c) 1996 by Christian Markus
 *
 * Modification log:
 */

#undef DEBUG

#define MS_NARUS_INGR       ({ "narusse_ingr1", "narusse_ingr2", })
#define MS_NARUS_MANA       100
#define MS_NARUS_TASK       TASK_ROUTINE
#define MS_NARUS_LIST       ({ SS_SPELLCRAFT, SS_ELEMENT_FIRE, SS_FORM_ENCHANTMENT })

mixed
do_narusse(string str)
{
    object  tp = this_player(),
            env,
            dummy,
           *ingr_arr,
            weapon,
           *weapon_list;
    string  fail;
    int     is_wiz = tp->query_wiz_level(),
            diff,
            soaked,
            result;

#if DEBUG
    is_wiz = 0;
#endif

    if (!strlen(str))
        return "Upon which blade do you wish to summon the fires of Orodruin?\n";

    weapon_list = FIND_STR_IN_OBJECT(LOW(str), tp);

    if (!sizeof(weapon_list))
        return "Upon which blade do you wish to summon the fires of Orodruin?\n";

    weapon_list = filter(weapon_list, objectp @ &->query_wielded());

    if (!sizeof(weapon_list))
        return "You can only summon the fires of Orodruin onto the blade of a "
          + "weapon that you are wielding!\n";
    if (sizeof(tp->query_weapon(-1)) > 1)
        return "You cannot summon the fires of Orodruin while wielding more than one weapon!\n";

    weapon = weapon_list[0];

    if (!(weapon->query_dt() & W_SLASH))
        return "You can only summon the fires of Orodruin onto a blade!\n";

    if (weapon->query_flame_blade())
        return "The fires of Orodruin have already been summoned upon the "
          + weapon->short() + ".\n";

    env = ENV(tp);
    // is the spell legal for this target, for this target environment?
    if (RNMAGIC(env) || ONMAGIC(weapon))
        return MORGUL_S_SPELL_FAIL;

    if (objectp(dummy = tp->query_attack()) && present(dummy, env))
        return "You cannot cast a spell while in combat!\n";

    if (!present(MORGUL_S_GUILD_OBJECT, tp))
        return "Without your robe, you cannot cast this spell!\n";
    if (stringp(fail = check_player(tp, MS_NARUS_INGR, MS_NARUS_MANA, MS_NARUS_MIN)))
        return fail;

    ingr_arr = find_ingr(MS_NARUS_INGR, tp);

    if ((!(is_wiz)) && ((result = tp->resolve_task(MS_NARUS_TASK, MS_NARUS_LIST)) <= 0))
    {
#if DEBUG
        write("DEBUG: narusse fail result: " + result + "\n");
#endif
        tp->add_mana(-(MS_NARUS_MANA/3));
        fail_cast(tp, ingr_arr);
        return 1;
    }
#if DEBUG
    write("DEBUG: narusse result: " + result + "\n");
#endif

	tp->catch_msg("Using the power the Dark Lord has bestowed upon you, "
	  + "you summon the flames of Orodruin on the " + weapon->short() + ", "
	  + "shouting:\n"
	  + "\tTulo lacho Orodruin! Minno russenna!\n");
    tell_room(env, QCTNAME(tp) + " raises " + HIS(tp) + " " + weapon->short()
      + " high into the air, shouting in a dark voice:\n"
	  + "\tTulo lacho Orodruin! Minno russenna!\n", tp);

    if (result <  60)
        result =  60;
    // effective max is 180!
    // effective max for apprentices (fire = 20, enchantment = 40, spellcraft = 50)
    // (1000 - 500 + 2 * 80) / 5 = 132
    // effective max for mages (fire = 40, enchantment = 80, spellcraft = 90)
    // (1000 - 500 + 2 * 150) / 5 = 160
    if (result > 150)
        result = 150;

    find_player("elessar")->catch_msg("DEBUG: "+tp->query_name() + " casts Narusse "
      + "on " + weapon->short() + ", result " + result + ".\n");
    if (!(clone_object(MORGUL_S_NARUSSE_SHADOW)->shadow_me(weapon)))
    {
        tell_room(env, "Flames engulf the "+weapon->short()+" but they fail "
          + "to find a hold, and disappear again.\n");
        return 1;
    }

    write("Casting the spell dehydrates you.\n");
	soaked = tp->query_soaked();
	if (result > soaked)
	{
        write("You parched body is hurt by the flames summoned upon the "
		  + weapon->short() + ".\n");
		tp->set_soaked(0);
		tp->heal_hp(soaked - result);
		if (tp->query_hp() < 0)
			tp->do_die(TO);    
	}
	else
		tp->set_soaked(soaked - result);

    weapon->set_mage(tp);
    // duration up to 60 min
    weapon->enchant_weapon(result * 30);

    if (!is_wiz)
    {
        tp->add_mana(-(MS_NARUS_MANA));
        remove_ingr(ingr_arr);
    }

    return 1;
}

#undef DEBUG

