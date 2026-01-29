/* The std room file used for Hollin. This file will allow me to check
 * if it's night outside, or whatever it is, morning, day, afternoon etc.
 * This is due to the code of Durins Doors, which will show some secrets
 * during the night whenever it is moon- or starlight outside.
 *
 * Odin, 16 September 1998
 */
#include "/d/Shire/sys/defs.h"
#include "/d/Shire/sys/terrain.h"

inherit AREA_ROOM;

#include <stdproperties.h>
#include <macros.h>

create_hollin_room() {}

public void
create_area_room()
{
	set_areatype(AREATYPE_ROAD);
	set_land("Erigon");
	set_areadesc("wastelands");
	set_area("east of");
	set_areaname("Ost-In-Edhil");	

	add_item(({"road", "dwarven road", "broken road"}),
	  "The road is broad, built by dwarves of Khazad-Dum for use when "+
	  "trading with the elves of Ost-In-Edhil. It runs thru the region "+
	  "called Erigon, going about 20 feet above the river Sirannon. You "+
	  "gather from all the overgrowth that it is seldom used.\n");
	add_item(({"river", "sirannon", "sirannon river", "river sirannon",
	  "gate-stream", "gate stream"}),"The river runs just south of the "+
	  "road, about 20 feet below the road. It looks cold and uninviting "+
	  "with it's source in the peaks of the Misty Mountains. It seems "+
	  "to be very powerful, with strong currents.\n");
	add_item(({"mountains", "misty mountains"}), "The Misty Mountains "+
	  "rise high above the surface of earth, making the near impossible "+
	  "to pass. With it's icy, towering peaks, offering nought but snow, "+
	  "ice and cold storms, there would surely be a passage underneath "+
	  "them.\n");
	add_item(({"bushes", "shrubs"}), "Every here and there some scattered "+
	  "bushes is found, but the landscape offer little or no vegetation "+
	  "around here. Only on the other side of the river you notice that "+
	  "grass grows and flowers seem to flourish.\n");

	add_item(({"forest", "hollin", "hollin forest"}), "Some distance "+
	  "further north across the barren landscape you see more trees, "+
	  "and it appears to be quite dense.\n");

	set_room_tell_time(ROOM_TELL_TIME);
	add_room_tell("A cold wind rushes over the wastelands down from "+
		"the Misty Mountains.");
	add_room_tell("An eerie howl souds over the barracked plains.");
	add_room_tell("High up in the sky a dark cloud passes by, almost as "+
		"if it was alive.");

	create_hollin_base();

	add_prop(ROOM_I_INSIDE, 0);
}

string 
describe_time(string time)
{
	string desc;

	switch(time)
	{
	  case "night":
	  switch(CLOCK->query_moon())  
	  {
		case "full":
		desc += "The moon shines with a cold blue light high up "+
		"in the sky, shreding an eerie light across the barren land "+
		"of Eregion. ";
		break;
		case "dark":
		desc += "Utter darkness lie upon this hostile area as the "+
		"moon and stars is hidden behind dark clouds. ";
		break;
		default:
		desc += "High up in the black sky stars twinkle and a "+
		"bright, yet not full moon shred its light over Eregion. ";
		break;
	  }
	  break;
	  case "morning":
		desc += "Behind the tops of the towering peaks of the "+
	  	"mountain-range, the sun slowly rises, bringing warmth "+
		"to the cold and barren land. ";
		break;
	  case "afternoon":
	  case "noon":
		desc += "Still high up, the sun shines with immense heat. "+
		"The warmth can only be felt in your soul as the cold winds "+
		"from the mountains chill your body. ";
		break;
	  case "evening":
		desc += "In the west the sun slowly starts to fade below "+
		"the horizon, making the surrounding areas even colder. ";
		break;
	  case "early morning":
		desc += "The eastern sky slowly brightens up as a new "+
		"day is about to come. A few rays of light can be seen "+
		"over the icy peaks of the Misty Mountains. ";
		break;
	}
	return desc;
}

