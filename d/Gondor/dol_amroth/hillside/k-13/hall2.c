/*
 * hall2.c
 * 
 * Skippern 20(c)02
 *
 * The living room.
 */
#include "../../defs.h"
inherit DOL_STD + "inside";
inherit "/d/Gondor/open/room_chairs/room_chairs";

#include "/d/Gondor/open/room_chairs/room_chairs.h"

#include <macros.h>
#include <stdproperties.h>

#define CHESTERFIELD        "comfortable chesterfield"

static object    winer;

/* Prototypes */
public void     leave_inv(object ob, object dest);
public string   look_at(string arg);

/* Code */
void
create_inside()
{
    set_short("a living room");
/**
 * @TODO: Improve description
 */
    set_long("This is a lavish furnished living room.\n");
    
    add_chair(CHESTERFIELD, "[down] [in] [the] [deep] [dark] [comfortable] [chesterfield] 'chair'", 1, "in");

    add_exit(DOL_HILLS + "k-13/hall1", "south", 0, 1);

    reset_room();
}

void
init()
{
    ::init();
    init_room_chairs();
}

void
reset_room()
{
    if (!present(winer)) {
		winer = clone_object(DOL_NPC+"k13-winer");
		winer->move(this_object());
	}
}

public void
leave_inv(object ob, object dest)
{
    ::leave_inv(ob, dest);
    leave_inv_room_chairs(ob, dest);
}

public string
look_at(string arg)
{
    switch (arg)
    {
        case CHESTERFIELD
            return "This deep comfortable chesterfield chair looks like "+
                "a good place to sit having your evening smoke. It is " +
                "made from dark leather, studded with dark brown buttons. "+
                sitting_on_chair(CHESTERFIELD, this_player(), 0) + "\n";
    }
}