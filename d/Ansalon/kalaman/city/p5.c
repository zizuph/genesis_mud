#include "/d/Ansalon/common/defs.h"
#include "../local.h"
#include <macros.h>
#include <stdproperties.h>

inherit KALAMAN_IN;
object c1, a1, a2, a3;

void
reset_kalaman_room()
{
    if(!objectp(a1))
    {
	a1 = clone_object(KNPC + "advisor");
	a1->arm_me();
	a1->move(TO);
    }
    if(!objectp(a2))
    {
	a2 = clone_object(KNPC + "advisor");
	a2->arm_me();
	a2->move(TO);
    }
    if(!objectp(a3))
    {
	a3 = clone_object(KNPC + "advisor");
	a3->arm_me();
	a3->move(TO);
    }

    if(!objectp(c1))
    {
	c1 = clone_object(KNPC + "calof");
	c1->arm_me();
	c1->move(TO);
    }
}

create_kalaman_room()
{
    set_long("@@long_descr");
    set_short("Council Hall");
    add_item(({"great circular hall","circular hall","hall"}),"@@long_descr");
    add_item(({"table","circular table","map","map of kalaman"}),
      "The large circular table is where the Lord and Councillors sit to discuss matters " +
      "of state. A map of Kalaman has been skillfully crafted into the center of the table.\n");
    add_item("chairs","Chairs surround the table.\n");
    add_item(({"high-backed chair","chair"}),
      "The high-backed chair is the seat of the Lord of Kalaman.\n");

    add_exit(CITY + "p4","south",0);

    reset_kalaman_room();
}

string
long_descr()
{
    return "You stand in a great circular hall on the second floor of the palace " +
    "of Kalaman. It is here that the Lord of the city along with his Councillors discuss " +
    "matters of state. A large circular table sits in the center of the room, surrounded " +
    "by chairs. A high-backed chair is at the head of the table on the northern side of the room.\n";
}
