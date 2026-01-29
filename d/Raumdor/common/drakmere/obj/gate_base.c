#pragma strict types
#include "defs.h"
inherit "/d/Raumdor/common/std/gates";

void
create_gates()
{
    ::create_gates();
    set_gates_name(({"huge iron gates", "huge gates", "iron gates", "gates"}));
    set_no_pick();
    set_open(0);
    set_locked(1);
    set_lock_desc("You cannot see any lock on this side.\n");
    add_prop(OBJ_I_WEIGHT, 1000000);
    add_prop(OBJ_I_VOLUME, 400000);
    add_prop(DOOR_I_HEIGHT, 300);
}

int
query_inner_gate()
{
    return 0;
}

string
standard_knock_resp2()
{
    return "You hear someone knock on the " + short() + ".\n";
}

void
guard_unlock()
{
    throw("This function should be defined in child");
}

void
autoclose(float delay)
{
    throw("This function should be defined in child");
}

int
attempt_approach()
{
    if (TP->query_prop(LIVE_I_UNDEAD) || TP->query_prop(IS_ENEMY_OF_DRAKMERE))
    {
        write("You approach the gates, but a guard stands in your way.\n");
        TELL_SEEN(TP, QCTNAME(TP) + " approaches the gates, but a guard " +
                "stands in the way.\n");
        return 0;
    }
    return 1;
}


object *
query_guards()
{
    return filter(FILTER_CAN_SEE_IN_ROOM(AINV(E(TO))),
           &->query_drakmere_guard());
}


int
query_guarded()
{
    return sizeof(FILTER_IS_SEEN(TP, query_guards()));
}

void
guard_open()
{
    string action = "pulls";

    load_other_door();

    if (query_locked())
    {
        write("As you approach the gates, a guard knocks on them.\n");
        say("A guard knocks on the gates.\n");
        tell_room(environment(other_door), knock_resp[2]);
        guard_unlock();
    }
    if (!query_open())
    {
        if (query_inner_gate())
            action = "pushes";
        do_open_door("The guard " + action + " open the gates.\n");
        other_door->do_open_door(check_call(open_mess[1]));
    }
    autoclose(15.0);
}

int
knock_door(string arg)
{
    int result;
    string tmp;

    notify_fail(capitalize(query_verb()) + " on what?\n", 0);
    if (!strlen(arg))
        return 0;
    if (sscanf(arg, "on %s", tmp))
        arg = tmp;
    if (!this_door(arg))
        return 0;

    if (!query_guarded())
    {
        result = ::knock_door(arg);
        if (result)
		    guard_unlock();
        return result;
    }

    if (attempt_approach())
    {
        if (query_open())
        {
            write("The " + short() + " are open, but you knock on them " +
                    "anyway. Nothing happens.\n");
            say(QCTNAME(TP) + " knocks on the open gates.\n");
        }
        else
            guard_open();
    }
    return 1;
}

int
open_door(string arg)
{
    if (!this_door(arg))
    {
        notify_fail(capitalize(query_verb()) + " what?\n", 0);
        return 0;
    }

    if (!query_guarded())
        return ::open_door(arg);

    if (query_open())
    {
        write("The " + short() + " are already open.\n");
        return 1;
    }

    if (attempt_approach())
        guard_open();
    return 1;
}

int
pass_door(string arg)
{
    if (query_guarded() && attempt_approach())
        guard_open();

    load_other_door();
	
	autoclose(2.0);
    return ::pass_door(arg);
}

