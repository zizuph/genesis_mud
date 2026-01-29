/* square3_1.c
 * metaprat - 920703
 * Updated by Shinto 10-19-98
 * Lilith -- changed the path to the gem recover room from Sorgum's
 *           directory to the /d/Terel/zodiac dir  6/5/08
 * Jan 2021, Lucius - Modernized
 *
 * Town square, north side
 */
#include "/d/Terel/include/Terel.h"
inherit STDROOM;


public int
has_solved_zodiac(object pl)
{
    /* wizards can see it even if they haven't sdone the zodiac quest */
    if (pl->query_wiz_level())
	return 1;

    if ((pl->test_bit("Terel", QUEST_POR_GROUP,   QUEST_POR_BIT)   == 0) ||
        (pl->test_bit("Terel", QUEST_FIRE_GROUP,  QUEST_FIRE_BIT)  == 0) ||
        (pl->test_bit("Terel", QUEST_BAL_GROUP,   QUEST_BAL_BIT)   == 0) ||
        (pl->test_bit("Terel", QUEST_DEATH_GROUP, QUEST_DEATH_BIT) == 0) ||
        (pl->test_bit("Terel", QUEST_MAZE_GROUP,  QUEST_MAZE_BIT)  == 0) ||
        (pl->test_bit("Terel", QUEST_CHI_GROUP,   QUEST_CHI_BIT)   == 0) ||
        (pl->test_bit("Terel", QUEST_ZOD_GROUP,   QUEST_ZOD_BIT)   == 0))
    {
	return 0;
    }

    return 1;
}

public string
my_long()
{
    string desc =
        "You are on the northern edge of a bustling town square. A huge " +
        "pine tree is towering above you to the northwest, next to a road " +
        "going into the forest. To the south, you see a monument, and beyond "+
        "it an inn, next to a couple of roads leading from the southwest " +
        "corner of the square. To your east is a town hall, and south of that "+
        "is another building.\n";

    if (has_solved_zodiac(TP))
    {
	desc += "There is an obelisk here which emanates an aura " +
            "of powerful magic.\n";
    }

    return desc;
}

public void
create_terel_room()
{
    set_short("Calathin Town Square, Northern edge");
    set_long("@@my_long");

    add_item( ({ "huge tree", "pine", "huge pine" }),
      "The tree looks like an ancient pine, about 100 meters tall or more. " +
      "It is towering above to the northwest. You can see some kind of " +
      "entrance on the south side of the trunk, and a sign, which is too far "+
      "away to read.\n");

    add_item( ({ "buildings" }),
      "To your south, across the square, you can see an inn, while to the " +
      "east you see a town hall and another unidentified building. To the " +
      "northwest, you can see an entrance leading into the huge pine tree, " +
      "which appears to be fairly busy.\n");

    add_item( ({ "town square", "square" }),
      "The square is bustling with people... maybe it's market day here?\n");

    add_item( ({ "mist", "icy mist" }),
      "The mist is just the effect of the chill weather on the water vapor " +
      "in the air.\n");

    add_item( ({ "snow" }),
      "There is no snow here at all, it's all been trodden into oblivion. " +
      "There is a lot of snow on the trees in the forest, and also in the " +
      "landscape visible from here.\n");

    add_item( ({ "ground", "footprint", "footprints" }),
      "Deeply frozen all year round, the ground never holds footprints.\n");

    add_item( ({ "monument", "statue" }),
      "It appears to be someone on a horse, modelled out of granite, and " +
      "facing towards the east. No other details are visible from this " +
      "distance.\n");

    add_cmd_item(
      ({ "tree", "huge tree", "pine", "huge pine", "huge pine tree", "up" }),
      "climb",
      "You're standing about 3 meters away from it... go west.\n");

    add_item("obelisk", "@@obelisk_desc");

    add_prop(OBJ_S_WIZINFO, "Those mortals who see the obelisk here have " +
      "solved the _full_ zodiac quest. If their gem has been lost " +
      "they _may_ recover it by touching the obelisk. They will " +
      "not recover the gem if they lost it by their own misuse.\n");

    add_exit(CALATHIN_DIR + "square4_1", "east", 0);
    add_exit(CALATHIN_DIR + "square3_2", "south", 0);
    add_exit(CALATHIN_DIR + "square2_1", "west", 0);
    add_exit(CALATHIN_DIR + "caravan_office", "north", 0);

    add_npc(CALATHIN_DIR + "npc/std_move_citizen");
}

public string
obelisk_desc()
{
    if (has_solved_zodiac(TP))
    {
	return "The obelisk is crafted of black obsidian. The obelisk " +
            "bears the symbol of a magical gem, glowing in all the " +
            "colours of the rainbow. The gem symbol is that of the " +
            "zodiac gem and it is here that those who have lost " +
            "their gem may have it restored. You " +
            "can 'place hand on obelisk' to enter.\n";
    }

    return "You see no obelisk.\n";
}

public int
do_touch(string str)
{
    if (!strlen(str))
    {
	NF("Place hand on what?\n");
	return 0;
    }

    if ((str == "hand on symbol") || (str == "hand on obelisk"))
    {
	if (has_solved_zodiac(TP))
        {
	    if (present("Terel_ZODIAC_gem", TP))
            {
		write("Your zodiac gem glows brightly for a moment and then " +
		  "returns to normal.\n");
		return 1;
	    }
	    else
            {
		write("Suddenly your surroundings change!\n");
		say(QCTNAME(TP) + " touches the obelisk and disappears in " +
		  "a puff of smoke!\n");
		TP->move_living("by the powers of the zodiac",
		  ZODIAC_DIR + "gem_recover", 1);
		return 1;
	    }
	}
	else
        {
	    NF("You see no obelisk.\n");
	    return 0;
	}
    }

    NF("Place hand on what?\n");
    return 0;
}

public void
init()
{
    ::init();
    add_action(do_touch, "place");
}

