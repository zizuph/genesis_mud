/*
 * Equipment Room for the Elemental Clerics of Calia
 * 
 * Created by Petros, April 2010
 */

#pragma strict_types

#include "defs.h"

inherit TEMPLE_ROOM_BASE;

// Defines
#define WEAPON_RACK     (ELEMENTALIST_OBJS + "ec_weapon_rack_beta")
#define ARMOUR_RACK     (ELEMENTALIST_OBJS + "ec_armour_rack_beta")
#define MISC_RACK       (ELEMENTALIST_OBJS + "ec_misc_rack_beta")
#define GARBAGE_BIN     (ELEMENTALIST_OBJS + "garbage_bin")
#define GEM_CRUSHER     (ELEMENTALIST_OBJS + "gem_crusher")

// Prototypes
public void     add_racks();
public void load_board();

public void
create_temple_room()
{
    set_short("Elemental Clerics Beta Testers Equipment Room");
    set_long("This is the equipment room for the Elemental Clerics of "
             + "Calia beta testers. Sometimes called the storage chamber, you can see that "
             + "it certainly lives up to its name. Here you see a weapon "
             + "chest, an armour rack, and a shelf to hold miscellaneous "
             + "items. Each storage container can hold things for you while "
             + "you or your fellow Elemental Clerics are not traveling "
             + "the realms. To the southeast you see the central stairwell "
             + "that leads back to the second floor of the Temple.\n\n");

    try_item( ({ "equipment room", "room", "storage chamber", "chamber" }),
              "You look more closely at the contents of the storage chamber, "
              + "but you don't find anything that you didn't already see "
              + "before.\n");

    try_item( ({ "central stairwell", "stairwell", "east" }),
              "To your east is the central stairwell. It looks like "
              + "the only way out of the storage chamber.\n");
              
    try_item(({"portal"}),"When you look at the portal, you see the old "+
        "Spirit Circle Temple study.\n");
                   
    add_exit(ELEMENTALIST_TEMPLE + "stairwell3", "southeast");
    add_exit(ELEMENTALIST_TEMPLE + "testing/ec_test_room", "testroom");

    add_racks();
    load_board();   
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
    if (!present("_temple_gem_crusher"))
    {
        clone_object(GEM_CRUSHER)->move(this_object());
    }
}

public void
load_board()
{
    object bb;
    seteuid(getuid(this_object()));
    bb = clone_object(ELEMENTALIST_OBJS + "beta_board");
    bb->move(this_object());
}
 
public int 
query_prevent_snoop()
{
    return 1;
}