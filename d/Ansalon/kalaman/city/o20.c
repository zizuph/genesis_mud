#include "/d/Ansalon/common/defs.h"
#include "../local.h"
#include <macros.h>
#include <stdproperties.h>

inherit CITY_OUT;

void
reset_kalaman_room()
{
    return;
}

create_kalaman_room()
{
    set_long("@@long_descr");

    set_short("To the southwest of the wall surrounding Kalaman");
    add_item("wall","To your north rises the wall surrounding the city " +
      "of Kalaman.\n");
    add_item(({"city","kalaman"}),
      "You can't see much of it. A wall is in the way.\n");
    add_item(({"small path","path"}),
      "A small path, hardly noticeable, follows the edge of the wall.\n");

    add_exit(SOLPLAINS, "north", 0);
    add_exit(CITY + "o19","south",0);

    reset_kalaman_room();

    add_prop(OBJ_S_WIZINFO, "This is a quest room, enter_inv is utilized " +
      "in the quest Love or Hate in Kalaman. This is the room where the " +
      "players wanting to do the Hate episode takes Wesley the NPC after " +
      "freeing him from the prison dungeon. When he arrives here and the " +
      "player is present a group of guards will emerge from the side of " +
      "road and take Wesley with them; telling the player to go back to " +
      "lord Calof for a reward. 2011-07-04:Lunatari\n");
}

string
long_descr()
{
    return "You stand to the southwest of the wall surrounding the city of Kalaman. " +
    tod_descr1() +
    "A small path seems to follow the edge of the wall.\n";
}

/* Love or Hate Quest */
void
enter_inv(object ob, object from)
{
  ::enter_inv(ob, from);

  if ( ob->query_name("_princess_lover_") )
  {
     /* CLONE GUARDS MOVE THEM IN FROM THE BUSHES, TAKE AWAY WESLEY */
  }
}
