#include "/d/Ansalon/common/defs.h"
#include "/d/Ansalon/taman_busuk/sanction/local.h"
#include <macros.h>
#include <stdproperties.h>
#include "/d/Krynn/common/clock/clock.h"

inherit SANCOUTROOM;

#define THROTYL "/d/Krynn/throtyl/rooms/throtyl-16-16-5"
#define CAVE "/d/Ansalon/taman_busuk/sanction/room/city/volcano_cave"

void
create_sanction_room()
{
    set_short("high on the side of a volcano");
    set_long("@@long_desc");

    add_item(({"mountains","valleys","basalt ridges","ridges","spires",
        "mountain range","ground","cliffs","cliff","seven spires",
        "terrain","barren terrain",
        "ranges","mountain ranges","volcanoes","volcano","vista"}),
        "All around you is the Taman Busuk mountain " +
        "range, an area of sheer cliffs and inhospitable volcanic " +
        "mountains.\n");
    add_item(({"trail", "rough trail", "taman busuk"}),
        "Far below you make out a trail winding across the sheer cliffs of " +
        "the Seven Spires range. You could probably climb down to it from here.\n");
    add_item(({"smoke clouds", "low smoke clouds", "clouds", "smoke", 
        "sky" }),
        "Smoke clouds from nearby volcanoes hang heavily throughout the " +
        "mountain range, the smell of sulfur strong and overpowering.\n");
    add_item(({"cave", "vent", "active vent","side of the volcano"}),
        "On the side of the volcano a cave opens up. Radiating incredible " +
        "heat and spewing toxic gases, you have no doubt this is an active " +
        "vent of the volcano.\n");
    add_item(({"volcano"}),
        "You find yourself high up on the side of an active volcano! Before " +
        "you opens a cave... or more rightly a vent that leads into the middle " +
        "of the volcano.\n");

    add_prop(ROOM_M_NO_TELEPORT_TO, 1);

    add_cmd_item(({"down","cliff","down to trail","to trail"}), "climb",
        "@@climb_down");
    add_cmd_item(({"cave"}), "enter", "@@enter_cave");

}

string
long_desc()
{
    string str, desc;

    str = "It is " + GET_TIME_STRING + " high on the side of a " +
        "volcano in the Taman Busuk mountain range. ";

    switch (GET_TIMEOFDAY)
    {
        case TOD_DAWN:
              desc = "The light from the rising sun fails to penetrate " +
                  "the low hanging smoke clouds of nearby volcanoes, illuminating " +
                  "the barren terrain in a strange twilight. ";
              break;
	case TOD_DAY:
              desc = "Grayish-brown sunlight breaks through the heavy low hanging " +
                     "smoke clouds of nearby volcanoes, weakly illuminating the barren " +
                     "terrain. ";
              break;
	case TOD_TWILIGHT:
              desc = "The light from the setting sun causes the low hanging smoke " +
                  "clouds from nearby volcanoes to glow a hellish red. ";
	      break;
	case TOD_NIGHT:
              desc = "Low smoke clouds of nearby volcanoes hang oppressively over " +
                  "you, their dark presence blotting out the night sky. ";
	      break;
    }

    str += desc;
    str += "Before you opens a cave into the volcano, radiating intense " +
        "heat. Far down below, you can make out a trail that you can climb down " +
        "to.\n";

    return str;
}

string
climb_down()
{
    write("You make your way down the side of the volcano to the trail below.\n");
    TP->move_living("climbs down the side of the volcano",THROTYL, 1, 0);
    return "";
}

string
enter_cave()
{
    if(TP->query_magic_res(MAGIC_I_RES_POISON) < 20)
        return "The toxic gases are too overwhelming for you to enter. You " +
            "would need better protection from poisons to even think of " +
            "entering!\n";

    if(TP->query_magic_res(MAGIC_I_RES_FIRE) < 20)
        return "The volcanic heat is too overwhelming for you to enter. You " +
            "would need better protection from fire to even think of " +
            "entering!\n";

    write("You make your way into the side of the volcano.\n");
    TP->move_living("enters the cave on the side of the volcano",CAVE, 1, 0);
    return "";
}


