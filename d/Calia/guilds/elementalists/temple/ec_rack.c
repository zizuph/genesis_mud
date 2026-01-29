/*
 * Equipment Room for the Elemental Clerics of Calia
 * 
 * Created by Petros, April 2010
 */

#pragma strict_types

#include "defs.h"

inherit TEMPLE_ROOM_BASE;

// Defines
#define WEAPON_RACK     (ELEMENTALIST_OBJS + "ec_weapon_rack")
#define ARMOUR_RACK     (ELEMENTALIST_OBJS + "ec_armour_rack")
#define MISC_RACK       (ELEMENTALIST_OBJS + "ec_misc_rack")
#define GARBAGE_BIN     (ELEMENTALIST_OBJS + "garbage_bin")
#define GEM_CRUSHER     (ELEMENTALIST_OBJS + "gem_crusher")
#define DONATION_LOG    "/d/Calia/log/elementalists/donation_log"

// Prototypes
public void     add_racks();
public object   sphere = 0;

public void
create_temple_room()
{
    set_short("Elemental Clerics Equipment Room");
    set_long("This is the equipment room for the Elemental Clerics of "
             + "Calia. Sometimes called the storage chamber, you can see that "
             + "it certainly lives up to its name. Here you see a weapon "
             + "chest, an armour rack, and a shelf to hold miscellaneous "
             + "items. Each storage container can hold things for you while "
             + "you or your fellow Elemental Clerics are not traveling "
             + "the realms. Above the shelf you see a scroll. To the east "
             + "you see the central stairwell "
             + "that leads back to the second floor of the Temple. "
             + "You also see a portal on the north wall.\n\n");

    try_item( ({ "equipment room", "room", "storage chamber", "chamber" }),
              "You look more closely at the contents of the storage chamber, "
              + "but you don't find anything that you didn't already see "
              + "before.\n");

    try_item( ({ "central stairwell", "stairwell", "east" }),
              "To your east is the central stairwell. It looks like "
              + "the only way out of the storage chamber.\n");
                     
    try_item(({"portal"}),"When you look at the portal, you see the old "+
        "Spirit Circle Temple sleeping chamber.\n");
    
    try_item(({"scroll"}),"There is a scroll on the wall above the shelf "+
        "that you could read.\n");               
    add_exit(ELEMENTALIST_TEMPLE + "stairwell3", "east");
    add_exit("/d/Calia/guilds/scop/temple/startroom","north");
    

    add_racks();
    reset_room();   
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

int
do_read(string str)
{
    if (!str)
    {
        NF("Read what?  The scroll maybe?\n");
        return 0;
    }

    if (str == "scroll")
    {
        write("The scroll reads:\n");
        seteuid(getuid());
        tail(DONATION_LOG);
        return 1;
    }

    NF("Read what?  The scroll maybe?\n");
    return 0;
}

void
init()
{
    ::init();
    add_action(do_read,"read");
}


public void
reset_room()
{
    ::reset_room();
    setuid(); 
    seteuid(getuid());
    // Clone the sphere for cleric conversion from scop
    if (!objectp(sphere))
    {
        sphere = clone_object(ELEMENTALIST_OBJS + "sphere_occ");
        sphere->move(this_object(), 1);        
    }
}

