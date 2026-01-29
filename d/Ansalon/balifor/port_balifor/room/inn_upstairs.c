#include "/d/Ansalon/common/defs.h"
#include "/d/Ansalon/balifor/local.h"

inherit         BALIFOR_IN;

void
reset_balifor_room()
{
return;
}

create_balifor_room()
{
set_short("Upstairs at the Pig and Whistle Inn");
set_long("@@long_descr");

add_exit(BROOM + "inn", "down", "@@down", 0);

reset_balifor_room();
}

string
long_descr()
{
return "This is the room rented out by the owner of the " +
"Pig and Whistle Inn. If you have paid him for the " +
"the room, you may spend the night, and wake here " +
"in the morning.\n";
}

string
down()
{
write("You climb down the stairway.\n");
return 0;
}
