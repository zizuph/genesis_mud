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
                  "across the land. " + long;
	      break;
	case TOD_NIGHT:
	      desc = "The pale light from the two moons, " + C(SOLINARI) + 
                  " and " + C(LUNITARI) + ", breaks through the dark rain clouds " +
                  "allowing you to see your " +
                  "surroundings. " + (gExtra_night_long ? gExtra_night_long : long);
	      break;
    }

    str += desc;

    return str;
}

string
query_moors_season()
{
    if(GET_SEASON == SPRING)
        return "flooded moorlands of Throtyl";

    return "moorlands of Throtyl";
}

string
query_moors_season_long()
{
    if(GET_SEASON == SPRING)
        return " Right now the moors are inundated from " +
            "spring rains, making travel extremely exhausting.";

    return "";
}


public void
create_throtyl_room()
{
    add_prop(ROOM_I_TYPE, ROOM_NORMAL);
    add_prop(ROOM_I_INSIDE, 0);
    add_prop(ROOM_I_LIGHT, 1);

    set_special_short("on the " +query_moors_season());
    set_short("the @@query_moors_season");
    set_long("The moors spread out before you, " +
        "a poorly drained plain covered in hardy purple heather " +
        "blooms." +query_moors_season_long()+ "\n");

    add_item(({"heather", "purple heather","blooms",
        "heath", "heather blooms"}),
        "A hardy heather grows wild across the moors of Throtyl, its " +
        "vibrant purple blooms a stark constrast to the rest of the " +
        "barren lands and dreary weather.\n");

    add_item(({"grey rain clouds", "rain clouds", "clouds", "rain",
        "dark rain clouds" }),
        "Dark rain clouds seem to permanently hang over the lands " +
        "of Throtyl.\n");

    add_item(({"throtyl", "moors", "moorlands", "bogs", "boggy moors", 
        "plain"}),
        "Around you is Throtyl, a land of vast moorlands " +
        "filled with nomadic goblin races. Heath and peat bogs are common " +
        "here, and this poorly drained land is inundated with rain " +
        "throughout the year. Even when at its driest the moors are " +
        "exhausting to navigate, but during the wet season almost " +
        "impossible.\n");

    add_std_exits();

    herbs = HERB_MASTER->query_herbs( ({ "wetlands", }) );
}

/* Function name: query_map_fatigue
 * Description:	  Return fatigue value for leaving this room for this_player()
 *		  Redefine it in ROOM base file.
 * Returns:	  int fatigue value
 */
public int
query_map_fatigue()
{
    if(GET_SEASON == SPRING)
        return 8;
    else
        return 4;
}
