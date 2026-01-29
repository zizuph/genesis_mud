/*
   lucky_coin.c
   ------------

   Coded ........: 95/05/30
   By ...........: Jeremiah

   Latest update : 95/05/30
   By ...........: Jeremiah

   well..... as the filename says :)

*/

inherit "/std/object";
#include <macros.h>
#include <wa_types.h>
#include <stdproperties.h>
#include "/d/Krynn/common/defs.h"
#include "/d/Krynn/pax/local.h"


void
create_object()
{
   set_name(({"coin", "lucky dollar", "lucky coin"}));
   set_short("coin");
   set_long("This is a shiny silver coin. There is a picture of a " +
            "pointy-eared friendly elf wizard on both sides of the coin. " +
            "On each side, right under the picture, there is some " +
            "text saying : 'good luck'.\n");

   set_adj("shiny");
   
   add_prop(OBJ_M_NO_SELL, 1);
   add_prop(OBJ_I_VALUE,   0);
   add_prop(OBJ_I_WEIGHT,  1);
   add_prop(OBJ_I_VOLUME,  1);

   set_alarm(180.0, 600.0, "feel_lucky");
}


void
feel_lucky()
{
   if(!living(E(TO)))
      return;

   switch(random(2) + 1)
   {
   case 1:
      E(TO)->catch_msg("Suddenly a cow falls from the sky! It hits " +
             "the ground with a heavy 'THUD'. But it misses you by " +
             "several yards. Boy! do you feel lucky.\n");
   
      tell_room(E(E(TO)), "Suddenly a cow falls from the sky! It hits " +
             "the ground with a heavy 'THUD'. It almost hit you, you " +
             "had to jump for your life. " + E(TO)->query_name() + " is " +
             "totally untouched. Boy! is " + PRONOUN(E(TO)) + " lucky.\n",
             E(TO)); 
      break;

   case 2:
      E(TO)->catch_msg("A bird above you drops something! It falls " +
             "towards you. You catch it easily. It's a rare and valuable " + 
             "gold coin! Oh my! aren't you lucky?\n");

      tell_room(E(E(TO)), "A bird above you drops something! It falls " +
             "towards you. You catch it! YUCK! This sticky stuff " +
             "definitely came from the wrong end of that bird. " +
             E(TO)->query_name() + " however, caught the thing from " +
             "the right end of the bird, a rare and valuable gold " +
             "coin. Oh my! Isn't " + PRONOUN(E(TO)) + " lucky?\n",
             E(TO));
      break;
   }
}
