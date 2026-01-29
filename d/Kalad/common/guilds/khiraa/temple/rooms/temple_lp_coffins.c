#include "/d/Kalad/defs.h"
#include "/d/Kalad/common/guilds/khiraa/khiraa_defs.h"
#pragma save_binary

inherit "/d/Kalad/room_std";

void
create_room()
{
    set_short("In the Lich's Coffin Room");
    
    set_long("\n   You are in a coffin lined room. The walls are "+
    "lined with many coffins made of black oak. The whole room "+
    "is cast in an eerie red glow that eminates from a large "+
    "orb hovering in the center of the room. A painting of "+
    "a grim skull adorns the cold marble floor under the orb.\n"+
    "    The stench of death and decay is strong. You feel "+
    "that great unholy powers are at work here.\n");

    add_item("coffins","There are the coffins where the warriors "+    
    "of Him come to rest. You see the emblem of the Priesthood "+
    "on them; an S shaped symbol on a grim skull with a staff through it. You "+
    "should type 'start here' so that you may start in this "+
    "room.\n");

    add_item("orb","The orb is not very large, but it emmits a "+
    "dull red glow, giving everything a bloody look to it.\n");
    add_item("walls","The walls are lined with coffins.\n");
    add_item("ceiling","The ceiling is made of black stone and "+
    "it is rather high here.\n");
    add_item("floor","The floor is made of smooth black marble, with "+
    "a large painting of a grim skull in red.\n");
    add_item(({"skull","painting"}),"The painting depicts Him, lord "+
    "of all that is Death.\n");

    INSIDE;
    add_prop(ROOM_I_LIGHT,1);
//    clone_object(KHIRAA_DIR(temple/doors/lpcoffindoor2))->move(TO); 
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
        "of your race. Your membership information has been saved.\n\n" +
        "***************************************************************\n\n");
}

void
init()
{
    ::init();

    set_alarm(1.0, 0.0, &eject_khiraa(this_player()));

//    AA(do_start,start);
}

int
do_start(string str)
{
    NF("Start here perhaps?\n");
    if(str != "here")
        return 0;
    NF("You cannot start here, you are not a Lich.\n");
    if(!IS_LP(TP))
        return 0;
    if(TP->set_default_start_location(KHIRAA_DIR(temple/rooms/temple_lp_coffins)))
        write("From now on, you will start in this room, in your coffin.\n");
    else
        write("For some reason, it failed. Mail guildmaster about it.\n");
    return 1;
}

