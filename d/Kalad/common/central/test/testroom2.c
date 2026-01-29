inherit "/d/Kalad/nroom_std";

#include "/d/Kalad/defs.h"

string kabal_test();
string district();
int test(string arg);

create_room()
{
   ::create_room();
    set_short("Testing Room");
    set_long(
       "This is the testroom for this directory where we " +
       "can test changes to the domain/district/area. " +
       "This room is @@kabal_test@@ the city of Kabal" +
       "@@district@@" +
       "\n");

   hear_bell = 2;
   SET_ETIME(20);
   EVENT("One for the money...\n");
   EVENT("Two for the show...\n");
   EVENT("Three to get aready...\n");
   EVENT("Nowa go cats, go!\n");
}


string
district()
{
   string dist;
   
   if ( (dist=query_district()) == "" )
      return ".";
   else
      return ", in the " + dist + " district.";
}


string
kabal_test()
{
   if (IN_CITY)
      return "in";
   else
      return "not in";
}


init()
{
   ::init();
   AA(test,test);
}


int
test(string arg)
{
   NF("Illegal or nonexistant test string\n");
   if (stringp(arg) && arg != "")
      SAYNAME("A dog barks and "," " + arg + "\n");
   else
      return 0;
      
   return 1;
}
