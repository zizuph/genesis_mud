#include "/d/Ansalon/common/defs.h"
#include "../local.h"
#include <macros.h>
#include <stdproperties.h>

inherit KEN_IN;

void
reset_kendermore_room()
{
    return;
}

create_kendermore_room()
{
    set_short("@@short_descr");
    set_long("@@long_descr");

    add_item(({"earthen walls","walls"}),
      "The earthen walls here consist of a rich brown soil, " +
      "truly a farmers wet dream.\n");
    add_item(({"glow-worms","glow worms","worms","jars"}),
      "Many jars full of glow-worms stand wherever there is " +
      "room. The light from these numerous jars light the " +
      "room spectacularly.\n");
    add_item(({"chain","ground"}),
      "Attached to the ground is one end of a solid iron chain. " +
      "The other end is attached to a book that rests on the floor. " +
      "You wonder what sort of people live around here that items " +
      "have to be chained to the floor?\n");
    add_item(({"twisted root","root"}),
      "A twisted root twirls upwards from here. You could go up it " +
      "if you wanted to.\n");
    add_item(({"book","leather-bound book"}),
      "Attached to a strong iron chain is a leather-bound " +
      "book. You could probably read it if you wanted to.\n");

    add_exit(KROOM + "r2","up","@@go_up");

    add_cmd_item(({"jar","jars","glow-worms","worms"}),
      ({"get","take","pick up"}),"@@get_worms");
    add_cmd_item("book",({"get","take"}),"@@get_book");

    reset_kendermore_room();
}

string
get_worms()
{
    write("You go to pick up a jar of glow-worms, but something " +
      "distracts you, and you forget about it.\n");
    say(QCTNAME(TP)+ " moves to pick up a jar of glow-worms, " +
      "but suddenly " +HE(TP)+ " is distracted, and forgets " +
      "about it.\n");
    return "";
}

string
get_book()
{
    write("You pick up the book but notice " +
      "it is chained to the floor, probably to stop " +
      "thieves, so you put it back on the floor again.\n");
    say(QCTNAME(TP)+ " picks up the book on the floor, " +
      "but then notices its chained and " +HE(TP)+ " can't go " +
      "anywhere with it. " +QCTNAME(TP)+ " puts the " +
      "book back on the floor.\n");
    return "";
}

int
go_up()
{
    write("You make your way up the twisty root stairway...\n");
    return 0;
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
    string page;

    NF("Read what page? Use 'read <page number>'.\n");
    if(!str)
    	return 0;

    if (sscanf(str, "page %s", page))
        str = page;
    
    switch(str)
    {
        case "leather-bound book":
        case "book":
        case "index":
            str = "1";
        case "1":
        case "2":
        case "3":
        case "4":
        case "5":
        case "6":
        case "7":
        case "8":
        case "9":
            write("You turn in the book to page " +
              str+ " and begin to read...\n");
            say(QCTNAME(TP)+ " turns to a page in the book " +
              "and begins to read.\n");
            TP->more(read_file(KTEXT + str),0);
            break;
        default:
            NF("There is no page number " +str+ " in this book.\n");
            return 0;
    }
    return 1;
}

string
short_descr()
{
    return "In a pleasant underground room beneath a giant oak tree.\n" +
    "A book is chained to the floor here";
}

string
long_descr()
{
    return "You are standing in a small underground room " +
    "beneath a giant oak tree. The earthen walls here are " +
    "pleasantly warm, and numerous jars filled with glow-worms " +
    "light the room in a fantastical way. On the floor rests a " +
    "book attached to a chain, the chain being secured firmly to " +
    "the ground to prevent the books removal. A twisted root twirls " +
    "upwards from here, and you could probably climb them like a " +
    "set of stairs.\nA book is chained to the floor here.\n";
}
