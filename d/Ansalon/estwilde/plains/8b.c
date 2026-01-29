#include "/d/Ansalon/common/defs.h"
#include "../local.h"
#include <macros.h>
#include <stdproperties.h>

inherit BPLAINS_OUT;
#define R1 "7b"
#define R2 "8c"
#define R3 "9c"
#define R4 "7a"
object ogre;

void
reset_estwilde_room()
{
    if(!objectp(ogre))
    {
	ogre = clone_object(LIVING + "ogre");
	ogre->arm_me();
	ogre->move(TO);
    }
}

create_estwilde_room()
{
    set_short("@@short_descr");
    set_long("@@long_descr");

    add_exit(ROOM + R1,"north",0);
    add_exit(ROOM + R2,"east",0);
    add_exit(ROOM + R3,"southeast",0);
    add_exit(ROOM + R4,"northwest",0);

    add_item_hill();
    remove_item("hill");
    add_item(({"steep hill","hill"}),
      "To your south rises a steep hill of considerable size. " +
      "The base of the hill is rocky and covered with wiry " +
      "brush and bushes, making it impossible to climb here, " +
      "while the hills pinnacle far above you seems quite barren. " +
      "You notice a goat trail runs around the side of the hill. You " +
      "could probably reach it by climbing up the side of the hill.\n");
    remove_item("bushes");
    add_item(({"bushes","wiry brush","brush"}),
      "Wiry brush and bushes cover the base of the steep hill, adding to " +
      "the rocky and steep slope.\n");

    add_cmd_item(({"up","hill","up the side of the hill",
	"up the hill","up hill"}),
      "climb","@@climb_hill");

    reset_estwilde_room();
}

string
climb_hill()
{
    write("You climb up the steep side of the hill to the " +
      "goat trail above you.\n");
    say(QCTNAME(TP) + " vanishes into the prickly bushes along " +
      "the side of the hill.\n");
    TP->move_living("M", ROOM + "trail1", 1, 1);

    tell_room(ROOM+"trail1", QCTNAME(TP)+" arrives climbing up the side of the hill.\n", TP);
    return "";
}

string
short_descr()
{
    return tod_descr1() + " before a steep hill";
}

string
long_descr()
{
    return plain_desc()+
    "To your south rises a steep hill that blocks your view " +
    "of the plains any further " +
    "in that direction.\n";
}
