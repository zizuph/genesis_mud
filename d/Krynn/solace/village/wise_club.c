/* created by Aridor */

#include "/d/Krynn/common/defs.h"
#include "local.h"
#include <macros.h>
#define WISE_OBJECT    OBJ + "wise_object"
#define WISE_ID        "krynn_wise_object"
#define WISE_LOG       LOG + "wise_log"

inherit SOLINROOM;

void
create_solace_room()
{
    set_short("Chamber of the Wise");
    set_long("This is the inside of a simple building with " +
	     "just one room. It is furnished completely in " +
	     "wood, fitting to its surroundings. Boughs of " +
	     "a great vallenwood tree can be seens through the " +
	     "windows and it is quite obvious that you are " +
	     "high up in the tree. The room is quite bare of " +
	     "equipment, except a small sign on the wall " +
	     "and a soft carpet with an eloquent softness. " +
	     "It is here that the wise people of Genesis come " +
	     "to gather their thoughts and may even pass some " +
	     "of their wisdom on to those coming here to see " +
	     "the light.\n");
    add_item(({"wood","walls","wall","panels","panel"}),
             "The walls are furnished with wooden panels, " +
             "giving the appearance of the inside of a " +
             "tree.\n");
     add_item(({"window","windows"}),
             "Through the windows you can see the boughs of " +
             "a huge vallenwood tree all around. Light enters " +
             "the room this way, too.\n");
    add_item("sign","It's a sign with words on it.\n");
    add_item("words","They are readable.\n");
    add_cmd_item(({"sign","words"}),"read",
		 "The sign reads:\n" +
		 "+------------------------------------------------+\n" +
		 "|            The Wise People Of Genesis          |\n" +
		 "|            ==========================          |\n" +
		 "| This is the meeting room of the Wise People Of |\n" +
		 "| Genesis. You can try to become a member of the |\n" +
		 "| Wise People here with      'join wise people'. |\n" +
		 "| You will receive your pin, the token of member |\n" +
		 "| ship.  Of course, you must have achieved quite |\n" +
		 "| something before you are allowed in.    Should |\n" +
		 "| you intend to leave the Wise People again, use |\n" +
		 "| 'leave wise people'.                           |\n" +
		 "+------------------------------------------------+\n");
    add_item(({"tree","trees","vallenwood","vallenwood tree","vallenwood trees",
		 "boughs"}),
	     "The trees visible outside are vallenwoods, very tall " +
	     "trees that grow in this area of Krynn. People build " +
	     "their houses high up in these trees, and this house " +
	     "is no exception.\n");
    add_item(({"carpet","floor"}),
	     "The floor is completely covered with a huge carpet. " +
	     "It is multicolored, but no scene is displayed and the " +
	     "colors are just all mixed up.\n");
    add_exit(TDIR + "innlanding", "south");
    LIGHT;
}

void
init()
{
    ADA("join");
    ADA("leave");
    ::init();
}

int
join(string str)
{
    object obj;
    if (L(str) == "wise people" || L(str) == "the wise people" ||
	L(str) == "wise people of genesis" ||
	L(str) == "the wise people of genesis")
      {
	  if (REALAGE(TP) >= 8640000) /* 100 days!!! */
	    {
		if (P(WISE_ID,TP))
		  {
		      write("You are already a member of the Wise People!\n");
		      return 1;
		  }
		seteuid(getuid(TO));
		obj = clone_object(WISE_OBJECT);
		obj->move(TP,1);
		find_living("aridor")->catch_msg(TP->query_name() + " joined WISE.\n");
		write("WELCOME to the Wise People Of Genesis!! Congratulations!\n" +
		      "You receive a plain pin.\n");
		say(QCTNAME(TP) + " has become a Wise Person of Genesis!\n");
		write_file(WISE_LOG, TP->query_name() + " joined " + 
			   extract(ctime(time()), 4, 15) + "\n");
	    }
	  else
	    {
		write("You don't meet the requirements to join yet!\n");
		find_living("aridor")->catch_msg(TP->query_name() + " COULDN'T join WISE.\n");
	    }
      }
    else
      write("Join the Wise People maybe? You may not form a team in this room.\n");
    return 1; /* always return 1 to prevent the team joining */
}

int
leave(string str)
{
    object obj;
    if (L(str) == "wise people" || L(str) == "the wise people" ||
	L(str) == "wise people of genesis" ||
	L(str) == "the wise people of genesis")
      {
	  obj = P(WISE_ID,TP);
	  if (!obj)
	    {
		write("But you are not a member!\n");
		return 1;
	    }
	  obj->remove_object();
	  write("You leave the Wise People Of Genesis. Well, it's up to you!\n");
	  say(QCTNAME(TP) + " has left the Wise People of Genesis! :-(\n");
	  seteuid(getuid(TO));
	  write_file(WISE_LOG, TP->query_name() + " left " + 
		     extract(ctime(time()), 4, 15) + "\n");
      }
    else
      write("Leave the Wise People maybe? You may not leave a team in this room.\n");
    return 1; /* always return 1 to prevent the team leaving */
}






