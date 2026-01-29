/*
 * /d/Gondor/common/guild2/spells/artirith.h
 *
 * Makes the caster invisible for some duration
 * (ar-tirith = out of sight)
 * 
 * Class 2 duration spell
 * Element Air; Form Enchantment
 * Area of effect: caster
 *
 * Ingredient: curugwath, lominen potion effect
 * Mana: 100
 * Skills: SS_ELEMENT_AIR, SS_FORM_TRANSMUTATION
 * Description: the caster will become invisible
 *              duration: 10 - 26 min
 *              or until the caster starts combat or picks something up
 * Requirements: Morgul Mage, guild level > 12
 *               mage robe must be present
 *
 * Olorin, 01-nov-1994
 */

#include <comb_mag.h>
#include <macros.h>
#include <tasks.h>

#include "/d/Gondor/common/guild2/lib/morgul_defs.h"
#include "/d/Gondor/common/guild2/spells/spell_defs.h"

#define MS_ARTIR_INGR     ({ "artirith_ingr1", })
#define MS_ARTIR_MANA      100
#define MS_ARTIR_TASK     TASK_ROUTINE
#define MS_ARTIR_LIST     ({ SS_ELEMENT_AIR, SS_FORM_TRANSMUTATION, SS_SPELLCRAFT})

#undef DEBUG
#define DEBUG 0

mixed
do_artirith(string str)
{
    object  tp = this_player(),
            env = environment(tp),
           *ingr_arr,
            robe,
            obj;
    int     is_wiz = tp->query_wiz_level(),
            fail,
            result;
    string  msg_m,
            msg_n;

#if DEBUG
    is_wiz = 0;
#endif

    str = LOW(str);
    if (strlen(str) &&
        (str != "me") &&
        (str != tp->query_real_name()))
    {
        return "You can cast the spell only on yourself!\n";
    }

/* magic check */
    if (NPMAGIC(tp))
        return MORGUL_S_SPELL_FAIL;

    if (tp->query_artirith_active())
        return "You are already within the realm of shadows!\n";
    if (sizeof(tp->query_weapon(-1)))
        return "You cannot cast a spell while wielding a weapon!\n";
    if (objectp(tp->query_attack()))
        return "You cannot cast this spell during a fight!\n";
    if (stringp(fail = check_player(tp, MS_ARTIR_INGR, MS_ARTIR_MANA,
        MS_ARTIR_MIN)))
        return fail;

    if (!present(MORGUL_S_GUILD_OBJECT, tp))
        return "Without your robe, you cannot cast this spell!\n";

    ingr_arr = find_ingr(MS_ARTIR_INGR, tp);

    if (!is_wiz &&
        (result = tp->resolve_task(MS_ARTIR_TASK, MS_ARTIR_LIST)) <= 0)
    {
#if DEBUG
    write("DEBUG: artirith result: " + result + "\n");
#endif
        tp->add_mana(-(MS_ARTIR_MANA/3));
        fail_cast(tp, ingr_arr);
        return 1;
    }
#if DEBUG
    write("DEBUG: artirith result: " + result + "\n");
#endif

    msg_m = "Employing Dark Sorcery, " + tp->query_met_name() +
        " calls upon the Power of Sauron.\n" + CAP(tp->query_pronoun()) +
        " throws " + tp->query_possessive() + " black robe over " +
        tp->query_possessive() +
        " head, mumbles a few words, and fades from your view.\n";
    msg_n = "Employing Dark Sorcery, " + tp->query_nonmet_name() +
        " calls upon the Power of Sauron.\n" + CAP(tp->query_pronoun()) +
        " throws " + tp->query_possessive() + " black robe over " +
        tp->query_possessive() +
        " head, mumbles a few words, and fades from your view.\n";
    tell_room(env, ({ msg_m, msg_n }), tp);
    write("With the power the Dark Lord has bestowed upon you, you call " +
        "Artirith. You throw your robe over your head, and mumble the " +
        "dark words:\n\t'Noro nin minna fuine, ar tirith ketymi!'\n" +
        "You have entered the realm of shadows now!\n");

    if (result < 20)
        result = 20;
    else if (result > 100)
        result = 100;

    msg_m = tp->query_met_name() + " casts a spell successfully.\n";
    msg_n = "The " + tp->query_nonmet_name() +
        " casts a spell successfully.\n";
    tell_room(env, ({ msg_m, msg_n }), tp);
    write("You cast the spell successfully.\n");

    FIX_EUID;
    obj = clone_object(MORGUL_SPELL_OBJS + "artirith_shadow");

    if (!obj->shadow_me(tp))
    {
        SECURITY->do_debug("destroy", obj);
        write("The spell did not work due to a bug, " +
            "please make a bug report!\n");
        return 1;
    }
    obj->set_time(12 * result + 360);

    if (!is_wiz)
    {
        tp->add_mana(-(MS_ARTIR_MANA));
        remove_ingr(ingr_arr);
    }
    return 1;
}
