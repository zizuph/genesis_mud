/*
 * /d/Gondor/common/guild2/spells/arhalgul.h
 *
 * The identify spell, coded by Mercade, 23 October 1993
 * Modified for the Morgul Mages by Olorin, July 1994
 * (ar-hal-gul = out of-hiding-magic)
 * 
 * Class 1 information spell
 * Element Air; Form Enchantment
 * Area of effect: object
 *
 * Ingredient: arhal potion effect
 * Mana: 40, 20 on failure
 * Skills: SS_ELEMENT_AIR, SS_FORM_ENCHANTMENT, SS_SPELLCRAFT
 * Description: Reveals MAGIC_AM_ID_INFO to caster
 * Requirements: Morgul Mage, guild level >= 1
 *               mage robe must be present
 *
 * Mercade, 23-oct-1993
 * modified Olorin, 18-jul-1994
 *
 *      TODO: Why does the spell use enchantment and not
 *            divination? Modify so the answer is obvious.
 *
 * Modification history:
 *      Gorboth: 12-December-1997
 *          Allowed appraisal of herbs using this spell.
 *      Mercade: 10-March-1998
 *          Made spellcasting invisible if the caster is invisible.
 */

#include <cmdparse.h>
#include <comb_mag.h>
#include <formulas.h>
#include <macros.h>
#include <tasks.h>
#include <std.h>

#include "/d/Gondor/common/guild2/lib/morgul_defs.h"
#include "/d/Gondor/common/guild2/spells/spell_defs.h"

#define MS_ARHAL_INGR     ({ "arhalgul_ingr1", })
#define MS_ARHAL_MANA      40
#define MS_ARHAL_MANA_FAIL 20
#define MS_ARHAL_TASK     TASK_ROUTINE
#define MS_ARHAL_LIST     ({ SS_ELEMENT_AIR, SS_FORM_ENCHANTMENT, SKILL_AVG, \
                             SS_SPELLCRAFT, SS_APPR_OBJ, SKILL_END, TS_WIS, })
#define MS_ARHAL_VICTIM   ({MAGIC_I_RES_IDENTIFY})

mixed
do_arhalgul(string str)
{
    object  tp = this_player(),
           *ingr_arr,
            target,
           *targets;
    string  fail,
            info = "",
            msg_m, msg_n;
    int     is_wiz = tp->query_wiz_level(),
            result,
            i;
    mixed   magical_info,
            prop;

#if DEBUG
    is_wiz = 0;
#endif

    if (!strlen(str))
        return "Cast the spell on which item?\n";

    targets = FIND_STR_IN_OBJECT(str, tp) +
        FIND_STR_IN_OBJECT(str, environment(tp));
    if (!sizeof(targets))
        return "Cast the spell on which item?\n";
    else
        target = targets[0];

    if (stringp(prop = target->query_prop(OBJ_M_NO_MAGIC)))
        return prop;
    else if (prop)
        return MORGUL_S_SPELL_FAIL;

    if (sizeof(tp->query_weapon(-1)))
        return "You cannot cast a spell while wielding a weapon!\n";
    if (!present(MORGUL_S_GUILD_OBJECT, tp))
        return "Without your robe, you cannot cast this spell!\n";

    ingr_arr = find_ingr(MS_ARHAL_INGR, tp);

    if (stringp(fail = check_player(tp,
        MS_ARHAL_INGR, MS_ARHAL_MANA, MS_ARHAL_MIN)))
        return fail;

    /* those bloody wizards always have an advantage. */
    if ((!(is_wiz)) && ((result =
        (tp->resolve_task(MS_ARHAL_TASK, MS_ARHAL_LIST,
        target, MS_ARHAL_VICTIM))) <= 0))
    {
#if DEBUG
    write("DEBUG: arhalgul fail result: " + result + "\n");
#endif
        tp->add_mana(-(MS_ARHAL_MANA_FAIL));
        fail_cast(tp, ingr_arr);
        return 1;
    }
#if DEBUG
    write("DEBUG: arhalgul result: " + result + "\n");
#endif

    msg_m = "Employing Dark Sorcery, " + tp->query_met_name() +
        " casts a spell on " + ((ENV(target) == TP) ? "something" :
        "the " + check_call(target->short())) + " to reveal " +
        ((living(target)) ? POSSESSIVE(target) : "its") + " secrets.\n";
    msg_n = "Employing Dark Sorcery, " + tp->query_nonmet_name() +
        " casts a spell on " + ((ENV(target) == TP) ? "something" :
        "the " + check_call(target->short())) + " to reveal " +
        ((living(target)) ? POSSESSIVE(target) : "its") + " secrets.\n";
    tell_room(ENV(tp), ({ msg_m, msg_n, "" }), tp);
    write("Using the power the Dark Lord has bestowed upon you, " +
        "with the words \"Waro torgul! Arhalo furion rum!\", you cast " +
        "Arhalgul on the " + check_call(target->short()) + ".\n");
        
    /*
     * In his example of an object that does magical identification, Nick
     * gives only one element in the array MAGIC_AM_ID_INFO whereas I think
     * that you should get all messages below the value of your magic.
     */
    if (result < 10)
        result = 10;
    if (result > 50)
        result = 50;
    result *= 2;

    magical_info = target->query_prop(MAGIC_AM_ID_INFO);
    for (i = 0; i < sizeof(magical_info); i += 2)
    {
        if (!intp(magical_info[i + 1]))
        {
            log_file("errors", "\n\nCorrupted MAGIC_AM_ID_INFO array in "+file_name(target)+".\n\n");
            break;
        }
        if (magical_info[i + 1] <= result)
        {
            info += (string)magical_info[i];
        }
    }

    if (strlen(info))
        write(info + "\n"); /* the "\n" should be in the result string. */
    else
    {
        write("You could not reveal any hidden secrets in the " +
            check_call(target->short()) + ", but you managed to " +
            "appraise it with magic power.\n");

        /*
         *  We want to be able to identify herbs using this spell.
         */
        if (target->id("herb"))
        {
            write(target->query_id_long());
        }
        else
        {
            target->appraise_object(result + 100);
        }
    }

    if (!is_wiz)
    {
        tp->add_mana(-(MS_ARHAL_MANA));
        remove_ingr(ingr_arr);
    }

    return 1;
}
