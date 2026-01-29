/* 
 * /d/Kalad/common/central/arm/lord_ring.c
 * Purpose    : Ring worn by the high lord in the citadel. Enables wearer to "offer" the ring to others.
 * Located    : /d/Kalad/common/central/arm/
 * Created By : Korat 1995
 * Modified By: Fixed typo Damaris 3/2002
 */ 

/*
High Lords ring
Made by korat
feb 14. 1995
*/

inherit "/d/Kalad/std/armour.c";
inherit "/lib/commands";
#include "/sys/wa_types.h"
#include "/sys/stdproperties.h"
#include "/d/Kalad/defs.h"
#include "/sys/ss_types.h"

create_armour()
{
   ::create_armour();
   set_name("ring");
   set_adj("golden");
   set_long("This ring shines in a refreshing golden colour. You "+
      "see no stones decorating it, but it still looks like "+
      "a valuable item. This is the ring the High Lord of Kabal "+
      "offers to his people to kiss.\n");
   
   set_ac(1);
   set_at(A_ANY_FINGER);
   add_prop(OBJ_I_VALUE,800);
   add_prop(OBJ_I_WEIGHT,300);
   add_prop(OBJ_I_VOLUME,50);
}  

init()
{
   ::init();
   add_action("offer","offer");
}

offer(string str)
{
   object *people;
   object who;
   object kiss_ob;
   notify_fail("You must wear the ring first!\n");
   if(!TO->query_worn()) return 0;
   notify_fail("Offer ring to whom?\n");
   if(!str) return 0;
   people=parse_this(str,"%l");
   if (sizeof(people)==0)
      {
      write("You don't see anyone called "+str+" here.\n");
      return 1;
   }
   if(sizeof(people)>1)
      {
      write("Who do you want to offer the ring to? Be more precise.\n");
      return 1;
   }
   who = people[0];
   TP->catch_msg("You offer the ring to "+QTNAME(who)+", for "+
      who->query_objective()+" to kiss it.\n");
   say(QCTNAME(TP)+" holds "+TP->query_possessive()+
      " ring out towards "+QTNAME(who)+", for "+who->query_objective()+
      " to kiss it.\n",({ who, TP }));
   who->catch_msg(QCTNAME(TP)+" holds "+TP->query_possessive()+" ring out, "+
      "for you to kiss it.\n");
   
   /* need code for the actual kiss or not kiss. */
   
   seteuid(getuid(TO));
   kiss_ob=clone_object("/d/Kalad/common/central/obj/kiss_object");
   kiss_ob->move(who);
   kiss_ob->set_ring_bearer(TP);
   return 1;
}

send_name(object ob)
{
   ob->set_short("tester");
}
