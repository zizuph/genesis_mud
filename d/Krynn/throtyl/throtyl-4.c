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
              desc = "The sun is making its way up in the sky, " +
		     "illuminating the clouds above you a dull grey. " + long;
              break;
	case TOD_DAY:
              desc = "Rays of sunlight break through the grey clouds above " +
                     "you, weakly illuminating the dreary landscape. " + long;
              break;
	case TOD_TWILIGHT:
              desc = "The sun is sinking below the horizon, causing " +
                  "the grey clouds above you to darken and cast shadows " +
                  "across the land. " + long;
	      break;
	case TOD_NIGHT:
	      desc = "The pale light from the two moons, " + C(SOLINARI) + 
                  " and " + C(LUNITARI) + ", breaks through the dark clouds " +
                  "allowing you to see your " +
                  "surroundings. " + (gExtra_night_long ? gExtra_night_long : long);
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

    set_special_short("on a trail passing through rugged foothills");
    set_short("On a trail through through rugged foothills");
    set_long("The trail leads into the cold and rugged " +
        "land of mountains and valleys known as Taman Busuk. The " +
        "ground is rocky here and stripped with basalt ridges, with " +
        "the occasional dry brush or pine pushing through the hard " +
        "soil.\n");

    add_item(({"mountains","valleys","basalt ridges","ridges",
        "foothills","rugged foothills","mountain range","ground",
        "ranges","mountain ranges"}),
        "These foothills are the beginning of the Taman Busuk mountain " +
        "range, an area of sterile and barren mountains and valleys, " +
        "basalt ridges, and the occasional dry brush or pine tree " +
        "struggling to grow in the poor soil of this region.\n");

    add_item(({"pine tree", "tree", "dry brush", "brush", "pine"}),
        "Plants struggle to grow in the poor soil of these foothills, " +
        "with only the occasional pine or dry brush managing to " +
        "grow in this region.\n");

    add_item(({"trail", "rough trail", "taman busuk"}),
        "You stand on a rough trail that leads southward into the " +
        "mountain ranges of Taman Busuk, and to the north down into " +
        "the moorlands of Throtyl.\n");

    add_item(({"throtyl", "moors", "moorlands", "bogs", "boggy moors", 
        "plain"}),
        "To your northwest the trail leads to Throtl, a land of vast " +
        "moorlands filled with nomadic goblin races.\n");

    add_item(({"grey clouds", "dark clouds", "clouds", "rain", "sky" }),
        "Dark grey clouds hang heavily over the foothills, the faint " +
        "smell of smoke and sulfur making you think they are composed " +
        "of more than just rain.\n");

    add_std_exits();

    herbs = HERB_MASTER->query_herbs( ({ "hills", }) );
}

/* Function name: query_map_fatigue
 * Description:	  Return fatigue value for leaving this room for this_player()
 *		  Redefine it in ROOM base file.
 * Returns:	  int fatigue value
 */
public int
query_map_fatigue()
{
    return 1;
}
