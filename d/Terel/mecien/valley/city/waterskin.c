inherit "/std/object";

#include "/d/Avenir/common/common.h"
#include <cmdparse.h>


int level;

create_object()
{
   set_name("waterskin");
   add_name("skin");
   set_short("waterskin");
   set_long("A large waterskin made from leather. You can drink " +
        "from it. It can also be \nrefilled with water at a suitable " +
        "place. The waterskin is " + "@@query_level_desc@@" + "\n");
   level=5000;
   add_prop(OBJ_I_VALUE,230);
   add_prop(OBJ_I_VOLUME,5500);
   add_prop(OBJ_I_WEIGHT,"@@query_weight");
   add_prop(OBJ_I_CONTAIN_WATER,"@@query_water");

}


init()
{
   ::init();
   ADD("do_drink", "drink");
   ADD("do_refill", "refill");
   ADD("do_refill", "fill");
   ADD("do_empty","empty");
   ADD("do_keep", "keep");
}

query_water()
{
   if(!level)
      return 0;
   else
      return 1;
}



int
ob_weight()
{
   return(500+level);
}




int
query_weight()
{
   return(500+level);
}



string
query_level_desc()
{
   switch(level)
   {
      case 1..500:
         return "almost empty.";
      case 501..2000:
         return "less than half full \nof water.";
      case 2001..3000:
         return "half full of water.";
      case 3001..4500:
         return "more than half full \nof water.";
      case 4501..5000:
         return "full of water.";
   }
   return "empty.";
}



do_keep(string str)
{
   object *obs;
   object obj;

   notify_fail("Keep what?\n");
   if(   (!parse_command(str, TP,"[the] %i",obs)) ||
         (!sizeof(obs = NORMAL_ACCESS(obs, 0, 0)))   )
   {
      return 0;
   }
   if (sizeof(obs) != 1)
   {
       write("Please try with one at a time.\n");
   }
   else
   {
       obj = obs[0];
   }

   if (obj != TO)
   {
       return 0;
   }
   else
   {
      if(!(query_prop(OBJ_M_NO_SELL)))
      {
         add_prop(OBJ_M_NO_SELL,1);
         write("You decide you dont want to part with your waterskin.\n");
      }
      else
      {
         remove_prop(OBJ_M_NO_SELL);
         write("You decide you will sell the waterskin again.\n");
      }
      return 1;
   }
   return 0;
}

do_empty(string str)
{
   object *obs;
   object obj;

   notify_fail("Empty what?\n");
   if(   (!parse_command(str, TP,"[the] %i",obs)) ||
         (!sizeof(obs = NORMAL_ACCESS(obs, 0, 0))))
   {
      return 0;
   }
   if (sizeof(obs) != 1)
   {
       write("Please try with one at a time.\n");
   }
   else
   {
       obj = obs[0];
   }

   if (obj != TO)
   {
       return 0;
   }
   else
   {
      if(!(TP==environment()))
         write("But you don't have the waterskin!\n");
      if(!level)
         write("The waterskin is already empty.\n");
      else
      {
         write("You empty your waterskin. The water rapidly soaks into " +
               "the ground.\n");
         say(QCTNAME(TP) + " empties " + TP->query_possessive() +
             " waterskin. The water rapidly soaks into the ground.\n");
         level=0;
      }
      return 1;
   }
   return 0;
}



do_refill(string str)
{
   object *obs;
   object obj;

   notify_fail("Refill what?\n");
   if(   (!parse_command(str, TP,"[the] %i",obs)) ||
         (!sizeof(obs = NORMAL_ACCESS(obs, 0, 0)))   )
   {
      return 0;
   }
   if (sizeof(obs) != 1)
   {
       write("Please try with one at a time.\n");
   }
   else
   {
       obj = obs[0];
   }

   if (obj != TO)
   {
       return 0;
   }
   else
   {
      if(!(TP==environment()))
         write("But you don't have the waterskin!\n");
      else if(environment(TP)->query_prop(OBJ_I_CONTAIN_WATER))
      {
         write("You refill your waterskin.\n");
         say(QCTNAME(TP) + " refills " + TP->query_possessive() +
             " waterskin.\n");
         level=5000;
      }
      else
         write("You cannot refill your waterskin here.\n");
      return 1;
   }
   return 0;
}



do_drink(string str)
{
   int max;
   int capacity;
   object *obs;
   object obj;

   max = TP->query_prop(LIVE_I_MAX_DRINK);
   capacity = max-TP->query_soaked();      /* How much more can u drink? */

   notify_fail("Drink from what?\n");
   if(   (!parse_command(str, TP,"'from' [the] %i",obs)) ||
         (!sizeof(obs = NORMAL_ACCESS(obs, 0, 0)))   )
   {
      return 0;
   }
   if (sizeof(obs) != 1)
   {
       write("Please try with one at a time.\n");
   }
   else
   {
       obj = obs[0];
   }

   if (obj != TO)
   {
       return 0;
   }
   else
   {
      if(!(TP==environment()))
         write("But you don't have the waterskin!\n");

      else if(!level)
         write("But the waterkin is empty!\n");

      else if(TP->query_soaked()==max)
      {
         say(QCTNAME(TP) + " tried to drink from from " +
             TP->query_possessive() + " waterskin, but failed.\n");
         write("You cannot drink anymore water!\n");
      }
      else if( capacity < 500 )
      {
         level = level - capacity;
         TP->drink_soft(capacity);
         say(QCTNAME(TP) + " drinks from a waterskin.\n");
         write("You drink from the waterskin until you are " +
                    "completely soaked.\n");
      }
      else if( level < 500 )
      {
         TP->drink_soft(level);
         level=0;
         say(QCTNAME(TP) + " drinks from a waterskin.\n");
         write("You drink from the waterskin until its empty.\n");
      }
      else
      {
         TP->drink_soft(500);
         level=level-500;
         say(QCTNAME(TP) + " drinks from a waterskin.\n");
         write("You drink some water from your waterskin.\n");
      }
      return 1;
   }
   return 0;
}

int
query_level()
{
   return level;
}






