/*
 * /d/Gondor/common/guild2/tower/tower_6c.c
 * The central room on the sixth floor of the Morgul Tower
 *
 * Olorin, 10-jan-1994
 * 
 * Morbeche, Feb 2000 - Added a full mage board, added the ability
 *                      to look at a few rooms in the nearby area
 *                      and see who is around.
 *
 * Toby, Oct 2007: Opened up the roof entrance.
 * Toby, Oct 2007: Fixed a typo in the ceiling desc.
 * Toby, Jun 2008: Fixed open hatch description a bit.
 * Eowul, 08-Okt-2008: Removed some of the descriptions due to the long
 *                     delay in movement.
 */

#pragma save_binary

inherit "/d/Gondor/morgul/tower/tower.c";

#include <stdproperties.h>
#include <macros.h>
#include <filter_funs.h>
#include <composite.h>
#include "/d/Gondor/defs.h"
#include "/d/Gondor/morgul/tower/tower_defs.h"
#include "/d/Gondor/common/guild2/lib/morgul_defs.h"

#define MORGUL_AS_DIRS      ({"southwest", "west",  "northwest", "north", \
                              "northeast", "north", "northwest", "west", })

/* These are for viewing the surrounding area */
#define TOWER_ENTRANCE  ("/d/Gondor/morgul/city/mmr3")
#define INNER_GATE      ("/d/Gondor/morgul/city/i_ngate")
#define OUTER_GATE      ("/d/Gondor/morgul/city/o_ngate")
#define CROSSROADS      ("/d/Gondor/ithilien/road/crossroads")

/* Prototypes */
public string	exa_down(string desc, string street_file);
void		preload_files();

void create_morgul_tower_room()
{
    object board;

    set_level(6);
    set_room_type("round room");
    set_extra_long(
      "In the middle of the room a large pillar rises to the roof. " +
      "The staircase is leading down, winding its way around the pillar. " +
      "The walls and the floor of the room slowly revolve around the " +
      "pillar, first one way, and after a few moments the other. " +
      "An evil, strangely pale glow fills the room, shining out of " +
      "the single window of the room.");

    add_item(({"wall", "walls", "ground", "floor"}), 
    "Like everywhere else in this tower, the walls and floor of this " +
    "room are made from dark black smoothly polished stones. But unlike " +
    "on the lower levels, these stones seem to emit an evil, strangely " +
    "pale light that fills the room. And very strangely, the walls and " +
    "the floor seem to revolve around the pillar in the centre of the " +
    "room.\n");

    add_item(({"roof", "ceiling"}), 
    "The roof is made from the same black stones as the floor and the " +
    "walls, though those do not emit the strange light. Faintly outlined " +
    "in the center near where the spiral staircase ends there is an outline " +
    "resembling a hatch.\n");

    add_item(({"hatch", "outline"}), 
    "The outline in the ceiling is indeed a hatch, perfectly fit with no " + 
    "apparent mean to open it.\n");

    add_item(({"pillar", "column", "staircase", "spiral staircase", "stairs",
    "stairways"}), 
    "A large round pillar rises in the centre of the room. Around this " +
    "pillar the room seems to revolve, and around this pillar the " +
    "spiral stairways wind their way to the level below.  "+
    "Leaning out the window you could look down to the entrance " +
    "of the Tower, or at the inner or outer gate, or to " +
    "the crossroads far to the north.  "+
    "A raven sits on the window ledge, looking around intently.\n");

    add_item(({"raven","black raven"}),
    "A black raven sits on the window ledge, quietly observing "+
    "the surrounding area.  Strangely, you cannot remember " +
    "a time when the raven has been absent.\n");
    add_item(({"glow", "light"}), BSN(
    "An evil strangely pale glow is emitted by the floor and the walls " +
    "of the room. This light is shining out through the single window, " +
    "throwing the pale glow over the Imlad Morgul."));

    add_item(({"window","imlad morgul","valley","morgul vale"}), "@@exa_window@@");

    add_item(({"down","ground","entrance"}),"@@exa_down|" +
      "Looking almost straight down you can see the "+
      "entrance to the Dark Tower.  |"+
      TOWER_ENTRANCE+"@@");

    add_item(({"inner gate"}),"@@exa_down|" +
      "Looking to the north you can see "+
      "inside the gates of His dreaded city.  |"+
      INNER_GATE+"@@");

    add_item(({"outer gate"}),"@@exa_down|" +
      "Looking to the north you can see "+
      "just beyond the gates of the Dark City.  |"+
      OUTER_GATE+"@@");

    add_item(({"crossroads"}),"@@exa_down|" +
      "Looking far to the north you see the "+
      "crossroads outside of Minas Morgul.  |"+
      CROSSROADS+"@@");

    add_exit(MAGES_DIR  + "tower/tower_5c", "down",  0, 4);

    add_prop(ROOM_I_LIGHT, 1);
    preload_files();
}

void
preload_files()
{
    INNER_GATE->teleledninganka();
    OUTER_GATE->teleledninganka();
    CROSSROADS->teleledninganka();
    TOWER_ENTRANCE->teleledninganka();
}

/* This is modified from /d/Gondor/elessar/lib/time.c */

int check_time(string str)
{
    int     hour, day, month, year;
    string  time, shour;
    object  clock;

    clock = find_object(CLOCK);
    time = (string)clock->query_time_of_day();
    hour = (int)clock->query_hour();
    if (hour == 12)
    shour = "noon";
    else if (hour == 0)
    shour = "midnight";
    else
    {
    if (hour > 12)
        hour -= 12;
    shour = hour + " o'clock in the " + time;
    }
    day = (int)clock->query_day();
    month = (int)clock->query_month();
    year = (int)clock->query_year();
    write(BSN("You look through the window and think that it is about "+
    shour+" of day "+day+", month "+ month+" in the year "+year+"."));
    say(QCTNAME(TP)+" looks through the window, trying to decide "+
      "what time it is.\n",TP);
    return 1;
}

public string
exa_down(string desc, string street_file)
{
    object  street = find_object(street_file),
    *people;

    people = FILTER_LIVE(all_inventory(street));
    if (!CAN_SEE_IN_OTHER_ROOM(TP,street_file))
    {
    desc += " It is too dark to see anything in that area.";
    return 0;
    }
    if (sizeof(people))
    desc += " You can see " + COMPOSITE_LIVE(people)+
    " in the area.";
    else
    desc += " There is no one near that area.";

    return BSN(desc);
}                                                                              

string exa_window()
{
    string  time,
    desc,
    todtxt,
    dir;
    object clock;

    clock = find_object(CLOCK);
    todtxt = (string)clock->query_time_of_day();
    dir = MORGUL_AS_DIRS[(clock->query_minute())%sizeof(MORGUL_AS_DIRS)];

    desc = "Looking through the window, you see that it is pointing " +
    "towards the " + dir + " now. ";

    switch(todtxt)
    {
    case "early morning":
    case "morning":
    desc += "You know that the sun has risen already, as it is early "+
    "morning now, but you cannot see it because of the murky clouds "+
    "covering the sky. ";
    break;
    case "noon":
    case "afternoon":
    desc += "The sun is probably trying to break through the heavy "+
    "clouds of the sky, because there is not much light outside. ";
    break;
    case "evening":
    case "night":
    desc += "It is quite dark out there, neither stars nor the moon " +
    "shine through the clouds covering the sky. ";
    break;
    }
    switch(dir)
    {
    case "southwest":
    desc += "The window is overlooking the western parts of the Imlad " +
    "Morgul and the jagged slopes of the Ephel Duath rising south " +
    "of the valley. ";
    if (todtxt != "evening" && todtxt != "night")
        desc += "In the distance, you can make out the green hills and " +
        "fields of Ithilien that start spreading outside the vale " +
        "where the grey feet of the mountains end. Beyond the " +
        "tree tops the wide blue band of the Anduin stretches from " +
        "north to south. ";
    else
        desc += "In the darkness of night, you can make out only shadows. " +
        "But far in the distance, a pale grey band is visible. That " +
        "must be the Anduin. ";
    break;
    case "west":
    desc += "The window is overlooking the western parts of the Imlad " +
    "Morgul on both sides of the Morgulduin. ";
    if (todtxt != "evening" && todtxt != "night")
        desc += "On the north bank of the river, the Morgul road is running " +
        "westward. In the distance, you can make out the green hills and " +
        "fields of Ithilien that start spreading outside the vale " +
        "where the grey feet of the mountains end. Beyond the " +
        "tree tops the wide blue band of the Anduin stretches from " +
        "north to south. ";
    else
        desc += "In the darkness of night, you can make out only shadows. " +
        "But far in the distance, a pale grey band is visible. That " +
        "must be the Anduin. ";

    break;
    case "northwest":
    desc += "The window is overlooking the western parts of the Imlad " +
    "Morgul and the jagged slopes of the Ephel Duath north of it. ";
    if (todtxt != "evening" && todtxt != "night")
        desc += "On the north bank of the Morgulduin, the Morgul road is " +
        "running westwards to Ithilien from the white bridge on which " +
        "it crosses the river outside the Morgul Gate. ";
    else
        desc += "In the darkness of night, you can make out only shadows, " +
        "and the dark band of the Morgul road on the north bank of the " +
        "Morgulduin. ";
    break;
    case "north":
    desc += "The window is overlooking the northern walls of Minas Morgul " +
    "and the Imlad Morgul north of them. You can make out the Morgul " +
    "road runing down from the Morgul gate to the bridge crossing the " +
    "Morgulduin. On the other side of the river, steep rock cliffs are " +
    "rising high into the sky.";
    break;
    case "northeast":
    desc += "The window is overlooking Minas Morgul northeast of the Morgul " +
    "Tower. You can see the city walls and the small northeastern tower " +
    "where the north and east walls meet. On the streets, many orcs and " +
    "humans are running around. Beyond the walls, you see the steep rock " +
    "cliffs of the Ephel Duath rising. ";
    break;
    }
    return desc + "\n";
}

void
move_mage(object mage)
{
    mage->move_living("M", MAGES_DIR  + "tower/tower_7c", 1);
}

int
rasp_command(string str)
{
    /*  panta adj. -- open
     *  assa n. -- hole, mouth, perforation, opening (any form)
     */

    if (!strlen(str))
        return 0;

    str = lower_case(str);

    if (str != "panta assa")
        return 0;

    write("Feeling a sudden sense of power flowing through your " +
          "undead veins, you turn your gaze toward the ceiling " +
          "and rasp: Panta assa!\n");

    say(QCTNAME(this_player()) + " turns " + this_player()->query_possessive() + 
          " gaze toward the ceiling rasping: Panta assa!\n");

/*          
    set_alarm(1.0, 0.0, &tell_room(TO, "The air is utterly still.\n\n"));    

    set_alarm(3.0, 0.0, &tell_room(TO, "A heaviness descends upon the air " +
                        "with sudden force!\n\n"));

    set_alarm(5.0, 0.0, &tell_room(TO, "The air keeps pressing heavily against " +
                        "your undead body.\n\n"));
*/
    set_alarm(2.0, 0.0, &write("The hatch silently glides open and you ascend unto " +
          "the beastiary atop the roof of the Black Tower!\n\n"));
    set_alarm(2.0, 0.0, &say("A hatch in the ceiling silently glides open and " +
          QTNAME(this_player()) +" ascends unto the roof of the Black Tower!\n\n"));

    set_alarm(2.0, 0.0, &tell_room(MAGES_DIR  + "tower/tower_7c", 
          "Suddenly the hatch in the seemingly unmarred ebony black floor opens and " + 
          QTNAME(this_player()) + " ascends the spiral staircase from below entering " +
          "the beastiary of the Black Tower.\n"));

    TP->add_mana(-30);

    set_alarm(2.1, 0.0, &move_mage(TP) );

    set_alarm(2.6, 0.0, &tell_room(TO, "The hatch in the ceiling silently glides shut " +
          "and the air feels less heavy.\n"));

    return 1;
}

void
init()
{
    ::init();

    add_action(rasp_command, "rasp");
}
