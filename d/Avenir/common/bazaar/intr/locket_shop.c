/*
 * A locket shop
 *
 * Here, a player can configure and purchase an auto-loading
 * locket made from the metal of his choose, which a picture
 * and engraving.
 *
 *    Cirion, May 1997
 *
 *    -Added signet rings. Sirra, July 2002.
 */
inherit "/std/room";
inherit "/lib/trade";

#include "/d/Avenir/smis/sys/statserv.h"
#include "/d/Avenir/include/relation.h"
#include "/d/Avenir/common/bazaar/bazaar.h"
#include <cmdparse.h>
#include <money.h>

#ifndef SCROLLING_LOG
#define SCROLLING_LOG(file, entry)   ((file_size(file) > 10000) ? \
			 (rm(file) && write_file(file, ctime(time()) + ": " + entry + "\n")) : \
			 (write_file(file, ctime(time()) + ": " + entry + "\n")))
#endif

#define LOCKET   (BAZAAR + "Obj/worn/locket")
#define RING		(BAZAAR + "Obj/worn/sig_ring")

#define ONONE  0
#define OMETAL 1
#define OENGRAVE 2
#define OIMAGE 3
#define OWORKING 4
#define OFINISHED 5

#define ENGRAVE_COST   256

#define LOCKET_BASE_COST   100

#define MS(delay, what)   (set_alarm(itof(delay), 0.0, &ms(what)))

object merchant;
mapping locket_metals = ([ "silver" : 400, "gold" : 800, "platinum" : 1050,
						  "copper" : 200, "brass" : 270, "bronze" : 250,
						  "tin" : 100, "mithril" : 5000, "steel" : 550 ]);
string *metals = m_indices(locket_metals);
string o_metal, o_engraving, o_who, o_image, o_piece;
object orderer, locket, ring;
int order_status;

void reset_room();
void finish_locket();

void
create_room()
{
	 set_name("tent");
	 set_short("well-arrayed tent");
	 set_long("Neatly arranged all around the tent are "
		+ "long glass-topped tables of ashwood. In the eastern corner is "
		+ "a small desk, on which lies scraps of metals, paper, "
		+ "and engraving tools.\n");
	 add_item(({"table","tables"}), "The desks are all identically "
		+ "long, and are made from carved ashwood. The tops of "
		+ "the tables are glass, revealing an array of jewelrey, "
		+ "mostly locket necklaces and signet rings, inside.\n");
	 add_item(({"desk", "small desk"}), "It is a small desk made of "+
		"heavy wood.\n");
	 config_default_trade();
	 set_money_give_reduce( ({ 0, 2, 3, 3 }) );
	
	IN;       // Avenir is an undergound domain.
	IN_IN;    // Interior room, no flux msgs, steeds etc.


	 add_exit(EXTR + "str21", "out");
	 reset_room();
}

void
ms(string str)
{
	 merchant->command("say " + str);
}

void
reset_order()
{
	 o_piece = 0;
	 o_metal = 0;
	 o_engraving = 0;
	 o_who = 0;
	 o_image = 0;
	 orderer = 0;
	 order_status = ONONE;
}

int
cancel(string str)
{
	 NF("Cancel what? Your order?\n");
	 if(str != "order")
		 return 0;

	 if(TP != orderer)
	 {
		 ms("You have no order to cancel!");
		 return 1;
	 }

	 ms("Ok, " + TP->query_race_name() + ", I will cancel your order.");
	 reset_order();
	 return 1;
}

void
reset_room()
{
	 reset_order();

	 if(!merchant)
	 {
                 merchant = clone_object(NPC + "locket_merchant.c");
		 merchant->arm_me();
	 }

	 if(!present(merchant))
		 merchant->move_living("away", TO);
}

int
order(string str)
{
	 NF("The merchant is not here now.\n");
	 if(!present(merchant))
		  return 0;

	 NF("You are too busy.\n");
	 if(TP->query_attack())
		  return 0;

	 if (IS_INFIDEL(this_player()))
	 {
		  tell_object(this_player(), "The merchant refuses to trade "+
				"with criminals.\n");
		  return 1;
	 }

	 if(str != "locket" && str != "ring" && str != "signet ring")
	 {
		 ms("I only sell lockets and signet rings.");
		 return 1;
	 }

	 if(orderer && orderer != TP)
	 {
		 ms("I am already working on a piece for someone else.");
		 ms("You will have to wait your turn.");
		 return 1;
	 }

	 if(orderer && orderer == TP)
	 {
		 ms("I am already working on a piece for you!");
		 ms("If you like, you can cancel your order at any time.");
		 return 1;
	 }


	 if(str == "ring" || str == "signet ring")
	 {
		o_piece="signet ring";
	 }

	 if(str == "locket")
	 {
		o_piece="locket";
	 }

	 ms("What sort of metal would you like your "+o_piece+ " to be made out of? You "
	  + "can choose from " + COMPOSITE_WORDS(metals) + ".");
	 ms("Select your metal by saying \"Make it out of <metal>\"");
	 order_status = OMETAL;
	 orderer = TP;
	 return 1;
}

leave_inv(object to, object from)
{
	 ::leave_inv(to, from);

	 if(orderer == to)
	 {
		  ms("I will cancel your order.");
		  reset_order();
	 }
}


int
do_say(string str)
{
	 string arg;
	 object *obs, what;

	 if(order_status == ONONE)
		return 0;

	 if(!strlen(str) || orderer != TP)
		return 0;

	 if(order_status == OMETAL)
	 {
		 str = lower_case(str);
		 sscanf(str, "make it out of %s", arg);
		 if(!strlen(arg))
			  return 0;

		 if(member_array(arg, metals) == -1)
		 {
			 set_alarm(0.0, 0.0, &ms("Eh? I don't have that "
			  + "available. I only can make " + o_piece
			  + "s from " + COMPOSITE_WORDS(metals) + "."));
			 return 0;
		 }

		 o_metal = arg;

		 set_alarm(0.0, 0.0, &ms("What image would you like to have on your "
			+ o_piece +"?"));
		 set_alarm(1.0, 0.0, &ms("I can only make a good rendering if "
			+ "the person or thing is present so I can see it."));
		 set_alarm(2.0, 0.0, &ms("You can just \"say Make the image "
			+ "of <whatever>\""));

		 order_status = OIMAGE;
		 return 0;
	 }

	 if(order_status == OIMAGE)
	 {
		 str = lower_case(str);
		 sscanf(str, "make the image of %s", arg);
		 if(!strlen(arg))
			  return 0;

		 obs = FIND_STR_IN_OBJECT(arg, TP);
		 if(!sizeof(obs))
			  obs = FIND_STR_IN_OBJECT(arg, ENV(TP));

		 if(!sizeof(obs))
		 {
			  MS(0, "Eh? What's that? I need to have a model to work from!");
			  return 0;
		 }

		 what = obs[0];

		 if(!living(what))
		 {
			 o_image = LANG_ASHORT(what);
		 }
		 else
		 {
			 if(interactive(what))
					o_who = what->query_real_name();

			 o_image = LANG_ADDART(what->query_nonmet_name());
		 }

		 MS(0, "I will put a rendering of " + o_image + " in the " +o_piece
			  + " for you.");

		 MS(1, "Would you like the " +o_piece
			  + " engraved with something special? "
			  + "It will cost an additonal " + LANG_WNUM(ENGRAVE_COST)
			  + " coppers.");
		 MS(2, "If not, just say \"Don't engrave it\"");
		 MS(3, "Otherwise, say: \"Engrave it with <words>\"");

		 order_status = OENGRAVE;
		 return 0;
	 }

	 if(order_status == OENGRAVE)
	 {
		 sscanf(lower_case(str), "don't engrave %s", arg);
		 if(strlen(arg))
		 {
			 MS(0, "Ok. I will have your " +o_piece +" ready in just a little "
				  + "bit.");
			 order_status = OWORKING;
			 set_alarm(5.0, 0.0, &finish_locket());
			 return 0;
		}

		 sscanf(str, "Engrave it with %s", arg);
		 if(!strlen(arg))
			  sscanf(str, "engrave it with %s", arg);
		 if(!strlen(arg))
			  return 0;

		 if(strlen(arg) > 100)
		 {
			  MS(0, "Sorry, but that is too long!");
			  MS(1, "You need to keep the engravings short, or else they won't "
					+ "fit.");
			  return 0;
		 }

		 MS(0, "Ok. I will engrave the "+o_piece+" with: \"" + arg + "\"");
		 MS(1, "I will have your " +o_piece+ " ready in just a little "
				  + "bit.");
		 o_engraving = arg;
		 order_status = OWORKING;
		 set_alarm(5.0, 0.0, &finish_locket());
		 return 0;
	 }

	 return 0;
}

int
locket_value()
{
	 int value;

	 value = LOCKET_BASE_COST;
	 if(o_engraving)
		 value += ENGRAVE_COST;
	 value += locket_metals[o_metal];

	 return value;
}

void
finish_locket()
{

	 order_status = OFINISHED;
	 ms("I am finished with the " +o_piece+ ". Can pay me for it now.");
	 ms("the cost is " + LANG_WNUM(locket_value()) + " coppers.");
}

int
do_pay(string str)
{
	 object loc;
	 int   *result;

	 NF("You have ordered nothing to pay for.\n");
	 if(orderer != TP)
		  return 0;

	 NF("Your order is not yet finished.\n");
	 if(order_status != OFINISHED)
		  return 0;


	 result = pay(locket_value(), TP);
	 if(sizeof(result) == 1)
		 return 0;

	  if (o_piece == "locket")
	  {
			loc = clone_object(LOCKET);
	  }

	  if (o_piece == "signet ring")
	  {
			loc = clone_object(RING);
	  }

	  loc->set_metal(o_metal);
	  loc->set_who(o_who);
	  loc->set_engraving(o_engraving);
	  loc->set_image(o_image);


	 STATSERV_LOG_EVENT("bazaar", "Lockets or Signet Rings bought:");
	 SCROLLING_LOG("/d/Avenir/log/bazaar/lockets", TP->query_name() + " bought a "
			  +o_piece+ " ( "
			  + o_metal + ", " + o_who + ", " + o_image + ", " + o_engraving + ")");


	 loc->move(TP, 1);
	 write("You get your " +o_piece+ ".\n");
	 say(QCTNAME(TP) + " pays for a " +o_piece+ ".\n");

	 reset_order();

	 return 1;
}

void
init()
{
	 ::init();

	 add_action(order, "order");
	 add_action(do_pay, "pay");
	 add_action(do_say, "say");
	 add_action(do_say, "'");
	 add_action(cancel, "cancel");
}

