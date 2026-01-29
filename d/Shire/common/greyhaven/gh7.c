inherit "/d/Shire/common/greyhaven/gh";

#include "/d/Shire/common/defs.h"

create_gh()
{
    set_short("By the White Towers");
    set_long(
	  "You are standing by the White Towers on the top of the Tower Hills. "
	+ "From here you have a magnificient view as you are looking on the "
	+ "distant Sea in the West, with the harbour town Mithlond, the "
	+ "Grey Havens in the long firth of Lune. The Great East Road continues "
	+ "eastwards from here.\n");
    add_item(({"towers", "white towers"}),
	     "There are three towers here, and the closest is the largest. " +
	     "This is the Elostirion, which once housed one of the Palantiri, " +
	     "a gazing stone which allowed one to see across the Sea to the " +
	     "Land of Bliss, where the Gods dwell.\n");
    add_item(({"town", "harbour", "mithlond", "ships", "shore"}),
	     "@@exa_town|The harbour is@@ and you can see the White Ships lying " +
	     "by the shore. North and south of the Gulf of Lune the Blue Mountains " +
	     "@@mountains_day_night@@.\n");
    add_item(({"road", "east road", "great road", "great east road"}),
	     "A great stone-paved road starts from the Tower Hills. This " +
	     "is the Great Eastroad which travels across the land in the east " +
	     "passing through the Shire, Bree and continuing to Rivendell " +
	     "where Elrond lives, under the vast slopes of the Misty Mountains.\n" +
	     "    It is built ages ago, by the men of Arnor, dwarves of Belegost and Nogrod, and " +
	     "hobbits from the Shire, this is the main route from the Grey Havens and " +
	     "to the Misty Mountains in the East.\n" +
	     "    It is said that it is built upon the foundations of the route " +
	     "the elves took when they travelled towards the Land of Bliss, where " +
	     "the Gods live, several centuries ago.\n" +
	     "    The road goes ever on in the eastern direction.\n");
    add_hills("You are standing on the top of a hill.");
    add_gulf();
    add_area("The area around the Tower Hills");
    add_item(({"wind", "western wind"}),
	"@@exa_wind@@\n");
    add_item(({"largest tower", "elostirion", "tower"}),
	  "Still being white it is said that Gil-galad made these towers "
	+ "for Elendil after the founding of the lost realm of Arnor. "
	+ "It was the western border of the realm, but is now but ruins "
	+ "when compared to what it once was.\n");

    add_exit(GHAVEN_DIR + "gh6", "east", 0, 0);
    add_exit(GHAVEN_DIR + "gh8", "west", 0, 0);

    reset_gh();
}
