/*
 * test room base
 * By Finwe, April 2019
 *  
 */

inherit "/std/room.c";
inherit "/d/Shire/std/room/room_tell";
 
#include <stdproperties.h>
#include <macros.h>
#include <language.h>

void
create_test_room() {}


public void 
create_room()
{
    setuid();
    seteuid(getuid());

    set_short("test room");
    set_long("This is a long description for a test room.\n");

    set_room_tell_time(30);
    add_room_tell("A Noldo walks by, acknowledging you.");
    add_room_tell("The smell of clean grass fills the air.");
    add_room_tell("The fragrance of the flowers wafts past you.");
    add_room_tell("The melodic sound of the River Bruinen drifts by.");

    create_test_room();

}

