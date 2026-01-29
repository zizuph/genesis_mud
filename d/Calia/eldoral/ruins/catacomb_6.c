#pragma strict_types

#include "defs.h"
#include <macros.h>
#include <language.h>

#define LIVE_I_FOUND_HOLE "eq_live_i_found_hole"
#define LIVE_I_STUMBLED   "eq_live_i_stumbled"
#define HIS_HER(x)        x->query_possessive()
#define HE_SHE(x)         x->query_pronoun()

inherit STDROOM;

int south_open,
    hole_found;
object sceptre_placed;

/*
 * Function name: reset_room
 * Description  : Resets whether or not the hole in the
 *                floor has been reset.
 * Arguments    : n/a
 * Returns      : n/a
 */
public void
reset_room()
{
    ::reset_room();
    if (!sceptre_placed)
    {
        hole_found = 0;
        remove_item("hole");
        remove_item("slot");
    }
}

/*
 * Function name: long_desc
 * Description  : Returns a VBFC'd long description for the
 *                room, varying it depending on whether or
 *                not the door has been opened.
 * Arguments    : n/a
 * Returns      : A string describing the extra long.
 */
public string
long_desc()
{
    if (!south_open)
        return "At least, it appears to run north and south, but to the " +
        "south, a stone door or gate of some sort is firmly shut " +
        "across the path, with no apparent means of opening or " +
        "closing it. In fact, if it wasn't for the fact that " +
        "the door is the largest single block visible in the floor, " +
        "ceiling or walls, you'd think this was a dead end. " +
        "There aren't even any scratches or trails through the " +
        "dust that are usually evident with secret doors.\n\n";
    else
        return "A dark passageway leads southwards " +
            "away from a lighter passage to the north.\n\n";
}

/*
 * Function name: south_block
 * Description  : Returns true if the door is closed to
 *                block the exit.
 * Arguments    : n/a
 * Returns      : 0 - Passage open.
 *                1 - Passage closed.
 */
public int
south_block()
{
    if (!south_open)
    {
        write("You can't walk through solid stone.\n");
        return 1;
    }
    return 0;
}

/*
 * Function name: south_vis
 * Description  : Returns true if the south exit is open
 *                and players can see it.
 * Arguments    : n/a
 * Returns      : 0 - Players can't see it.
 *                1 - Players can see it.
 */
public int
south_vis()
{
    if (!south_open)
        return 1;
    else
        return 0;
}

/*
 * Function name: door_desc
 * Description  : Returns a description if players examine
 *                the door, but only if the door is closed.
 * Arguments    : n/a
 * Returns      : A string, the door description.
 */
public string
door_desc()
{
    if (south_open)
        return "It's not there anymore!\n";
    else
        return "For all intents and purposes, it appears to " +
            "be just a plain wall at first glance. Only " +
            "attention to the fact that the whole wall is " +
            "a single piece of stone leads to suspicion " +
            "of a door that goes from wall to wall, floor " +
            "to ceiling.\n";
}

public string
exa_floor_extra()
{
    if (hole_found)
    {
        if (sceptre_placed)
            return "One of the cobblestones has been rolled " +
                "over, revealing a narrow slot beneath, from " +
                "which " + 
                LANG_ADDART(sceptre_placed->query_prop(OBJ_S_ORIG_SHORT)) +
                " has been placed.";
        else
            return "One of the cobblestones has been rolled " +
                "over, revealing a narrow slot beneath.";
    }
    else
        return "";
}

public string
exa_slot()
{
    if (hole_found)
    {
        if (sceptre_placed)
            return "It appears to be a simply cylindrical " +
                "slot cut into the floor. " +
                capitalize(LANG_ADDART(
                sceptre_placed->query_prop(OBJ_S_ORIG_SHORT))) +
                " has been placed into it.\n";
        else
            return "It appears to be a simple cylindrical " +
                "slot cut into the floor.\n";
    }
    else
        return "";
}

/*
 * Function name: create_room
 * Description  : Turns the object into a room.
 * Arguments    : n/a
 * Returns      : n/a
 */
public void
create_room()
{
    set_short("a narrow passageway");
    set_long("You have entered a narrow passageway that leads " +
        "north and south somewhere beneath " + CASTLE_NAME + ". " +
        VBFC_ME("long_desc"));

    add_item(({"door", "stone door", "south wall"}),
        VBFC_ME("door_desc"));
    add_item(({"walls"}),
        "Walls flank either side of this passage, formed " +
        "by large blocks of cut grey stone. The only exception " +
        "is the south wall, which looks suspiciously like " +
        "a large stone door.\n");
    add_item(({"floor", "ground"}),
        "The floor consists of a number of small blocks " +
        "of stone, almost like cobblestones, closely fit " +
        "together. Their smaller size seems to be keeping " +
        "them in better shape than most of the stone " +
        "floors in the ruins. " + VBFC_ME("exa_floor_extra") +
        "\n");
    add_item(({"ceiling", "roof"}),
        "Above your head, the low stone ceiling is unadorned, " +
        "except for a small carving directly above your head.\n");
    add_item(({"carving", "small carving"}),
        "It appears to be a carving of a chimera, perched atop " +
        "a long shaft or pole of some kind. A strange sensation " +
        "of holiness seems to emanate from it.\n");
    add_prop(OBJ_S_WIZINFO, "This door is an illusion, dispelled " +
        "by the player with /d/Calia/eldoral/obj/sceptre.c. You, " +
        "however, can pass it with 'Call here open_passage'.\n");

    add_exit(RUIN + "catacomb_hub", "north");
    add_exit(RUIN + "catacomb_7", "south", VBFC_ME("south_block"), 1,
        VBFC_ME("south_vis"));

    add_prop(OBJ_S_SEARCH_FUN, "search_floor");

    DARK;
    INSIDE;

    set_alarm(0.0, 0.0, reset_room);
}

/*
 * Function name: search_floor
 * Description  : Allows players to search the floor.
 * Arguments    : player - Object pointer to the searching player.
 *                extra - String, the argument players supplied
 *                        with the 'search' command.
 * Returns      : Results as a string. "" if nothing found.
 */
public string
search_floor(object player, string extra)
{
    if (!parse_command(extra, TO, "[the] 'ground' / 'floor' / " +
        "'cobblestones'"))
        return "";

    if (!CAN_SEE_IN_ROOM(TP))
        return "It's too dark to search anything.\n";

    if (hole_found)
        return "You find nothing else special about the floor.\n";

    hole_found = 1;
    add_item(({"hole","slot"}), VBFC_ME("exa_slot"));
    tell_room(TO, QCTNAME(player) + " passes " + HIS_HER(player) +
        " eyes across the floor, suddenly stopping and narrowing " +
        "them at a single cobblestone. " + 
        capitalize(HE_SHE(player)) + " brushes it aside with " +
        HIS_HER(player) + " foot, revealing a narrow slot " +
        "beneath it.\n", ({player}));
    return "Examining the ground carefully, you notice one of " +
        "the cobblestones is loose. Brushing it aside, it " +
        "reveals a narrow slot.\n";    
}

public void
close_passage()
{
    tell_room(TO, "A stone wall shimmers into view across " +
        "the south exit.\n");
    south_open = 0;
}

public varargs void
open_passage(object who)
{
    if (!who)
        who = TP;

    if (south_open)
        return;

    tell_room(TO, "Suddenly, the stone door fades from view, the " +
        "illusion temporarily broken!\n");
    sceptre_placed->remove_sceptre(who);
    who->add_prop(LIVE_I_BEAST_QUEST,
        who->query_prop(LIVE_I_BEAST_QUEST) | BQ_USED_SCEPTRE);
    south_open = 1;
    set_alarm(30.0, 0.0, close_passage);
}

public int
do_open(string str)
{
    notify_fail("Open what?\n");
    if (!str || !strlen(str))
        return 0;

    if (!parse_command(str, TO, "[the] 'door' / 'wall'"))
        return 0;

    write("You don't see any way to open the door physically.\n");
    return 1;
}

public void
halfway_opening_door(object who)
{
    if (!sceptre_placed)
        return;

    tell_room(TO, "The " +
        sceptre_placed->query_prop(OBJ_S_ORIG_SHORT) +
        " rotates until the chimera on the top is facing " +
        "the south wall. A blue light flares in the " +
        "chimera's eye, and the wall begins glowing " +
        "in response!\n");

    set_alarm(5.0, 0.0, &open_passage(who));
}

public void
start_opening_door(object who)
{
    if (!sceptre_placed)
        return;

    tell_room(TO, "Suddenly, the " +
        sceptre_placed->query_prop(OBJ_S_ORIG_SHORT) +
        " begins to rotate slowly.\n");

    set_alarm(10.0, 0.0, &halfway_opening_door(who));
}

public int
do_insert(string str)
{
    mixed arr;

    if (!str || !strlen(str))
        return 0;

    if (!parse_command(str, TP, "%i 'in' / 'into' [the] " +
        "'slot' / 'hole'", arr))
    {
        notify_fail(capitalize(query_verb()) + " what where?\n");
        return 0;
    }

    if (!arr[0])
    {
        if (sizeof(arr[1..]) > 1)
        {
            NF("You can only put one thing in the slot.\n");
            return 0;
        }
        else
            arr = (object)arr[1];
    }

    else if (arr[0] > 0)
    {
        if (arr[0] > 1)
        {
            NF("You can only put one thing in the slot.\n");
            return 0;
        }
        else
            arr = (object)arr[arr[0]];
    } 

    else
        arr = (object)arr[-arr[0]];

  /* Fail if the player can't see the selected object */
    if (!CAN_SEE(TP, arr))
    {
        NF("You can't put something you can't see anywhere.\n");
        return 0;
    }

  /* If the object isn't the chimera sceptre, fail. */
    if (!(arr->is_eldoral_chimera_sceptre()))
    {
        NF("The " + arr->short() + " doesn't look like it " +
            "will fit properly.\n");
        return 0;
    }

  /* Can't place a sceptre if one is already in place. */
    if (sceptre_placed)
    {
        write("There's alread a sceptre in the slot.\n");
        return 1;
    }

    write("You bend over, and slip the " + arr->short() + 
        " into the slot in the floor.\n");
    say(QCTNAME(TP) + " bends over, and slips " +
        LANG_ADDART(arr->short()) + " into a slot in the floor.\n");
    arr->move(TO, 1);
    arr->add_prop(OBJ_S_ORIG_SHORT, arr->query_short());
    arr->set_short(arr->query_short() + ", jutting from a slot " +
        "in the floor");
    arr->add_prop(OBJ_M_NO_GET, "It seems to be locked into " +
        "the slot somehow.\n");
    sceptre_placed = arr;
    set_alarm(10.0, 0.0, &start_opening_door(TP));
    return 1;    
}

public void
init()
{
    ::init();
    add_action(do_open, "open");
    add_action(do_insert, "insert");
    add_action(do_insert, "put");
    add_action(do_insert, "place");
}

public void
stumble(object who)
{
    object *all;

    write("You stumble a bit as you trip on something.\n");
    say(QCTNAME(who) + " stumbles on something.\n");
    all = filter(all_inventory(TO), interactive);
    all->add_prop(LIVE_I_STUMBLED, 1);
}

public void
enter_inv(object ob, object from)
{
    ::enter_inv(ob, from);

    if (!interactive(ob))
        return;

    if (ob->query_prop(LIVE_I_STUMBLED))
        return;

    if (ob->test_bit("Calia",ELDORAL_QUEST_GROUP,ELDORAL_BEAST_QUEST_BIT))
        return;

    set_alarm(0.5, 0.0, &stumble(ob));
}
