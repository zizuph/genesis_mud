/*
 * /d/Gondor/clubs/storyteller/rooms/sittingroom.c
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

#include <macros.h>
#include <stdproperties.h>

#define PILLOWS 5

public nomask string sitting_look(string arg);
public string fire_desc(string arg);

int gPilTaken = 0;

string
long_desc()
{
    return "This is a finely appointed room, small and cozy. A large " +
        "wing-back chair sits in one corner near a bright lamp, and a " +
        "small, overstuffed love seat stands in the middle of the floor. " +
        "Several large, soft pillows are lying atop a braided rug. " +
        (gPilTaken < PILLOWS ?
        "A few small pillows are scattered across the room as well. " : "") +
        "In the north wall is a fireplace, with a small bin standing just " +
        "next to it. An atmosphere of romance, mystery and quiet pervades " +
        "the room.\n" + fire_desc("light");
}

int
is_pillow(object ob)
{
    if (ob->id("_story_pillow"))
        return 1;

    return 0;
}

public string
pillow_desc()
{
    int num;
    object *pillows;

    pillows = all_inventory(TO);
    pillows = filter(pillows, is_pillow);
    num = sizeof(pillows);
    if ((PILLOWS - gPilTaken + num) > 0)
        return "The outer covering of the small pillows are made of smooth " +
            "coloured satin. They are incredibly fluffy and soft, perfect for " +            "squeezing, cuddling, sleeping and even throwing! There are " +
            (PILLOWS - gPilTaken + num) + " pillows left.\n";
    else
        return "There aren't any pillows left.\n";
}

void
create_gondor()
{
    set_short("the first floor sittingroom");
    set_long(&long_desc());

    add_item(({"wall", "walls"}), "The walls are made of polished wood " +
        "panels. A fireplace has been placed on the north wall.\n");
    add_item(({"panel", "panels", "wood panel", "wood panels"}),
        "The wood panels on the walls have all been polished down, " +
        "though they do look aged still.\n");
    add_item(({"lamp", "bright lamp"}), "A bright lamp stands near the " +
        "large chair, and it seems to be the main source of light in the " +
        "room, except for the fireplace.\n");
    add_item(({ "small pillow", "small pillows" }), &pillow_desc());
    add_item(({"pillow", "pillows", "large pillow", "large pillows",
        "soft pillow", "soft pillows", "large soft pillow", 
        "large soft pillows", }), "There are a number of pillows on the " +
        "floor that people listening to the storyteller can use to sit more " +
        "comfortably on the floor. You can sit on a pillow near the " +
        "fireplace, near the love seat and near the chair.\n");
    add_item("fireplace", &fire_desc("fireplace"));
    add_item(({"fire", "flames", "flame", "red flames", "gold flames",
        "red flame", "gold flame", }), &fire_desc("fire"));
    add_item(({"firelight", "light", "fire light", }), &fire_desc("light"));
    add_item(({"ash", "ashes", "ash in fireplace", "ashes in fireplace", }),
        &fire_desc("ashes"));
    add_item(({"wood", "firewood", "wood in fireplace",
        "firewood in fireplace",}), &fire_desc("wood"));
    add_item(({"supply", "wood supply", "firewood supply", "bin",
        "firewood bin", "small bin", "firewood in bin",}), "A small bin " +
        "next to the fireplace holds a supply of firewood.\n");
    add_chair("fireplace", "[down] [on] [a] [pillow] [near] [the] 'fireplace'",
        3, "near");
    add_chair("love seat", "[down] [in] [the] [love] 'seat'", 2, "in");
    add_chair("loveseat", "[down] [on] [pillow] 'near' [the] [love] 'seat'",
        3, "near");
    add_chair("chair", "[down] [on] [a] [pillow] 'near' [the] 'chair'",
        3, "near");
    add_chair("large chair", "[down] [in] [the] [storyteller] 'chair'", 1, "in");
    add_item(({"chair", "large chair", "wing-back chair"}),
        &sitting_look("chair"));
    add_item(({"seat", "love seat", "loveseat",}), &sitting_look("love seat"));
    add_prop(ROOM_I_INSIDE, 1);
    add_prop(ROOM_I_LIGHT, 2);
    add_exit(STORYT_DIR + "rooms/foyer", "south", check_sitting, 0);
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

public void
do_sit_msgs(object pl, string prep, string name)
{
    if (name == "fireplace")
    {
        write("You grab a pillow and place it near the fireplace, making " +
            "yourself comfortable.\n");
        say(QCTNAME(pl) + " grabs a pillow and sits down on it near the " +
            "fireplace.\n", pl);
    }
    else if (name == "chair")
    {
        write("You grab a pillow and place it near the Storyteller's chair, " +
            "making yourself comfortable.\n");
        say(QCTNAME(pl) + " grabs a pillow and sits down on it near the " +
            "Storyteller's chair.\n", pl);
    }
    else if (name == "loveseat")
    {
        write("You grab one of the pillows and sit down comfortably near " +
            "the love seat.\n");
        say(QCTNAME(pl) + " grabs one of the pillows and sits down on it " +
            "near the love seat.\n", pl);
    }
    else if (name == "large chair")
    {
        write("You sink down comfortably in the large wing-back chair that " +
            "is reserved for the one who is going to perform a story.\n");
        say(QCTNAME(pl) + " sits down in the large Storyteller's chair.\n", pl);
    }
    else if (name == "love seat")
    {
        write("You sink into the softness of the love seat. It feels so " +
            "comfortable that any aches or pains are soon forgotten, " +
            "replaced by warmth and relaxation.\n");
        say(QCTNAME(pl) + " seats " + pl->query_objective() + "self in " +
            "the love seat, a look of relaxation spreading across " +
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
    else if (name == "chair")
    {
        write("You stand up from your position on the floor near the chair, " +
            "and put your pillow back where you found it.\n");
        say(QCTNAME(pl) + " stands up over by the chair, putting the pillow " +
            "back where " + pl->query_pronoun() + " found it.\n", pl);
    }
    else if (name == "loveseat")
    {
        write("You stand up from the pillow near the love seat, putting " +
            "the pillow back where you found it.\n");
        say(QCTNAME(pl) + " stands up and puts the pillow back where " +
            pl->query_pronoun() + " found it.\n", pl);
    }
    else ::do_stand_msgs(pl, name);
}

nomask public string
sitting_look(string arg)
{
    string  occupants;
    if (arg == "large chair" || arg == "chair")
    {
        return "The large wing-back chair has scrolled arms making " +
            "it look very comfortable and soft.\n" +
            sitting_on_chair("chair", TP, 0);
    }
    if (arg == "love seat" || arg == "seat" || arg == "loveseat")
    {
        return "It is a small, comfortable couch that sits two people " +
            "close enough to make room for romance. \n" +
            sitting_on_chair("love seat", TP, 0);
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
        if (fire_state == FIRE_BURNING)
            desc = "A nice fire is burning in the stone fireplace " +
                "in the north wall, casting a warm light over the " +
                "room. A small bin stands next to the fireplace, " +
                "holding extra firewood.";
        else if (fire_state == FIRE_UNLIT_WOOD)
            desc = "In the north wall is a stone fireplace, and a " +
                "stack of firewood has been placed within it ready " +
                "to be lit. A small bin next to the fireplace holds " +
                "extra firewood.";
        else 
            desc = "A stone fireplace is set into the north wall, " +
                "dark and empty at the moment. A small bin next to " +
                "it holds an extra supply of firewood.";
            return desc + "\n" + sitting_on_chair("fireplace", TP, 0);
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
    default:
        return "You find nothing.\n";
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
        write("You try to " + query_verb() + " " +
            LANG_ADDART(pillow->short()) + ", but fail.\n");
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

