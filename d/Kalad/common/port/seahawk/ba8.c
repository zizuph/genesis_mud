#include "../default.h"
inherit PORT_ROOM;

void
create_port_room()
{
    set_short("A dark, dismal section of the prison");
    set_long("This is a dark corner of the prison cell.\n"+
      "This area seems particularly bleak, its walls and floor covered "+
      "with grime and filth. From beneath the floor boards can be heard the "+
      "chittering of rats.\n");
    add_item(({"walls","wall","floor"}),"The entire cell is filled with "+
      "human waste combined with those of the ever present rats. The "+
      "disgusting combination results in an odor most foul to your sense "+
      "of smell.\n");
    add_item(({"grime","filth"}),"It covers the walls and floor, making "+
      "you sick to your stomach.\n");
    add_item(({"floor boards","boards","board"}),"The wooden planks "+
      "are riddled with tiny three inch holes, from which the sound of "+
      "chittering can be heard.\n");

    add_prop(ROOM_I_INSIDE,1);

    add_exit(PORT + "seahawk/ba5", "east",0,0,4);
    add_exit(PORT + "seahawk/ba9", "south",0,0,4);
}

