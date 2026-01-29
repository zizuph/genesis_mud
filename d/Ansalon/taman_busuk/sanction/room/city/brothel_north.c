#include "/d/Ansalon/common/defs.h"
#include "/d/Ansalon/taman_busuk/sanction/local.h"

inherit SANCINROOM;


void
create_sanction_room()
{
    set_short("Behind a drape in the brothel of the Naked Sylph.\n"+
      "You can go south through the drape here");
    set_long("@@long_descr");

    add_item(({"dark red drape","red drape","drape"}),
      "A dark red drape hangs from the ceiling here. You could " +
      "probably find your way out of this area and back into the " +
      "brothel's foyer if you headed south.\n");
    add_item(({"trapdoor","open trapdoor"}),
      "A trapdoor stands open here, leading down into the basement.\n");
    add_item("basement",
      "You can't make out much from up here except for a soft light " +
      "about ten feet down.\n");
    add_item("brothel",
      "You are standing in a brothel. If only your mother could see " +
      "you now!\n");

    add_invis_exit(SCITY + "brothel","south","@@exit_drapes");
    add_invis_exit(SCITY + "pawn","down","@@go_down");

    add_cmd_item("trapdoor",({"close","open"}),"@@close_trapdoor");
}

int
exit_drapes()
{
    write("You wade your way through the drapes to the brothel foyer.\n");
    return 0;
}

int
go_down()
{
    write("You climb down through the trapdoor...\n\n"+
      "Welcome rogue, to the Underworld of Sanction!\n\n");
    return 0;
}

string
close_trapdoor()
{
    write("The trapdoor is secured open. You cannot do that.\n");
    return "";
}


string
long_descr()
{
    return "You stand behind a red drape that hangs from the ceiling in " +
    "the brothel of the Naked Sylph. At your feet is an open trapdoor, " +
    "leading down into the basement.\nYou can go south through the " +
    "drape here.\n";
}
