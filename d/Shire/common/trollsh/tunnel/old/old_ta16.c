/*
 * Tunnel beneath the Trollshaws
 * By Finwe, August 2001
 */
 

#pragma strict_types

inherit "/d/Shire/std/room.c";

#include "/d/Shire/sys/defs.h"
#include "local.h"
#include <stdproperties.h>
#include <macros.h>
#include <language.h>

#define MAX_TROLLS 3


inherit TUNNEL_BASE;
static object grothaur;
static object *trolls  = allocate(MAX_TROLLS);

void
make_trolls();

void
reset_room()
{
  make_trolls();
}

void
create_tunnel_room()
{
    set_long("@@tunnel_desc6@@");
    add_my_desc("The tunnel becomes wider here. Many exits lead " +
        "off in various directions. The main ones lead north, " +
        "west, and southeast.\n");

    add_exit(TUN_DIR + "ta24", "north");
    add_exit(TUN_DIR + "ta15", "west");
    add_exit(TUN_DIR + "ta17", "southeast");

    reset_room();
}


void
make_trolls()
{
    int index;

    setuid();
    seteuid(getuid());

    /* Loop over all elements in the array. */
    for(index = 0; index < MAX_TROLLS; index++)
    {
        if (!objectp(trolls[index]))
        {
            trolls[index] = clone_object(NPC_DIR + "newtroll");
            trolls[index]->move(TO);
 
        }
    }

   if(!objectp(grothaur))
    {
        grothaur = clone_object(NPC_DIR + "grothaur");
        grothaur->move(TO);
    }
 
}
