inherit "/d/Shire/common/greyhaven/path";

#include "defs.h"


create_path()
{
    set_short("South of Grey Havens");
    set_long(
	  "You are standing south of the marvelous town of Mithlond, or "
	+ "Grey Havens in the common speech. This is the town where the "
	+ "famous elven shipwright Cirdan is said to keep his housing. "
	+ "You can smell the salt water of the sea coming from the Gulf of "
	+ "Lune in the west, and continuing along a small road you will "
	+ "end up by the shore.\n"
	+ "    In the east, a track continues over the weather-beaten land "
	+ "slowly sloping upwards towards some hills called the Tower Hills. "
	+ "Upon them stands the White Towers, ever gazing towards the Sea in "
	+ "the west.\n"
	+ "    A path starts here continuing south towards a mountain range. "
	+ "That must be the Blue Mountains, where it is said that "
	+ "the dwarves have delved the Mountains from the dawn of time.\n");

    add_item(({ "track", "tracks" }), "The tracks are mostly made by wagons "
	    + "and mules. There are also a few that indicate horses.\n");

    add_item(({ "grey havens", "havens", "mithlond", "town" }), BS(
	  "This is a magnificient town indeed, as elves made it several "
	+ "centuries ago. It houses mostly elves, though dwarves, humans "
	+ "and occationally hobbits are also inhabitants. The northern "
	+ "gates are closed now however, as the dark times forbids the "
	+ "elves from allowing strangers into the town.\n"));

    add_item(({ "gulf", "lune", "sea", "gulf of lune" }), BS(
	  "The Sea in the west is actually the Gulf of Lune which comes "
	+ "from the Great Sea in the West, and continues all the way "
	+ "past the Grey Havens and north-east all the way up to and "
	+ "meeting the River of Lhun. You might go west and visit the "
	+ "shore, if you desire.\n"));

    add_item(({ "road", "shore" }),
	"You might follow the road towards the shore in the west.\n");

    add_item(({ "blue mountains", "mountains" }), BS(
	  "Being rather distant from here, you notice the blue colour upon "
	+ "its hills. It is the start of a mountain range from here and "
	+ "several hundreds miles southwards, and it is said that the "
	+ "dwarves cave in mines under the mountains.\n"));

    add_item(({ "towers", "white towers", "tower hills", "hills" }), BS(
	  "In the east, you see a track sloping up towards some hills. "
	+ "This is the Tower Hills, on which three towers, the White Towers, "
	+ "stand gazing westwards toward the Sea. It was once the Watch-towers "
	+ "of the Western border of the lost realm Arnor, of which not many "
	+ "remember or even have heard of.\n"));

    add_item(({ "path" }), BS(
	  "The path continues southwards about a mile or two from the western "
	+ "shore of the Gulf of Lune. It seems to lead towards the Mountains "
	+ "in the south, The Blue Mountains.\n"));

    add_exit(STAND_DIR + "gh9", "east", 0);
    add_exit(STAND_DIR + "shore", "west", 0);
    add_exit(STAND_DIR + "dwarf2", "south", 0);
}
