/*
 * /d/Gondor/common/guild2/spells/mortirio.h
 *
 * See in darkness
 * (mor-tirio = dark-I see)
 * 
 * Class 1 duration spell
 * Element Air; Form Enchantment
 * Area of effect: caster
 *
 * Ingredient: black potato
 * Mana: 20..40, depending on success of casting
 *       twice that when target not the caster
 * Skills: SS_ELEMENT_AIR, SS_FORM_ENCHANTMENT, SS_SPELLCRAFT
 * Description: Increases caster's LIVE_I_SEE_DARK by 5
 * Requirements: Morgul Mage, level >= 1
 *               mage robe must be present
 *
 * Olorin, 15-jul-1994
 *
 * Modification log:
 * 26-feb-1997, Olorin: Works now inside and outside.
 *                      Duration reduced.
 * 14 Feb 2000, Morbeche: Caster can cast it on himself
 *                        if he has one hand free.
 */
#define MS_MORTI_INGR     ({ "mortirio_ingr1", })
#define MS_MORTI_MANA_SELF 	20
#define MS_MORTI_MANA_OTHER	40
#define MS_MORTI_TASK     TASK_SIMPLE
#define MS_MORTI_LIST     ({ SS_ELEMENT_AIR, SS_FORM_ENCHANTMENT, SS_SPELLCRAFT})
#define MS_MORTI_VICTIM   ({ SS_ELEMENT_EARTH, SS_FORM_ABJURATION })

#undef DEBUG

public mixed
do_mortirio(string str)
{
    object  tp = this_player(),
    env = environment(tp),
    *ingr_arr,
    *target,
    shadow,
    robe;
    int     is_wiz = tp->query_wiz_level(),
    mana_cost = MS_MORTI_MANA_OTHER,
    mana,
    fail,
    duration,
    result;
    string  success,
    msg;

#if DEBUG
    is_wiz = 0;
#endif

    str = LOW(str);
    if (!stringp(str) || str == "me")
	target = ({ tp });
    else
	target = parse_this(str, "[the] %l");
    if (!sizeof(target))
	return "Cast the spell at whom?\n";
    if (sizeof(target) > 1)
	return "You cannot cast the spell at more than one person!\n"; 
    if (target[0] == tp)
	mana_cost = MS_MORTI_MANA_SELF;

    /*
	if (sizeof(tp->query_weapon(-1)))
	    return "You cannot cast a spell while wielding a weapon!\n";
    */

    if ((sizeof(tp->query_weapon(-1))) &&
      (target[0] != tp))
	return "You cannot cast this spell on someone else while wielding a weapon!\n";

    if (sizeof(tp->query_weapon(-1)) > 1)
	return "You cannot cast this spell with no free hands!\n";

if (tp->query_weapon(1536))
      return "You cannot cast this spell with no free hands!\n";

    if (objectp(tp->query_attack()) || objectp(target[0]->query_attack()))
	return "You cannot cast this spell during a fight!\n";

    if (stringp(fail = check_player(tp,
	  MS_MORTI_INGR, mana_cost, MS_MORTI_MIN)))
	return fail;

    if (objectp(target[0]->query_prop(MORGUL_O_MORTIRIO_OBJECT)))
	return "You cannot cast that spell on " +
	((target[0] == tp) ? "yourself" : str) + " again.\n";

    if (!present(MORGUL_S_GUILD_OBJECT, tp))
	return "Without your robe, you cannot cast this spell!\n";

    ingr_arr = find_ingr(MS_MORTI_INGR, tp);

    if (target[0] == tp)
	result = tp->resolve_task(MS_MORTI_TASK, MS_MORTI_LIST);
    else
	result = tp->resolve_task(
	  MS_MORTI_TASK, MS_MORTI_LIST, target[0], MS_MORTI_VICTIM);

    if (!is_wiz && (result <= 0))
    {
#if DEBUG
	write("DEBUG: mortirio fail result: " + result + "\n");
#endif
	tp->add_mana(-(mana_cost/3));
	fail_cast(tp, ingr_arr);
	return 1;
    }
#if DEBUG
    write("DEBUG: mortirio result: " + result + "\n");
#endif

    if (target[0] == tp)
    {
	msg = " starts chewing something and mumbles strange words.\n" +
	"Suddenly, " + tp->query_possessive() + " eyes begin to glow " +
	"like red coals.\n";
	say( ({ tp->query_met_name() + msg,
	    "The " + tp->query_nonmet_name() + msg }) );
	write("You start chewing the black potato.\nWith the power the " +
	  "Dark Lord has bestowed upon you, you cast Mortirio,\n" +
	  "praying silently: Anno nin tur morth, Belegir Morui!\n");
    }
    else
    {
	tell_object(target[0], tp->query_The_name(target[0]) +
	  " starts chewing something and mumbles strange words.\n" +
	  "Then " + tp->query_pronoun() + " glares at you with piercing " +
	  "eyes.\nSuddenly, your eyes start to tingle strangely.\n");
	tell_room(env, QCTNAME(tp) + " starts chewing something and " +
	  "mumbles strange words.\nThen " + tp->query_pronoun() +
	  " glares at " + QTNAME(target[0]) + " with piercing eyes.\n" +
	  "Suddenly, the eyes of " + QTNAME(target[0]) +
	  " begin to glow like red coals.\n", ({ tp, target[0] }) );
	write("You start chewing the black potato.\nWith the power the " +
	  "Dark Lord has bestowed upon you, you cast Mortirio on " +
	  target[0]->query_the_name(tp) + ",\npraying silently: Anno " +
	  "tur morth, Belegir Morui!\n" +
	  CAP(target[0]->query_possessive()) + " eyes begin to glow like " +
	  "red coals.\n");
    }

    if (result < 100)
	result = 100;
    else if (result > 300)
	result = 300;

    // duration between 6 2/3 min and 20 min
    duration = (result * 4);
    mana_cost = ((mana_cost * (result + 100)) / 200);

    if (tp != target[0])
	duration -= duration * target[0]->query_magic_res(MAGIC_I_RES_AIR) / 100;

#if DEBUG
    write("DEBUG: mortirio duration: " + duration +
      ", mana cost: " + mana_cost + "\n");
#endif

    /* here comes the action */
    FIX_EUID;
    shadow = clone_object(MORGUL_S_MORTIRIO_OBJECT);
    shadow->move(target[0], 1);
#if DEBUG
    write("DEBUG: " + file_name(shadow) + "\n");
#endif
    /*
    if (!shadow->shadow_me(target[0]))
    {
	SECURITY->do_debug("destroy",shadow);
	write("The spell did not work due to a bug, " +
	    "please make a bug report!\n");
	return 1;
    }
    */
    shadow->set_duration(duration);

    if (!is_wiz)
    {
	tp->add_mana(-mana_cost);
	remove_ingr(ingr_arr);
    }

    return 1;
}

#undef DEBUG
