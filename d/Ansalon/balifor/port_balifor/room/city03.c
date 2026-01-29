
#include "/d/Ansalon/common/defs.h"
#include "/d/Ansalon/balifor/port_balifor/local.h"

inherit BALIFOR_OUT;
object drac;

void
reset_balifor_room()
{
    if(!objectp(drac))
    {
	drac = clone_object(KNPC + "bozak");
	drac->move(TO);
    }
}

create_balifor_room()
{
    set_short("Street on the Bay");
    set_long("@@long_descr");
    add_item(({"breakwater","Breakwater"}),"@@break_water");
    add_item(({"steppes","Steppes"}),"@@steppes");
    add_item(({"main","main road"}),
      "The main road heads from the north and turns down towards " +
      "the southwest.\n");
    add_item(({"road","smaller road"}),
      "A road smaller than the main road leads to the southeast " +
      "deeper into the town.\n");
    add_item(({"northeast","building"}),
      "To the northeast stands a tavern or inn of some kind, " +
      "with people entering it through its entrance to the north.\n");
    add_item("people","You notice a fair number of people " +
      "entering and leaving a building to the north.\n");
    add_item(({"bay","bay of balifor","dark ships","ships",
	"coast"}),
      "To the west you look out onto the Bay of Balifor. Dark " +
      "ships of the dragonarmy often enter and leave Port Balifor, " +
      "this town being an important dock for its ships.\n");
    add_exit(BROOM + "city04","southwest",0);
    add_exit(BROOM + "city01","north",0);
    add_exit(BROOM + "city13","southeast",0);

    reset_balifor_room();
}

string
long_descr()
{
    return tod_descr1() + " You are standing on the main road " +
    "along the " +
    "coast in Balifor. To the northeast, you hear the sounds of "+
    "laughter, and spot many people going in and out of a building. "+
    "The main road turns to the southwest here, and continues " +
    "north; a smaller road leads southeast deeper into town. "+
    "As you look out over the bay, you spot the dark ships of the "+
    "dragonarmy sailing in and out of Port Balifor. "+season_descr()+
    "\n";
}
