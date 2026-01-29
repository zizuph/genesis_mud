inherit "/std/unarmed_enhancer";
#include <wa_types.h>
#include <formulas.h>
#include <stdproperties.h>
#include <macros.h>

void
create_unarmed_enhancer()
{
    set_name("boots");
    add_adj("spurred");
    add_adj("grimy");
    set_long("This pair of boots is disgusting. They may have " +
             "once been golden in colour, but it is impossible to tell " + 
             "for sure, as they are inundated with worn-in grime. " +
             "The back of each boot carries a spur, so they seem to " +
             "be used for riding.\n");
    set_short("pair of grimy spurred boots");
    set_pshort("pairs of grimy spurred boots");
    set_default_enhancer(29, 24, W_BLUDGEON | W_IMPALE, 25, A_LEGS | A_FEET, 0, this_object());
    add_prop(OBJ_I_VOLUME, 1400);
    add_prop(OBJ_I_WEIGHT, F_WEIGHT_DEFAULT_ARMOUR(25, A_LEGS));
    add_prop(OBJ_I_VALUE, F_VALUE_ARMOUR(25));
}

public varargs int
did_hit(int aid, string hdesc, int phurt, object enemy, int dt, int phit, int dam)
{
    object me, *us;
    int rc = ::did_hit(aid, hdesc, phurt, enemy, dt, phit, dam);

    if (dt != W_IMPALE || phurt <= 0)
    {
        return rc;
    }

    me = environment(this_object());
    us = ({ me, enemy });

    switch(phurt)
    {
    case 0..5:
        enemy->catch_msg(QCTNAME(me) + " pokes your " +
            hdesc + " with the dull spur of " + me->query_possessive() +
            " grimy spurred boot.\n");
        me->catch_msg("You poke " + QTPNAME(enemy) + " " + hdesc +
            " with the dull spur of your grimy spurred boot.\n");
        me->tell_watcher(QCTNAME(me) + " pokes " +
            QTPNAME(enemy) + " " + hdesc +
            " with the dull spur of " + me->query_possessive() +
            " grimy spurred boot.\n",
            enemy, us);
        break;
    case 6..15:
        enemy->catch_msg(QCTNAME(me) + " stabs your " +
            hdesc + " with the dull spur of " + me->query_possessive() +
            " grimy spurred boot.\n");
        me->catch_msg("You stab " + QTPNAME(enemy) + " " + hdesc +
            " with the dull spur of your grimy spurred boot.\n");
        me->tell_watcher(QCTNAME(me) + " stabs " +
            QTPNAME(enemy) + " " + hdesc +
            " with the dull spur of " + me->query_possessive() +
            " grimy spurred boot.\n",
            enemy, us);
        break;
    case 16..30:
        enemy->catch_msg(QCTNAME(me) + " punctures your " +
            hdesc + " with the dull spur of " + me->query_possessive() +
            " grimy spurred boot.\n");
        me->catch_msg("You puncture " + QTPNAME(enemy) + " " + hdesc +
            " with the dull spur of your grimy spurred boot.\n");
        me->tell_watcher(QCTNAME(me) + " punctures " +
            QTPNAME(enemy) + " " + hdesc +
            " with the dull spur of " + me->query_possessive() +
            " grimy spurred boot.\n",
            enemy, us);
        break;
    default:
        enemy->catch_msg(QCTNAME(me) + " forcefully impales your " +
            hdesc + " with the dull spur of " + me->query_possessive() +
            " grimy spurred boot.\n");
        me->catch_msg("You forcefully impale " + QTPNAME(enemy) + " " + hdesc +
            " with the dull spur of your grimy spurred boot.\n");
        me->tell_watcher(QCTNAME(me) + " forcefully impales " +
            QTPNAME(enemy) + " " + hdesc +
            " with the dull spur of " + me->query_possessive() +
            " grimy spurred boot.\n",
            enemy, us);
        break;
    }

    return 1;
}
