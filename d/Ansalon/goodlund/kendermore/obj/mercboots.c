/* Boots for Jane the Mercenary, Gwyneth, June 1999
 *
 * Ported to use unarmed_enhancers to match description, Ckrik, Nov 2021
 *
 */

inherit "/std/unarmed_enhancer";
#include <wa_types.h>
#include <stdproperties.h>
#include <macros.h>

void
create_unarmed_enhancer()
{
    set_name("boots");
    set_pname(({"pairs of boots", "armours"}));
    add_name("pair of boots");
    set_adj("sharp");
    add_adj("steel-toed");
    set_short("steel-toed boots");
    set_pshort("pairs of steel-toed boots");
    set_long("The steel coverings on these boots have a sharp tip on them " + 
        "for extra damage while kicking. They reach mid-calf, and look " + 
        "well used.\n");
    set_default_enhancer(31, 32, W_BLUDGEON | W_IMPALE, 10, A_FEET, 0, this_object());
    add_prop(OBJ_I_VOLUME, 300);
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

    // We give impale hits 10% extra damage
    int extra_dam = dam / 10;
    enemy->heal_hp(-extra_dam);

    me = environment(this_object());
    us = ({ me, enemy });

    switch(phurt)
    {
    case 0..5:
        enemy->catch_msg(QCTNAME(me) + " tickles your " +
            hdesc + " with the tip of " + me->query_possessive() +
            " steel-toed boot.\n");
        me->catch_msg("You ticke " + QTPNAME(enemy) + " " + hdesc +
            " with the tip of your steel-toed boot.\n");
        me->tell_watcher(QCTNAME(me) + " tickles " +
            QTPNAME(enemy) + " " + hdesc +
            " with the tip of " + me->query_possessive() +
            " steel-toed boot.\n",
            enemy, us);
        break;
    case 6..15:
        enemy->catch_msg(QCTNAME(me) + " stabs your " +
            hdesc + " with the tip of " + me->query_possessive() +
            " steel-toed boot.\n");
        me->catch_msg("You stab " + QTPNAME(enemy) + " " + hdesc +
            " with the tip of your steel-toed boot.\n");
        me->tell_watcher(QCTNAME(me) + " stabs " +
            QTPNAME(enemy) + " " + hdesc +
            " with the tip of " + me->query_possessive() +
            " steel-toed boot.\n",
            enemy, us);
        break;
    case 16..30:
        enemy->catch_msg(QCTNAME(me) + " deeply stabs your " +
            hdesc + " with the tip of " + me->query_possessive() +
            " steel-toed boot.\n");
        me->catch_msg("You deeply stab " + QTPNAME(enemy) + " " + hdesc +
            " with the tip of your steel-toed boot.\n");
        me->tell_watcher(QCTNAME(me) + " deeply stabs " +
            QTPNAME(enemy) + " " + hdesc +
            " with the tip of " + me->query_possessive() +
            " steel-toed boot.\n",
            enemy, us);
        break;
    default:
        enemy->catch_msg(QCTNAME(me) + " viciously punctures your " +
            hdesc + " with the tip of " + me->query_possessive() +
            " steel-toed boot.\n");
        me->catch_msg("You viciously puncture " + QTPNAME(enemy) + " " + hdesc +
            " with the tip of your steel-toed boot.\n");
        me->tell_watcher(QCTNAME(me) + " viciously punctures " +
            QTPNAME(enemy) + " " + hdesc +
            " with the tip of " + me->query_possessive() +
            " steel-toed boot.\n",
            enemy, us);
        break;
    }

    return 1;
}