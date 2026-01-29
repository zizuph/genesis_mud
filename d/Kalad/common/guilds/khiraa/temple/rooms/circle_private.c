#include "/d/Kalad/common/guilds/khiraa/khiraa.h"
#include "/d/Kalad/common/guilds/khiraa/default.h"
#pragma save_binary

inherit "/d/Kalad/room_std";

void
create_room()
{
    set_short("Private Chambers of the Circle");
    set_long("\n   You have entered a small chamber of black stone "+
    "that glows with an eerie green light. The floor is covered "+
    "with a giant mosaic of red grim skull. The ceiling is low, and "+
    "an atmosphere of great evil and darkness prevades the room.\n"+
    "   This is the private chambers of the Khiraa Circle. This is "+
    "where secret discussions and policy enforcement takes place. "+
    "On the wall, you notice a mirror of pure black liquid.\n\n");

    add_item("skull","It is a large painting of the Horror.\n");

    add_item("mirror","@@mirror@@");
    
    add_item("ceiling","The ceiling is made of solid black stone.\n");
    add_item("walls","The walls are made of dark black stone, and "+
    "they seem to glow with a magical eerie green light.\n");
    add_item("floor","The floor is of solid polished black marble.\n");
   
    INSIDE;
    clone_object(KHIRAA+"temple/obj/kcboard")->move(TO);
    add_prop(ROOM_I_LIGHT,1);
    add_exit(KHIRAA+"temple/rooms/temple_circle","south",0,-1);
}

int
do_seal(string str)
{
    object oroom,eroom, *obs;
    int i;
    obs = users();
    NF("Seal what? The temple entrance?\n");
    if(str != "temple entrance")
        return 0;
    call_other("/d/Kalad/common/raum/cdlair1/cd01","??");
    call_other("/d/Kalad/common/raum/cdlair1/h02","??");
    oroom = find_object("/d/Kalad/common/raum/cdlair1/cd01");
    eroom = find_object("/d/Kalad/common/raum/cdlair1/h02");
    if(oroom->query_blocked() == 1)
    {
        write("The entrance has already been blocked.\n");
        return 1;
    }
    oroom->set_blocked(1);
    eroom->set_blocked(1);
    tell_room(oroom,"A shimmering field suddenly appears above "+
    "the stairs!\n");
    write("You have sealed the entrance to the temple.\n");
    for(i=0;i<sizeof(obs);i++)
    {
         if((IS_DK(obs[i]) || IS_LP(obs[i])) && obs[i] != TP)
             tell_object(obs[i],TP->query_name()+" has sealed the "+
             "temple entrance.\n");
    }
    return 1;
}

int
do_unseal(string str)
{
    object oroom,eroom, *obs;
    int i;
    obs = users();
    NF("Unseal what? The temple entrance?\n");
    if(str != "temple entrance")
        return 0;
    call_other("/d/Kalad/common/raum/cdlair1/cd01","??");
    call_other("/d/Kalad/common/raum/cdlair1/h02","??");
    oroom = find_object("/d/Kalad/common/raum/cdlair1/cd01");
    eroom = find_object("/d/Kalad/common/raum/cdlair1/h02");

    if(oroom->query_blocked() == 0)
    {
        write("The entrance is not sealed.\n");
        return 1;
    }

    oroom->set_blocked(0);
    eroom->set_blocked(0);
    tell_room(oroom,"A shimmering field above the stairs suddenly "+
    "vanishes.\n");
    write("You have unsealed the entrance to the temple.\n");
    for(i=0;i<sizeof(obs);i++)
    {
         if((IS_DK(obs[i]) || IS_LP(obs[i])) && obs[i] != TP)
             tell_object(obs[i],TP->query_name()+" has unsealed the "+
             "temple entrance.\n");
    }
    return 1;
}
