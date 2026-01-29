
/*
 * storage_chamber.c
 *
 * Storage chamber (rack room) for the Spirit Circle of Psuchae Temple
 * 
 *
 * Copyright (C): Jaacar (Mike Phipps), Jul 24, 2003
 *
 */
 
#pragma strict_types
#pragma save_binary

inherit "/std/room";

#include <stdproperties.h>
#include <macros.h>

#include "defs.h"

#define DONATION_LOG "/d/Calia/log/spirit_circle/donation_log"

void
reset_room()
{

}

void
create_room()
{
    set_short("Storage chamber");
    set_long("You are in the storage chamber. Here you see a "+
        "weapon chest, an armour rack and a shelf. Each of them "+
        "are to hold things for you or your fellow Circle members "+
        "when you are not travelling the realms. The statue chamber "+
        "is back to the east. Above the racks is a small sign and a "+
        "scroll.\n");
    
    IN;
    add_prop(ROOM_M_NO_ATTACK,"You cannot attack in here, you are in a "+
        "sacred place!\n");
    add_prop(ROOM_M_NO_MAGIC_ATTACK,"You cannot attack in here, you are in "+
        "a sacred place!\n");

    add_item(({"sign","small sign"}),"There is a small sign above the "+
        "racks that you could read.\n");
    add_item("scroll","There is a scroll on the wall that you could read.\n");
    add_item("floor", "The floor is made from the same plain grey stone "+
      "as the walls and ceiling are made from.\n");
    add_item(({"wall","walls"}), "The walls are very plain and made out "+
      "of grey stones placed together.\n");
    add_item("ceiling", "The ceiling is made of the same plain grey stone "+
      "as the walls and floor are made from.\n");
    add_item("north wall", "The north wall is inset with a thin glass "+
      "panel.  As you stand before the panel, you see a reflection of "+
      "your features in its highly polished surface.\n");
    add_item("reflection", "Your reflection is quite clear in the glass, "+
      "though you must shift slightly in order to see yourself clearly "+
      "around the inscription which has been etched in the glass.\n");
    add_item("inscription", "The inscription reads:\n\n"+
      "The first peace, which is the most important, "+
      "is that which comes within the souls of people "+
      "when they realize their relationship, "+
      "their oneness, with the universe and all its powers, "+
      "and when they realize that at the center "+
      "of the universe dwells Spirit, "+
      "and that this center is really everywhere, it is within each of us. "+
      "This is the real peace, and the others are but reflections of this.\n\n"+
      "The second peace is that which is made between two individuals, "+
      "and the third is that which is made between two nations. "+
      "But above all you should understand that there can never "+
      "be peace between nations until there is known that true peace, "+
      "which, as I have often said, is within the souls of men.\n");
    
    add_exit(SPIRIT_TEMPLE+"statue_chamber","east",0,1);

    clone_object(SPIRIT_OBJECTS+"weapon_rack")->move(TO);
    clone_object(SPIRIT_OBJECTS+"armour_rack")->move(TO);
    clone_object(SPIRIT_OBJECTS+"misc_shelf")->move(TO);
    clone_object(SPIRIT_OBJECTS+"garbage_bin")->move(TO);
    clone_object(SPIRIT_NPCS+"misc_clerk")->move(TO);

}

int
do_read(string str)
{
    if (!str)
    {
        NF("Read what?  The sign maybe? Or the scroll? <read sign> <read "+
           "scroll>\n");
        return 0;
    }

    if (str == "sign")
    {
        write("The sign reads:\n  You may buy component pouches, herb jars, "+
            "wraps for herbs, silver ingots, sheathes for knives, gloves "+
            "for herbing, lanterns and oil.\n\n");
        return 1;
    }

    if (str == "scroll")
    {
        write("The scroll reads:\n");
        seteuid(getuid());
        tail(DONATION_LOG);
        return 1;
    }

    NF("Read what?  The sign maybe? Or the scroll? <read sign> <read "+
        "scroll>\n");
    return 0;
}

void
init()
{
    ::init();
    add_action(do_read,"read");
}
