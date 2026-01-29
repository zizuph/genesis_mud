inherit "/d/Gondor/common/room";
#include "/d/Gondor/defs.h"
#include <ss_types.h>
#include <macros.h>
#include "dirdefs.h".

#define UP_ROOM    "chimney2"

object up_room;


create_room()
{
  set_long(BS("You are climbing at the bottom of a narrow chimney in the " +
    "White Mountains. It's a very uncomfortable place. High above you can " +
    "see a projecting rock. The chimney starts here and it looks as if it " +
    "extends far up. You can leave the chimney to step onto a narrow ledge. " +
    "You might be able to climb up.\n"));
  set_short("At the bottom of a narrow chimney in the White Mountains");
  add_item(({ "walls", "wall", "rock walls" }), BS("The walls are rather steep, "
    + "but an experienced climber might be able to climb up in the chimney.\n"));
  add_item(({ "rock", "projecting rock" }), "You can't see what's on it " +
    "from here.\n");
  add_item("chimney", BS(
    "This is a narrow chimney, going straight up between the rock walls.\n"));
  seteuid(getuid());
  up_room = THIS_DIR + UP_ROOM;
  if(up_room) up_room->load_me();
}

init()
{
  ::init();
  add_action("do_leave","leave");
  add_action("do_leave","step");
  add_action("climb", "climb");
}

do_leave(string str)
{
  if (QVB == "leave")
  {
    if (!strlen(str) ||
	(str != "chimney" &&
	 str != "the chimney"))
    {
      if (!sizeof(TP->query_team()) &&
          !sizeof(TP->query_team_others()))
      {
        write("Leave what?\n");
	return 1;
      }
      NF0("Leave what?\n");
    }
  }
  else
  {
    if (!strlen(str) ||
	!parse_command(str, ({}), "[onto] [a] / [the] [narrow] 'ledge'"))
    {
      NF0("Step where?\n");
    }
  }

  write("You squeeze yourself through the narrow opening onto the ledge.\n");
  TP->move_living("onto the ledge", THIS_DIR + "ledge2", 1);
  return 1;
}

climb(string str)
{
  NF("Climb what?\n");
  if (str == "up" ||
      str == "up chimney" ||
      str == "up the chimney")
  {
    if(up_room)
      return climb_up();
    else
    {
      write("You cannot climb up here.\n");
      return 1;
    }
  }
  if (str == "down" ||
      str == "down chimney" ||
      str == "down the chimney")
  {
    write("You cannot climb down here.\n");
    return 1;
  }
  return 0;
}
int
climb_up()
{
  int skillvalue, rnd;
  skillvalue = TP->query_skill(SS_CLIMB);
// skillvalue = TP->query_skill(SS_CLIMB);
skillvalue = ((TP->query_skill(SS_CLIMB) - 5) * 2);
  if (skillvalue < 15)
  {
    write(BS("You examine the wall closely and realize that you are not sufficiently " +
      "skilled in climbing, so you dare not to try it.\n"));
      return 1;
  }
  rnd = random(20);
  if (skillvalue + rnd > 40)
  {
    write("You skillfully climb up in the chimney.\n");
    say(QCTNAME(TP) + " climbs up.\n", TP);
    TP->move_living("M", up_room, 1);
    TP->add_fatigue((rnd+skillvalue)/6 - 25);
    say(QCTNAME(TP) + " arrives climbing up from below.\n", TP);
    return 1;
  }
  write("You try to climb higher, but you lose your grip!\n");
  say(QCTNAME(TP) + " begins to climb higher, but "+
    TP->query_pronoun() + " loses " +
    TP->query_possessive() + " grip and falls down again!\n", TP);
  return 1;
}


do_fall(object player, int height)
{
  int acrobat, dex, hurt;
  object egg;

  acrobat = TP->query_skill(SS_ACROBAT);
  if(acrobat > 25) acrobat = 25;
  dex = TP->query_stat(SS_DEX);
  if(dex > 100) dex = 100;
  hurt = height*height*20 - acrobat*2 - dex/2;
  if(hurt < height*height*10) hurt = height*height*10;
  hurt = hurt*3 + random(hurt*4);
  write("You crash to the ground at the bottom of the chimney.\n");
  say(QCTNAME(TP) + " falls down from higher up in the chimney.\n");
  TP->heal_hp(-hurt);
  if(objectp(egg = present("egg",TP)))
  {
    write("The "+egg->query_short()+" shatters.\n");
    egg->remove_object();
  }
  if (TP->query_hp() <= 0)
  {
    TP->do_die(TO);
    write_file("/d/Gondor/log/climb", TP->query_name() + " died climbing in the White Mountains in the chimney. " +
      "Avg_stat = " + TP->query_average_stat() + ", climbing = " + TP->query_skill(SS_CLIMB) + ", " + ctime(time())+".\n");
  }
  return;
}
