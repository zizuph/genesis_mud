/*
 *  /w/novo/open/auction/store_room.c
 *
 *  This is the store room, for holding the NPC during a quest.
 *
 *  Created March 2008, by Novo
 */
#pragma  strict_types

inherit "/std/room";

#include <cmdparse.h>
#include <language.h>
#include <macros.h>
#include <stdproperties.h>
#include <time.h>

#include "../defs.h"


void
create_room()
{

    ::create_room();
    
    set_short("Store room");
    
    set_long("This is a temporary store room.  No player should be "+
      "here.\n");
    
    add_prop(ROOM_I_INSIDE,1);

}