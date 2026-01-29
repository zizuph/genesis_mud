#include "/d/Ansalon/common/defs.h"
#include "/d/Ansalon/balifor/flotsam_forest/local.h"

inherit FOREST_OUT;

object corpse;

void
reset_flotsam_room()
{
    if(!objectp(corpse))
    {
	corpse = clone_object(FOBJ + "remains");
	corpse->move(TO);
    }
}

create_flotsam_room()
{
    set_short("bottom of a cliff");
    set_long("@@long_descr");

    add_item("waves","Waves crash around you, throwing " +
      "salty spray high up into the air, drenching you.\n");
    add_item(({"Bloodsea of Istar","bloodsea of istar","bloodsea"}),
      "The turbulent waters of the Bloodsea of Istar crash " +
      "around you.\n");
    add_item(({"rocky shelf","shelf"}),
      "You stand on a rocky shelf wide enough to comfortably " +
      "stand on. Just below you, waves crash violently into " +
      "the cliff, keeping you away from the shelfs' edge.\n");
    add_item("cliff","The cliff towers about 100 feet above you.\n");

    add_cmd_item(({"cliff","up"}),"climb","@@climb_cliff");

    reset_flotsam_room();
}

string
long_descr()
{
    return "Waves crash around you as you stand on a " +
    "rocky shelf, as close to the bottom of the cliff as you " +
    "would care to get. You fear any moment that a great wave " +
    "is going to wash you into the Bloodsea of Istar, making " +
    "you little more than fishbait.\n";
}

string
climb_cliff()
{
    write("You climb the cliff to the ridge above.\n");
    TP->move_living("up to the ridge above", CROOM + "ridge3.c",1,0);
    return "";
}
