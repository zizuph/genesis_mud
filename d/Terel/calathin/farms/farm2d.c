/*
 * Farm2d.c   Tomas  -- Jan 2000
 *
 * Lucius - Feb 2021
 *    Cleaned and modernized.
 */
#include "farm.h"
inherit FARMRM;

#define ITEM_DIR        (CFARMS + "armour/")

public int found = 0;

public void
reset_terel_room()      { found = 0; }

public void
create_terel_room()
{
    INSIDE;
    set_short("farmhouse");
    set_long("The interior of the house is spartan at best. " +
       "Rustic furnishings fill what little space the house has " +
       "to offer. A fireplace provides heat and a convienent place " +
       "to cook ones meals. A small cast iron pot hangs from a rod " +
       "within the fireplace.\n");

    add_item(("furnishings"),"A small unmade pallet rests before " +
       "the far wall while a table and stool sits in the middle of the room.\n");
  
    add_item(("pallet"),"A wooden pallet rests before the far wall. A pile " +
       "of what looks like a pile of clothes.\n");

    add_item(({"pile","clothes","pile of clothes"}),
       "Mostly smelly old clothes.\n");

    add_item(("table"),"Dirty dishes and mug sits on the table.\n");
    
    add_item(({"dishes","mug"}),"The dishes and mug look largely uninteresting.\n");
    
    add_item(("stool"),"A small rickey stool rests before the table.\n");
  
    add_item(({"fireplace"}),
       "The fireplace looks like it is used to heat the room of the house. " +
       "A small pot hangs from a metal rod within the fireplace.\n");

    add_item(({"metal rod","rod","pot"}),
       "A small pot used for cooking hangs within the fireplace by a metal " +
       "rod. It looks well used. You decide it isn't worth getting dirty " +
       "by exploring the pot further.\n");

    add_cmd_item(({"stool"}),({"sit","sit on"}), "You decide not to chance " +
       "breaking the stool by sitting on it.\n");

    add_cmd_item(({"pallet"}),({"sleep","sleep in","sit on","sit"}),
       "You decide that the pallet is far to smelly for you to get a good " +
       "nights rest in.\n");

    add_cmd_item(({"through pile","pile","clothes"}),"rummage", "@@rummage");

    room_add_object(CFARMS + "obj/farm2d_door1");
    add_npc(CFARMS + "npc/farmer_farm2");
}

public void
get_item(object player)
{
    object obj;

    if (!objectp(player) || ENV(player) != TO)
        return;

    if (found)
    {
        player->catch_tell("You rummage through the pile of "+
            "clothes but find nothing.\n");
        tell_room(TO, QCTNAME(player) +" digs through a pile of clothes "+
            "but finds nothing.\n", player, player);
        return;
    }

    found = 1;
    player->catch_tell("As you dig through the pile of clothes "+
        "you find something.\n");
    tell_room(TO, QCTNAME(player) +" digs through a pile of clothes "+
        "and finds something.\n", player, player);
    
    switch(random(5)) 
    {
        case 0: obj = clone_object(ITEM_DIR + "gr_boots")->move(TP);
                break;
        case 1: obj = clone_object(ITEM_DIR + "gr_breeches")->move(TP);
                break;
        case 2: obj = clone_object(ITEM_DIR + "hat")->move(TP);
                break;
        case 3: obj = clone_object(ITEM_DIR + "g_tunic")->move(TP);
                break;
        case 5: obj = clone_object(ITEM_DIR + "workgloves")->move(TP);
                break;
    }

    if (obj->move(player))
        obj->move(TO);
}

public int
rummage()
{
    write("You start rummaging through the pile of clothes.\n");
    say(QCTNAME(TP) +" starts rummaging through a pile of clothes.\n");
    set_alarm(5.0, 0.0, &get_item(TP));
    return 1;
}
