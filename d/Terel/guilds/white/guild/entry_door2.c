/*
    Entry Doors
 */
inherit "/std/door";

#include "/d/Terel/include/Terel.h"

public void
create_door()
{
    ::create_door();

    set_door_id("entry_door");
    set_pass_command(({"s","south"}));
    set_door_name(({"ornate door", "door","north door","grand door"}));
    set_other_room(WHITE + "guild/courtyard");


/* This door is open and not locked */
    set_open(0);
    set_locked(0);
}
