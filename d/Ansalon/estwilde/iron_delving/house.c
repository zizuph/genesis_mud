#include "/d/Ansalon/common/defs.h"
#include "../local.h"
#include <macros.h>
#include <stdproperties.h>

inherit DWARF_IN;
object dwarf;

void
reset_dwarf_room()
{
    if(!objectp(dwarf))
    {
	dwarf = clone_object(LIVING + "old_dwarf");
	dwarf->arm_me();
	dwarf->move(TO);
    }
}

create_dwarf_room()
{
    set_short("@@short_descr");
    set_long("@@long_descr");

    add_item(({"stone house","house","dwelling","home"}),
      "@@long_descr");
    add_item("book","A book sits on a small desk here. You can probably " +
      "read it or a particular page of the book by typing read " +
      "<page number>.\n");
    add_item(({"small desk","desk"}),
      "A small desk stands in this room. A book sits on top of it.\n");
    add_item(({"closed door","door"}),
      "A door to your south stands closed. It seems to have been " +
      "craftily made, as you see no handles or hinges on it. You " +
      "wonder if you can open it?\n");

    add_exit(IRON + "r15","northeast",0);
    add_exit(IRON + "app_room","south","@@go_south");

    add_cmd_item("door",({"open","push","pull","knock","kick","bash"}),
      "@@open_door");

    reset_dwarf_room();
}

int
open_door()
{
    if(TP->query_race() == "dwarf")
    {
	write("Ha! A simple yet craftily made dwarven portal! A " +
	  "subtle move of this loose bit here and you should be " +
	  "able to walk through it simply by going south!\n");
	return 1;
    }
    write("For some strange reason, whatever you are doing " +
      "is not helping in opening this craftily made dwarven " +
      "portal.\n");
    return 1;
}

int
go_south()
{
    if(TP->query_race() == "dwarf")
    {
	write("You move a loose portion of the door that was " +
	  "craftily hidden, opening the door and allowing you " +
	  "to go south.\n");
	say(QCTNAME(TP)+ " does something to the door to the " +
	  "south. It swings open, allowing " +HIM(TP)+ " to enter!\n");
	return 0;
    }
    write("You bump into the closed door.\n");
    say(QCTNAME(TP)+ " bumps into the closed door to the south.\n");
    return 1;
}

string
short_descr()
{
    return "A snug dwarven dwelling in Iron Delving.\n" +
    "A small desk with a book on it stands here";
}

string
long_descr()
{
    return "You are standing in a small stone house in " +
    "the dwarven community of Iron Delving. This dwelling " +
    "is rather snug and comfortable, and by the looks of things " +
    "is the home of an elderly person. A small desk stands here with " +
    "a book on it. There is a closed door to the south.\n";
}

void
init()
{
    ADA("read");
    ::init();
}

int
read(string str)
{

    NF("Read what page? Use 'read <page number>'.\n");
    if(!str)
	return 0;

    if(TP->query_race() != "dwarf")
    {
	write("The book is written in dwarven. You cannot read it.\n");
	return 1;
    }

    switch(str)
    {
    case "book":
    case "index":
	str = "1";
    case "1":
    case "2":
    case "3":
    case "4":
    case "5":
    case "6":
	write("You turn in the book to page " +str+" and begin to read...\n");
	say(QCTNAME(TP)+ " turns to a page in the book and begins to read.\n");
	TP->more(read_file(DTEXT + str), 0);
	break;
    default:
	NF("There is no page numbered "+str+" to read in the book.\n");
	return 0;
    }
    return 1;
}
