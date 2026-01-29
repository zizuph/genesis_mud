#include "/d/Ansalon/common/defs.h"
#include "/d/Ansalon/balifor/port_balifor/local.h"

inherit         BALIFOR_IN;
object          drac;
object          drac2;
object          drac3;

void
reset_balifor_room()
{
    if (!objectp(drac)) {
	drac = clone_object(KNPC + "sivak");
	drac->move(TO);
    }
    if (!objectp(drac2)) {
	drac2 = clone_object(KNPC + "bozak");
	drac2->move(TO);
    }
    if (!objectp(drac3)) {
	drac3 = clone_object(KNPC + "bozak");
	drac3->move(TO);
    }
}

create_balifor_room()
{
    set_short("Guardroom in Balifor");
    set_long("@@long_descr");
    add_item("guardroom","@@long_descr");
    add_item("gate","To your southwest is the Gate of " +
      "Balifor.\n");
    add_exit(BROOM + "gate", "southeast", 0);
    reset_balifor_room();
}

string
long_descr()
{
    return "You are in a guardroom overlooking the Gate of Balifor. " +
    "Here the guards on reserve spend their time on duty while " +
    "another group guards the actual gate. Should there be any " +
    "trouble, they would be the first to be notified.\n";
}
