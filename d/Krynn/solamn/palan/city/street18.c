/* created by Aridor 06/21/93 */

#include "../local.h"

inherit STREET_BASE

#include <macros.h>
#define IN_WALL    ROOM + "wall"

int door_open = 0;
object minst;

string
query_to_jail()
{
  return "west";
}


void
reset_palan_room()
{
    //    if (minst)
      //      return;
    //    minst = clone_object(LIV + "minstrel");
    //    minst->move(TO);
}


void
create_palan_room()
{
    set_short("Eastern outskirts of Palanthas");
    set_long("@@my_long");

    add_exit(ROOM + "street7","north","@@bend_north_west",1);
    add_exit(ROOM + "street2","south","@@bend_south_west",1);
    add_exit(ROOM + "street6","west",0,1);
    add_exit(ROOM + "knight1","northwest",0,1);

    add_item(({"villas","green"}),
	     "To your northwest you can see a lot of trees, almost a garden." +
	     " The villas are hidden behind the green, so you can't see much" +
	     " of them.\n");
    add_item(({"wall","city wall"}),
	     "The city wall surrounds the entire city, except at the " +
	     "harbour to the north. It is made of big and small stone " +
	     "blocks.\n");
    add_item(({"stone blocks","blocks","stones","stone","block"}),
	     "They look like ordinary stone blocks, some of them are big, " +
	     "others are small.\n");
    add_item(({"big stone blocks","big stone block","big stone","big block",
		 "big block","big stones"}),
	     "Some of the are really big and heavy.\n");
    add_item(({"small stone blocks","small stone block","small stone",
		 "small block","small blocks","small stones"}),
	     "These small stones are used to fill the spaces between the big" +
	     " blocks. You notice that one of the small stones seems loose.\n");
    add_item(({"hole"}),
	     VBFC_ME("examine_the_hole"));

    add_cmd_item(({"small stone","small block"}),
		 ({"pry","get","push","press"}),
		 VBFC_ME("secret_door_opens"));
    add_cmd_item(({"hole"}),({"enter"}),
		 VBFC_ME("go_into_the_wall"));

    add_cmd_item(({"north sign","n sign"}),({"read","exa","examine"}),
	     "This sign says: Circle Street.\n");
    add_cmd_item(({"south sign","s sign"}),({"read","exa","examine"}),
	     "The sign pointing south says: Circle Street.\n");
    add_cmd_item(({"west sign","w sign"}),({"read","exa","examine"}),
	     "You read: Paladine Street.\n");
    add_cmd_item(({"northwest sign", "nw sign"}),({"read","exa","examine"}),
	     "The sign declares: Knights' Avenue.\n");
    add_cmd_item(({"signs"}),({"read","exa","examine"}),
	     "You have to be specific, which sign do you want to read?\n");
    add_cmd_item(({"sign"}),({"read","exa","examine"}),
	     "Which of the signs do you want to read?\n");

    reset_room();
}


my_long()
{
    return "These are the eastern outskirts of Palanthas. This is the " +
      "eastern edge of the city, the city wall is right to your east. " +
      (door_open ? "There is a hole in the wall. " : "") +
      "Villas with lots of green mark this part of the city. To the " +
      "northwest you can make out some especially noble villas. There are " +
      "small signs pointing north, south, northwest and west.\n";
}


int
bend_south_west()
{
    write("The street bends southwest.\n");
    return 0;
}

int
bend_north_west()
{
    write("The street bends northwest.\n");
    return 0;
}


string
secret_door_opens()
{
    seteuid(getuid(TO));
    if (door_open)
      write("Nothing happens.\n");
    else
      {
	  tell_room(IN_WALL,"One of the big stone blocks moves silently " +
		    "into the room, revealing a hole to your west.\n");
	  tell_room(TO,"One of the big stone blocks moves silently inside " +
		    "the wall, revealing a hole.\n");
	  door_open = 1;
	  add_exit(IN_WALL,"east");
	  set_alarm(25.0,0.0,"secret_door_closes");
      }
    return "";
}

void
secret_door_closes()
{
    if (!door_open)
      return;
    tell_room(IN_WALL,"One of the big stone blocks moves silently back " +
	      "into the wall, closing the hole.\n");
    tell_room(TO,"One of the big stone blocks moves silently out from " +
	      "inside the wall, closing the hole.\n");
    door_open = 0;
    remove_exit("east");
    (IN_WALL)->remove_exit("west");
}


string
go_into_the_wall()
{
    if (!door_open)
      {
	  write("What?\n");
	  return "";
      }
    write("You enter the hole and find yourself in a small dark room " +
	  "inside the city walls.\n");
    say(QCTNAME(TP) + " leaves into the hole in the city wall.\n");
    TP->move_living("into the hole",IN_WALL, 1, 0);
    return "";
}


string
examine_the_hole()
{
    if (door_open)
      return "It's a hole into the city wall. Inside you can't see " +
	"anything since it's dark there. You think it's large enough that " +
	"you can fit through.\n";
    else
      return "You find no hole.\n";
}


int
query_door_open()
{ return door_open; }

