/*
 *  To be inherited by all doors in Kalad
 */

inherit "/std/door";
#include "/d/Kalad/defs.h"


create_door()
{
    set_door_desc("@@standard_door_desc");
}

string
query_first_name()
{
    string first_name;

	first_name = obj_names[0];

    return first_name;
}

int
query_thick()
{
    return 0;
}

/*so players can't tell if its bashable*/ 
string
query_condition()
{
    return "sturdy looking";
}

string
standard_open_desc()
{
    string temp_desc;
    temp_desc = "There is a " + query_condition() + ", " +
    "open " + query_first_name();
    if (strlen(pass_commands[0]) <= 2)
	temp_desc = temp_desc + " leading " + pass_commands[1] + ".\n";
    else
	temp_desc = temp_desc + " here.\n";
    return temp_desc;
}

string
standard_closed_desc()
{
    string temp_desc;
    temp_desc = "There is a " + query_condition() + ", " +
    "closed " + query_first_name();
    if (strlen(pass_commands[0]) <= 2)
	temp_desc = temp_desc + " leading " + pass_commands[1] + ".\n";
    else
	temp_desc = temp_desc + " here.\n";
    return temp_desc;
}

string
open_long()
{
    string temp_desc;

    temp_desc = "It is open";
    if (strlen(TO->query_condition()) && strlen(pass_commands[0]) <= 2)
	temp_desc = temp_desc + ", " + TO->query_condition() +
	", and leads " + pass_commands[1];
    else if(strlen(pass_commands[0]) <= 2)
	temp_desc = temp_desc + " and leads " + pass_commands[1];
    else
	temp_desc = temp_desc + " and " + TO->query_condition();

    return break_string(temp_desc + ".\n", 70);
}

string
closed_long()
{
    string temp_desc;

    temp_desc = "It is closed";
    if (strlen(TO->query_condition()) && strlen(pass_commands[0]) <= 2)
	temp_desc = temp_desc + ", " + TO->query_condition() +
	", and leads " + pass_commands[1];
    else if(strlen(pass_commands[0]) <= 2)
	temp_desc = temp_desc + " and leads " + pass_commands[1];
    else
	temp_desc = temp_desc + " and " + TO->query_condition();

    return break_string(temp_desc + ".\n", 70);
}

void
do_open_door(string mess)
{
    object env;

    env = E(TO);
    env->change_my_desc(check_call(open_desc));  /*update short*/
    env->remove_item(TO->query_first_name());
    env->add_item(obj_names,check_call("@@open_long"));

    if (strlen(mess))
	tell_room(env, mess);
    open_status = 1;
}

void
do_close_door(string mess)
{
    object env;

    env = E(TO);
    env->change_my_desc(check_call(closed_desc));  /*update short*/
    env->remove_item(TO->query_first_name());
    env->add_item(obj_names,check_call("@@closed_long"));

    if (strlen(mess))
	tell_room(env, mess);
    open_status = 0;
}

void
enter_env(object dest, object old)
{
    add_door_info(dest);
    if (open_status)
    {
	dest->change_my_desc(check_call(open_desc));  /*update short*/
	dest->add_item(obj_names,check_call("@@open_long"));
    }
    else
    {
	dest->change_my_desc(check_call(closed_desc));  /*update short*/
	dest->add_item(obj_names,check_call("@@closed_long"));
    }
    if (strlen(lock_desc) && lock_name)
	dest->add_item(lock_name, lock_desc);
}

/*
 *  Swiped from Nick's example door
 */ 

void
do_pick_lock(int skill, int pick)
{
    object room;

    ::do_pick_lock(skill, pick);

    room = E(TO);
    if (room->query_trap())
	room->do_trap(TP);
}
