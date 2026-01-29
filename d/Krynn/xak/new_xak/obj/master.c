/*
 *
 */
#pragma save_binary
#pragma strict_types
#pragma no_clone

inherit "/std/object";

#include "../local.h"
#include RND_MEET
#include <macros.h>

static string gPack_room;

static void
hide_bupu_pack()
{
    if (random(2))
        gPack_room = HALL + "southcrypt" + (random(1) + 2);
    else
        gPack_room = HALL + "northcrypt" + (random(4) + 2);
}

public void
create_object()
{
    seteuid(getuid());
    set_short("hole in Xak Tsaroth");
    hide_bupu_pack();
}

public int
query_bupu_pack(object ob)
{
    if (MASTER_OB(ob) == gPack_room)
    {
        clone_object(OBJ + "bupu_bag")->move(ob);
        gPack_room = 0;
	return 1;
    }
    return 0;
}

public string
query_npc_file(string table)
{
    return GET_RANDOM_NAME(table);
}

public mixed
debug()
{
    return ([ "bupu pack" : gPack_room ]);
}




