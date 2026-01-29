#pragma strict_types

/*
 * Redid long desc and added kick emote Ckrik March, 2004
 * 
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
    set_pname(({"bootses"}));
    set_adj(({"embossed", "bronze"}));
    set_short("pair of embossed bronze boots");
    set_pshort("pairs of embossed bronze boots");
    set_long("The " +query_short()+ 
        " are covered in embossed patterns swirling " +
        "along the soles to the tips of the boots. The long and thin " +
        "stiletto heels form lines rising elegantly to the " +
        "thigh high tops of the boots. They look very strong " +
        "yet feminine.\n");

    set_default_enhancer(39, 39, W_BLUDGEON | W_IMPALE, 38, A_FEET | A_LEGS, 0, this_object());
    
    add_prop(OBJ_I_VALUE, 950);
    add_prop(OBJ_I_WEIGHT, 550);
    add_prop(OBJ_I_VOLUME, 250);
}

public int
kick(string str)
{
    object target, tp;

    tp = this_player();
    if (parse_command(str, environment(tp), "%o", target))
    {
        if (living(target))
    {
        tp->catch_msg("You kick " + QTNAME(target) + ", digging the thin " +
            "stiletto of your embossed bronze boot into " + 
            target->query_objective() + ", " +
            "and leaving " + target->query_objective() + 
            " reeling in pain.\n");
        target->catch_msg(QCTNAME(tp) + " kicks you, " + 
            "digging the thin stiletto of " + 
            tp->query_possessive() +
            " embossed bronze boot into " + 
            "you, and leaving you reeling in pain.\n");
        tell_room(environment(tp),
            QCTNAME(tp) + " kicks " + QTNAME(target) + ", " +
            "digging the thin stiletto of " + tp->query_possessive() +
            " embossed bronze boot into " + 
            target->query_objective() + ", and leaving " +
            target->query_objective() + " reeling in pain.\n",
            ({target, tp}));
    }
    else
    {
        tp->catch_msg("You kick the " + target->short() +
            " with the tip " +
            "your embossed bronze boot.\n");
        tell_room(environment(tp), 
            QCTNAME(tp) + " kicks the " + target->short() + 
            " with the tip of " + tp->query_possessive() + " " +
            "embossed bronze boot.\n",
            tp);
    }
      return 1;
    }

    notify_fail("Kick whom/what?\n");
    return 0;
}

public mixed 
wear(object obj)
{
  object tp = this_player();

  switch (tp->query_race())
    {
    case "half-elf":
    case "elf":
    case "human":
        write("You wear the " + query_short() + " and the rest " +
            "of the world looks a bit shorter to you.\n");
        say(QCTNAME(tp) + " wears the " + query_short() + " and becomes " +
            "quite a bit taller.\n");
        return 1;
    case "hobbit":
    case "kender":
    case "dwarf":
    case "gnome":
    case "goblin":
    case "hobgoblin":
    case "orc":
        return "Your legs are too short to wear the " + query_short() + ".\n";
    case "ogre":
    case "minotaur":
        return "You find your legs far too big for these tiny boots.\n";
    default:
        return "You are not able to fit into the " + query_short() +
            "properly.\n";
    }
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
        enemy->catch_msg(QCTNAME(me) + " attempts to stab you with the stiletto " +
            "heel of " + me->query_possessive() + " embossed bronze boot " +
            "and " + me->query_possessive() + " kick misses your " + hdesc +
            " as you move away from the kick.\n");
        me->catch_msg("You attempt to stab " + QTNAME(enemy) + " with the stiletto " +
            "heel of your embossed bronze boot " +
            "and your kick misses " + enemy->query_possessive() + " " + hdesc +
            " as " + enemy->query_pronoun() + " moves away from the kick.\n");
        me->tell_watcher(QCTNAME(me) + " attempts to stab " + QTNAME(enemy) + 
            " with the stiletto heel of " + me->query_possessive() +
            " embossed bronze boot and " + me->query_possessive() +
            " kick misses " + QTPNAME(enemy) + " " + hdesc +
            " as " + enemy->query_pronoun() + " moves away from the kick.\n");
        break;
    case -2:
        // parry
        enemy->catch_msg(QCTNAME(me) + " attempts to stab you with the stiletto " +
            "heel of " + me->query_possessive() + " embossed bronze boot " +
            "and you parry the kick safely away from your " + hdesc + ".\n");
        me->catch_msg("You attempt to stab " + QTNAME(enemy) + " with the stiletto " +
            "heel of your embossed bronze boot " +
            "and " + QTNAME(enemy) + " parries your kick away from " +
            enemy->query_possessive() + " " + hdesc + ".\n");
        me->tell_watcher(QCTNAME(me) + " attempts to stab " + QTNAME(enemy) + 
            " with the stiletto heel of " + me->query_possessive() +
            " embossed bronze boot and " + QTNAME(enemy) + " parries the " +
            " kick safely away from " + enemy->query_pronoun() + " " + hdesc + ".\n",
            enemy, us);
        break;
    case -3:
        // acrobat
        enemy->catch_msg(QCTNAME(me) + " attempts to stab you with the stiletto " +
            "heel of " + me->query_possessive() + " embossed bronze boot " +
            "and " + me->query_possessive() + " kick misses your " + hdesc +
            " as you backflip away from the kick.\n");
        me->catch_msg("You attempt to stab " + QTNAME(enemy) + " with the stiletto " +
            "heel of your embossed bronze boot " +
            "and your kick misses " + enemy->query_possessive() + " " + hdesc +
            " as " + enemy->query_pronoun() + " backflips away from the kick.\n");
        me->tell_watcher(QCTNAME(me) + " attempts to stab " + QTNAME(enemy) + 
            " with the stiletto heel of " + me->query_possessive() +
            " embossed bronze boot and " + me->query_possessive() +
            " kick misses " + QTPNAME(enemy) + " " + hdesc +
            " as " + enemy->query_pronoun() + " backflips away from the kick.\n",
            enemy, us);
        break;
    case 0..5:
        if (enemy_is_undead)
        {
            enemy->catch_msg(QCTNAME(me) + " pokes your " +
                hdesc + " with the stiletto heel of " + me->query_possessive() +
                " embossed bronze boot.\n");
            me->catch_msg("You poke " + QTPNAME(enemy) + " " + hdesc +
                " with the stiletto " +
                "heel of your embossed bronze boot.\n");
            me->tell_watcher(QCTNAME(me) + " pokes " +
                QTPNAME(enemy) + " " + hdesc +
                " with the stiletto heel of " + me->query_possessive() +
                " embossed bronze boot.\n",
                enemy, us);
        }
        else
        {
            enemy->catch_msg(QCTNAME(me) + " pokes your " +
                hdesc + " with the stiletto heel of " + me->query_possessive() +
                " embossed bronze boot, drawing a trickle of blood.\n");
            me->catch_msg("You poke " + QTPNAME(enemy) + " " + hdesc +
                " with the stiletto " +
                "heel of your embossed bronze boot, drawing a trickle of blood.\n");
            me->tell_watcher(QCTNAME(me) + " pokes " +
                QTPNAME(enemy) + " " + hdesc +
                " with the stiletto heel of " + me->query_possessive() +
                " embossed bronze boot, drawing a trickle of blood.\n",
                enemy, us);
        }
        break;
    case 6..15:
        if (enemy_is_undead)
        {
            enemy->catch_msg(QCTNAME(me) + " stabs your " +
                hdesc + " with the stiletto heel of " + me->query_possessive() +
                " embossed bronze boot.\n");
            me->catch_msg("You stab " + QTPNAME(enemy) + " " + hdesc +
                " with the stiletto " +
                "heel of your embossed bronze boot.\n");
            me->tell_watcher(QCTNAME(me) + " stabs " +
                QTPNAME(enemy) + " " + hdesc +
                " with the stiletto heel of " + me->query_possessive() +
                " embossed bronze boot.\n",
                enemy, us);
        }
        else
        {
            enemy->catch_msg(QCTNAME(me) + " stabs your " +
                hdesc + " with the stiletto heel of " + me->query_possessive() +
                " embossed bronze boot, drawing some blood.\n");
            me->catch_msg("You stab " + QTPNAME(enemy) + " " + hdesc +
                " with the stiletto " +
                "heel of your embossed bronze boot, drawing some blood.\n");
            me->tell_watcher(QCTNAME(me) + " stabs " +
                QTPNAME(enemy) + " " + hdesc +
                " with the stiletto heel of " + me->query_possessive() +
                " embossed bronze boot, drawing some blood.\n",
                enemy, us);
        }
        break;
    case 16..30:
        if (enemy_is_undead)
        {
            enemy->catch_msg(QCTNAME(me) + " deeply stabs your " +
                hdesc + " with the stiletto heel of " + me->query_possessive() +
                " embossed bronze boot.\n");
            me->catch_msg("You deeply stab " + QTPNAME(enemy) + " " + hdesc +
                " with the stiletto " +
                "heel of your embossed bronze boot.\n");
            me->tell_watcher(QCTNAME(me) + " deeply stabs " +
                QTPNAME(enemy) + " " + hdesc +
                " with the stiletto heel of " + me->query_possessive() +
                " embossed bronze boot.\n",
                enemy, us);
        }
        else
        {
            enemy->catch_msg(QCTNAME(me) + " deeply stabs your " +
                hdesc + " with the stiletto heel of " + me->query_possessive() +
                " embossed bronze boot, drawing some blood.\n");
            me->catch_msg("You deeply stab " + QTPNAME(enemy) + " " + hdesc +
                " with the stiletto " +
                "heel of your embossed bronze boot, drawing some blood.\n");
            me->tell_watcher(QCTNAME(me) + " deeply stabs " +
                QTPNAME(enemy) + " " + hdesc +
                " with the stiletto heel of " + me->query_possessive() +
                " embossed bronze boot, drawing major amounts blood.\n",
                enemy, us);
        }
        break;
    default:
        if (enemy_is_undead)
        {
            enemy->catch_msg(QCTNAME(me) + " viciously punctures your " +
                hdesc + " with the stiletto heel of " + me->query_possessive() +
                " embossed bronze boot.\n");
            me->catch_msg("You viciously puncture " + QTPNAME(enemy) + " " + hdesc +
                " with the stiletto " +
                "heel of your embossed bronze boot.\n");
            me->tell_watcher(QCTNAME(me) + " viciously punctures " +
                QTPNAME(enemy) + " " + hdesc +
                " with the stiletto heel of " + me->query_possessive() +
                " embossed bronze boot.\n",
                enemy, us);
        }
        else
        {
            enemy->catch_msg(QCTNAME(me) + " viciously punctures your " +
                hdesc + " with the stiletto heel of " + me->query_possessive() +
                " embossed bronze boot, blood sprays all over.\n");
            me->catch_msg("You viciously puncture " + QTPNAME(enemy) + " " + hdesc +
                " with the stiletto " +
                "heel of your embossed bronze boot, blood sprays all over.\n");
            me->tell_watcher(QCTNAME(me) + " viciously punctures " +
                QTPNAME(enemy) + " " + hdesc +
                " with the stiletto heel of " + me->query_possessive() +
                " embossed bronze boot, blood sprays all over.\n",
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

public void 
init()
{
    add_action(kick, "kick");
}

public string
query_recover()
{
    return MASTER + ":" + query_arm_recover();
}

public void
init_recover(string arg)
{
    init_arm_recover(arg);
}
