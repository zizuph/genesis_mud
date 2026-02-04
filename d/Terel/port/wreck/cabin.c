inherit "/std/room";

#include <stdproperties.h>
#include <macros.h>
#include <ss_types.h>
#include <wa_types.h>
#include <money.h>

#include "/d/Terel/common/terel_defs.h"
#define TP           this_player()
#define TO           this_object()

#define WRECK        "/d/Terel/port/wreck/"
#define BEACH        "/d/Terel/port/beach/"

#define DECK         WRECK + "deck"

public void
reset_room()
{
}

public void
init()
{
    ::init();
}

public void
create_room()
{
    set_short("in the cabin");
    set_long("You are standing in the cabin of the old wreck. " +
             "There is not much left here. Everything of value " +
             "has disappeared. There is an old ladder going " +
             "down.\n");

    add_item(({"wreck"}), "It was a small sailing ship. It looks very old, " +
                          "but it seems to be fairly intact.\n");
                          
    add_item(({"cabin"}), "It is in pretty bad condition. " +
                          "You catch a glimpse of the sky through " +
                          "the ceiling.\n");

    add_item(({"ladder"}), "It looks unsafe.\n");
    
    add_prop(ROOM_I_INSIDE, 1);

    add_exit(DECK,          "east", 0);
    add_exit(WRECK + "d1",  "down", 0);

    reset_room();
}
