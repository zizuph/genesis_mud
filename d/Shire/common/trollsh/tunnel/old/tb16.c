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

inherit TUNNEL_BASE;
//int clone_trolls = random(2);

static object grothaur, guard;

void
create_tunnel_room()
{
    set_long("@@tunnel_desc2@@");
    add_my_desc("The tunnel appears well used. It runs " +
        "southwest and northeast.\n");

    add_exit(TUN_DIR + "tb25", "northeast");
    add_exit(TUN_DIR + "tb15", "west");


    reset_shire_room();
}

void reset_shire_room()
{

    setuid();
    seteuid(getuid());

/*
    if (clone_trolls == 1) // if 1 make trolls, else no trolls
    {
        make_trolls();     
    }
    clone_trolls = random(2);
*/
/*
    if(!objectp(grothaur))
    {
        grothaur = clone_object(NPC_DIR + "grothaur");
        grothaur->move(TO);
    }
*/
// set guards for grothaur

        guard = clone_object(NPC_DIR + "newtroll");
        guard->move(TO);
 
        guard = clone_object(NPC_DIR + "newtroll");
        guard->move(TO);

        guard = clone_object(NPC_DIR + "newtroll");
        guard->move(TO);




}

