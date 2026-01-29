/*
 *  /d/Sparkle/guilds/new_merc/kitchen.c
 *
 *  This is the kitchen of the Mercenary Guild. If the cook is here,
 *  and Pearl is in the cafeteria, players are shooed out.
 *
 *  Created July 2009, by Cooper Sherry (Gorboth)
 */
#pragma strict_types
#include "../merc_defs.h"

inherit MERC_ROOM_BASE;

#include <macros.h>
#include <stdproperties.h>


/* Global Variables */
public object      Cook; /* The cook npc */
public string     *Cupboard_Items = ({ "ladel",
                                       "rolling_pin",
                                       "spatula",
                                       "butcher_knife",
                                       "wooden_spoon",
                                    });
public string     *Removed_Items = ({}); /* Items removed from cupboard */
public mixed       Searcher = 0; /* Anyone searching the cupboard. */

/* Prototypes */
public void        create_merc_room();
public void        reset_room();
public int         prevent_enter(object ob);
public void        leave_inv(object ob, object dest);
public int         stop_delay_cmd(mixed arg);
public mixed       begin_cupboard_search();
public string      end_cupboard_search();
public string      describe(string arg);

public mixed       query_c_items() { return Cupboard_Items; }
public mixed       query_r_items() { return Removed_Items; }
public mixed       query_searcher() { return Searcher; }
public mixed       query_cook_errand() { return Cook->query_errand(); }

/* Definitions */
#define            SEARCHED_MERC_KITCHEN "_searched_merc_kitchen"


/*
 * Function name:        create_merc_room
 * Description  :        set up the room with area presets
 */
public void
create_merc_room()
{
    set_short("within a rather cramped kitchen");
    set_long("You stand within a rather cramped kitchen. A large stove"
      + " is connected to a chimney in the northeast corner of the"
      + " room. Cupboards line the southern wall. A large counter"
      + " fills the western half of the room, providing plenty of"
      + " space for food preparation. An opening in the western wall"
      + " leads out into the feasting hall.\n\n");

    add_name("_merc_guild_kitchen");

    add_item( ({ "here", "area", "room", "kitchen" }),
        "It is rather cramped in here. It is no wonder the cook"
      + " looks so tired most of the time.\n");
    add_item( ({ "cramped", "cramped kitchen" }),
        "Rather cramped, yes ...\n");
    add_item( ({ "rather cramped", "rather cramped kitchen" }),
        "This kitchen is more cramped than the bowels of a"
      + " constipated mule in a potato patch.\n");
    add_item( ({ "mule", "constipated mule" }),
        "Don't get cute.\n");
    add_item( ({ "potato", "potato patch" }),
        "It might be slapping time.\n");
    add_item( ({ "floor", "ground", "down" }),
        "The floor in here is a sight. The cook doesn't seem to"
      + " mind a mess, it is safe to say.\n");
    add_item( ({ "mess" }),
        "Disgraceful. Well, if you're a goblin, possibly homey.\n");
    add_item( ({ "stove", "large stove", "oven" }),
        "The stove appears, to put it in polite terms, to be"
      + " well-used. A less forgiving description would be that"
      + " it is a grease-caked disaster.\n");
    add_item( ({ "grease" }),
        "At this rate, future generations will be able to use this"
      + " kitchen as a soap mine.\n");
    add_item( ({ "disaster", "grease-caked disaster",
                 "grease caked disaster" }),
        "So much grease, so little ... er ... just yuck.\n");
    add_item( ({ "chimney" }),
        "This chimney isn't very large. It heads up through the"
      + " ceiling probably on its way to the roof.\n");
    add_cmd_item( ({ "chimney", "up chimney", "in chimney" }),
                  ({ "climb", "enter" }),
        "The only thing going up the chimney any time soon will be"
      + " smoke.\n");
    add_item( ({ "soap mine", "mine" }),
        "Give it a few more decades.\n");
    add_item( ({ "smoke" }),
        "It might be inside the chimney, but it isn't visible"
      + " here in the kitchen. The cook, sloppy as he may be, at"
      + " least has enough sense to keep the air breathable.\n");
    add_item( ({ "air" }), 
        "Its breathable, thankfully.\n");
    add_item( ({ "northeast", "northeast corner", "corner",
                 "corner of the room",
                 "northeast corner of the room" }),
        "The chimney is there, along with the stove.\n");
    add_item( ({ "cupboard", "cupboards" }),
        "The cupboards are nearly bursting with various objects."
      + " It is a wonder the cook can find anything there. Searching"
      + " for even the simplest tool would be a considerable"
      + " quest in and of itself!\n");
    add_item( ({ "south", "south wall", "southern wall" }),
        "Most of the southern wall is taken up by cupboards.\n");
    add_item( ({ "objects", "various objects" }),
        "The cupboard is full of 'em.\n");
    add_item( ({ "tool", "tools", "simple tool", "simple tools",
                 "simplest tool", "simplest tools" }),
        "There are certainly many in the cupboard. Good luck"
      + " searching for the one you need, though.\n");
    add_item( ({ "counter", "large counter", "counter top",
                 "countertop" }),
        "The counter is cluttered beyond hope. I suppose the act"
      + " of preparing enough food to keep a hungry lot like the"
      + " Mercenaries happy doesn't leave much time for being"
      + " orderly.\n");
    add_item( ({ "west", "western half",
                 "west half", "western half of the room",
                 "west half of the room" }),
        "That's where the counter is. Whoa ...\n");
    add_item( ({ "food", "food preparation" }),
        "It seems to be the raison d'etre around here.\n");
    add_item( ({ "raison d'etre" }),
        "Pardon your french!\n");
    add_item( ({ "opening", "western wall",
                 "opening in the western wall", "west wall",
                 "opening in the west wall" }),
        "It leads out to the feasting hall.\n");
    add_item( ({ "mess hall", "cafeteria", "feasting hall",
                 "hall", "large hall" }),
        "Sit. Talk. Eat. That sort of place.\n");

    add_item( ({ "trough", "rubbish trough" }), &describe("rubbish"));
    add_item( ({ "bucket", "water bucket", "wooden bucket",
                 "wood bucket" }), &describe("water"));

    add_indoor_view();
    add_indoor_lodge_view();

    add_prop(ROOM_I_INSIDE, 1);

    add_exit("mess_hall", "west");

    set_no_exit_msg( ({ "northwest", "northeast", "southeast",
                        "southwest", "north", "east" }),
        "There is no way to exit the kitchen in that direction.\n");

    add_delay_cmd_item( ({ "cupboard", "cupboards" }),
                       "search",
                       "searching the cupboards",
                       10,
                       begin_cupboard_search,
                       end_cupboard_search);

    setuid();
    seteuid(getuid());

    room_add_object(DOORS_DIR + "kitchen_s");

    reset_room();
} /* create_room */


/*
 * Function name:        reset_room
 * Description  :        bring the cook in if he's not around
 */
public void
reset_room()
{
    string    c_item = one_of_list(Removed_Items);
    string    c_item_desc;
    object    pearl;
    object    cafeteria = find_object(ROOM_DIR + "mess_hall");

    if (objectp(Cook))
    {
        if (c_item && present(Cook, this_object()))
        {
            c_item_desc = implode(explode(c_item, "_"), " ");

            Cook->command("$emote searches for something in the"
               + " cupboards.");
            Cook->command("$scratch");
            Cook->command("$emote mutters: Now where did I put"
              + " that " + c_item_desc + ", I wonder?");
            Cook->command("$sigh");
            Cook->command("$shout Um ... Darling ... I seem to"
              + " have misplaced my " + c_item_desc + " again. Would"
              + " you .... um .... be able to help?");

            if (!(pearl = present("_merc_guild_waiter", cafeteria)))
            {
                Cook->command("$shout Darling? Did you hear me?");
                Cook->command("$grumble");
                Cook->command("say Guess I'll find a workaround.");

                return;
            }

            Cupboard_Items += ({ c_item });
            Removed_Items -= ({ c_item });

            pearl->command("$shout You worthless slob!");
            pearl->command("$emote snaps her fingers. A " + c_item_desc
              + " appears in her hand with a brilliant flash of light!");
            pearl->command("$emote hurls the " + c_item_desc + " into the"
              + " kitchen! A painful yelp echoes from within, and"
              + " the cook peers from the room, smiles sheepishly,"
              + " blows a kiss to his wife, and disappears again.");
            pearl->command("$rolleyes");

            tell_room(this_object(), "A " + c_item_desc + " hurtles into"
              + " the room from the feasting hall, and hits the cook"
              + " right in the face!\n");
            Cook->command("$emote yelps in pain!");
            Cook->command("$emote peeks out into the mess hall and"
              + " then returns, red-faced, back into the kitchen. After"
              + " using the " + c_item_desc + " for a few minutes, he returns"
              + " it to the cupboard.");
        }

        return;
    }

    tell_room(this_object(), "Looking a bit glassy-eyed, a man enters"
      + " the kitchen, puts on his cooking hat and apron, and gets to"
      + " work.\n");

    Cook = clone_object(NPC_DIR + "cook");
    Cook->arm_me();
    Cook->move(this_object());
} /* reset_room */


/*
 * Function name: prevent_enter
 * Description:   Called when an object is trying to enter this container to
 *                see if we will allow it in.
 * Arguments:     object ob - the object that is trying to enter.
 * Returns:       1 - The object is not allowed to enter
 *                0 - The object is allowed to enter
 */
public int
prevent_enter(object ob)
{
    object    old_tp = this_player();

    if (!interactive(ob) ||
         ob->query_wiz_level() ||
         ob->id("_merc_guild_cook") || 
         ob->id("_merc_guild_waiter"))
    {
        return 0; /* always let wizards go where they will. */
    }

    if (!present(Cook, this_object()))
    {
        return 0;
    }

    set_this_player(ob);

    if (!CAN_SEE(Cook, ob))
    {
        set_alarm(0.5, 0.0, &write("The cook doesn't seem to notice"
          + " you ...\n"));

        set_this_player(old_tp);
        return 0;
    }

    write("You enter the kitchen, but before you can even look around "
      + "the cook brandishes a spatula and shoo's you out again!\n");

    tell_room(this_object(), "Noticing that " + QTNAME(ob) + " has"
      + " entered the kitchen, the"
      + " cook brandishes a spatula and shoo's "
      + ob->query_objective() + " out again!\n");
    tell_room(environment(ob), QCTNAME(ob) + " is shoo'd out of the"
      + " kitchen by the cook.\n", ob);

    set_this_player(old_tp);

    return 1;
} /* prevent_enter */


/*
 * Function name:       leave_inv
 * Description  :       catch any cupboard searchers leaving. They can't
 *                      do it on their own, but they might be trans'd
 * Arguments    :       object ob -- the departing object
 *                      object dest -- its destination
 */
public void
leave_inv(object ob, object dest)
{
    if (Searcher == ob)
    {
        Searcher = 0;
    }

    ::leave_inv(ob, dest);
} /* leave_inv */


/*
 * Function name:       stop_delay_cmd
 * Description  :       mask parent so that if player does "stop",
 *                      we clear Searcher
 * Arguments    :       mixed arg -- if string, player did "stop"
 *                                -- if object, time ran out or
 *                                    called from leave_inv().
 * Returns      :       0 -- stop is always allowed
 */
public int
stop_delay_cmd(mixed arg)
{
    object      tp;

    if (!objectp(arg))
    {
        /* called from paralyze object when player did "stop" */
        tp = environment(previous_object());
        if (tp == Searcher)
        {
            Searcher = 0;
        }
    }
    return ::stop_delay_cmd(arg);
} /* stop_delay_cmd */


/*
 * Function name:        begin_cupboard_search
 * Description  :        Provides a slightly different message when a
 *                       player begins searching the cupboard based on
 *                       whether they have already done so.
 * Returns      :        mixed: integer -- 0 if command fails,
 *                           or string  -- the "You begin ..." message
 */
public mixed
begin_cupboard_search()
{
    if (!Searcher)
    {
        Searcher = this_player();
        say(QCTNAME(Searcher) + " begins searching through the"
          + " cupboards.\n");

        if (this_player()->query_prop(SEARCHED_MERC_KITCHEN))
        {
            return "You start searching through the cupboards again,"
              + " determined to find something useful.\n";
        }

        return "You start searching through the cupboards.\n";
    }

    write(Searcher->query_The_name(this_player()) + " is already doing"
      + " that, and is in your way."
      + " You'll have to wait until " + Searcher->query_pronoun()
      + " is finished.\n");
    return 1;
} /* begin_cupboard_search */


/*
 * Function name:        end_cupboard_search
 * Description  :        Provides the result of having searched the
 *                       cupboard.
 * Returns      :        string - message for the player
 */
public string
end_cupboard_search()
{
    string    searcher_msg;
    string    other_msg = QCTNAME(Searcher);
    string    cupboard_item = one_of_list(Cupboard_Items);
    string    c_item_desc;
    object    c_item;

    if (!cupboard_item)
    {
        searcher_msg = "Searching through the cupboards, you just don't"
                     + " find anything that interests you.";
        other_msg += " finishes searching the cupboards, apparently not"
                  + " finding anything of value.";
    }
    else
    {
        Cupboard_Items -= ({ cupboard_item });
        Removed_Items += ({ cupboard_item });
        c_item = clone_object(OBJ_DIR + cupboard_item);
        c_item_desc = implode(explode(cupboard_item, "_"), " ");

        searcher_msg = "You pull a " + c_item_desc + " from one of the"
          + " cupboards.";
        other_msg += " pulls a " + c_item_desc + " from one of the"
          + " cupboards.";
    
        if (c_item->move(Searcher))
        {
            searcher_msg += " Oops! You dropped it!";
            other_msg += " Oops! " + capitalize(Searcher->query_pronoun())
              + " dropped it!";
            c_item->move(this_object());
        }
    }

    tell_room(this_object(), other_msg + "\n", Searcher);
    Searcher = 0;
    return searcher_msg + "\n";
} /* end_cupboard_search */


/*
 * Function name:        describe
 * Description  :        provide some state-based descriptions of
 *                       things in the room that the cook may or may
 *                       not have taken on an errand.
 * Arguments    :        string arg - the thing we want to describe
 * Returns      :        string - the appropriate description for the
 *                                add_item to show the player.
 */
public string
describe(string arg)
{
    string  txt = "";
    mixed   cook = present(Cook, this_object());

    if (!cook &&
         objectp(Cook) &&
         query_cook_errand() == arg)
    {
        return "It appears to be missing.\n";
    }

    switch (arg)
    {
        case "rubbish":
            return "A rubbish trough is tucked beside the counter on"
              + " the floor and appears to be getting more full by"
              + " the minute.\n";
            break;
        case "water":
            return "A bucket filled with water rests against one wall."
              + " The water is filled with soap suds and gets dirtier"
              + " with each thing the cook washes in it.\n";
            break;
    }

    return "You find no such thing.\n"; /* Should never happen. */
} /* describe */