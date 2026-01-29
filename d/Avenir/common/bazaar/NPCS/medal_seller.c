// Lilith Jun 1996
// cloned to /d/Avenir/common/bazaar/extr/str22

inherit "/std/monster";
inherit "/lib/trade";
inherit "/d/Avenir/common/bazaar/NPCS/call_for_help";

#include "/d/Avenir/common/bazaar/bazaar.h"
#include "/d/Avenir/include/relation.h"
#include <macros.h>
#include <money.h>

// if more medallions, raise this number, so he can sell them
#define MEDNUM        78
#define MEDAL_LIST    "/d/Avenir/common/bazaar/Obj/misc/medal_list"
#define NUM           sizeof(MONEY_TYPES)
#define PRICELIST_ID  ({"pricelist","list","prices",})

void
create_monster()
{
   ::create_monster();

   config_default_trade();
   default_config_npc(90);
   
   set_name("chuck");
   add_name(({"chuckie", "gobbo"}));
   set_adj(({"handsome", "perfumed"}));
   set_race_name("goblin");
   set_gender(0);
   set_short("goblin wearing medallions pinned to his cloak");
   set_long("He is almost handsome, for a goblin, and some small "+
      "spark of intelligence glows in his dull eyes. He is wear"+
      "ing a cloak covered with dozens of medallions, examples of what "+
      "he is offering for sale. He wears a list hanging on a chain "+
      "from his neck.\n");

   set_act_time(10);
   add_act("shout Medallions for sale!");
   
   
}

int
do_buy(string str) 
{
    object button;
    int bnum;
    int *arr, price, silent, i;
   
    if (IS_INFIDEL(this_player()))
    {
        command("say Goblin am I, but Infidel are you.");        
        command("say No trading with you! Go.");
        return 0;
    }
    if (!str)
    {
        notify_fail("The goblin says: Buy what? Trying using the "+
            "medallion's number only, like this: buy 10.\n");
        return 0;
    }
   
    if ( (sscanf(str,"%d", bnum)) != 1)
    {
        notify_fail("Buy what? Read the list, then try to buy using "+
            "just the medallion number.\n");
        return 0;
    }
   
   
    if ( (bnum > MEDNUM) || (bnum < 0) )
    {
        notify_fail("The goblin says: I don't have that one.\n");
        return 0;
    }
    else
    {   
        button = clone_object(MISC +"medallion");
        button->set_button(bnum);
        button->move(this_object(),1);
        price = 144;
    }
   
    arr = pay(price, this_player(), "", 0, 0, "");
    if (sizeof(arr) == 1) 
    {
        command("say Hey! These valuable items aren't free ya know!");
        button->remove_object();
        return 1;
    }
    else
    {
        /* he paid for it */
        command("say Here's your medallion, "+check_call(QTNAME(this_player()))+".");
        command("give button to "+lower_case(this_player()->query_real_name()));
    }
    return 1;
}

int
do_read(string str)
{
    string text;

    if ( (str!="list") && (str!="items") )
    {
        notify_fail("Read What?\n");
        return 0;
    }
    setuid();
    seteuid(getuid());
    text = read_file(MEDAL_LIST);
    this_player()->more(text);
    return 1;
}

void
init_living()
{
    ::init_living();
    add_action(do_read,"read",0);
    add_action(do_buy,"buy",0);
   
}
