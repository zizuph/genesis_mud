/* created by Aridor 06/21/93 */

#include "../local.h"

inherit STREET_BASE

object lady;

string
query_to_jail()
{
  return "west";
}

void
reset_palan_room()
{
    if (lady)
      return;
    lady = clone_object(LIV + "lady");
    lady->move(TO);
}

void
create_palan_room()
{

    set_short("Eastern parts of Palanthas");
    set_long("In this part of Palanthas are only residences. The houses " +
	     "belong to the more wealthy people and seem to be well cared " +
	     "for. They are spaced so openly, that trees and flowers are " +
	     "all around, too. The street appears to be clean also, and no " +
	     "people just hang around, everyone is absorbed in his or her " +
	     "own matters.\n");

    add_exit(ROOM + "street18","east",0,1);
    add_exit(ROOM + "plaza","west",0,1);

    add_item(({"residence","house","residences","houses"}),
	     "The houses in this street belong to noble people of the city.\n");

    reset_room();
}
