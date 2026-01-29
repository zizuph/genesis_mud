#include "/d/Ansalon/common/defs.h"
#include "/d/Ansalon/balifor/port_balifor/local.h"

inherit         BALIFOR_OUT;
object          kender;

void
reset_balifor_room()
{
    if (!objectp(kender)) {
	kender = clone_object(KNPC + "kender");
	kender->move(TO);
    }
}

create_balifor_room()
{
    set_short("Street in Northern City");
    set_long("@@long_descr");
    add_item(({"breakwater", "Breakwater"}), "@@break_water");
    add_item(({"steppes", "Steppes"}), "@@steppes");
    add_item(({"dark chilling building","building","barracks",
	"dark building","chilling building"}),
      "Along the road to your northeast is a dark, chilling " +
      "building that is now being used as a barracks for the " +
      "dragonarmies. What it was used for before the town was " +
      "overrun you cannot guess, although you are pretty sure " +
      "it wasn't for picnics.\n");
    add_item("road","The road here leads northeast towards " +
      "the barracks of the dragonarmy, southwest towards the " +
      "Bay, and southeast towards the central parts of town.\n");
    add_exit(BROOM + "city21", "northeast", 0);
    add_exit(BROOM + "city06", "southwest", 0);
    add_exit(BROOM + "city09", "southeast", 0);
    reset_balifor_room();
}

string
long_descr()
{
    return tod_descr1() + " You are in the Northern parts of town. Your " +
    "gaze is drawn to a dark, chilling building that has been taken " +
    "by the Dragonarmy, which uses it as a barracks. The citizens " +
    "avoid the northern area, for this very reason. A road leads to " +
    "the Bay, southwest; it also leads northeast towards the the " +
    "barracks. You can also travel southeast into the central parts " +
    "of town. " + season_descr() + "\n";
}
