/*
 * /d/Gondor/common/guild2/spells/new/ringurth.c
 *
 * The magic shield of the Morgul Mages
 * (ring-gurth = chill-death)
 * 
 * Class 3 duration spell
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
#define MS_RINGU_TASK     TASK_SIMPLE
#define MS_RINGU_LIST     ({SKILL_AVG, SS_ELEMENT_DEATH, SS_FORM_CONJURATION,\
                            SKILL_END, SS_SPELLCRAFT})
#define MS_RINGU_AURA	  (MORGUL_SPELLS + "new/obj/ringurth_aura")

#undef  DEBUG
#define DEBUG 1

//	Prototypes
public void    ringurth_message(object caster, object *targets);
public mixed   ringurth_success(object caster, object *targets);

public void
create_spell_ringurth()
{
    set_element(SS_ELEMENT_DEATH, 10);
    set_form(SS_FORM_CONJURATION, 10);

    set_spell_time(MS_RINGU_TIME);
    set_mana_spell(MS_RINGU_MANA);

    set_spell_message(ringurth_message);
    set_spell_success(ringurth_success);
    set_find_target(find_caster_target);
    set_spell_object(MS_RINGU_AURA);

    set_ingredients(MS_RINGU_INGR);
}

public mixed
ringurth_success(object caster, object *targets)
{
    int     result;

    if ((result = caster->resolve_task(MS_RINGU_TASK, MS_RINGU_LIST)) <= 0)
        return 0;

    if (result < 60)
        result = 60;
    else if (result > 300)
        result = 300;
    set_duration(result * 5 + 300);

    return result;
}

public mixed
do_ringurth(string str)
{
    object  tp = query_caster();
    int     is_wiz = tp->query_wiz_level();

    if (sizeof(tp->query_weapon(-1)))
        return "You cannot cast a spell while wielding a weapon!\n";
    if (objectp(tp->query_attack()) && !tp->query_npc())
        return "You cannot cast this spell during a fight!\n";

    if (!present(MORGUL_S_GUILD_OBJECT, tp))
        return "Without your robe, you cannot cast this spell!\n";

    if (present("_morgul_aura", tp))
        return "The Dark Lord refuses your request, for you are already "+
          "protected!\n";

    return cast_spell();
}

public void
ringurth_message(object caster, object *targets)
{
    object  tp = query_caster(),
            env = environment(tp);

    tell_room(env, "Employing Dark Sorcery, " + QTNAME(tp) + " calls the Chill of Death.\n" +
        "A cloud appears and envelopes " + tp->query_objective() + ".\n", tp);
    tp->catch_msg("With the power the Dark Lord has bestowed upon you, you call the Chill of Death.\n" +
        "A cloud appears and envelopes you.\n");

#if 0
    seteuid(getuid());
    cloud = clone_object(MORGUL_SPELL_OBJS + "aura");
    cloud->add_prop("_morgul_s_caster", tp->query_real_name());
/* duration from 5 min to 20 min */
    cloud->move(tp);
#endif

    tell_room(env, QCTNAME(tp) + " casts a spell successfully.\n", tp);
    tp->catch_msg("You cast the spell successfully.\n");
}

