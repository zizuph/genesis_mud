#include "/d/Kalad/defs.h"
#include "/d/Kalad/common/guilds/khiraa/khiraa_defs.h"
#pragma save_binary

inherit "/d/Kalad/room_std";


void
create_room()
{
    set_short("In a dark coffin");
    
    set_long("\n   You are in a wooden coffin. It is very cramped "+
    "in here, not to mention dark. So very dark.\n\n");

    clone_object(KHIRAA_DIR(temple/doors/coffin_in))->move(TO);  
 
    INSIDE;
    add_prop(ROOM_I_LIGHT,0);
}

void
enter_inv(object ob, object from)
{
    ::enter_inv(ob,from);
    if(ob->query_prop(KHIRAA_JOIN_INITIATE))
        set_alarm(8.0,0.0,"lor",ob);
}

void
lor(object ob)
{
    tell_object(ob,"You feel a sudden chill such as you have never felt "+
    "before!\n");
    set_alarm(4.0,0.0,&tell_object(ob,"All of a sudden, a dark and "+
    "bleak landscape appears before you. The sky is black and the ground "+
    "is a sickly green color that stretches forever in all directions.\n"));
    set_alarm(12.0,0.0,&tell_object(ob,"Slowly, a giant grim skull "+
    "fades into view, hovering above the landscape. You now know that "+
    "you are looking into the Netherworld. And it is He who is "+
    "before you!\n"));
    set_alarm(17.0,0.0,&tell_object(ob,"The giant grim skull softly "+
    "hisses: Fear not, my child of Darkness...\n"));
    set_alarm(21.0,0.0,&tell_object(ob,"The giant grim skull softly "+
    "hisses: You have boldly stepped into a new world. Welcome to my "+
    "world....\n"));
    set_alarm(26.0,0.0,&tell_object(ob,"The giant grim skull softly "+
    "hisses: You are now a warrior of the Netherworld, my trusted "+
    "servant. You shall not fail me. I am with you always....\n"));
    set_alarm(30.0,0.0,"release",ob);
}

void
release(object ob)
{
    tell_object(ob,"The vision slowly fades from view...and you find "+
    "you can now see here.\n");
    ob->add_prop(LIVE_I_SEE_DARK,1);
}

