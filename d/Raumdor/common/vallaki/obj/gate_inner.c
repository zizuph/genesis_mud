#pragma strict types
#include "defs.h"
inherit DRAKMERE_GATE;

int close_alarm;

string
crossbar_description()
{
    if (query_locked())
        return "It is lowered, securing the gates.\n";
    return "It is raised, allowing the gates to be opened.\n";
}

void
create_gates()
{
    ::create_gates();
    set_gates_name(({"huge iron gates", "huge gates", "iron gates", "gates"}));
    set_lock_desc("A thick crossbar serves to secure the gates. One side is " +
            "attached to a chain that dangles from the walls above. The " +
            "other side is hinged to the stone, allowing the bar to be " +
            "raised vertically to open the cases or lowered into its support " +
            "hooks for reinforcement.\n");   
    set_door_desc("The gates are quite tall and made of dark iron, embedded " +
            "within the tall stone gatehouse. Large hinges are bolted to the " +
            "outer corners on each side. The gates are secured with a thick " +
            "crossbar connected to a chain, allowing it to be raised or " +
            "lowered from above.\n");
    add_item("crossbar", "@@crossbar_description");
}

int
query_inner_gate()
{
    return 1;
}

string
standard_fail_open2()
{
    return "The lowered crossbar prevents you from opening the gates.\n";
}

void
do_unlock()
{
    load_other_door();
    set_locked(0);
    other_door->set_locked(0);
    tell_room(E(other_door), "You hear something move on the " +
            "other side of the gates.\n");

}

void
do_lock()
{
    load_other_door();
    set_locked(1);
    other_door->set_locked(1);
    tell_room(E(other_door), "You hear something move on the " +
            "other side of the gates.\n");
}

void
guard_lock()
{
    if (!query_open() && !query_locked())
    {
        tell_room(E(TO), "The hear the sound of cranking metal.\n");
        TELL_CAN_SEE(E(TO), "The crossbar is lowered by its " +
                "chain, securing the gates.\n");
        do_lock();
    }
}

void
do_autoclose()
{
    object *guards;
    if (query_locked())
        return;
    load_other_door();
    if (query_open())
    {
        guards = query_guards();
        if (sizeof(guards))
            guards[0]->command("$close " + OB_NAME(TO));
    }
    guard_lock();
}

void
autoclose(float delay)
{
    remove_alarm(close_alarm);
    close_alarm = set_alarm(delay, 0.0, &do_autoclose());
}

void
guard_unlock()
{
    if (query_locked())
    {
        tell_room(E(TO), "The hear the sound of cranking metal.\n");
        TELL_CAN_SEE(E(TO), "The chain dangling from above is quickly " +
                "pulled taut and the crossbar is raised.\n");
        do_unlock();
    }
}

    
int
raise_crossbar(string arg)
{
    if (arg != "crossbar" && arg != "the crossbar")
    {
        notify_fail("Raise what? The crossbar?\n");
        return 0;
    }

    if (!query_locked())
        write("The crossbar is already raised.\n");
    else
    {
        do_unlock();
        write("You raise the crossbar.\n");
        say(QCTNAME(this_player()) + " raises the crossbar on the gates.\n");
    }

    return 1;
}

int
lower_crossbar(string arg)
{
    if (arg != "crossbar" && arg != "the crossbar")
    {
        notify_fail("Lower what? The crossbar?\n");
        return 0;
    }

    if (query_locked())
        write("The crossbar is already lowered.\n");
    else if (query_open())
        write("The gates need to be closed to lower the crossbar.\n");
    else
    {
        do_lock();
        write("You lower the crossbar.\n");
        say(QCTNAME(this_player()) + " lowers the crossbar on the gates.\n");
    }
    return 1;
}


int knock_door(string arg)
{
    int result = ::knock_door(arg);
    if (result)
    {
        guard_unlock();
        if (other_door)
            other_door->autoclose(15.0);
    }
    return result;
}

int
pass_door(string arg)
{
    int result = ::pass_door(arg);
    if (result && other_door)
        other_door->autoclose(2.0);
    return result;
}

void
init()
{
    ::init();

    add_action(&raise_crossbar(), "raise");
    add_action(&lower_crossbar(), "lower");
} 
