/*
 * Copyright notice, please read.
 *
 * Copyright Chalmers Datorf|rening, 1992
 *
 * You are welcome to read this file for information & education purposes.
 * However, you are expressly forbidden to copy this code for use in any
 * other mud. This code is part of Genesis and we want Genesis to remain
 * unique. You must invent your own world on your own mud.
 *
 */

#pragma save_binary
#pragma strict_types

inherit "/std/room";

#include "../defs.h"

void reset_room();

object dv;

void
create_room()
{
    set_short("Palace entrance");
    set_long("This is the huge entrance hall of the Royal castle.\n"+
             "The walls are covered with thin plates of gold, and\n"+
             "above the fireplace in the east wall hangs a very\n"+
             "impressive sword, with a small sign under it.\n");

    add_item("fireplace","Someone has lit a fire in the fireplace.\n");
    add_item("fire","It looks very hot.\n");
    add_item("plates of gold", "They are lavishly made from gold.\n");
    add_item("sign","The sign says: The Sword of Andaluphin.\n");
    add_cmd_item("sign","read","The sign says: The Sword of Andaluphin.\n");

    add_item("sword","The sword is made of steel, decorated with gold, and\n"+
             "is most likely the sword that saved the dwarfs in the\n"+
             "great battle of Andaluphin about four hundred years\n"+
             "ago, when they were attacked by an army of evil orcs.\n");

    add_cmd_item("sign","read","The sign says: The Sword of Andaluphin.\n");
  
    add_exit(LVL1+"square","west");
    add_exit(LVL1+"palace2","north");

    reset_room();
}

void
reset_room()
{
    if(dv)
        return;

    dv = clone_object(D_MON + "citizen");
    dv->arm_me();
    dv->move_living("singing a merry tune.\n",TO);
}
