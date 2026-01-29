/*
 *	/d/Gondor/lebennin/road/road.c
 *
 *	Coded by Olorin, February 1997
 *
 *	Copyright (c) 1997 by Christian Markus
 *
 *	Modification log:
 */
#pragma strict_types

inherit "/d/Gondor/common/lib/area_room.c";

#include "/d/Gondor/defs.h"

public void
create_road()
{
}

nomask void
create_area_room()
{
    set_land("Gondor");
    set_areatype(8);
    set_areaname("Lebennin");

    create_road();

}

static void
add_road(int repair, string extra = 0)
{
    string  desc = "This is the road that connects Pelargir "
	         + "in the south with Minas Tirith, the Capital "
		 + "of Gondor, running through the length of "
	         + "Lebennin from the south to the north.",
            stone_desc;

    if (repair)
    {
	desc += " It is made from paved stones ";
	stone_desc =
	    "The road is made from large flat stones ";
    }

    switch (repair)
    {
    case 0:
    default:
	break;
    case 1:
	desc += "and is in good repair and free of growth.";
	stone_desc += "that have been fitted together expertly. "
	    + "The stones are level and none of them are broken, "
	    + "even though they show the signs of heavy use.";
	break;
    case 2:
	desc += "and is in generally good repair, although "
	    + "in some places there is grass growing from the "
	    + "cracks between the stones.";
	stone_desc += "that have been fitted together with "
	    + "great care. The stones are level and none of "
	    + "them are broken even though they show the signs "
	    + "of age and heavy use. In some places, the cracks "
	    + "between them have widened and grass is growing "
	    + "there.";
	break;
    case 3:
	desc += "but is not in good repair. The signs of age "
	    + "and heavy use show heavily. Some of the paved "
	    + "stones are broken, and in some places there are "
	    + "even a few missing at the sides of the road.";
	stone_desc += "that once have been fitted together with "
	    + "great care and expertise. But time and heavy use "
	    + "have left many traces, some stones are broken, "
	    + "and a few are missing.";
	break;
    }

    if (strlen(extra))
	desc += " " + extra;

    add_item( ({ "road", }), BSN(desc));
    if (strlen(stone_desc))
	add_item( ({ "stones", "paved stones", }), BSN(stone_desc));
}

static void
add_ground(string vegetation = 0, string extra = 0)
{
    string  desc = "On the road, the ground is covered by "
	+ "paved stones. To both sides of the road ";

    if (!strlen(vegetation))
    {
	if (!strlen(grass))
	    set_grass("green");
	vegetation = grass + " grass";
    }

    desc += vegetation + " is growing.";

    if (strlen(extra))
	desc += " " + extra;

    add_item( ({ "ground", }), BSN(desc));
}

static void
add_rammas(string dir = "northeast", string extra = 0)
{
    string  desc;

    desc = "To the " + dir + " is the dark shape of the Rammas "
	+ "Echor, the large outer wall of Minas Tirith that "
	+ "encircles all of the Pelennor";

    if (strlen(extra))
	desc += " " + extra;

    add_item( ({ "rammas", "rammas echor", "wall", "outer wall", }),
	     BSN(desc));
}

static void
add_white_mountains(string dir = "north", string extra = 0)
{
    string  desc;

    desc = "To the "+dir+", the snow-covered tops of the Ered Nimrais, "
	+ "the White Mountains of Gondor, are running from west to "
	+ "east all along the horizon. One the eastern end of the "
	+ "mountain-range, mighty Mindolluin rises, guarding over "
	+ "Minas Tirith, the Tower of Guard, which lies on a hill "
	+ "at the feet of the Mindolluin.";

    if (strlen(extra))
	desc += " " + extra;

    add_item( ({ "ered nimrais", "white mountains", "mountains", 
		 "mindolluin", }), BSN(desc));
    add_item( ({ "minas tirith", }),
	"Minas Tirith cannot be seen from here, it is too far away.\n");
}

static void
add_harlond()
{
    add_item( ({"harlond","the harlond","dock"}), BSN(
        "The Harlond is the harbour of Minas Tirith. It lies " +
	"just outside the Rammas Echor south of Minas Tirith " +
	"where the Anduin makes a bend, flowing westwards for " +
        "a short stretch before turning south towards the Sea " +
	"again. Ships travelling on the Anduin but also some " +
	"ocean-going vessels land there."));
}

static void
add_anduin(string where, string extra = 0)
{
    string  desc = "";

    switch (where)
    {
    case "harlond":
	desc += "Just south of Minas Tirith, the Anduin flows "
	    + "westward for a short stretch before it turns south "
	    + "and towards the Sea again. In that bend lies the "
	    + "Harlond, the harbour of Minas Tirith.";
	break;
    case "north":
	desc += "The road does not follow the river, but travels "
	    + "south a short way west of it. Beyond green fields "
            + "and meadows east of the road, the wide blue-green "
            + "band of the waters of the Anduin is visible in the "
            + "distance.";
	break;
    case "central":
	desc += "The road runs south several miles west of the "
            + "Anduin. The river can be seen in the distance as "
	    + "a wide blue band between green fields and meadows.";
	break;
    case "south":
	desc += "The plain slopes gently down towards the river "
	    + "over a distance of many miles. From the slightly "
	    + "elevated perspective on the plain north of Pelargir, "
            + "the course of the river can be seen for as many "
            + "miles, as the Anduin flows slowly from the north "
            + "to the Sea, forming a wide bend to the southwest "
            + "where Pelargir lies upon its western bank.";
	break;
    }

    if (strlen(extra))
	desc += " " + extra;

    if (strlen(desc))
	add_item( ({ "river", "great river", "anduin", }), 
		 BSN(desc));
}

static void
add_plain(string where, string extra = 0)
{
    string  desc = "";

    switch (where)
    {
    case "forest":
	desc = "The great plain stretches out in all direction south of the "
	    + "narrow forest, gently sloping down towards to river. In the "
	    + "east and the south, the plain ends on "
	    + "the banks of the Anduin, while it seems to extend endlessly "
	    + "to the west.";
	break;
    case "city":
	desc = "North of Pelargir and west of the Anduin lies great "
	    + "wide plain, which rises very gently towards the north "
	    + "and the west. The road that connects Pelargir and "
            + "Minas Tirith in the north runs over that plain close "
            + "to the Anduin.";
	break;
    }

    if (strlen(extra))
	desc += " " + extra;

    if (strlen(desc))
	add_item( ({ "field", "fields", "plain", "plains", }), BSN(desc));
}

static void
add_pelargir(string distance, string extra = 0)
{
    string  desc = "";

    switch (distance)
    {
    case "far":
	desc = "The city of Pelargir is located at the southern end of a "
	    + "long, gently sloped plain that stretches from the White "
	    + "Mountains to the Anduin river. On the way the plain drops "
	    + "several hundred feet in altitude and the view south is "
            + "excellent. The city can be seen in the far distance as "
	    + "a grey and silver area within the green fields of "
            + "Lebennin west of the blue wide band of the Anduin.";
	break;
    case "medium":
	desc = "Pelargir upon Anduin is still many leagues away, but "
	    + "across the gently sloping plain one can already make out "
	    + "some details like the towers and the city walls.";
	add_item( ({ "towers", "tower", }), BSN(
	    "While the towers set into the city wall surrounding " +
            "Pelargir can hardly be distinguished from the walls, a " +
            "a high tower set into the center of the city can clearly " +
            "be made out even from this far away. Left of the high " +
            "tower and almost built into the waters of the Anduin " +
            "rises a smaller tower which might be a lighthouse."));
    case "close":
	desc += "Pelargir is not far away to the south, its mighty "
	    + "city walls almost going out of your field of view. "
	    + "Set into the walls are mighty watchtowers, squat and "
	    + "low, but well fortified. Behind the walls, some of "
	    + "the roofs can be seen, but most prominent are the two "
            + "towers rising above them, a tall white tower in the "
            + "middle of the city, and what probably is a lighthouse "
            + "closer to the Anduin.";
	break;
    }

    if (strlen(extra))
	desc += " " + extra;

    if (strlen(desc))
	add_item( ({ "pelargir", "pelargir upon anduin", "city", }),
	    BSN(desc));
}

static void
add_fields(string extra = 0)
{
    string  desc =
	"To both sides of the road are the green fields of Lebennin, " +
        "reaching in the east as far as the Anduin and in the west " +
        "as far as the eye can see.";

    if (strlen(extra))
	desc += " " + extra;

    add_item( ({ "field", "fields", "lebennin", }), BSN(desc));
}
