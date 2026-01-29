/*
 * /d/Kalad/common/wild/pass/underdark/dark_dom.c
 * Purpose    : inherit for Dark Dominion rooms
 * Located    : Only inheritted
 * Created By : Distilled by Nikklaus, Aug'97, from Antharanos's rooms
 * Modified By:
 *    Toby, 971014 (fixed typo in exa stone)
 *    Fysix, X-mas 1997, removed the bugging /std/room inherit.
 */
#pragma strict_types

inherit "/d/Kalad/room_std";

#include "/d/Kalad/defs.h"
#include <stdproperties.h>

/* Note:  Redefine create_dark_dom() and create_tunnel() in that
 * if it's one of the tunnel rooms. To use the long descrip defined
 * here:
 * set_long(long() + "<added room description, including directions>\n");
 *  --Nikklaus, Aug'97
 */

void create_dark_dom() { }

public nomask void
create_room()
{
    ::create_room();
    set_short("Dark Dominion");
    add_prop(ROOM_I_INSIDE,1);
    add_prop(ROOM_M_NO_TELEPORT,1);
    remove_prop(ROOM_I_LIGHT);
    set_short("Dark Dominion");
    set_long("You are within the confines of the Dark Dominion, in "+
      "the lightless land below the world of men. "+
      "Dark stone surrounds you from all directions, seeming to weigh down "+
      "upon you like a physical weight. "+
      "An oppressive silence hangs in the air, as dense as the stone "+
      "around you.\n");
    set_noshow_obvious(1);

    create_dark_dom();
}

public void
create_tunnel()
{
    set_long(long()+ "Rough granite forms the jagged passageways "+
      "tunnelling through the rock. ");

    add_item(({"tunnel", "passage", "stone"}),
      "The rough uncut stone indicates this passage as a "+
      "natural phenomenon.\n");
    add_item(({"dark stone", "stone"}),
      "The entire tunnel is made out of it.\n");
    add_item(({"silence", "air"}),
      "It surrounds you with black stillness.\n");
}

/*
 * Function name : cave_block
 * Description   : General exit vbfc for temporarily caved in passages
 */
public int
cave_block()
{
    write("The way is blocked by a cave-in.\n");
    return 1;
}
