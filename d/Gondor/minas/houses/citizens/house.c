/*
 * Standard house room for Minas Tirith, version II
 *
 * June 1995 by Sir Denbarra of Gondor
 *
 * Based upon /d/Gondor/minas/sewer/sewer.c by Honourable Olorin of Gondor
 *
 * Modification log:
 *	- Replaced VBFC by function calls where VBFC are not necessary
 *	  Olorin, 18-Jun-1995
 */

inherit "/d/Gondor/common/room";

#include <stdproperties.h>
#include <macros.h>
#include <ss_types.h>
#include <composite.h>

#include "/d/Gondor/defs.h"

/*
 *	Prototypes
 */
varargs void    ceiling(string ceiling_extra_desc);
varargs void    floor(string floor_extra_desc);
varargs void    walls(string wall_extra_desc);

// Global variables
static string  side,
               circle,
               short_desc;
// wealth and activity should correspond to the circle which adjoins
//   the house!
static int     wealth,
               activity;

object  clock = CLOCK;

void    set_circle(string s) { circle = s; }

void    set_activity(int i) { activity = i; }

int     set_wealth(int i) { wealth = i; }

int     query_wealth(int i) { return wealth; }

int
set_side(string str)
{
    if(!strlen(str))
        return 0;
    side = str;
    return 1;
}

string query_side() { return side; }

void
add_window(string desc)
{
    if (item_id("window"))
        return;
    add_item(({"window"}), "@@window|"+desc+"@@");
}

varargs string 
window(string window_extra_desc)
{
    string time, moon, desc;
    int activity;

    time = clock->query_time_of_day();
    moon = clock->query_moon();

    desc = "You look out the ";
    switch(wealth)
    {
        case 0:
            desc += "small window, straining to see through the " +
                "murky glass. ";
            break;
        case 1:
            desc += "window, squinting past the slight distortion " +
                "in the imperfect glass. ";
            break;
        case 2:
            desc += "large window and through the clear glass. ";
            break;
    }

    desc += "You see that it is "+time+". ";
    switch(time)
    {
        case "night":
            switch(moon)
            {
                case "dark":
                    desc += "The night air is cool, and the sky " +
                        "is clear and full of stars. ";
                    break;
                case "full":
                    desc += "The full moon is shining amid the " +
                        "brilliant stars. ";
                    break;
                case "waxing crescent":
                case "waning crescent":
                    desc += "The moon is a thin crescent ringed " +
                        "amid a halo of shining stars. ";
                    break;
                case "waxing gibbous":
                case "waning gibbous":
                    desc += "The moon is gibbous, a bulging " +
                        "semicircle suspended amid glowing stars. ";
                    break;
            }
            break;
        case "early morning":
            desc += "There is a light which struggles to get " +
                "around the perpetual darkness of the eastern sky. ";
            break;
        case "morning":
            desc += "The sun has finally risen over the Shadow " +
                "in the East, giving light to a new day. ";
            break;
        case "noon":
        case "afternoon":
            desc += "The sun hangs high in the sky, showering " +
                "the Gondorian day with light. ";
            break;
        case "evening":
            desc += "The sun has begun to sink in the West, " +
                "lending fearsome strength to the Shadows in the " +
                "East. ";
            break;
    }

    desc += "Looking down upon the street, you see the "+side+
        " of the "+circle+". ";
    switch(activity)
    {
        case 0:
            desc += "There is little activity on the street. You " +
                "hear the distant sounds of household activity " +
                "echoing in the street. ";
            break;
        case 1:
            desc += "You see some people coming and going in the " +
                "street, entering and leaving the buildings and making " +
                "their ways about Minas Tirith. ";
            break;
        case 2:
            desc += "A great crowd of people surges in the street. " +
                "You are amazed that such a crowd exists in this " +
                "partially-evacuated city. There must be a market " +
                "nearby. ";
            break;
    }

    desc += window_extra_desc;

    return (desc);
}

varargs void
add_walls(string desc = "")
{
    if (item_id("wall"))
        return;
    // there is no reason to use VBFC here!
    add_item(({"wall","walls"}), walls(desc));
}

varargs string 
walls(string wall_extra_desc = "")
{
    string  desc;

    desc = "You examine the walls carefully. ";
    switch(wealth)
    {
        case 0:
            desc += "They are built of rough-hewn stone cut from " +
                "the hill of Minas Tirith. The stone has " +
                "been rudely worked and poorly put together. " +
                "There is but a crumbling mortar holding " +
                "this stonework together.";
        break;
        case 1:
            desc += "They are most impressive. The lower " +
                "half of the walls are cut from the living " +
                "stone of the hill, so that the walls would " +
                "not have to be built so high and would have " +
                "a firmer foundation. The upper half of the " +
                "walls is free-standing, allowing for windows " +
                "to be easily built.";
        break;
        case 2:
            desc += "They look very sturdy and fine. The " +
                "walls appear at first to have been made " +
                "of wood, but you soon realize that the " +
                "wood covers fine-hewn stone in order to " +
                "insulate the house and present a fine " +
                "appearance.";
        break;
    }

    if (strlen(wall_extra_desc))
        desc += (" " + wall_extra_desc);

    return desc;
}

varargs void
add_ceiling(string desc = "")
{
    if (item_id("ceiling"))
        return;
    // there is no reason to use VBFC here!
    add_item(({"ceiling"}), ceiling(desc));
}

varargs string 
ceiling(string ceiling_extra_desc = "")
{
    string  desc;

    desc = "You tilt your head back and examine the ceiling. ";
    switch(wealth)
    {
        case 0:
            desc += "You see that the ceiling is made of a " +
                "solid-looking but coarse wood. The wooden " +
                "beams and the cracks between them are coated " +
                "with pitch to keep moisture out.";
        break;
        case 1:
            desc += "It seems to be stone supported by wooden " +
                "beams. The beams look to be oak and are very " +
                "thick. The stonework is rough but functional.";
        break;
        case 2:
            desc += "It is composed of very impressive dressed stone " +
                "supported by magnificent arches. The ceilings are " +
                "vaulted and the doorways are arched.";
        break;
    }

    if (strlen(ceiling_extra_desc))
        desc += (" " + ceiling_extra_desc);

    return (desc);
}

varargs void
add_floor(string desc = "")
{
    if (item_id("floor"))
        return;
    add_item(({"floor","floors"}), floor(desc));
}

varargs string 
floor(string floor_extra_desc = "")
{
    string  desc;

    desc = "You look down at the floors. ";
    switch(wealth)
    {
        case 0:
            desc += "They are made of wooden planks laid over " +
                "the first of the ground. The planks have old " +
                "pitch between then to keep moisture and " +
                "creatures out.";
            break;
        case 1:
            desc += "It is the bare, undressed stone of the " +
                "hill upon which the city rests. The stone " +
                "was crudely levelled, leaving some irregularities " +
                "and depressions in the floor. However, time and " +
                "the passage of many feet have served to work " +
                "the floor down to a mostly level surface.";
            break;
        case 2:
            desc += "It is the stone of the hill which Minas " +
                "Tirith is carved from. It is living stone, " +
                "but it has been beautifully worked into a " +
                "tile pattern on the floor. The surface is " +
                "smooth and almost perfectly level.";
            break;
    }

    if (strlen(floor_extra_desc))
        desc += (" " + floor_extra_desc);

    return (desc);
}

void
add_lamp()
{
    object  lamp;

    lamp = clone_object(OBJ_DIR + "oil_lamp");
    switch(wealth)
    {
        case 0:
            lamp->remove_object();
            break;
        case 1:
            lamp->set_long(BSN("It is an iron oil-lamp. It is a " +
                "very nice lamp with a wick behind a curved " +
                "glass bulb. It seems to be completely filled " +
                "with lamp oil. It is bolted to the wall."));
            break;
        case 2:
            lamp->remove_adj("iron");
            lamp->add_adj("brass");
            lamp->set_short("brass oil-lamp");
            lamp->set_pshort("brass oil-lamps"); /* Should never happen */
            lamp->set_long(BSN("It is a brass oil-lamp. It is a " +
                "ornately crafted lamp, with floral patterns " +
                "carved into the metal. It has a wick behind " +
                "a curved glass bulb. It seems to be completely " +
                "filled with lamp oil. It is bolted to the wall."));
            break;
    }
    lamp->set_time(9999999);
    lamp->set_time_left(9999999);
    lamp->remove_action("do_keep");
    lamp->light_me();
    lamp->add_prop(OBJ_I_WEIGHT, 400);
    lamp->add_prop(OBJ_I_VOLUME, 800);
    lamp->add_prop(OBJ_I_VALUE,  800);
    lamp->add_prop(OBJ_M_NO_GET, VBFC_ME("lamp_get"));
    lamp->move(TO);
}

string
lamp_get()
{
    say(QCTNAME(TP) + " tries to get the lamp, but soon finds that " +
        "it is securely bolted to the wall.\n");
    return BSN(
        "You grab the lamp, which is bolted to the wall, and pull " +
        "with all your might, but the bolts which secure it to the " +
        "wall are too sturdy for you.");
}
