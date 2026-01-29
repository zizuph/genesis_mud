inherit "/d/Shire/common/greyhaven/path";

#include "defs.h"

create_path()
{
    set_short("Overlooking Grey Havens");
    set_long(
      "You are walking on a path south of Grey Havens. In the north, "
      + "and somewhat down you can see the splendid town @@town_desc@@. "
      + "The path continues south over a rather open landscape towards "
      + "the Blue Mountains, where the dwarves are said to have built "
      + "splendid caves under the earth.\n"
      + "    The wind blows salt water from the Gulf of Lune west of you, "
      + "the reek filling you with fresh energy. Somewhat east you can "
      + "see the White Towers standing on the Tower Hills, "
      + "set with their lonely gaze "
      + "West towards the Great Sea and the Land of the Gods of the West.\n");

    add_exit("/d/Shire/eastroad/western/er2s","north",0,1);
    add_exit(STAND_DIR + "dwarf1", "south");

    add_item(({"mountains", "blue mountains"}), BS(
	"The Blue Mountains looms south of you, though in fact it looms north "
	+ "of you as well. Once upon the time, this mountain range was a single "
	+ "row of mountains stretching from the far north to the White Mountains "
	+ "in the south, but in the end of the First Age, some thousands years "
	+ "ago, the Gods from the West battled a great War against the Great "
	+ "Enemy, Morgoth, of which Sauron was but a Leutenant, and during "
	+ "this battle beetween Gods, the Blue Mountains was divided in two, and "
	+ "now the Gulf of Lune separates the two mountain ranges.\n"));

    add_item(({"path"}), BS(
	"The path goes north-south, south towards the Blue Mountains, and "
	+ "north towards the Elven town Grey Havens, which is called Mithlond "
	+ "by the elves.\n"));

    add_item(({"grey havens", "havens", "town"}), BS(
	"The Grey Havens lies somewhat north of you, and the path slopes "
	+ "slowly down towards it. It is an elven harbour town, where the "
	+ "famous elven shipwright Cirdan is said to keep his House.\n"));

    add_item(({"landscape", "surroundings", "vegetation"}), BS(
	"The typical weather beaten landscape at the sea permits no growth "
	+ "of bigger trees and the vegetation is hence sparse.\n"));

    add_item(({"sea", "gulf", "lune"}), BS(
	"The Gulf of Lune is coming in from the Great Sea, Belagear, and "
	+ "continues past Grey Havens and into the river Lhun, or Lune, "
	+ "though the river is far to far north from here to see.\n"));

    add_item(({"tower", "tower hills", "white towers"}), BS(
	"The white towers can be seen in far distance in the east. "
	+ "The Great Eastroad is said to start from there, and once upon a "
	+ "time, it was the Westernmost borderpost of the ancient realm of "
	+ "Arnor, now long lost in people's memories.\n"));

}

string
town_desc()
{
    object clock = find_object(CLOCK);
    int hour;

    if (!clock)
	return "twinkling in the early morning light";

    hour = clock->query_hour();

    switch(hour)
    {
    case EARLY_NIGHT:
	return "twinkling with lights in the early night";
    case LATE_NIGHT:
	return "lying silent during the night";
    case EARLY_MORNING:
	return "shining in the early morning light";
    case MORNING:
	return "bathe in the morning light";
    case NOON:
	return "shine as the sun stands at it's zenith";
    case AFTERNOON:
	return "is filled with life in the afternoon";
    case EVENING:
	return "stands in long shadow in the evening";
    }
}
