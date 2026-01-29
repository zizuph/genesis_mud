inherit "/d/Shire/common/greyhaven/gh";
#include "/d/Shire/common/defs.h"

//   Prototypes
void add_ship();

int alarm_id;
object ship;

create_gh()
{
    set_short("Grey Havens harbour");
    set_long(
	  "You are standing at the harbour in Mithlond, or Grey Havens in the "
	+ "Common Language.\n"
	+ "    This is an odd place indeed. Along the piers stand several "
	+ "boats looking like great white swans with tall and beautiful necks "
	+ "which bow gently towards the sea. They have got bejeweled eyes "
	+ "and look almost alive.\n"
	+ "    On the other side of the Gulf of Lune you see the Northern "
	+ "Greyhavens, while the town itself extends north-east. On each "
	+ "side of the Gulf the Blue Mountains @@mountains_day_night@@." +
	" New paths lead north and south.\n");

    add_item(({ "track", "tracks" }), "The tracks are mostly made by wagons "
	    + "and mules. There are also a few that indicate horses.\n");
    add_item(({ "pier", "docks", "harbour" }),
	"On the piers there are several big crates and sacks. Probably meant "
	+ "to be shiped to whereever they go.\n");

    add_item(({"sign","small sign"}),
	"The ship to Sparkle lands and departs from here.\n");
    add_item(({ "sack", "sacks" }),
	"The sacks are filled with grain and in some instances, pipeweed.\n");
    add_item(({"crate", "crates"}),
	   "They are all closed and you can't see what's in them.\n");
    add_item("grain",
	   "Better leave it here. Someone might be upset if it's missing.\n");
    add_item("pipeweed",
	   "Fine looking pipeweed indeed. It's not for you however.\n");
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

    add_exit(ER_DIR + "er1","east",0,1);
    add_exit("/d/Shire/common/greyhaven/path1","north",0,1);
    add_exit(GHAVEN_DIR + "path4","south",0,1);
   
     "/d/Shire/michel/fairroad3"->teleledningsanka();
    add_prop(ROOM_I_NO_CLEANUP, 1);
    alarm_id = set_alarm(5.0,0.0,&add_ship());
}

void
add_ship() {
    remove_alarm(alarm_id);
    seteuid(getuid(this_object()));
    if(!ship) {
	ship = clone_object(SHIP_DIR + "ship");
	ship->start_ship();
    }
}

  
