/* 
 * Blacksmith - the place to get armours made and repaired.
 * Elessar, January '92.
 * Modifications to make the armour rebootable,
 * Olorin, June '93
 *
 * Modification log:
 * 17-jan-1994, Olorin: Small changes:
 *              - remove set_up_vars(), set up vars using defines
 *              - List metals when ordering,
 *              - reset old value of o_aconst when new armour type is chosen
 * 13-jul-1998, Gnadnar: conform to domain.rules,
 *			timeout idle customers so one person can't deadlock
 *			the shop.
 * 3-oct-1998, Gnadnar: allow paying for armour as it's completed,
 *			instead of having to wait until all orders are done
 * 10-nov-2000, Gwyneth: added an exit to the new paintshop.
 */

#pragma strict_types

inherit "/d/Gondor/std/room.c";
inherit "/lib/trade.c";

#include <composite.h>
#include <formulas.h>
#include <language.h>
#include <macros.h>
#include <money.h>
#include <stdproperties.h>
#include <wa_types.h>

#include "/d/Gondor/defs.h"

#define VOL_STANDARD   150	/* Used to calculate the volume and weight */
#define GREED          125	/* price = value * greed */
#define PRICE(x)       (x->query_prop(OBJ_I_VALUE) * GREED / 100)
#define NUM            sizeof(MONEY_TYPES)
#define METAL          ({ "silver", "brass", "gold", "bronze", "iron", \
                          "tempered iron", "steel", "alloyed steel", \
                          "high steel", "mithril", })
#define ATYPE          ({ "cuirass", "shield", "helm", "greaves", "bracers", })
#define ACONST         ({ "ring", "scale", "splint", "chain", "double", \
			  "bar", "augmented", "banded", "plate", })
#define HCONST         ({ "ring", "chain", "double", "plate", "tabarded", \
                          "visored", "great", })
#define SCONST         ({ "small", "medium", "large", })
#define METAL_PRICE    ({ 115, 80, 135, 85, 100, 110, 120, 160, 240, 600, })
#define	TIMEOUT		300.0

/* prototypes */
public void	create_gondor();
public void	reset_room();
public void	init();
public void	enter_inv(object ob, object from);
public void	leave_inv(object obj, object to);
public int	do_read(string str);
public string	read_sign();
public string	read_armourlist();
public string	read_pricelist();
public int	place_order(object player);
public int	reorder();
public int	cancel_order();
public void	ask_for_input();
public int	armour_type(string at);
public int	metal_type(string me);
public int	construction_type(string co);
public int	estimate_value();
public void	describe_armour();
public int	accept_order();
public int	make_the_armour();
public void	finish_armour(object player);
public void	reset_ordering();
public int	pay_and_get(string str);
public int	can_afford(object player, int price, string arm);
public void	info_pay_for_armour(mixed *arr);
public object	query_ordering();
public void	too_long(object player);


static object	Smith,
		Ordering,
		*Armour_ready = ({});
static mixed	*Order = ({});
static string	O_metal,
		O_atype,
		O_constr,
		Pay_type,
		Get_type,
		Coin_pay_text,
  		Coin_get_text;
static int	Mithril_in_stock,
		*Money_arr,
		I_atype,
		I_aconst,
		I_ametal,
		Prompt_alarm,
		Timeout_alarm;



/*
 * Function name:	create_gondor
 * Description	:	set up the armoury
 */
public void
create_gondor()
{
    FIX_EUID;
    set_short("the workshop of the blacksmith");
    set_long(BSN("This is the blacksmith's workshop, a hot place with "+
	"armours of all kinds on the walls, and a hot forge by the inner "+
	"wall, where the blacksmith heats and hammers metals into shields, "+
	"helms and plates to be worn by warriors throughout Gondor. There "+
        "is a sign on one wall, and a list just below it. An opening leading " +
        "to a back room can be seen on the south wall, and north is the "+
	"exit to the street."));
    add_prop(ROOM_I_INSIDE, 1);
    add_prop(ROOM_I_NO_ATTACK, 1);
    add_prop(ROOM_I_NO_CLEANUP, 1);
    add_item("armours",
	BSN("There are all kinds of armours in here: Plate armours, "+
	    "scale mails, chain mails and ring mails, round metal "+
	    "shields, huge wall shields, visored helms and smaller "+
	    "pot helmets. There are plate leggings and arm bracers."));
    add_item( ({ "sign", "poster" }), read_sign);
    add_item( ({ "list", "armourlist" }), read_armourlist);
    add_item( ({ "prices", "pricelist" }), read_pricelist);
    add_item( "forge",
	BSN("The heat from the forge is incredible, you have no "+
	    "understanding for how the blacksmith manages to work "+
	    "under these conditions every day. A large black anvil "+
	    "stands next to a large bellows, and a pair of pliers and "+
	    "some hammers lie on a shelf."));
    add_item( ({ "opening", "south wall" }), "Some lamplight floods " +
        "out from the back room.\n");
    add_exit(MINAS_DIR + "s1crc2", "north", 0, 0);
    add_exit(MINAS_DIR + "rooms/mt_paint_shop", "south", 0, 0);
    reset_room();
    config_default_trade();
} /* create_gondor */



/*
 * Function name:	reset_room
 * Description	:	clone up the smith
 */
public void
reset_room()
{
    Smith = clone_npc(Smith, MORGUL_DIR + "npc/smith");
} /* reset_room */


/*
 * Function name:	init
 * Description	:	add all the verbs
 */
void 
init()
{
    ::init();
    add_action(do_read, "read",  1);
    add_action(accept_order, "accept");
    add_action(reorder, "rechoose");
    add_action(reorder, "redesign");
    add_action(reorder, "reorder");
    add_action(cancel_order, "cancel");
    add_action(construction_type, "const",  1);
    add_action(metal_type, "metal");
    add_action(armour_type, "armour",  1);
    add_action(pay_and_get, "pay");
} /* init */


/*
 * Function name:	enter_inv
 * Description	:	mask parent to detect arriving customers
 * Arguments	:	object ob -- the entering object
 *			object from -- its source
 */
public void
enter_inv(object ob, object from)
{
    int i, cnt, is_ready;

    ::enter_inv(ob, from);

    if (!from ||
	!interactive(ob))
    {
	return;
    }

    cnt = sizeof(Order);
    i = -1;
    while (cnt > 0)
    {
	cnt -= 2;
	if (Order[cnt] == ob)
	{
	    i = cnt;
	}
    }
    if (i == -1)
    {
	return;
    }

    cnt = 0;
    is_ready = 0;
    while (cnt < sizeof(Armour_ready))
    {
	if (Order[i + 1] == Armour_ready[cnt])
	{
	    is_ready = 1;
	    break;	/* while */
	}
	cnt++;
    }
    if (!is_ready)
    {
	return;
    }

    set_alarm(1.0, 0.0, &info_pay_for_armour(({ ob, PRICE(Order[i + 1]) })));
    return;
} /* enter_inv */


/*
 * Function name:	leave_inv
 * Description	:	mask parent to cancel order if customer leaves
 * Arguments	:	object obj -- the departing object
 *			object to -- its destination
 */
public void
leave_inv(object obj, object to)
{
    int i;

    ::leave_inv(obj, to);
    if (!living(obj))
    {
	return;
    }
    if (Smith)
    {
	Smith->command("shout Fare well, traveller and come back soon!");
    }
    if (obj == Ordering)
    {
	if (Smith)
	{
	    Smith->command("shout I will cancel your order then, "+
		obj->query_nonmet_name()+"!");
	}
	Ordering = 0;
	O_atype = 0;
	O_constr = 0;
	O_metal = 0;
    }
    if (Timeout_alarm)
    {
	remove_alarm(Timeout_alarm);
	Timeout_alarm = 0;
    }
    if (obj->query_prop("_tmp_accepted_armour"))
    {
	obj->remove_prop("_tmp_accepted_armour");
    }
} /* leave_inv */


/*
 * Function name:	do_read
 * Description	:	handle attempts to read signs etc
 * Arguments	:	string str -- whatever the player typed
 * Returns	:	1 on success, 0 on failure
 */
public int 
do_read(string str)
{
    if (str == "armourlist" ||
	str == "list")
    {
	read_armourlist();
	return 1;
    }
    if (str == "pricelist" ||
	str == "prices")
    {
	read_pricelist();
	return 1;
    }
    if (str == "sign" ||
	str == "poster")
    {
	read_sign();
	return 1;
    }
    NF0("Read what?\n");
} /* do_read */


/*
 * Function name:	read_sign
 * Description	:	VBFC for sign item + handle "read"
 * Returns	:	string -- "" (desc is written here)
 */
public string 
read_sign()
{
    write(
    "           Thaurmindar's Armoury\n"+
    "          --------------------\n"+
    "  Thaurmindar the Blacksmith crafts metal armours on request.\n"+
    "\n"+
    "  You may state what kind of armour you want, and what kind\n"+
    "  of metal it should be made of.\n"+
    "\n"+
    "  Price will be calculated according to your choice.\n"+
    "\n"+
    "  To order, just say that you would like to order. You will\n"+
    "  be asked for type of armour (cuirass, shield, helm etc.),\n"+
    "  construction type (plate, chain, ring etc.), and of what kind\n"+
    "  of metal you would like the armour to be made.\n"+
    "\n"+
    "  See the armourlist to get the available armour-types\n"+
    "  and constructions. After stating your choices you will\n"+
    "  be given an estimated price, after which you may cancel\n"+
    "  your order.\n"+
    "  \n"+
    "  The armour may take some time to finish, but you will be duly\n"+
    "  notified when it can be picked up.\n"+
    "\n"+
    "  Thaurmindar is also capable of repairing armours that are\n"+
    "  damaged by battle. Please give the armour to him and he\n"+
    "  will examine it and repair it if you want him to.\n"+
    "\n"+
    "     Please feel free to place an order!\n");

    return "";
} /* read_sign */


/*
 * Function name:	read_armourlist
 * Description	:	VBFC for armourlist item + handle "read"
 * Returns	:	string -- "" (desc is written here)
 */
public string 
read_armourlist()
{
    write("           Thaurmindar's Armoury\n" +
	   "          --------------------\n" +
	   "  Possible armour types:\n" +
	   "    Cuirasses, shields, helms, greaves (for legs),\n" +
	   "    and bracers (for arms).\n\n" +
	   "  Possible constructions, listed from worst to best:\n" +
	   "    Ring, scale, splint, chain, double, bar,\n" +
	   "    augmented, banded and plate mails.\n\n" +
	   "  Metals available:\n" +
	   "    Iron, bronze, brass, silver, gold, steel,\n" +
	   "    alloyed steel, tempered iron and high steel.\n");
    return "";
} /* read_armourlist */



/*
 * Function name:	read_pricelist
 * Description	:	VBFC for pricelist item + handle "read"
 * Returns	:	string -- "" (desc is written here)
 */
public string 
read_pricelist()
{
    write("           Thaurmindar's Armoury\n" +
    "          --------------------\n" +
    "          Prices, relative to metal and construction.\n" +
    "   Iron          - standard price.\n" +
    "   Bronze        - 85 % of standard price, not quite so solid.\n" +
    "   Brass         - 80 % of standard price, even less solid.\n" +
    "   Gold          - 135 % of standard price, quite soft metal.\n" +
    "   Silver        - 115 % of standard price, even softer than gold.\n" +
    "   Tempered iron - 110 % of standard price, better than iron.\n" +
    "   Steel         - 120 % of standard price, even better than "+
							"tempered iron.\n" +
    "   Alloyed steel - 160 % of standard price.\n" +
    "   High steel    - 240 % of standard price.\n" +
    "   Mithril       - 600 % of standard price (rarely available).\n");
    return "";
} /* read_pricelist */


/*
 * Function name:	place_order
 * Description	:	called from smith to actually start order
 * Arguments	:	object player -- the customer
 * Returns	:	int -- 0 if player not here, 1 otherwise
 */
public int 
place_order(object player)
{
    if (ENV(player) != TO)
    {
	return 0;
    }
    if (player == Ordering)
    {
	Smith->command("say You are already ordering!");
	Smith->command("say Please continue designing the armour.");
	return 1;
    }
    if (TP->query_prop("_tmp_accepted_armour"))
    {
	TP->remove_prop("_tmp_accepted_armour");
    }
    Ordering = player;
    if (!O_atype)
    {
	Smith->command("say What type of armour would you like?");
	Smith->command("say Cuirass, shield, helm, bracers, or greaves?");
	Smith->command("say State your wish with 'armourtype <type>'.");
	Smith->command("smile");
    }
    Timeout_alarm = set_alarm(TIMEOUT, 0.0, &too_long(player));
    return 1;
} /* place_order */


/*
 * Function name:	reorder
 * Description	:	start the order over
 * Returns	:	int -- 1 (always)
 */
public int
reorder()
{
    if (!objectp(Ordering))
    {
	return 1;
    }
    if (TP != Ordering)
    {
	Smith->command("say Please wait, "+TP->query_nonmet_name()+".");
	return 1;
    }
    O_atype = 0;
    O_constr = 0;
    O_metal = 0;
    if (TP->query_prop("_tmp_accepted_armour"))
    {
	TP->remove_prop("_tmp_accepted_armour");
    }
    Smith->command("say Ok, redesigning the armour. What kind would you like?");
    Smith->command("say Armour, shield, helm, bracers, or greaves?");
    Smith->command("say State your wish with 'armourtype <type>'.");
    Smith->command("smile");
    if (Timeout_alarm)
    {
	remove_alarm(Timeout_alarm);
	Timeout_alarm = set_alarm(TIMEOUT, 0.0, &too_long(Ordering));
    }
    return 1;
} /* reorder */


/*
 * Function name:	cancel_order
 * Description	:	cancel the outstanding order
 * Returns	:	int -- 1 (always)
 */
public int
cancel_order()
{
    if (!objectp(Ordering))
    {
	return 1;
    }
    if (TP != Ordering)
    {
	Smith->command("say Please wait, "+TP->query_nonmet_name()+".");
	return 1;
    }
    Ordering = 0;
    O_atype = 0;
    O_constr = 0;
    O_metal = 0;
    Smith->command("say Ok, you have cancelled your order.");
    return 1;
} /* cancel_order */


/*
 * Function name:	ask_for_input
 * Description	:	prompt customer for next info
 */
public void
ask_for_input()
{
    string	lastchar;

    if (Prompt_alarm)
    {
	remove_alarm(Prompt_alarm);
	Prompt_alarm = 0;
    }
    if (!objectp(Ordering) ||
	ENV(Ordering) != TO)
    {
	return;
    }

    if (!O_atype)
    {
	Smith->command("say Well, what kind of armour do you want?");
	Smith->command("say I can make cuirasses, shields, helms, and");
	Smith->command("say also greaves and bracers.");
	Smith->command("say Choose with 'armourtype <text>'.");
    }
    else if (!O_constr)
    {
	Smith->command("say How would you like it constructed?");
	/* roll our own plural .. LANG_PWORD doesn't do well with "bracers" */
	lastchar = O_atype[(strlen(O_atype)-1)..];
	Smith->command("say These are the constructions I know for " +
	    (lastchar == "s" ? O_atype : O_atype + "s")+".");
	switch (O_atype)
	{
	case "helm":
	    tell_room(TO, BSN(CAP(implode(HCONST, ", ")) + "."));
	    break;
	case "shield":
	    tell_room(TO, BSN(CAP(implode(SCONST, ", ")) + "."));
	    break;
	default:
	    tell_room(TO, BSN(CAP(implode(ACONST, ", ")) + "."));
	    break;
	}
	Smith->command("say Choose by 'construction <text>'.");
    }
    else if (!O_metal)
    {
	Smith->command("say Now what kind of metal would you like?");
	Smith->command("say I have the following metals available:");
	if (!Mithril_in_stock)
	{
	    Smith->command("say "+CAP(COMPOSITE_WORDS(METAL[0..8]))+".");
	}
	else
	{
	    Smith->command("say "+CAP(COMPOSITE_WORDS(METAL))+".");
	}
	Smith->command("say Choose by 'metal <metal>'.");
    }
    else if (!TP->query_prop("_tmp_accepted_armour"))
    {
	Prompt_alarm = set_alarm(2.0, 0.0, describe_armour);
    }
} /* ask_for_input */


/*
 * Function name:	armour_type
 * Description	:	set armour type
 * Arguments	:	string at -- whatever the player typed
 * Returns	:	int -- 1 (always)
 */
public int 
armour_type(string at)
{
    int		tmp;
    if (Prompt_alarm)
    {
	remove_alarm(Prompt_alarm);
	Prompt_alarm = 0;
    }

    if (objectp(Ordering))
    {
	if (ENV(Ordering) != TO)
	{
	    Smith->command("say Could you please wait until the "+ 
		   Ordering->query_nonmet_name()+" has ordered?");
	    return 1;
	}
    }
    else
    {
	Ordering = TP;
    }

    if (!strlen(at))
    {
	Smith->command("say Yes, choose the type of armour you want.");
	Smith->command("say Use 'armourtype <type>'.");
    }
    else if ((tmp = member_array((at = LOW(at)), ATYPE)) > -1)
    {
	I_atype = tmp;
	O_atype = at;
	O_constr = 0;
	Prompt_alarm = set_alarm(2.0, 0.0, ask_for_input);
    }
    else
    {
	Smith->command("say I don't know how to make "+LANG_ADDART(at)+".");
	Smith->command("shrug");
    }
    Smith->already_ordered();
    return 1;
} /* armour_type */


/*
 * Function name:	metal_type
 * Description	:	set metal type
 * Arguments	:	string at -- whatever the player typed
 * Returns	:	int -- 1 (always)
 */
public int 
metal_type(string me)
{
    int	tmp;
    if (Prompt_alarm)
    {
	remove_alarm(Prompt_alarm);
	Prompt_alarm = 0;
    }
    if (!objectp(Ordering) ||
	ENV(Ordering) != TO)
    {
	Ordering = 0;
	Smith->make_order(TP);
    }
    else if (TP != Ordering)
    {
	Smith->command("say Could you please wait until the "+
	    Ordering->query_nonmet_name()+" has ordered?");
    }
    else if (!strlen(me))
    {
	Smith->command("say Yes, choose the metal you want.");
	Smith->command("say Use 'metal <type>'.");
    }
    else if ((me = LOW(me)) == "mithril" &&
	     !Mithril_in_stock)
    {
	Smith->command("say I'm deeply sorry, but mithril cannot be found");
	Smith->command("say anywhere anymore. You will have to choose again.");
    }
    else if ((tmp = member_array(me, METAL)) > -1)
    {
	I_ametal = tmp;
	O_metal = me;
	Prompt_alarm = set_alarm(2.0, 0.0, ask_for_input);
    }
    else
    {
	Smith->command("say I don't have that kind of metal.");
	Smith->command("say Please choose again.");
	O_metal = 0;
	Prompt_alarm = set_alarm(2.0, 0.0, ask_for_input);
    }
    return 1;
} /* metal_type */


/*
 * Function name:	construction_type
 * Description	:	set construction type
 * Arguments	:	string at -- whatever the player typed
 * Returns	:	int -- 1 (always)
 */
public int 
construction_type(string co)
{
    string *const;
    int	tmp;

    if (Prompt_alarm)
    {
	remove_alarm(Prompt_alarm);
	Prompt_alarm = 0;
    }
    if (O_atype == "shield")
    {
	const = SCONST;
    }
    else if (O_atype == "helm")
    {
	const = HCONST;
    }
    else
    {
	const = ACONST;
    }

    if (!objectp(Ordering) ||
	ENV(Ordering) != TO)
    {
	Ordering = 0;
	Smith->make_order(TP);
    }
    else if (TP != Ordering)
    {
	Smith->command("say Could you please wait until the "+
	    Ordering->query_nonmet_name()+" has ordered?");
    }
    else if ((tmp = member_array((co = LOW(co)), const)) > -1)
    {
	I_aconst = tmp;
	O_constr = co;
	Prompt_alarm = set_alarm(2.0, 0.0, ask_for_input);
    }
    else
    {
	Smith->command("say I don't know how to construct "+
	    LANG_ADDART(co)+" "+O_atype+".");
	Smith->command("say Please choose again from the constructions "+
	    "listed");
	Smith->command("say on the armour-list.");
	Smith->command("smile");
    }
    return 1;
} /* construction_type */



/*
 * Function name:	estimate_value
 * Description	:	estimate the value of the ordered armour
 * Returns	:	int -- the estimate
 */
public int 
estimate_value()
{
    int cac;
    cac = MIN((I_aconst * 2) + 10 + (I_ametal * 2), MAX_BOUGHT_AC);
    return (GREED * F_VALUE_ARMOUR(cac) * METAL_PRICE[I_ametal]) / 10000;
} /* estimate_value */


/*
 * Function name:	describe_armour
 * Description	:	describe the ordered armour
 */
public void 
describe_armour()
{
    if (TP->query_prop("_tmp_accepted_armour"))
    {
	return;	/* typed ahead */
    }
    Smith->command("say You have chosen "+LANG_ADDART(O_constr)+
	" "+O_atype+" of "+O_metal+".");
    Smith->command("say This will cost about "+estimate_value()+" coppers,");
    Smith->command("say not taking the metal in account.");
    Smith->command("say If you are not pleased with this, you may 'rechoose'.");
    Smith->command("say If you are pleased, just do 'accept armour', and");
    Smith->command("say I will start working on it. You may wait here, or");
    Smith->command("say await a messenger from me somewhere else.");
    Smith->command("say Pay when you pick it up.");
    Smith->command("smile");
} /* describe_armour */


/*
 * Function name:	accept_order
 * Description	:	customer ok's the order
 * Returns	:	int -- 1 (always)
 */
public int
accept_order()
{
    if (!objectp(Ordering))
    {
	return 1;
    }
    if (TP != Ordering)
    {
	Smith->command("say Please wait, "+TP->query_nonmet_name()+".");
	return 1;
    }
    if (!O_atype ||
	!O_metal ||
	!O_constr)
    {
	Smith->command("say You haven't told me exactly what you want, yet!");
	call_out("ask_for_input", 2);
	return 1;
    }
    if (TP->query_prop("_tmp_accepted_armour"))
    {
	Smith->command("say Yes, you did already tell me you accepted it.");
	return 1;
    }
    make_the_armour();
    set_alarm((60.0 + rnd() * 60.0), 0.0, &finish_armour(Ordering));
    Smith->command("say That is a deal! I will start crafting it at once.");
    Smith->command("say I will send a messenger to notify you.");
    Smith->command("wave");
    tell_room(TO, "The blacksmith starts heating a piece of "+O_metal+".\n");
    Smith->set_current_metal(O_metal);
    TP->add_prop("_tmp_accepted_armour", 1);
    if (Timeout_alarm)
    {
	remove_alarm(Timeout_alarm);
	Timeout_alarm = 0;
    }
    reset_ordering();
    return 1;
} /* accept_order */


/*
 * Function name:	make_the_armour
 * Description	:	clone up the armour
 * Returns	:	1 on success, 0 on failure
 */
public int
make_the_armour()
{
    object arm_obj;

    arm_obj = clone_object(MINAS_DIR + "obj/mtarmour.c");
    arm_obj->set_armtype(I_atype);
    arm_obj->set_metal(I_ametal);
    arm_obj->set_const(I_aconst);
    Order += ({ Ordering, arm_obj });

    return arm_obj->make_the_armour();
} /* make_the_armour */


/*
 * Function name:	finish_armour
 * Description	:	finish up the order
 * Arguments	:	object player -- the customer
 */
public void
finish_armour(object player)
{
    int		i,
		cnt,
		is_customer;
    string	a_name,
		lastchar;

    if (!objectp(player) ||
        !sizeof(Order))
    {
	return;
    }

    cnt = sizeof(Order) - 1;
    is_customer = 0;
    while (cnt > 0)
    {
	if (player == Order[cnt - 1] &&
	    member_array(Order[cnt], Armour_ready) == -1)
	{
	    is_customer = 1;
	    i = cnt - 1;
	    break; /* while */
	}
	cnt -= 2;
    }
    if (!is_customer)
    {
	return;
    }
    Armour_ready += ({ Order[i + 1] });
    if (ENV(player) == TO)
    {
	Smith->command("say Ah - "+player->query_nonmet_name()+"!");
	Smith->command("smile");
	Smith->command("say Your armour is now finished!");
	Smith->command("say It will cost you "+PRICE(Order[i + 1])+" coppers.");
	Smith->command("say Just 'pay for armour', and you will get it.");
    }
    else
    {
	a_name = Order[i + 1]->query_name();
	lastchar = a_name[(strlen(a_name)-1)..];
	tell_object(player,
	    "A pigeon comes flying, delivering the following message:\n" +
	    BSN("Your "+a_name+(lastchar == "s" ? " are" : " is") +
	        " now finished, and you may come " +
	        "and fetch it when you have the time. The price is " +
	         PRICE(Order[i + 1])+" coppers.") +
	    "  Yours, "+Smith->query_name()+" "+Smith->query_title()+".\n");
    }
} /* finish_armour */


/*
 * Function name:	reset_ordering
 * Description	:	reset order info so we're free to take new one
 */
public void
reset_ordering()
{
    Ordering->remove_prop("_tmp_accepted_armour");
    Ordering = 0;
    O_atype = 0;
    O_metal = 0;
    O_constr = 0;
} /* reset_ordering */


/*
 * Function name:	pay_and_get
 * Description	:	collect the order
 * Returns	:	int -- 1 (always)
 */
public int
pay_and_get(string str)
{
    int		i,	/* index into Armoury_ready */
		j,	/* index into Order */
		s,	/* size of Armour_ready */
		price;
    object	armour;

    if (member_array(TP, Order) < 0)
    {
	Smith->command("say Pay? For what? You have no order placed here.");
	Smith->command("shrug");
	return 1;
    }

    for (i = 0, s = sizeof(Armour_ready); i < s; ++i)
    {
	if ((j = member_array(Armour_ready[i], Order)) > 0 &&
	    Order[j - 1] == TP)
	{
	    break;	/* while */
	}
    }

    if (i >= s)
    {
	Smith->command("say I'm sorry, I have not yet finished it.");
	Smith->command("say Please come back later.");
	return 1;
    }

    armour = Armour_ready[i];
    price = PRICE(armour);
    Smith->command("say That will be "+price+" coppers.");
    if (can_afford(TP, price, armour->query_name()))
    {
	Armour_ready = exclude_array(Armour_ready, i, i);
	if (armour->move(TP))
	{
	    Smith->command("say It's too heavy for you to carry.");
	    Smith->command("say I'll just drop it here for you.");
	    armour->move(TO);
	    Smith->command("say Hope you will be pleased! Welcome back!");
	    Smith->command("smile");
	}
	say(QCTNAME(TP)+" is handed "+armour->query_short()+".\n");
	Order = exclude_array(Order, (j - 1), j);
    }
    return 1;
} /* pay_and_get */


/*
 * Function name:	can_afford
 * Description	:	find out if customer can afford it; if so, take
 *			her/his money 
 * Arguments	:	object player -- the customer
 *			int price -- how much it costs
 * 			string arm -- the ordered armour
 * Returns	:	1 on success, 0 on failure
 */
public int
can_afford(object player, int price, string arm)
{
    if (sizeof(Money_arr = pay(price, player, Pay_type, 0, 0, Get_type)) == 1)
    {
	if (Money_arr[0] == 2)
	{
	    Smith->command("say You don't have enought "+Pay_type+
		" coins, "+player->query_name()+".");
	    return 0;
	}
	if (Money_arr[0] == 1)
	{
	    Smith->command("say I think the "+arm+" is too expensive to only");
	    Smith->command("say pay for it in "+Pay_type+" coins.");
	    return 0;
	}
	else
	{
	    Smith->command("say The "+arm+" is too expensive for you!");
	    Smith->command("say All this work for naught! Begone!");
	    Smith->command("growl");
	    return 0;
	}
    }
    Coin_pay_text = text(exclude_array(Money_arr, NUM, NUM * 2 - 1));
    Coin_get_text = text(exclude_array(Money_arr, 0, NUM - 1));
    write("You pay "+Coin_pay_text+" for the "+arm+".\n");
    write("You get "+Coin_get_text+" back in change.\n");
    return 1;
} /* can_afford */


/*
 * Function name:	info_pay_for_armour
 * Description	:	inform arriving customer of status
 * Arguments	:	mixed * -- the order array
 */
public void
info_pay_for_armour(mixed * arr)
{
    object ob;
    int price;
    ob = arr[0];
    price = arr[1];
    Smith->command("say Ah - "+ob->query_nonmet_name()+"!");
    Smith->command("smile");
    Smith->command("say Your armour is now finished!");
    Smith->command("say It will cost you "+price+" coppers.");
    Smith->command("say Just 'pay for armour', and you will get it.");
    return;
} /* info_pay_for_armour */


/*
 * Function name:	query_ordering
 * Description	:	query the current customer
 * Returns	:	object -- the customer
 *
 * N.B. called from Thaurmindar
 */
public object
query_ordering()
{
    return Ordering;
} /* query_ordering */


/*
 * Function name:	too_long
 * Description	:	cancel order of customer who tarry too long
 * Arguments	:	object player -- the customer
 */
public void
too_long(object player)
{
    object	save_tp;
    Smith->command("peer "+player->query_real_name());
    Smith->command("say Well, perhaps you need more time to consider, "+
	player->query_nonmet_name()+".");
    Smith->command("say Let's cancel your order for now.");
    Smith->command("say You can order again later.");
    save_tp = TP;
    set_this_player(player);
    cancel_order();
    set_this_player(save_tp);
} /* too_long */
