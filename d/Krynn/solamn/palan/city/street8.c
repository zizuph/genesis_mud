/* created by Aridor 06/21/93 */

#include "../local.h"

inherit STREET_BASE

object maid;

string
query_to_jail()
{
  return "northeast";
}

void
reset_palan_room()
{
    if (maid)
      return;
    maid = clone_object(LIV + "maid");
    maid->move(TO);
}

void
create_palan_room()
{

    set_short("Southwestern outskirts of Palanthas");
    set_long("The houses around here are mainly private houses. People are " +
	     "heading to the northeast and you can see a dark tower looming " +
	     "above the roofs to the north. Further away you see a white " +
	     "tower sparkling in the sunlight. Circle Street continues to " +
	     "the northwest and southeast. A big red sign hangs above the " +
	     "entrance to the south.\n");

    add_item("sign",
	     "The sign says there is a Post Office in this building.\n");
    add_cmd_item("sign","read",
		 "The sign says there is a Post Office in this building.\n");

    add_exit(ROOM + "street1","southeast","@@bend_east",1);
    add_exit(ROOM + "street9","northwest","@@bend_north",1);
    add_exit(ROOM + "street10","northeast",0,1);
    add_exit(ROOM + "post","south",0,0);

    reset_room();
}


int
bend_east()
{
  write("The street bends to the east.\n");
  return 0;
}

int
bend_north()
{
  write("The street bends to the north.\n");
  return 0;
}

