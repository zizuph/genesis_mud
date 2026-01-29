#include "/d/Kalad/defs.h"
#include "/d/Kalad/common/guilds/khiraa/khiraa_defs.h"
#pragma save_binary

inherit "/d/Kalad/room_std";

void
create_room()
{
    set_short("In the Death Knight Coffin Room");
    
    set_long("\n   You find yourself in a dark and gloomy room. The "+
    "air is filled with the eternal stench of death and decay. There "+
    "is something very ancient and magical here, you can feel it "+
    "in your soul. The walls are lined with old black coffins, and "+
    "the ceiling is vaulted up high. The floor is made of smooth "+
    "black marble.\n"+
    "   In the center of the floor, you see a hole filled with "+
    "strange, green glowing liquid. Above the liquid, a lone "+
    "spectre hovers, its eternal red eyes keeping vigil.\n\n");
    add_item("coffins","There are the coffins where the warriors "+
    "of Him come to rest. You see the emblem of the Knighthood "+
    "on them; a grim skull with a sword through the black. You "+
    "should type 'start here' so that you may start in this "+
    "room.\n");
    add_item("walls","The walls are lined with coffins.\n");
    add_item("ceiling","The ceiling is made of black stone and "+
    "it is rather high here.\n");
    add_item("floor","The floor is made of smooth black marble, with "+
    "a strange hole in the center.\n");
    add_item(({"hole","liquid"}),"The hole is filled with eerie "+
    "glowing liquid that casts a greenish light around the room. "+
    "Over it, hovers a black spectre with blazing red eyes.\n");
    add_item(({"spectre","black spectre"}),"The spectre stands un"+
    "moving and unblinking over the pool.\n");   
    INSIDE;
    add_prop(ROOM_I_LIGHT,1);
    clone_object(KHIRAA_DIR(temple/doors/dkcoffindoor2))->move(TO);
}

#include <ss_types.h>

void
eject_khiraa(object player)
{
    setuid();
    seteuid(getuid());

    write_file("/d/Kalad/common/guilds/khiraa/closing.log",
        sprintf("%s %-11s OCC %8d LAY %8d\n",
        ctime(time()),
	capitalize(player->query_real_name()),
	player->query_acc_exp(SS_OCCUP),
	player->query_acc_exp(SS_LAYMAN)));

    player->clear_guild_stat(SS_OCCUP);
    player->set_guild_pref(SS_OCCUP, 0);
    player->clear_guild_stat(SS_LAYMAN);
    player->set_guild_pref(SS_LAYMAN, 0);

    player->set_default_start_location(player->query_def_start());

    player->move_living("X", "/d/Kalad/common/guilds/khiraa/temple/rooms/temple_circle");

    player->catch_tell("\n" +
        "***************************************************************\n\n" +
	"You are now free of all ties with the Khiraa. The next time you\n" +
	"enter the realms, you will find yourself in the start location\n" +
        "of your race.\n\n" +
        "***************************************************************\n\n");
}

void
init()
{
    ::init();

    // set_alarm(1.0, 0.0, &eject_khiraa(this_player()));

//    AA(do_start,start);
}

int
do_start(string str)
{
    NF("Start here perhaps?\n");
    if(str != "here")
        return 0;
    NF("You cannot start here, you are not a Death Knight.\n");
    if(!IS_DK(TP))
        return 0;
    if(TP->set_default_start_location(KHIRAA_DIR(temple/rooms/temple_dk_coffins)))
        write("From now on, you will start in this room, in your coffin.\n");
    else
        write("For some reason, it failed. Mail guildmaster about it.\n");
    return 1;
}

