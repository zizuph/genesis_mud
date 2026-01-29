/*
 * /d/Gondor/clubs/storyteller/rooms/sittingroom2.c
 * Copyright, Rolf Braun a.k.a. Elessar. Genesis, 1998.
 *
 * This is the second floor sittingroom of the clubhouse
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
    return "The room isn't overly large, yet doesn't seem too crowded " +
        "with furniture. A large sturdy rocking chair is over in one " +
        "corner. Across from a smaller, comfortable love seat is a " +
        "large overstuffed couch, near an iron wood-burning stove. " +
        "Several large, soft pillows are lying on the floor. " +
        (gPilTaken < PILLOWS ?
        "A few small pillows are scattered across the room as well. " :
        "") + "Ample lighting is provided by some brass lanterns on the " +
        "walls.\n" + fire_desc("light");
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
    set_short("the second floor sittingroom");
    set_long(&long_desc());

    add_item(({"lamp", "lamps", "lantern", "lanterns", "brass lantern",
        "brass lanterns",}), "Brass lanterns on the walls provide most " +
        "of the ample lighting in the room.\n");
    add_item(({ "small pillow", "small pillows"}), &pillow_desc());
    add_item(({"pillow", "pillows", "large pillow", "large pillows",
        "soft pillow", "soft pillows", "large soft pillow",
        "large soft pillows", }), "There are a number of pillows on the " +
        "floor that people listening to the storyteller can use to sit " +
        "more comfortably on the floor. You can sit on pillows near the " +
        "stove, near the love seat, near the couch and near the chair\n");
    add_item(({"stove", "iron stove", "wood-burning stove",
        "iron wood-burning stove", "wood-stove", }), &fire_desc("stove"));
    add_item(({"fire", "flames", "flame", "red flames", "gold flames",
        "red flame", "gold flame", }), &fire_desc("fire"));
    add_item(({"firelight", "light", "fire light", }), &fire_desc("light"));
    add_item(({"ash", "ashes", "ash in stove", "ashes in stove", }),
        &fire_desc("ashes"));
    add_item(({"wood", "firewood", "wood in stove", "firewood in stove",}),
        &fire_desc("wood"));
    add_item(({"supply", "wood supply", "firewood supply", "bin",
        "firewood bin", "small bin", "firewood in bin",}),
        "A small bin next to the stove holds a supply of firewood.\n");
    add_chair("stove",
        "[down] [on] [a] [pillow] [near] [the] [iron] [wood-burning] 'stove'",
        3, "near");
    add_chair("love seat", "[down] [in] [the] [love] 'seat'", 2, "in");
    add_chair("loveseat", "[down] [on] [pillow] 'near' [the] [love] 'seat'",
        3, "near");
    add_chair("chair", "[down] [on] [a] [pillow] 'near' [the] 'chair'",
        3, "near");
    add_chair("rocking chair", "[down] [in] [the] [rocking] 'chair'",
        1, "in");
    add_chair("large couch",
        "[down] [on] [a] [pillow] 'near' [the] [large] [overstuffed] 'couch'",
        3, "near");
    add_chair("couch",
        "[down] [in] / [on] [the] [large] [overstuffed] 'couch'", 4);
    add_item(({"couch", "large couch", "overstuffed couch",
        "large overstuffed couch", }), &sitting_look("couch"));
    add_item(({"chair", "rocking chair", "rockingchair", "rocking-chair",
        "sturdy chair", }), &sitting_look("chair"));
    add_item(({"seat", "love seat", "loveseat",}), &sitting_look("love seat"));
    add_prop(ROOM_I_INSIDE, 1);
    add_prop(ROOM_I_LIGHT, 2);
    add_exit(STORYT_DIR + "rooms/shallway", "north", check_sitting, 0);
}

nomask public void
reset_room()
{
    set_wood(100);
    tell_room(TO, "A servant silently enters the room, replenishing the " +
        "firewood in the bin by the iron stove before quietly departing " +
        "again.\n");
    gPilTaken = 0;
}


public void
do_sit_msgs(object pl, string prep, string name)
{
    if (name == "stove")
    {
        write("You grab a pillow and place it near the iron stove, making " +
            "yourself comfortable.\n");
        say(QCTNAME(pl) + " grabs a pillow and sits down on it near the " +
            "iron wood-burning stove.\n", pl);
    }
    else if (name == "chair")
    {
        write("You grab a pillow and place it near the rocking chair, " +
            "making yourself comfortable.\n");
        say(QCTNAME(pl) + " grabs a pillow and sits down on it near the " +
            "rocking chair.\n", pl);
    }
    else if (name == "loveseat")
    {
        write("You grab one of the pillows and sit down comfortably near " +
            "the love seat.\n");
        say(QCTNAME(pl) + " grabs one of the pillows and sits down on it " +
            "near the love seat.\n", pl);
    }
    else if (name == "large couch")
    {
        write("You grab a pillow and place it near the large overstuffed " +
            "couch, making yourself comfortable.\n");
        say(QCTNAME(pl) + " grabs a pillow and sits down on it near the " +
            "large overstuffed couch.\n", pl);
    }
    else if (name == "rocking chair")
    {
        write("You sit down in the large rocking chair that " +
            "is reserved for the one who is going to perform a story.\n");
        say(QCTNAME(pl) + " sits down in the Storyteller's rocking " +
            "chair.\n", pl);
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
    else if (name == "couch")
    {
        write("You sink down into the soft, comfortable couch, and " +
            "settle back for a relaxing time of listening to stories.\n");
        say(QCTNAME(pl) + " sinks down into the soft couch, looking " +
            "quite comfortable.\n", pl);
    }
    else
        ::do_sit_msgs(pl, prep, name);
}

public void
do_stand_msgs(object pl, string name)
{
    if (name == "stove")
    {
        write("You stand up from where you were sitting near the stove, " +
            "and bring your pillow back to where you found it.\n");
        say(QCTNAME(pl) + " stands up from the pillow on the floor near " +
            "the iron stove, putting the pillow back where " +
            pl->query_pronoun() + " found it.\n", pl);
    }
    else if (name == "chair")
    {
        write("You stand up from your position on the floor near the " +
            "chair, and put your pillow back where you found it.\n");
        say(QCTNAME(pl) + " stands up over by the chair, putting the " +
            "pillow back where " + pl->query_pronoun() + " found it.\n", pl);
    }
    else if (name == "loveseat")
    {
        write("You stand up from the pillow near the love seat, putting " +
            "the pillow back where you found it.\n");
        say(QCTNAME(pl) + " stands up and puts the pillow back where " +
            pl->query_pronoun() + " found it.\n", pl);
    }
    else if (name == "large couch")
    {
        write("You stand up from the pillow near the large overstuffed " +
            "couch, putting the pillow back where you found it.\n");
        say(QCTNAME(pl) + " stands up from the pillow near the couch, and " +
            "puts the pillow back where " + pl->query_pronoun() +
            " found it.\n", pl);
    }
    else ::do_stand_msgs(pl, name);
}

nomask public string
sitting_look(string arg)
{
    string  occupants;
    if (arg == "chair")
    {
        return "The large wooden rocking chair seems quite sturdy, " +
            "and with pillows and arm rests it looks very comfortable.\n" +
            sitting_on_chair("chair", TP, 0);
    }
    if (arg == "love seat")
    {
        return "It is a small, comfortable couch that sits two people " +
            "close enough to make room for romance. \n" +
            sitting_on_chair("love seat", TP, 0);
    }
    if (arg == "couch")
    {
        return "The large couch sits four people, and seems a very " +
            "comfortable place to sit while listening to stories.\n" +
            sitting_on_chair("couch", TP, 0);
    }
}

nomask public string
fire_desc(string arg)
{
    int     fire_state = query_fire_state();
    string  desc;

    switch(arg)
    {
    case "stove":
        switch (fire_state)
        {
        case FIRE_BURNING:
            return "A nice fire is burning in the iron stove, emitting " +
                "a comfortable heat throughout the room. A small bin " +
                "stands next to the stove, holding extra firewood. \n" +
                sitting_on_chair("stove", TP, 0);
        case FIRE_UNLIT_WOOD:
            return "By the south wall is an iron wood-burning stove, a " +
                "stack of firewood  placed within it ready to be lit. " +
                "A small bin next to the stove holds extra firewood. " +
                sitting_on_chair("stove", TP, 0) + "\n";
        default:
            return "An iron wood-burning stove is set by the north wall, " +
                "dark and empty at the moment. A small bin next to it " +
                "holds an extra supply of firewood. " +
                sitting_on_chair("stove", TP, 0) + "\n";
        }
    case "fire":
        if (fire_state == FIRE_BURNING)
            return "Gold and red flames cast a weak light over the room.\n";
        else
            return "You find no fire.\n";
    case "wood":
        switch (fire_state)
        {
        case FIRE_BURNING:
            return "The wood in the stove burns warmly, emitting a " +
                "pleasant warmth. In the small bin next to the stove " +
                "more wood has been stacked.\n";
        case FIRE_UNLIT_WOOD:
            return "Wood has been piled up in the stove, waiting to be " +
                "lit. An extra supply lies in the small bin next to the " +
                "stove.\n";
        default:
            return "A small bin next to the iron stove holds a supply of " +
                "firewood.\n";
        }
    case "ashes":
        switch (fire_state)
        {
        case FIRE_BURNING:
            return "Beneath the brightly burning fire, ashes cover the " +
                "bottom of the iron stove.\n";
        case FIRE_UNLIT_WOOD:
            return "Beneath the firewood, ashes cover the bottom of the " +
                "iron stove.\n";
        default:
            return "Ashes cover the bottom of the stove.\n";
        }
    case "light":
        if (fire_state == FIRE_BURNING)
            return "The flames in the stove cast a weak light over the room.\n";
        if (!strlen(Exa_arg))
            return "";
        if (Exa_arg != "light")
            return "You find no fire.\n";
    default:
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

