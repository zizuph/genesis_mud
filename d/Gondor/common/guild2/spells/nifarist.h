/*
 * /d/Gondor/common/guild2/spells/nifarist.h
 *
 * Make Forget
 * (nif-ar-ist - face-out of-knowledge)
 * 
 * Class 1 instant spell
 * Element Air; Form Enchantment
 * Area of effect: player
 *
 * Ingredient: platinum coin, handasse
 * Mana:  50..100, depending on target's INT
 * Skills: SS_ELEMENT_AIR, SS_FORM_ENCHANTMENT, SS_SPELLCRAFT
 * Description: Makes the target to forget the name of the caster 
 * Requirements: Morgul Mage, Level >= 17
 *               mage robe must be present
 *
 * Olorin, 22-jul-1994
 */

#include <comb_mag.h>
#include <formulas.h>
#include <macros.h>
#include <tasks.h>
#include <std.h>

#include "/d/Gondor/common/guild2/lib/morgul_defs.h"
#include "/d/Gondor/common/guild2/spells/spell_defs.h"

#define MS_NIFAR_INGR     ({ "nifarist_ingr1", })
#define MS_NIFAR_MANA_BASE	50
#define MS_NIFAR_TASK     TASK_ROUTINE
#define MS_NIFAR_LIST     ({ SS_ELEMENT_AIR, SS_FORM_ENCHANTMENT, \
                             SKILL_AVG, TS_INT, SS_SPELLCRAFT, SKILL_END })
#define MS_NIFAR_VICTIM   ({ SS_ELEMENT_EARTH, SS_FORM_ABJURATION, TS_INT})

mixed
do_nifarist(string str)
{
    object  tp = this_player(),
            env = environment(tp),
           *ingr_arr,
           *target,
            robe;
    int     is_wiz = tp->query_wiz_level(),
            mana_cost,
            fail;

#if DEBUG
    is_wiz = 0;
#endif

    str = LOW(str);
    if (!stringp(str) || str == "me")
        return "You cannot cast this spell on yourself!\n";
    else
        target = parse_this(str, "[the] %l");
    if (!sizeof(target))
        return "Cast the spell at whom?\n";
    if (sizeof(target) > 1)
        return "You cannot cast the spell at more than one person!\n"; 

    if (sizeof(tp->query_weapon(-1)))
        return "You cannot cast a spell while wielding a weapon!\n";
    if (objectp(tp->query_attack()) || objectp(target[0]->query_attack()))
        return "You cannot cast this spell during a fight!\n";
    if (NPMAGIC(target[0]))
        return MORGUL_S_SPELL_FAIL;

    mana_cost = (MS_NIFAR_MANA_BASE * 
                (100 + MIN(100, target[0]->query_stat(SS_INT)))) / 100;
    if (stringp(fail = check_player(tp,
        MS_NIFAR_INGR, mana_cost, MS_NIFAR_MIN)))
        return fail;

    if (!present(MORGUL_S_GUILD_OBJECT, tp))
        return "Without your robe, you cannot cast this spell!\n";

    ingr_arr = find_ingr(MS_NIFAR_INGR, tp);

    if ((!is_wiz) && (tp->resolve_task(
        MS_NIFAR_TASK, MS_NIFAR_LIST, target[0], MS_NIFAR_VICTIM) <=
        target[0]->query_magic_res(MAGIC_I_RES_AIR)))
    {
#if DEBUG
    write("DEBUG: nifarist failed!\n");
#endif
        tp->add_mana(-(mana_cost/3));
        fail_cast(tp, ingr_arr);
        return 1;
    }
#if DEBUG
    write("DEBUG: nifarist succeeded!\n");
#endif

    tell_object(target[0], tp->query_The_name(target[0]) +
        " mumbles strange words and looks you deep into the eyes.\n" +
        "Suddenly you feel confused. You seem to have forgotten something.\n");
    /* Intentionally left showing to unseen people because of the mumbling. */
    tell_room(env, QCTNAME(tp) + " mumbles strange words and looks deep " +
        "into the eyes of " + QTNAME(target[0]) + ".\n" + QCTNAME(target[0]) +
        " suddenly looks confused and has a vacuous look.\n",
        ({ tp, target[0] }) );
    write("With the power the Dark Lord has bestowed upon you,\n" +
        "you cast Nifarist on " + target[0]->query_the_name(tp) + ",\n" +
        "praying silently: Danarist kothni nifni, Belegir Morui!\n" +
        CAP(target[0]->query_pronoun()) +
        " suddenly looks confused and has a vacuous look.\n");

/* here comes the action */
    seteuid(getuid());
    target[0]->remove_remembered(tp->query_real_name());

    if (!is_wiz)
    {
        tp->add_mana(-mana_cost);
        remove_ingr(ingr_arr);
    }

    return 1;
}
