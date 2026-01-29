/* Filename    : /d/Genesis/new/start/dwarf/town/std_town_room.c
 * Author      : Nuf
 * Description : base room for the dwarf town
 */

#pragma strict_types

inherit "/std/room";

/* Prototypes */
public nomask void create_room();
public void create_town_room();

/* Function name: create_town_room
 * Purpose      : set up a town room
 * Arguments    :
 * Returns      :
 */
public void
create_town_room()
{
}

/* Function name: create_room
 * Purpose      : set up the room
 * Arguments    :
 * Returns      :
 */
public nomask void
create_room()
{
    ::create_room();
    create_town_room();
}

