/* A ladder used in the apple tree questin solace */

inherit "/std/object";
#include "/d/Krynn/common/defs.h"
#include "../local.h"
#include <stdproperties.h>
#include <macros.h>

#define START_ROOM HOUSE + "house1"

int moves;

void owner_arrives();

create_object()
{
    moves = 0;

    set_name("ladder");
    set_adj("wooden");
    set_short("@@my_short");
    set_long("It's a wooden ladder, it's very long and looks heavy.\n");

    add_prop(OBJ_I_WEIGHT, 70000);
    add_prop(OBJ_I_VOLUME, 60000);
    add_prop(OBJ_I_VALUE, 0);

    seteuid(getuid());
}

init()
{
    ADA("push");
    ADD("push", "move");
    ADA("climb");
}

push(str)
{
    string *ss, to, cond;
    mixed *arr;
    int i, result;
    object from;

    NF("Push what?\n");

    if (!str)
	return 0;
    ss = explode(str, " ");
    if (ss[0] != "ladder")
	return 0;
    
    NF("Push ladder where?\n");
    if (sizeof(ss) == 1)
	return 0;

    if (!(from = E(TO)))
	return 0;

    switch(ss[1])
      {
	case "w": ss[1] = "west";
	          break;
	case "n": ss[1] = "north";
	          break;
	case "e": ss[1] = "east";
	          break;
	case "s": ss[1] = "south";
	          break;
	case "se": ss[1] = "southeast";
	           break;
	case "sw": ss[1] = "southwest";
	           break;
	case "ne": ss[1] = "northeast";
	           break;
	case "nw": ss[1] = "northwest";
	           break;
	case "u": ss[1] = "up";
	          break;
	case "d": ss[1] = "down";
	          break;
      }


    arr = from->query_exit();
    for (i = 1; i < sizeof(arr); i += 3)
    {
	if (arr[i] == ss[1])
	{	    
		to = arr[i - 1];

		if (intp(arr[i + 1]))
		{
			result = arr[i + 1];
		} 
		if (!intp(arr[i + 1]))
		{
	    		cond = extract(arr[i + 1], 2);
			result = call_other(from, cond);
		}
		if (result)
		{
			NF("You can't push the ladder there!\n");
			return 0;
		}
	    if (!move(to))
	    {
		tell_room(from, QCTNAME(TP) + " pushes the ladder " + ss[1] + 
				".\n", TP);
		tell_room(to, "A ladder arrives.\n");
		write("You pushed the ladder " + ss[1] + ".\n");
		moves++;
		if (moves > 15)
		    set_alarm(8.0, 0.0, owner_arrives);
		return 1;
	    }
	}
    }

    NF("No direction " + ss[1] + " found.\n");
    return 0;
}

my_short()
{
    string name, str1, str2;

    if (living(E(TO)))
	return "large wooden ladder";

    if (!E(TO)->query_prop(ROOM_I_INSIDE))
	return "large wooden ladder";
    return "large wooden ladder on the ground";
}

void
owner_arrives()
{
    moves = 0;
    tell_room(E(TO),
	"A man arrives screaming: There is my ladder, give it to me!\n" +
	"The next second both man and the ladder are gone.\n");
    move(START_ROOM);
    tell_room(find_object(START_ROOM),
	"The house owner arrives with his ladder under one arm and puts it\n" +
	"on the ground, then disappears.\n");
}

climb(str)
{
    NF("Climb what?\n");
    if (str != "ladder")
	return 0;

    write("You lean the ladder up, then climb up and down the ladder. " +
          "It was fun!\n");
    say(QCTNAME(TP) + " leans a ladder up, then climbs up and down it.\n");

    return 1;
}

