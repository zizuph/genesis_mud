/*
 * ne_court_base.c
 * 
 * Baseroom for the northeast courtyard in the ruins of 
 * Castle Chimera.
 *
 * Coded: Khail, Dec 5/96
 */
#pragma strict_types

#include "defs.h"
#include <composite.h>
#define NORTH     0
#define WEST      0
#define CENTRAL   1
#define SOUTH     2
#define EAST      2

inherit STDROOM;
               /* 0     1    2     3    4    5    6     7    8 */
string *dirs = ({"nw", "n", "ne", "w", "c", "e", "sw", "s", "se"});

public varargs int
room_index(int toggle = 0)
{
    int index;
    string arg;

    sscanf(file_name(TO), RUIN + "ne_court_%s", arg);
    index = member_array(arg, dirs);
    if (!toggle)
    {
        if (index < 0 || index > sizeof(dirs) - 1)
            return -1;
        else
            return index;
    }

  /* We want a row (north, central, or south) */
    if (toggle == 1)
    {
        if (index < 3)
            return 0;
        if (index < 6)
            return 1;
        else
            return 2;
    }

  /* We want a column (west, central, or east) */
    if (toggle == 2)
    {
        if (member_array(index, ({0, 3, 6})) >= 0)
            return 0;
        if (member_array(index, ({1, 4, 7})) >= 0)
            return 1;
        if (member_array(index, ({2, 5, 8})) >= 0)
            return 2;
    }
}

public int
player_knows_castle()
{
    int skill;
    skill = TP->query_skill(SK_ELDORAL_CASTLE_NAME);
    if (skill & SK_CASTLE_NAME_VALUE)
        return 1;
    return 0;
}

public string
castle_name()
{
    if (player_knows_castle())
        return "Castle Chimera";
    else
        return "an old castle";
}

public void
create_long()
{
    string temp,
           *exits;
    int row,
        column;
    
    exits = allocate(3);

    temp = "You are in a courtyard in the ruins " +
        "of " + VBFC_ME("castle_name") + ". Tall " +
        "walls of crumbling grey stone surround the " +
        "square courtyard on all sides, with only " +
        "a few apparent means of permitting egress. ";

    row = room_index(1);
    column = room_index(2);

  /* The northeast archway is only 'normally' visible in */
  /* rooms in rows 1 and 2 (central and south). */    
    if (row == NORTH)
    {
      /* If we are in the north row, we either don't see */
      /* the arch, or it's right beside us if we're in the */
      /* third (eastmost) column. */
        if (column == EAST)
            exits[0] = "a collapsed archway leads north into " +
                "the forest";
    }
    else
    {
        exits[0] = "a collapsed archway in the northeast " +
            "corner leads out into the forest";
    }

  /* Now, the stairs on the south wall are always visible, */
  /* however we get a 'near' desc if in the southmost column, */
  /* and a 'far' desc in the other two. */
    if (row == SOUTH)
    {
        if (column == WEST)
            exits[1] = "a stone stairway begins an ascent up " +
                "the southern wall here";
        else
            exits[1] = "a stone stairway ascends the side of the " +
                "southern wall rising above you";
    }
    else
    {
        exits[1] = "a stone stairway ascends the face of the " +
            "southern wall";
    }

  /* Now, the two tunnels are especially tricky, as we should */
  /* try to 'combine' their desc into a single sentence when */
  /* both are visible (it looks 'clunky' otherwise). */

  /* What to do if we're in the southernnmost wall. */
    if (row == SOUTH)
    {
        if (column == EAST)
            exits[2] = "two tunnels, one in the northwest corner, " +
                "and one immediately before you leading south, " +
                "delve beneath the ruins";
        else if (column == CENTRAL)
            exits[2] = "a tunnel in the northwest corner delves " +
                "beneath the ruins";
    }

  /* Now what to do if we're in the westmost wall. */
    else if (column == WEST)
    {
        if (row == NORTH)
            exits[2] = "two tunnels, one in the southeast corner, " +
                "and one immediately before you leading west, " +
                "delve beneath the ruins";
        else if (row == CENTRAL)
            exits[2] = "a tunnel in the southeast corner delves " +
                "beneath the ruins";
    }

  /* Otherwise, both tunnels should be normally visible. */
    else
        exits[2] = "two tunnels, in the northwest and southeast " +
            "corners, delve beneath the ruins";

    exits = filter(exits, stringp);

    temp += capitalize(COMPOSITE_WORDS(exits)) + ". ";

    temp += "The most notable feature of the decaying " +
        "courtyard, however, is the mysterious series of " +
        "black stone obelisks standing at its heart.\n\n";

    set_long(temp);
}

public void
create_courtyard()
{
    string temp;
    int index;

    index = room_index();
    if (index < 0)
        return;
    set_short("a courtyard in the ruins of " +
        VBFC_ME("castle_name"));
    
    add_item(({"pillars", "obelisks", "pillar", "obelisk"}),
        ({"To the southeast", "To the south",
        "To the southwest", "To the east", "All around you",
        "To the west", "To the northeast", "To the north",
        "To the northwest"})[index] + " rise twelve strange " +
        "pillars or obelisks of some sort. They appear to be carved " +
        "from single pieces of some black stone, and at one " +
        "time were probably perfectly rectangular, but time " +
        "and the elements have smoothed and worn them into " +
        "almost into shapes more consistant with a cylinder. " +
        "The pillars stand in an almost random placement at " +
        "various places around a pattern on the ground.\n");
    add_item(({"pattern"}),
        (index != 4 ? "In the center of the courtyard, you " +
        "can see a pattern of some sort in the placement of " +
        "the stones on the ground, around which stand a dozen " +
        "dark pillars.\n" : "Beneath you on the ground, dark " +
        "stones form a strange pattern beneath your feet. " +
        "spread over a fair distance, it's difficult to get " +
        "a grasp of what the pattern might represent or be " +
        "from this close. The twelve pillars, which now " +
        "surround you in a roughly circular formation, stand " +
        "at seemingly random points around the pattern.\n"));
    add_item(({"walls"}),
        "There are four main walls surrounding the courtyard, " +
        "located on and marking the north, south, east and " +
        "west boundaries of it. All of them are in various " +
        "stages of ruin and collapse, the north and east " +
        "walls being at a much more advanced stage than the " +
        "south and west.\n");
    add_item(({"west wall"}),
        ((index == 0 || index == 3 || index == 6) ? 
        "Immediately to your west" : "Across the " +
        "courtyard to the west") + " rises the west wall of " +
        "the courtyard. It's in rather good condition, " +
        "crumbling and cracking only around the upper edge, " +
        "showing signs of decay but not yet any real damage. " +
        "You also observe a dark opening in the bottom corner " +
        "of the north end of the wall, leading through the " +
        "stone beneath the ruins themselves.\n");
    add_item(({"south wall"}),
        (index > 5 ? "Immediately to " +
        "the south" : "Across the courtyard to the south") + 
        " rises the south wall of the courtyard. It's in fairly " +
        "good condition, with little damage aside from a few " +
        "missing stones, and some serious crumbling of the " +
        "ramparts at the top. You notice a long staircase " +
        "that starts at the bottom of the west end of the " +
        "wall, and slants eastwards to reach the top at " +
        "the east end of the wall. Also, you " +
        "notice a dark opening at the base of the eastern " +
        "end of the wall, leading southwards through its " +
        "surface.\n");
    add_item(({"north wall"}),
        (index < 3 ? "Immediately to the north" : "Across the " +
        "courtyard to the north") + " rises the heavily " +
        "damaged northern wall of the courtyard. It looks " +
        "to have absorbed quite a lot of damage over the " +
        "years, as the battlements have all but crumbled " +
        "away into nothing. Large holes stand open where " +
        "blocks of stone have cracked and fallen out of " +
        "place, smashing into the ground below. In fact, " +
        "most of the entire eastern end of the wall has " +
        "collapsed into a pile of rubble, leaving a ragged " +
        "opening where once an archway stood, leading out " +
        "into the forest.\n");
    add_item(({"east wall"}),
        ((index == 2 || index == 5 || index == 8) ? "Immediately " +
        "to the east" : "Across the courtyard to the east") +
        " rises the eastern wall of the courtyard. It has " +
        "suffered a fair amount of damage over the years, " +
        "with gaping holes along the top where battlements " +
        "once stood, and topped now only by crumbling holes " +
        "and massive fractures.\n");
    add_item(({"sky", "fog", "mist"}),
        "Overhead, a dense white mist blankets the sky " +
        "obscuring anything more than a good stone's " +
        "throw distant.\n");
    add_item(({"stairs", "staircase", "stairway"}),
        (index != 6 ? "Across the courtyard at the base " +
        "of the west end of the south wall " : "Here " +
        "at the base of the south wall ") + "rests the " +
        "bottom of a narrow stone staircase that ascends " +
        "diagonally across the face of the wall, topping " +
        "the wall at the east end.\n");
    add_item(({"openings", "dark openings"}),
        "You can see dark openings in the northwest " +
        "and southeast corners of the courtyard.\n");
    add_item(({"northwest opening"}),
        (index != 0 ? "Across the courtyard, at the " +
        "base of the northern end of the west wall, " :
        "Rising before you in the base of the west " +
        "wall, ") + "a dark opening passes westwards " +
        "through the wall and beneath the ruins.\n");
    add_item(({"southeast opening"}),
        (index != 8 ? "Across the courtyard, at the " +
        "base of the eastern end of the south wall, " :
        "Rising before you in the base of the south " +
        "wall, ") + "a dark opening passes southwards " +
        "through the wall and beneath the ruins.\n");
    add_item(({"ruins", "buildings", "towers"}),
        "Beyond the tops of the south and west walls, " +
        "you can see the crumbling and partially " +
        "collapsed ruins of many buildings and towers " +
        "that were once home to the denizens of Castle " +
        "Chimera, many, many years ago.\n");
    add_item(({"ground", "flagstones"}),
        "The ground of the courtyard is rougly paved " +
        "with hundreds of large flagstones. It might " +
        "once have been a well-laid floor, but time " +
        "has had its way with them, like everything " +
        "else here, and now the flagstones are loosely " +
        "in place and for the most part split and cracked " +
        "into several smaller portions of their former " +
        "wholes.\n");
} 
