#include "/d/Kalad/defs.h"
#include "/d/Kalad/common/guilds/khiraa/khiraa_defs.h"
#pragma save_binary

inherit "/d/Kalad/room_std";

#define KHIRAA_DESTS  ({ "/d/Kalad/common/port/s74", \
                         "/d/Kalad/common/central/plaza/sq_mon", \
                         "/d/Kalad/common/raum/road/r13", \
                         "/d/Kalad/common/wild/pass/desert/d1" })

#define NUM_DESTS 4

int posi;

object
load_dest_room(string str)
{
    object ob;
    call_other(str,"??");
    ob = find_object(str);
    return ob;
}

void
create_room()
{
    set_short("In the portal room");
    set_long("\n   You are now in a room filled with eerie purple "+
    "light. Dark shadows linger on the black stone walls and "+
    "ceiling. The floor is made of smooth black marble. The air "+
    "is filled with forboding coldness.\n"+
    "   The source of the light seems to be the large portal standing "+
    "against the far north wall. Next to the portal, a small, clear "+
    "orb floats. Nothing else is in the room.\n\n");
 
    add_item("orb","@@orb@@");
    add_item("portal","The portal is in the shape of a giant skull. "+
    "In its open mouth, you see nothing but pure purple light beaming "+
    "out of. The portal is made of pure white stone, and the eyes "+
    "of the skull are made of sparkling emeralds. On the side of "+
    "the panel, you see a small dial.\n");
   
    add_item("dial","@@dial@@");

    add_prop(ROOM_I_LIGHT,1);
    INSIDE;
    add_exit(KHIRAA_DIR(temple/rooms/t8),"south",0,-1);
    posi = 0;
}

void
init()
{
    ::init();
    AA(do_enter,enter);
    AA(do_turn,turn);
}

int
do_turn(string str)
{
    NF("Turn what?\n");
    if(str != "dial")
        return 0;
    posi++;
    if(posi > (NUM_DESTS-1) )
        posi = 0;
    write("You turn the dial and it now points to '"+(posi+1)+"'.\n");
    say(QCTNAME(TP)+" turns the dial.\n");
    return 1;
}

int
do_enter(string str)
{
    object proom;
    NF("Enter what?\n");
    if(str != "portal")
        return 0;   
    proom = load_dest_room(KHIRAA_DESTS[posi]);
    write("You step into the portal.\n");
    say(QCTNAME(TP)+" steps into the portal, and is gone.\n");
    TP->move_living("M",proom);
    tell_room(E(TP),QCTNAME(TP)+" suddenly steps out of "+
    "nowhere!\n",TP);
    return 1;
}


string
dial()
{
    return "The dial is small, and made of a stone shaped like an "+
    "arrow head. There seems to be "+NUM_DESTS+" settings on the dial. The "+
    "arrow is currently pointing to the one marked '"+(posi+1)+
    "'.\n";
}

string
orb()
{
    string roomlong;
    roomlong = load_dest_room(KHIRAA_DESTS[posi])->long();
    return "You gaze into the orb, and a vision is displayed there. "+
    "You see:\n\n"+roomlong+"\n";
}

