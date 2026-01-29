/* Ashlar, 20 Aug 97 */

#include <stdproperties.h>
#include <ss_types.h>
#include <wa_types.h>
#include <macros.h>
#include <filter_funs.h>
#include <tasks.h>
#include "/d/Ansalon/common/defs.h"
#include "../local.h"

inherit "/std/object";

#define GRABOBJ_ID  "_zombie_grab_"

object gGrabber;

void
create_object()
{
    set_name(GRABOBJ_ID);
    add_prop(OBJ_I_VOLUME, 0);
    add_prop(OBJ_I_WEIGHT, 0);
    add_prop(OBJ_I_NO_DROP, 1);
    add_prop(OBJ_I_NO_GIVE, 1);
    add_prop(OBJ_I_VALUE, 0);
    set_no_show();
}

int
no_command()
{
    if (gGrabber)
        write("You are held by " + gGrabber->query_the_name(TP) +
        " and cannot move!\n");
    else
        write("You are still out of breath, but you will be all " +
        "right in a little while.\n");
    return 1;
}

public int
do_all_commands(string str)
{
    string verb;
    string *not_allowed;

    not_allowed = ({"n","north","s","south","w","west","e","east","nw",
      "northwest","sw","southwest","se","southeast",
      "northeast","ne","u","up","d","down","teleport",
      "goto","home","kill" });

    if (TP->query_wiz_level())
        return 0;

    verb = query_verb();
    if (member_array(verb, not_allowed) == -1)
        return 0;
    else
        return no_command();

    return 1;
}

init()
{
    ::init();
    add_action(do_all_commands, "", 1);
}

void
set_grabber(object ob)
{
    gGrabber = ob;
}

void
do_break_free()
{
    object victim;

    victim = E(TO);

    victim->catch_msg("You " +
    (victim->query_stat(SS_STR) > victim->query_stat(SS_DEX) ? "break free" :
    "wriggle out") + " of " + gGrabber->query_the_name(victim) +
    "'s deadly grip!\n");
    victim->tell_watcher(QCTNAME(victim) + " breaks free of " +
    QTNAME(gGrabber) + "'s deadly grip.\n", gGrabber);
    gGrabber->grabbed_break_free();
    remove_object();
}

void
try_break_free()
{
    int success;
    object victim;
    mixed r;
    string *str;

    victim = E(TO);
    if (!gGrabber)
    {
        victim->catch_msg("Your captor is dead and you can move again.\n");
        set_alarm(1.0,0.0,remove_object());
        return;
    }

    success = victim->resolve_task(TASK_DIFFICULT,
        ({ TS_STR, TS_DEX }), gGrabber, ({ TS_STR }));

    if (success > 0)
    {
        set_alarm(2.0,0.0,do_break_free);
        return;
    }

    victim->add_attack_delay(20,1);

    r = victim->hit_me(gGrabber->query_stat(SS_STR),
        W_BLUDGEON,gGrabber,-1,A_TORSO);

    if (r[0] <= 0)
    {
        str = ({ "You try to break free but fail.",
        QCTNAME(victim) + " tries to break free from the " +
        QTNAME(gGrabber) + "'s grip, but fails." });
    }
    else if (r[0] < 5)
    {
        str = ({ gGrabber->query_The_name(victim) + " squeezes you " +
        "in its grip, hurting you slightly.",
        QCTNAME(gGrabber) + " squeezes " + QTNAME(victim) + " in its grip, " +
        "hurting " + QTNAME(victim) + " slightly." });
    }
    else if (r[0] < 15)
    {
        str = ({ gGrabber->query_The_name(victim) + " tightens its grip, " +
        "making it hard to breathe.",
        QCTNAME(gGrabber) + " tightens its grip on " + QTNAME(victim) +
        ", who looks out of breath." });
    }
    else if (r[0] < 40)
    {
        str = ({ "You can feel bones beginning to break as " +
        gGrabber->query_the_name(victim) + " squeezes you harder.",
        QCTNAME(victim) + " winces in pain as " + QTNAME(gGrabber) +
        " squeezes harder." });
    }
    else if (r[0] < 100)
    {
        str = ({ gGrabber->query_The_name(victim) + " crushes you in " +
        "its grip, breaking several of your bones.",
        "You hear bones break as " + QTNAME(gGrabber) + " crushes " +
        QTNAME(victim) + " in its grip." });
    }
    else
    {
        str = ({ "You faint from lack of air and the pain as " +
        gGrabber->query_the_name(victim) + " crushes you in its grip.",
        QCTNAME(victim) + " mercifully faints right before " +
        QTNAME(gGrabber) + " crushes " + HIM(victim) + " to death." });
    }
    victim->catch_msg(str[0]+"\n");
    gGrabber->tell_watcher(str[1]+"\n",victim);
    if (victim->query_hp() < 0)
    {
        victim->do_die(gGrabber);
        gGrabber->grabbed_break_free();
    }
}

void
do_grab()
{
    object victim;
    victim = E(TO);

    victim->catch_msg("You are unable to move!\n");
    victim->add_stun();

    if(victim->query_wiz_level())
        victim->catch_msg("As a wizard, you are immune to being stunned.\n");

    victim->add_attack_delay(20,1);
    set_alarm(10.0, 10.0, try_break_free);
}

void
enter_env(object env, object from)
{
    ::enter_env(env, from);

    if (!objectp(env) || !(living(env)))
        set_alarm(0.0, 0.0, remove_object);
    else
        set_alarm(0.0, 0.0, do_grab);
}

void
leave_env(object env, object to)
{
    ::leave_env(env, to);

    if (living(env))
        env->remove_stun();
}
