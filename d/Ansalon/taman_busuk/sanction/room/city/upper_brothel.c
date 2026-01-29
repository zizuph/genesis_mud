#include "/d/Ansalon/common/defs.h"
#include "/d/Ansalon/taman_busuk/sanction/local.h"

inherit SANCINROOM;

object pro;

reset_sanction_room()
{
    if(!objectp(pro))
    {
	pro = clone_object(SNPC + "prostitute");
	pro->move(TO);
    }
}

void
create_sanction_room()
{
    set_short("In a bedroom of the Naked Sylph, Sanction's "+
      "local brothel");
    set_long("@@long_descr");

    add_item(({"bedroom","room"}),
      "@@long_descr");
    add_item("bed","A largish bed sits to the side of " +
      "the room. You remember it as being a little lumpy.\n");
    add_item("door","A door, slightly ajar, leads out " +
      "to the east.\n");
    add_item("hallway","To your east is a hallway on " +
      "the top level of the Naked Sylph.\n");

    add_exit(SCITY + "brothel","east","@@go_down");
    reset_sanction_room();
}

int
go_down()
{
    write("You hurry out the small bedroom and down " +
      "a flight of steps to the lower floor of the brothel...\n\n");
    return 0;
}

string
long_descr()
{
    return "You find yourself in a bedroom within the " +
    "Naked Sylph, a brothel where you spent the night " +
    "enjoying the pleasures of a skilled courtesan. " +
    "The room is rather small, with the bed being the " +
    "primary feature of the room. A door to the east leads " +
    "out to a hallway.\n";
}
