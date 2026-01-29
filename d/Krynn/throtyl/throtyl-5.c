#include "local.h"
#include CLOCKH
inherit TDIR + "throtyl_base";

public string
long_desc(string long)
{
    string str, desc;

    str = "It is " + GET_TIME_STRING + " " +
          (gSpecial_short ? gSpecial_short : short()) + ". ";

    switch (GET_TIMEOFDAY)
    {
        case TOD_DAWN:
              desc = "The light from the rising sun fails to penetrate " +
                  "the low hanging smoke clouds of nearby volcanoes, illuminating " +
                  "the barren terrain in a strange twilight. " + long;
              break;
	case TOD_DAY:
              desc = "Grayish-brown sunlight breaks through the heavy low hanging " +
                     "smoke clouds of nearby volcanoes, weakly illuminating the barren " +
                     "terrain. " + long;
              break;
	case TOD_TWILIGHT:
              desc = "The light from the setting sun causes the low hanging smoke " +
                  "clouds from nearby volcanoes to glow a hellish red. " + long;
	      break;
	case TOD_NIGHT:
              desc = "Low smoke clouds of nearby volcanoes hang oppressively over " +
                  "you, their dark presence blotting out the night sky. " + long;
	      break;
    }

    str += desc;

    return str;
}

public void
create_throtyl_room()
{
    add_prop(ROOM_I_TYPE, ROOM_NORMAL);
    add_prop(ROOM_I_INSIDE, 0);
    add_prop(ROOM_I_LIGHT, 1);

    set_special_short("high on a trail winding across the sheer cliffs " +
        "of the Seven Spires mountains of Taman Busuk");
    set_short("On a trail high in the Taman Busuk mountain range");
    set_long("The vista around you is breathtaking and terrifying, " +
        "with many travellers having fallen to their death from " +
        "one false step.\n");

    add_item(({"mountains","valleys","basalt ridges","ridges","spires",
        "mountain range","ground","cliffs","cliff","seven spires",
        "terrain","barren terrain",
        "ranges","mountain ranges","volcanoes","volcano","vista"}),
        "You are walking a trail high in the Taman Busuk mountain " +
        "range, an area of sheer cliffs and inhospitable volcanic " +
        "mountains.\n");

    add_item(({"trail", "rough trail", "taman busuk"}),
        "You stand high on a trail winding across the sheer cliffs of " +
        "the Seven Spires range, one of the few passes through the " +
        "mountains to the grim city of Sanction.\n");

    add_item(({"smoke clouds", "low smoke clouds", "clouds", "smoke", 
        "sky" }),
        "Smoke clouds from nearby volcanoes hang heavily throughout the " +
        "mountain range, the smell of sulfur strong and overpowering.\n");

    add_std_exits();

    herbs = HERB_MASTER->query_herbs( ({ "mountains", }) );
}

/* Function name: query_map_fatigue
 * Description:	  Return fatigue value for leaving this room for this_player()
 *		  Redefine it in ROOM base file.
 * Returns:	  int fatigue value
 */
public int
query_map_fatigue()
{
    return 2;
}
