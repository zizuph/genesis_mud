/* This is the start room for the PoT.
 *
 * This will be overwritten with ../../temple_v2/lvl2/dorm.c when the
 * temple is ready to reopen.
 */

#pragma strict_types

inherit "/std/room";

void
create_room()
{
    set_short("The sleeping quarters");
    set_long("This is a large chamber sub-divided into smaller sections " +
        "by thin walls but all sections are open towards the centre of " +
        "the room. In each little section stands a single bed neatly " +
        "made and to the north is an open archway.\n");
}
