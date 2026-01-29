/*
 * /d/Gondor/pelargir/pelargir_room.c
 *
 * Copyright (C) 1999 by Cooper Sherry (Gorboth) and
 *	Nancy L. Mintz (Gnadnar)
 *
 * base room for pelargir
 *
 */

#pragma strict_types

inherit "/d/Gondor/std/room";

#include "/d/Gondor/defs.h"
#include "pelargir_room.h"

static int	Room_type;	/* types defined in pelargir_room.h */
static string	Extra_desc;	/* meat of long desc, other stuff 
				 * (time of day, type of town, etc)
				 * may be wrapped around it.
				 * no ending newline!
				 */
static string	Street_name;	/* defined in pelargir_room.h 
				 * to prevent minor but annoying
				 * variances in spelling
				 */
static string	Part;		/* also defined in pelargir_room.h
				 * to avoid mixtures of e.g., "north"
				 * and "northern"
				 */


/* prototypes in order of appearance */
public void	create_pelargir_room();
nomask void	create_gondor();
public string	long_func();
public void	set_room_type(int type);
public int	query_room_type();
public void	set_street_name(string street);
public string	query_street_name();
public void	set_part(string part);
public string	query_part();
public void	set_extra_desc(string desc);
public string	query_extra_desc();


/*
 * Function name:	create_pelargir_room
 * Description	:	configure your room here
 */
public void
create_pelargir_room()
{
} /* create_pelargir_room() */

/*
 * Function name:	create_gondor
 * Description	:	set up common stuff
 */
nomask void
create_gondor()
{
    create_pelargir_room();
    if (!short())
    {
	set_short("On " + Street_name + " in " + Part + " Pelargir");
    }
    if (!query_long())
    {
	set_long(long_func);
    }

    /* set up default items for this room type */
    /* XXX what items for which type? what items everywhere?
     * do items vary by part, as well as type -- lighthouse
     * visible in north for example
     */
    switch (Room_type)
    {
    case TYPE_STREET:
        try_item( ({ "street", "ground" }), BSN(
            "The street here is made of large stone slabs which show"
         + " the heavy use it has received through the centuries."));
        try_item( ({ "slab", "slabs", "stone slabs", "large slabs",
                     "large stone slabs", "stone slab", "large slab",
                     "large stone slab" }), BSN(
            "The slabs are immenesely thick, and covered with many"
          + " cracks and scars which have been delivered over the"
          + " many years of use."));
        try_item( ({ "crack", "cracks", "scar", "scars",
                     "scars and cracks", "cracks and scars" }), BSN(
            "In some cases the cracks have completely split the"
          + " stone slab in two. Newer material has been used"
          + " in some places to repair the worst erosion."));
        try_item( ({ "new material", "material", "newer material",
                     "erosion", "worst erosion" }), BSN(
            "The worst cases of the erosion have been patched up"
          + " with newer material, to insure a safe passage for"
          + " carts and horses."));
        break;
    case TYPE_DOCKS:
	break;
    case TYPE_POOR:
	break;
    case TYPE_SQUARE:
	break;
    }

    /* taking the easy way out ... generic items more or
     * less applicable to all outdoor rooms :-)
     */
    try_item(LOW(Street_name), long_func);
    try_item( ({ "harbour", "harbour area" }), BSN(
        "The harbour is obviously a very central location for"
      + " commerce in Pelargir. Activity of all sorts is taking"
      + " place on the docks."));
    try_item( ({ "house", "houses", "home", "homes",
                 "building", "buildings", "dwelling",
                 "dwellings" }), BSN(
        "The many houses which run along the streets of Pelargir"
      + " reflect various and sundry styles and levels of affluence."
      + " Some are large and display cunning architecture, while"
      + " others are little more than square shacks."));
    try_item( ({ "architecture", "cunning architecture" }), BSN(
        "The architecture to be found in Pelargir is wide and"
      + " varied. Many examples exist of the stylings of Old"
      + " Gondor from hundreds of years past."));
    try_item( ({ "pelargir", "city", "town", "here",
                 "area", "city of pelargir", "pelargir city" }), BSN(
        "The City of Pelargir covers a large area of the surrounding"
      + " landscape, extending east towards the edge of the River"
      + " Anduin, and west towards fertile farmland."));
    try_item( ({ "river", "rivers" }), BSN(
        "The city is surrounded by rivers on both sides. To the west,"
      + " the Sirith runs down from its sources in the far north."
      + " East flows the mighty Anduin, greatest of the waterways"
      + " in Middle Earth."));
    try_item( ({ "sirith", "river sirith", "sirith river" }), BSN(
        "The River Sirith flows to the west of the City where it"
      + " flows down from the feet of the Ered Nimrais far to"
      + " the north."));
    try_item( ({ "ered nimrais", "mountains", "mountain" }), BSN(
        "The mountais are visible far on the horizon to the north,"
      + " standing as dim shadows in the distance."));
    try_item( ({ "anduin", "river anduin", "anduin river",
                 "mighty anduin", "anduin the great" }), BSN(
        "The mighty Anduin flows to the east, running the final"
      + " laps of its long channel to the sea."));
    try_item( ({ "sea", "ocean" }), BSN(
        "The sea is yet a good distance to the southwest, past"
      + " the Mouths of the Anduin and the Bay of Belfalas."));
    try_item( ({ "bay of belfalas" }), BSN(
        "The Bay of Belfalas is far from view here."));
    try_item( ({ "mouths", "mouths of the anduin" }), BSN(
        "The Mouths of the Anduin are barely visible in the great"
      + " distance to the southwest, marking the final egress"
      + " of the Anduin from Middle Earth."));
    try_item( ({ "ship", "ships", "boats", "boat" }), BSN(
        "Ships of all sorts come to port here in the City of"
      + " Pelargir. Their masts are visible standing in bobbing"
      + " rows along the eastern docks."));
    try_item( ({ "mast", "masts", "masts of the ships" }), BSN(
        "The masts of the ships dip and sway with the waves along"
      + " the docks of Pelargir."));
    try_item( ({ "dock", "docks", "docks of pelargir" }), BSN(
        "Docks are plentiful in the city of Pelargir. Though not"
      + " always visible from the city streets, the tall masts"
      + " of the ships at port are a constant reminder of their"
      + " presence."));
    try_item( ({ "port", "port of pelargir" }), BSN(
        "The port of Pelargir is a bustling hub of commerce and"
      + " trade. Activity is everywhere in this city."));
    try_item( ({ "sky", "up" }), BSN(
        "The sky is filled with billowing clouds and gulls from"
      + " the sea."));
    try_item( ({ "cloud", "clouds", "billowing cloud",
                 "billowing clouds" }), BSN(
        "Clouds are visible in the sky, rolling in from the sea"
      + " far to the south."));
    try_item( ({ "bird", "birds", "gull", "gulls", "seagull",
                 "seagulls" }), BSN(
        "The cry of the gulls is ever present over the"
      + " roofs of Pelargir. The birds are visible hovering"
      + " over the docks, looking for food."));
    try_item( ({ "roof", "roofs", "roofs of pelargir" }), BSN(
        "The roofs of the houses of Pelargir dot the horizon."));
    try_item( ({ "street", "streets", "streets of pelargir",
                 "city street", "city streets",
                 "streets of the city", "road", "roads" }), BSN(
        "The streets of the city are crowded in many places, even"
      + " at night, where the activity never seems to die down."));
    try_item( ({ "door", "doors", "doorway", "doorways" }), BSN(
        "The doors of the many houses of the city are often"
      + " decorated by a small window or a nameplate."));
    try_item( ({ "window", "windows", "small window" }), BSN(
        "Many of the windows in the houses of the city are lit,"
      + " occasionally revealing a shadow or two moving within"
      + " the house."));
    try_item( ({ "plate", "nameplate", "name plate" }), BSN(
        "The names of the people of Pelargir have a noble ring to"
      + " them, in many cases suggesting a hint of the Numenoreans"
      + " of old."));
    try_item( ({ "ground", "down", "floor", "earth" }), BSN(
        "The ground is for the most part kept litter-free here"
      + " within the city, where citizens take great pride in their"
      + " heritage and homesteads."));

} /* create_gondor */


/*
 * Function name:	long_func
 * Description	:	VBFC for room long
 * Returns	:	string -- the desc
 *
 * XXX square will need to mask this
 */
public string
long_func()
{
    return BSN("On " + Street_name + " in the " + Part +
	    " parts of Pelargir. It is " + tod() +
	    ". " + Extra_desc);
} /* long_func */


public void	set_room_type(int type)		{ Room_type = type;     }
public int	query_room_type()		{ return Room_type;     }
public void	set_street_name(string street)	{ Street_name = street; }
public string	query_street_name()		{ return Street_name;   }
public void	set_part(string part)		{ Part = part;          }
public string	query_part()			{ return Part;          }
public void	set_extra_desc(string desc)	{ Extra_desc = desc;    }
public string	query_extra_desc()		{ return Extra_desc;    }
