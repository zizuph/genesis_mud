/*
 * Equipment Room for the Academy of Elemental Arts in Gelan
 * 
 * Created by Petros, September 2009
 */

#pragma strict_types

#include "defs.h"

inherit SCHOOL_ROOM_BASE;

// Defines
#define WEAPON_RACK     (ACADEMIC_OBJS + "weapon_rack")
#define ARMOUR_RACK     (ACADEMIC_OBJS + "armour_rack")
#define MISC_RACK       (ACADEMIC_OBJS + "misc_rack")

// Prototypes
public void     add_racks();

public void
create_school_room()
{
    set_short("Equipment Room");
    set_long("This room is filled along every wall with various "
        + "equipment used by those who reside in this Academy. Upon "
        + "the northern wall lies a large wooden chest with weapons. Along "
        + "the western wall, you can see a stone rack that contains "
        + "armours. The southern wall has a long glassy shelf that "
        + "seems to hold miscellaneous items.\n\n");
                   
    try_item( ({ "walls", "wall" }),
                "Each wall in this room is filled with something. This "
              + "is a very busy area that is frequently used as "
              + "members of the Academy travel when they are not "
              + "busy studying.\n");

    try_item( ({ "north wall", "northern wall" }),
                "The northern wall is made of marble, like the rest of the "
              + "Academy. Its entire length is occupied by a large "
              + "wooden chest that holds weapons.\n");

    try_item( ({ "west wall", "western wall" }),
                "The western wall holds different kinds of armours that "
              + "can be used by Academics to protect themselves when "
              + "travelling abroad. The stone rack that stretches the "
              + "length of the wall looks rather curious.\n");

    try_item( ({ "south wall", "southern wall" }),
                "The southern wall is a bit more bare compared to the "
              + "other walls. At first glance, you can barely tell "
              + "that there is something that, as the items on the "
              + "glassy shelf just seem to be floating in the air.\n");

    try_item( ({ "east wall", "eastern wall", "east", "arch",
                 "large arch" }),
                "A large arch takes up a large portion of the east "
              + "wall. The arch leads you back into the Hall of "
              + "Peace.\n");

    add_exit(ACADEMIC_SCHOOL + "boardroom", "east"); 
    
    add_racks();   
}

public void
add_racks()
{
    if (!present("_academy_weapons_chest"))
    {
        clone_object(WEAPON_RACK)->move(this_object());
    }
    
    if (!present("_academy_armour_rack"))
    {
        clone_object(ARMOUR_RACK)->move(this_object());
    }
    
    if (!present("_academy_misc_shelf"))
    {
        clone_object(MISC_RACK)->move(this_object());
    }
}
