inherit "/std/object";
#include "/d/Kalad/defs.h"
/* this code is based on Antharanos' rock in
* /d/Kalad/common/wild/pass/obj/throw_rock.c
* and has been changed to become a bucket with water
* by Korat.
*/

object water;
int water_in_it;

create_object()
{
   set_name("bucket");
   add_name("bucket of water");
   set_adj("wooden");
   set_short("wooden bucket");
   set_long("It is a plain wooden bucket. @@check_water_inside@@\n");
   add_prop(OBJ_I_WEIGHT,5000);
   add_prop(OBJ_I_VOLUME,5000);
   add_prop("water_inside",1);
   water_in_it = 1;
}

check_water_inside()
{
   if (water_in_it) return "You see some water inside it.";
   return "It is empty.";
}

init()
{
   add_action("throw_me","throw");
}
throw_me(string s)
{
   object bum;
   string dir;
   
   NF("You are not skilled enough!\n");
   if(TP->query_skill(SS_WEP_MISSILE) < 11)
      return 0;
   NF("Throw what where?\n");
   if(!parse_command(s,E(TO),"%w %w",bum,dir))
      return 0;
   if (bum != "bucket" ||
         bum != "water")
   return 0;
   NF("But there is no water in the bucket!\n");
   if (bum == "water" && !water_in_it)
      return 0;
   if(bum=="water")
      {
      say(QCTNAME(TP) + " throws the water in the bucket "+ dir +".\n");
      write("You throw the water in the bucket "+dir+".\n");
      water=clone_object("/d/Kalad/common/central/obj/bucket_water")->move(TP);
      water_in_it = 0;
      change_prop("water_inside",0);
      return(TO->throw_it(dir,1));
   }
   say(QCTNAME(TP)+" throws a bucket "+ dir+".\n");
   write("You throw the bucket "+dir+".\n");
   
   return(TO->throw_it(dir,0));
}
throw_it(string dir,int threw_water)
{
   string where;
   
   int i;
   object *apa;
   
   if((i=member_array(dir,E(E(TO))->query_exit()))<0)
      {
      if (threw_water)
         tell_room(E(TO),"Some water comes flying in!\n");
      else
         tell_room(E(TO),"A bucket comes flying in!\n");
      return 1;
   }
   
   where = E(TO)->query_exit()[i-1];
   if (threw_water)
      tell_room(where,"Some water flies through "+
      "the air, heading "+dir+".\n");
   else
      tell_room(where,"A bucket flies through the air, "+
      "heading "+dir+".\n");
   if (threw_water) water->move(where);
   else TO->move(where);
   
   if (threw_water) apa = FILTER_LIVE(all_inventory(E(water)));
   else apa = FILTER_LIVE(all_inventory(E(TO)));
   
   if((i = random(3))<sizeof(apa) && threw_water)
      {
      apa[i]->catch_msg("The water splashes down, making you ... wet.\n");
      
      tell_room(E(TO),QCTNAME(apa[i])+ " got all soaked as the "+
         "water hits "+apa[i]->query_objective()+".\n");
      set_alarm(0.5,0.0,"remove_it",dir,water);
      return 1;
   }
   set_alarm(0.5,0.0,"throw_it",dir,TO);
   
   return 1;
}
remove_it(int i,object what)
{
   if(what->query_real_name()=="water")
      {
      tell_room(E(what),"The water dissapears as it hits the ground.\n");
      water->remove_object();
   }
   else
      tell_room("The bucket lands on the ground.\n");
}
