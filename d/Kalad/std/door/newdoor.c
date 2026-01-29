/*
 *  inherit this if you want a bashable door but don't forget to put 
 *  "::create_door();" in the create_door function of your door
 * All doors in Kalad should inherit this instead of "/std/door"
 *  -modified from commander's smashable cube
 */ 

inherit "/std/door";
#include "/d/Kalad/defs.h"

int wholeness = 500; /*current structural strength*/
int thickness = 500; /*base structural strength*/
string broken_str;           /*string to write when door breaks*/
int bashable = 0;  /*if true, door is bashable*/

create_door()
{
    ::create_door();
   set_alarm(1.0,0.0,"reset_door"); /*give it full hp*/
}

/* make sure to set the other side bashable also*/
void
set_bashable(int bash)
{
    bashable = bash;    
}

int
query_bashable()
{
    return bashable;
}

void
set_thick(int thick)
{
    object other; /*the other side of the door*/

    thickness = thick;

/* this code would make sure both sides
 * have the same thickness but it seems
 * to cause problems for the same reasons
 * as similar code in set_key().
 * For now make sure to set the same thickness
 * manually in both sides.

    other = TO->query_other_door();
    if (other->query_thick() < thick)
      other->set_thick(thick);
    else if (other->query_thick() > thick)
      thickness = other->query_thick();
*/
}

int
query_thick()
{
    if (!thickness)
      thickness = 500; /*default thickness if not set*/
    return thickness;
}

reset_door()
{
    wholeness = query_thick(); /*give it full hp*/
}

init()
{
    ::init();
    AA(bash,bash);
}

void
set_wholeness(int val)
{
    wholeness = val;
}

mixed* query_weapon() { return ({}); }

string
query_first_name()
{
    string first_name;

    if (!sizeof(door_name))
      first_name = door_name;
    else
      first_name = door_name[0];

    return first_name;
}

string query_the_name()
{
    return "the " + TO->query_first_name();
}
void
update_descs()
{
    object env;

    env = E(TO); /*room the door is in*/
    env->remove_item(TO->query_first_name()); /*remove old long desc*/
    if (open_status)
    {
      env->change_my_desc(check_call(open_desc)); /*update short*/
      env->add_item(door_name,check_call("@@open_long")); /*update long*/
    }
    else
    {
      env->change_my_desc(check_call(closed_desc)); /*update short*/
      env->add_item(door_name,check_call("@@closed_long")); /*update long*/
    }
}

mixed* hit_me(int wcpen, int dt, object attacker, int aid)
{
    int phurt;
    string location;
    object other;

    if (random(4))      /*hitloc of door*/
      location = "center";
    else
      location = "frame";

    if (wholeness < 1)
      return ({0,location,0,0});

    phurt = 100*wcpen / wholeness;
    wholeness = wholeness - wcpen;  /*damage the door*/
    other = TO->query_other_door();
    other->set_wholeness(wholeness);  /*same damage for other side*/
    other->update_descs(); /*update other side's descs*/
    TO->update_descs(); /*update this side's descs*/
    other = TO->query_other_room();
    tell_room(other,"THUD!\n" + BS(C(TO->query_the_name()) + " " +
       "suddenly bulges inward, as if struck from the " +
       "other side!\n"));

    return ({phurt,location,phurt,wcpen});
}

int
query_hp()
{
    if (wholeness < 1)
      return 0;
    else
      return wholeness;
}

string
query_condition()
{
    int pwhole; /*percentage of original wholeness*/
    string condition;

    if (wholeness > thickness) /*should never happen*/
      wholeness = thickness;

    if (wholeness < 1)
      condition = "completely shattered";
    else
    {
      pwhole = 100*wholeness/thickness;
      if (pwhole > 75)
        condition = "sturdy looking";
      else if (pwhole < 25)
        condition = "mangled";
      else
        condition = "battered looking";
    }

    return condition;
}

string
standard_open_desc()
{
    string temp_desc;
    temp_desc = "There is a " + query_condition() + ", " +
      "open " + door_name[0];
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
      "closed " + door_name[0];
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

    return BS(temp_desc + ".\n");
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

    return BS(temp_desc + ".\n");
}

void
do_open_door(string mess)
{
    object env;

    env = E(TO);
    env->change_my_desc(check_call(open_desc));  /*update short*/
    env->remove_item(TO->query_first_name());
    env->add_item(door_name,check_call("@@open_long")); /*update long*/

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
    env->add_item(door_name,check_call("@@closed_long")); /*update long*/

    if (strlen(mess))
      tell_room(env, mess);
    open_status = 0;
}

void
enter_env(object dest, object old)
{
    add_door_info(dest);
    TO->update_descs(); /*update short and long description*/
    if (strlen(lock_desc) && lock_name)
      dest->add_item(lock_name, lock_desc);
}


void
set_broken_str(string str)
{
    broken_str = str;
}


string
query_broken_str()
{
    if(!broken_str)
      broken_str = "With a loud crack, the door is torn from its hinges!\n";
    return broken_str;
}

void
do_die()
{
    object other;

    wholeness = 0;
    other = TO->query_other_door();
    TO->do_unlock_door(query_broken_str());
    other->do_unlock_door(query_broken_str());
}

int
query_ghost()
{
    if (wholeness < 1)
      return 1;
    else
      return 0;
}

int
bash(string cmd)
{
    string *dnames;
    int i, found;

    found = 0;

    if (!sizeof(door_name))
    {
      if (cmd == door_name)
        found = 1;
    }
    else
    {
      dnames = door_name;
      for (i=0;i < sizeof(dnames);i++)
      {
      if (cmd == dnames[i])
        found = 1;
      }
    }
    if (!found)
      return 0;

    NF("You vainly throw your body into the unrelenting " +
      TO->query_first_name() + ".\n");
    if (!bashable)  /*not a bashable door*/
    {
      say(BS(QCTNAME(TP) + " looks pretty silly as " + TP->query_pronoun() +
        " repeatedly throws " + TP->query_objective() + "self into " +
        TO->query_the_name() + ".\n"));
      return 0;
    }

    if(TO->query_open())
    {
      NF("It's already open.\n");
      return 0;
    }

    if(!TO->query_locked())
    {
      NF("It isn't locked.\n");
      return 0;
    }

    if (wholeness < 1)
    {
      NF("It's already broken.\n");
      return 0;
    }

    write("You begin bashing " + TO->query_the_name() + ".\n");
    say(QCTNAME(TP) + " begins bashing " + TO->query_the_name() + ".\n");
    TP->attack_object(TO);
    return 1;
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
