#include "/d/Krynn/common/defs.h"
#include "../local.h"
#include <macros.h>
#include <ss_types.h>
#include <stdproperties.h>
#include "/d/Krynn/common/clock/clock.h"
#include "/d/Krynn/guilds/OotS/defs.h"

inherit THARK_OUT;
inherit HERBSEARCHNEW

#define AM_PRAYING "_praying_kirijolith_altar"

string *herbs = HERB_MASTER->query_herbs(({"mountains",}));
int snow_cleared = 0;
object pray_stun;

void
reset_tharkadan_room()
{
    set_searched(0);

    if(((GET_SEASON == WINTER) || (GET_SEASON == AUTUMN)) && snow_cleared)
    {
	tell_room(TO, "Snow fills the depression here, completely " +
	  "covering the altar.\n", ({ }) ); 
	snow_cleared = 0;
    }
}

create_tharkadan_room()
{
    set_short("@@short_descr");
    set_long("@@long_descr");

    add_exit(ROOM + "ledge14","north",0);

    add_item(({"valley","vale","wide vale","protected vale",
	"isolated valley","floor","centre","forested valley"}),
      "Standing at the top of the peak you get a stunning view of the " +
      "entire valley and the mountains that rim the vale. Aspens and " +
      "firs grow in abundance down below.\n");
    add_item(({"aspen","aspen trees","aspens"}), "You see aspen trees " +
      "growing in large numbers in the valley far below.\n");
    add_item(({"fir","fir trees","firs"}),"You see large fir trees " +
      "growing in the valley far below.\n");
    add_item(({"trees","tree"}),"Aspens and firs grow in abundance far " +
      "below in the valley.\n");
    add_item(({"snow","snow-covered","snow-covered ground","seasonal snow",
	"white","snow-covered land","winters snow","winter's snow"}),
      "@@add_summit_snow");
    add_item(({"towering peak","peak","ancient volcano","volcano",
	"mountain","summit"}), "You are standing on the summit of a " +
      "towering peak, likely once an ancient volcano. Far below you " +
      "can see this mountain stands alone amongst a sea of aspen and " +
      "fir trees.\n");
    add_item(({"depression","bowl","shallow bowl","vent"}),
      "@@add_depression_desc");
    add_item(({"altar","simple time-worn altar","time-worn altar",
	"simple altar","altar of basalt","simple time-worn altar of " +
	"basalt"}), "@@add_altar_desc");
    add_item(({"carvings","carving","carving of great longsword",
	"longsword carving","carving of longsword",
	"carving of bison horns","bison horns","horns","warrior-priests",
	"carving of warrior-priests","kneeling warrior priests"}),
      "@@add_carving_desc");

    add_cmd_item(({"snow"}), ({"dig","clear"}), "@@dig_snow");

    seteuid(getuid(TO));

    set_up_herbs( ({ ONE_OF(herbs), ONE_OF(herbs), ONE_OF(herbs),
	ONE_OF(herbs), ONE_OF(herbs) }), ({ "canyon","ground" }), 3);

    reset_tharkadan_room();
}

string
short_descr()
{
    return "the top of a towering peak in the Tharkadan mountain range";
}

public void
init()
{
    ::init(); 
    add_action("worship_kirijolith", "worship");
    add_action("worship_kirijolith", "pray"); 
}

public int
worship_kirijolith(string str)
{
    if (!strlen(str))
    {
	return 0;
    }

    if((str != "kiri-jolith") && (str != "Kiri-Jolith") && 
      (str != "Kiri Jolith") && (str != "to kiri-jolith") && 
      (str != "to Kiri-Jolith") && (str != "to Kiri Jolith"))
    {
	notify_fail("Who do you wish to pray to?\n");
	return 0;
    }       

    if(((GET_SEASON == WINTER) || (GET_SEASON == AUTUMN)) && !snow_cleared)
    {
	notify_fail("You feel like you are missing something to " +
	  "properly pay homage to one of the Old Gods... a focus for " +
	  "your prayers.\n");
	return 0;
    }

    if(TP->query_prop(AM_PRAYING))
    {
	notify_fail("You are already praying.\n");
	return 0;
    }

    if(TP->query_guild_name_occ() == "Solamnian Knights" && IS_OOTS(TP) &&
      OOTS_MANAGER->query_oots_god(TP) != "Kiri-Jolith")
    {
	// if (TP->query_knight_level() < 4)
	// {
	    write("You kneel reverently before the time-worn altar and " +
	      "begin praying to one of the Old Gods dedicated to " +
	      "courage, honour, and heroism in war... Kiri-Jolith.\n"); 
	    say(QCTNAME(TP)+ " kneels reverently before the time-worn " +
	      "altar and begins to pray.\n");

	    setuid();
	    seteuid(getuid());

	    pray_stun = clone_object(TOBJ + "knight_praying_stun");
	    pray_stun->move(TP);
	    TP->add_prop(AM_PRAYING, 1);
	    return 1;
	// }
    }

    if(TP->query_prop("_suitable_for_kirijolith") < 2 || IS_OOTS(TP))
    {
	write("You kneel before the time-worn altar and offer a brief " +
	  "prayer to the Old God it is dedicated to before standing " +
	  "up.\n"); 
	say(QCTNAME(TP)+ " kneels before the time-worn altar and " +
	  "offers a brief prayer before standing up.\n");

	if(IS_OOTS(TP))
	{
	    if(!OOTS_QUERY_REV(TP, "kirijolith"))
	    {
		OOTS_ADD_REV(TP,"kirijolith","the aspect of kiri-jolith");
		TP->catch_msg("\n\nA heroic figure, larger-than-life and " +
		  "filled with conviction and spirit appears in your mind, " +
		  "and you are filled with divine clarity as a revelation " +
		  "on the aspect of Kiri-Jolith manifests to you!\n\n\n");
	    }
	}
	return 1;
    }

    write("You kneel reverently before the time-worn altar, " +
      "clasping your hands and praying to the God dedicated to courage, " +
      "honour, and heroism in war... Kiri-Jolith.\n"); 
    say(QCTNAME(TP)+ " kneels reverently before the time-worn altar and " +
      "begins to pray.\n");

    setuid();
    seteuid(getuid());

    pray_stun = clone_object(TOBJ + "praying_stun");
    pray_stun->move(TP);
    TP->add_prop(AM_PRAYING, 1);
    return 1;
}

public int
query_snow_cleared()
{
    return snow_cleared;
}

string
dig_snow()
{
    if((GET_SEASON != WINTER) && (GET_SEASON != AUTUMN))
	return "While the wind at these heights have a freezing bite, " +
	"little snow fills this depression for you to dig.\n";

    if(snow_cleared)
	return "It looks like the snow has already been cleared here, " +
	"revealing a simple time-worn altar of basalt.\n";

    say(QCTNAME(TP)+ " starts clearing the snow from the center of the " +
      "depression, revealing a simple time-worn altar of basalt!\n");
    snow_cleared = 1;
    return "You start clearing the snow from the center of the " +
    "depression, and reveal a simple time-worn altar of basalt!\n";

}

string
add_summit_snow()
{
    if((GET_SEASON != WINTER) && (GET_SEASON != AUTUMN))
	return "While the wind at these heights have a freezing bite, " +
	"there is very little snow around you at this time of year.\n";

    if(snow_cleared)
	return "Snow fills the depression up here at the summit of the " +
	"peak, although it looks like the snow has been cleared " +
	"here, revealing a simple time-worn altar of basalt.\n";

    return "Seasonal snow has filled the depression here, and " +
    "covers the mountains rimming the valley beneath you.\n";

}

string
add_depression_desc()
{
    if((GET_SEASON != WINTER) && (GET_SEASON != AUTUMN))
	return "Once long ago the vent of a volcano, the summit of this " +
	"peak is now sealed, leaving only a shallow bowl of a " +
	"depression to indicate its past fiery glory. In the center " +
	"of the bowl sits a simple time-worn altar of basalt.\n";

    if(snow_cleared)
	return "Once long ago the vent of a volcano, the summit of this " +
	"peak is now sealed, leaving only a shallow bowl of a " +
	"depression to indicate its past fiery glory. Seasonal snow " +
	"fills the depression, although it looks like the snow has " +
	"been cleared here revealing a simple time-worn altar of " +
	"basalt.\n";

    return "Once long ago the vent of volcano, the summit of this peak " +
    "is now sealed, leaving only a shallow bowl of a depression to " +
    "indicate its past fiery glory. Seasonal snow has filled the " +
    "depression here, and covers the mountains rimming the valley " +
    "beneath you.\n";
}

string
add_altar_desc()
{
    if((GET_SEASON != WINTER) && (GET_SEASON != AUTUMN))
	return "In the center of the bowl sits a simple time-worn altar " +
	"of black basalt. In the middle of the altar is a worn carving " +
	"of great longsword inlaid with corroded and tarnished copper. " +
	"Flanking the longsword are faded carvings of kneeling " +
	"warrior-priests. Two great bison horns also inlaid with " +
	"copper are carved into the sides of the altar.\n";

    if(snow_cleared)
	return "In the center of the bowl sits a simple time-worn altar " +
	"of black basalt. In the middle of the altar is a worn " +
	"carving of great longsword inlaid with corroded and tarnished " +
	"copper. Flanking the longsword are faded carvings of kneeling " +
	"warrior-priests. Two great bison horns also inlaid with " +
	"copper are carved into the sides of the altar.\n";

    return "You cannot find that.\n";
}

string
add_carving_desc()
{
    string carving_descs;

    if(TP->query_guild_name_occ() == "Priests of Takhisis")
	carving_descs = "Examining the carvings, the great longsword and " +
	"bison horns gives this altar away as being dedicated to " +
	"Kiri-Jolith - the Sword of Justice and Bison of Heaven - one " +
	"of Takhisis' martial godly opponents.\n";
    else if(TP->query_guild_name_occ() == "Solamnian Knights")
	carving_descs = "Examining the carvings, the great longsword and " +
	"bison horns remind you of similar carvings found in the " +
	"ancient chapels of the great keeps and castles of Solamnia, " +
	"being dedicated to the old patron god of the Knights of the " +
	"Sword, Kiri-Jolith - the Sword of Justice and Bison of " +
	"Heaven!\n";
    else if(TP->query_race_name() == "minotaur")
	carving_descs = "Examining the carvings, the great longsword and " +
	"bison horns remind you of tales of a God known as 'the " +
	"Emperor', the minotaur patron god of war and honour, " +
	"the Sword of Justice and Bison of Heaven - Kiri-Jolith!\n";
    else
	carving_descs = "You examine the carvings but are not " +
	"enlightened any further in relation to their meaning or who " +
	"the altar is dedicated to.\n";

    if((GET_SEASON != WINTER) && (GET_SEASON != AUTUMN))
	return carving_descs;

    if(snow_cleared)
	return carving_descs;

    return "You cannot find that.\n";
}

string
mountain_desc()
{
    string str;
    switch (GET_SEASON)
    {
    case SPRING:
    case SUMMER:
	str = "now long sealed. In the centre of the depression sits " +
	"what looks like a simple time-worn altar of basalt. ";
	break;
    case AUTUMN:
    case WINTER:
	if(snow_cleared)
	{
	    str = "now long sealed and filled with seasonal snow. In the " +
	    "centre of the depression the snow has been cleared, " +
	    "uncovering a simple time-worn altar of basalt. ";
	    break;
	}
	else
	    str = "now long sealed and filled with seasonal snow. ";
	break;
    }
    return str;
}

string
long_descr()
{
    return "You stand at the top of a towering peak in the centre of a " +
    "forested valley. The summit is actually a shallow bowl that " +
    "would have once been the vent of an ancient volcano, " +
    mountain_desc()+ "\n";
}
