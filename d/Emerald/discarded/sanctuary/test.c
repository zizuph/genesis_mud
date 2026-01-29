inherit "std/room";
inherit "/lib/trade";

#include <money.h>
#include <formulas.h>
#include <wa_types.h>
#include "/d/Emerald/defs.h"

#define LOW(x)     lower_case(x)
#define VOL_STANDARD   150   /* Used to calculate the volume and weight */
#define GREED          500   /* price = value * greed */
#define PRICE(x)       x->query_prop(OBJ_I_VALUE) * GREED / 100
#define NUM            sizeof(MONEY_TYPES)
#define METAL		({"midnight", "ivory", "purple", "grey", \
				"blood-red", "gold", "forest-green"})
#define ATYPE		({"short", "long", "voluminous", \
	"sweeping", "formidable", "splendid", "exquisite"})
#define ACONST		({"leather", "silk", "linen", "velvet", \
				"wool"})
#define HCONST		({"exquisite", "crude", "splendid", \
				"shoddy"})
#define STYLE			({"high collared", "hooded", "cowled"})
#define METAL_PRICE    ({6, 6, 6, 6, 6, 6, 6, 6, })

object  customer,
armour,
npc,
ordering,
*armour_ready = ({});
mixed  *order = ({});
string  o_metal,
o_atype,
o_constr,
o_style,
cur_metal,
pay_type,
get_type,
coin_pay_text,
coin_get_text;
int     *money_arr,
i_atype,
i_aconst,
i_ametal,
i_style;

void reset_room();
int  finish_armour(object player);

void create_room()
{
    set_short("cloak shop");
    set_long("This is Carista's Cloak shop.\n\n");

    add_prop(ROOM_I_INSIDE,1);
    add_prop(ROOM_I_NO_ATTACK,1);
    add_prop(ROOM_I_NO_CLEANUP,1);


    reset_room();
    config_default_trade();
}

object query_ordering()
{
    return ordering;
}

void reset_room()
{
    if (!npc || !present("carista", TO))
    {
	npc = clone_object("/d/Emerald/sanctuary/npc/carista");
	npc->move(TO);
    }
}




int place_order(object player)
{
    if (!present(player,TO))
	return 0;
    if (player == ordering)
    { 
	npc->command("say You are already ordering!");
	npc->command("say Shall we continue designing the cloak?");
	return 1;
    }
    customer = player;
    ordering = player;
    npc->command("say What size of cloak would you like?");
    npc->command("say Short, long, voluminous, sweeping or formidable?");
    npc->command("say State your wish with 'choose <type>'.");
    npc->command("smile swe");
    return 1;
}

int armour_type(string at) //choose
{
    if (!ordering)
	npc->make_order(TP);
    if (!present(ordering,TO))
    {
	ordering = 0;
	npc->make_order(TP);
	return 1;
    }
    if (TP != ordering)
    {
	npc->command("say Could you please wait until the "+ordering->query_nonmet_name()+
	  " has ordered?");
	return 1;
    }
    if (!at) { 
	npc->command("say Yes, choose the size of cloak you want.");
	npc->command("say Use 'choose <type>'.");
	return 1;
    }
    at = LOW(at);
    if ((i_atype = member_array(at, ATYPE)) > -1)
    {
	o_atype = at;
	o_constr = 0;
	set_alarm(1.0, 0.0, "ask_for_input");
	return 1;
    }
npc->command("say I don't know how to make a "+at+" cloak.");
    npc->command("sniff .");
    return 1;
}


ask_for_input()
{
    if (!o_atype)
    {
	npc->command("say Well, what size of cloak do you want made?");
	npc->command("say Short, long, voluminous, sweeping or formidable?");
	npc->command("say Tell me with 'choose <type>'.");
	return 1;
    }
    if (!o_constr)
    {
	npc->command("say Now we need to decide on materials.");
	npc->command("say I hope you don't find the selection too "+
	  "limited for "+
(o_atype[strlen(o_atype)-1..strlen(o_atype)-1] == " cloaks" ? o_atype : o_atype+ " cloaks")+
	  ":");
	switch(o_atype)
	{
	case "cloak":
	    tell_room(TO,break_string(CAP(implode(HCONST,", "))+" .\n",70));
	    break;
	default:
	    tell_room(TO,break_string(CAP(implode(ACONST,", "))+".\n",70));
	}
	npc->command("say You may choose by using 'material "+
	  "<material>'.\n");
	return 1;
    }
    if (!o_metal)
    {
	npc->command("say Next we need to decide what color "+
	  "you would like.");
	npc->command("say At present, I have these colors "+
	  "available:");
	tell_room(TO,break_string(CAP(implode(METAL,", "))+".\n", 70));
	npc->command("say Choose using 'color <color>'.");
	return 1;
    }
    if (!o_style)
    {
	npc->command("say Time to make your final selection. " +
	  "What make would you like it to be?");
	npc->command("say These are the popular styles:");
	npc->command("say Hooded, cowled, and high collared.");
	npc->command("say Choose using 'style <style>'.");
	return 1;
    }                                                                                                                                                                                                                                                          
    set_alarm(2.0, 0.0, "describe_armour");
}

int metal_type(string me)
{
    if (!present(ordering,TO))
    {
	ordering = 0;
	npc->make_order(TP);
	return 1;
    }
    if (TP != ordering)
    {
	npc->command("say Could you please wait until the "
	  +ordering->query_nonmet_name()+ " has ordered?");
	return 1;
    }
    me = LOW(me);
    if ((i_ametal = member_array(me, METAL)) > -1)
    {
	o_metal = me;
	set_alarm(2.0, 0.0, "ask_for_input");
	return 1;
    }
    npc->command("say I don't have that color available.");
    npc->command("say Please choose your color again.");
    o_metal = 0;
    set_alarm(2.0, 0.0, "ask_for_input");
    return 1;
}

int construction_type(string co)
{
    string *const;

    if (o_atype == "hat")
	const = HCONST;
    else
	const = ACONST;
    if (!present(ordering,TO))
    {
	ordering = 0;
	npc->make_order(TP);
	return 1;
    }
    if (TP != ordering)
    {
	npc->command("say Could you please wait until the " +
	  ordering->query_nonmet_name()+ " has ordered?");
	return 1;
    }
    co = LOW(co);
    if((i_aconst = member_array(co, const)) > -1)
    {
	o_constr = co;
	set_alarm(2.0, 0.0, "ask_for_input");
	return 1;
    }
    npc->command("say I haven't the talent to "+
      "make a "+co+" "+o_atype+" for you.");
    npc->command("say Would you please make a choice from "+
      "the materials listed on the counter?");
    npc->command("blush");
    return 1;
}


int style_type(string st)
{
    string *style;

    if (!present(ordering,TO))
    {
	ordering = 0;
	npc->make_order(TP);
	return 1;
    }
    if (TP != ordering)
    {
	npc->command("say Could you please wait until the "
	  +ordering->query_nonmet_name()+ " has ordered?");
	return 1;
    }

    st = LOW(st);
    if ((i_style = member_array(st, STYLE)) > -1)
    {
	o_style = st;
	set_alarm(2.0, 0.0, "ask_for_input");
	return 1;
    }
    npc->command("say I am not sure I can make a "+o_atype+
      " in a " +st+ " style.");
    npc->command("say Would you please make a choice from "+
      "the styles listed on the counter?");
    npc->command("sigh");
    return 1;
}

int estimate_value()
{
    int cac;
    cac = i_aconst*2 + 10 + i_ametal*2;
    if (cac > 20)
	cac = 20;
    return (GREED * F_VALUE_ARMOUR(cac) * METAL_PRICE[i_ametal] ) / 10000;
}

int describe_armour()
{
    npc->command("say You are asking me to make a "
+o_metal+" "+o_atype+" "+o_style+" "+o_constr+" cloak.");
    npc->command("say It will cost you about 100 coppers.");
    npc->command("say If you are not pleased with what you "+
      "have selected, you may 'rechoose'.");
npc->command("say If you are pleased, just 'accept cloak'.");
    npc->command("smile hope");
    return 1;
}

void init()
{
    ::init();
    add_action("accepted","accept");
    add_action("reordered","rechoose");
    add_action("reordered", "reselect");
    add_action("reordered","redesign");
    add_action("reordered","reorder");
    add_action("cancelled","cancel");
    add_action("construction_type","material",1);
    add_action("metal_type","color");
    add_action("armour_type","choose",1);
    add_action("style_type", "style", 1);
    add_action("pay_and_get","pay");
}                                                                                                                                                                                                                                                              

int
make_the_armour()
{
    object arm_obj;

    arm_obj = clone_object("/d/Emerald/sanctuary/arm/cloak");

    /* ************************************************************
     *          ALL THIS CODE NOW HANDLES IN THE HAT ITSELF
     *                     TO ALLOW FOR RECOVERY

	       // Medium to soft leather
      arm_obj->set_ac(3);      
    arm_obj->set_at(A_ROBE);
    arm_obj->add_name("cloak");
	       // It is a novelty item, so I've included a weight penelty.         
      arm_obj->add_prop(OBJ_I_WEIGHT, 2000); 
      arm_obj->add_prop(OBJ_I_VOLUME, 2000); 
      arm_obj->add_item(({"tag", "green tag"}), "Approved by Inspector 12.\n");

      arm_obj->set_long("This is a "+o_style+" "+o_metal+" "
    +o_atype+" "o_constr+". The quality of the craftsmanship "+
	       "is consistent with what one would expect of a hat made "+
	       "by Heboba of Sybarus.\nThere is a small tag green tag "+
	       "sewn to the inside of it.\n");

    arm_obj->set_short(""+o_style+" "+o_metal+" "+o_atype+" "+o_constr+"");
    arm_obj->set_name("cloak");
    arm_obj->set_adj(({o_style, o_metal, o_constr, o_type}));

    ******************************************************************** */

    arm_obj->set_adj1(o_style);
    arm_obj->set_adj2(o_metal);
    arm_obj->set_adj3(o_atype);
    arm_obj->set_adj4(o_constr);
    arm_obj->set_type("cloak");

    arm_obj->initialize_cloak();

    order += ({ ordering, arm_obj });

    return 1;
}     


leave_inv(obj,to)
{
    int i;
    ::leave_inv(obj,to);
    if (!living(obj)) return;
    if (npc)
	npc->command("shout Pleasure doin' business with you!");
    if (obj == ordering)
    {
	if (npc)
	    npc->command("shout I will cancel your order then, "+obj->query_name()+"!");
	ordering = 0;
	o_atype = 0;
	o_constr = 0;
	o_metal = 0;
	o_style = 0;
	return 1;
    }
}

int finish_armour(object player)
{
    int i,cnt,is_customer;
    string  a_name;

    if (!player) return 0;
    if (!order) return 0;
    cnt = sizeof(order)-1;
    is_customer = 0;
    while (cnt > 0)
    {
	if (player == order[cnt-1] && member_array(order[cnt],armour_ready) == -1)
	{
	    is_customer = 1;
	    i = cnt-1;
	}
	cnt-=2;
    }
    if (!is_customer)
	return 0;
    armour_ready += ({ order[i+1] });
    if (ENV(player) == TO) 
    {
	npc->command("say Celebrate the Source, "+player->query_nonmet_name()+"!");
	npc->command("smile joy");
	npc->command("say Your hat is a work of art!");
	npc->command("say It will cost you "+PRICE(order[i+1])+" coppers.");
	npc->command("say Just 'pay for hat', and you will get it.");
	return 1;
    }
    if (ENV(player) != TO) 
    {
	a_name = order[i+1]->query_name();
	tell_object(player,"A small, bedraggled child tugs on "+
	  "your sleeve.\nThe small, bedraggeld child whispers "+
	  "to you: Your "+
	  a_name+(a_name [strlen(a_name)-1..strlen(a_name)-1] == "s" ? " are" : " is") +
	  " now finished, and Heboba says you may retrieve it "+
	  "at your earliest convenience. The price is "+
	  PRICE(order[i+1] + 20)+" coppers.\nThe small, bedraggled "+
	  "child runs away.\n");
    }
    return 1;
}

cancelled()
{
    if (TP != ordering) {
	npc->command("say Wait a moment, please, "+
	  TP->query_nonmet_name()+".");
	return 1;
    }
    ordering = 0;
    o_atype = 0;
    o_constr = 0;
    o_metal = 0;
    o_style = 0;
    npc->command("say Your order has been cancelled.");
    return 1;
}

reordered()
{
    if (TP != ordering) {
	npc->command("say Please wait, "+TP->query_nonmet_name()+".");
	return 1;
    }
    o_atype = 0;
    o_constr = 0;
    o_metal = 0;
    o_style = 0;
    npc->command("emote throws away the design for your hat.");
    npc->command("say Let us start again, shall we?");
    npc->command("say Now, what type of hat do you want made?");
    npc->command("say Beret, bonnet, cap, fedora, fez, hat, "+
      "snood or turban?");
    npc->command("say Tell me with 'choose <type>'.");
    npc->command("smile hope");
    return 1;
}

void
reset_ordering()
{
    ordering = 0;
    o_atype = 0;
    o_metal = 0;
    o_constr = 0;
    o_style = 0;
}

int
accepted()
{
    if (TP != ordering)
    {
	npc->command("say Please wait, "+TP->query_nonmet_name()+".");
	return 1;
    }
    if (!o_atype || !o_metal || !o_constr)
    {
	npc->command("say You haven't told me exactly what you want, yet!");
	set_alarm(2.0, 0.0, "ask_for_input");
	return 1;
    }
    make_the_armour();
    set_alarm(itof( 45 + random(15) ), 0.0, &finish_armour(ordering));

    npc->command("say My helpers have already begun work on the hat, "+
      "so I'll just add the finishing touches");
    npc->command("say It should be ready in just a moment, if you "+
      "would like to wait.");

    npc->command("emote turns away from the counter and grabs hold "+
      "of some material.");

    npc->set_current_metal(o_metal);
    set_alarm(4.0, 0.0, "reset_ordering");
    return 1;
}

pay_and_get(string str)
{
    int i,cust,cnt,is_ready;
    object player;

    player = TP; cust = 0; cnt = sizeof(order);
    while (cnt > 0)
    {
	cnt-=2;
	if (order[cnt] == player) { i = cnt; cust = 1; }
    }
    if (!cust) 
    {
	npc->command("confused");
	npc->command("say Payment is not required until you have "+
	  "ordered and your hat has been made to your satisfaction.");
	npc->command("say If you are not satisfied you may either "+
	  "<cancel> or <reorder>.\n");
	return 1;
    }
    cnt = 0; is_ready = 0;
    while (cnt<sizeof(armour_ready))
    {
	if (order[i+1] == armour_ready[cnt]) { cust = cnt; is_ready = 1; }
	cnt++;
    }
    if (!is_ready) 
    {
	npc->command("say I am terribly sorry. I work too slowly, "+
	  "I am afraid.");
	npc->command("say Your order is not yet ready.");
	return 1;
    }
    npc->command("say That will be "+PRICE(order[i+1])+" coppers.");
    if (can_afford(player,PRICE(order[i+1]),order[i+1]->query_name())) 
    {
	armour_ready = exclude_array(armour_ready,cust,cust);
	if(order[i+1]->move(player)) 
	{
	    npc->command("say My! You certainly are carrying a lot!");
	    npc->command("say I'll just leave it here.");
	    order[i+1]->move(TO);
	    npc->command("say Thank you for the privilege of "+
	      "serving you!");
	    npc->command("smile charm");
	}
	say(QCTNAME(player)+" is handed "+order[i+1]->query_short()+".\n");

	write_file("/d/Avenir/common/bazaar/log/hatshop",
	  player->query_real_name()+" bought a "+order[i+1]->query_short()+ 
	  " on "+ctime(time())+".\n");

	finish_customer(i);
    }
    return 1;
}

can_afford(object player, int price, string arm)
{
    if (sizeof(money_arr = pay(price, player, pay_type, 0, 0, get_type)) == 1)
    {
	if (money_arr[0] == 2)
	{
	    npc->command("say You don't have enough "+pay_type+" coins, "+player->query_name()+".");
	    return 0;
	}
	if (money_arr[0] == 1) {
	    npc->command("say I think the "+arm+" is too costly for you to");
	    npc->command("say pay for it in "+pay_type+" coins.");
	    return 0;
	}
	else {
	    npc->command("say The "+arm+" is too expensive for you!");
	    npc->command("sob");     
	    return 0;
	}
    }
    coin_pay_text = text(exclude_array(money_arr,NUM,NUM*2-1));
    coin_get_text = text(exclude_array(money_arr,0,NUM-1));
    write("You pay "+coin_pay_text+" for the "+arm+".\n");
    write("You get "+coin_get_text+" back in change.\n");
    return 1;
}

finish_customer(int cust)
{
    order = exclude_array(order,cust,cust+1);
}


void
enter_inv(object ob, object from)
{
    int i, cnt, is_ready;

    ::enter_inv(ob, from);

    if((!from) || (!interactive(ob)))
	return;

    cnt = sizeof(order);
    i = -1;
    while(cnt > 0)
    {
	cnt-=2;
	if (order[cnt] == ob)
	    i = cnt;
    }
    if(i == -1)
	return;

    cnt = 0;
    is_ready = 0;
    while(cnt < sizeof(armour_ready))
    {
	if (order[i+1] == armour_ready[cnt]) 
	    is_ready = 1;
	cnt++;
    }
    if(!is_ready)
	return;

    set_alarm(2.0, 0.0, "info_pay_for_armour",({ob,PRICE(order[i+1])}));
    return;
}

void
info_pay_for_armour(mixed *arr)
{
    object ob;
    int price;
    ob = arr[0];
    price = arr[1];
    npc->command("say Celebrate the Source, "+ob->query_nonmet_name()+"!");
    npc->command("smile charm");
    npc->command("say Your hat is now finished!");
    npc->command("say It will cost you "+price+" coppers.");
    npc->command("say Just 'pay for hat', and I will give it to you.");
    return;
}                                                                                                                                                                                                                                                              



