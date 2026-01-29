/*
 * Chert Armstrong
 * modified from Toede.
 * by Teth
 * Jan.12,'97
/*
 * Added support for the commerce module in July 2002, by Boron
 * Also added the scalearmour to this buy.
 */
 /*



.
Eagledraco asks Chert: magical scale
Eagledraco asks Chert: dragon
Eagledraco asks Chert: dragon scale
The well-muscled black-bearded male dwarf wipes the sweat from his brow.

Eagledraco asks Chert: stock
*/

#include <std.h>
#include <ss_types.h>
#include <wa_types.h>
#include <stdproperties.h>
#include <filter_funs.h>
#include "../local.h";
#include "../knight/guild.h"

#include <macros.h>

inherit "/sys/global/money";
inherit M_FILE /* The Krynn humanoid monster file */
inherit "/d/Genesis/lib/commerce";

inherit "/std/act/action";

#define SHOP_STORE_ROOM  VROOM + "sol_store2"
#define PLAYER_I_SOLD    "_player_i_sold_to_chert"

void
preload_commodities(string *commod)
{
    object *wizard = map(({ "boron" }), find_player);

    if (!sizeof(commod))
    {
        return;
    }

    this_object()->hook_commerce_amount_update(commod[0], 0);
    set_alarm(0.5, 0.0, &preload_commodities(commod[1..]));
}

public void
remove_object()
{
    remove_commerce();

    ::remove_object();
}

/*
 * Function name : hook_commerce_buy_prevent_buy
 * Description   : function is the last validator in the chain of buy
 *                 validators, when it returns false specified commodity
 *                 would be bought for sure, and when it returns 1 it
 *                 would not, this hook must generate it's own messages
 *                 when returning true
 * Arguments     : object  - the master object of commodity player buys
 *                 int     - the quantity of item he tries to buy
 * Returns       : int     - 1 when buy is prevented or 0 otherwise
 */
public int
hook_commerce_buy_prevent_buy(object commod, int amount)
{
    int value;

    if (!MEMBER(TP))
    {
        command("I only sell to Solamnian Knights");
        return 1;
//        value = TP->query_prop(PLAYER_I_SOLD);
//        if (value > commod->query_commodity_value())
//        {
//          command("say With the effort you put into this, there is nothing for you!");
//
//          return 1;
//        }
//        else
//        {
//            TP->add_prop(PLAYER_I_SOLD, value - commod->query_commodity_value());
//        }
    }

    return 0;
}

/*
 * Function name : hook_commerce_sell_prevent_sell
 * Description   : function is the last validator in the chain of sell
 *                 validators, when it returns false specified commodity
 *                 would be sold for sure, and when it returns 1 it
 *                 would not, this hook must generate it's own messages
 *                 when returning true (please do not destruct or split
 *                 the passed object, p.s. parsing macros split heaps)
 * Arguments     : object  - the commodity object player sells
 * Returns       : int     - 1 when sell is prevented or 0 otherwise
 */
public int
hook_commerce_sell_prevent_sell(object commod)
{
    int value;
    int prestige;

    if (MEMBER(TP))
    {
       prestige = commod->query_commodity_value() < 500 ? commod->query_commodity_value() : 500;
       prestige = prestige / (TP->query_knight_level() + TP->query_knight_sublevel());

       TP->change_prestige( prestige );
       command("say May Paladine bless you!");
    }
    else
    {
        command("say I only accept those from Solamnian Knights");
        return 1;
        // Normally it takes a number of ingridients to create a
        // valueable commodity, we only credit for one third of the
        // value
//        value = TP->query_prop(PLAYER_I_SOLD);
//        value = value + (commod->query_commodity_value() / 3);
//        TP->add_prop(PLAYER_I_SOLD, value);
    }

    return 0;
}


public void
create_krynn_monster()
{
    set_name("chert");
    set_living_name("chert");
    set_race_name("dwarf");
    set_title("Armstrong of Thorbardin, Famed Blacksmith");
    set_long("This dwarf is well-muscled. A black beard sprouts " +
      "from his chin and cheeks in disarray, while deep black eyes " +
      "glare beneath a sweating forehead. He is obviously a " +
      "blacksmith.\n");
    add_name(({"armstrong","blacksmith","smith"}));
    set_adj("well-muscled");
    add_adj("black-bearded");
    set_gender(G_MALE);
    add_prop(CONT_I_HEIGHT, 120);
    add_prop(CONT_I_WEIGHT, 30000);
    add_prop(NPC_I_NO_LOOKS,1);
    add_prop(LIVE_M_NO_ACCEPT_GIVE, 1);
    set_introduce(1);

    set_stats(({120,90,200,60,60,120}));
    set_skill(SS_DEFENCE,        100);
    set_skill(SS_PARRY,          100);
    set_skill(SS_WEP_CLUB,       100);
    set_skill(SS_BLIND_COMBAT,   100);

    set_alignment(440);
    set_knight_prestige(-2);

    // Add commerce support
    set_commerce_savefile("/d/Krynn/common/commerce/chert_data");
    config_default_trade();

    add_demanded_commodity("iron bar", 2, 250, 1.3);
    set_commodity_amount("iron bar", 40);
    set_commodity_reserve("iron bar", 30);

    add_demanded_commodity("carbon bar", 3, 60, 1.8);
    set_commodity_amount("carbon bar", 10);
    set_commodity_reserve("carbon bar", 8);

    add_demanded_commodity("carbonpiece", 5, 60, 1.5);
    set_commodity_amount("carbonpiece", 10);
    set_commodity_reserve("carbonpiece", 8);

    add_demanded_commodity("silver bar", 7, 30, 1.5);
    set_commodity_amount("silver bar", 0);
    set_commodity_reserve("silver bar", 8);

    add_demanded_commodity("scale", 11, 8, 3.0);
    set_commodity_amount("scale", 0);
    set_commodity_reserve("scale", 1);

    add_demanded_commodity("full_armour", 13, 6, 1.3);

    add_supplied_commodity ("Sol.2H.lsword", 17, 2, 1.3);
    set_commodity_amount("Sol.2H.lsword", 2);
    add_supply_requirement("Sol.2H.lsword",
                    ({ "iron bar", 2, "carbon bar" , 1}) );

    add_supplied_commodity("scalearmour", 19 , 4, 2.0);
    set_commodity_amount("scalearmour", 0);
    add_supply_requirement("scalearmour",
                    ({ "silver bar", 1, "full_armour" , 1, "scale", 1}) );

    add_supplied_commodity("s_boots", 23, 2, 1.1);
    set_commodity_amount("s_boots", 1);
    add_supply_requirement("s_boots",
                    ({ "iron bar", 1, "carbonpiece" , 1}) );

    add_supplied_commodity("s_halberd", 29, 3, 1.2);
    set_commodity_amount("s_halberd", 1);
    add_supply_requirement("s_halberd",
                    ({ "iron bar", 2, "carbonpiece" , 1}) );

    add_supplied_commodity("s_armour", 31, 3, 1.1);
    set_commodity_amount("s_armour", 1);
    add_supply_requirement("s_armour",
                    ({ "iron bar", 2, "carbonpiece" , 1}) );

    add_supplied_commodity("s_gauntlets", 37, 2, 1.1);
    set_commodity_amount("s_gauntlets", 1);
    add_supply_requirement("s_gauntlets",
                    ({ "iron bar", 1, "carbonpiece" , 1}) );

    add_supplied_commodity("s_helm", 41, 3, 1.1);
    set_commodity_amount("s_helm", 1);
    add_supply_requirement("s_helm",
                    ({ "iron bar", 2, "carbonpiece" , 1}) );

    add_supplied_commodity("s_shield", 43, 3, 1.1);
    set_commodity_amount("s_shield", 1);
    add_supply_requirement("s_shield",
                    ({ "iron bar", 1, "carbon bar" , 1}) );

    set_default_answer("Judging from the looks on his face, he seems " +
      "to think you speak nonsense.\nHe shakes his " +
      "head as if you are going crazy and continues his work.\n");
    add_ask(" [about] 'wax' / 'repair'", "say Read the sign!",1);
    add_ask(" [about] 'task' / 'quest'", "say Get me some supplies "+
      "you shall be rewarded handsomely!",1);
    add_ask(" [about] 'steel'","say Solamnian steel is some of " +
      "the finest in the land! I craft weapons and armours, but " +
      "I need iron and carbon!",1);
    add_ask(" [about] 'carbon'","say Solamnian steel is some of " +
      "the finest in the land one of the core ingredients of steel " +
      "is carbon, I'd be happy to pay for it if need be!",1);
    add_ask(" [about] 'iron'","say Iron is a key ingredient in the " +
      "fine Solamnian steel.",1);
    add_ask(" [about] 'stock'", "@@list_my_stock", 1);
    add_ask(" [about] 'weapons'", "say I can make weapons aye, ask " +
      "about my stock if you want to know which", 1);
    add_ask(" [about] 'ingredients'", "say Ingredients for what? my " +
      "two main ingridients are carbon and iron, thats for making " +
      "steel!", 1);
    add_ask(" [about] 'armours'", "say Aye I make armours, you can buy "+
      "them in the shop up there. I'm also experimenting with some rather "+
      "interesting techniques where I can use material which is already magic!", 1);
    add_ask(" [about] 'order'", "say Order? Ask about the stock if you " +
      "wanna know what I might have, and then buy what ya need, not like " +
      "the little rodent who just grabs it...", 1);

    add_ask(" [about] [lance] [sword] [mace] [club] [blade]", "say Just " +
      "buy what you want from the shop...  that'll be more then others " +
      "do 'round here", 1);

    add_ask(" [about] 'rodent'", "say Ya know who I mean, the little... " +
      "Aaarggh - I never should've hired 'im!", 1);
    add_ask(" [about] 'kender'", "say Yeah what 'bout 'im? Don't go " +
      "mess with him, he 'pose to work not play!", 1);
    add_ask(" [about] [quality] 'material'", "say The dwarves in the "+
      "mountains mine some good material, their smith makes it into " +
      "some nice bars too!", 1);
    add_ask(" [about] [magic] [magical] [weapons] [armours] [weapon] [armours]",
      "@@magic_items", 1);
    add_ask(" [about] [magic] [magical] [ingredient] [ingredients] [material] ",
      "say I'm not too sure what magic to experiment with... but those " +
      "dragons are said to be all magic... maybe something from them!?", 1);
    add_ask(" [about] [dragon] [dragons]", "say Aye! By Reorx! They say the " +
      "evil dragons have returned!", 1);
    add_ask(" [about] 'reorx'", "say Well he created the world! How much "+
      "greater can ya be? I'll tell ya, being the only God who can empty "+
      "an ocean of beer now thats a God!", 1);
    add_ask(" [about] 'griffon'", "shout Nooo! Not you too! Its enough the " +
      "rodent is rambling on 'bout griffons - I don't care 'bout 'em!", 1);
    add_ask(" [about] [iron] [silver] [carbon] [supply] [supplies]",
      "@@check_supply", 1);

    set_act_time(26);
    add_act("emote throws a quick glance at the piles in the corner");
    add_act("emote checks up on his iron supply");
    add_act("emote checks up on his carbon supply");
    add_act("emote checks up on his silver supply");
    add_act("say I am sure the dwarven craft will help turn the tide " +
      "of evil back...");
    add_act("say The dwarves in the mountains are mining some really " +
      "good material!");
    add_act("say If someone could just fetch some quality material " +
      "for me...");
    add_act("say Steel is a fine metal to work with!");
    add_act("say I really need iron and carbon!");
    add_act("say Aye, my stock grows slowly now... atleast until the " +
       "knights come and clean it out, or the little rodent!");


    add_act("emote looks at his work with appraising glances, ensuring " +
      "quality.");
    add_act("emote throws a quick look at the iron in the corner.");
    add_act("emote hammers a piece of metal repeatedly!\n\nCLANG!\n\n" +
      "CLANG!\n\nCLANG!\n\n\n");
    add_act("emote uses the bellows to stoke the fire.");
    add_act("say One day, I wish my craftsmanship would rival that of " +
      "the ancient dwarves!");
    add_act("shout By Reorx! I'm a fine craftsman!");
    add_act("emote wipes the sweat from his brow.");
    add_act("say If I'm slow in reacting t'day, it might be cause of the " +
      "bad weather I'm experiencing...");

    set_cact_time(3);
    add_cact("shout I'll smash your head soft like molten metal!");
    add_cact("shout Someone dares to attack me! Fool!");

    // lets move default items to shop
    preload_commodities(query_supplied_commodity());
}

void
write_debug(string str)
{
   object wizard = find_player("boron");

   if (!objectp(wizard))
     return;

   if ( environment(wizard) == environment(TO) )
      wizard->catch_tell(str);

}

/*
 * This function will return a percentage of what is in
 * stock of the pass commodity.
 */
public int
query_stock(string commod)
{
    int cap;
    int amo;
    int res;

    write_debug("Query stock on " + commod + "\n");

    if (!exist_demanded_commodity(commod))
      return 0;


    cap = query_commodity_capacity(commod);
    amo = query_commodity_amount(commod);
    res = amo * 100;

    write_debug("cap " + cap + "\tamo " + amo + " -- ");

    write_debug("res = amo * 100: " + amo * 100 + "  -- ");

    if ( res <= 0 )
       return 0;

    write_debug("res / cap: Percentage: " + res / cap + "\n");

    return (res / cap);
}


/*
 * We hook up here so we can move the object to the stock room, when
 * Chert is done making them.
 *
 * Items not going to the stock room includes objects which are not
 * allowed to be sold in a shop, ie. magic items like the scalemail
 *
 * -Boron, July 2002
 */
public void
hook_commerce_amount_update(string commod, int amount)
{
    //object *wizard = map(({ "boron"  }), find_player);
    object *oblist;
    object *ob;
    string  result;

    /*wizard->catch_tell("\n\nChert the Blacksmith reports:\nI am" +
        " producing " + amount + " units of " + commod + "\n");*/

    if (!exist_supplied_commodity(commod) || (commod == "scalearmour"))
    {
        return 0;
    }

    // Lets give the players a nice experience too
    if (E(TO) && amount)
    {
        ob = all_inventory(E(TO));
        ob = FILTER_PLAYERS(ob);
        if (ob && sizeof(ob))
        {
            ob->catch_msg("The kender arrives with a huge grin, he grabs "+
              "some newly made equipment and carries it north to the shop.\n" +
              "A kender arrives.\n" + QCTNAME(TO) + " throws quick glance at " +
              "the kender and grumbles: everything better be there when I " +
              "check the shop later.\nThe kender gets an offended look on his " +
              "face and hmpfs imitating a dwarf while running into the back room " +
              "with an old piece of iron flying after him.\n");
            command("curse wild");
            command("say That rodent!");
        }
    }

    amount = query_commodity_amount(commod); /* stock amount */
    add_commodity_amount(commod, -amount);   /* remove stock */

    /* clone_commodity would return array of cloned object   */
    /* with size 'amount' or a heap array with size '1'      */

    oblist = clone_commodity(MASTER_OB(find_commodity(commod)), amount);
    amount = sizeof(oblist);
    result = val2str(map(oblist, &->move(SHOP_STORE_ROOM, 1)));

    /*wizard->catch_tell("Tried to move " + amount + " such an " +
      "item(s) to the store with these results: "+ result +
      " check: 'sman /std/object move' for error result.\n");*/


}

string
check_supply()
{
    command("say The piles there.");
    command("emote points at his piles in the corner.\nYou notice a " +
      "pile of silver, carbon and iron in the corner of the forge.");
    return "say That's all I have...";
}

/*
 * This function should give a response to magic,
 * Return the string as a command.
 * VBFC'ed from an add_ask
 */
string
magic_items()
{
    command("grumble");
    command("say I don't like magic more than any Knight...");
    command("shout I saw that! Get back to work in there, stop " +
       "playing with the water!");
    command("curse wild");
    command("say What did you ask again?");
    command("emote continues: Ahh yes magic... now there is some " +
       "trickery!  ...you know, now knights even have to fight " +
       "magical dragons!");
    return "say What if there was a way to combine the powers " +
       "of Reorx, use m' talents as a smith, and have evil turn " +
       "on it self?";
}


/*
 * This function should list what the dwarf have in stock
 * Return the string as a command.
 * VBFC'ed from an add_ask
 */
string
list_my_stock()
{
   return "say I'm trying to work out how to make some really nice " +
     "armours, anything else is sold in the shop!\n";
}

public void
init_living()
{
    ::init_living();
    init_commerce();
    add_action("payit", "pay");
}

int
payit(string str)
{
   object ob;

   if ((str=="chert") || (str=="for iron bar"))
   {
      if (!MEMBER(TP))
      {
          TO->command("say I only sell to the Solamnian Knights.");
          return 1;
      }

      if (!take_money(TP,120))
      {
         TO->command("say You don't have enough"+
            " money to pay me. Come back when you have earned some more.");
         return 1;
      }
      else
      {
         ob=clone_object("/d/Shire/smiths/obj/ir_bar");
         if (ob->move(TP)!=0)
         {
            TO->command("say Hmm.. It seems you cannot even carry the"+
               " bar; You'll need quite a bit of luck being as weak as"+
               " you are. I will drop the bar on the floor for you.");
            ob->move(environment(TP));
         }

         TO->command("say It is a pleasure dealing with you. Good luck"+
            " with the forging.");
         TP->catch_msg("You are handed an iron bar.\n");
         return 1;
      }
   }
}


public string
stat_living()
{
    return ::stat_living() + stat_commerce();
}

public void
arm_me()
{
    clone_object(VWEP + "smith_hammer")->move(TO);
    clone_object(VARM + "s_shield")->move(TO);
    command("wield all");
    command("wear all");
}


