#pragma strict_types

inherit "/std/object.c";
#include <macros.h>
#include <stdproperties.h>
#include "/d/Gondor/defs.h"

// Prototypes:
public string  long_func();
public object  setup_boat();

// Global variables:
static object  Boat_room;

public void
create_object()
{
    set_name("boat");
    add_name("rowing boat");
    set_adj("rowing");
    set_adj("wooden");
    set_short("wooden rowing boat");
    set_long(long_func);
    add_prop(OBJ_M_NO_GET,1);
    add_prop(OBJ_I_WEIGHT,400000);
    add_prop(OBJ_I_VOLUME,10000);
    setup_boat();

}

public int
enter_boat(string str)
{
    if (str != "boat" && str != "in boat" && str != "aboard boat")
    {
	NF(CAP(query_verb()) + " what?\n");
	return 0;
    }
    ENV(TP)->set_dircmd(str);

    write("You climb aboard the wooden boat.\n");
    setup_boat();
    TP->move_living("boarding the boat", Boat_room);
    return 1;
}

public object
setup_boat()
{
    seteuid(getuid(TO));
    if (!objectp(Boat_room))
    {
	Boat_room = clone_object(COMMON_DIR + "misc/inboat");
	Boat_room->set_boat_obj(TO);
    }
    return Boat_room;
}

public int
no_of_persons()
{
    if (!objectp(Boat_room))
	setup_boat();
    return Boat_room->query_livings();
}

public string
long_func()
{
    string  longstr,
            pers;
    int     i;

    switch (i = no_of_persons())
    {
        case 0:
            pers = "are no persons";
            break;
        case 1:
            pers = "is one person";
            break;
        default:
            pers = "are "+LANG_WNUM(i)+" persons";
            break;
    }

  longstr = "It is a little rowing boat made of wood, just big enough to "+
    "hold three persons. Right now there "+pers+" in the boat. ";
  if (!present("oars", Boat_room))
    longstr += "There are no oars in the boat.\n";
  else
    longstr += "There is a pair of oars in the boat.\n";
  return BS(longstr);
}

public void
init()
{
  ::init();
  add_action(enter_boat, "embark");
  add_action(enter_boat, "enter");
  add_action(enter_boat, "use");
  add_action(enter_boat, "board");
}

