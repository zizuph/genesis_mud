/*
 *  The Sailors pub in Pelargir dock-area.
 */

inherit "/d/Gondor/common/room";
inherit "/lib/trade";

#include <language.h>
#include <macros.h>
#include <money.h>
#include <stdproperties.h>

#include "/d/Gondor/defs.h"

#define STAND_DIR "/d/Gondor/pelargir/obj/"
#define MY_PRICES ({ 15, 24, 72, 180, 288, 12, 24, 48 })
#define NUM sizeof(MONEY_TYPES)

int     can_afford(int price, string ware);
string  price_long();
void    reset_room();

int     clone_alarm;
object *citizens = allocate(3);
string  pay_type,
        get_type;

void
create_room()
{
   set_short("the Broken Oar Tavern");
   set_long(
      "You are in the Broken Oar Tavern. The place seems crowded with "
    + "rowdy-looking men, sailors from the ships docked nearby, or "
    + "dockworkers and other kinds of rabble. Tobacco-smoke hangs "
    + "thick in the air, and the noise of loud discussions, laughter "
    + "and singing, makes it difficult to talk normally in here. On "
    + "the wall behind the bar counter is a pricelist and menu.\n");

    add_exit(PELAR_DIR + "streets/shipwright04", "east", 0, 0);

   add_item(({"rug","remains of rug"}),
      "The rug was once beautiful and red, but now it is grey and full of holes.\n");
   add_item(({"table","tables","chair","chairs"}),
      "All the tables and chairs are taken by other visitors.\n");
   add_item(({"panels", "wooden panels"}),
      "You notice nothing special about the wooden panels.\n");
   add_item("counter", BSN(
      "Above the wooden counter is a lamp and a shelf. On the shelf "
    + "are several brands of liquor. Behind the counter is the innkeeper of "
    + "the Broken Oar Tavern, Grimbold, the owner of the tavern."));
   add_item(({"innkeeper","barkeeper","bartender","owner", "grimbold"}),
      BSN("The barkeeper, Grimbold, is a typical Dunadan, with a stern "
    + "face. He seldom takes a break, but runs between the kitchen and "
    + "the bar serving his customers, trying to keep the glasses as "
    + "shiny as possible, and the meals hot and delicious. Grimbold "
    + "looks at you, waiting for you to order something."));
   add_prop(ROOM_I_INSIDE,1);  /* This is a real room */
   config_default_trade();
   set_money_give_max(2000);
   set_money_give_out(({ 2000, 700, 50, 4}));
   set_money_give_reduce(({1,1,1,1}));

   add_cmd_item(({"pricelist","list","prices","menu"}), "read", price_long());
   add_item(({"pricelist","list","prices","menu"}), price_long());
   reset_room();
}

void
init()
{
    ::init();
/*
 * This one does not seem to be used.
    add_action("do_read","read",0);
 */
    add_action("do_buy","buy",0);
    add_action("do_buy","order",0);
    add_action("chk_time","time");
}

string
price_long()
{
   return (
      "The pricelist reads:\n\n"
    + "DRINKS:\n"
    + sprintf("   %-24s ... %28s\n", "Golden Ale",
        text(MONEY_SPLIT(MY_PRICES[0])))
    + sprintf("   %-24s ... %28s\n", "Beer from Pelargir",
        text(MONEY_SPLIT(MY_PRICES[1])))
    + sprintf("   %-24s ... %28s\n", "Wine from Lebennin",
        text(MONEY_SPLIT(MY_PRICES[2])))
    + sprintf("   %-24s ... %28s\n", "Whiskey from Dol Amroth",
        text(MONEY_SPLIT(MY_PRICES[3])))
    + sprintf("   %-24s ... %28s\n\n", "Rum from Belfalas",
        text(MONEY_SPLIT(MY_PRICES[4])))
    + "HOT MEALS:\n"
    + sprintf("   %-24s ... %28s\n", "Porridge",
        text(MONEY_SPLIT(MY_PRICES[5])))
    + sprintf("   %-24s ... %28s\n", "Fish stew",
        text(MONEY_SPLIT(MY_PRICES[6])))
    + sprintf("   %-24s ... %28s\n", "Bacon and beans",
        text(MONEY_SPLIT(MY_PRICES[7])))
    +"\n");
}

int
do_buy(string str)
{
    object  item;
    string  item_name,
            get_type,
            pay_type;
    int     iHave = 0;

    if (!strlen(str))
        return 0;

    if (sscanf(str,"%s for %s and get %s", item_name,pay_type,get_type) != 3)
    {
        get_type = "";
        if (sscanf(str,"%s for %s", item_name, pay_type) != 2)
        {
            pay_type = "";
       	    item_name = str;
        }
    }

    switch (str)
    {
        case "ale":
        case "golden ale":
            if (can_afford(MY_PRICES[0], "ale"))
                item = clone_object(STAND_DIR + "ale");
            iHave = 1;
            break;
        case "beer":
            if (can_afford(MY_PRICES[1],"beer"))
                item = clone_object(STAND_DIR + "beer");
            iHave = 1;
            break;
        case "wine":
            if (can_afford(MY_PRICES[2],"wine"))
                item = clone_object(STAND_DIR + "wine");
            iHave = 1;
            break;
        case "whiskey":
            if (can_afford(MY_PRICES[3],"whiskey"))
                item = clone_object(STAND_DIR + "whiskey");
            iHave = 1;
            break;
        case "rum":
            if (can_afford(MY_PRICES[4],"rum"))
                item = clone_object(STAND_DIR + "rum");
            iHave = 1;
            break;
        case "porridge":
            if (can_afford(MY_PRICES[5],"porridge"))
                item = clone_object(STAND_DIR + "porridge");
            iHave = 1;
            break;
        case "fish stew":
        case "stew":
        case "fish":
            if (can_afford(MY_PRICES[6],"fish stew"))
                item = clone_object(STAND_DIR + "stew");
            iHave = 1;
            break;
        case "beans and bacon":
        case "beans":
        case "bacon":
            if (can_afford(MY_PRICES[7],"beans and bacon"))
                item = clone_object(STAND_DIR + "beans");
            iHave = 1;
            break;
    }
    if (!iHave)
    {
        NFN("The innkeeper says: We don't have that on the menu.");
        return 0;
    }

    if (item->move(TP))
    {
        write("The bartender places the "+item->short()+" in front of you, since you can't carry it.\n");
        item->move(TO);
    }
    say(QCTNAME(TP) + " orders "+LANG_ADDART(item->short())+".\n");
    return 1;
}

/* Test if this_player has more money on him than the price */
int
can_afford(int price, string ware)
{
    int    *money_arr;
    string  coin_pay_text,
            coin_get_text;

    if (sizeof(money_arr = pay(price, this_player(),pay_type,0,0,get_type)) == 1)
    {
        if (money_arr[0] == 2)
        {
	       tell_room(TO, "The innkeeper says: You haven't got any "+pay_type+
              " coins, honoured "+QNAME(TP)+".\n");
	          return 0;
	    }

        if (money_arr[0] == 1)
	    {
           tell_room(TO, BSN(
               "The innkeeper says: You haven't got enough "+pay_type+
               " coins to pay for the "+ware+", honoured "+QNAME(TP)+"."));
	      return 0;
	    }
        else
	    {
            tell_room(TO, BSN(
               "The innkeeper says: When you have enough money for it, I would "+
               "be glad to serve you "+ware+"."));
	        return 0;
	    }
    }
    coin_get_text = text(money_arr[NUM..]);
    coin_pay_text = text(money_arr[..NUM-1]);
    write("You order a "+ware+" and pay "+coin_pay_text+".\n");
    if (coin_get_text)
        write("The innkeeper hands you "+coin_get_text+" back in change.\n");
    return 1;
}

chk_time()
{
  write("You ask the innkeeper what time it is.\n");
  say(QCTNAME(this_player())+" asks the innkeeper what time it is.\n",this_player());
  tell_room(this_object(),"The innkeeper says: It is about "+qstime()+".\n");
  return 1;
}

void
clone_citizen()
{
    int     i;

    for (i = 0; i > sizeof(citizens); i++)
    {
        if (!objectp(citizens[i]))
        {
            citizens[i] = clone_object(PELAR_DIR + "npc/citizen");
            citizens[i]->arm_me();
            citizens[i]->add_act("emote orders a wine.");
            citizens[i]->add_act("emote drinks a wine.");
            citizens[i]->move_living("down", TO);
            if (!(clone_alarm && sizeof(get_alarm(clone_alarm))))
                clone_alarm = set_alarm(itof(30) + 60.0 * rnd(), 0.0, clone_citizen);
            return;
        }
    }
}

void
reset_room()
{
    set_alarm(15.0 + 30.0 * rnd(), 0.0, clone_citizen);
}

