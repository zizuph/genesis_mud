inherit "/d/Genesis/newmagic/spell_effect_object";
inherit "/std/shadow";

#include <stdproperties.h>

#define UNSEEN_SUBLOC "_subl_unseen"
#define SW shadow_who

static private int unseen_level;

varargs public int dispel_spell_effect(object dispeller);

public int
start()
{
    int base_stat;

    set_spell_effect_desc("invisibility");

    if (!shadow_me(spell_target))
    {
        return 0;
    }

    unseen_level = spell_target->query_vamp_stat() / (75 + random(26));

    spell_target->add_mana_drain(5);
    spell_target->modify_thirst_rate(-650);
    spell_target->add_subloc(UNSEEN_SUBLOC, this_object());
    spell_target->add_prop(OBJ_I_INVIS,
        spell_target->query_prop(OBJ_I_INVIS) + unseen_level);

    spell_target->add_prop(LIVE_I_NO_FOOTPRINTS,
        spell_target->query_prop(LIVE_I_NO_FOOTPRINTS) + 1);

    set_alarm(30.0, 0.0, dispel_spell_effect);
    return 1;
}

//        set_unseen(0);

string
show_subloc(string subloc, object carrier, object for_obj)
{
    if (carrier->query_prop(TEMP_SUBLOC_SHOW_ONLY_THINGS))
    {
        return SW->show_subloc(subloc, carrier, for_obj);
    }

    if (subloc == UNSEEN_SUBLOC)
    {
        if (for_obj == carrier)
        {
            return "You are concealed in the shadows.\n";
        }

        return 0;
    }

    return SW->show_subloc(subloc, carrier, for_obj);
}

varargs public int
dispel_spell_effect(object dispeller)
{
    if (spell_target)
    {
        spell_target->add_mana_drain(-5);
        spell_target->modify_thirst_rate(650);
        spell_target->remove_subloc(UNSEEN_SUBLOC);
        spell_target->add_prop(OBJ_I_INVIS,
            spell_target->query_prop(OBJ_I_INVIS) - unseen_level);
        spell_target->add_prop(LIVE_I_NO_FOOTPRINTS,
            spell_target->query_prop(LIVE_I_NO_FOOTPRINTS) - 1);

    }

    remove_spell_effect_object();
    return 1;
}

static int
try_break_unseen(int lvl)
{
    if (lvl && (SW->power_check(lvl) > 0))
    {
        return 0;
    }

    SW->catch_tell("You are revealed.\n");
    dispel_spell_effect();
    return 1;
}

public int
break_unseen(object breaker, int dam)
{
    int light;

    if (!unseen_level)
    {
        return 0;
    }

    light = environment(SW)->query_prop(OBJ_I_LIGHT);

    if (light < 1)
    {
        /* If the room is dark, unseen might be broken by damage */
        return (dam ? try_break_unseen(dam * 2 / 3) : 0);
    }

    /* The room is light */

    if ((environment(SW)->query_prop(ROOM_I_LIGHT) > 0) ||
        (light > unseen_level))
    {
        /* If the room is "naturally" (by default) light or if the
         * light level exceeds the unseen level, unseen is broken.
         */
        return try_break_unseen(0);
    }

    /* If the room is naturally dark and the light level is less than
     * or equal to the unseen level, unseen might be broken by damage
     */
    return (dam ? try_break_unseen(dam * 2 / 3) : 0);
}

/*
 * See if unseen is broken when the caster attacks
 */
void attack_object(object ob)
{
    SW->attack_object(ob);
    break_unseen(ob, 0);
}

/*
 * See if unseen is broken when the caster is attacked
 */
void attacked_by(object ob)
{
    SW->attacked_by(ob);
    break_unseen(ob, 0);  
}

/*
 * See if unseen is broken when the caster is hit
 */
void
cr_got_hit(int hid, int ph, object att, int aid, int dt, int dam)
{
    SW->cr_got_hit(hid, ph, att, aid, dt, dam);

    if (dam > 50)
    {
        break_unseen(att, dam);
    }
}

int
query_unseen_level() { return unseen_level; }

int
query_unseen() { return !!unseen_level; }
