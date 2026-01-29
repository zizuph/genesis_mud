/*
 * Commented out line with teleledningsanka();
 * Seems to be causing /d/Shire/michel/fairroad3.c not to load.
 * -- May 2004, Finwe
 *
 * Added trashcan so players can destroy stuff. Stuff remains the 
 * trashcan for 5 minutes before it's destroyed.
 * -- May 2004, Finwe
 Ship to PortMacdunn disabled - Tapakah 04/2009 
 *
 * 2011/04/03 Finwe - Last update
 * 2011/07/19 Lavellan - Fixed (removed mention of) "signs"

 */

/*
 * Sets flag in players from calling dragons into ME.
 * Disabled by request of Admin, June 2001
#include "/d/Gondor/common/lib/gs_include.c"
*/
#include <macros.h>
#include "/d/Shire/common/defs.h"
#include <macros.h>
#include <stdproperties.h>
#include <ss_types.h>

inherit "/d/Shire/common/greyhaven/gh";
inherit "/d/Genesis/gsl_ships/lib/pier";

//   Prototypes
int alarm_id;

create_gh()
{
    object timetable;

    add_prop(ROOM_S_MAP_FILE, "grey_havens.txt");
    //set_short("Grey Havens harbour\nA large sign and a small sign");
    set_short("Grey Havens harbour");
    set_long(
	  "You are standing at the harbour in Mithlond, or Grey Havens in the "
	+ "Common Language.\n\n"
	+ "This is an odd place indeed. Along the piers stand several "
	+ "boats looking like great white swans with tall and beautiful necks "
	+ "which bow gently towards the sea. They have bejeweled eyes "
	+ "and look almost alive.\n\n"
	+ "On the other side of the Gulf of Lune you see the Northern "
	+ "Greyhavens, while the town itself extends north-east. On each "
	+ "side of the Gulf the Blue Mountains @@mountains_day_night@@." +
	//" New paths lead north and south. Two signs have been planted " +
    //"here, a large sign and a small sign.\n");
	" New paths lead north and south. A sign has been planted here.\n");

    add_item(({ "track", "tracks" }), "The tracks are mostly made by wagons "
	    + "and mules. There are also a few that indicate horses.\n");
    add_item(({ "pier", "docks", "harbour" }),
	"On the piers there are several big crates and sacks. Probably meant "
	//+ "to be shiped to wherever they go.\n");
	+ "to be shipped to wherever they go.\n");

//    add_item("small sign",
//	"The ship to Sparkle lands and departs from here.\n");
    add_item(({ "sack", "sacks" }),
	"The sacks are filled with grain and in some cases, tobacco.\n");
    add_item(({"crate", "crates"}),
	   "They are all closed and you can't see what's in them.\n");
    add_item("grain",
	   "Better leave it here. Someone might be upset if it's missing.\n");
    add_item("tobacco",
	   "Fine looking tobacco indeed. It's not for you however.\n");
    add_item(({"sea", "gulf", "lune"}),
	  "You are looking upon the calm Gulf of Lune which enters "
	+ "from the Great Sea between the Northern and Southern parts "
	+ "of the Blue Mountains. On the other side, you see the "
	+ "other side of the Grey Havens, as this city lies on both "
	+ "sides of the Gulf.\n");
    add_item(({"grey havens", "other side", "city", "mithlond" }),
	  "The ancient city of Grey Havens, or Mithlond as the elves "
	+ "here call it is divided by the Gulf of Lune. On the other "
	+ "side you can see the North City under the Blue Mountains.\n");
    add_item(({"ships", "boats", "white ships", "swans", "white swans"}),
	  "The White Ships are built by the Elves to sail from "
	+ "Middle-Earth to the Land of Bliss, Eldamar, where the Gods "
	+ "dwell. They have both oars and sails. The Elves do not "
	+ "permit anyone to board these Ships, without the admittance "
	+ "of the Gods and Cirdan the Shipwright.\n");
    /*add_item(({"sign", "signs"}),
        "Two signs stand at the pier, a small sign and a large sign.\n");*/

    room_add_object("/d/Shire/common/obj/trashcan");

    add_exit(ER_DIR + "er1","east",0,1);
    add_exit("/d/Shire/common/greyhaven/path1","north",0,1);
    add_exit(GHAVEN_DIR + "path4","south",0,1);
   
//     "/d/Shire/michel/fairroad3"->teleledningsanka();
    add_pier_entry(MASTER_OB(TO), "Grey Havens", "Passage to Sparkle.");
    add_prop(ROOM_I_NO_CLEANUP, 1);
    initialize_pier();
    timetable = clone_object("/d/Khalakhor/inisi/roke/nyreese/gs_office/timetable");
    timetable->set_timetable_domain("Shire");
    timetable->move(TO);
    timetable->set_no_show_composite(0);
}
