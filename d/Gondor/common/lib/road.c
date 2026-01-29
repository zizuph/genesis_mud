/*
 *	This file is obsolete!
 *
 *	It has been replaced by /d/Gondor/common/lib/roads.c.
 *
 *	It should not be used in new code anymore, and should be replaced
 *	in old code in which it is inherited.
 *
 *	Olorin, August 1995
 */
#pragma save_binary

inherit "/d/Gondor/common/room";

#include <stdproperties.h>
#include <macros.h>
#include <language.h>
#include "/d/Gondor/defs.h"

string long_descf, street, where, county, land, mountain, vegetation,
extraline, forest;
string moonlight;

make_the_room()
{
    log_file("road", MASTER + " inherits /d/Gondor/common/lib/road.c.\n", -1);

   set_short(CAP(LANG_ADDART(street)) + " in "+land);
   set_long("@@describe");
   add_item("road","You're on a dusty road in "+land+". You're not sure where it leads.\n");
   add_item("ground","You see a dusty road.\n");
}

describe()
{
   string time;
   object clock;
   clock = find_object(CLOCK);
   long_descf = 
      "You are standing on " + LANG_ADDART(street) + " in the " +where+ 
      " parts of " +county+ " in " +land+ ". ";
   time = clock->query_time_of_day();
   moonlight = clock->query_moon();
   if(time == "early morning" || time == "morning")
      long_descf += "It is "+time+" in "+land+". A couple of deer are eating the "
         +vegetation+ ", but you can hardly spot them in the "+time+" fog. "
         + "You hear some birds, just awake, singing. East of here the "
         + "magnificent sun is rising. ";
   if(time == "noon")
      long_descf +=   "A few wild horses are grazing along the "+street+". "
         + "You can hear the sound of squeaking wheels, possibly a wagon train "
         + "somewhere along the road. It's "+time+" now, and a hot day in "+land+". "
         + "Most birds are taking a nap. ";
   if(time == "afternoon" || time == "evening")
      long_descf += "The sun is setting in the western horizon. It is "+
         time+" in "+land+". A light breeze touches your face. ";
   if(time == "night") 
      {
      if(moonlight == "dark")
         long_descf +=  "The sky is covered with dark clouds, so you can't see any stars in "
            + "the sky this "+time+". There are no people on the "
            + "road. ";
    else if (moonlight == "full")
      long_descf += "The full moon is up this night, shining its silvery "+
        "light over "+county+". ";
    else
         long_descf +=  "You can see stars twinkling in the clear "+time+" sky. "
            + "The "+moonlight+" moon casts its silvery light over the "+vegetation+". "
           + "The land of "+land+" seems quiet. ";
   }
   if(extraline) 
      long_descf += extraline;
   return BSN(long_descf);
}
