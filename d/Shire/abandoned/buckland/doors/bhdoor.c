inherit "/std/door";
#include <macros.h>
#include "../buckdefs.h"

int query_inside();
void reset_door();
void set_inside();
int anybody_home(string str);


object clock = find_object("/d/Gondor/elessar/lib/clock");
string time = clock->query_time_of_day();
int inside;




void
create_door()
{
    ::create_door();
    set_name("door");
    set_door_name(({"wooden door","door"}));
    set_door_desc("This is a round wooden door.  It is more elaborate "+
      "than most hobbit doors, which is to be expected since this is a "+
      "door of Brandy Hall.  There is also a lock on it!\n");
    set_lock_command("lock");
    set_lock_name("lock");
    set_unlock_command("unlock");
    set_open(0);
    set_locked(0);
}

void
reset_door()
{
    ::reset_door();
    if(time=="night" && !query_inside())
      set_locked(1);
}

void
set_inside()
{
    inside=1;
}

int
query_inside()
{
    return inside;
}

void
init()
{
    ::init();
    add_action("anybody_home","knock");
}

int
anybody_home(string str)
{
    if(str != "door" && str != "on door")
      {
        notify_fail("Knock on what?\n");
        return 0;
      }

    if(query_open())
      {
      notify_fail("The door is already open!\n");
      return 0;
      }

    if(query_inside())
      {
      notify_fail("Why would you knock from the inside?");
      return 0;
      }

     write("You knock on the door.\n");
     say(QCTNAME(TP) + " knocks on the door.\n");
     other_room->load_me();
     tell_room(other_room,"There is someone at the door.\n");
     return 1;
}

                          

int
open_door(string str)
{
    if(::open_door(str))
      {
      set_alarm(20.0,0.0,"closing_door");
      return 1;
      }
    else
      return 0;
}

void
closing_door()
{
    if(!query_open())
      return;

    do_close_door("The door suddenly swings shut.\n");
    other_door->do_close_door("The door suddenly swings shut.\n");
}
