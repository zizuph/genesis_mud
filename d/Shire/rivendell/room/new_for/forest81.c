/*
 * Forest near Rivendell
 * By Finwe, August 1998
 */
 
#pragma strict_types
 
#include "local.h"
 
inherit FOREST_BASE;
 
void
create_forest_room()
{
    set_vbfc_extra(forest_desc3);
    set_extraline("The river Bruinen flows past here.");
    reset_shire_room();
 
    add_item(({"river", "river bruinen", "bruinen"}),
        "The river flows lazily to the west from the mountains. " +
        "It looks clear and fresh.\n");

    add_exit(FOREST_DIR + "forest82", "east",0,4, check_person);
    add_exit(FOREST_DIR + "forest80", "west","@@bush_exit@@",4, check_person);
 
}


int bush_exit()
{
    write ("You go west and crash through the bushes.\n");
    say(QCTNAME(TP) + " goe west and crashes through the bushes.\n");
    tell_room(FOREST_DIR + "forest80", QCTNAME(TP)+" comes " +
        "crashing through the forest and startles you.\n", TP);


}

void init()
{   
    ::init();
    add_action("drink_it",      "drink");
}
 
int drink_it(string s)
{
 
int amount;
 
   if(s=="water" || s=="water from river")
       {
           amount = TP->query_prop(LIVE_I_MAX_DRINK) / 20;
           if (TP->drink_soft(amount))
           {
           TP->catch_msg("You kneel before the river, dipping " +
                "your cupped hands into the river and get a " +
                "drink of the clear icy water. Its taste " +
                "refreshes your mind and body.\n");
 
           say(QCTNAME(TP)+" kneels before the river and gets a " +
                "drink.\n");
           
           }
           else
           {
           write("You cannot drink more water.\n");
           }
 
            return 1;
        }
    else
            NF("Drink what?\n");
}

void reset_shire_room()
{
}
