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
		     "illuminating the grey rain clouds above you. " + long;
              break;
	case TOD_DAY:
              desc = "Rays of sunlight break through the rain clouds above " +
                     "you, breaking up the dreary weather with the occasional " +
                     "rainbow. " + long;
              break;
	case TOD_TWILIGHT:
              desc = "The sun is sinking below the horizon, causing " +
                  "the grey rain clouds above you to darken and cast shadows " +
                  "across the Throtyl moors. " + long;
	      break;
	case TOD_NIGHT:
	      desc = "The pale light from the two moons, " + C(SOLINARI) + 
                  " and " + C(LUNITARI) + ", breaks through the dark rain clouds " +
                  "hanging over the Throtyl moors, allowing you to see your " +
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

    set_special_short("on a trail in Throtyl");
    set_short("On a trail through Throtyl pass");
    set_long("The trail passes between the Northern and Southern " +
        "Dargaard Mountains, through the great pass known as Throtyl Gap. " +
        "To your northwest looms the dark Stormshire Forest " +
        "while the boggy moors of Throtyl spread to your southeast. " +
        "Stony outcroppings and jagged drop-offs make this route " +
        "difficult to navigate.\n");

    add_item(({"grey rain clouds", "rain clouds", "clouds", "rain",
        "dark rain clouds" }),
        "Dark rain clouds seem to permanently hang over the lands " +
        "of Throtyl.\n");

    add_item(({"trail", "route", "stony outcroppings", "outcroppings",
        "drop-offs","jagged drop-offs" }),
        "The trail before you passes between the gap between the " +
        "Northern and Southern ends of the Dargaard Mountains. " +
        "Navigation here is tricky, with stony outcroppings and " +
        "jagged drop-offs making it potentially treacherous for " +
        "the unwary traveller.\n");

    add_item(({"northern dargaard mountains", "dargaard mountains",
        "mountains", "southern dargaard mountains"}),
        "On either side of the pass are the beginnings of two " +
        "great mountain ranges. To your northeast begins the " +
        "the Northern Dargaard Mountains, while to your " +
        "southwest begins the Southern Dargaard Mountains.\n");

    add_item(({"pass", "throtyl gap", "throtyl pass" }),
        "Before you is Throtyl Gap, the only pass in leagues that " +
        "allows access to the plains of Solamnia from Taman Busuk " +
        "and the Estwilde plains.\n");

    add_item(({"throtyl", "moors", "moorlands", "bogs", "boggy moors"}),
        "To your southeast stretches Throtl, a land of vast moorlands " +
        "filled with nomadic goblin races. Heath and peat bogs are common " +
        "here, and this poorly drained land is inundated with rain " +
        "throughout the year.\n");

    add_item(({"stormshire forest", "forest", "ancient forest", "trees"}),
        "Dark, tall, and ancient. The trees of the Stormshire Forest " +
        "crowd closely together to your northwest, and are rumours to " +
        "be infested with hobgoblins and other unnatural horrors.\n");

    add_std_exits();
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
