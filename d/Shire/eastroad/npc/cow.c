/* This is supposed to be a plain cow. Will implement so he follows his master
 * wherever he walks.
 * 
 * Updated add_exp() to add_exp_quest()
 * Finwe, May 2004
 */

inherit "/std/creature";
inherit "/std/combat/unarmed";
inherit "/std/act/attack";
inherit "/std/act/action";	

#include "/d/Shire/sys/defs.h"
#include "/sys/ss_types.h"
#include "/sys/wa_types.h"
#include "/sys/macros.h"
#include "/d/Shire/bits.h"
#include "/sys/stdproperties.h"
#define QUEST_NAME "milking"
#define OBJ_DIR ("/d/Shire/common/obj/")

/* Trying to find some fit attack/hitlocation numbers, just for myself, or you :)
 */

/* Attack numbers first. */
#define A_BITE 0
#define H_HEAD 0
#define H_BODY 1
#define H_TAIL 2

void
create_creature()
{
    if(!IS_CLONE)
	return;
    set_name("cow");
    set_living_name("_bessie_the_shire_cow");
    set_race_name("cow");
    set_adj("premium");
    set_gender(G_FEMALE);
    set_long("This is one of the Brandybucks premium cows, which according to "+
	     "rumours have won many prizes at the market during the last sessions.\n");
    
    set_stats(({ 30, 15, 17, 20, 40, 30 }));  /* It is an old and wise cow :) */
    set_skill(SS_DEFENCE, 20);
    set_attack_chance(0);
    set_alignment(175);
  
   set_attack_unarmed( A_BITE, 70, 10, W_IMPALE,    80, "bite");

   set_hitloc_unarmed( H_HEAD, ({ 20, 15, 1}), 10, "head");
   set_hitloc_unarmed( H_BODY, ({ 30, 25, 1}), 80, "body");
   set_hitloc_unarmed( H_TAIL, ({ 20, 15, 1}), 10, "legs");

    add_prop(CONT_I_WEIGHT, 35000); /* About 350 Kg's, fair isnt it? */
    add_prop(CONT_I_VOLUME, 23000); /* Some 230 Ltr. */
    add_prop(LIVE_M_NO_ACCEPT_GIVE,1);

   add_prop(LIVE_I_NEVERKNOWN, 1);
    set_appearance(50);
    set_act_time(5);
    add_act("emote goes 'Mooooooooo'.");
    add_act("emote chews some hay.");
    add_act("emote lets go of a real big rip-roarer.");

   set_alarm(30.0,300.0,"do_crap");
}
void
init_living()
{
    ::init_living();
    add_action("milk_cow","milk");
}
int
milk_cow(string str)
{

   object milk, bucket;
   if(str != "cow into bucket")
   {
    notify_fail("Milk what into what??\n");
   return 0;
   }
   if(!TP->query_prop(ST_PROP_SITTING))
   {
   write("You can't do that in your position.\n");
   say(QCTNAME(TP)+ " grabs at the underbelly of the cow, but the cow ducks out of the way.\n");
    return 1;
   }

   if(!present("bucket",ENV(TO)))
   {
     write("But where's your bucket?\n");
     say(QCTNAME(TP)+ " begins to pull at the cow's nipples but stops suddenly.\n");
   return 1;
   }
   if(!present("_old_milk_farmer_",ENV(TO)))
   {
    write("The old cow runs off in search of her master.\n");
   say(QCTNAME(TO)+ " runs off in search of her master.\n");
   TO->remove_object();
   return 1;
   }
    if (TP->query_skill(SS_ANI_HANDL)>20)
    {
   write("You skillfully milk the cow. She seems pleased "+
	      "with your treatment of her.\n");
	say(QCTNAME(TP)+" milks the cow with an unexpected skill.\n"+
	    " The cow seems pleased with "+QTNAME(TP)+"'s treatment.\n");

/* Passed all checks, now let's give out the milk, and put it */
/* In the bucket too. :) */
   milk = clone_object(OBJ_DIR + "milk");
   bucket = present("bucket",ENV(TO));
   milk->move(bucket);

   set_alarm(15.0,0.0,"reward_player",TP);
    return 1;
    }
    else
    {
	write("As you start to milk the cow she gets angry at you.\n"+
	      " Obviously you don't know how to do this thing.\n"+
	      " The cow kicks you and you fall backwards landing on \n"+
		"your bottom.\n");
	say(QCTNAME(TP)+" tries to milk the cow. As the cow notices \n"+
			"that "+QTNAME(TP)+" doesn't know how to do it she \n"+
			"kicks "+QTNAME(TP)+" so "+HE_SHE(TP)+" falls backwards and lands \n"+
			"on "+HIS_HER(TP)+" bottom!!\n");
   return 1;
    }
}

int
reward_player(object player)
{
   if(TP->test_bit("Shire",WESTERN_GROUP,MILKING_QUEST_BIT))
   {
    write("Good work, but you've already done this before.\n");
    return 1;
   }


   write("You have saved a cow from the market and certain death.\n");
   write("You have made the old farmer very happy.\n");
   TP->set_alignment(TP->query_alignment() + 25);

   write("You feel more experienced.\n");
   say(QCTNAME(TP)+ " was rewarded nicely.\n");

   player->remove_prop("i_am_sitting_on_a_milking_stool");
   player->set_bit(WESTERN_GROUP,MILKING_QUEST_BIT);
//   player->add_exp(MILKING_QUEST_EXP, 0);
   player->add_exp_quest(MILKING_QUEST_EXP);
   seteuid(getuid(TO));

   log_file(QUEST_NAME, extract(ctime(time()), 4,15) +" "+
   CAP(player->query_real_name())+ " rewarded with "+MILKING_QUEST_EXP+
   " exp, "+"<"+player->query_average_stat()+ "> avg stats.\n");

   return 1;

}

int
do_crap()
{
   int i;
   object crap;

   i = random(10);

   if(i < 5)
   {
    tell_room(ENV(TO), "You hear a loud sound coming from the back of the cow.\n");
   return 1;
    }

   tell_room(ENV(TO), "The cow takes a large crap right before your eyes. How disgusting!\n");
   crap = clone_object(OBJ_DIR + "crap");
   crap->move(ENV(TO));
   return 1;

}
