#include "../stddefs.h"
#include <stdproperties.h>
#include <macros.h>
#include <language.h>

#pragma save_binary

inherit ELFROOM;
inherit "/lib/shop";


#define EAST     ROOMDIR + "vill_road_3"
#define STORE    ROOMDIR + "vill_store"


#define NAT_SHORT "In Melien Tamsin's office"
#define FOR_SHORT "In a trader's office"

#define NAT_LONG \
  "This is trader Melien Tamsin's office. " + \
  "The walls are covered with dark oak " + \
  "panels, and there are thick, exclusive carpets on the floor. A huge " + \
  "desk takes up a major part of the room, most of its surface covered " + \
  "with papers with strange calculations.\n" + \
  "Behind the desk sits Melien Tamsin, a somewhat podgy dark-haired sprite, "+\
  "on a high stool. He is dressed in sober-colored, expensive-looking "+\
  "clothing of a conservative cut, which contrast oddly to the gaudy riot "+\
  "of colours on his butterfly-like wings.\n" + \
  "On the desk is a small, discreet " +\
  "sign, engraved with simple, old-fashioned letters.\n"
#define FOR_LONG \
  "This room looks mostly like an office. " + \
  "The walls are covered with dark oak " + \
  "panels, and there is thick carpets on the floor. A huge " + \
  "desk takes up a major part of the room, most of its surface covered " + \
  "with papers.\n" + \
  "Behind the desk sits a somewhat podgy dark-haired sprite "+\
  "on a high stool. He is dressed in sober-colored "+\
  "clothing of a conservative cut, which contrast oddly to the gaudy riot "+\
  "of colours on his butterfly-like wings.\n" + \
  "On the desk is a small, discreet " +\
  "sign, engraved with simple, old-fashioned letters.\n"

#define INSTRUCTIONS \
  "You can try these commands: \n" + \
  "    buy sword for gold and get copper back\n" + \
  "    buy sword for gold coins\n" + \
  "    sell sword for copper coins\n" + \
  "    sell all  - will let you sell all items except for\n" + \
  "                items you wield or wear.\n" + \
  "    sell all! - will let you sell ALL items you have, well\n" + \
  "                at least the droppable, and no coins.\n" + \
  "    sell sword, sell second sword, sell sword 2, sell two swords\n" + \
  "                also works. You might want to change the verb to\n" + \
  "                'value' or 'buy' too. Beware, you will never buy\n"+ \
  "                more than one item at a time, so if you really want\n" + \
  "                those three expensive swords, you have to repeat\n" + \
  "                yourself three times.\n" + \
  "    If you want a list of all swords available in the store, the\n" + \
  "    correct syntax is: list sword\n" + \
  "    (not: list swords, though this might change) \n"


#define PANEL_ITEM ({"panel", "panels", "oak panel", "oak panels"})
#define PANEL_DESC \
  "The oak panel on the walls have their dark colour from age, not " + \
  "from varnish or paint.\n"

#define DESK_ITEM ({"desk", "huge desk"})
#define DESK_DESC \
  "It is hard to see the desk for all papers.\n"

#define PAPER_ITEM ({"paper", "papers", "calculation", "calculations"})
#define PAPER_DESC \
  "The papers are filled with complex calculations, that seem to be " + \
  "set up according to some weird tabular arrangement that simply is " + \
  "too strange for you to follow.\n"

#define CARPET_ITEM ({"carpet", "carpets", "floor"})
#define CARPET_DESC \
  "The carpets are thick, soft, wide, and have simple geometric patterns " +\
  "woven in muted red, brown and purple colours."

#define SPRITE_ITEM ({"sprite", "pudgy sprite", "trader", "trader tamsin", \
		"melien", "tamsin", "melien tamsin", "trader melien tamsin"})
#define SPRITE_DESC \
  "His hair is a dark, mousy brown, but the weary eyes are brilliantly, " +\
  "almost glowing green, looking out between a high forehead and small " + \
  "snub-nose. " + \
  "His features have probably sometime in the past been sharp and pointy, " +\
  "but now some more flying probably would do him good. The expensive cut " +\
  "of his clothes cannot totally hide a pot-belly, and he has the "+\
  "beginning of a double chin.\n" + \
  "He is dressed in dark grey and blue clothes of "+\
  "costly simpleness, contrasting to the swirls and complex patterns of "+\
  "bright, gaudy colours that covers the butterfly wings that grow from "+\
  "his back.\n"

#define SPRITE \
  check_call(N_KNOW("Melien Tamsin", "the podgy sprite"))
#define C_SPRITE \
  check_call(N_KNOW("Melien Tamsin", "The podgy sprite"))

#define SIGN_ITEM ({"sign", "plate" })
#define SIGN_DESC   "The sign reads:\n" 

sprite_The_met_name() 
{ 
  if (previous_object() && IS_NATIVE(previous_object()))
    return "Melien Tamsin";
  else 
    return "The podgy sprite";
}


#define WIZINFO \
  "You'll find the store room belonging to this shop in '" + STORE + "'.\n"


#define FAIL_MSG(STR)  notify_fail(WRAP(C_SPRITE + " says: " + STR))
#define SPRITE_MSG(STR)  \
  say("@@sprite_The_met_name:"+file_name(this_object())+ "@@ says: " + STR);\
  write(WRAP(C_SPRITE + " says: " + STR));


#define MAXLIST 30
#define MONEY_NUM 4

void  
create_room()
{    
    config_default_trade();
    set_short(N_KNOW(NAT_SHORT, FOR_SHORT));
    set_long( N_KNOW(WRAP(NAT_LONG),
		     WRAP(FOR_LONG)));
    
    add_item( PANEL_ITEM, WRAP( PANEL_DESC));
    add_item(  DESK_ITEM, WRAP(  DESK_DESC));
    add_item( PAPER_ITEM, WRAP( PAPER_DESC));
    add_item(CARPET_ITEM, WRAP(CARPET_DESC));
    add_item(SPRITE_ITEM, WRAP(SPRITE_DESC));
    add_item(  SIGN_ITEM, WRAP(  SIGN_DESC + INSTRUCTIONS)); 
    
    add_cmd_item(SIGN_ITEM, "read", WRAP(SIGN_DESC + INSTRUCTIONS));
    
    add_prop(ROOM_I_INSIDE, 1);
    STD_WIZINFO;
  
    add_exit(EAST,      "east", 0);

    set_store_room(STORE);
    set_money_greed_sell("@@discriminate@@");

    /* set_money_give_out(   ({ 10000,   700,   5,    1 }));
     * set_money_give_reduce(({     0,     4,   2,    1 }));
     * stock();
     */
}


stock()
{
}

wizinfo()
{
  return WRAP(WIZINFO);
}

void 
init()
{
   ::init();   /* You MUST do this in a room-init */
   init_shop(); /* Get the commands from the shop */

   /* add_action("do_buy", "buy");
    * add_action("do_sell", "sell");
    * add_action("do_value", "value");
    * add_action("do_list", "list");
    */
}


discriminate() 
{
  if (IS_NATIVE(this_player()))
    return 100;
  else
    return 110;
}

void
shop_hook_sell_no_value(object ob)
{ 
    FAIL_MSG("I'm sorry, but " + LANG_THESHORT(ob) +
	     " has no value.\n"); 
}

void
shop_hook_sell_worn_or_wielded(object ob)
{
    FAIL_MSG("I normally don't buy wielded or worn objects.\n");
}

void
shop_hook_sell_no_sell(object ob, string str)
{
    if (stringp(str))
      notify_fail(str);
    else
      FAIL_MSG("I don't want " + LANG_THESHORT(ob) + ".\n");
}

void
shop_hook_sell_object_stuck(object ob, int err)
{
    FAIL_MSG("It seems to me that you are stuck with that.\n");
}

int
shop_hook_buy_no_match(string str)
{
    FAIL_MSG("I'm sorry, but I don't have any " + str + " to sell.\n");
    return 0;
}

void
shop_hook_buy_magic_money(object ob)
{
    SPRITE_MSG("You are carrying magic money my friend, no deal!.\n");
}

void
shop_hook_value_not_interesting(object ob)
{
    FAIL_MSG("Your " + ob->short() + 
		 " does not interest me.\n");
}

void
shop_hook_value_held(object ob, string text)
{
    SPRITE_MSG("You would get " + text + " for " +
		LANG_THESHORT(ob) + ".\n");
}

void
shop_hook_list_empty_store(string str)
{
    FAIL_MSG("My store room is currently empty.\n");
}

int
shop_hook_list_no_match(string str)
{
    FAIL_MSG("I am sorry, but we have no '" + str + "' in stock.\n");
    return 0;
}
