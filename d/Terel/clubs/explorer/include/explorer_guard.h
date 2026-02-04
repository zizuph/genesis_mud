/*
  Inherit file for Terel NPC's used when meeting members of the Explorers Club
  Tomas -- Dec 1999
*/

#include "/d/Terel/include/Terel.h"
#include "/d/Terel/clubs/explorer/include/explorer_club.h"
#include <macros.h>

string dowhat();

int
react_enter()
{
     if (TP->query_prop("_wearing_exp_ring"))
     {
         set_alarm(1.0, 0.0, dowhat);
         return 1;
     } 
     
     return 0;
}


string
dowhat()
{
    string name = TP->query_name(); 
    string noname = TP->query_nonmet_name();

    switch (random(4))
    {
       case 0 :
           this_object()->command("emote salutes the " + noname +".");
           break;
       case 1 :
           this_object()->command("bow deeply "  + OB_NAME(TP));
           break;       
       case 2 :
           this_object()->command("say Give em hell, "+ name +"!");
           break;
       case 3 :
           this_object()->command("say We're behind you all the " +
              "the way, "+ name +"!");
           break;
       case 4 :
           this_object()->command("nod ack" + OB_NAME(TP));
           break;

    }
}









/*

       set_alarm(1.0, 0.0,&dowhat(who));

int
react_enter(string who, string name, string noname)
{
    who = TP->query_prop("_live_i_am_explorer");
    name = TP->query_name(who);
    noname = TP->query_nonmet_name(who);
    if (who)
    {
       set_alarm(itof(random(1) + 1), 0.0, "command", 
           "emote gasps in astonishment at the " +noname+".");
       set_alarm(itof(random(2) + 2), 0.0, "command", 
           "shout Everyone, its " +name+ "!" );
  
        return 1;
    }      
     return 0;
}
*/
