/*
  Inherit file for Terel NPC's used when meeting members of the Explorers Club
  Tomas -- Dec 1999
*/

#include "/d/Terel/include/Terel.h"
#include "/d/Terel/clubs/explorer/include/explorer_club.h"
#include <macros.h>

string dowhat();
string hobgoblin();
string goblin();

int
react_enter()
{
     if (TP->query_prop(EXPLORER_PROP))
     {
         set_alarm(1.0, 0.0, dowhat);
         return 1;
     } 
     if (TP->query_race_name() == "hobgoblin")
     {
         set_alarm(1.0, 0.0, hobgoblin);
         return 1;
     }
     if (TP->query_race_name() == "goblin")
     {
         set_alarm(1.0, 0.0, goblin);
         return 1;
     }
     return 0;
}


string
dowhat()
{
    string name = TP->query_name(); 
    string noname = TP->query_nonmet_name();

    switch (random(10))
    {
       case 0 :
           this_object()->command("emote gasps in astonishment at the " +
               noname + ".");
           this_object()->command("shout Everyone, it's " + name + "!" );
           break;
       case 1 :
           this_object()->command("bow deeply " + OB_NAME(TP));
           break;
       case 2 :
           this_object()->command("say " + name + ", are the rumours true?");
           break;
       case 3 :
           this_object()->command("say " + name + ", what news do you bring?");
           break;
       case 4 :
           this_object()->command("cheer " + OB_NAME(TP));
           break;
       case 5 :
           this_object()->command("clap enth " + OB_NAME(TP));
           break;
       case 6 :
           this_object()->command("say Welcome home, " + name + "!");
           break;
       case 7 :
           this_object()->command("greet " + OB_NAME(TP));
           break;
       case 8 :
           this_object()->command("say Gods speed, " + name + "!");
           break;
       case 9 :
           this_object()->command("say Our prayers are with you " + name + "!");
           break;
    }
}



string
goblin()
{
    string noname = TP->query_nonmet_name();

    switch (random(6))
    {
       case 0 :
           this_object()->command("spit " + OB_NAME(TP));
           break;
       case 1 :
           this_object()->command("shout Get out of town " +noname+"! " +
               "You're not welcome here!");
           break;
       case 2 :
           this_object()->command("shout Get back to the mountains " +
               "where you belong " + noname +"!");
           break;
       case 3 :
           this_object()->command("emote murmurs something about lousy stinking " +
               "goblins.");
           break;
       case 4 : this_object()->command("shout hey! which screwup let " +
                "this " + noname + " in the city!");
           break;
       case 5 : this_object()->command("finger " + OB_NAME(TP));
           break;
       case 6 : this_object()->command("glare angr " + OB_NAME(TP));
           break;
       case 7 : this_object()->command("shout Hey " + noname + "Keep on " +
                "walking straight to hell. Where you belong!!");
           break;
     }
}


string
hobgoblin()
{
    string noname = TP->query_nonmet_name();

    switch (random(7))
    {
       case 0 :
           this_object()->command("spit " + OB_NAME(TP));
           break;
       case 1 :
           this_object()->command("shout Hey half breed! Yah " +
               "i'm talking to you " + noname + "!");
           break;
       case 2 :
           this_object()->command("shout Half breed! I can tell yer " +
               "part gobbo, but whats the other half!?! Donkey! " +
               "Yah, thats it donkey!");
           this_object()->command("laugh loud " + OB_NAME(TP));
           break;
       case 3 :
           this_object()->command("say I hear tell dat half breeds are " +
               "part gobbo n' part donkey.. Dat true? " + noname + ". Yer " +
               "daddy make it with his donkey?!?!");
           break;
       case 5 : this_object()->command("shout hey! which screwup let " +
                "this " + noname + " in the city!");
           break;
       case 6 : this_object()->command("finger " + OB_NAME(TP));
           break;
       case 7 : this_object()->command("glare angr " + OB_NAME(TP));
           break;
       case 8 : this_object()->command("shout Hey " + noname + "Keep on walking " +
               "straight to hell. Where you belong!!");
           break;
     }
}





