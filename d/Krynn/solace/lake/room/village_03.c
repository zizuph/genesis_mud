/*
 * Outside room in the Toron minotaur village
 * By Cherek Jan 2007. Made to inherit village_base_out.
 */
 
#include "../local.h"

inherit VILLAGE_BASE_OUT;

object mino1, mino2;

string door_desc = "The gates are closed.";

int gate_status = 0; /* 0 = Gate is closed, 1 = Gate is open */

object other_room = ROOM + "village_fort_01";

void add_long_desc();

void
reset_toron_room()
{
    if (!objectp(mino1))
    {
        mino1 = clone_object(NPC + "minotaur_standard.c");
        
        mino1->move(TO, 1);
        
        tell_room(TO, "A minotaur arrives.\n", mino1);

        mino1->add_act("close gates");
        mino1->add_act("close gates");
        mino1->add_act("close gates");        
        
    }
    
    if (!objectp(mino2))
    {
        mino2 = clone_object(NPC + "minotaur_standard.c");
        
        mino2->move(TO, 1);
        
        tell_room(TO, "A minotaur arrives.\n", mino2);
        
        mino2->add_act("close gates");
        mino2->add_act("close gates");
        mino2->add_act("close gates");
                
    }
}

void
create_toron_room()
{

    set_location("ROAD");
    set_short("Intersection");
    set_start_desc("You are walking on a narrow dirt road within a " +
                   "small village. ");
    add_long_desc();

    add_item("intersection",
             "The north-south road seems somewhat wider than " +
             "the east-west road. \n");
             
    add_item(({"door", "doors", "gate" , "gates", "entrance"}),
               "The gates consists of two massive heavy doors made of dark " +
               "well-polished wood. \n");
             
    add_road_items(); 
    add_fires();
    add_smoke();    
    add_trees();
    add_path();
    add_village();
    add_lake();
    add_structure();
    add_dirt_mud();
    add_poles_logs();
    add_pots();

    add_exit(ROOM + "village_02","south",0,3);
    add_exit(ROOM + "village_f","west",0,3);
    add_exit(ROOM + "village_g","east",0,3);

    reset_room();
}

void add_long_desc()
{

    if(gate_status == 1)
    {
        door_desc = "The gates are open";     
    }
    else
    {
        door_desc = "The gates are closed";     
    }

    set_long_desc("Two dirt roads intersect here. One is leading east-west " +
                  "and another goes south. To the north stands a large " +
                  "wooden structure. Made from logs and wooden poles it is " +
                  "clearly a fortress of some kind. Heavy wooden gates " +
                  "guard the entrance leading inside. " + door_desc  + ".");
}

void init()
{
   add_action("open_gate", "open");
   add_action("close_gate", "close");
   ::init();
}

         
int
open_gate(string what)
{
    if (what != "gate" && what != "gates" && what != "Gate" && what != "Gates")
    {
        NF("Open what? \n");
        return 0;
    }

    if (gate_status == 1)
    {
        write("The gates are already open!\n");
        return 1;
    }

    if (TP->query_stat(0) < 40)
    {
        write("With all your strength you try to open the massive gates but " +
              "they refuse to move even an inch..\n");
        say(QCTNAME(TP) + "tries to open the massive gate but " +
              "fails.\n");
        return 1;
    }

    write("Using all your strength you manage to push the massive gates open.\n");
    say(QCTNAME(TP) + " pushes the massive gates open. \n");

    other_room->gate_opens();

    add_exit(ROOM + "village_fort_01","in",0,3); 
   
    gate_status = 1;

    add_long_desc();    
   
    return 1;
}

int
close_gate(string what)
{
    if (what != "gate" && what != "gates" && what != "Gate" && what != "Gates")
    {
        NF("Close what?\n");
        return 0;
    }

    if (gate_status == 0)
    {
        write("The gates are already closed!.\n");
        return 1;
    } 

    if (TP->query_stat(0) < 40)
    {
        write("With all your strength you try to close the massive gates but " +
              "they refuse to move even an inch..\n");
        say(QCTNAME(TP) + "tries to close the massive gates but " +
              "fails.\n");
        return 1;
    }

    write("Using all your strength you manage to pull the massive gates closed.\n");
    say(QCTNAME(TP) + " pulls the massive gates closed. \n");

    other_room->gate_closes();
   
    remove_exit("in");
    
    gate_status = 0;
    
    add_long_desc();
   
    return 1;
    
}

void
gate_opens()
{
    tell_room(TO, "Suddenly the massive gates swings open.\n");

    add_exit(ROOM + "village_fort_01","in",0,3);        
   
    gate_status = 1;
    
    add_long_desc();
}


void
gate_closes()
{
    tell_room(TO, "Suddenly the massive gates swings shut.\n");
             
    remove_exit("in");
   
    gate_status = 0;
    
    add_long_desc();
    
}

