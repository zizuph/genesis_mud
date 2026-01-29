/* Street base file for Tantallon.
* By Teth, Jan 17 , 1996
*/

#include "../local.h"

inherit OUTROOM; 
inherit HERBSEARCHNEW

string *herbs = HERB_MASTER->query_herbs( ({ "urban", }) );

public void
reset_tant_room()
{
    set_searched(random(2));
}

public void
create_street()
{
   
}

nomask void
create_tant_room()
{
   set_place(STREET);
   set_long_desc("This is a temporary long desc.");
   
   AI(({"street","cobblestoned street"}),"The street is an " +
      "interwoven pattern of cobblestones, expertly set. " +
      "No weeds can be seen between the cracks.\n");
   AI(({"pattern","interwoven pattern"}),"No discernible pattern " +
      "can be seen that is of any significance.\n");
   AI(({"cobblestones","stones"}),"The stones are grey and dull " +
      "in appearance. They may have been imported from " +
      "the mountains south of Kalaman.\n");
   AI("wall","This section of the wall hints at no weakness.\n");
   AI(({"walls","walls of Vingaard Keep"}),"The walls of " +
      "Vingaard Keep have never been penetrated by those of " +
      "evil intent, nor shall they ever. They are a solid " +
        "reminder that if a foundation is strong, it can " +
      "withstand whatever attempts to shake it.\n");
    AI(({"jutting platform","platform"}),"The platform is made of a dusky " +
      "grey mineral, that you can't identify from here. It " +
      "stands as a reminder that vigilance is the price of " +
      "freedom and security, as it is most likely where guards stand " +
      "watch over Vingaard.\n");
    AI(({"fortress","guildhall"}),"The fortress stands proud in " +
        "a way that seems befitting the home of the Knights of " +
        "Solamnia.\n");
    AI(({"plants","shrubs"}),"Some were planted at the side of the street, " +
        "while others happened there by mistake.\n");
    AI("plant","It is one of many that line the street.\n");
    AI("shrub","It is one of few that line the street.\n");

   OUTSIDE;
   
   seteuid(getuid(TO));
   set_up_herbs( ({ ONE_OF(herbs), ONE_OF(herbs), ONE_OF(herbs),
       ONE_OF(herbs) }), ({ "plants", "shrubs", "plant", "shrub", }), 3);
 


   create_street();
   reset_room();
   
}

