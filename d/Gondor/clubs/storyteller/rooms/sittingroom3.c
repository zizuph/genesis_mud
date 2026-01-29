/*
 * /d/Gondor/clubs/storyteller/rooms/sittingroom3.c
 * Copyright, Rolf Braun a.k.a. Elessar. Genesis, 1998.
 *
 * This is the first room of the clubhouse, connected to
 * /d/Gondor/pelargir/street/nroad2.c
 */
inherit "/d/Gondor/std/room";
inherit "/d/Gondor/open/room_chairs/room_chairs";
inherit "/d/Gondor/open/fireplace/fireplace";

#include "/d/Gondor/defs.h"
#include "/d/Gondor/open/room_chairs/room_chairs.h"
#include "/d/Gondor/open/fireplace/fireplace.h"

#include <stdproperties.h>
#include <macros.h>

#define PILLOWS 5

public nomask string sitting_look(string arg);
public string fire_desc(string arg);

int gPilTaken = 0;

string
long_desc()
{
    return "A lush well appointed room that is very large and well " +
        "lit by brass lanterns hung from the walls. There is a large " +
        "stone fireplace at one end of the hall. There are three " +
        "large sofas, two overstuffed loveseats, and a large round " +
        "ottoman in the center of the room for the storyteller. There " +
        "are some large pillows laying around on the floor waiting to " +
        "be used. " + (gPilTaken < PILLOWS ? 
        "A few small pillows are scattered across the room as well." : "") +
        "\n" + fire_desc("light");
}

int
is_pillow(object ob)
{
    if (ob->id("_story_pillow"))
        return 1;

    return 0;
}

string
pillow_desc()
{
    int num;
    object *pillows;

    pillows = all_inventory(TO);
    pillows = filter(pillows, is_pillow);
    num = sizeof(pillows);
    if ((PILLOWS - gPilTaken + num) > 0)
        return "The outer covering of the small pillows are made of smooth " +
            "coloured satin. They are incredibly fluffy and soft, perfect for " +            
            "squeezing, cuddling, sleeping and even throwing! There are " +
            (PILLOWS - gPilTaken + num) + " pillows left.\n";
    else
        return "There aren't any pillows left.\n";
}

void
create_gondor()
{
    set_short("the grand hall");
    set_long(&long_desc());


    add_item(({"lantern", "lanterns", "brass lantern", "brass lanterns",}),
        "Brass lamps hung from the walls provide ust enough light for " +
        "the hall.\n");
    add_item(({"small pillow", "small pillows"}), &pillow_desc());
    add_item(({"pillow", "pillows", "large pillow", "large pillows",
        "soft pillow", "soft pillows", "large soft pillow", 
        "large soft pillows", }), "There are a number of pillows on the " +
        "floor that people listening to the storyteller can use to sit more " +
        "comfortably on the floor. You can sit on pillows near the " +
        "fireplace, near the loveseat, near the ottoman and near the sofa.\n");
    add_item(({"fireplace", "stone fireplace",}), &fire_desc("fireplace"));
    add_item(({"fire", "flames", "flame", "red flames", "gold flames",
        "red flame", "gold flame", }), &fire_desc("fire"));
    add_item(({"firelight", "light", "fire light", }), &fire_desc("light"));
    add_item(({"ash", "ashes", "ash in fireplace", "ashes in fireplace",
        "ash in stone fireplace", "ashes in stone fireplace",}),
        &fire_desc("ashes"));
    add_item(({"wood", "firewood", "wood in fireplace", "firewood in fireplace",
        "wood in stone fireplace", "firewood in stone fireplace",}),
        &fire_desc("wood"));
    add_item(({"supply", "wood supply", "firewood supply", "bin",
        "firewood bin", "small bin", "firewood in bin",}), "A small bin " +
        "next to the fireplace holds a supply of firewood.\n");

    add_chair("fireplace", "[down] [on] [a] [pillow] [near] [the] 'fireplace'",
        3, "near");
    add_chair("love seat", "[down] [in] [the] [love] 'seat'", 4, "in");
    add_chair("loveseat", "[down] [on] [a] [pillow] 'near' [the] [love] 'seat'",
        3, "near");
    add_chair("sofa", "[down] [on] [a] [the] 'sofa'", 6, "in");
    add_chair("large sofa",
        "[down] [on] [a] [pillow] 'near' [the] 'sofa'", 3, "near");
    add_chair("ottoman", "[down] [in] [the] [storyteller] 'ottoman'", 1, "in");
    add_chair("large ottoman",
        "[down] [on] [a] [pillow] 'near' [the] [storyteller] 'ottoman'",
        3, "near");
    add_item(({"ottoman", "large ottoman", "round ottoman",
        "large round ottoman"}), &sitting_look("ottoman"));
    add_item(({"seat", "love seat", "loveseat", "overstuffed loveseat",
        "loveseats", "overstuffed loveseats", "love seats",}),
        &sitting_look("love seat"));
    add_item(({"sofa", "large sofa", "sofas", "large sofas"}),
        &sitting_look("sofa"));

    add_prop(ROOM_I_INSIDE, 1);
    add_prop(ROOM_I_LIGHT, 2);
    add_exit(STORYT_DIR + "rooms/3rdfloor", "north", check_sitting, 0);
}

nomask public void
reset_room()
{
    set_wood(100);
    tell_room(TO, "A servant silently enters the room, replenishing the " +
        "firewood in the bin by the fireplace before quietly departing " +
        "again.\n");
    gPilTaken = 0;
}


// ********** stop here ***********

public void
do_sit_msgs(object pl, string prep, string name)
{
    if (name == "fireplace")
    {
        write("You grab a pillow and place it near the stone fireplace, " +
            "making yourself comfortable.\n");
        say(QCTNAME(pl) + " grabs a pillow and sits down on it near the " +
            "stone fireplace.\n", pl);
    }
    else if (name == "large sofa")
    {
        write("You grab a pillow and place it near one of the large sofas, " +
            "making yourself comfortable.\n");
        say(QCTNAME(pl) + " grabs a pillow and sits down on it near one " +
            "of the large sofas.\n", pl);
    }
    else if (name == "sofa")
    {
        write("You sink into the cusions of the sofa, making yourself " +
            "comfortable.\n");
        say(QCTNAME(pl) + " sits down on the sofa.\n", pl);
    }
    else if (name == "loveseat")
    {
        write("You grab one of the pillows and sit down comfortably near " +
            "the love seat.\n");
        say(QCTNAME(pl) + " grabs one of the pillows and sits down on it " +
            "near the love seat.\n", pl);
    }
    else if (name == "ottoman")
    {
        write("You sink down comfortably in the large ottoman that " +
            "is reserved for the one who is going to perform a story.\n");
        say(QCTNAME(pl) + " sits down in the large Storyteller's ottoman.\n",
            pl);
    }
    else if (name == "large ottoman")
    {
        write("You grab a pillow and place it near one of the overstuffed " +
            "ottomans, making yourself comfortable.\n");
        say(QCTNAME(pl) + " grabs a pillow and sits down on it near one " +
            "of the overstuffed ottomans.\n", pl);
    }
    else if (name == "love seat")
    {
        write("You sink into the softness of the love seat. It feels so " +
            "comfortable that any aches or pains are soon forgotten, " +
            "replaced by warmth and relaxation.\n");
        say(QCTNAME(pl) + " seats " + pl->query_objective() + "self in the " +
            "love seat, a look of relaxation spreading across " +
            pl->query_possessive() + " features.\n", pl);
    }
    else
        ::do_sit_msgs(pl, prep, name);
}

public void
do_stand_msgs(object pl, string name)
{
    if (name == "fireplace")
    {
        write("You stand up from where you were sitting near the fireplace, " +
            "and bring your pillow back to where you found it.\n");
        say(QCTNAME(pl) + " stands up from the pillow on the floor near " +
            "the fireplace, putting the pillow back where " +
            pl->query_pronoun() + " found it.\n", pl);
    }
    else if (name == "loveseat")
    {
        write("You stand up from the pillow near the love seat, putting " +
            "the pillow back where you found it.\n");
        say(QCTNAME(pl) + " stands up and puts the pillow back where " +
            pl->query_pronoun() + " found it.\n", pl);
    }
    else if (name == "large sofa")
    {
        write("You stand up from the pillow near the large sofa, " +
            "putting the pillow back where you found it.\n");
        say(QCTNAME(pl) + " stands up and puts the pillow back where " +
            pl->query_pronoun() + " found it.\n", pl);
    }
    else if (name == "large ottoman")
    {
        write("You stand up from the pillow near the large round ottoman, " +
            "putting the pillow back where you found it.\n");
        say(QCTNAME(pl) + " stands up from the pillow on the floor near " +
            "the large round ottoman, putting it back where " +
            pl->query_pronoun() + " found it.\n", pl);
    }
    else ::do_stand_msgs(pl, name);
}

nomask public string
sitting_look(string arg)
{
    string  occupants;
    if (arg == "ottoman")
    {
        return "A large round ottoman sits in the center of the room " +
            "which has been reserved for the storyteller.\n" +
            sitting_on_chair("chair", TP, 0);
    }
    if (arg == "love seat" || arg == "seat" || arg == "loveseat")
    {
        return "It is a small, comfortable couch that sits two people " +
            "close enough to make room for romance. \n" +
            sitting_on_chair("love seat", TP, 0);
    }
    if (arg == "sofa")
    {
        return "Three large sofas are scattered around the room.  Each " +
            "with a good vantage point to see the storyteller. \n" +
            sitting_on_chair("sofa", TP, 0);
    }
}

nomask public string
fire_desc(string arg)
{
    int     fire_state = query_fire_state();
    string  desc;

    switch(arg)
    {
    case "fireplace":
        switch (fire_state)
        {
        case FIRE_BURNING:
            desc = "A nice fire is burning in the stone fireplace " +
                "in the south wall, casting a warm light over the " +
                "room. A small bin stands next to the fireplace, " +
                "holding extra firewood.";
        case FIRE_UNLIT_WOOD:
            desc = "In the south wall is a stone fireplace, and a " +
                "stack of firewood has been placed within it ready " +
                "to be lit. A small bin next to the fireplace holds " +
                "extra firewood.";
        default:
            desc = "A stone fireplace is set into the south wall, " +
                "dark and empty at the moment. A small bin next to " +
                "it holds an extra supply of firewood.";
            return desc + "\n" + sitting_on_chair("fireplace", TP, 0);
        }
    case "fire":
        if (fire_state == FIRE_BURNING)
            return "Gold and red flames cast a warm light over the room.\n";
        else
            return "You find no fire.\n";
    case "wood":
        switch (fire_state)
        {
        case FIRE_BURNING:
            return "The wood in the fireplace burns brightly, emitting " +
                "both a pleasant warmth and light. In the small bin next " +
                "to the fireplace more wood has been stacked.\n";
        case FIRE_UNLIT_WOOD:
            return "Wood has been piled up in the fireplace, waiting " +
                "to be lit. An extra supply lies in the small bin next " +
                "to the fireplace.\n";
        default:
            return "A small bin next to the fireplace holds some " +
                "firewood that could be used in the hearth.\n";
        }
    case "ashes":
        switch (fire_state)
        {
        case FIRE_BURNING:
                return "Beneath the brightly burning fire, ashes " +
                    "cover the bottom of the fireplace.\n";
        case FIRE_UNLIT_WOOD:
                return "Beneath the firewood, ashes cover the bottom " +
                    "of the fireplace.\n";
        default:
                return "Ashes cover the bottom of the fireplace.\n";
        }
    case "light":
        if (fire_state == FIRE_BURNING)
            return "The flames in the fireplace cast a warm light " +
                "over the room.\n";
        if (!strlen(Exa_arg))
            return "";
        if (Exa_arg != "light")
            return "You find no fire.\n";
    }
    return "";
}

public int
get_pillow(string str)
{
    object pillow;

    if (!strlen(str))
        return 0;

    if (lower_case(str) != "pillow")
        return 0;

    if (objectp(present("pillow", TO)))
        return 0;

    if (gPilTaken >= PILLOWS)
    {
        write("Hmm, there don't seem to be any left for you.\n");
        return 1;
    }

    pillow = clone_object(STORYT_DIR + "obj/pillow");

    if (!pillow->move(TP))
    {
        write("You " + query_verb() + " " + LANG_ADDART(pillow->short()) +
            ".\n");
        say(QCTNAME(TP) + " " + query_verb() + "s " +
            LANG_ADDART(pillow->short()) + ".\n");
        gPilTaken++;
        return 1;
    }
    else
    {
        write("You try to " + query_verb() + " " + LANG_ADDART(pillow->short()) +
            ", but fail.\n");
        say(QCTNAME(TP) + " tries to " + query_verb() + " " +
            LANG_ADDART(pillow->short()) + ", but fails.\n");
        pillow->remove_object();
        return 1;
    }
}

void
init()
{
    ::init();
    init_room_chairs();
    init_fire();
    add_action(get_pillow, "get");
    add_action(get_pillow, "take");
    add_action(get_pillow, "pick");
}

void
leave_inv(object obj, object to)
{
    int i, size;
    object *all_inv;

    leave_inv_room_chairs(obj, to);
    ::leave_inv(obj, to);

    all_inv = deep_inventory(obj);
    for (i = 0, size = sizeof(all_inv); i < size; i++)
        if (all_inv[i]->id("_story_pillow"))
            all_inv[i]->run_away_alarm();
}

