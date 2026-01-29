#pragma strict types
#include "defs.h"
inherit "/std/door";

void create_gates();

void
create_door()
{
    set_name(({"gates", "gate"}));
    add_prop(OBJ_I_WEIGHT, 1000000);
    add_prop(OBJ_I_VOLUME, 400000);
    add_prop(DOOR_I_HEIGHT, 300);

    create_gates();
}

void
create_gates() {}

string
standard_open_desc()
{
    return capitalize(short()) + " stand open to the " + pass_commands[1] + ".\n";
}

string
standard_closed_desc()
{
    return capitalize(short()) + " stand closed to the " + pass_commands[1] + ".\n";
}

string
standard_open_mess2()
{
    return "The " + short() + " open.\n";
}

string
standard_fail_open1()
{
    return "The " + short() + " are already open.\n";
}

string
standard_fail_open2()
{
    return "The " + short() + " are locked.\n";
}

string
standard_close_mess2()
{
    return "The " + short() + " close.\n";
}

string
standard_fail_lock1()
{
    return "The " + short() + " are already locked.\n";
}

string
standard_fail_pass()
{
    return "The " + short() + " are closed.\n";
}

string
standard_fail_close()
{
    return "The " + short() + " are already closed.\n";
}

string
standard_fail_unlock()
{
    return "The " + short() + " are already unlocked.\n";
}

void
set_gates_id(string id)
{
    set_door_id(id);
}

void
set_gates_name(mixed name)
{
    set_door_name(name);
}

void
set_gates_desc(string desc)
{
    set_door_desc(desc);
}

void
load_other_gates()
{
    load_other_door();
}

static void
remove_gates_info(object dest)
{
    remove_door_info(dest);
}

void
do_open_gates(string mess)
{
    do_open_door(mess);
}

void
do_close_gates(string mess)
{
    do_close_door(mess);
}

void
do_lock_gates(string mess)
{
    do_lock_door(mess);
}

void
do_unlock_gates(string mess)
{
    do_unlock_door(mess);
}

int
knock_gates(string arg)
{
    return knock_door(arg);
}


