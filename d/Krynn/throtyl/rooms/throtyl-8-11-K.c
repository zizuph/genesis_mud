#include "../local.h"
#include CLOCKH
inherit TDIR + "throtyl_base";

#define HOBGOB_ELIGIBLE_RACES ({"human", "orc", "goblin", \
    "hobgoblin","ogre", "drow"})
#define MEMBER(ob) ob->query_guild_member("Raiders of Throtyl")
#define ESTWILDE_LINK "/d/Ansalon/estwilde/plains/9c"
#define JOINROOM "/d/Krynn/guilds/hobgob/joinroom"

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
        return "flooded moorlands of Throtyl on the edge of Estwilde";

    return "moorlands of Throtyl on the edge of Estwilde";
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
    set_short("before East Keep on the moorlands of Throtyl");
    set_long("The moors spread out before you, " +
        "a poorly drained plain covered in hardy purple heather " +
        "blooms." +query_moors_season_long()+ " To your southwest " +
        "stands a forlorn tower overlooking the moors.\n");

    add_item(({"estwilde","estwilde plains","plains"}),
       "To your northeast the moors of Throtyl end and the plains " +
       "of Estwilde begin.\n");

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

    add_item(({"tower","keep","east keep","forlorn tower","citadel"}),
        "To your southwest rises a forlorn tower known as East Keep. " +
        "This small citadel was once the central command of the " +
        "human residents of Throtyl known as the Riders of the Moor, " +
        "but was overrun by hobgoblin marauders and has since been " +
        "in their iron grip.\n");

    add_cmd_item(({"keep","east keep","gate","gates"}), "enter",
        "You can try and enter the gates of East Keep by travelling " +
        "southwest.\n");

    add_std_exits();
    add_exit(JOINROOM, "southwest", "@@enter_keep", 1, 1);

    herbs = HERB_MASTER->query_herbs( ({ "wetlands", }) );
}

int
enter_keep()
{
    string race_name = TP->query_race_name();

    if(TP->query_npc())
        return 0;

    if(MEMBER(TP) || TP->query_wiz_level())
    {
        write("The hobgoblins manning the gates of East Keep " +
            "open them for you, allowing entry.\n");
        say("The gates of East Keep open for " +QTNAME(TP) + 
            ", allowing " +HIM(TP)+ " entry.\n");
        return 0;
    }

    if(!IN_ARRAY(race_name, HOBGOB_ELIGIBLE_RACES))
    {
        write("The hobgoblins manning the gates of East Keep " +
            "refuse to open them for you. You cannot enter.\n");
        say(QCTNAME(TP) + " tries futilely to enter East Keep, " +
            "however the hobgoblins manning the gate refuse " +
            HIM(TP)+ " entry.\n");
        return 1;
    }

    if(TP->query_alignment() > -200)
    {
        write("The hobgoblins manning the gates of East Keep " +
            "don't trust you and refuse to open them for you.\n");
        say(QCTNAME(TP) + " tries futilely to enter East Keep, " +
            "however the hobgoblins manning the gate refuse " +
            HIM(TP)+ " entry.\n");
        return 1;
    }

    write("The hobgoblins manning the gates of East Keep " +
            "open them for you, allowing entry.\n");
    say("The gates of East Keep open for " +QTNAME(TP) + 
            ", allowing " +HIM(TP)+ " entry.\n");
    return 0;
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
