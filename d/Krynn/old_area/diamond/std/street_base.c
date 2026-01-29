/* Street base file for the Diamond Isle.
* By Kentari, April 10, 1997
*/

#include <macros.h>
#include "../local.h"

inherit OUT_BASE; 
inherit HERBSEARCHNEW

string *herbs = HERB_MASTER->query_herbs( ({ "urban", }) );

public void
reset_dim_room()
{
    set_searched(random(2));
}

public void
create_street()
{
   
}

nomask void
create_dim_room()
{
   set_short("Street within the Diamond City");
   set_long("@@long_desc");
   
   AI(({"street","cobblestoned street"}),"The street is an " +
      "interwoven pattern of cobblestones, expertly set. " +
      "No weeds can be seen between the cracks, just a few " +
      "shrubs and plants along the side.\n");
   AI(({"pattern","interwoven pattern"}),"No discernible pattern " +
      "can be seen that is of any significance.\n");
   AI(({"cobblestones","stones"}),"The stones are varying shades of " +
      "gray and white in appearance. The particular type of stone " +
      "used is not discernable.\n");
   AI("wall","This section of the wall appears as clean, sturdy, and " +
	"nondescript as any other.\n");
   AI(({"walls","walls of Diamond City","gleaming walls","outer ring"}),
	"The unblemished white walls of the Diamond City are bright "+
	"and cheerful. Protecting the treasures of culture within, the walls "+
	"serve to compliment the more mystical surrounding fog of the " +
	"island's defences.\n");
    AI(({"keep","clubhall","club","diamond drunkards club"}),
	"The keep of the Diamond Drunkards Club is the center of the " +
	"city, both geographically and economically. Surrounded by the " +
	"Crystal Waters Tributary, its serves its members with glories " +
	"unknown to most.\n");
    AI(({"fountain","sparkling","top of fountain","inside keep"}),
	"Contributing to the name of the Isle, the water from the " +
	"fountain seems to catch all of the light and sparkle as " +
	"diamond would.\n");
    AI(({"trench","tributary","crystal waters tributary","water","inner ring"}),
	"The crystal clear water comes from the center fountain of " +
	"Diamond City, and though looks refreshing, is undrinkable. It " +
	"also serves as a decorative, yet effective, moat to the keep.\n");
    AI(({"plants","shrubs"}),"Some were planted at the side of the street, " +
        "while others happened there by mistake.\n");
    AI("plant","It is one of many that line the street.\n");
    AI("shrub","It is one of few that line the street.\n");
    ACI(({"water","from tributary","from trench"}),"drink", "@@do_badwater");

   OUTSIDE;
   
   seteuid(getuid(TO));
   set_up_herbs( ({ ONE_OF(herbs), ONE_OF(herbs), ONE_OF(herbs),
       ONE_OF(herbs) }), ({ "plants", "shrubs", "plant", "shrub", }), 3);
 


   create_street();
   reset_room();
   
}

string
long_desc()
{
   return tod()+season()+"This is a cobblestoned street in the " +
   "Diamond City. The gleaming walls of this peaceful city rise " +
   "above you in an outer ring, and the well cut trench of the Crystal " +
   "Waters Tributary is on your other side forming an inner ring, with " +
   "the keep of the Diamond Drunkards Club within. From inside the " +
   "keep, you can see the top of a fountain sparkling like diamonds in " +
   "the light. The beauty of the city is quite breath-taking. ";
}

int
do_badwater()
{
    write("You bend down to take a drink from the crystal clear water " +
	"and remember that the water is undrinkable. There are so many " +
	"better things to drink in this city after all.\n");
    say( QCTNAME(TP)+" bends down to take a drink from the crystal clear " +
	"water and apparently comes to " +HIS(TP)+ " senses.\n");
    TP->command("blush");
    return 1;
}
