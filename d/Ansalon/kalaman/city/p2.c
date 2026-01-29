#include "/d/Ansalon/common/defs.h"
#include "../local.h"
#include <macros.h>
#include <stdproperties.h>

inherit KALAMAN_IN;
object n1,n2,n3,n4;

void
reset_kalaman_room()
{
    if(!objectp(n1))
    {
	n1 = clone_object(KNPC + "noble");
	n1->arm_me();
	n1->move(TO);
    }

    if(!objectp(n2))
    {
	n2 = clone_object(KNPC + "noble");
	n2->arm_me();
	n2->move(TO);
    }

    if(!objectp(n3))
    {
	n3 = clone_object(KNPC + "noble");
	n3->arm_me();
	n3->move(TO);
    }

    if(!objectp(n4))
    {
	n4 = clone_object(KNPC + "noble");
	n4->arm_me();
	n4->move(TO);
    }
}

create_kalaman_room()
{
    set_long("@@long_descr");
    set_short("Entrance hall within the palace of Kalaman");

    add_item(({"hall","entrance hall"}),"@@long_descr");
    add_item(({"sumptuous furnishings","furnishings"}),
      "Expensive furnishings surround you, here to keep " +
      "visiting nobles and dignitaries comfortable while " +
      "they wait for the Lord of Kalaman.\n");

    add_exit(CITY  + "p1","north",0);
    add_exit(CITY + "p3","south",0);

    reset_kalaman_room();
}

string
long_descr()
{
    return "You stand in an impressive entrance hall within " +
    "the palace of Kalaman. Ornate and sumptuous furnishings " +
    "surround you, obviously used by nobles and influential citizens who " +
    "wait for an audience with the Lord of Kalaman " +
    "and his council.\n";
}
