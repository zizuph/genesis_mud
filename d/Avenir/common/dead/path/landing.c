// file name: landing
// creator: Ilyian, September 20, 1995
// last update:
// purpose: Landing where the ship doscks
// note: 
// bug(s):
// to_do:

inherit "/d/Avenir/common/dead/dead.c";
#include "../dead.h"

#define DEAD_ENABLE  "_live_i_cango_dead"

void
create_room()
{
   set_short("rickety pier");
   set_long("This is a rough and unstable wooden pier that "
                +"extends out over the dark sea. To the north lies "
                +"a large island, most of which seems to be covered "
                +"in grey mist. There is a large hill rising from the "
                +"center of the island, and a cobbled path leads "
                +"north towards a crossroads.\n");
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
   AI(({"hill"}),"The hill to the north rises up out of the "
            +"mist that enshrouds the entire island.\n");
   AI(({"island","rock","rocks"}),"The island stretches out to "
            +"the north. Most of it seems to be covered in a "
            +"thick haze of mist, around which a narrow white "
            +"path shirts the perimiter of the island. A large "
            +"hill rises out from the center of the island.\n");
   AI(({"path","walkway","perimiter"}),"The path that leads around "
            +"the island seems to be made from a bright white "
            +"rock. It follows along the contours of the irregular "
            +"shoreline.\n");

   AE(PATH+"path1","north",0,1);

   reset_room();
}

void
reset_room()
{
}

void populate_island()
{
   UMAKER->create_room();
   UMAKER->start_cooking();
}

void
enter_inv(object ob, object from)
{
    ::enter_inv(ob, from);

    /* People coming from this side don't have to ride in coffins */
    if (interactive(ob))
    {
        ob->add_prop(DEAD_ENABLE, 1);
        populate_island();
    }                            
}
