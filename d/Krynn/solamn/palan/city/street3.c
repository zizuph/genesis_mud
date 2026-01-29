/* created by Aridor 06/21/93 */

#include "../local.h"

inherit STREET_BASE

object knight;

string
query_to_jail()
{
  return "north";
}

void
reset_palan_room()
{
    if (knight)
      return;
    knight = clone_object(LIV + "ret_knight");
    knight->move(TO);
}

void
create_palan_room()
{

    set_short("Library Lane in southern Palanthas");
    set_long(BS("You are in the southern parts of Palanthas. "
        +    "An important looking building is to your east. It "
        +    "also seems to be old but good taken care of and "
        +    "freshly painted. There is a sign above "
        +    "the door to your east. "
        +    "A lot of people seem to be using the street to "
        +    "get to the central plaza which lies to the north.",SL));

    add_exit(ROOM + "street1","south",0,1);
    add_exit(ROOM + "plaza","north",0,1);
    add_exit(LIBRARY_PUBLIC,"east","@@inform_ari@@",1);
    //add_exit(ROOM + "flame","west",0,1);

    add_cmd_item("sign","read",
		 "The sign above the door to your east reads:\n" +
		 "                  LIBRARY\n");
    add_item("sign",
	     "The sign above the door to your east reads:\n" +
	     "                  LIBRARY\n");
    add_item("building",
	     "Which building do you want to look at? The west or " +
	     "the east building?\n");
    add_item("west building",
	     "It's a new building, and looks like a temple of " +
	     "some sort, but you won't know what to find " +
	     "in there until you go in yourself...\n");
    add_item("east building",
	     "It is a large building stretching all the way to the plaza in " +
	     "north and to Circle Street in the south. The building itself " +
	     "is rather spartan looking, but you sense a presence of forever, " +
	     "past, present and future mingled together radiating from the " +
	     "building. A sign hangs above the door.\n");
    add_item("buildings",
	     "You can't look at both buildings at the same time. You need " +
	     "to turn around for that, so look at the east and then the west " +
	     "building (or the other way around if you like).\n");
    reset_room();
}


int
inform_ari()
{
    find_living("aridor")->catch_msg(TP->query_name() + " enters the library.\n");
    return 0;
}

