/*
 *  Shapeshift Closet
 *
 *  Holding areas for player objects while they are in use.
 *
 *  Created by Eowul, November 2008
 *  Modified by Petros, May 2012 to adapt to new Genesis Magic System
 *
 */
 
inherit "/std/room";

void create_room() 
{
    set_short("Shapeshift Holding Area");
    set_long("This is the place where the remains of shapeshifted "
        + "players go once they have been taken over. Should you "
        + "find yourself in this place, then you should commune "
        + "a wizard to get yourself out.\n");
}