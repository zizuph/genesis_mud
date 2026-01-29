#pragma strict_types

inherit "/std/armour";
inherit "/lib/keep.c";

#include <stdproperties.h>
#include <macros.h>
#include <wa_types.h>
#include "/d/Gondor/defs.h"

int init_done;

void remove_badge();
void rem_drop_prop();

void
create_armour()
{
   set_name("badge");
   remove_name("armour");
   add_name("_ithilien_badge");
   set_short("small badge");
   add_adj("small");
   set_long("@@long_desc");
   add_prop(OBJ_I_VOLUME,25);
   add_prop(OBJ_I_WEIGHT,50);
   add_prop(OBJ_M_NO_BUY,1);
   add_prop(OBJ_M_NO_SELL,1);
   set_at(A_NECK);
   set_af(TO);
   set_ac(1);
   init_done = 0;
}

public void
init()
{
   ::init();
   if (TP == ENV(TO))
   {
       if ((TP->query_alignment() < 0) || (TP->query_race() == "goblin"))
       {
          /*
           * We use set_alarm with no delay and no repeation as we want
           * the remove_badge to be called directly _after_ this function.
           */
           set_alarm(0.0, 0.0, remove_badge);    
       }
       if (!init_done)
       {
           TP->add_prop("_ithilien_leave_by_hunthor",1);
           add_prop("_ithilien_leave_name",TP->query_real_name());
           if (interactive(TP))
               add_prop(OBJ_M_NO_GIVE,"Didn't Hunthor tell you not to give the badge away?\n");
           init_done = 1;
       }
   }
}

public string
query_auto_load()
{
   if(ENV(TO)->query_prop("_no_pass_to_ithilien") || 
         !ENV(TO)->query_prop("_ithilien_leave_by_hunthor") ||
      query_prop("_ithilien_leave_name") != ENV(TO)->query_real_name() )
   return "";
   add_prop(OBJ_I_NO_DROP, 1); /* Destruct when saving */
   set_alarm(1.0, 0.0, rem_drop_prop); /* If not saved allow drop again */
   return MASTER + ":";
}

void rem_drop_prop() { remove_prop(OBJ_I_NO_DROP); }

mixed
wear(object ob)
{
   if ((TP->query_alignment() < 0) || (TP->query_race() == "goblin"))
   {
       set_alarm(0.0, 0.0, remove_badge);
       return "You cannot wear the small badge.\n";
   }
   write("You wear the small badge on your chest.\n");
   return 1;
}

void remove_badge()
{
   write("Suddenly, the small badge starts glowing and then disappears!\n");
   set_alarm(0.0, 0.0, remove_object);
}

string long_desc()
{
   object tp = ENV(TO);
   
   if(interactive(tp))
   {
       if ((tp->query_alignment() < 0) || (tp->query_race() == "goblin"))
           set_alarm(0.0, 0.0, remove_badge);
   }
   return BSN("A small badge, stamped out of iron. It carries the sign of " +
       "the Stewards of Gondor, a simple rod on a white field.");
}

public string query_recover() { return 0; }
