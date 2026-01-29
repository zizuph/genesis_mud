/* This is supposed to be a plain cow. Will implement so he 
 * follows his master wherever he walks.
 * Removed 'do_stand' routines and now call them from stool.
 * -- Finwe February 2002
 */

inherit "/std/creature";
inherit "/std/combat/unarmed";
inherit "/std/act/attack";
inherit "/std/act/action";


#include "/d/Shire/sys/defs.h"
#include <ss_types.h>
#include <wa_types.h>
#include <macros.h>
#include <stdproperties.h>

#define ST_PROP_SITTING "_live_i_sitting_on_milking_stool"

#define QUEST_NAME  "milk"
#define SHIRE_COW    "_bessie_the_shire_cow"
#define STOOL       "/d/Shire/obj/stool"

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
    set_living_name(SHIRE_COW);
    set_race_name("cow");
    set_adj("premium");
    set_gender(G_FEMALE);
    set_long("This is one of the Brandybuck's premium cows, " +
        "which according to rumours, has won many prizes at the " +
        "market during the last seasons.\n");
    
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
    add_action("do_nothing","north");
    add_action("do_nothing","south");
    add_action("do_nothing","east");
    add_action("do_nothing","west");
    add_action("do_nothing","up");
    add_action("do_nothing","down");
    add_action("do_nothing","southeast");
    add_action("do_nothing","southwest");
    add_action("do_nothing","northeast");
    add_action("do_nothing","northwest");
    add_action("do_nothing", "kill");

}

int
milk_cow(string str)
{

    object milk, bucket;

    if (str != "cow into bucket")
    {
        notify_fail("Milk what into what??\n");
        return 0;
    }
    if (!TP->query_prop(ST_PROP_SITTING))
    {
        write("You can't do that in your position.\n");
        say(QCTNAME(TP)+ " grabs at the underbelly of the cow, " +
            "but the cow ducks out of the way.\n");
        return 1;
    }

    if (!present("bucket",ENV(TO)))
    {
        write("But where's your bucket?\n");
        say(QCTNAME(TP)+ " begins to pull at the cow's teets" +
            "but stops suddenly.\n");
        return 1;
    }
    if (!present("_old_milk_farmer_",ENV(TO)))
    {
        write("The old cow runs off in search of her master.\n");
        say(QCTNAME(TO)+ " runs off in search of her master.\n");
        remove_object();
        return 1;
    }
    if (TP->query_skill(SS_ANI_HANDL) > 20)
    {
        write("You skillfully milk the cow. She seems pleased "+
	        "with your treatment of her.\n");
	    say(QCTNAME(TP)+" milks the cow with an unexpected " +
            "skill. The cow seems pleased with "+QTNAME(TP) +
            "'s treatment.\n");

/* Passed all checks, now let's give out the milk, and put it */
/* In the bucket too. :) */
        milk = clone_object(COMMON_OBJ + "milk");
        bucket = present("bucket",ENV(TO));
        milk->move(bucket);
        set_alarm(15.0,0.0,"reward_player",TP);
        TP->command("stand up");
        return 1;
     }
     else
     {
	    write("As you start to milk the cow she gets angry at " +
            "you. It seems you don't know what you're doing or " +
            "you've upset the cow. The cow kicks the stool out " +
            "from under you and you fall backwards on your bottom!\n");
	    say(QCTNAME(TP)+" tries to milk the cow. Suddenly, the " +
            "cow looks back behind her and kicks the stool " + 
            QTNAME(TP) + " is sitting on, causing " + HIM_HER(TP) + 
            "to fall off the stool and land on " + HIS_HER(TP) + 
            " bottom!!\n");
        TP->command("stand up");

        return 1;
    }
}

void
reward_player(object player)
{
   if (!REWARD_QUEST(TP, QUEST_NAME))
   {
        write("Good work, but you've already done this before.\n");
        TP->command("stand up");

       return;
   }
   write("You have saved a cow from the market and certain death.\n");
   write("You have made the old farmer very happy.\n");
//   player->set_alignment(player->query_alignment() + 25);
   write("You feel more experienced.\n");
   say(QCTNAME(TP)+ " was rewarded nicely.\n");
   player->remove_prop(ST_PROP_SITTING);
   return;
}

int
do_crap()
{
    int i;
    object crap;

    i = random(10);

    if(i < 5)
    {
        tell_room(ENV(TO), "The cow lifts its tail and emits a " +
            "loud, squishy sound.\n");
        return 1;
    }

    tell_room(ENV(TO), "The cow drops a large cowpie right before " +
        "your eyes.\n");
    crap = clone_object(COMMON_OBJ + "crap");
    crap->move(ENV(TO));
    return 1;
}

int
do_sit(string str)
{
    if(str != "on stool")
    {
        write("Sit on what?\n");
        return 1;
    }

    if(TP->query_prop(ST_PROP_SITTING))
    {
        write("You're already sitting down!\n");
        return 1;
    }
    TP->add_prop(ST_PROP_SITTING,1);
    TP->add_prop(LIVE_S_EXTRA_SHORT, " is sitting on a wooden stool");
    add_prop(OBJ_M_NO_GET, QCTNAME(TP)+" is sitting on it!\n");
    write("You sit down on the stool, a bit uncomfortably.\n");
    say(QCTNAME(TP)+ " sits down on a wooden stool.\n");
    return 1;
}

int
do_nothing()
{
    if (TP->query_prop(ST_PROP_SITTING)) 
    {
        write("You must stand up from the stool before you can do that.\n");
        return 1;
    }

    return 0;

}
