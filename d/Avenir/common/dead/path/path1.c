// file name: path1
// creator: Ilyian, September 20, 1995
// last update:
// purpose: A path along the marshes in ~Avenir/common/dead/
// note: most of the code in these rooms is inherited in
//       ~avenir/common/dead/dead.c
// bug(s):
// to_do:

inherit "/d/Avenir/common/dead/dead.c";
#include "../dead.h"

void
create_room()
{
   path_long("To the north there seems to be a crossroads, "
            +"while to the south is a ferry landing. There "
            +"is some mist scattered over the path."); 
   AI(({"crossroad","crossroads"}),"It is a crossing in the "         
            +"roads to the north.\n");
   AI(({"landing","ferry","ferry landing","dock"}),"It is a narrow "
            +"and rickety dock that extends out onto the "
            +"water.\n");

   AI(({"water","sea","ocean","shore","shoreline"}),"The "
            +"dark sea stretches out to the south, into "
            +"a vague darkness that is broken up only by "
            +"the dim lights that can be seen coming accross "
            +"from the bazaar island and Sybarus City.\n");
   AI(({"lights","city","sybarus city","island","bazaar"}),"No "
            +"details can be made out about the other "
            +"islands from this distance.\n");

   AE(PATH+"cross","north",0,1);
   AE(PATH+"landing","south",0,1);
   
   path_reset();
}
