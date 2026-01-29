/*
 * Small dog that will leave if feed.
 * Cloned by ~Shire/common/hobbiton/garden
 */

inherit "/std/creature";
inherit "/std/combat/unarmed";

#include "/sys/ss_types.h"
#include "/sys/wa_types.h"
#include "/sys/macros.h"
#include "/sys/stdproperties.h"
#include "/d/Shire/common/defs.h"

/* Invent some attack/hitlocation numbers, for ourselves */
#define ATT_TEETH    0
#define ATT_CLAWS    1

#define HIT_HEAD     0
#define HIT_BODY     1
#define HIT_TAIL     2
#define HIT_LFPAW    3
#define HIT_RFPAW    4
#define HIT_LBPAW    5
#define HIT_RBPAW    6

//  Prototypes
void remove(object ob);

void
create_creature()
{
   if (!IS_CLONE)
      return;
   set_short("guard dog");
   set_name("dog");
   set_living_name("_guard_dog_");
   set_race_name("dog"); 
   set_gender(G_NEUTER);
   set_long("The dog guards this cottage. It is not very big but it seems "
	    + "fierce.\nHe looks hungry.\n");

   set_stats(({ 2, 4, 2, 15, 15, 25 }));

   set_skill(SS_DEFENCE, 5);
   
   set_attack_unarmed(ATT_TEETH,  8, 8,W_IMPALE, 70, "teeth");
   set_attack_unarmed(ATT_CLAWS,  8, 8, W_SLASH, 30, "claws");

   set_hitloc_unarmed(HIT_HEAD,  ({ 2, 2, 2, 2 }), 10, "head");
   set_hitloc_unarmed(HIT_BODY,  ({ 8, 8, 8, 8 }), 40, "body");
   set_hitloc_unarmed(HIT_LFPAW, ({ 8, 8, 8, 8 }), 15, "left front paw");
   set_hitloc_unarmed(HIT_RFPAW, ({ 8, 8, 8, 8 }), 15, "right front paw");
   set_hitloc_unarmed(HIT_LBPAW, ({ 8, 8, 8, 8 }), 05, "left rear paw");
   set_hitloc_unarmed(HIT_RBPAW, ({ 8, 8, 8, 8 }), 05, "right rear paw");
   set_hitloc_unarmed(HIT_TAIL,  ({ 8, 8, 8, 8 }), 10, "tail");

   add_prop(CONT_I_WEIGHT, 5000);   /* 5 Kg  */
   add_prop(CONT_I_VOLUME, 7000);   /* 7 Ltr */
   add_prop(LIVE_I_NEVERKNOWN, 1);
   add_prop(NPC_M_NO_ACCEPT_GIVE, 0);
}

void
remove(object ob) {

  write("The dog looks at the " + ob->query_short() + ".\n");
  write("It then grabs the " + ob->query_short() + " and runs\n");
  write("around the corner with its catch.\n");

  remove_object();

}
void
enter_inv(object ob, object from) {
  
  ::enter_inv(ob,from);
  

    if(!ob->query_prop("_steak_for_doggie"))
    {
     command("grumble");
     command("drop "+ ob->query_name());
     return;
   }


  if(ob->query_amount()) 
    set_alarm(5.0,0.0,&remove(ob));

  }
