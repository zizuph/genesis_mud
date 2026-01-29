/*
 *  /d/Emerald/telberin/telberin_street.c
 *
 *  This is the main room to be inherited by streets in the city of
 *  Telberin in Emerald. It contains functionality for building code
 *  as well as street names. It also contains the primary descriptions
 *  for add_items which reveal the city to players.
 *
 *  Copyright (c) April 2003 by Shiva, and Cooper Sherry (Gorboth)
 */
#pragma strict_types
inherit "/d/Emerald/telberin/telberin_room";

#include "defs.h"
#include <filepath.h>
#include "/d/Emerald/sys/time.h"

/*
 *  Prototypes
 */
public void        add_building(string building);
public void        add_street_items();


public void
config_street_room(string quarter, string street)
{
    config_telberin_room(quarter);

    if (strlen(quarter))
    {
        set_short("On " + street + " in the " + quarter + 
            " Quarter of Telberin");
    }
    else
    {
        set_short("On " + street + " in Telberin");
    }
}

public void
create_telberin_street()
{
}

nomask public void
create_telberin_room()
{
    string *buildings;

    setuid();
    seteuid(getuid());
    
#if defined(USE_TELBERIN_BUILDING_MANAGER) && USE_TELBERIN_BUILDING_MANAGER
    if (sizeof(buildings =
        TELBERIN_BUILDING_MANAGER->query_buildings(this_object())))
    {
        map(buildings, add_building);
    }
#endif

    create_telberin_street();

    /* We call this after the create function so that the try_item
     * can do its job, and not create duplicate versions of the
     * the same add_item.
     */
    add_street_items();
    add_telberin_outside_items();
}

/*
 * Function name: check_exit_dest
 * Description:   We may have more than one exit that uses the "enter" verb,
 *                so we use this block function to distinguish between
 *                "enter post office" and "enter bank", for instance.
 * Arguments:     1. (mixed)  The id(s) associated with this exit.
                              "post office" or "bank", for example.
 *                2. (string) An optional message indicating that the exit
 *                            is closed
 * Returns:       0 - This is the exit you're looking for, and it's open
 *                1 - This is the exit you're looking for, and it's closed
 *                2 - This isn't the exit you're looking for
 */
varargs public int
check_exit_dest(mixed dest_ids, string closed_mess)
{
    int i;
    string dircmd = query_dircmd();

    if (!strlen(dircmd))
    {
        return 2;
    }

    if (stringp(dest_ids))
    {
        dest_ids = ({ dest_ids });
    }
    else if (!pointerp(dest_ids))
    {
        return 2;
    }

    for (i = 0; i < sizeof(dest_ids); i++)
    {
        string tmp;
        if ((dest_ids[i] == dircmd) ||
            parse_command(dircmd, ({}), dest_ids[i], tmp))
	{
            if (closed_mess)
	    {
                write(closed_mess);
                return 1;
	    }

            return 0;
	}
    }

    return 2;
}

/*
 * Function name: add_building
 * Description:   This can be used to add special features to this room
 *                related to a particular "building" (room) that connects to
 *                it.
 * Arguments:     1. (string) The filename of the building.
 */
public void
add_building(string path)
{
    mixed m, dest_id;

    // We can use relative paths for this, just like for add_exit()
    if (stringp(path) &&
        (path[0] != '/') &&
        (path[0] != '@'))
    {
        string dir = implode(explode(file_name(this_object()), "/")[..-2], "/");
        path = FPATH(dir, path);
    }

    setuid();
    seteuid(getuid());

    // The building provides its own set of ids
    dest_id = path->query_location_ids();

    // Add an exit to the building if it's open
    if (!(m = path->query_location_closed()))
    {
        add_exit(path, "enter", dest_id ? &check_exit_dest(dest_id) : 0, 0, 1);
    }
    // Otherwise, if the building is closed, we add an exit as long as a
    // closure message has been specified.  If there isn't one, we don't
    // bother with an exit at all.
    else if (stringp(m))
    {
        add_exit(path, "enter", &check_exit_dest(dest_id, m), 0, 1);
    }

    // Add a description of the building, if it has one
    if (m = path->query_location_desc())
    {
        add_item(dest_id, m);
    }

    path->add_building_exit(this_object());
}


/*
 * Function name:        add_street_items
 * Description  :        call this function to add the items which
 *                       should be visible from the streets of
 *                       Telberin to a room
 */
public void
add_street_items()
{
    try_item( ({ "palace gates", "gates of the palace" }),
        "The gates of the palace are located within the Royal Circle,"
      + " at the heart of Telberin.\n");
    try_item( ({ "clock", "clock tower", "great clock tower",
                 "clock tower of telberin",
                 "great clock tower of telberin" }),
        "A great clock tower rises from Scholars Plaza in the"
      + " Science Quarter of the city. Though elves see little value"
      + " in recording time, this has stood for many years as a"
      + " monument to the ways of the Scholars Guild of Telberin,"
      + " who, above all things, value order and measure.\n" +
        "The clock shows: " + EMERALD_EXACT_TIME_STRING_VBFC + ".\n");
    try_item( ({ "stone", "stones", "cobblestone", "cobblestones" }),
        "The streets are paved with cobblestones which have been"
      + " worn and rounded in places by the frequent traffic.\n");
    try_item( ({ "garden", "gardens" }),
        "Telberin boasts a number of prominant gardens. The Royal"
      + " Fruit Garden is southwest of the Palace, and the Royal"
      + " Magic Garden is to its northeast.\n");
    try_item( ({ "fruit garden", "fruit gardens", "royal fruit garden",
                 "royal fruit gardens" }),
        "The Royal Fruit Garden is one of the professionally tended"
      + " nature sanctuaries within the City. It is reknown for its"
      + " incredible variety of flora and fauna as well as for its"
      + " tremendous scents which are known to waft into neighboring"
      + " zones of the city.\n");
    try_item( ({ "magic garden", "magic gardens", "royal magic garden",
                 "royal magic gardens" }),
        "The Royal Magic Garden is a rather mysterious part of the"
      + " city. It is kept and tended by professionals who keep up"
      + " a number of tended gardens near the Palace. The nature"
      + " behind the plants within are known only to its keepers.\n");
    try_item( ({ "wall", "walls", "walls of the city", "city walls",
                 "wall of the city", "city wall", "walls of telberin",
                 "wall of telberin", "walls which surround the city",
                 "great wall", "great walls" }),
        "Great walls surround the city of Telberin. They were built"
      + " many centuries ago, before most of the buildings which now"
      + " stand. Tales tell that certain sections of the wall are"
      + " actually remnants of the wall which protected the ancient"
      + " city of Telberin which was destroyed long ago, before the"
      + " memories of most elves who now live within the city.\n");
    try_item( ({ "cantors plaza", "cantor plaza" }),
        "Cantors Way opens onto a wide plaza at the tip of its"
      + " eastern loop where many of the major establishments"
      + " within the Arts Quarter can be found.\n");
    try_item( ({ "artisans plaza", "artisan plaza" }),
        "Artisans Plaza is on the far western end of the City, just"
      + " before the Main Gate. It is a hub for all kinds of"
      + " trade and merchandise within Telberin.\n");
    try_item( ({ "channelers plaza", "channeler plaza" }),
        "At the southern end of the city, Channelers Way opens onto"
      + " a wide plaza where various establishments of arcanum can"
      + " be found.\n");
    try_item( ({ "scholars plaza", "scholar plaza" }),
        "Scholars Plaza is located at the northern end of the"
      + " city where Scholars Way bends in a wide loop on its"
      + " journey to and from the Royal Circle.\n");
    try_item( ({ "city", "telberin", "telberin city",
                 "city of telberin", "town", "area" }),
        "Telberin, the jewel of Emerald, is an extremely beautiful"
      + " city despite the damage it has sustained by recent raids."
      + " Great artistry has been put into the architecture of nearly"
      + " every building, large and small. This is most stunningly"
      + " evident in the buildings which rise from the Royal Circle"
      + " at the center of town. Vaulting above them all is the"
      + " magnificent Royal Palace, which rises almost impossibly"
      + " high above the city streets. The main avenues of the city"
      + " travel in long petal-shaped ellipses from the Royal Circle,"
      + " north, south, east, and west. Within each boulevard runs"
      + " a dramatic reflecting pool which extends the long length"
      + " of each quarter of the Telberin.\n");
    try_item( ({ "royal circle", "circle", "center of town",
                 "city center", "center of the city",
                 "center of telberin", "royal circle of telberin" }),
        "The Royal Circle is the main thoroughfare of Telberin,"
      + " travelling in a wide lane around the Royal Palace. The"
      + " outside of the circle is framed by three tall structures"
      + " which rise prominantly into view beneath the tall spires"
      + " of the Palace - the Temple, the Tower of Telan-Ri, and"
      + " the Fortress of the Protectorate. The four main boulevards"
      + " of the city run north, south, east and west from the circle,"
      + " travelling the length of their respective quarters.\n");
    try_item( ({ "palace", "royal palace", "palace of telberin" }),
        "Even from a distance, the Royal Palace of Telberin is a"
      + " marvel to behold. Striking upward from the Royal Circle"
      + " like a vast pearlescent stalagmite, its turrets and"
      + " spires travel upward to a perfect point high above the"
      + " city. It positively glows with light.\n");
    try_item( ({ "turret", "spire", "turrets", "spires",
                 "turrets and spires", "spires and turrets" }),
        "The turrets and spires of the Royal Palace extend impossibly"
      + " high above the rest of the Royal Circle, reaching a perfect"
      + " point at the top.\n");
    try_item( ({ "perfect point", "point" }),
        "The spires and turrets of the city rise to a singular point"
      + " directly above the palace. The top of the point glistens and"
      + " sparkles with a radiant light, almost as if some great light-"
      + "catching jewel were placed there.\n");
    try_item( ({ "temple", "temple of telberin", "great temple" }),
        "The Temple of Telberin is visible rising above the Royal"
      + " Circle with its vast framework of pillars and stone. It,"
      + " unlike other buildings in the city center, seems broad"
      + " rather than lofty. Perhaps this is to accomodate the many"
      + " worshippers who gather there regularly.\n");
    try_item( ({ "tower", "towers" }),
        "There are numerous towers in the city. Most notable are the"
      + " Tower of Telan-Ri within the Royal Circle, and the Mage Guild"
      + " of Telberin which rises at the southern end of the Magic"
      + " Quarter.\n");
    try_item( ({ "guild", "magic guild", "guild tower",
                 "magic guild tower", "magic guild of telberin" }),
        "Tall, straight, and unadorned, the Magic Guild of Telberin"
      + " rises from the southern portion of the city completely alone"
      + " in its heights.\n");
    try_item( ({ "tower of telan-ri", "tower of telan ri", 
                 "order of telan-ri", "order of telan ri" }),
        "The Order of Telan-Ri is housed within a vast tower directly"
      + " to the south of the Royal Palace. This structure is unique"
      + " in the city, with myriad towers and pinnacles branching as"
      + " tree limbs might from the main base of the tower. There is"
      + " an odd glow to the structure, as if it pulses with magical"
      + " energy.\n");
    try_item( ({ "fortress", "fortress of the protectorate",
                 "fortress of the protectorate of telberin",
                 "protectorate of telberin" }),
        "The Keepers of Telberin base their operations in a great"
      + " structure rising west of the Royal Palace. This structure"
      + ", the Fortress of the Protectorate, is not as elegant as the others, but looks mighty indeed."
      + " Its sides are sloped and walled with great stones which"
      + " rise to support the main vault of the building.\n");
    try_item( ({ "streets", "city streets", "avenues", "main avenues",
                 "boulevards", "boulevard", "street", "city street",
                 "avenue", "main avenue", "ellipse", "main ellipse",
                 "road", "roads", "roadway" }),
        "The streets of the city have been arranged in the form"
      + " of a symmetrical cross. Each point of the cross leads"
      + " into one of the four quarters of the city as a boulevard"
      + " in the shape of a long ellipse. Scholars Way runs north,"
      + " Cantors Way runs east, Channelers Way runs south, and"
      + " Artisans Way runs east. All have their beginning and end"
      + " at the corners of the Royal Circle, an avenue which rings"
      + " the Palace itself.\n");
    try_item( ({ "scholars way" }),
        "Scholars Way, one of four main boulevards in the city, runs"
      + " to the north of the Royal Circle. It travels the length of"
      + " the Science Quarter on each side of a long reflecting pool."
      + " At its northern point it opens into a wide plaza.\n");
    try_item( ({ "cantors way" }),
        "Cantors Way, one of four main boulevards in the city, runs"
      + " to the east of the Royal Circle. It travels the length of"
      + " the Arts Quarter on each side of a long reflecting pool."
      + " At its eastern point it opens into a wide plaza.\n");
    try_item( ({ "channelers way" }),
        "Channelers Way, one of four main boulevards in the city, runs"
      + " to the south of the Royal Circle. It travels the length of"
      + " the Magic Quarter on each side of a long reflecting pool."
      + " At its southern point it opens into a wide plaza.\n");
    try_item( ({ "artisans way" }),
        "Artisans Way, one of four main boulevards in the city, runs"
      + " to the west of the Royal Circle. It travels the length of"
      + " the Mercantile Quarter on each side of a long reflecting pool."
      + " At its western point it opens into a wide plaza.\n");
    try_item( ({ "quarter", "quarters" }),
        "The city is divided into four quarters, each devoted to its"
      + " own order of business. The Science Quarter makes up the"
      + " northern portion of the city. The Arts Quarter resides in"
      + " the east. The Mercantile Quarter is to the west. And the"
      + " southern portion of the city is dominated by the Magic"
      + " Quarter.\n");
    try_item( ({ "science quarter" }),
        "The Science Quarter makes up the northern portion of Telberin."
      + " It is dedicated to the persuit of knowledge and understanding"
      + " of the laws of nature, and contains many of the great"
      + " thinkers, and groups of scholars within the city.\n");
    try_item( ({ "arts quarter", "art quarter" }),
        "The Arts Quarter makes up the eastern portion of Telberin."
      + " Among its denizens are the great painters, poets, actors"
      + " and musicians in the city.\n");
    try_item( ({ "magic quarter" }),
        "The Magic Quarter makes up the southern portion of Telberin."
      + " It is typically not considered a very sociable area of the"
      + " city due to its strong focus on arcanum, and the magical"
      + " arts. Its populace are very reserved, and do not share"
      + " their knowledge lightly.\n");
    try_item( ({ "mercantile quarter" }),
        "The Mercantile Quarter makes up the western portion of Telberin."
      + " Here one can find skilled craftsman of all sorts, eager to"
      + " trade in their wares or offer their services to paying"
      + " customers. It is widely regarded as the most friendly and"
      + " hospitable portion of the city.\n");
    try_item( ({ "repair", "repairs", "repair work", "damage",
                 "damaged building", "damaged buildings",
                 "damaged street", "damaged streets", "destruction",
                 "raid", "raids", "recent raid", "recent raids" }),
        "Recent raids upon the city have caused heavy damage to certain"
      + " sectors of town. In particular, the northwest and"
      + " the southeastern quadrants have sustained great damage, causing the"
      + " bordering roads to be closed off for repair work. All over"
      + " the city, damaged streets and buildings are being restored"
      + " to their prior functionality.\n");
    try_item( ({ "light", "illumination", "radiance" }),
        "The entire city of Telberin seems filled with light. The"
      + " effect is one in which everything is clearly visible, and"
      + " there are few if any shadows.\n");
    try_item( ({ "shadow", "shade", "shadows" }),
        "Remarkably, there are no shadows to be found here.\n");
    try_item( ({ "pool", "water", "reflecting pool", "long pool",
                 "long reflecting pool", "pool of water" }),
        "At the center of each main boulevard is a long pool of clear"
      + " blue water, extending from the edge of the Royal Circle"
      + " towards a plaza at the end of each quarter of the city."
      + " These reflecting pools are very beautiful, and add to the"
      + " serenity of travel within Telberin.\n");
    try_item( ({ "lawn", "green lawn", "grass", "bright lawn",
                 "bright green lawn" }),
        "A green lawn separates the streets from the reflecting pools"
      + " at their center. The grass blows now and again in the fresh"
      + " breeze.\n");
    try_item( ({ "architecture", "architectural style", "style",
                 "building", "buildings", "structure", "structures" }),
        "The buildings within the city seem to follow a similar"
      + " aesthetic in their architectural style. There is an emphasis"
      + " on drawing the eye upward along curved lines.\n");
    try_item( ({ "gate", "west gate", "western gate", "city gate",
                 "gates", "gates of the city", "main gate",
                 "western gates of the city", "main gates",
                 "gates of telberin", "western gates of telberin" }),
        "The main gates of the city rise along the western edge"
      + " of Artisans Way in the Mercantile Quarter. They lead out"
      + " of Telberin toward the docks.\n");
    try_item( ({ "dock", "docks" }),
        "The docks of Telberin are not visible from within the City,"
      + " though it is well known that they lie just outside of the"
      + " city gates.\n");
    try_item( ({ "plaza", "plazas", "wide plaza" }),
        "Each of the four main boulevards of the city opens into a"
      + " wide plaza at its extremety. It is often in these plazas"
      + " that the greatest concentration of activity for that"
      + " quarter of the city takes place.\n");
} /* add_street_items */

public int
exit_move(string cmd, object room)
{
    string how;

    if (strlen(how = room->query_entry_desc()))
    {
        return this_player()->move_living(how, room);
    }
    else
    {
        return ::exit_move(cmd, room);
    }
}
