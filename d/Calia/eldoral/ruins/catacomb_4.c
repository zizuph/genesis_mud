/*
 * catacomb_4.c
 *
 * This room is a fairly typical catacomb room, except for the fact
 * that a special door leads north into the grotto where Firestorm,
 * the dragon that 'gives' the Eye of the Beast and Calian Sup. Guru
 * Quests lives. The door is opened by taking the sword from the
 * pedestal in the room south of here (catacomb_hub.c) and raising
 * it above your head here.
 *
 * Khail - Feb 12/96
 */
#pragma strict_types

#include "defs.h"

inherit STDROOM;

int door_open,
    memory_alarm_id;

public void reset_room();

/*
 * Function name: check_pass
 * Description  : VBFC'd exit blocking function. Prevents players
 *                from using this exit until the north 'door' is
 *                opened.
 * Arguments    : n/a
 * Returns      : 0 - Player may pass.
 *                1 - Player can't pass.
 */
public int
check_pass()
{
    if (!door_open)
    {
        write("You cannot pass through solid stone!\n");
        return 1;
    }
    return 0;
}

/*
 * Function name: check_vis
 * Description  : VBFC'd exit visibility function. Prevents players
 *                from seeing a north exit until the 'door' is
 *                opened.
 * Arguments    : n/a
 * Returns      : 1 - Exit invis.
 *                0 - Exit vis.
 */
public int
check_vis()
{
    return !door_open;
}

/*
 * Function name: exa_door
 * Description  : VBFC'd add_item desc for the door.
 * Arguments    : n/a
 * Returns      : A string describing the door.
 */
public string
exa_door()
{
    if (!door_open)
        return "It quite effectively blocks further passage " +
            "to the north, and aside from a carving of " +
            "some sort on its face, is completely " +
            "featureless.\n";
    else
        return "The door has withdrawn almost completely into " +
            "the wall, opening the way north into a dark " +
            "passage.\n";
}

/*
 * Function name: create_room
 * Description  : Turns this object into a room.
 * Arguments    : n/a
 * Returns      : n/a
 */
public void
create_room()
{
    set_short("a narrow passageway");
    set_long("You have entered a narrow passageway that leads " +
        "north and south beneath " + CASTLE_NAME + ", somewhere. " +
        "At least, it appears to run north and south, but to the " +
        "north, a stone door or gate of some sort is firmly shut " +
        "across the path, with no apparent means of opening nor " +
        "closing it. In fact, if it wasn't for the fact that " +
        "the door is the largest single block visible in the floor, " +
        "ceiling or walls, you'd think this was a dead end. " +
        "There aren't even any scratches or trails through the " +
        "dust that are usually evident with secret doors.\n\n");

    add_item(({"ceiling", "roof"}),
        "The ceiling appears to be nothing more than a " +
        "number of stone slabs laid across the tops of " +
        "the walls.\n");
    add_item(({"walls"}),
        "Walls flank either side of this passage, formed " +
        "by large blocks of cut grey stone. The only exception " +
        "is the north wall, which looks suspiciously like " +
        "a large stone door.\n");
    add_item(({"floor", "ground"}),
        "The floor consists of a number of small blocks " +
        "of stone, almost like cobblestones, closely fit " +
        "together. Their smaller size seems to be keeping " +
        "them in better shape than most of the stone " +
        "floors in the ruins.\n");
    add_item(({"door", "gate", "stone door"}),
        VBFC_ME("exa_door"));
    add_item(({"carving", "door face", "face of door"}),
        "The carving itself is ancient, and time has " +
        "taken its toll upon it, leaving little " +
        "trace of the original carving except for a " +
        "faint outline. It looks to be a figure of " +
        "a man, with a polearm, or a spear, or maybe " +
        "a sword, raised above his head.\n");

    add_prop(OBJ_S_WIZINFO, "This room is a passage " +
        "to the dragon, Firestorm, in the grotto " +
        "below. To pass it, a player requires a special " +
        "sword, /d/Calia/eldoral/objects/s_sword.c, " +
        "which the player raises to pass this door. " +
        "The sword just calls pass_door(player) in " +
        "this room.\n");
    DARK;
    INSIDE;
    add_prop(ROOM_I_NO_CLEANUP, 1);

    add_exit(RUIN + "catacomb_hub", "south");
    add_exit(RUIN + "catacomb_8", "north", VBFC_ME("check_pass"),
        1, VBFC_ME("check_vis"));

    reset_room();
}

/*
 * Function name: close_the_door
 * Description  : Closes the passage to the north.
 * Arguments    : n/a
 * Returns      : n/a
 */
public void
close_the_door()
{
    if (door_open)
    {
        tell_room(TO, "A stone door slides back into place, " +
            "closing off the passage to the north.\n");
        door_open = 0;
    }
    (RUIN + "catacomb_8")->close_the_door();
}
     
/*
 * Function name: open_the_door
 * Description  : Opens up the passage to the north.
 * Arguments    : second - Optional arg called when the door is
 *                         opened from the other side.
 * Returns      : n/a
 */
public varargs void
open_the_door(int second = 0)
{
    seteuid(getuid());

    if (!door_open)
    {
        tell_room(TO, "Suddenly, the door blocking the way " +
            "north begins rumbling to one side, opening the " +
            "way into a dark passage beyond.\n");
        door_open = 1;
        set_alarm(20.0, 0.0, close_the_door);
    }
    if (!second)
    {
        (RUIN + "catacomb_8")->open_the_door(1);
    }
}
 
/*
 * Function name: pass_door
 * Description  : 'opens' the door north into the grotto. Called by
 *                the sword taken from the pedestal to the south 
 *                when players raise it over their heads.
 * Arguments    : ob - Object pointer to the player raising the 
 *                     sword.
 * Returns      : n/a
 */
public void
pass_door(object ob)
{
  /* Make sure the player is in this room. */
    if (!ob || !present(ob, TO))
        return 0;

    open_the_door();
}

public int
query_dragon_door_room()
{
    return 1;
}

public void
reset_room()
{
    close_the_door();
}

public void
remember_player_with_sword(object ob)
{
    tell_object(ob, "You feel a strange presense wash over " +
        "you, and oddly enough see an image of yourself " +
        "in your mind, holding once again the ancient " +
        "shimmering longsword above your head.\n");
    pass_door(ob);
}

public void
enter_inv(object ob, object from)
{
    ::enter_inv(ob, from);

    if (!interactive(ob))
        return;

    if (from == find_object(RUIN + "catacomb_hub") &&
        !present(SHIMMERING_SWORD_NAME, ob) &&
        ob->test_bit("Calia", ELDORAL_QUEST_GROUP,
        ELDORAL_SWORD_QUEST_BIT))
    {
        if (get_alarm(memory_alarm_id))
            return;
        else
            memory_alarm_id = set_alarm(2.0, 0.0,
                &remember_player_with_sword(ob));
    }
}
        
