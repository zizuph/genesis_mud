//-*-C++-*-
// file name:     /d/Avenir/registry/registrar	  
// creator(s):    Lilith    27 Mar 2004
// purpose:       sells seals for the registry
// note:          
// last update:             
// bug(s):
// to-do:
#pragma strict_types

inherit "/d/Avenir/inherit/sybarite";
inherit "/d/Avenir/inherit/helper";
inherit "/d/Avenir/inherit/death_crier";
inherit "/d/Avenir/inherit/intro";
inherit "/d/Avenir/inherit/log_asks";
inherit "/lib/shop";

#include "/d/Avenir/include/macros.h"
#include "/d/Avenir/include/relation.h"
#include "/d/Avenir/smis/sys/statserv.h"

#include <macros.h>
#include <stdproperties.h>

#define NUM_ITEMS(x)  sizeof(filter(deep_inventory(TO), &->id((x))))
#define STORE_ROOM    this_object()
#define REG_LOG       "/d/Avenir/log/registry"

#define TP	this_player()


int     counter,
        i;

void 
create_monster()
{
    /* If I'm not a clone, don't proceed */
    if (!IS_CLONE)
        return;

    /* Lets make sure the sybarite stuff is initialized */
    ::create_sybarite();

    set_name("ryter");
    set_living_name("ryter");
    add_name("scribe");
    set_race_name("human");
    set_adj("dark-haired");
    add_adj("slender");
    set_title("the scribe");
 
    set_long("He is a slender fellow, appearing to be rather bookish.\n"+
        "His hair and eyes are dark, while his skin is quite pale.\n");
   
    set_gender(G_MALE);
    default_config_npc(random(70) + 50);

    config_default_trade();

    set_alignment(0);

    add_ask(({ "pay", "buy", "fee", "seal", "cost" }), 
        "say I sell seals. The cost is 5 platinum coins.", 1);
    add_ask(({ "shadows" }), "say They bind and protect us.", 1);
    add_ask(({ "source" }), "say It is a sacred gift of the Gods.", 1);
    add_ask(({ "skills" }), "say I have many skills.", 1);
    add_ask(({ "register", "registry" }), "say You may register here. "+
       "Read the sign for instructions.", 1);
    add_ask(({ "help" }), "say Read the signs. If you don't understand "+
       "them, make a report.", 1);


   add_prop(CONT_I_HEIGHT, 200);

   seteuid(getuid());
}

void 
init_living()
{
  ::init_living();
   
   add_action(do_buy, "buy");
}

int
do_buy(string str) 
{
    object seal;
    int *arr, price, silent, i;
 
    if (!CAN_SEE(this_object(), TP))
    {
        command("say Come out so I can see you first!");
        return 1;
    }
   
    if (IS_INFIDEL(this_player()))
    {
        command("emote points south");
        command("say to "+ TP->query_real_name() +" Filthy "+
            "law-breakers are not welcome here.");
        command("say Leave, else I will fetch the guards.");
        return 0;
    }

    seal = clone_object("/d/Avenir/registry/seal");
    seal->move(this_object(),1);
    price = 8640;
   
    arr = pay(price, this_player(), "", 0, 0, "");
    if (sizeof(arr) == 1) 
    {
        command("say A seal costs 5 platinum coins. You don't have enough money.");
        seal->remove_object();
        return 1;
    }
    {
        /* he paid for it */
        command("say Here's your seal.");
        command("give seal to "+ this_player()->query_real_name());
        STATSERV_LOG_EVENT("registry", "Seals purchased");
        SCROLLING_LOG(REG_LOG, "Registrar sold seal to " + TP->query_name());
    }
    return 1;
}
