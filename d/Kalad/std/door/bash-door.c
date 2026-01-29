/*
 *  inherit this if you want a bashable door but don't forget to put 
 *  "::create_door();" in the create_door function of your door
 *  -modified from commander's smashable cube
 */ 

inherit "/d/Kalad/std/door";
#include "/d/Kalad/defs.h"

int wholeness = 500, thickness = 500;  /*current hp, base hp of door*/
string broken_str;           /*string to write when door breaks*/

create_door()
{
    ::create_door();
   set_alarm(1.0,0.0,"reset_door");
}

void
set_thick(int thick)
{
    object other; /*the other side of the door*/

    thickness = thick;

/* this code would make sure both sides
 * have the same thickness but it seems
 * to cause problems for the same reasons
 * as similar code in set_key()

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
    wholeness = query_thick();
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
string query_the_name()
{
    return "the " + TO->query_first_name();
}
void
update_my_desc()
{
    if (open_status)
      E(TO)->change_my_desc(check_call(open_desc));
    else
      E(TO)->change_my_desc(check_call(closed_desc));
}

mixed* hit_me(int wcpen, int dt, object attacker, int aid)
{
    int phurt;
    string location;
    object env, other;

    if (random(4))
      location = "center";
    else
      location = "frame";

    if (wholeness < 1)
      return ({0,location,0,0});

    phurt = 100*wcpen / wholeness;
    wholeness = wholeness - wcpen;  /*damage the door*/
    other = TO->query_other_door();
    other->set_wholeness(wholeness);
    other->update_my_desc();
    other = TO->query_other_room();
    tell_room(other,"THUD!\n" + BS(C(TO->query_the_name()) + " " +
       "suddenly bulges inward, as if struck from the " +
       "other side!\n"));
    /*update other side of door*/

    env = E(TO);
    env->remove_item(TO->query_first_name());
    other->remove_item(TO->query_first_name());
    if (open_status)
    {
      env->change_my_desc(check_call(open_desc));
      env->add_item(door_name,check_call("@@open_long"));
      other->add_item(door_name,check_call("@@open_long"));
    }
    else
    {
      env->change_my_desc(check_call(closed_desc));
      env->add_item(door_name,check_call("@@closed_long"));
      other->add_item(door_name,check_call("@@closed_long"));
    }

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

    if(TO->query_open())
    {
      write("It's already open.\n");
      return 1;
    }

    if(!TO->query_locked())
    {
      write("It isn't locked.\n");
      return 1;
    }

    if (wholeness < 1)
    {
      write("It's already broken.\n");
      return 1;
    }

    write("You begin bashing " + TO->query_the_name() + ".\n");
    say(QCTNAME(TP) + " begins bashing " + TO->query_the_name() + ".\n");
    TP->attack_object(TO);
    return 1;
}

