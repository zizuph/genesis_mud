/*
 * /d/Gondor/common/guild2/spells/ephessul.h
 *
 * Protects vs poison cloud of the Morgul Mages
 * (ephel-sul = fence-wind)
 * 
 * Class 2 duration spell
 * Element Air; Form Enchantment
 * Area of effect: living target
 *
 * Ingredient: foxglove, myrtle
 * Mana: 50 (25 for self)
 * Skills: SS_ELEMENT_AIR, SS_FORM_ENCHANTMENT
 * Description: Protects the target against the sulambar poison cloud,
 *              adds magic resistance MAGIC_I_POISON_RES of 40 (additive)
 * Requirements: Morgul Mage, morgul level > 13
 *               mage robe must be present
 *
 * Olorin, 18-jan-1994
 */

#include <comb_mag.h>
#include <macros.h>
#include <tasks.h>

#include "/d/Gondor/common/guild2/lib/morgul_defs.h"
#include "/d/Gondor/common/guild2/spells/spell_defs.h"

#define MS_EPHES_INGR     ({ "ephessul_ingr1", })
#define MS_EPHES_MANA      50
#define MS_EPHES_TASK     TASK_SIMPLE
#define MS_EPHES_LIST     ({ SS_ELEMENT_AIR, SS_FORM_ENCHANTMENT, SS_SPELLCRAFT})

mixed
do_ephessul(string str)
{
    object  tp = this_player(),
            env = environment(tp),
           *ingr_arr,
           *target,
            robe,
            obj;
    int     is_wiz = tp->query_wiz_level(),
            fail,
            result;
    string  he,
            his;

#if DEBUG
    is_wiz = 0;
#endif

    if (!strlen(str))
        str = "me";

    str = LOW(str);
    if (str == "me" || str == tp->query_real_name())
        target = ({ tp });
    else
        target = parse_this(str, "[the] %l");
    if (!sizeof(target))
        return "Cast the spell at whom?\n";
    if (sizeof(target) > 1)
        return "You cannot cast the spell at more than one person!\n"; 

/* magic check */
    if (NPMAGIC(target[0]))
        return MORGUL_S_SPELL_FAIL;

    if (sizeof(tp->query_weapon(-1)))
        return "You cannot cast a spell while wielding a weapon!\n";
    if (objectp(tp->query_attack()) || objectp(target[0]->query_attack()))
        return "You cannot cast this spell during a fight!\n";
    if (stringp(fail = check_player(tp, MS_EPHES_INGR, MS_EPHES_MANA,
        MS_EPHES_MIN)))
        return fail;

    if (!present(MORGUL_S_GUILD_OBJECT, tp))
        return "Without your robe, you cannot cast this spell!\n";

    ingr_arr = find_ingr(MS_EPHES_INGR, tp);

    if (!is_wiz &&
        (result = tp->resolve_task(MS_EPHES_TASK, MS_EPHES_LIST)) <= 0)
    {
#if DEBUG
    write("DEBUG: ephessul result: " + result + "\n");
#endif
        if (target[0] == tp)
            tp->add_mana(-(MS_EPHES_MANA/6));
        else
            tp->add_mana(-(MS_EPHES_MANA/3));
        fail_cast(tp, ingr_arr);
        return 1;
    }
#if DEBUG
    write("DEBUG: ephessul result: " + result + "\n");
#endif

    he = tp->query_pronoun();
    his = tp->query_possessive();
    if (target[0] != tp)
    {
        tell_object(target[0], "Employing Dark Sorcery, " +
            tp->query_the_name(target[0]) + " calls upon the Power of " +
            "Sauron.\n" + CAP(he) + " throws " + his + " black robe over " +
            "your head, mumbling a few words.\nFor a short moment, the " +
            "robe seems to shine with a pale green glow.\nThen " +
            tp->query_the_name(target[0]) + " throws back the robe and " +
            "looks at you confidently.\n");
    }
    tell_room(env, "Employing Dark Sorcery, " + QTNAME(tp) +
        " calls upon the Power of Sauron.\n" + CAP(he) + " throws " + his +
        " black robe over " + ((target[0] == tp) ? (his + " head") :
        ("the head of " + QTNAME(target[0]))) + ", and mumbles a few " +
        "words.\nFor a short moment, the robe seems to shine with a pale " +
        "green glow.\n" + QCTNAME(tp) + " throws back the robe and looks " +
        "around menacingly.\n", ({ tp, target[0] }) );
    write("With the power the Dark Lord has bestowed upon you, you call " +
        "the Windfence.\nYou throw your robe over " + ((target[0] == tp) ?
        "your head" : ("the head of " + target[0]->query_the_name(tp))) +
        ", and mumble the dark words:\n\t'Telio, ephessul, berio bior " +
        "Beleghir Morui'\nFor a short moment, the robe seems to shine " +
        "with a pale green glow.\nThen you throw back the cloak again, " +
        "having summoned the Windfence!\n");

    if (result < 20)
        result = 20;
    else if (result > 100)
        result = 100;

    seteuid(getuid());
    obj = clone_object(MORGUL_SPELL_OBJS + "ephessul_ob");
    obj->add_prop("_morgul_s_caster", tp->query_real_name());
    if (obj->move(target[0]))
        obj->move(target[0],1);
    obj->set_time(12*result + 120);

    if (!is_wiz)
    {
        if (target[0] == tp)
            tp->add_mana(-(MS_EPHES_MANA/2));
        else
            tp->add_mana(-MS_EPHES_MANA);
        remove_ingr(ingr_arr);
    }

    tell_room(env, QCTNAME(tp) + " casts a spell successfully.\n", tp);
    write("You cast the spell successfully.\n");
    return 1;
}
