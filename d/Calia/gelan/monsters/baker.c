
/*
   A hobbit baker for the McCroissant bakers in Gelan 
   Adapted from shopkeeper in Minas Tirith, Gondor
   Coder: Maniac

   History:

           3/5/98      response to corpse                Maniac
          12/4/98      rabbit -> gopheroo                Maniac
          31/5/96      triggers out                      Maniac
          14.9.95      different logging                 Maniac
           8.3.95      Forced save after quest           Maniac
          24.1.95      Modified on quest change          Maniac
          28.11.94     Rabbit quest added                Maniac
*/



#pragma save_binary

inherit "/std/monster";
#include <ss_types.h>
#include <macros.h>
#include <stdproperties.h>
#include "monster.h"
inherit STD_AIDED;
#include HAUNT_CODE
#include GOPHEROO_QUEST

void
create_monster() 
{
    if (!IS_CLONE)
      return;
    set_name("donut");
    set_living_name("donut");
    add_name("owner");
    add_name("baker");
    add_name("shopkeeper");
    add_name(OWNER_NAME);
    set_race_name("hobbit");
    set_adj(({"plump","red-faced"}));
    set_title("McCroissant the Baker");
    set_long("This is Donut McCroissant, the baker of Gelan. " +
      "He looks jolly and friendly, and his rotund profile is testament to " +
      "his enthusiastic appreciation for freshly baked cuisine.\n");
    default_config_npc(55);
    set_base_stat(SS_CON,75);
    set_hp(5000);
    set_skill(SS_UNARM_COMBAT, random(20) + 35);
    set_skill(SS_DEFENCE, random(10) + 40);
    set_skill(SS_AWARENESS, random(10) + 50);
    remove_prop(NPC_M_NO_ACCEPT_GIVE);

    set_alignment(50 + random(100));
    set_chat_time(12);
    add_act("@@quest_hint");
    add_act("say Welcome to the McCroissant bakery!");
    add_act("say Feel free to salivate over my delicious cakes.");
    add_act("say Excellent food, and at competitive prices!");
    add_act("say Hungry? There's not much that isn't edible here!");
    add_cchat("The guards in Gelan will sort you out mark my words!");
    add_cchat("You must be a coward to attack a peaceful little baker!");
    add_cchat("Mummy!");
    add_cchat("This won't get you any free food you know!");

    add_ask(({"hutch", "gopheroo", "bouncer", "about hutch", 
             "about gopheroo", "about bouncer" }), 
             VBFC_ME("reply"), 1); 
}


string
quest_hint()
{
    if (!present(GOPHEROO_NAME, this_object()))
        return "say I wish someone would catch Bouncer for me.";
    else
        return "";
}


string
reply()
{
  if (present(GOPHEROO_NAME, this_object()))
      return "say I have Bouncer back!";
  else
      return "say My pet gopheroo, Bouncer, has escaped. I think " +
             "he's running around out in the square somewhere. " +
             "I can't go after him myself as I need to mind the " +
             "shop, not to mention the fact that I'm too unfit " +
             "to be chasing gopheroos, and I wouldn't stand much " +
             "chance anyway, being not very good with animals. " +
             "I'd be very grateful if you " +
             "could catch him and return him to me. Be warned " +
             "that he's very fast!";
}


void
emote_hook(string emote, object actor, string adverb)
{
    if ((emote == "bow") || (emote == "curtsey"))  
        set_alarm(1.0, 0.0, &command("bow " + actor->query_real_name())); 
}


/* Donut is stunned! */
private void
goof2()
{
    command("say er..    oops");
}


/* Donut goofs and the gopheroo jumps out of his arms */
private void
goof1()
{
    object gopheroo = present(GOPHEROO_NAME, this_object());

    if (gopheroo) {
        gopheroo->stop_docile();
        gopheroo->jump_out();
        gopheroo->bolt(); 
    } 

    set_alarm(1.0, 0.0, goof2); 
}

/* Returns 1 if player did not trap gopheroo, 0 otherwise */
private int
did_not_trap_gopheroo(object pl)
{
    if (!(pl->query_prop(I_TRAPPED_GOPHEROO)))
        return 1;
    else
        return 0;
}


/* Returns 1 if player did quest before, 0 otherwise */
private int
done_quest_before(object pl)
{
    if (pl->test_bit(GQ_DOM, GQ_GROUP, GQ_BIT))
        return 1;
    else
        return 0;
}


/* Gives thanks to player who gave Bouncer to him
   if the player caught him. */
private void
thanks(object pl)
{
    if (did_not_trap_gopheroo(pl)) {
        command("say I would thank you more if you were the one who " +
                "trapped it, " + pl->query_nonmet_name());
    }
    else if (done_quest_before(pl)) { 
        command("thank " + pl->query_real_name());
        tell_object(pl, "You have done this quest before, " +
                        "so you are not rewarded.\n"); 
    } 
    else { 
        command("thank " + pl->query_real_name());
        pl->set_bit(GQ_GROUP, GQ_BIT);
        pl->add_exp(GQ_EXP); 
        pl->catch_msg("You feel more experienced.\n");
        pl->command("save");
        log_file("gopheroo_quest", capitalize(pl->query_real_name()) + 
                 " gets " + GQ_EXP + " experience, " + 
                 ctime(time()) + ".\n");
    }

    pl->remove_prop(I_TRAPPED_GOPHEROO);

    set_alarm(3.0, 0.0, goof1); 
}



/* Donut celebrates if someone gives him his gopheroo back */
private void
celebrate(object pl)
{
    command("flip");
    command("cheer");
    command("say You found Bouncer!");
    set_alarm(1.0, 0.0, &thanks(pl)); 
}



/* Deals with Donut's reaction to being given something.
   If it's his gopheroo, a quest-related sequence will be 
   entered. */
private void
react_give(object obj, object from)
{
    if (!living(from)) {
        command("hmm");
        command("say I wonder where this "+obj->query_name()+
                " came from.");
        command("drop " + OB_NAME(obj));
        return;
    }
    else if (obj->id(GOPHEROO_NAME)) {  /* Someone returns gopheroo */
        celebrate(from); 
        return;
    }
    else if (obj->id("corpse") && 
             lower_case(obj->query_met_name()) == "bouncer" &&
             obj->query_prop(CORPSE_S_RACE) == "gopheroo") {
        command("gasp"); 
        command("say You killed him!"); 
        command("say I know he can be annoying, but THIS?");  
        command("say I wasn't serious about putting him in a pie " +
                "you know!"); 
        command("rolleyes");
        return; 
    } 
    else {            /* ordinary object received */ 
        command("say You'd better keep that, "+
                from->query_nonmet_name()+".");
        command("give "+OB_NAME(obj)+" to "+from->query_real_name());
        if (environment(obj) == this_object()) 
            command("drop "+OB_NAME(obj));
    }
} 


/* An object is given to Donut */
void
enter_inv(object obj, object from) 
{
    ::enter_inv(obj, from);
    set_alarm(1.0, 0.0, &react_give(obj, from));
}
