#include "/d/Ansalon/common/defs.h"
#include "/d/Ansalon/balifor/flotsam_forest/local.h"
#include <macros.h>
#include "/d/Krynn/guilds/OotS/defs.h"

inherit FOREST_OUT;

#include "/d/Krynn/common/herbsearch.h"
#define H1 "/d/Krynn/common/herbs/bur_reed"

object centaur1, centaur2, centaur3;

void
reset_flotsam_room()
{
    if(!objectp(centaur1))
    {
	centaur1 = clone_object(FNPC + "centaur3");
	centaur1->arm_me();
	centaur1->move(TO);
    }
    if(!objectp(centaur2))
    {
	centaur2 = clone_object(FNPC + "centaur2");
	centaur2->arm_me();
	centaur2->move(TO);
    }
    if(!objectp(centaur3))
    {
	centaur3 = clone_object(FNPC + "centaur2");
	centaur3->arm_me();
	centaur3->move(TO);
    }
}

create_flotsam_room()
{
    set_short("The centre of a centaur glade");
    set_long("@@long_descr");

    add_item(({"centaurs glade","centaur glade","glade","clearing",
	"natural clearing"}),"@@long_descr");
    add_item(({"lush green grass","green grass","grass"}),
      "Throughout the glade grows lush green grass. In some areas " +
      "it looks like it has been trampled.\n");
    add_item(({"pool","small pool of clear water","small pool",
	"clear water","natural well","fresh water"}),
      "This small pool stands in the centre of the glade. Its water " +
      "is crystal clear and fresh, it obviously being a natural " +
      "well of fresh water.\n");

    add_exit(FROOM + "g46","northwest",0);

    add_cmd_item(({"from pool","water","from well"}),
      "drink","@@drink_water");

    seteuid(getuid(TO));
    set_search_places(({"water","pool","herbs"}));
    add_prop(OBJ_I_SEARCH_TIME,3);
    add_prop(OBJ_S_SEARCH_FUN,"herb_search");
    add_herb_file(H1);

    reset_flotsam_room();
}

string
long_descr()
{
    return "You stand in the center of a centaurs glade. Lush " +
    "green grass grows all through this natural clearing, and " +
    "in the middle is a small pool of clear water that ripples slightly " +
    "with the wind. " +
    tod_descr3() + "\n";
}

string
drink_water()
{
     if(IS_OOTS(TP))
     {
        if(!OOTS_QUERY_REV(TP, "habbakuk"))
        {
            TP->catch_msg("\n\nYour mind explodes with the image of a Blue Phoenix and "+
                            "filled with divine clarity, as a " +
                            "revelation on the aspect of Habbakuk manifests to you!\n\n\n");
            OOTS_ADD_REV(TP,"habbakuk","the aspect of habbakuk");  
        }
     }

    if(TP->drink_soft(TP->drink_max() / 16, 0))
    {
	write("You taste the water of the pool... " +
	  "It's quite refreshing!\n");
	say(QCTNAME(TP)+ " drinks some water from the pool.\n");
	TP->heal_hp(2);
	return "";
    }
    else
	write("You don't feel like drinking any more water from the pool.\n");
    return "";
}
