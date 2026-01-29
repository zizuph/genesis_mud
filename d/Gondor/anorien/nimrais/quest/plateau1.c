inherit "/d/Gondor/common/room";
#include "/d/Gondor/defs.h"
#include <ss_types.h>
#include <macros.h>
#include <stdproperties.h>
#include "/d/Gondor/common/lib/herbsearch.h"
#include "dirdefs.h".

#define DOWN_ROOM    "chimney4"

string down_room;

void reset_room();

void
create_room()
{
  set_long(BS("You are on a small plateau next to the top of a narrow chimney in the " +
    "White Mountains. It's a very uncomfortable place. Above you can " +
    "see a projecting rock. On three sides of the plateau, the walls are falling " +
    "down far too steep for climbing. To the southeast, there is " +
    "a rocky slope that is limited to the east by a broad cleft. On the other side of the cleft, " +
    "that ends here in a narrow chimney, a smooth wall is vertically rising " +
    "up to the projecting rock above your head. You can enter the chimney by climbing down " +
    "but it looks as if it extends far down. \n"));
  set_short("On a small plateau high up in the White Mountains");
  add_item(({ "wall", "rock wall" }), BS("The wall on the other side of the chimney is rather steep, "
    + "and since the chimney is too broad, you cannot climb it.\n"));
  add_item(({ "rock", "projecting rock" }), "You can't see what's on it " +
    "from here.\n");
  add_item("chimney", BS(
    "This is a narrow chimney, going straight down between the rock walls.\n"));
  add_item(({"slope", "plateau"}), BSN(
    "The plateau extends to the southeast where goes over into " +
    "a rocky slope that is surrounded by steep rock cliffs and a " +
    "broad cleft. In a few protected places on the plateau you can " +
    "see a little green growing."));
  add_item(({"cleft"}), BSN(
    "The chimney east of here continues to the south, where it " +
    "changes into a broad cleft. "));
  add_prop(OBJ_S_SEARCH_FUN,"herb_search");
  add_prop(OBJ_I_SEARCH_TIME,8);
  set_search_places(({"ground","plateau", "slope", "rock"}));
  add_herb_file(HERB_DIR+"frostheal");
  add_herb_file(HERB_DIR+"madwort");
  add_exit(THIS_DIR + "plateau2", "southeast", 0, 2);
  seteuid(getuid());
  down_room = (THIS_DIR + DOWN_ROOM);
  if(down_room) down_room->load_me();
}

init()
{
  ::init();
  add_action("climb", "climb");
}

climb(string str)
{
  NF("Climb what?\n");
  if (str == "down")
  {
    if(down_room)
      return climb_down();
    else
    {
      write("You cannot climb down here.\n");
      return 1;
    }
  }
  if (str == "up")
  {
    write("You cannot climb up here.\n");
    return 1;
  }
  return 0;
}
int
climb_down()
{
  int skillvalue, rnd;
// skillvalue = TP->query_skill(SS_CLIMB);  /* old */
skillvalue = ((TP->query_skill(SS_CLIMB) - 5) * 2);
  if (skillvalue < 10)
  {
    write(BS("You examine the chimney closely and realize that you are not sufficiently " +
      "skilled in climbing, so you dare not to try it.\n"));
      return 1;
  }
  rnd = random(20);
  if (skillvalue + rnd > 35)
  {
    write("You skillfully climb down in the chimney.\n");
    say(QCTNAME(TP) + " climbs down, entering the chimney.\n", TP);
    TP->move_living("M", down_room, 1);
    TP->add_fatigue((rnd+skillvalue)/6 - 25);
    say(QCTNAME(TP) + " arrives climbing down from the plateau above.\n", TP);
    return 1;
  }
  write("You try to climb down, but you lose your grip!\n");
  say(QCTNAME(TP) + " begins to climb higher, but "+
    TP->query_pronoun() + " loses " +
    TP->query_possessive() + " grip and falls down again!\n", TP);
  return 1;
}


do_fall(object player, int height)
{
  if(!height)
    write("AAARRRRGGGHHH!!! You fall.\n\n");
  else
    write("\nYou continue to fall down.\n\n");

  height = height + 1;

  tell_room(down_room, "You hear a terrible scream as someone falls down from above.\n");
  player->move_living("M", down_room, 1);
  down_room->do_fall(player, height);
  return;
}

void reset_room()
{
    set_searched(0);
}
