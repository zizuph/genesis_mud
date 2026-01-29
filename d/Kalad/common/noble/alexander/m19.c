inherit "/d/Kalad/room_std";
#include "/d/Kalad/defs.h"

/* Sarr */
object other_room;


void
init_npc(object ob)
{
    ob->set_house_name("Alexander");
    ob->set_color_name("black");
    ob->arm_me();
}

void
create_room()
{
    ::create_room();
    set_short("A small bedroom");
    INSIDE;
    set_long("You are in a small, sparsely furnished room. The "+
            "walls are solid oak, and there is a small window on one wall. "+
            "There is blood on some walls. A table and some chairs are "+
            "set in the center of the room. A tiny cot is shoved to one "+
            "corner.\n");
    add_item("cot","A small cot, with no sheets on it.\n");
    add_item("window","The window is slightly open, and hot breezes "+
            "blow in. You can see the noble district outside.\n");
    add_item("walls","The walls are smooth and dark. There is some "+
            "blood on some of them.\n");
    add_item("blood","Red blood, some fresh, some dried.\n");
    add_item("table","The table is made of black oak. There is nothing "+
            "on the table, except a steel spike.\n");
    add_item("spike","The spike has some blood in it.\n");
    add_item("chairs","The chairs are hard, and look uncomfortable.\n");
    add_item("floor","The floor is very clean. A patern of "+
            "black and white covers its entirety.\n");
    add_item("walls","The walls are black. They are polished, however, "+
            "and you can see your reflection on them.\n");
    add_item("holder","The candle holder lights up the room.\n");
    add_item("staircases","Stone staircases that spiral to the upper "+
            "level of this house.\n");
    add_item("statues","There are many statues, each one portraing "+   
            "a warrior in combat armour.\n");
    add_item("paintings","They are of the armies of Lord Kabal leading "+
            "his troops into battle.\n");
    add_item("tables","The tables are made of polished oak. On them "+
            "rests candles and incense.\n");

    add_exit(NOBLE(alexander/m16),"north","@@check@@",0,0);
    reset_room();

    add_npc(NOBLE(npc/brutal_guard2), 1, init_npc);
    add_npc(NOBLE(npc/cap_gobo));
}

void
init()
{
    ::init();
    AA(do_knock,knock);
    AA(do_climb,climb);
    AA(do_lock,lock);
    AA(do_lock,unlock);
    if(!other_room)
        other_room = load_room(member_array(NOBLE(alexander/m16),room_exits));

}

int
do_lock(string str)
{
    write("The lock is on the other side of the door.\n");
    return 1;
}

int
do_climb(string str)
{
    NF("Climb what? Out the window maybe?\n");
    if(str != "out the window")
        return 0;
    write("You jump out the window, and climb down the ivy.\n");
    say(QCTNAME(TP)+" jumps out the window, and climbs down the "+
            "ivy.\n");
    TP->move_living("M",NOBLE(alexander/g4));
    tell_room(E(TP),QCTNAME(TP)+" climbs down.\n",TP);
    return 1;
}

int
do_knock(string str)
{
    NF("Knock on what?\n");
    if(str != "on door")
        return 0;
    write("You knock on the door.\n");
    say(QCTNAME(TP)+" knocks on the door.\n");
    set_alarm(3.0,0.0,"check_the_door",TP);
    return 1;
}

void
check_the_door(object ob)
{
    other_room->check_knock_door(ob);
}

int
check()
{
    if(other_room->query_door_locked())
    {
        write("You try to open the door, but find its locked!\n");
        return 1;
    }
    write("You open the door and step through.\n");
    return 0;
}    

