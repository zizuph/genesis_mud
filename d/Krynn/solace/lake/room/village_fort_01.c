/*
 * Fortess room in the Toron minotaur village  
 * Made to inherit village_base_in.
 * Made by Cherek Jan 2007.
 */
 
#include "../local.h"

inherit VILLAGE_BASE_IN;

string door_desc = "The gates are closed.";

int gate_status = 0; /* 0 = Gate is closed, 1 = Gate is open */

object other_room = ROOM + "village_03";

object mino1, mino2;

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
            
    set_location("FORT");
    set_short("Inside a wooden fortress");
    set_start_desc("You stand inside a fortress made almost entirely " + 
                   "of wood. ");
    add_long_desc();

    add_item(({"fortress", "building"}),
               "You can smell the fresh wood it is made of. \n"); 

    add_item("wood",
             "Every peice of wood is sleek and well-polished. \n");
             
    add_item(({"carving", "carvings", "wooden carvings"}),
              "You see several carvings on the walls. Most of them depict " +
              "great minotaur warriors in battle. \n");

    add_item(({"decorations"}),
              "You see several carvings on the walls. Most of them depict " +
              "great minotaur warriors in battle. \n");
              
    add_item(({"painting", "paintings"}),
              "They are all portraits of strong and proud minotaurs. " +
              "You believe they are important ancestors to the current " +
              "inhabitants of this village. \n");
              
    add_item("portraits",
             "You see both paintings and wooden carvings. \n");              

    add_item(({"wall", "walls", "logs", "log", "pole", 
               "poles", "plank", "planks", "wood"}),
               "The walls are remarkably sleek and well-polished. " +
               "Whoever built this fortress took great pride in " +
               "his or her work. \n");

     add_item(({"tapestry", "tapestries"}),
                "The tapestries are deep green in color with golden " +
                "trims. They look well-made and very expensive. \n");

     add_item(({"rug", "rugs", "fur", "furs", "floor", "ground"}),
                "These rugs and furs are in much better condition " +
                "then the rest you have seen in the village. They " +
                "do not even smell bad. \n");

     add_item("ceiling",
              "Like the rest of the room it is made from sleek wooden " +
              "planks. \n");
                
     add_item(({"torch", "torches"}),
                "They are just standard torches. Good for light " +
                "and good for heat. As always with torches, smoke " +
                "is a problem though. \n");

     add_item(({"doorway", "doorways"}),
                "You count three doorways. To the west, east and north. \n"); 
             
     add_item(({"door", "doors", "gate" , "gates"}),
                "The gate consists of two massive heavy doors made of dark " +
                "well-polished wood. \n");

     add_item(({"north doorway", "throne room"}),
                "There seems to be a throne room of some sorts to " +
                "the north. \n");
             
     add_item(({"east doorway", "storage room"}),
                "It appears to be a storage room. \n"); 
             
     add_item(({"west doorway", "study", "library"}),
                "It might be a study or library in there, only one " +
                "way to find out for sure. \n"); 
             

    add_exit(ROOM + "village_fort_03","north",0,3); 
    add_exit(ROOM + "village_fort_04","east",0,3);
    add_exit(ROOM + "village_fort_02","west",0,3);
    
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

    set_long_desc("This structure is more of a real building than " +
                  "anything you have seen anywhere else in the village. " +
                  "The interior walls are made of sleek wooden planks, " +
                  "and you even see a few decorations in the form of " +
                  "carvings and paintings. Long green tapestries hang " +
                  "from the ceiling partly covering the walls. Several " +
                  "fine rugs and furs have been placed on the floor and " +
                  "a few large torches lights up the windowless room. " +
                  "Three doorways lead further inside the fortress while " +
                  "heavy wooden gates guard the exit leading outside. " + 
                  door_desc  + ".");
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

    add_exit(ROOM + "village_03","out",0,3); 
   
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
   
    remove_exit("out");
    
    gate_status = 0;
    
    add_long_desc();
   
    return 1;
    
}

void
gate_opens()
{
    tell_room(TO, "Suddenly the massive gates swings open.\n");

    add_exit(ROOM + "village_03","out",0,3);        
   
    gate_status = 1;
    
    add_long_desc();
}


void
gate_closes()
{
    tell_room(TO, "Suddenly the massive gates swings shut.\n");
             
    remove_exit("out");
   
    gate_status = 0;
    
    add_long_desc();
    
}


