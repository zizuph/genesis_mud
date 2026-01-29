//               Torch Peddler (/bazaar/NPCS/t_peddler.c)
// creator(s):   Tepisch  August 1994
// last update:  Kazz  fixed the gold coin logic.  May 1995
//               Lilith, May 2022:  updated path for torches
// purpose:      sells good torches for all those dark places
// note:         only takes gold coins
// bug(s):
// to-do:

inherit "/d/Avenir/common/bazaar/NPCS/call_for_help";
inherit "/lib/trade";

#include "/d/Avenir/include/relation.h"
#include "../bazaar.h"
#include "/sys/money.h"
#include <language.h>

#define TORCH "/d/Avenir/common/obj/torch"

void
create_monster()
{
    config_default_trade();

    set_name("peddler");
    add_name("human");
    set_adj("heavily");
    add_adj("burdened");
    set_race_name("human");
    set_short("heavily burdened peddler");
    set_long(
      "This human carries upon his back a huge parcel from which a " +
      "multitude of torches protrude.\n" +
      "If the colour of your coin is correct, he may be disposed " +
      "to sell you one of his excellent torches.\n");

   default_config_npc(90);

   set_alignment(0);
   set_random_move(20);
   set_restrain_path("/d/Avenir/common/bazaar/extr");

   set_act_time(5);
   add_act("shout Torches for sale! Excellent torches for sale!");
   add_act("sigh tiredly");
   add_act(({"say No one makes better torches than we Sybaruns.", 
             "grin proudly",
      "say Some of us live in the Source-less reaches of the Utterdark."}));
   add_act(({"say Tomorrow I visit Melchior's Bath.","smile dreamily",
            "emote rubs his sore back.", "say I need a massage."}));
   add_act("say Where are you from, stranger?");

   set_cact_time(10);
   add_cact("say If you are smart you will run away, the Protectors "+
      "of Sybarus see All.");

   add_ask(({"torch", "torches", "excellent"}),
      "say Why yes, I have excellent torches. Two gold pieces each, and worth "+
      " every hard-won copper.",1);
   add_ask(({"bath", "melchior's bath"}),
      "say It is in Sybarus City, a heavenly place to wash and rest.",1);
   add_ask("sybarus",
      "say All in this cavern is Sybarus, and every island within it, though "+
      "some be called City, or Park, or Bazaar.",1);
   add_ask("city", "say It is Sybarus, the Shadow-elf City. A "+
      "wonderous place.",1);
   add_ask("massage", "say You can get one at Melchior's Bath, if you can " +
      "win passage into the City.",1);
    add_ask("park",
        ({"say Beautiful, but dangerous, that is all I'll say."}),1);
   add_ask("bazaar",
      "say You're standing in it! The commercial center of Sybarus.",1);
   add_ask(({"task", "job", "quest", "help"}),
      "say Try the Baker, or ask the gate-wardens, they might have "+
      "something for you to do.",1);
   add_ask("passage","say Ah, that must be earned. One way or another we all "+
      "strive to enter there.",1);

   NEVERKNOWN;

   set_all_attack_unarmed(25, 90);
   set_all_hitloc_unarmed(70);
   set_stats(({100,100,100,100,100,100}));
}

void
arm_me()
{
   seteuid(geteuid(this_object()));

   MONEY_MAKE_GC(random(5))->move(this_object());
   MONEY_MAKE_SC(random(40))->move(this_object());

   clone_object(BAZAAR + "Obj/wield/pclub")->move(TO);
   command("wield all");

   clone_object(BAZAAR + "Obj/worn/pshirt")->move(TO, 1);
   clone_object(BAZAAR + "Obj/worn/ppants")->move(TO, 1);
   clone_object(BAZAAR + "Obj/worn/pshoes")->move(TO, 1);
   clone_object(BAZAAR + "Obj/worn/pbelt")->move(TO, 1);
   command("wear all");

   clone_object(BAZAAR + "Obj/misc/ptorch")->move(this_object());
   clone_object(BAZAAR + "Obj/misc/ptorch")->move(this_object());
}

int
do_buy(string str) 
{
    object torch;
    int *arr, price, silent, i;
   
    if (IS_INFIDEL(this_player()))
    {
        command("say No trading with you, you treacherous infidel.");
        return 0;
    }

    if (!str) 
    {
        command( "say I only sell torches." );
        return 0;
    }
    if (str != "torch")   
    {
        command("say I only sell torches, and one at a time.");
        return 0;
    }

    torch = clone_object(TORCH);
    torch->move(this_object(),1);
    price = 144;
   
    arr = pay(price, this_player(), "", 0, 0, "");
    if (sizeof(arr) == 1) 
    {
        command("say You need money to buy a torch.");
        torch->remove_object();
        return 1;
    }
    else
    {
        /* he paid for it */
        tell_object(this_player(), "You pay for a torch.\n");        
        command("give torch to "+
            lower_case(this_player()->query_real_name()));
    }
    return 1;
}

void
init_living()
{
    ::init_living();
    add_action(do_buy, "buy");
}


