/*
 * /d/Gondor/anorien/osgiliath/libvault.c
 * Modifications:  
 *   Tigerlily, April 23, 2004: updated scroll reference
 *       for ranger recode
 */

inherit "/d/Gondor/common/room";
#include "/d/Gondor/defs.h"
#include "/sys/stdproperties.h"

object scroll;

public mixed	check_teleport();

create_room()
{
  set_short("A dark little storage room in the Osgiliath library");
  set_long(BSN("This little room seems to have been used for "+
    "storing of important or valuable books and scrolls, judging by the "+
    "heavy iron door you entered through, and the solid stone walls "+
    "of the room. Nothing is left here now, except some ashes on the floor."));
  add_item("walls",BSN("The walls are made of thick grey-white stone."));
  add_item("floor",BSN("The floor is bare, except for the layers of dust "+
    "that have accumulated with the passing years. There is a pile of "+
    "ashes on the floor, that seem to be made from burnt paper."));
  add_item("ashes",BSN("The ashes are probably from burnt paper."));
  add_item(({"books","scrolls"}),BSN("Nothing like that is left now."));
  seteuid(getuid(this_object()));
  add_prop(ROOM_M_NO_TELEPORT, check_teleport);
  clone_object(OSG_DIR+"obj/libvaultin")->move(this_object());
  reset_room();
}

reset_room()
{
    if (!scroll) 
    {
#ifndef NEW_RANGERS_OPEN
    scroll = clone_object(RANGER_DIR+"spells/obj/rest_scroll");
#endif
//else
#ifdef NEW_RANGERS_OPEN
    scroll = clone_object("/d/Gondor/guilds/rangers/spells/obj/rest_scroll");
#endif
    scroll->move(TO, 1);
    }
}


public mixed
check_teleport()
{
    if ( !objectp(TP) )
        return 1;

    if ( ENV(TP) == TO )
        return 0;

    /* never teleport in here -- must get key */
    return "You don't seem to be able to focus on that location.\n";
}
