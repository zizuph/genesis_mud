inherit "/d/Shire/common/greyhaven/gh";

#include "/d/Shire/common/defs.h"

create_gh()
{
    set_short("On a sloping track");
    set_long(
	  "You are travelling on a track which slopes upwards in the east "
	+ "towards the White Towers. The sparse and weather-beaten landscape "
	+ "surrounding you does not permit any trees to grow here, and the "
	+ "western wind comes in heavy gusts from the Sea to the west.\n"
	+ "    Looking north and south you can see the Blue Mountains. "
	+ "They @@mountains_day_night@@, and you know that the ancient "
	+ "dwarven cities of Belegost and Nogrod are somewhere deep within the "
	+ "mountain range.\n"
	+ "    The track continues down west to an elven town called "
	+ "the Grey Havens, or Mithlond in the elven speech, where the "
	+ "master shipwright Cirdan is said to keep his housing.\n");

    add_item(({ "track", "tracks" }),
	  "The tracks are mostly made by wagons "
	+ "and mules. There are also a few that indicate horses.\n");

    add_area();
    add_item(({"wind", "western wind"}),
	"@@exa_wind@@\n");

    add_hills("Looking further east, the track slopes slowly upwards towards a hill.");
    add_gulf();
    add_town("The Grey Havens lie by the Gulf of Lune northwest of you. It is");

    add_exit(GHAVEN_DIR + "gh8", "east", 0, 2);
    add_exit(GHAVEN_DIR + "gh10", "west", 0, 0);
}
