/*
 * /d/Gondor/common/guild2/spells/ringurth.h
 *
 * The magic shield of the Morgul Mages
 * (ring-gurth = chill-death)
 * 
 * Class ??? duration spell
 * Element Death, Form Abjuration
 * Area of effect: caster.
 *
 * Ingredient: frostheal potion and ginger or fennel
 * Mana: 50
 * Skills: SS_ELEMENT_DEATH, SS_FORM_CONJURATION, SS_SPELLCRAFT
 * Description: increased armour protection
 *              duration 5 to 20 min
 *              
 * Requirements: Morgul Mage, morgul level > 9
 *
 * Xeros, 10-jun-1994
 */

#include <macros.h>
#include <stdproperties.h>
#include <tasks.h>

#include "/d/Gondor/common/guild2/lib/morgul_defs.h"

#define MS_RINGU_INGR     ({ "ringurth_ingr1", "ringurth_ingr2" })
#define MS_RINGU_MANA      50
#define MS_RINGU_TASK     TASK_ROUTINE
#define MS_RINGU_LIST     ({ SS_ELEMENT_DEATH, SS_FORM_CONJURATION, SS_SPELLCRAFT})

mixed
do_ringurth(string str)
{
    object  tp = this_player(),
            env = environment(tp),
           *ingr_arr,
            cloud;
    int     is_wiz = tp->query_wiz_level(),
            fail,
            result;
    string  msg_m,
            msg_n;

#if DEBUG
    is_wiz = 0;
#endif

    if (sizeof(tp->query_weapon(-1)))
        return "You cannot cast a spell while wielding a weapon!\n";
    if (objectp(tp->query_attack()) && !tp->query_npc())
        return "You cannot cast this spell during a fight!\n";

    if (!present(MORGUL_S_GUILD_OBJECT, tp))
        return "Without your robe, you cannot cast this spell!\n";

    if (stringp(fail = check_player(tp, MS_RINGU_INGR, MS_RINGU_MANA, MS_RINGU_MIN)))
        return fail;
    if(present("_morgul_aura",tp))
    { 
        write("The Dark Lord refuses your request, for you are already "+
          "protected!\n");
        return 1;
    }

    ingr_arr = find_ingr(MS_RINGU_INGR, tp);

    if (!is_wiz &&
        (result = tp->resolve_task(MS_RINGU_TASK, MS_RINGU_LIST)) <= 0)
    {
#if DEBUG
    write("DEBUG: ringurth result: " + result + "\n");
#endif
        tp->add_mana(-(MS_RINGU_MANA/3));
        fail_cast(tp, ingr_arr);
        return 1;
    }
#if DEBUG
    write("DEBUG: ringurth result: " + result + "\n");
#endif

    msg_m = "Employing Dark Sorcery, " + tp->query_met_name() + " calls " +
        "the Chill of Death.\nA cloud appears and envelopes " +
        tp->query_objective() + ".\n";
    msg_n = "Employing Dark Sorcery, the " + tp->query_nonmet_name() +
        " calls the Chill of Death.\nA cloud appears and envelopes " +
        tp->query_objective() + ".\n";
    say( ({ msg_m, msg_n }) );
    write("With the power the Dark Lord has bestowed upon you, you call " +
        "the Chill of Death.\nA cloud appears and envelopes you.\n");

    if (result < 60)
        result = 60;
    else if (result > 300)
        result = 300;

    seteuid(getuid());
    cloud = clone_object(MORGUL_SPELL_OBJS + "aura");
    cloud->add_prop("_morgul_s_caster", tp->query_real_name());
/* duration from 5 min to 20 min */
    cloud->set_duration(result * 5 + 1200);
    cloud->move(tp);

    if (!is_wiz)
    {
        tp->add_mana(-MS_RINGU_MANA);
        remove_ingr(ingr_arr);
    }

    msg_m = tp->query_met_name() + " casts a spell successfully.\n";
    msg_n = "The " + tp->query_nonmet_name() +
        " casts a spell successfully.\n";
    say( ({ msg_m, msg_n }) );
    write("You cast the spell successfully.\n");
    return 1;
}
