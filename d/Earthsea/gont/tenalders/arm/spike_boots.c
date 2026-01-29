#pragma strict_types

/*
 * Allow the boots to enhance hit/pen Ckrik Oct, 2021
 *
 */

inherit "/std/unarmed_enhancer";

#include <stdproperties.h>
#include <wa_types.h>
#include <macros.h>

public void
create_unarmed_enhancer()
{
    set_name("boots");
    add_name("pair of spiked boots");
    set_pname("pairs of spiked boots");
    set_pshort("pairs of spiked boots");
    set_adj(({"spiked", "tough", "leather"}));
    set_short("pair of spiked boots");
    set_long("A pair of tough leather boots "+
        "which have a sharp bronze spike protruding from the big toe. "+
        "The soles and heels are reinforced with bronze plate.\n");
    set_default_enhancer(29, 29, W_BLUDGEON | W_IMPALE, 25, A_FEET | A_LEGS, 0, this_object());
    add_prop(OBJ_I_WEIGHT,  900);
    add_prop(OBJ_I_VOLUME, 500);
    add_prop(OBJ_I_VALUE, 400 + random(50));
}

public varargs int
did_hit(int aid, string hdesc, int phurt, object enemy, int dt, int phit, int dam)
{
    object me, *us;
    int enemy_is_undead;
    int rc;

    rc = ::did_hit(aid, hdesc, phurt, enemy, dt, phit, dam);

    if (dt != W_IMPALE)
    {
        return rc;
    }

    // Custom combat message for W_IMPALE
    me = environment(this_object());
    us = ({ me, enemy });
    enemy_is_undead = enemy->query_property(LIVE_I_UNDEAD);

    switch(phurt)
    {
    case -1:
        // defense
        enemy->catch_msg(QCTNAME(me) + " attempts to stab you with the spike " +
            "of " + me->query_possessive() + " spiked boot " +
            "and " + me->query_possessive() + " kick misses your " + hdesc +
            " as you move away from the kick.\n");
        me->catch_msg("You attempt to stab " + QTNAME(enemy) + " with the spike " +
            "of your spiked boot " +
            "and your kick misses " + enemy->query_possessive() + " " + hdesc +
            " as " + enemy->query_pronoun() + " moves away from the kick.\n");
        me->tell_watcher(QCTNAME(me) + " attempts to stab " + QTNAME(enemy) + 
            " with the spike of " + me->query_possessive() +
            " spiked boot and " + me->query_possessive() +
            " kick misses " + QTPNAME(enemy) + " " + hdesc +
            " as " + enemy->query_pronoun() + " moves away from the kick.\n",
            enemy, us);
        break;
    case -2:
        // parry
        enemy->catch_msg(QCTNAME(me) + " attempts to stab you with the spike " +
            "of " + me->query_possessive() + " spiked boot " +
            "and you parry the kick safely away from your " + hdesc + ".\n");
        me->catch_msg("You attempt to stab " + QTNAME(enemy) + " with the spike " +
            "of your spiked boot " +
            "and " + QTNAME(enemy) + " parries your kick away from " +
            enemy->query_possessive() + " " + hdesc + ".\n");
        me->tell_watcher(QCTNAME(me) + " attempts to stab " + QTNAME(enemy) + 
            " with the spike of " + me->query_possessive() +
            " spiked boot and " + QTNAME(enemy) + " parries the " +
            " kick safely away from " + enemy->query_pronoun() + " " + hdesc + ".\n",
            enemy, us);
        break;
    case -3:
        // acrobat
        enemy->catch_msg(QCTNAME(me) + " attempts to stab you with the spike " +
            "of " + me->query_possessive() + " spiked boot " +
            "and " + me->query_possessive() + " kick misses your " + hdesc +
            " as you backflip away from the kick.\n");
        me->catch_msg("You attempt to stab " + QTNAME(enemy) + " with the spike " +
            "of your spiked boot " +
            "and your kick misses " + enemy->query_possessive() + " " + hdesc +
            " as " + enemy->query_pronoun() + " backflips away from the kick.\n");
        me->tell_watcher(QCTNAME(me) + " attempts to stab " + QTNAME(enemy) + 
            " with the spike of " + me->query_possessive() +
            " spiked boot and " + me->query_possessive() +
            " kick misses " + QTPNAME(enemy) + " " + hdesc +
            " as " + enemy->query_pronoun() + " backflips away from the kick.\n",
            enemy, us);
        break;
    case 0..5:
        if (enemy_is_undead)
        {
            enemy->catch_msg(QCTNAME(me) + " pokes your " +
                hdesc + " with the spike of " + me->query_possessive() +
                " spiked boot.\n");
            me->catch_msg("You poke " + QTPNAME(enemy) + " " + hdesc +
                " with the spike of your spiked boot.\n");
            me->tell_watcher(QCTNAME(me) + " pokes " +
                QTPNAME(enemy) + " " + hdesc +
                " with the spike of " + me->query_possessive() +
                " spiked boot.\n",
                enemy, us);
        }
        else
        {
            enemy->catch_msg(QCTNAME(me) + " pokes your " +
                hdesc + " with the spike of " + me->query_possessive() +
                " spiked boot, drawing a trickle of blood.\n");
            me->catch_msg("You poke " + QTPNAME(enemy) + " " + hdesc +
                " with the spike of your spiked boot, drawing a trickle of blood.\n");
            me->tell_watcher(QCTNAME(me) + " pokes " +
                QTPNAME(enemy) + " " + hdesc +
                " with the spike of " + me->query_possessive() +
                " spiked boot, drawing a trickle of blood.\n",
                enemy, us);
        }
        break;
    case 6..15:
        if (enemy_is_undead)
        {
            enemy->catch_msg(QCTNAME(me) + " stabs your " +
                hdesc + " with the spike of " + me->query_possessive() +
                " spiked boot.\n");
            me->catch_msg("You stab " + QTPNAME(enemy) + " " + hdesc +
                " with the spike of your spiked boot.\n");
            me->tell_watcher(QCTNAME(me) + " stabs " +
                QTPNAME(enemy) + " " + hdesc +
                " with the spike of " + me->query_possessive() +
                " spiked boot.\n",
                enemy, us);
        }
        else
        {
            enemy->catch_msg(QCTNAME(me) + " stabs your " +
                hdesc + " with the spike of " + me->query_possessive() +
                " spiked boot, drawing some blood.\n");
            me->catch_msg("You stab " + QTPNAME(enemy) + " " + hdesc +
                " with the spike of your spiked boot, drawing some blood.\n");
            me->tell_watcher(QCTNAME(me) + " stabs " +
                QTPNAME(enemy) + " " + hdesc +
                " with the spike of " + me->query_possessive() +
                " spiked boot, drawing some blood.\n",
                enemy, us);
        }
        break;
    case 16..30:
        if (enemy_is_undead)
        {
            enemy->catch_msg(QCTNAME(me) + " deeply stabs your " +
                hdesc + " with the spike of " + me->query_possessive() +
                " spiked boot.\n");
            me->catch_msg("You deeply stab " + QTPNAME(enemy) + " " + hdesc +
                " with the spike of your spiked boot.\n");
            me->tell_watcher(QCTNAME(me) + " deeply stabs " +
                QTPNAME(enemy) + " " + hdesc +
                " with the spike of " + me->query_possessive() +
                " spiked boot.\n",
                enemy, us);
        }
        else
        {
            enemy->catch_msg(QCTNAME(me) + " deeply stabs your " +
                hdesc + " with the spike of " + me->query_possessive() +
                " spiked boot, drawing some blood.\n");
            me->catch_msg("You deeply stab " + QTPNAME(enemy) + " " + hdesc +
                " with the spike of your spiked boot, drawing some blood.\n");
            me->tell_watcher(QCTNAME(me) + " deeply stabs " +
                QTPNAME(enemy) + " " + hdesc +
                " with the spike of " + me->query_possessive() +
                " spiked boot, drawing major amounts blood.\n",
                enemy, us);
        }
        break;
    default:
        if (enemy_is_undead)
        {
            enemy->catch_msg(QCTNAME(me) + " viciously punctures your " +
                hdesc + " with the spike of " + me->query_possessive() +
                " spiked boot.\n");
            me->catch_msg("You viciously puncture " + QTPNAME(enemy) + " " + hdesc +
                " with the spike of your spiked boot.\n");
            me->tell_watcher(QCTNAME(me) + " viciously punctures " +
                QTPNAME(enemy) + " " + hdesc +
                " with the spike of " + me->query_possessive() +
                " spiked boot.\n",
                enemy, us);
        }
        else
        {
            enemy->catch_msg(QCTNAME(me) + " viciously punctures your " +
                hdesc + " with the spike of " + me->query_possessive() +
                " spiked boot, blood sprays all over.\n");
            me->catch_msg("You viciously puncture " + QTPNAME(enemy) + " " + hdesc +
                " with the spike of your spiked boot, blood sprays all over.\n");
            me->tell_watcher(QCTNAME(me) + " viciously punctures " +
                QTPNAME(enemy) + " " + hdesc +
                " with the spike of " + me->query_possessive() +
                " spiked boot, blood sprays all over.\n",
                enemy, us);
        }
        break;
    }

    if(enemy->query_hp() <= 0)
    {
        if (enemy_is_undead)
        {
            enemy->catch_msg("You die!\n");
            tell_room(environment(me), QCTNAME(enemy) + " dies!\n",
                ({ enemy }));
        }
        else
        {
            enemy->catch_msg("The spray of blood turns into a torrent and you die!\n");
            tell_room(environment(me), "The spray of blood from " + QTNAME(enemy) +
                " turns into a torrent and " + enemy->query_pronoun() + " dies!\n",
                ({ enemy }));
        }
        enemy->do_die(me);
    }

    return 1;   
}