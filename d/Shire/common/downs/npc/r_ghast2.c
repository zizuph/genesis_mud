/*
 *  Ghast in the barrow downs
 *  The randomize func's are originally Rogon's
 *  Cloned by ~Shire/common/downs/stone4*.c
 *
 *  Modifyed a  little by Odin, 9. March 1994
 */

inherit "/std/monster";

#include <ss_types.h>
#include <macros.h>
#include "/d/Shire/common/defs.h"
#include <stdproperties.h>
#include "/d/Shire/common/lib/evilkill.h"

#define RNAMES ({ \
   "arrgghh","blarrghh","bmurghh","smakks","craggt", \
   "ciggulf", "zmarghh","thgresf","ugglagrhh","smokker" })

#define RADJ ({ "black eyed","horrible looking", "ghastly","smelly","grught", \
               "rigid","handsome.. ","slimy","red eyed","grinning"})

//    Prototypes
void create_ghast(int r);
void arm();

int alarm_id;

void
create_monster()
{

    seteuid(getuid());
    create_ghast(random(10));
}
int myrand(int val)
{
    return val-val/4+random(val/2)+1;
}

void
create_ghast(int r)
{
    set_name(({RNAMES[r], "ghast ",  "_ghast_"}));
    set_pname("s");
   set_short(RADJ[r] + " ghast");
    set_pshort("ghasts");
    set_adj(RADJ[r]);
    set_race_name("ghast");
   if (!IS_CLONE)
      return;

   
   set_long("This is a ghast, nasty feller..\n"
          + "Just one more of the horrors that roam the dawns.\n");

   add_prop(CONT_I_WEIGHT,70000);   /* 70 kg  */
   add_prop(CONT_I_HEIGHT,180);     /* 180 cm */
   add_prop(NPC_I_NO_LOOKS, 1);     /*Does NOT look plesant*/
   add_prop(LIVE_O_LAST_KILL,TP);
   add_prop(LIVE_I_UNDEAD, 1);      /*Is an undead*/
   add_prop(LIVE_I_NO_CORPSE, 1);   /*Leaves no corpse*/
   add_prop("_ranger_i_not_blind",1);

            /* STR DEX CON INT WIS DIS */
   set_stats(({ 100, 100, 100, 50, 2, 70}));
   set_alignment(-200 + random (100));
   set_skill(SS_UNARM_COMBAT, 100);
   set_skill(SS_DEFENCE, 90);
   set_skill(SS_PARRY, 80);
   set_pick_up(99);
    

   set_aggressive(99);
   set_attack_chance(99);

   set_hp(900); /* Heal fully */

   set_chat_time(15);
   add_chat("Ghaaaaaasssst");
   add_chat("Hoblahsbet");
   add_chat("Snaga obey!");
   add_chat("HAHAHAHAHA!!!");
   add_chat("eeeshnbaeesh");   

   set_cchat_time(15);
   add_cchat("You smell snotty");
   add_cchat("I shall feast on your earthly remains");
   add_cchat("Soon I shall chew your bones!!");
   add_cchat("Get ready to die snaga!");

   
   set_cact_time(20);
   add_cact("growl");
   add_cact("snarl");
   add_cact("spit");
   add_cact("emote sniffs at your legs!");

   /* Global sequence */
   set_act_time(5);
   seq_new("do_things");
   alarm_id = set_alarm(2.0,0.0,&arm());
}

void
arm() {
	object money;

	
         remove_alarm(alarm_id);
        money = clone_object("/std/coins");
	money->set_coin_type("gold");
	money->set_heap_size(5 + random(10));
	money->move(this_object());
	command ("snarl");
	command ("kill "+TP->query_name());
}


return_to_normal() {
   set_act_time(5);
}
