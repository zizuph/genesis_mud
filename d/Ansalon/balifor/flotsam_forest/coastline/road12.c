#include "/d/Ansalon/common/defs.h"
#include "/d/Ansalon/balifor/flotsam_forest/local.h"
#include <macros.h>

#define FFF random(3)

inherit FOREST_OUT;

void
reset_flotsam_room()
{
    return;
}


create_flotsam_room()
{
    set_short("Beside a wooden sign on a small trail");
    set_long("@@long_descr");

    add_item(({"wooden sign","sign"}),
      "Planted firmly into the ground is a wooden sign with " +
      "writing on it. Its weathered appearance, as well as the " +
      "growth of tufts of grass at its base, gives you the " +
      "impression that it has stood here for some time. You " +
      "can probably read it.\n");
    add_item(({"small trail","trail"}),
      "This is a small trail that leads southwestwards towards " +
      "a quaint little cottage and eastwards towards " +
      "the main road.\n");
    add_item(({"border","forest","evergreen forest",
	"ancient evergreen forest"}),
      "To the south of the trail is the outer border of an " +
      "ancient evergreen forest. The sounds of birds and insects, " +
      "as well as the rustle of leaves as a gentle sea breeze " +
      "blows through its canopy, eminates from the forest.\n");
    add_item(({"quaint cottage","cottage",
	"old fashioned cottage","chimney","chimney stack"}),
      "To your southwest you make out a two-story old fashioned " +
      "cottage. Smoke puffs merrily from its chimney stack.\n");


    add_cmd_item(({"wooden sign","sign"}),"read","@@read_sign");
    add_exit(CROOM + "road11","east",0);
    add_exit(CROOM + "road13","southwest",0);

    reset_flotsam_room();
}

string
long_descr()
{
    return tod_descr1() + "Beneath your feet is a small " +
    "trail, no more than two feet in width, leading eastward " +
    "to the main road, and southwestward towards a quaint " +
    "cottage. A wooden sign has been planted on the northern " +
    "side of the trail.\n";
}

string
read_sign()
{
    string str;
    switch(random(3))
    {
    case 1:
	str = "\n" +
	"          _________________________\n" +
	"          |                        |\n" +
	"          |   No tresspassing!     |\n" +
	"          |   Violators should     |\n" +
	"          |   notify next of kin.  |\n" +
	"          |                        |\n" +
	"          |   Have a pleasant day. |\n" +
	"          |                        |\n" +
	"          |   -Fermammon the Wise  |\n" +
	"          |________________________|\n" +
	"                    |     |\n" +
	"                    |     |\n" +
	"                    |     |\n" +
	"                    |     |\n";
	break;
    case 2:
	str = "\n" +
	"          _________________________\n"+
	"          |                        |\n" +
	"          | Rumours of spike-filled|\n" +
	"          |pits along this path are|\n" +
	"          | almost totally false.  |\n" +
	"          | Thank you for your     |\n" +
	"          | caution.               |\n" +
	"          |                        |\n" +
	"          |    -Fermammon the Wise |\n" +
	"          |________________________|\n" +
	"                    |     |\n" +
	"                    |     |\n" +
	"                    |     |\n" +
	"                    |     |\n";
	break;
    case 0:
	str = "\n" +
	"          _________________________\n" +
	"          |                       |\n" +
	"          |   Private property.   |\n" +
	"          |   Enter at your own   |\n" +
	"          |   risk!               |\n" +
	"          |                       |\n" +
	"          |   -Fermammon the Wise |\n" +
	"          |_______________________|\n" +
	"                    |     |\n" +
	"                    |     |\n" +
	"                    |     |\n" +
	"                    |     |\n";
	break;
    }
    return str;
}
