#pragma save_binary
#pragma strict_types

#include <stdproperties.h>
#include <macros.h>
#include "../guild.h"

inherit SHIRE_ROOM;

void
create_shire_room()
{
    set_short("starting room");
    set_long("This is a big dark hall with rows of beds in it. Every "+
        "warrior from Angmar's army has his own bed here and whenever "+
        "he wishes to, he can sleep here.\n");

    add_item(({"bed", "beds", "warrior", "warriors"}), "Most of the beds are "+
        "empty at the moment but you can see some warriors sleeping here.\n");

    add_prop(ROOM_I_INSIDE,1);  /* This is a real room */

    add_exit(AA_DIR+"rooms/train", "east","@@my_guild_member@@");
//    add_exit(AA_DIR+"rooms/gates", "southwest");
}

int 
start(string str)
{
    NF(CAP(query_verb())+" where?\n");
    if(str != "here") return 0;
    if(IS_MEMBER(TP))
    {
        if(TP->set_default_start_location(MASTER_OB(TO)))
            write("Ok. You will be sleeping here.\n");
        else
            write("There are some problems. Please try again.\n");
        return 1;
    }
    write("No way!!! The owner of the bed would kill you for sure!\n");
    return 1;
}

void
init()
{
    ::init();
    add_action(start,"start");
    add_action(start,"sleep");
}


public int
my_guild_member()
{
    if (this_player()->query_wiz_level())
    {
        return 0;
    }
    else if(TP->query_guild_member(GUILD_NAME)) 
    {
        write("A soldier of the Army snaps to attention as you pass by.\n");
        return 0;
    }
    else
    {
        write("Large orcs step out of the shadows and block you. You are " +
            "no longer a soldier of the Army, and are not welcomed here!\n");
	    return 1;
    }
}