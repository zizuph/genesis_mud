/*
 * Arman October 2020
 * 
 * Sells spyglasses and nets.
 *
 */

#include "../../local.h"
#include <macros.h>
#include <ss_types.h>
#include <money.h>
#include <cmdparse.h>
#include "/d/Krynn/common/defs.h"

inherit M_FILE
inherit "/d/Ansalon/common/cheater";

#define FISHING_OPEN     1
#define NET              "/d/Calia/sea/objects/fish_net"
#define SPYGLASS         "/d/Ansalon/goodlund/bloodsea/obj/spyglass"
#define ROD              "/d/Krynn/common/fishing/fishing_rod"
#define BAIT             "/d/Krynn/common/fishing/earthworm"
#define GAFF             "/d/Krynn/common/fishing/fishing_gaff"

string *gAdj1 = ({"salty","rugged","old"});

void
create_krynn_monster()
{
    set_name("seadog");
    set_race_name("human");
    set_adj("brawny");
    add_adj(ONE_OF(gAdj1));
    set_short(implode(query_adjs()," ") + " seadog");
    set_long("This old seadog sits on the docks mending nets " +
       "and watching the ships sail in and out of Palanthas harbour. " +
       "He sells fishing rods and bait to aspiring anglers. " +
       "He also sells nets and gnomish spyglasses to sailors and " +
       "fishermen for a fair price.\n");
    set_stats(({80, 70, 75, 55, 55, 60}));
    set_skill(SS_DEFENCE, 60);
    set_skill(SS_AWARENESS, 60);
    set_skill(SS_UNARM_COMBAT, 60);
    set_all_hitloc_unarmed(10);
    set_act_time(9);
    add_act("shout Argh! Me gammy! Your silver for nets and spyglasses!");
    add_act("emote stares wistfully out to the ships on the harbour.");
    add_act("emote skillfully works on fixing a hole in a net with his " +
        "gnarled hands.");
    add_act("say Many a treasure lost in the great reef in Branchala Bay!");

    add_ask(({"bonito","balifor bonito","Balifor bonito"}),
        "say Balifor bonito? Great fighting fish! But ya'll need betta " +
        "bait than earthworms to catch one... like a bardee grub or " +
        "live bait fish!", 1);
    add_ask(({"earthworms","worms","worm","bait"}),
        "say Earthworms are pretty basic bait... I sell them for 10 copper " +
        "each! Or if you don't want to buy them from me, you could probably " +
        "find them in the moors west of Palanthas.", 1);
    add_ask(({"bait fish", "live bait fish"}),
        "say Bait fish you can probably catch with earthworms. 10 copper " +
        "each!", 1);
    add_ask(({"bardee grubs", "grubs", "bardee grub", "grub"}),
        "say Fantastic bait those grubs! I've found them in my youth " +
        "under the bark of the trees growing on the Isle of Mithas!", 1);
    add_ask(({"fishing", "fishing tips", "tips"}),
        "say Argh, you want to know how to fish do you? Easy! You " +
        "basically just need a fishing rod and bait, and water where " +
        "fish swim! If you want to actually catch fish rather than get " +
        "bait wet, you'll need some hunting skill!", 1);
    add_ask(({"fishing gaff", "gaff"}),
        "When the fish is too big to catch solo, bring some friends " +
        "with gaffs! I sell em! 3 gold each!", 1);

    set_default_answer(VBFC_ME("default_answer"));

    add_prop(LIVE_I_NEVERKNOWN, 1);
}

string
default_answer()
{
    if(FISHING_OPEN || this_player()->query_wiz_level())
    {
        command("frown");
        command("say I sell nets for 2 silver, and gnomish spyglasses for " +
            "30 silver.");
        command("say I also sell fishing rods for 2 gold, and earthworm " +
            "bait for 10 copper each.");
        command("say You wanna catch big fish? Bring a friend with a " +
            "fishing gaff! They cost 3 gold each. The gaff, not the " +
            "friend!");
        command("say If you want one, then <buy> one from me. Otherwise " +
            "I ain't got time to be answering your lubberish questions.");
        return "";
    }

   command("frown");
   command("say I sell nets for 2 silver, and gnomish spyglasses for " +
       "30 silver.");
   command("say If you want one, then <buy> one from me. Otherwise " +
       "I ain't got time to be answering your lubberish questions.");
   return "";
}

void
init_living()
{
    ::init_living();
    ADA("buy");
}


buy(string str)
{
    object pig, who;
    int num, cost;

    if (check_cheater(TP, TO))
        return 1;

    if (!stringp(str) || sscanf(str, "%d %s", num, str) != 2)
      num = 1;

    if (str == "net")
    {
        NF("The old seadog says: You cannot afford a net.\n");
        if(!MONEY_ADD(TP, -24))
	    return 0;

        NF("The old seadog says: I only sell one net at a time!\n");
        if(num > 1)
	    return 0;

        write("You pay the seadog, and he passes you a " +
          "fishing net.\n");
        say(QCTNAME(TP) + " buys a fishing net from the " +
          "old seadog.\n");

        who = TP;
        pig = clone_object(NET);
        if (pig->move(who) != 0)
        {
              write("Noticing that you are too burdened to carry the fishing " +
                  "net, the old seadog places it on the ground before you.\n");
    	      say("The old seadog places the fishing net on the ground " +
                  "before " + QTNAME(TP) + ".\n");
    	      /* pig?? */
    	      pig->move(environment(who));
         }
         return 1;
     }

    if (str == "spyglass" || str == "gnomish spyglass")
    {
        NF("The old seadog says: You cannot afford a gnomish spyglass.\n");
        if(!MONEY_ADD(TP, -360))
	    return 0;

        NF("The old seadog says: I only sell one spyglass at a time!\n");
        if(num > 1)
	    return 0;

        write("You pay the seadog, and he passes you a " +
          "gnomish spyglass.\n");
        say(QCTNAME(TP) + " buys a gnomish spyglass from the " +
          "old seadog.\n");

        who = TP;
        pig = clone_object(SPYGLASS);
        if (pig->move(who) != 0)
        {
              write("Noticing that you are too burdened to carry the gnomish " +
                  "spyglass, the old seadog places it on the ground before you.\n");
    	      say("The old seadog places the gnomish spyglass on the ground " +
                  "before " + QTNAME(TP) + ".\n");
    	      /* pig?? */
    	      pig->move(environment(who));
         }
         return 1;
     }

    if (str == "gaff" || str == "fishing gaff")
    {
        NF("The old seadog says: You cannot afford a fishing gaff.\n");
        if(!MONEY_ADD(TP, -432))
	    return 0;

        NF("The old seadog says: I only sell one fishing gaff at a time!\n");
        if(num > 1)
	    return 0;

        write("You pay the seadog, and he passes you a " +
          "fishing gaff.\n");
        say(QCTNAME(TP) + " buys a fishing gaff from the " +
          "old seadog.\n");

        who = TP;
        pig = clone_object(GAFF);
        if (pig->move(who) != 0)
        {
              write("Noticing that you are too burdened to carry the fishing gaff, " +
                  "the old seadog places it on the ground before you.\n");
    	      say("The old seadog places the fishing gaff on the ground " +
                  "before " + QTNAME(TP) + ".\n");
    	      /* pig?? */
    	      pig->move(environment(who));
         }
         return 1;
     }

    if (str == "fishing rod" || str == "rod")
    {
        NF("The old seadog says: You cannot afford a fishing rod.\n");
        if(!MONEY_ADD(TP, -288))
	    return 0;

        NF("The old seadog says: I only sell one fishing rod at a time!\n");
        if(num > 1)
	    return 0;

        NF("The old seadog says: Hmm... seems I am out of fishing rods! " +
            "Come back again at a later date.\n");
        if(!FISHING_OPEN && !this_player()->query_wiz_level())
            return 0;

        write("You pay the seadog, and he passes you a " +
          "fishing rod.\n");
        say(QCTNAME(TP) + " buys a fishing rod from the " +
          "old seadog.\n");

        who = TP;
        pig = clone_object(ROD);
        if (pig->move(who) != 0)
        {
              write("Noticing that you are too burdened to carry the fishing " +
                  "rod, the old seadog places it on the ground before you.\n");
    	      say("The old seadog places the fishing rod on the ground " +
                  "before " + QTNAME(TP) + ".\n");
    	      /* pig?? */
    	      pig->move(environment(who));
         }
         return 1;        
    }

    if (str == "earthworm" || str == "worm" || str == "worms" || str == "earthworms")
    {
        cost = 10 * num;

        NF("The old seadog says: I sell earthworms up to the dozen! No more!\n");
        if(num < 1 || num > 12)
	    return 0;

        NF("The old seadog says: You dinnat have the coin for me earthworms!\n");
        if(!MONEY_ADD(TP, -cost))
	    return 0;

        NF("The old seadog says: Hmm... seems I am out of earthworms! " +
            "Come back again at a later date.\n");
        if(!FISHING_OPEN && !this_player()->query_wiz_level())
            return 0;

        if(num > 1)
        {
            write("You pay the seadog, and he passes you your " +
               "earthworms.\n");
            say(QCTNAME(TP) + " buys earthworms from the " +
               "old seadog.\n");
        }
        else
        {
            write("You pay the seadog, and he passes you an " +
               "earthworm.\n");
            say(QCTNAME(TP) + " buys an earthworm from the " +
               "old seadog.\n");
        }

        who = TP;
        pig = clone_object(BAIT);
        pig->set_heap_size(num);
        if (pig->move(who) != 0)
        {
              write("Noticing that you are too burdened to carry the earthworm, " +
                  "the old seadog places it on the ground before you.\n");
    	      say("The old seadog places the earthworm on the ground " +
                  "before " + QTNAME(TP) + ".\n");
    	      /* pig?? */
    	      pig->move(environment(who));
         }
         return 1;        
    }

    NF("Buy what? A net, fishing rod, fishing gaff, earthworms, or a spyglass?\n");
	return 0; 

}
