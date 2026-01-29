inherit "/d/Shire/common/greyhaven/path";
#include "defs.h"

create_path()
{
    set_short("You are walking on a path");
    set_long(
	  "You are walking on a path from the Grey Havens towards the "
	+ "Blue Mountains in the South. This is a rather open landscape "
	+ "and you can see far from here. In the west @@desc_gulf@@\n"
	+ "    Even further west you see the lights of the town Forlond, "
	+ "and somewhat north-east you see the White Towers standing lonely "
	+ "upon the Tower Hills gazing west towards the Sea.\n");

    add_exit("/d/Gondor/common/dwarf_guild/gondor", "south", 0);
    add_exit(STAND_DIR + "dwarf2", "north");

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
      + "north towards the Elven town Grey Havens, or Mithlond for elves.\n"));

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

    add_item(({"forlond"}), BS(
	"Though you cannot see as far as that, being more than 200 miles "
      + "from here, Forlond is am elven harbour on the north of the Gulf, "
      + "in the area west of the Northern Blue Mountains, called "
      + "Forlindon.\n"));

    add_item(({"tower", "tower hills", "white towers"}), BS(
	"The white towers can be seen in far distance in the north-east. "
      + "The Great Eastroad is said to start from there, and once upon a "
      + "time, it was the Westernmost borderpost of the ancient realm of "
      + "Arnor, now long lost in folks memories.\n"));
}


string
desc_gulf()
{
    object clock = find_object(CLOCK);
    int hour;
    string *text;

    text = ({
	"you listen to the relaxing sounds of the sea rushing against " +
	"the shore in this star-lit night by the Gulf of Lune.",

	"you can see your long shadows as the sun has emerged over the " +
	"eastern horizon, and further in the west, you see the waves of " +
	"the Gulf of Lune beat the shores of Middle-Earth.",

	"you feel the fresh morning light fill the Gulf of Lune with " +
	"magnificient blue and green colours as the Sea waves relentlessly " +
	"against the shore.",

	"you can see the Gulf of Lune coming in from the Great Sea in the " +
	"West, Belagear, with it's green and blue colours and gentle waves " +
	"slowly traversing against in your direction and eating yet more " +
	"land of the shores of Middle-Earth.",

	"you see the Sun passing across the sky ever more westwards and down. " +
	"Soon she will be going down below the horizon and into the Gulf of " +
	"Lune.",

	"you can only see half of the Sun in the red horizon. Soon the Sun " +
	"will not shine anymore, hearing only the ever continuing sounds of " +
	"waves from the Gulf of Lune beating against the western shores of " +
	"Middle-Earth.",

	"you can hear the Sea rumbling by the shore of the " +
	"Gulf of Lune in the early night."
    });


    if (!clock)
	return "you see the Gulf of Lune's waves gushing towards the shore "
	      +"in the early morning light.";

    hour = clock->query_hour();

    switch (hour)
    {
	case LATE_NIGHT:
	    return text[0];
	case EARLY_MORNING:
	    return text[1];
	case MORNING:
	    return text[2];
	case NOON:
	    return text[3];
	case AFTERNOON:
	    return text[4];
	case EVENING:
	    return text[5];
	case EARLY_NIGHT:
	    return text[6];
    }
}
