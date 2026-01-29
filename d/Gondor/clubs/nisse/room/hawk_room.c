/*
 *  /d/Gondor/clubs/nisse/room/hawk_room.c
 *
 *  The room, where the hawk moved in when it delivers a message.
 *  It is not used nowadays, because the hawks are not messengers anymore.
 *
 *  Deagol, March 2003
 */

inherit "/std/room";

void
create_room()
{
    ::create_room();
    
    set_short("Temporary hawk room");
    set_long("Temporary hawk room.\n");
}
