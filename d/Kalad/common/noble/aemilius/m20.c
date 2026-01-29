inherit "/d/Kalad/room_std";
#include "/d/Kalad/defs.h"

/* Sarr */

object ob;
void reset_room();

void
create_room()
{
    ::create_room();
    set_short("In a room of the House of Aemilius");
    INSIDE;
    set_long("You have entered a spacious room. It appears to "+
        "be a bed chamber of sorts. The walls are made of polished "+
        "pine wood, and there is a table in the center with chairs "+
        "around it. A bed lays off to the side, while a chest and "+
        "dresser stands against a wall under a window. The floor "+
        "is carpeted.\n");
    add_item("walls","Very shiny.\n");
    add_item("table","It is a sturdy table with cups and empty "+
        "plates on it.\n");
    add_item("chairs","Soft, cusioned chairs.");
    add_item("bed","A huge canopy bed with down sheets and pillows.\n");
    add_item("dresser","It holds clothes and other things.\n");
    add_item("chest","It is locked shut.\n");
    add_item("window","You can see the streets bellow out of it.\n");
    add_item("carpet","A beautiful carpet woven with many designs.\n");
    
    
    add_exit(NOBLE(aemilius/m17),"east",0,-1,-1);
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

