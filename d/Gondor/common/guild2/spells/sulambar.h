/*
 * /d/Gondor/common/guild2/spells/sulambar.h
 *
 * The poison cloud of the Morgul Mages
 * (sul-ambar = wind-doom)
 * 
 * Class 3 duration spell
 * Element Air, Form Conjuration
 * Area of effect: location
 *
 * Ingredient: hemlock
 * Mana: 180
 * Skills: SS_ELEMENT_AIR, SS_FORM_CONJURATION, SS_SPELLCRAFT
 * Description: Creates a poison cloud in the room, all
 *              livings in that room are effected
 *              protects caster against effects of the cloud
 * Requirements: Morgul Mage, guild level >= 21
 *               must have quaffed nenamarth potion
 *
 * Olorin, 12-jan-1994
 *
 * Elessar, Oct 11th 1995- Added logging to /d/Gondor/log/curses
 */

#include <comb_mag.h>
#include <macros.h>
#include <stdproperties.h>
#include <tasks.h>

#include "/d/Gondor/common/guild2/lib/morgul_defs.h"

#define MS_SULAM_INGR     ({ "sulambar_ingr1", "sulambar_ingr2", })
#define MS_SULAM_MANA     180
#define MS_SULAM_TASK     TASK_ROUTINE
#define MS_SULAM_LIST     ({ SS_ELEMENT_AIR, SS_FORM_CONJURATION, SS_SPELLCRAFT})

mixed
do_sulambar(string str)
{
    object  tp = this_player(),
    env = environment(tp),
    *ingr_arr,
    cloud,
    obj;
    int     is_wiz = tp->query_wiz_level(),
    fail,
    result;
    string  msg_m,
    msg_n;

#if DEBUG
    is_wiz = 0;
#endif

    // magic check
    if ((env) && (RNATTACK(env) || RNMATTACK(env)))
	return MORGUL_S_SPELL_FAIL;

    if (objectp(tp->query_attack()) && (!tp->query_npc()))
	return "You cannot cast this spell during a fight!\n";
    if (sizeof(tp->query_weapon(-1)) && (!tp->query_npc()))
	return "You cannot cast a spell while wielding a weapon!\n";

    if (!present(MORGUL_S_GUILD_OBJECT, tp))
	return "Without your robe, you cannot cast this spell!\n";

#if MULTI_CASTING
    if ((!objectp(present(MORGUL_S_NENAMARTH_EFFECT_NAME, tp))) &&
      (!tp->query_npc()))
	return "You are not properly prepared to cast this spell!\n";
#endif

    if (stringp(fail = check_player(tp, MS_SULAM_INGR, MS_SULAM_MANA,
	  MS_SULAM_MIN)))
	return fail;

    ingr_arr = find_ingr(MS_SULAM_INGR, tp);

    if (!is_wiz &&
      (result = tp->resolve_task(MS_SULAM_TASK, MS_SULAM_LIST)) <= 0)
    {
#if DEBUG
	write("DEBUG: sulambar result: " + result + "\n");
#endif
	tp->add_mana(-(MS_SULAM_MANA/3));
	fail_cast(tp, ingr_arr);
	return 1;
    }
#if DEBUG
    write("DEBUG: sulambar result: " + result + "\n");
#endif

    say("Employing Dark Sorcery, " + QTNAME(tp) + " calls the Wind of " +
      "Doom.\nA few inches in front of " + HIM(tp) + ", a dark dense " +
      "cloud appears.\nThe cloud forms an almost perfect sphere and " +
      "grows quickly.\nWhen the cloud is threatening to envelope " +
      HIM(tp) + ", " + QTNAME(tp) + " makes a quick gesture " +
      "with both arms.\nQuickly the cloud turns into a pale yellow " +
      "colour and spreads into the surroundings.\n");
    write("With the power the Dark Lord has bestowed upon you, you call " +
      "the Wind of Doom.\nA few inches in front of your eyes, a dense " +
      "dark cloud appears.\nThe cloud forms almost a perfect sphere and " +
      "grows quickly.\nWhen the cloud is threatening to envelope you, you " +
      "make a quick gesture with both arms.\nQuickly the cloud turns " +
      "into a pale yellow colour and spreads into the surroundings.\n");

    if (result < 20)
	result = 20;
    else if (result > 100)
	result = 100;

    seteuid(getuid());

    obj = clone_object(MORGUL_SPELL_OBJS + "ephessul_ob");
    obj->add_prop("_morgul_s_caster", tp->query_real_name());
    if (obj->move(tp))
	obj->move(tp,1);
    obj->set_time(6*result + 360);

    cloud = clone_object("/d/Gondor/common/guild2/spells/obj/sulambar_cloud");
    cloud->add_prop("_morgul_s_caster", tp->query_real_name());
    cloud->set_time(2*result + 100, 3);
    if (cloud->move(env))
	cloud->move(env, 1);
    if (!is_wiz)
    {
	tp->add_mana(-MS_SULAM_MANA);
	remove_ingr(ingr_arr);
    }

    msg_m = tp->query_met_name() + " casts a spell successfully.\n";
    msg_n = "The " + tp->query_nonmet_name() +
    " casts a spell successfully.\n";
    say( ({ msg_m, msg_n }) );
    write("You cast the spell successfully.\n");

    log_file("curses", tp->query_name() + " cast a Sulambar cloud in " +
      file_name(env) + ", " + ctime(time()) + ".\n");
    log_file("mm_player_fight", tp->query_name() + " cast a Sulambar cloud in " +
      file_name(env) + ", " + ctime(time()) + ".\n");

    return 1;
}
