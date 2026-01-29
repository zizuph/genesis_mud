 
// file name: cross
// creator: Ilyian, September 20, 1995
// last update:
// purpose: A crossroads in ~Avenir/common/dead/
// note: most of the code in these rooms is inherited in
//       ~avenir/common/dead/dead.c
// bug(s):
// to_do:

inherit "/d/Avenir/common/dead/dead.c";
#include "../dead.h"

//void populate_island();

void
create_room()
{
   path_long("This is a misty crossroads, with a cobbled "
            +"path leading north into the mist, and back "
            +"south towards a ferry landing. To the west "
            +"and east, the path runs along the shoreline "
            +"of the island. To the northwest and "
            +"southwest is a dismal marsh.\n"
            +"There is a large signpost "
            +"here.");
   set_short("crossing");

   AI(({"sign","signpost"}),"This is a large signpost that "  
            +"has been hammered deep into the ground. Written "
            +"in large red letters on the sign is:\n"
            +"Beware! Leave the paths under no circumstances!\n"
            +"The dead reside on the moors.\n");
   ACI("sign","read","Written in large read letters on " 
            +"the sign is:\nBeware! Leave the path under no "
            +"circumstances!\nThe dead reside on the moors.\n");

   AI(({"marsh","moor","moors","swamp","fen","fens"}),
             "To the northwest and northeast spread out "
            +"a menacing swamp, upon which a thick shroud "
            +"of mist hangs.\n");
   AI(({"mist","fog"}),"It is thick and eerie.\n");
   AI(({"landing","ferry","ferry landing","dock"}),"Back to the "
            +"south you can see the narrow "
            +"and rickety dock that extends out onto the "
            +"water.\n");

   AI(({"water","sea","ocean","shore","shoreline"}),"The "
            +"black sea stretches out to the south, into "
            +"a vague darkness that is broken up only by "
            +"the dim lights that can be seen coming accross "
            +"from the bazaar island and Sybarus City.\n");
   AI(({"lights","city","sybarus city","island","bazaar"}),"No "
            +"details can be made out about the other "
            +"islands from this distance.\n");

   AE(PATH+"path2","north",0,1);
   AE(PATH+"path1","south",0,1);
   AE(PATH+"shore1","west",0,1);
   AE(PATH+"shore26","east",0,1);


}

/* Changed to landing.c by Lilith 9/25/03 
enter_inv(object ob, object from)
{
   if(interactive(ob))
      populate_island();
   ::enter_inv(ob, from);
}

void populate_island()
{
   UMAKER->create_room();
   UMAKER->start_cooking();
}
*/
