inherit "/d/Shire/common/greyhaven/gh";

#include "/d/Shire/common/defs.h"

create_gh()
{
    set_short("On a steep track west of the White Towers");
    set_long("You are on a steep track west of the White Towers.\n" +
	     "The track runs down west towards the firth of Lune by " +
	     "the town of Grey Havens, or Mithlond in Elven speech. " +
	     "@@exa_town|Mithlond is@@.\n");
    add_item(({"towers", "white towers"}),
	     "The White Towers stand gazing westwards towards the Sea. " +
	     "They stand on the top of the Tower Hills which rise quite " + 
	     "steeply upwards in the east.\n");
    add_item(({"mountains", "blue mountains"}),
	     "Further north and south the Blue Mountains @@mountains_day_night@@.\n");
    add_item(({ "track", "tracks" }),
	  "The tracks are mostly made by wagons "
	+ "and mules. There are also a few that indicate horses.\n");
    add_area();
    add_item(({"wind", "western wind"}),
	"@@exa_wind@@\n");
    add_hills("The track slopes slowly upwards over a hill.");
    add_gulf();
    add_town("The Grey Havens lie by the Gulf of Lune west of you. It is");

    add_exit(GHAVEN_DIR + "gh7", "east", 0, 12);
    add_exit(GHAVEN_DIR + "gh9", "west", 0, 0);

    reset_gh();
}
