/*
 * Equipment Room for the Elemental Worshippers of Calia
 * 
 * Created by Petros, April 2010
 */

#pragma strict_types

#include "defs.h"

inherit TEMPLE_ROOM_BASE;

// Defines
#define WEAPON_RACK     (ELEMENTALIST_OBJS + "weapon_rack")
#define ARMOUR_RACK     (ELEMENTALIST_OBJS + "armour_rack")
#define MISC_RACK       (ELEMENTALIST_OBJS + "misc_rack")
#define GARBAGE_BIN     (ELEMENTALIST_OBJS + "garbage_bin")

// Prototypes
public void     add_racks();

public void
create_temple_room()
{
    set_short("Elemental Worshippers Equipment Room");
    set_long("This is the equipment room for the Elemental Worshippers of "
             + "Calia. Sometimes called the storage chamber, you can see that "
             + "it certainly lives up to its name. Here you see a weapon "
             + "chest, an armour rack, and a shelf to hold miscellaneous "
             + "items. Each storage container can hold things for you while "
             + "you or your fellow Elemental Worshippers are not traveling "
             + "the realms. To the northeast you see the central stairwell "
             + "that leads back to the main Temple floor.\n\n");

    try_item( ({ "equipment room", "room", "storage chamber", "chamber" }),
              "You look more closely at the contents of the storage chamber, "
              + "but you don't find anything that you didn't already see "
              + "before.\n");

    try_item( ({ "central stairwell", "stairwell", "northeast" }),
              "To your northeast is the central stairwell. It looks like "
              + "the only way out of the storage chamber.\n");
                   
    add_exit(ELEMENTALIST_TEMPLE + "stairwell2", "northeast");
    

    add_racks();   
}

public void
add_racks()
{
    if (!present("_temple_weapons_chest"))
    {
        clone_object(WEAPON_RACK)->move(this_object());
    }
    
    if (!present("_temple_armour_rack"))
    {
        clone_object(ARMOUR_RACK)->move(this_object());
    }
    
    if (!present("_temple_misc_shelf"))
    {
        clone_object(MISC_RACK)->move(this_object());
    }
    if (!present("_temple_garbage_bin"))
    {
        clone_object(GARBAGE_BIN)->move(this_object());
    }
}
