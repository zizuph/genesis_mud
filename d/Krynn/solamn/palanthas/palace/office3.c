/* created by Aridor 09/14/93 */

#include "../local.h"

inherit CITY_ROOMBASE;

#include <macros.h>

int pen = 1;

string
query_to_jail()
{
  return "east";
}

void
reset_palan_room()
{
    if (!pen) pen = 1;
}

void
create_palan_room()
{
    set_short("Waiting Room");
    set_long("This is the waiting room. There are several chairs here "
          +  "and a little table. Otherwise, the room is rather empty "
          +  "except for the attendant standing by the door.\n");

    INSIDE;
    LIGHT;

  add_item(({"chair","chairs"}),"These are just normal chairs to sit down.\n");
    add_item("table","@@table_desc");
    add_item("feather","@@feather_desc");
    add_item("attendant","He is just standing by the door and seems pretty "
         +   "bored. You wonder what his job is.\n");
    add_cmd_item(({"pen","feather"}),({"take","get"}),"@@take_the_feather");
    add_cmd_item(({"feather","pen"}),({"put","drop"}),"@@put_the_feather");
    add_exit(PALACE + "hall3","east","@@only_without_pen",0);
}


string
table_desc()
{
    if (pen)
        return "A wooden table with a feather lying on top.\n";
    else
        return "A wooden table with nothing on top.\n";
}

string
feather_desc()
{
    if (pen)
        return "It's a normal feather with some blue spots on it.\n";
    else
        return "You can't find a feather.\n";
}


int
take_the_feather()
{
    if (pen)
    {
        write("You take the feather from the table.\n");
        say(QCTNAME(TP) + " takes a feather from the table.\n");
        clone_object(OBJ + "pen")->move(TP);
        pen = 0;
        return 1;
    }
    NF("Take what?");
    return 0;
}


int
put_the_feather()
{
    object the_pen = present("pen_feather", TP);
    if (the_pen)
    {
        write("You put the feather back on the table.\n");
        say(QCTNAME(TP) + " puts a feather on the table.\n");
        the_pen->remove_object();
        pen = 1;
        return 1;
     }
     NF("Put what?");
     return 0;
}


int
only_without_pen()
{
    object the_pen = present("pen_feather", TP);
    if (the_pen)
    {
        write("Hey! We don't want our inventory to wander off all the "
           +  "time! Leave the pen here. The attendant prevents you from "
           +  "leaving the room.\n");
        say(QCTNAME(TP) + " was prevented by the attendant to leave the "
          + "room.\n");
        return 1;
    }
    return 0;
}


