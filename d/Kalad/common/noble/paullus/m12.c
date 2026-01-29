inherit "/d/Kalad/room_std";
#include "/d/Kalad/defs.h"
/* Sarr */

object ob;
void reset_room();

void
create_room()
{
    set_short("In a bedroom of the House of Paullus");
    set_long("You have entered a lavish bedroom. The walls are "+
    "made of beautiful polished red wood, and the floor "+
    "is covered with a large and fluffy bear-skin rug. Sitting "+
    "in one corner, there is a desk. Along the opposite wall, "+
    "a beautifuly crafted bed rests. A table and two chairs are "+
    "placed alongside another wall, while in the center a large "+
    "wooden chest stands. Paintings and other decorations are "+
    "scattered throughout the room.\n");

    add_item("walls","You run your hands across these wonderful "+
    "wood pannels feeling the smooth surface. However, on one "+
    "wall, you notice one panel is loose.\n");
    add_item("rug","A beautiful rug made of bear skin. It feels "+
    "good to run your naked skin across.\n");
    add_item("desk","The desk is bare, except for a sheaf of paper "+
    "and an ink bottle.\n");
    add_item(({"bottle","ink bottle"}),"A glass bottle filled with "+
    "black ink.\n");
    add_item("paper","At the top, you see the words written: "+
    "To Sir Roger:\n"+
    "Please inform our customer that their item was stolen from "+
    "our house, and we have yet to discover the....\n"+
    "The words break off there.\n");
    add_item("bed","The bed is made of solid oak and is polished "+
    "to a shine. The bed is covered with soft pillows and a "+
    "giant fluffy blanket that is just perfect for snuggling up "+
    "with.\n");
    add_item("table","The table is made of solid oak, and you can "+
    "see your reflection from it. A small figurine rests on top of "+
    "it.\n");
    add_item("figurine","It is a small clay figure that looks like "+
    "a naked man with large muscles.\n");
    add_item("chairs","They are made of solid wood and have cusions "+
    "on them.\n");
    add_item("chest","You rummage through this open chest, but find "+
    "nothing of intrest.\n");
    add_item("paintings","Wonderful paintings of the wilderness.\n");
    add_item("decorations","Candles, ornate candle holders and "+
    "golden clocks and lanterns are placed about.\n");
    add_item("panel","It is loose, perhaps you can lift it?\n");
    INSIDE;

    add_exit(NOBLE(paullus/m10),"east",0,-1,-1);
    reset_room();
}

void
reset_room()
{
    if(!ob)
    {
        ob = clone_object(NOBLE(npc/maid));
        ob->arm_me();
        ob->move_living("xxx",TO);
    }
}

void
init()
{
    ::init();
    AA(do_lift,lift);
    AA(do_enter,enter);
}

int
do_lift(string str)
{
    NF("Lift what?\n");
    if(str != "panel")
        return 0;
    write("You lift the panel open and discover a small hole behind "+
    "it! The panel is just wide enough for you to enter, if you dare.\n");
    write("You can't see anything but darkness beyond.\n");
    say(QCTNAME(TP)+" lifts back a wall panel and discovers a hole!\n");
    return 1;
}

int
do_enter(string str)
{
    NF("Enter what?\n");
    if(str != "hole")
        return 0;
    write("You squish into the space between the panels and enter "+
    "a dark hole.\n");
    say(QCTNAME(TP)+" squeezes into the hole behind one of the pannels.\n");
    TP->move_living("M",NOBLE(paullus/hole1));
    return 1;
}

