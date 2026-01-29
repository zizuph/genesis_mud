/*
 * Dagger now cloned to gakhan if (!random(10))
 * Milan
 */

#include "/d/Ansalon/common/defs.h"
#include <macros.h>
#include <stdproperties.h>
#include "/d/Ansalon/balifor/flotsam/local.h"

inherit FLOTSAM_IN;

int    dagger = 1;   /* Special dagger. One pr. reboot only */
object gakhan;
object innkeeper;

void
reset_flotsam_room()
{
    if(!objectp(gakhan))
    {
	gakhan = clone_object(FNPC + "gakhan");
	gakhan->arm_me(!random(10));
	gakhan->move(TO);
    }
    if(!objectp(innkeeper))
    {
	innkeeper = clone_object(FNPC + "innkeeper2");
	innkeeper->move(TO);
    }

    dagger = 0;
}

create_flotsam_room()
{
    set_short("Saltbreeze Inn");
    set_long("@@long_descr");

    add_item("sign","A sign has been stuck up on the wall. " +
      "Perhaps you would like to read it? \n");
    add_item(({"wall","northern wall"}),"A sign has been " +
      "stuck up on the northern wall.\n");
    add_item("staircase","A staircase leads up to the Inns rooms.\n");
    add_item("door","A door to the south leads out onto " +
      "the streets of Flotsam. \n");

//  Removed this prop as it is just an annoyance to people who keep losing their
//  Horse here, because the automount and autodismount doesn't work.
//    add_prop(ROOM_I_NO_ALLOW_STEED, 1);

    add_exit(FROOM + "street44","out","@@out",0);
    add_exit(FROOM + "upper_inn02","up","@@up",0);

    add_cmd_item("sign","read","@@read_sign");

    reset_flotsam_room();
}

string
long_descr()
{
    return "You stand within the finest Inn in Flotsam, " +
    "the Saltbreeze Inn. Built high on a cliff it overlooks the Blood Sea " +
    "of Istar, whose waves break on the rocks below. A " +
    "staircase leads up to its fine rooms, and a doorway " +
    "to the south leads out to the streets. A sign has been " +
    "stuck up on the northern wall. \n";
}

int
up()
{
    write("You climb the stairway...\n");
    return 0;
}

int
out()
{
    write("You open the door and step out into the streets...\n");
    return 0;
}

int
read_sign()
{
    write("\nDue to our cook finding disfavour with her Ladyship, \n" +
      "the Saltbreeze Inn's kitchen has been closed. Sorry for \n" +
      "any inconvienience. \n" +
      "\nReginald, Innkeeper.\n");
    return 1;
}
