/*
   Modifications: Added enter_env to boot non-members 
                  from the starting room. -- Tomas November 2017
*/


#pragma save_binary
#pragma strict_types

#include <stdproperties.h>
#include <macros.h>
#include "../guild.h"



inherit SHIRE_ROOM;

static int alarm;

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


void
do_whispers()
{  
    if (AA_COUNCIL_OBJ->no_captain() == 1)
    {
        this_player()->catch_tell("\n\nYou hear a whisper from the "
        +"Emissary of the Dark Lord, saying: The Captain of the Army "
        +"of Angmar is gone! Go to the old court room immediately!\n\n");    
    
        return;   
    }
        
    return;
}


void
enter_inv(object ob, object from)
{
    ::enter_inv(ob, from);
    
    if (!alarm && !living(ob))
        alarm = set_alarm(20.0, 0.0, "tidy_room");
    
    if(!living(ob) || ob->query_wiz_level() || 
        IS_MEMBER(ob) || ob->query_npc())
        
        set_alarm(1.0, 0.0, &do_whispers());
        
        return;
    
    ob->command("look");
    ob->catch_msg("A bunch of warriors come screaming at you!\n"+
        "They grab you and throw you out of their starting room.\n");
    tell_room(AA_DIR+"rooms/g1", QCTNAME(ob)+" comes flying from the southeast and "+
        "lands in one heap on the floor.\n");
    ob->move(AA_DIR+"rooms/g1");
    tell_room(TO, QCNAME(ob)+" arrives.\n"+
        "A bunch of warriors come screaming at "+QTNAME(ob)+"!\n"+
        "They grab "+HIM(ob)+" and throw "+HIM(ob)+" out.\n");
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



