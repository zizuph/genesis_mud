/*
 * /d/Emerald/telberin/arts/minstrel_guild.c
 *
 * This is simply a placeholder. The Minstrel's Guildhall will eventually
 * be located here, east of Cantor's Plzaz in the Arts Quarter of
 * Telberin.
 *
 * Copyright (c) May 2000, by Cooper Sherry (Gorboth)
 *
 * Expanded on by Arman as part of the Minstrel recode, Nov 2019.
 */

inherit "/d/Emerald/std/room";
inherit "/d/Emerald/lib/room_tell";

#include <macros.h>
#include <stdproperties.h>

/* prototypes */
public void    create_emerald_room();
public void    reset_room();

object book;

/*
 * Function name:        create_emerald_room
 * Description  :        set up the room
 */
public void
create_emerald_room()
{
    set_short("the entry to the Outer Hall of the Minstrel's Guild");
    set_em_long("You stand within the entry to the grand Outer Hall of the "
        + "Minstrel's Guild of Telberin. Unparalleled as a school of music, "
        + "the Minstrel's Guild is exclusive in who it allows access to it's "
        + "halls, let alone those it grants training to in the ancient "
        + "Bardic traditions.\n");

    add_item( ({"outer hall", "hall", "grand outer hall", "halls"}),
        "This is the Outer Hall of the Minstrel's Guild of Telberin. Grand "
        + "and inspiring, renown performers travel from far and wide "
        + "to spend time here musing on their musical works or seeking "
        + "sponsorship for training to become a Master Bard of Telan-Ri.\n");

    add_item( ({"entry", "entryway"}), "To your west is the entryway "
        + "to the Minstrel's Guild of Telberin. Only the most renown "
        + "performers are granted access to the Outer Hall of the "
        + "guild.\n");

    add_item( ({"school", "school of music", "guild", "minstrel guild" }),
        "You stand within the Minstrel's Guild of Telberin, one of the "
        + "greatest schools of music in the realms and the halls where "
        + "the acclaimed Bards of Telan-Ri are trained.\n");

    add_exit("/d/Emerald/telberin/arts/cantors_plaza", "west");
    add_exit("/d/Emerald/telberin/arts/minstrel_guild_hall1", "north");
    add_exit("/d/Emerald/telberin/arts/minstrel_guild_hall4", "east");
    add_exit("/d/Emerald/telberin/arts/minstrel_guild_hall6", "south");

    add_prop(ROOM_M_NO_TELEPORT_TO, 1);
    // add_prop(ROOM_S_EXIT_FROM_DESC, "from inside the Minstrel's Guild.");
    add_prop(ROOM_I_INSIDE, 1);

    reset_room();
} /* create_emerald_room */

/*
 * Function name:        reset_room
 * Description  :        
 */

public void
reset_room()
{
    if (!objectp(book))
    {
        setuid();
        seteuid(getuid());
        book = clone_object("/d/Emerald/telberin/obj/minstrel_book");
        book->move(this_object(), 1);
    }
} /* reset_room */
