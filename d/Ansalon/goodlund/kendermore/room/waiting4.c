#include "../local.h"
#include "/d/Ansalon/common/defs.h"
#include <macros.h>

inherit KENDERMORE_IN;
inherit STREET_DESC;

object kender1, kender2, kender3, kender4;

string* sick_emotes = ({"blurts out: Wow! You sure look sick! You can go in ahead of me.",
                        "laughs: Did you come to the wrong place? Looks aren't something that can be cured.",
	                "sniffs: I got the same illness twice; how unlucky is that when there are so many to chose from!",
                        "states: I have been here so many times that I am practically a doctor!",
                        "says: I wonder what illness I may have today. I hope it is another curse, last week was exciting!",
                        "argues: What is taking the doctor so long, it must be my turn next!",
                        "shouts: Hurry up in there, or I won't get to see the doctor before I die from my deadly illness, or worse... I may be cured by the time I get my turn."});


void
reset_kendermore_room()
{
  if (!kender1)
  {
    kender1 = clone_object(KNPC+"std_kender");
    kender1->set_should_walk(0);
    kender1->move(this_object(), 1);
  }

  if (!kender2)
  {
    kender2 = clone_object(KNPC+"std_kender");
    kender2->set_should_walk(0);
    kender2->move(this_object(), 1);
  }

  if (!kender3)
  {
    kender3 = clone_object(KNPC+"std_kender");
    kender3->set_should_walk(0);
    kender3->move(this_object(), 1);
  }

  if (!kender4)
  {
    kender4 = clone_object(KNPC+"std_kender");
    kender4->set_should_walk(0);
    kender4->move(this_object(), 1);
  }
}

void
create_kendermore_room()
{
    set_short("A small waiting room");

    set_long("You stand in the waiting room to the doctors office. " +
        "A dozen chairs is placed in the room. Other than the " + 
	     "chairs the room is sparsely decorated.\n");

    add_item(({"wall", "walls"}), "They are made of unadorned wood.\n");

    add_item(({"chair", "chairs"}), "They look rather comfortable, and " + 
        "bolted down to the floor. That must explain why they are still " + 
        "here.\n");

    add_exit(KROOM + "waiting1", "north", 0);
    reset_kendermore_room();
}

void
do_emote(object kender)
{
  kender->command("emote "+ONE_OF(sick_emotes));
}

public void
enter_inv(object ob, object from)
{
  ::enter_inv(ob, from);

  if (interactive(ob))
  {
    object* objects_in_room = all_inventory(this_object());
    int i;

    for (i = 0; i < sizeof(objects_in_room); i++)
    {
      object obj = objects_in_room[i];

      // Kenders likes to talk to newcomers.
      if (living(obj) && !interactive(obj) && obj->id("my_kender") && !random(2))
      {
	set_alarm(1.0, 0.0, &do_emote(obj));
	break;
      }
    }
  }
}
