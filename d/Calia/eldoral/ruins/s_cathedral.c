#pragma strict_types

#include "../defs.h"
#define LIVE_I_FOUND_PANEL   "_live_i_found_panel"

inherit STDROOM;

int sceptre_found;

public string exa_altar();
public string exa_panels();
public string exa_back_panel();
public int north_msg();

public void
reset_room()
{
    ::reset_room();
    sceptre_found = 0;
}

public void
create_room()
{
    set_short("a cathedral in " + CASTLE_NAME);
    set_long("You've entered a large, magnificent room. Judging " +
        "from the furnishings, you're in what was once a cathedral " +
        "of sorts, now decayed into dusty ruins. To the west, " +
        "massive doors of solid wood, once richly polished and " +
        "carved, now dried, cracked and worm-ridden, hang ajar and " +
        "seized on their hinges. At the opposite end of the room, " +
        "to the east, the floor is elevated a few feet, with " +
        "steps at either corner leading up to the dais. Upon " +
        "the platform, a stone altar rests before chipped " +
        "carvings. The main floor of the cathedral is cluttered " +
        "by rows of dried out wooden benches, huddled beneath " +
        "the massive stone columns rising from the floor to the " +
        "arched ceiling of the chamber. To the south, the jagged " +
        "remains of what might have been windows with some sort " +
        "of colouring stand high upon the walls. Light falling " +
        "down from the outside across these coloured shards of " +
        "glass fills the peacefully ancient cathedral with a rainbow " +
        "of light, dancing off the dust which hangs in the " +
        "air. In the north, a set of stairs lead upwards along " +
        "the wall to a doorway that passes through the wall into " +
        "darkness.\n\n");

    add_item(({"doors", "massive doors"}),
        "At the west end of the room, massive doors stand ajar. " +
        "They must have been beautifully carved and polished " +
        "at one time, but now they are worm-ridden and appear " +
        "ready to fall apart any day.\n");
    add_item(({"dais", "platform", "steps"}),
        "The floor is raised up a few feet to form a dais at " +
        "the east end of the room, with shorts steps leading " +
        "up to it. Upon the platform stands a low stone podium, " +
        "and beyond that some carvings on the wall.\n");
    add_item(({"carvings", "man", "chimeras"}),
        "Beyond the altar on the dais, stone carvings in the " +
        "wall depict a strange figure of a man, bearing a sword " +
        "in one hand, and a dove in the other. On either side " +
        "of the man, stone chimeras look on in silence.\n");
    add_item(({"benches", "wooden benches"}),
        "Dominating most of the floor space in the cathedral, " +
        "long wooden benches, or what remains of them, stand " +
        "in neat rows, lining each side of the room.\n");
    add_item(({"columns", "massive columns", "stone columns",
        "massive stone columns"}),
        "Rising from the floor to the dizzying heights of the " +
        "ceiling, wide stone columns easily three times as " +
        "thick as a man stand in ordered rows down the length " +
        "of the room.\n");
    add_item(({"ceiling", "arched ceiling"}),
        "High above you, the ceiling of the chamber is arched " +
        "gracefully. The number of holes now present, however, " +
        "dictates that grace and strength are not the same " +
        "thing.\n");
    add_item(({"windows"}),
        "High on the south wall, jagged remains of what " +
        "were once windows of some sort filter light passing " +
        "through into a spectacular rainbow of colours.\n");

    add_item(({"altar", "pedestal", "podium"}), "@@exa_altar");
    add_item(({"panel", "panels", "panels on altar", "panelling"}),
        "@@exa_panels");
    add_item(({"back panel", "panel on back", "false panel",
        "panel on back of altar"}), "@@exa_back_panel");

    INSIDE;

    add_exit(RUIN + "cath-build1", "west");
    add_exit(RUIN + "cath-build4", "north", "@@north_msg");

    add_prop(OBJ_S_SEARCH_FUN, "search_altar");
    add_prop(OBJ_I_SEARCH_TIME, 5);

    set_alarm(0.0, 0.0, reset_room);
}

public string
exa_altar()
{
    string ret;

    ret = "The altar seems to be quite well made. It has a " +
        "largely stone frame, with wooden panelling inlaid " +
        "into the sides and top.\n";

    if (sceptre_found)
        ret += "One of the panels has been smashed apart, " +
            "and whatever was within taken.\n";
    return ret;
}

public string
exa_panels()
{
    string ret;

    ret = "The panels are inlaid into the stone frame of the " +
        "podium on all sides. However they may have looked " +
        "while new, they are now rotten, dried, and splintery.\n";
    if (sceptre_found)
        ret += "One of the panels has been smashed open, and " +
           "whatever was contained within taken.\n";
    return ret;
}

public string
exa_back_panel()
{
    if (!TP->query_prop(LIVE_I_FOUND_PANEL))
        return "You seen nothing remarkable about them.\n";
    else if (sceptre_found)
        return "It appears to have concealed something once, " +
            "but it's been smashed open, its treasure taken.\n";
    else
        return "It appears to be a false panel that covers " +
           "something.\n";
}

public int
north_msg()
{
    write("You climb the stairs and slip inside the dark doorway " +
        "in the north wall.\n");
    say(QCTNAME(TP) + " climbs the stairs and slips inside the " +
        "doorway in the north wall.\n");
    return 0;
}

public string
search_altar(object player, string extra)
{
    object sceptre;

    if (extra == "altar")
    {
        if (sceptre_found)
        {
            return "You give the altar a careful once-over, " +
                "discovering the shattered remains of a " +
                "false panel. What might once have been " +
                "inside remains a mystery.\n";
        }
        TP->add_prop(LIVE_I_FOUND_PANEL, 1);
        return "You give the altar a careful " +
            "once-over, discovering a false panel on the " +
            "back.\n";
    }
    else if (extra == "false panel" ||
        extra == "back panel" ||
        extra == "panel on back" ||
        extra == "panel on back of altar")
    {
        if (!TP->query_prop(LIVE_I_FOUND_PANEL))
            return "";
        else if (sceptre_found)
            return "It's definately a false cover, but " +
                "whatever it covered is long gone.\n";
        else
            sceptre = clone_object(OBJ + "sceptre");
            sceptre->move(TO);
            sceptre_found = 1;
            player->add_prop(LIVE_I_BEAST_QUEST,
                player->query_prop(LIVE_I_BEAST_QUEST) | BQ_FOUND_SCEPTRE);
            return "You confirm your suspicions that the " +
                "panel is a fake, and give it a sharp " +
                "blow. It shatters into splinters easily, " +
                "and somethings falls out onto the ground.\n";
    }
    return "";
}
