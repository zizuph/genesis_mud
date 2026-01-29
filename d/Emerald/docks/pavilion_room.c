#include "defs.h"

inherit PAV_PATH_ROOM;

#include <subloc.h>
#include <filter_funs.h>
#include <stdproperties.h>
#include <composite.h>
#include <macros.h>

#define COUNTER_SUBL "_counter"

void
create_pav_room()
{
}

public string
desc_pav_areas()
{
    return "At the center of the pavilion lies the information and " +
        "ticketing counter, while a small pub and post office can be " +
        "found at the northern end.";
}

nomask void
create_pavpath_room()
{
    string str;

    set_short("Ceral Island Pavilion");
    set_em_long("The large tent pavilion serves as a tourist information " +
        "center and waiting area for passengers, particularly welcome in " +
        "inclement weather.  " + desc_pav_areas() + "\n");

    remove_item("pavilion");
    add_item(({ "tent", "pavilion", "pavilion tent" }),
        "The large tent is supported by a number of immense wood poles " +
        "jutting up from the stone floor.  The tent would not fare well " +
        "in a violent storm, but it seems to be fitted to be easily " +
        "dismantled with little warning or easily replaced in the event " +
        "of unexpected gusts.\n");

    add_item(({ "pole", "poles", "wooden pole", "wooden poles" }),
        "Each wooden pole is about a meter in diameter and rises about " +
        "eight meters high to the top of the tent.  It's hard to " +
        "guess how deeply they may be buried.\n");

    add_item(({ "floor", "stone floor", "slabs", "granite slabs", "ground", }),
        "The floor is laid with wide granite slabs.  A number of huge " +
        "wooden poles poke up from the floor, supporting the tent.\n");

    add_item(({ "sides", "tent sides", "sides of tent", "sides of the tent",
                "side", "tent side", "pavilion side", "side of pavilion",
                "sides of the pavilion", "wall", "walls", "pavilion wall",
                "pavilion walls", "tent wall", "tent walls" }),
        "The walls of the pavilion look to be made from the same heavy, " +
        "sturdy material as the top is.  Four openings along the sides " +
        "provide access from outside.\n");

    add_item(({ "top", "ceiling", "roof", "top of tent", "top of the tent",
                "top of pavilion", "top of the pavilion" }),
        "The ceiling of the pavilion appears to be some sort of sturdy, " +
        "elastic material coloured in brilliant gold.\n");

    add_item(({ "material", "elastic material", "sturdy elastic material",
                "thick material", "thick elastic material" }),
        "The ceiling and walls of the pavilion appear to be made of the " +
        "same thick, elastic material.\n");
        
    add_item(({ "waiting area" }),
        "The whole tent serves as a waiting area and information center. " +
        "While not comfortably furnished, the pavilion would certainly " +
        "be welcome shelter in stormy weather.\n");

    add_item(({ "pub", "small pub" }), (PUB_OPEN ? 
        "The tiny pub is barely more than a collection of a few tables " +
        "at the northern edge of the pavilion.\n" :
        "The tiny pub is barely more than a collection of a few tables " +
        "at the northern edge of the pavilion.  It appears to be closed " +
        "at the moment.\n"));

    add_item(({ "table", "tables", "small tables", "collection of tables" }),
        (PUB_OPEN ? "A few small tables are set out at the northern side " +
        "of the pavilion where travellers can rest and order drinks or a " +
        "quick meal.\n" :
        "A few small tables are set out at the northern side of the " +
        "pavilion where travellers can rest and order drinks or a quick " +
        "meal.  Currently, though, there doesn't appear to be any service, " +
        "and the chairs have been removed from the tables.\n"));       

    add_item(({ "post", "office", "post office", "postal area" }),
        "A small area is set aside to the left of the north entrance where " +
        "travellers can use the postal services.\n");

    str = "A small walkway leads up to the pavilion at the %s entrance, " +
      "providing access from the docks along Ceral Island's shore.";

    add_item(({ "north entrance", "northern entrance", "north exit",
                "northern exit" }),
        sprintf(str, "northern") + "  Just to the left of the entrance an " +
        "area has been set aside where travellers can send and receive " +
        "mail, and just across from it, on the other side of the entrance, " +
        "a few tables are set out.\n");

    add_item(({ "west entrance", "western entrance", "west exit",
                "western exit" }), sprintf(str, "western"));
 
    add_item(({ "east entrance", "eastern entrance", "east exit",
                "eastern exit" }), sprintf(str, "eastern"));
 
    add_item(({ "south entrance", "southern entrance", "south exit",
                "southern exit" }), sprintf(str, "southern"));

    add_item(({ "exits", "entrances", }),  "Four openings in in the sides " +
        "of the pavilion tent provide access from outside.\n");

    add_item(({ "walkway", "walkways", "path", "paths" }),
        "Four walkways lead in from the docks on the shore to the pavilion " +
        "area.\n");

    add_item(({ "pavilion area" }), query_long());

    add_prop(ROOM_I_INSIDE, 1);
    add_prop("_room_i_sunlight", 1);

    create_pav_room();
}

public void
add_information_desk()
{
    string sign, *lines;
    int i, price;

    add_item(({ "information center", "information counter", "counter",
        "information desk", "desk", }),
        "A small area at the center of the pavilion is enclosed by a " +
        "four-sided counter.  A large sign above the area reads " +
        "\"INFORMATION\".\n");
 
    sign = "A large sign hangs above the information center.  It reads\n" +
        "\t\tINFORMATION\n\n" +
        sprintf("\t%-25s %-10s\n", "Shipline", "Cost (cc)") +
        "\t====================================\n";

    lines = SHIP_MGR->query_shiplines();
    for (i = 0; i < sizeof(lines); i++)
    {
        price = SHIP_MGR->query_price(lines[i]);
        sign += sprintf("\t%-25s %-10s\n",
            lines[i], ((price < 1) ? "Free" : "" + price));
    }

#if !AGENT_PRESENT
    sign += "\nA notice as been tacked onto the sign.  It reads:  The " +
        "Travel Bureau has temporarily suspended service at Ceral Island.  " +
        "Please see your ship captain for ticketing.  Thank you.\n";
#endif

    add_item(({ "sign", "large sign", "information sign" }), sign);
    add_cmd_item(({ "sign", "large sign", "information sign" }), "read", sign);

    add_subloc(COUNTER_SUBL, this_object());
}

public string
query_counter_subloc()
{
    return COUNTER_SUBL;
}

public string
show_subloc(string subloc, object ob, object for_obj)
{
    object *livings = FILTER_LIVE(subinventory(subloc));

    if (sizeof(livings))
    {
        return capitalize(COMPOSITE_LIVE(livings)) +
            ((sizeof(livings) == 1) ? " is " : " are ") + "behind the " +
            "information counter.\n";
    }

    return "";
}

public mixed
subloc_access(string subloc, object ob, string access, object for_obj)
{
    if (access == SUBLOC_ACCESS_MANIP)
    {
        return "You can't reach across the counter.\n";
    }

    return 1;
}

void
over_counter()
{
    if (this_player()->query_subloc() == COUNTER_SUBL)
    {
        this_player()->move(this_object());
    }
    else
    {
        this_player()->move(this_object(), COUNTER_SUBL);
    }
 
    write("You climb over the counter.\n");
    say(QCTNAME(this_player()) + " climbs over the counter.\n");
}

int
climb_counter(string str)
{
    // First, check to see that we actually have a counter here!
    if (member_array(COUNTER_SUBL, query_sublocs()) < 0)
    {
        return 0;
    }

    if (!strlen(str))
    {
        return 0;
    }

    if (parse_command(str, ({}),
        "[over] [behind] [the] [information] 'counter' / 'desk'"))
    {
        over_counter();
        return 1;
    }

    notify_fail(capitalize(query_verb()) + " where?\n");
    return 0;
}

int
climb(string str)
{
    if (!strlen(str))
    {
        return 0;
    }

    if (parse_command(str, ({}),
        "[up] [the] [a] [huge] [immense] [wooden] 'pole' / 'poles'"))
    {
        write("It is too difficult to get a grip.\n");
        return 1;
    }

    return climb_counter(str);
}

void
init()
{
    ::init();
    add_action(climb, "climb");

    if (member_array(COUNTER_SUBL, query_sublocs()) >= 0)
    {
        add_action(climb_counter, "jump");
        add_action(climb_counter, "go");
        add_action(climb_counter, "move");
    }
}

public int
query_pavilion_room()
{
    return 1;
}
