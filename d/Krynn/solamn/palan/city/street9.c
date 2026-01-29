/* created by Aridor 06/21/93 */

#include <composite.h>
#include "../local.h"

inherit STREET_BASE

object farmer;

string
query_to_jail()
{
  return "east";
}

void
reset_palan_room()
{
    if (farmer)
      return;
    farmer = clone_object(LIV + "farmer");
    farmer->move(TO);
}

void
create_palan_room()
{

    set_short("Western part of Palanthas");
    set_long(BS("You are in the western outskirts of Palanthas. Not many "
        +    "houses "
        +    "are around here any more, these are mostly gardens. The street "
        +    "leading off to the east looks very interesting, maybe you "
        +    "should take a look. From the north you can already smell the "
        +    "fresh and salty air of the harbour. There are signs pointing "
        +    "in all directions.",SL));

    OUTSIDE;

    add_item(({"north sign","n sign"}),"It reads:  Circle Street.\n");
    add_item(({"south sign","s sign"}),"The sign reads:  Circle Street.\n");
    add_item(({"east sign","e sign"}),"You read:  Paladine Street.\n");
    add_item(({"west sign","w sign"}),"The sign says:  Gate Road.\n");
    add_item("signs","Which of the signs do you want to read?\n");
    add_item("sign","You have to be specific which sign you want to read.\n");
    add_cmd_item(({"north sign","n sign"}),"read",
		 "It reads:  Circle Street.\n");
    add_cmd_item(({"south sign","s sign"}),"read",
		 "The sign reads:  Circle Street.\n");
    add_cmd_item(({"east sign","e sign"}),"read",
		 "You read:  Paladine Street.\n");
    add_cmd_item(({"west sign","w sign"}),"read",
		 "The sign says:  Gate Road.\n");
    add_cmd_item("signs","read","Which of the signs do you want to read?\n");
    add_cmd_item("sign","read",
		 "You have to be specific which sign you want to read.\n");

    add_exit(ROOM + "street15","north","@@bend_north_east",1);
    add_exit(ROOM + "street8","south","@@bend_south_east",1);
    add_exit(ROOM + "street20","east",0,1);
    add_exit(ROOM + "wgate","west",0,1);

    reset_room();
}

void
init()
{
    ::init();
    ADA("look");

}

int
bend_south_east()
{
  write("The street bends to the southeast.\n");
  return 0;
}

int
bend_north_east()
{
  write("The street bends to the northeast.\n");
  return 0;
}

int
look(string str)
{
    mixed *exits;
    int i;
    string dummy;
    object where, *things;
    if (!str)
      return 0;
    exits = query_exit_cmds();
    for (i = 0; i < sizeof(exits); i++)
      if (exits[i] == str)
	break;
    if (i >= sizeof(exits))
      return 0;
    query_exit_rooms()[i]->load_me();
    where = find_object(query_exit_rooms()[i]);
    things = all_inventory(where);
    write("To the " + str + " you see:\n");
    write(where->long());
    dummy = capitalize(COMPOSITE_DEAD(things));
    if (dummy != "Something")
      write(dummy + ".\n");
    return 1;
}

