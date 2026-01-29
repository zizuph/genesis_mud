/*
 *   /d/Gondor/minas/npc/stablemaster_noquest.c
 *
 *   The Master of the Royal Stables - pre fall of Isengard.
 *
 *   Alto, 16 April 2001
 */


#pragma strict_types

inherit "/d/Gondor/minas/npc/std_gondor_guard.c";

#include <language.h>
#include <macros.h>
#include <money.h>
#include <ss_types.h>
#include <stdproperties.h>

#include "/d/Gondor/defs.h"
#include "/d/Gondor/minas/lib/porter_defs.h"

#define WEP_ARRAY1 ({WEP_DIR + "dlongsword"})
#define WEP_ARRAY2 ({ARM_DIR + "gshield" })
#define ARM_ARRAY1 ({ARM_DIR + "ghelmet"})
#define ARM_ARRAY2 ({ARM_DIR + "schainmail"})

#define INNER_MINAS "/d/Gondor/minas"


public void
create_monster()
{
    int rnd;
    if (!IS_CLONE) return;
    seteuid(getuid());
 

    ::create_monster();
    set_adj("good-natured");
    set_adj("dusty");
    set_living_name("geradan");
    set_name("Geradan");
    add_name("stablemaster");
    add_name("geradan");
    add_name("master");
    set_title("the Master of the Royal Stables");
    set_long("This is the Master of the Royal Stables. He is "
        + "entrusted with the care of the horses stabled here. "
        + "Born and raised on a farm in the Lossarnach, this "
        + "groom knows more about equestrian lore than any other in "
        + "the kingdom.\n");

    rnd = random(60);
    default_config_npc(120+rnd/2);
    set_base_stat(SS_DIS, 140 + rnd);
    set_alignment(350+rnd*10);
    set_skill(SS_WEP_SWORD, MIN(100, 75 + rnd));
    set_skill(SS_WEP_POLEARM, MIN(100, 75 + rnd));
    set_skill(SS_WEP_CLUB, MIN(100, 75 + rnd));
    set_skill(SS_WEP_AXE, MIN(100, 75 + rnd));
    set_skill(SS_WEP_KNIFE, MIN(100, 75 + rnd));
    set_skill(SS_PARRY, MIN(100, 75 + rnd));
    set_skill(SS_DEFENCE, MIN(100, 75 + rnd));
    add_prop(CONT_I_HEIGHT,170+rnd);
    add_prop(CONT_I_WEIGHT,85000+rnd*500);
    add_prop(CONT_I_VOLUME,80000+rnd*500); 

    clone_object(INNER_MINAS + "/obj/horse_whip.c")->move(TO);


    set_chat_time(15);
    add_chat("Welcome! Do you have a horse that needs stabling?");
    add_chat("We keep the north stable ever-ready for the return "
        + "of the King.");
    add_chat("Other than the horse of the Steward, I do not have "
        + "many animals to look after these days.");

    set_cchat_time(5);
    add_cchat("Guards! Raise the alarm!");
    add_cchat("If you leave now I may decide against killing you!");
    add_cchat("For Gondor!");

    set_act_time(7);
    add_act("grin");
    add_act("chuckle");
    add_act("smile");
    add_act("crack whip");


    remove_prop(LIVE_I_NEVERKNOWN);

    set_default_answer( ({ "say Excuse me?", "cough incoherently" }) );


    add_ask_item(({"horse", "horses"}), "say This is where the riders of the "
        + "Steward stable their horses. None are in at the moment.");
    add_ask_item(({"mearas", "shadowfax", "Shadowfax"}), "say Eh? I've never "
        + "heard of such a thing!");
    add_ask_item(({"north stable"}), "say We keep the stable to the north always "
        + "clean, with fresh straw and water, so that it will be ready for "
        + "the mount of the King, should he return.");
    add_ask_item(({"stem", "greenery", "paths", "path"}), "say What would "
        + "I know about such things? Ask a botanist.");
    add_ask_item(({"drink"}), "say Do you have any?");
    add_ask_item(({"whip"}), "say It is just for show. I would never apply "
        + "it to horseflesh!");
    add_ask_item(({"assistant", "assistants"}), "say You certainly do not see "
        + "them around here working! Perhaps they are all sleeping off "
        + "the spirits from last night.");
    add_ask_item(({"hair", "horse hair"}), "say It gets into everything! "
        + "Between that and the dust, we stablehands find ourselves in "
        + "need of a good bath by the end of the day.");
    add_ask_item(({"dust"}), "say The horses kick up the dirt in here when "
        + "they exercise, and as a result no grass will really grow here. "
        + "Without grass to hold the soil together, it pretty much stays "
        + "dusty. Except, of course, when it rains. Then it just stays "
        + "muddy.");
    add_ask_item(({"bench"}), "say It is right over there in the corner. I am "
        + "not really sure why you need to ask me about it.");
    add_ask_item(({"stables"}), "say Feel free to go inside and look around.");
    add_ask_item(({"tool", "tools"}), "say There are a number of "
        + "tools stored on the bench.");
    add_ask_item(({"mallet"}), "say We use a mallet to tap the pegs into the "
        + "shoes of our horses.");
    add_ask_item(({"crop"}), "say A crop is useful for motivating horses to run "
        + "about the stable and get some exercise.");
    add_ask_item(({"rake"}), "say A rake is a wonderful tool for moving large "
        + "quantities of hay or straw.");
    add_ask_item(({"comb"}), "say Well, combs are useful for grooming people, "
        + "but they are rather inadequate for grooming horses.");
    add_ask_item(({"groom", "grooming"}), "say Grooming a horse is a serious "
        + "business. If you do not keep your head about you, the horse "
        + "might just kick you in the teeth.");

    /* quest related asks */

    add_ask_item(({"brush"}), "say A brush is used for the grooming of "
        + "horses.");
    add_ask_item(({"hobbit", "halfling", "Pippin", "Peregrin", "pippin",
        "peregrin"}), "say What is a hobbit?");
    add_ask_item(({"quest", "task", "job", "help"}), "say I don't really "
        + "need any help right now, thank you.");
    add_ask_item(({"reward", "for reward", "about reward"}), "say Huh? Did "
        + "you solve a murder or something? Go see Hunthor! What would I "
        + "know of such things?");
    add_ask_item(({"oat", "oats", "faradan", "Faradan"}), "say Yes, I "
        + "feed them to the horses here. I have plenty at the moment.");
    add_ask_item(({"firewood"}), "say Firewood? Why would I need firewood?");

    arm_me();
    refresh_mobile();

}


public void
return_giggle(object actor)
{
    if (!objectp(present(actor, ENV(TO))))
    return;

    switch (random(3))
    {
    case 0:
        command("say Nice to see joy in such perilous times.");
        break;
    case 1:
        command("grin . "+ actor->query_real_name());
        break;
    case 2:
        command("smile . " + actor->query_real_name());
        break;
    default:
        break;
    }
}

public void
return_laugh(object actor)
{
    if (!objectp(present(actor, ENV(TO))))
  	 return;

    switch (random(3))
    {
    case 0:
        command("say Laughter is truly the best medicine.");
	       break;
    case 1:
	       command("tickle . " + actor->query_real_name());
	       break;
    case 2:
        command("say I could use some help from the likes of you.");
	       command("smile .");
	       break;
    default:
        break;
    }
}

public void
emote_hook(string emote, object actor, string adverb = 0)
{
    if (!objectp(actor) || !interactive(actor))
        return 0;

    switch (emote)
        {
        case "giggle":
	           set_alarm(2.0, 0.0, &return_giggle(actor));
	           break;
        case "laugh":
	           set_alarm(2.0, 0.0, &return_laugh(actor));
	           break;
    }
}

void
return_introduce(object pl)
{
    if ((!objectp(pl)) || (objectp(query_attack())))
        return;

    command("introduce me to "+pl->query_real_name());
    return;
}

void
add_introduced(string who)
{
    object  pl = find_player(LOW(who));

    if ((!objectp(pl)) || (objectp(query_attack())))
        return;

    set_alarm(3.0, 0.0, &return_introduce(pl));
    return;
}

public void 
set_arm_arrays()
{
  ::set_arm_arrays();
  wep1 = WEP_ARRAY1;
  wep2 = WEP_ARRAY2;
  arm1 = ARM_ARRAY1;
  arm2 = ARM_ARRAY2;
}

public int
query_knight_prestige() { return -30; }

