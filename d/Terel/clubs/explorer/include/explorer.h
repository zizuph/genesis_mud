/*
  Inherit file for Terel NPC's used when meeting members of the Explorers Club
  Tomas -- Dec 1999
*/

#include "/d/Terel/include/Terel.h"
#include "/d/Terel/clubs/explorer/include/explorer_club.h"
#include <macros.h>

string dowhat();


/*
 * The following are neccessary to the guild server.
 */
#define SAVE    file_name(this_object())
#define MLC(x)  (x = lower_case(x))

/*
 * Indexes into the members mapping
 */
#define MAGE    0      /* Time joined field */
#define SNAME   1       /* Surname field */
#define MRACE   2       /* Race selector field */
#define HNAME   3       /* House field */


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

    switch (random(11))
    {
       case 0 :
           this_object()->command("gasp");
           this_object()->command("point " + OB_NAME(TP));
           this_object()->command("shout its " + name +"!");
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
           this_object()->command("say God speed, " + name + "!");
           break;
       case 9 :
           this_object()->command("say Our prayers are with you " + name + "!");
           break;
       case 10 :
           this_object()->command("smile warmly " + OB_NAME(TP));
           break;

    }
}


