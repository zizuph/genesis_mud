#pragma strict_types

inherit "/std/object";
#include "/d/Terel/include/Terel.h"
#include "white.h"
#include <stdproperties.h>
#include <macros.h>
#include <ss_types.h>

static object me;

int quickness;
int duration;
static void quick_one();
static void quick_two();
static void quick_three();
static void quick_four();
static void quick_five();
static void quick_end();
static void remove_me();

public void
create_object()
{
    set_name("_alacrity_object");
    remove_prop(OBJ_I_WEIGHT);
    remove_prop(OBJ_I_VALUE);
    remove_prop(OBJ_I_VOLUME);
    add_prop(OBJ_M_NO_DROP, "Drop what?\n");
    add_prop(OBJ_M_NO_GIVE,1);
    add_prop(OBJ_M_NO_SELL,1);
    add_prop(OBJ_M_NO_BUY,1);

    set_no_show();
}

void enter_env(object to, object from)
{
    object where;

    ::enter_env(to,from);

    if(!living(to))
    {
        set_alarm(0.0, -1.0, "remove_me");
        return;
    }
    me = to;
    quickness = (me->query_skill(WHITE_ALACRITY) + me->query_stat(SS_OCCUP)) / 2;
    duration = (me->query_skill(WHITE_ALACRITY) + me->query_stat(SS_OCCUP)) / 2;
    where = environment(me);

    // Determine how much speed is added and make sure it doesn't exceed 100.
    if(quickness >= 100)
    {
        quickness = 100;
    }
    write("My quickness is: "+quickness+".\n");
    write("My duration is: "+duration+".\n");
    set_alarm(5.0, -1.0, "quick_one");

}


static void quick_one()
{
    // Set the props for the speed and performing the ability.
    me->add_prop(LIVE_I_QUICKNESS, me->query_prop(LIVE_I_QUICKNESS) + quickness);
    me->add_prop(LIVE_I_ALACRITY, 1);
    write("You call out to the spirits of glory and valar.\n");
    say("An eerie wail chills you to the bone.\n");

    // Send our messages.
    set_alarm(20.0, -1.0, "quick_two");
    return;
}

static void quick_two()
{

    write(" You feel the strength of ages as the spirits harken to your call.\n");
    say("For a moment, "+QCTNAME(me)+" is surrounded by pale figures.\n");

    if(duration > 20)
    {
        set_alarm(20.0, -1.0, "quick_three");
        return;
    }
    set_alarm(1.0, -1.0, "quick_end");
    return;
}

static void quick_three()
{
    write("Your heart pounds and your vision blurs. Your thoughts and motions become one.\n");
    say("Images of spirits long dead flicker briefly in "+
        QCTPNAME(me)+" grim visage.\n");
    if(duration > 40)
    {
        set_alarm(20.0, -1.0, "quick_four");
        return;
    }
    set_alarm(1.0, -1.0, "quick_end");
    return;
}

static void quick_four()
{
    write("Message four for alacrity.\n");
    if(duration > 60)
    {
        set_alarm(20.0, -1.0, "quick_five");
        return;
    }
    set_alarm(1.0, -1.0, "quick_end");
    return;
}

static void quick_five()
{
    write("Message five for alacrity.\n");
    if(duration > 80)
    {
        set_alarm(20.0, -1.0, "quick_end");
        return;
    }
    set_alarm(1.0, -1.0, "quick_end");
    return;
}

static void quick_end()
{
    write("Ending Alacrity.\n");
    me->remove_prop(LIVE_I_ALACRITY);
    me->add_prop(LIVE_I_QUICKNESS, me->query_prop(LIVE_I_QUICKNESS) - quickness);
    TO->remove_object();
    return;
}


static void remove_me()
{
    ::remove_object();
}
