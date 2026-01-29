/*
 *  /d/Emerald/blackwall/delrimmon/lakeside/caves/store_room.c
 *
 *  This room was once used by Formandil and his men to house various
 *  supplies for their outposts. Over the centuries, few things have
 *  survived (though the observant adventurer may find a treat.)
 *  Lately, Ugluk and his band have used it to stow the rowboat they
 *  used to enter the area from the north.
 *
 *  Copyright (c) December 1998, by Cooper Sherry (Gorboth)
 */
#pragma strict_types

inherit "/d/Gondor/std/room.c";

#include <language.h>
#include <macros.h>
#include <stdproperties.h>
#include "/d/Emerald/blackwall/delrimmon/defs.h"

/* prototypes */
public void    create_gondor();
public void    reset_room();
public int     open_stuff(string arg);
public void    init();


/*
 * function name:        create_gondor
 * description  :        set up the room
 */
public void
create_gondor()
{
    set_short("the ceiling of this stone chamber is low, and shadows"
            + " crowd the small space it affords");
    set_long(BSN("This stone chamber appears to have at one time"
               + " served as a store room, judging from the many"
               + " delapidated supplies and shelves which crowd"
               + " this cramped space."));

    add_item( ({"print", "prints", "footprint", "footprints",
                "print in the dust",
                "prints in the dust",
                "footprint in the dust",
                "footprints in the dust"}), BSN(
        "There are many footprints which have recently disturbed"
      + " the dust which covers the floor of this chamber. They"
      + " are everywhere, and look too confused to be of any real"
      + " use to a tracker."));
    add_item( ({"shadow", "shadows"}), BSN(
        "Shadows fill this small chamber, making it somewhat"
      + " difficult to make ones way amid all the odds and ends."));
    add_item( ({"roof of the door", "top of the door"}), BSN(
        "The top of the door is a very short distance from the "
      + "ceiling of this cramped space."));
    add_item( ({"space", "cramped space"}), BSN(
        "There is quite a lot of which crowds this chamber. The doorway"
      + " appears to be the easiest place to stand."));
    add_item( ({"chamber", "room", "store room", "stone chamber",
                "here"}), BSN(
        "There is very little which is remarkable about this chamber."
      + " It is filled with delapidated supplies, and old storage"
      + " containers."));
    add_item( ({"supplies", "old supplies",
                "delapidated supplies"}), BSN(
        "There are many odds and ends strewn about this chamber. You"
      + " see some rusted hammers, sharpened stones, crusted rags,"
      + " and various rotted sacks."));
    add_item( ({"odds", "ends", "odds and ends"}), BSN(
        "You see some rusted hammers, sharpened stones, crusted rags,"
      + " and various rotted sacks."));
    add_item( ({"hammer", "hammers", "rusted hammer",
                "rusted hammers"}), BSN(
        "These tools look old and corroded, and would very likely be"
      + " of no use to anyone anymore."));
    add_item( ({"stone", "stones", "sharpened stone",
                "sharpened stones"}), BSN(
        "These stones are nearly buried in dust, which covers a good"
      + " deal of the floor here. It may be that these are pieces of"
      + " flint."));
    add_item( ({"flint", "piece of flint", "pieces of flint"}), BSN(
        "If indeed these stones are flint, they are hardly of any"
      + " real interest."));
    add_item( ({"dust"}), BSN(
        "Dust covers most everything in this chamber, laying in a"
      + " thick carpet on the floor. Prints in the dust reveal that"
      + " there has been some investigation of this chamber"
      + " by someone other than yourself recently."));
    add_item( ({"carpet", "thick carpet"}), BSN(
        "The dust lies heavily here. It looks to have had hundreds"
      + " of years to collect."));
    add_item( ({"rag", "rags", "crusted rag", "crusted rags"}), BSN(
        "The rags are so old and crusted that they almost seem"
      + " petrified. They were perhaps once used to polish weapons."));
    add_item( ({"sack", "sacks", "rotted sack", "rotted sacks"}), BSN(
        "The sacks are in many cases torn and look to have been"
      + " plundered. Many of them contain what might once have been"
      + " some form of fertilizer. However, now there is mostly"
      + " just dirt piling from their torn exteriors."));
    add_item( ({"fertilizer"}), BSN(
        "The dirt around the sacks does not appear to carry any"
      + " of its perhaps once fertile properties any longer."));
    add_item( ({"dirt"}), BSN(
        "The dirt may once have been fertilizer. It now however looks"
      + " rather plain and useless, flowing from the rotted threads"
      + " of the sacks which once contained it."));
    add_item( ({"thread", "threads", "rotted thread",
                "rotted threads"}), BSN(
        "It would seem that years of contact with either the contents"
      + " of the sacks or the air of the cave have taken their toll"
      + " on these threads, causing them fall to pieces."));
    add_item( ({"floor", "ground", "down"}), BSN(
        "The floor of this chamber is piled with many supplies and"
      + " old storage containers. There is also quite a lot of dust"
      + " resting over just about everything."));
    add_item( ({"storage container", "storage containers",
                "container", "containers", "old container",
                "old containers", "old storage container",
                "old storage containers"}), BSN(
        "There are barrels along the southern wall, which rest"
      + " below shelves which have been carved out of the rock."));
    add_item( ({"south wall", "wall to the south", "southern wall",
                "south"}), BSN(
        "Shelves have been carved in the stone of the southern wall"
      + " of this chamber. Barrels line the wall beneath them."));
    add_item( ({"barrel", "barrels"}), BSN(
        "The barrels appear to have been ripped open and plundered."
      + " They are all badly damaged, and quite empty, except for a"
      + " sturdy cask which appears to have escaped from the"
      + " vandalism."));
    add_item( ({"shelf", "shelves"}), BSN(
        "Aside from a good deal of dust and some piles of rust,"
      + " there is nothing of interest to be found on these"
      + " shelves. Barrels line the wall beneath them."));
    add_item( ({"rust", "pile of rust", "piles of rust"}), BSN(
        "These piles of rust must be the result of many hundreds"
      + " of years of corrosion. What they once were it seems"
      + " impossible to discover."));
    add_item( ({"ceiling", "roof", "up"}), BSN(
        "The ceiling of this chamber is rather low, rising very little"
      + " from the roof of the door which connects it to the larger"
      + " chamber to the north."));
    add_item( ({"door", "doorway", "passage", "north"}), BSN(
        "The northern passage winds a little ways before opening"
      + " once more onto a larger chamber in that direction."));
    add_item( ({"larger chamber"}), BSN(
        "There is little to see from here."));
    add_item( ({"wall", "walls", "wall of the chamber",
                "walls of the chamber", "chamber walls",
                "chamber wall", "stone wall", "stone walls"}), BSN(
        "The walls of this chamber are rough and dark, comprised"
      + " of the same stone which makes up the bedrock of the"
      + " cliffs."));
    add_item( ({"cliff", "cliffs", "cliffside", "cliffsides"}), BSN(
        "The cliffs are not visible from here, deep within their"
      + " own foundations."));
    add_item( ({"sky", "sun", "moon", "stars"}), BSN(
        "The sky is not visible from deep within the cliffs."));
    add_item( ({"west wall", "western wall", "wall to the west",
                "west"}), BSN(
        "There is nothing particularly remarkable about the wall"
      + " to the west. A few rotted sacks lay at its base."));
    add_item( ({"east wall", "eastern wall", "wall to the east",
                "east"}), BSN(
        "Aside from some crusted rags, sharpened stones, and rusted"
      + " hammers at its base, there is nothing of much interest"
      + " about the eastern wall."));
    add_item( ({"north wall", "northern wall", "wall to the north",
                "north"}), BSN(
        "The wall to the north is marked by a passage which travels"
      + " a short distance in that direction."));

    add_prop(ROOM_I_INSIDE, 1);
    add_prop(ROOM_I_LIGHT, 0);

    add_exit(DELRIMMON_DIR + "lakeside/caves/barracks", "north");

    set_no_exit_msg( ({ "northwest", "northeast", "east", "southeast",
                        "south", "southwest", "west" }),
        "The walls of the chamber block your path.\n");

    reset_room();

} /* create_gondor */

/*
 * function name:        reset_room
 * description  :        add some stuff to the room at resets
 */
public void
reset_room()
{
    object barrel;
    object boat;

    if (!(barrel = present("cask", this_object())))
    {
        barrel = clone_object(DELRIMMON_DIR + "obj/barrel")->move(TO);
    }

    if (!objectp(present("boat", this_object())))
    {
        boat = clone_object(DELRIMMON_DIR + "obj/boat")->move(TO);
    }

    barrel->fill_cask();
    barrel->add_prop(CONT_I_CLOSED, 1);
} /* reset_room */

/*
 * function name:        open_stuff
 * description  :        allows the player to open/close the barrel
 * arguments    :        int arg - 1 = open it, 0 = close it
 * returns      :        int 1 = success, 0 = failure
 */
public int
open_stuff(string arg)
{
    if (!strlen(arg))
    {
        NFN0("What do you wish to " + query_verb() + "?");
    }

    if (!parse_command(arg, ({}),
        "[the] 'sturdy' 'barrel'"))
    {
        if (parse_command(arg, ({}),
            "[the] [damaged] [empty] 'barrel' / 'barrels'"))
        {
            if (query_verb() == "close")
            {
                NFN0("Most of the barrels here have been destroyed,"
                   + " making it impossible for them to be closed.");
            }

            NFN0("Most of the barrels here have already been opened"
               + " by brute force, leaving them broken and empty.");
        }

        if (parse_command(arg, ({}),
            "[the] [torn] [rotted] 'sack' / 'sacks'"))
        {
            if (query_verb() == "close")
            {
                NFN0("The sacks are so badly rotted and torn that"
                   + " there is no way to close them now.");
            }

            NFN0("The sacks are torn, and destroyed. There is nothing"
               + " of use or interest to be found within them.");
        }

        return 0;
    }

    return 0;
} /* open barrel */

/*
 * function name:        init
 * description  :        set up some actions for the player
 */
public void
init()
{
    ::init();

    add_action(open_stuff, "open");
    add_action(open_stuff, "close");
} /* init */

