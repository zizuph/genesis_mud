
/* 
 * A tin donut-shaped frisbee, one of the Calia christmas toys. 
 * Coded by Maniac@Genesis, 19/12/98
 */

inherit "/cmd/std/command_driver"; 
inherit "/std/object";
/* Inherit /lib/wearable_item to make the item wearable */
inherit "/lib/wearable_item";

#include <wa_types.h>
#include <stdproperties.h>
#include <tasks.h>
#include <ss_types.h>
#include <macros.h>
#include <cmdparse.h>

int landing; 

void
create_object()
{
    set_name("frisbee");
    set_adj(({"tin", "donut-shaped"}));
    set_short("tin donut-shaped frisbee"); 
    set_long("This is a frisbee made of tin in the shape of " +
             "a donut. You could try throwing it, or maybe " +
             "even landing it on someone.\n"); 

    config_wearable_item(A_HEAD, 2, 3, this_object());

    add_prop(OBJ_I_WEIGHT, 500);
    add_prop(OBJ_I_VOLUME, 500); 
    add_prop(OBJ_I_VALUE, 10); 
    add_prop(OBJ_M_NO_SELL, 
               "The tin donut-shaped frisbee is too silly " +
               "to interest the merchant.\n"); 

    landing = 0; 
}


public mixed
wear(object obj)
{
    return landing; 
}


/*
 * We need to override leave_env() so that we can be sure to
 * remove the hat if it gets moved from the wearer while it
 * is still worn.
 */
public void
leave_env(object env, object to)
{
    ::leave_env(env, to);
    wearable_item_leave_env(env, to);
}


int
do_land(string str)
{
    object tp, trg, *oblist; 
    int td; 

    tp = this_player(); 
    if (environment(tp)->query_prop(ROOM_I_TYPE) == ROOM_UNDER_WATER) {
        notify_fail("You can't do that under water!\n"); 
        return 0;
    } 

    notify_fail("Land what on whom?\n"); 
    if (!stringp(str) || !strlen(str))
        return 0;

    if (!objectp(present(this_object(), tp))) {
        notify_fail("You don't have the " + short() + ".\n"); 
        return 0; 
    } 

    if (!sizeof(oblist = 
        parse_this(str, "[the] [tin] [donut-shaped] 'frisbee' 'on' %l")))
        return 0;  

    if (sizeof(oblist) > 1) {
        notify_fail("You can't land the " + short() + 
                    " on more than one target!\n"); 
        return 0; 
    } 

    trg = oblist[0]; 

    if (!(trg->query_combat_object()->query_hitloc(TS_HEAD))) {
        notify_fail("That target doesn't appear to be humanoid!\n"); 
        return 0;
    }

    if (objectp(trg->query_attack()))  {
        if (objectp(tp->query_attack()))
            td = TASK_FORMIDABLE;
        else
            td = TASK_DIFFICULT; 
    }
    else if (objectp(tp->query_attack()))
        td = TASK_DIFFICULT; 
    else
        td = TASK_ROUTINE;

    if (!trg->query_prop(LIVE_M_NO_ACCEPT_GIVE) &&
        (tp->resolve_task(td, ({ SS_WEP_MISSILE })) > 0) &&
        !move(trg)) {
        set_this_player(trg);
        landing = 1; 
        if (wear_me() == 1) {
            tell_object(tp, "You land the " + short() + " on " + 
                        trg->query_the_name(tp) + "'s head!\n"); 
            tell_object(trg, tp->query_The_name(trg) + " lands " + 
                        tp->query_possessive() + " " + short() + 
                        " on your head!\n"); 
            say(QCTNAME(tp) + " lands " + tp->query_possessive() + 
                " " + short() + " on " + QTNAME(trg) + "'s head.\n", 
                ({ tp, trg })); 
        }
        else { 
            move(environment(tp));  
            tell_object(tp, "You land the " + short() + " on " + 
                        trg->query_the_name(tp) + "'s head but " +
                        "it won't stay on and clatters to the ground.\n"); 
            tell_object(trg, tp->query_The_name(trg) + " " +
                        "lands " + tp->query_possessive() + " " + short() + 
                        " on your head but it won't stay on and clatters " +
                        "to the ground.\n"); 
            say(QCTNAME(tp) + " lands " + tp->query_possessive() + 
                " " + short() + " on " + QTNAME(trg) + "'s head but " +
                "it won't stay on and clatters to the ground.\n", ({ tp, trg }));
        } 
        landing = 0; 
        set_this_player(tp); 
        return 1;
    }

    move(environment(tp)); 
    tell_object(tp, "You try to land the " + short() + " on " + 
          trg->query_the_name(tp) + "'s head but " +
          "it misses and clatters to the ground.\n"); 
    tell_object(trg, tp->query_The_name(trg) + " tries " + 
                "to land " + tp->query_possessive() + " " + 
                short() + " on your head but it misses " + 
                "and clatters to the ground.\n"); 
    say(QCTNAME(tp) + " tries to land " + tp->query_possessive() + 
        " " + short() + " on " + QTNAME(trg) + "'s head " +
        "but it misses and clatters to the ground.\n", ({tp, trg})); 
    return 1;
}


int
do_throw(string str)
{
    object tp, trg, *oblist; 
    int td, ignore; 
    string resp_me, resp_them; 

    tp = this_player(); 
    if (environment(tp)->query_prop(ROOM_I_TYPE) == ROOM_UNDER_WATER) {
        notify_fail("You can't do that under water!\n"); 
        return 0;
    } 

    notify_fail("Throw what to whom?\n"); 
    if (!stringp(str) || !strlen(str))
        return 0;

    if (!objectp(present(this_object(), tp))) {
        notify_fail("You don't have the " + short() + ".\n"); 
        return 0; 
    } 

    if (!sizeof(oblist = 
        parse_this(str, "[the] [tin] [donut-shaped] 'frisbee' 'to' %l")))
        return 0;  

    if (sizeof(oblist) > 1) {
        notify_fail("You can't throw the " + short() + 
                    " to more than one target!\n"); 
        return 0; 
    } 

    trg = oblist[0]; 

    if (!(trg->query_combat_object()->query_hitloc(TS_LARM)) &&
        !(trg->query_combat_object()->query_hitloc(TS_RARM))) {
        notify_fail("That target doesn't appear to be humanoid!\n"); 
        return 0;
    }

    if (objectp(tp->query_attack()))
        td = TASK_DIFFICULT;
    else 
        td = TASK_SIMPLE; 

    if (tp->resolve_task(td, ({ SS_WEP_MISSILE })) < 0) {
        move(environment(tp)); 
        tell_object(tp, "You attempt to throw your " + short() + 
              " to " + trg->query_the_name(tp) + " but it clatters " +
              "to the ground well wide of the mark.\n"); 
        tell_object(trg, tp->query_The_name(trg) + " attempts " + 
              "to throw " + tp->query_possessive() + " " + 
              short() + " to you but it clatters to the ground " +
              "well wide of the mark.\n"); 
        say(QCTNAME(tp) + " attempts to throw " + tp->query_possessive() + 
              " " + short() + " to " + QTNAME(trg) + " but it " +
              "clatters to the ground well wide of the mark.\n", 
              ({tp, trg})); 
        return 1;
    } 

    if (!(ignore = objectp(trg->query_attack()) || 
                   trg->query_prop(LIVE_M_NO_ACCEPT_GIVE))) {
        if ((trg->resolve_task(TASK_SIMPLE, ({ SS_WEP_MISSILE })) > 0) &&
            !move(trg)) {
            tell_object(tp, "You throw the " + short() + " to " + 
                        trg->query_the_name(tp) + ", who catches it.\n"); 
            tell_object(trg, tp->query_The_name(trg) + " throws " + 
                        tp->query_possessive() + " " + short() + 
                        " to you, and you catch it.\n"); 
            say(QCTNAME(tp) + " throws " + tp->query_possessive() + 
                " " + short() + " to " + QTNAME(trg) + ", who catches " +
                "it.\n", ({ tp, trg })); 
            return 1;
        }
        resp_me = ", but you fail to catch it."; 
        resp_them = ", who fails to catch it."; 
    } 
    else {
        resp_me = ", but you ignore it."; 
        resp_them = ", who ignores it."; 
    }

    resp_me += " It clatters to the ground nearby.\n"; 
    resp_them += " It clatters to the ground nearby.\n"; 

    move(environment(tp)); 
    tell_object(tp, "You throw the " + short() + " to " + 
                trg->query_the_name(tp) + resp_them); 
    tell_object(trg, tp->query_The_name(trg) + " throws " + 
                tp->query_possessive() + " " + short() + 
                " to you" + resp_me); 
    say(QCTNAME(tp) + " throws " + tp->query_possessive() + 
        " " + short() + " to " + QTNAME(trg) + resp_them, 
       ({ tp, trg })); 
    return 1;
}


void
init()
{
    ::init(); 
    add_action(do_throw, "throw"); 
    add_action(do_land, "land"); 
}
