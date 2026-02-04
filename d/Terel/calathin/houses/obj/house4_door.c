/*
    House4.c main door    
    Tomas 10271999
 */

inherit "/std/door";
#include "/d/Terel/include/Terel.h"

public void
create_door()
{
    ::create_door();

    set_door_id("house4_door");
    set_pass_command(({"n","north"}));
    set_door_name(({"massive door", "door","oak door"}));
    set_door_desc("The door is a massive slab of oak that has been carved with " +
       "knights and mythical beasts doing battle. Set in the center " +
       "of the door is a fine crytal window pane with an etching of a " +
       "sword radiating light.\n");
    set_other_room(CALATHIN_DIR + "houses/house4a");
    set_open(0);
    set_locked(0);
    set_pick(1);
    set_unlock_command("unlock");
}    


