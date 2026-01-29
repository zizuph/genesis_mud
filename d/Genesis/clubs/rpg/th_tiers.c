/*
 * The actors club theatre tiers
 */
#pragma strict_types

inherit "/std/room";

#include "actor.h"
#include <stdproperties.h>

public nomask void
create_room()
{
    set_short("Tiers");
    set_long("  You're in the theatre proper now, all around you are tiers of seats. Just pick any one. The stage is further down, covered with a curtain.\n\n");

    add_item(({ "seat", "seats" }), "The seats are not padded and they are worn with age and neglect. Whatever reasons people have for coming here, physical comforts is *not* it.\n");
    add_item("stage", "The experienced eye (yours, of course :) can see that this stage has *everything*, multiple backgrounds, collapsable floor, platforms that can be lowered into the stage... everything...\n");
    add_item("curtain", "The curtain stretching across the stage is of a rich, probably very heavy, dark red fabric. The pattern of the masks in white and black silk is sewn into it, enhanced by the background red.\n");

    add_prop(ROOM_I_INSIDE, 1);
    add_prop(ROOM_I_TYPE, ROOM_NORMAL);

    add_exit("/d/Genesis/clubs/rpg/th_hall", "east");
    add_exit("/d/Genesis/clubs/rpg/th_stage", "west");
}
