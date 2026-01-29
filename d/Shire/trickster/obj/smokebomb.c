//     Igneous' smokebomb.

//     A simple smokebomb which creates a dense, dark
//     smoke which blocks out all light for a 5-10 second 
//     period of time.

//    Copyright (C)    Chad Richardson    March 96

#pragma save_binary

inherit "/std/object";

#include <filter_funs.h>
#include <macros.h>
#include <stdproperties.h>
#include "/d/Shire/common/defs.h"

//    Prototypes
void start_smoking();
void timeout();

int      smoke, time;

void
create_object()
{
   set_name("bomb");
   set_long("This glass container is full of oil, flint, and herbs "+
      "which will ignite when the container breaks, sending a dense " +
      "smoke into the environment.\n");
   set_short("smoke bomb");
   set_adj("smoke");
   
   add_prop(OBJ_I_VALUE, 0);
   add_prop(OBJ_I_WEIGHT, 0);
   add_prop(OBJ_I_VOLUME, 0);
   add_prop(OBJ_M_NO_GET, "The smoke bomb is too hot to pick up!\n");
   
   smoke = set_alarm(0.5,0.0,&start_smoking());
   time = set_alarm(itof(5 + random(6)),0.0,&timeout());
}

void
start_smoking()
{
   object    *coughers;
   int       i;
   
   add_prop(OBJ_I_LIGHT, -5);
   remove_alarm(smoke);
   tell_room(ENV(TO), "With a loud hissing noise a cloud of " +
      "dense smoke fills the room, blocking out all light, making " +
      "it impossible to see!\n");
   coughers = FILTER_LIVE(all_inventory(ENV(TO)));
   if (!sizeof(coughers))
      return;
   for (i = 0; i < sizeof(coughers); i++)
   coughers[i]->catch_msg("Cover your mouth when you cough noisily!\n");
}

void
timeout()
{
   remove_alarm(time);
   tell_room(ENV(TO), "The smoke finally dissapates, enabling " +
      "you to see your surroundings once again.\n");
   remove_object();
}
