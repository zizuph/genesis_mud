/* Blacksmith - the place to get armours made and repaired.
 * Elessar, January '92.
 * Modifications to make the armour rebootable,
 * Olorin, June '93
 *
 * Modification log:
 * 17-jan-1994, Olorin: Small changes:
 *              - remove set_up_vars(), set up vars using defines
 *              - List metals when ordering,
 *              - reset old value of o_aconst when new armour type is chosen
 */
inherit "/d/Gondor/common/room";
inherit "/lib/trade";
#include <money.h>
#include <stdproperties.h>
#include <macros.h>
#include <formulas.h>
#include <wa_types.h>
#include "/d/Gondor/defs.h"

#define VOL_STANDARD   150   /* Used to calculate the volume and weight */
#define GREED          125   /* price = value * greed */
#define PRICE(x)       x->query_prop(OBJ_I_VALUE) * GREED / 100
#define NUM            sizeof(MONEY_TYPES)
#define METAL          ({"silver", "brass", "gold", "bronze", "iron", \
                         "tempered iron", "steel", "alloyed steel", \
                         "high steel", "mithril", })
#define ATYPE          ({"armour", "shield", "helm", "greaves", "bracers", })
#define ACONST         ({"ring", "scale", "splint", "chain", "double", "bar", \
                         "augmented", "banded", "plate", })
#define HCONST         ({"ring", "chain", "double", "plate", "tabarded", \
                         "visored", "great", })
#define SCONST         ({"small", "medium", "large", })
#define METAL_PRICE    ({115, 80, 135, 85, 100, 110, 120, 160, 240, 600, })

//   Prototypes
int ask_for_input();
int describe_armour();
int finish_armour(object player);
void reset_ordering();
void info_pay_for_armour(mixed *arr);

object  customer,
        armour,
        smith,
        ordering,
       *armour_ready = ({});
mixed  *order = ({});
string  o_metal,
        o_atype,
        o_constr,
        cur_metal,
        pay_type,
        get_type,
        coin_pay_text,
        coin_get_text;
int     mithril_in_stock,
       *money_arr,
        i_atype,
        i_aconst,
        i_ametal;

void reset_room();

void create_room()
{
  set_short("The workshop of the blacksmith");
  set_long("This is the blacksmiths workshop, a hot place with armours of\n"+
    "all kinds on the walls, and a hot forge by the inner wall, where the\n"+
    "blacksmith heats and hammers metals into shields, helms and plates\n"+
    "to be worn by warriors throughout Gondor. There is a sign on one wall,\n"+
    "and a list just below it. North is the exit to the street.\n");
  add_prop(ROOM_I_INSIDE,1);
  add_prop(ROOM_I_NO_ATTACK,1);
  add_prop(ROOM_I_NO_CLEANUP,1);
  add_item("armours",
    "There are all kinds of armours in here: Plate armours, scale mails,\n"+
    "chain mails and ring mails, round metal shields, huge wall shields,\n"+
    "visored helms and smaller pot helmets. There are plate leggings and\n"+
    "arm bracers.\n");
  add_item(({"sign","poster"}),"@@read_sign");
  add_item(({"list","armourlist"}),"@@exa_armourlist");
  add_item(({"prices","pricelist"}),"@@exa_pricelist");
  add_item("forge","The heat from the forge is incredible, you have no understanding for\n"+
    "how the blacksmith manages to work under these conditions every day.\n"+
    "A large black anvil stands next to a large bellows, and a pair of\n"+
    "pliers and some hammers lie on a shelf.\n");
  add_exit(MINAS_DIR + "s1crc2","north",0,0);
  reset_room();
  config_default_trade();
}

object query_ordering()
{
  return ordering;
}

void reset_room()
{
    if (!smith || !present("calmacil",TO))
    {
        smith = clone_object(MINAS_DIR + "npc/calmacil");
        smith->move(TO);
    }
}

string read_sign()
{
  write("           Calmacil's Armoury\n"+
        "          --------------------\n"+
        "  Calmacil the Blacksmith crafts metal armours on request.\n"+
        "  You may state what kind of armour you want,\n"+
        "  and what kind of metal it should be made of.\n"+
        "  Price will be calculated according to your choice.\n\n"+
        "  To order, just say that you would like to order. You\n"+
        "  will be asked for type of armour (armour, shield, helm etc.),\n"+
        "  construction type (plate, chain, ring etc.), and last\n"+
        "  what kind of metal you would like the armour to be made of.\n"+
        "  See the armourlist to get the available armour-types\n"+
        "  and constructions. After stating your choices you will\n"+
        "  be given an estimated price, after which you may cancel\n"+
        "  your order. The armour may take some time to finish, but\n"+
        "  you will be duly notified when it can be picked up.\n\n"+
        "  Calmacil is also capable of repairing armours that are\n"+
        "  damaged by battle. Please give the armour to him and he\n"+
        "  will examine it and repair it if you want him to.\n"+
        "     Please feel free to place an order!\n");
  return "";
}

string exa_armourlist()
{
  write("           Calmacil's Armoury\n"+
        "          --------------------\n"+
        "  Possible armour types:\n"+
        "    Armours, shields, helms, greaves (for legs),\n"+
        "    and bracers (for arms).\n\n"+
        "  Possible constructions, listed from worst to best:\n"+
        "    Ring, scale, splint, chain, double, bar,\n"+
        "    augmented, banded and plate mails.\n\n"+
        "  Metals available:\n"+
        "    Iron, bronze, brass, silver, gold, steel,\n"+
        "    alloyed steel, tempered iron and high steel.\n");
  return "";
}

string exa_pricelist()
{
  write("           Calmacil's Armoury\n"+
        "          --------------------\n"+
        "      Prices, relative to metal and construction.\n"+
        "   Iron - standard price.\n"+
        "   Bronze - 85 % of standard price, not quite so solid.\n"+
        "   Brass - 80 % of standard price, even less solid.\n"+
        "   Gold - 135 % of standard price, quite soft metal.\n"+
        "   Silver - 115 % of standard price, even softer than gold.\n"+
        "   Tempered iron - 110 % of standard price, better than iron.\n"+
        "   Steel - 120 % of standard price, even better than t.iron.\n"+
        "   Alloyed steel - 160 % of standard price.\n"+
        "   High steel - 240 % of standard price.\n"+
        "   Mithril - 600 % of standard price - hardly available.\n");
  return "";
}

int place_order(object player)
{
    if (!present(player,TO))
        return 0;
    if (player == ordering)
    { 
        smith->command("say You are already ordering!");
        smith->command("say Please continue designing the armour.");
        return 1;
    }
    customer = player;
    ordering = player;
    smith->command("say What type of armour would you like?");
    smith->command("say Armour, shield, helm, bracers, or greaves?");
    smith->command("say State your wish with 'armourtype <type>'.");
    smith->command("smile");
    return 1;
}

int armour_type(string at)
{
    if (!ordering)
        smith->make_order(TP);
    if (!present(ordering,TO))
    {
        ordering = 0;
        smith->make_order(TP);
        return 1;
    }
    if (TP != ordering)
    {
        smith->command("say Could you please wait until the "+ordering->query_nonmet_name()+
            " has ordered?");
        return 1;
    }
    if (!at) { smith->command("say Yes, choose the type of armour you want.");
      smith->command("say Use 'armourtype <type>'.");
      return 1;
      }
    at = LOW(at);
    if ((i_atype = member_array(at, ATYPE)) > -1)
    {
        o_atype = at;
        o_constr = 0;
        set_alarm(2.0,0.0,&ask_for_input());
        return 1;
    }
    smith->command("say I don't know how to make a "+at+".");
    smith->command("shrug");
    return 1;
}

int
ask_for_input()
{
  if (!o_atype)
    {
      smith->command("say Well, what kind of armour do you want?");
      smith->command("say I can make armours, shields, helms, and");
      smith->command("say also greaves and bracers.");
      smith->command("say Choose with 'armourtype <text>'.");
      return 1;
    }
  if (!o_constr)
    {
      smith->command("say How would you like it constructed?");
      smith->command("say These are the constructions I know for "+
        (o_atype[strlen(o_atype)-1..strlen(o_atype)-1] == "s" ? o_atype : o_atype+"s")+
        ".");
      switch(o_atype)
  {
  case "helm":
    tell_room(TO,break_string(CAP(implode(HCONST,", "))+".\n",70));
    break;
  case "shield":
    tell_room(TO,break_string(CAP(implode(SCONST,", "))+".\n",70));
    break;
  default:
    tell_room(TO,break_string(CAP(implode(ACONST,", "))+".\n",70));
  }
      smith->command("say Choose by 'construction <text>'.");
      return 1;
    }
  if (!o_metal)
    {
      smith->command("say Now what kind of metal would you like?");
      smith->command("say I have the following metals available:");
      smith->command("say " + CAP(implode(
          (mithril_in_stock ? METAL[0..8] : METAL[0..7]), ", ")) + 
          ", and " + 
          (mithril_in_stock ? METAL[9] : METAL[8]) + ".");
      smith->command("say Choose by 'metal <metal>'.");
      return 1;
    }
  set_alarm(2.0,0.0,&describe_armour());
}

int metal_type(string me)
{
    if (!present(ordering,TO))
    {
        ordering = 0;
        smith->make_order(TP);
        return 1;
    }
    if (TP != ordering)
    {
        smith->command("say Could you please wait until the "
            +ordering->query_nonmet_name()+ " has ordered?");
        return 1;
    }
    me = LOW(me);
    if (me == "mithril" && !mithril_in_stock)
    {
        smith->command("say I'm deeply sorry, but mithril cannot be found");
        smith->command("say anywhere anymore. You will have to choose again.");
        return 1;
    }
    if ((i_ametal = member_array(me, METAL)) > -1)
    {
        o_metal = me;
        set_alarm(2.0,0.0,&ask_for_input());
        return 1;
    }
    smith->command("say I don't have that kind of metal.");
    smith->command("say Please choose again.");
    o_metal = 0;
    set_alarm(2.0,0.0,&ask_for_input());
    return 1;
}

int construction_type(string co)
{
    string *const;

    if (o_atype == "shield")
        const = SCONST;
    else if (o_atype == "helm")
        const = HCONST;
    else
        const = ACONST;
    if (!present(ordering,TO))
    {
        ordering = 0;
        smith->make_order(TP);
        return 1;
    }
    if (TP != ordering)
    {
        smith->command("say Could you please wait until the " +
            ordering->query_nonmet_name()+ " has ordered?");
        return 1;
    }
    co = LOW(co);
    if((i_aconst = member_array(co, const)) > -1)
    {
        o_constr = co;
        set_alarm(2.0,0.0,&ask_for_input());
        return 1;
    }
    smith->command("say I don't know how to construct a "+co+" "+o_atype+".");
    smith->command("say Please choose again from the constructions listed");
    smith->command("say on the armour-list.");
    smith->command("smile");
    return 1;
}

int estimate_value()
{
    int cac;
    cac = i_aconst*2 + 10 + i_ametal*2;
    if (cac > 40)
        cac = 40;
    return (GREED * F_VALUE_ARMOUR(cac) * METAL_PRICE[i_ametal] ) / 10000;
}

int describe_armour()
{
  smith->command("say You have chosen a "+o_constr+" "+o_atype+" of "+o_metal+".");
  smith->command("say This will cost about "+estimate_value()+" coppers,");
  smith->command("say not taking the metal in account.");
  smith->command("say If you are not pleased with this, you may 'rechoose'.");
  smith->command("say If you are pleased, just do 'accept armour', and");
  smith->command("say I will start working on it. You may wait here, or");
  smith->command("say await a messenger from me somewhere else.");
  smith->command("say Pay when you pick it up.");
  smith->command("smile");
  return 1;
}

void init()
{
  ::init();
  add_action("do_read","read",1);
  add_action("accepted","accept");
  add_action("reordered","rechoose");
  add_action("reordered","redesign");
  add_action("reordered","reorder");
  add_action("cancelled","cancel");
  add_action("construction_type","const",1);
  add_action("metal_type","metal");
  add_action("armour_type","armour",1);
  add_action("pay_and_get","pay");
}

int do_read(string str)
{
    if (!str)
    {
        NF("Read what?\n");
        return 0;
    }
    if (str == "armourlist" || str == "list")
        exa_armourlist();
    if (str == "sign" || str == "poster")
        read_sign();
    return 1;
}

int
make_the_armour()
{
  object arm_obj;

  arm_obj = clone_object(MINAS_DIR + "obj/mtarmour.c");
  arm_obj->set_armtype(i_atype);
  arm_obj->set_metal(i_ametal);
  arm_obj->set_const(i_aconst);
  order += ({ ordering, arm_obj });

  return arm_obj->make_the_armour();
}

leave_inv(obj,to)
{
  int i;
  ::leave_inv(obj,to);
  if (!living(obj)) return;
  if (smith)
  smith->command("shout Fare well, traveller and come back soon!");
  if (obj == ordering)
    {
      if (smith)
      smith->command("shout I will cancel your order then, "+obj->query_name()+"!");
      ordering = 0;
      o_atype = 0;
      o_constr = 0;
      o_metal = 0;
      return 1;
    }
}

finish_armour(object player)
{
  int i,cnt,is_customer;
  string  a_name;

  if (!player) return;
  if (!order) return;
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
    smith->command("say Ah - "+player->query_nonmet_name()+"!");
    smith->command("smile");
    smith->command("say Your armour is now finished!");
    smith->command("say It will cost you "+PRICE(order[i+1])+" coppers.");
    smith->command("say Just 'pay for armour', and you will get it.");
    return 1;
  }
  if (ENV(player) != TO) 
  {
      a_name = order[i+1]->query_name();
      tell_object(player,"A pigeon comes flying, delivering the following message:\n"+
          "Your "+a_name+(a_name [strlen(a_name)-1..strlen(a_name)-1] == "s" ? " are" : " is") +
          " now finished, and you may come\n"+
          "and fetch it when you have the time. The price is "+
          PRICE(order[i+1])+" coppers.\n"+
          "  Yours, "+smith->query_name()+" "+smith->query_title()+".\n");
  }
  return 1;
} 

cancelled()
{
  if (TP != ordering) {
    smith->command("say Please wait, "+TP->query_nonmet_name()+".");
    return 1;
    }
  ordering = 0;
  o_atype = 0;
  o_constr = 0;
  o_metal = 0;
  smith->command("say Ok, you have cancelled your order.");
  return 1;
}

reordered()
{
  if (TP != ordering) {
    smith->command("say Please wait, "+TP->query_nonmet_name()+".");
    return 1;
    }
  o_atype = 0;
  o_constr = 0;
  o_metal = 0;
  smith->command("say Ok, redesigning the armour. What kind would you like?");
  smith->command("say Armour, shield, helm, bracers, or greaves?");
  smith->command("say State your wish with 'armourtype <type>'.");
  smith->command("smile");
  return 1;
}

void
reset_ordering()
{
    ordering = 0;
    o_atype = 0;
    o_metal = 0;
    o_constr = 0;
}

int
accepted()
{
    if (TP != ordering)
    {
        smith->command("say Please wait, "+TP->query_nonmet_name()+".");
        return 1;
    }
    if (!o_atype || !o_metal || !o_constr)
    {
        smith->command("say You haven't told me exactly what you want, yet!");
        set_alarm(2.0,0.0,&ask_for_input());
        return 1;
    }
    make_the_armour();
    set_alarm(itof(60+random(15)),0.0,&finish_armour(ordering));
    smith->command("say That is a deal! I will start crafting it at once.");
    smith->command("say I will send a messenger to notify you.");
    smith->command("wave");
    tell_room(TO,"The blacksmith starts heating a piece of "+o_metal+".\n");
    smith->set_current_metal(o_metal);
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
    smith->command("say Pay? For what? You have no order placed here.");
    smith->command("shrug");
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
    smith->command("say I'm sorry, I have not yet finished it.");
    smith->command("say Please come back later.");
    return 1;
  }
  smith->command("say That will be "+PRICE(order[i+1])+" coppers.");
  if (can_afford(player,PRICE(order[i+1]),order[i+1]->query_name())) 
  {
    armour_ready = exclude_array(armour_ready,cust,cust);
    if(order[i+1]->move(player)) 
    {
      smith->command("say It's too heavy for you to carry.");
      smith->command("say I'll just drop it here for you.");
      order[i+1]->move(TO);
      smith->command("say Hope you will be pleased! Welcome back!");
      smith->command("smile");
    }
    say(QCTNAME(player)+" is handed "+order[i+1]->query_short()+".\n");
/*
    write_file("/d/Gondor/log/smiths",player->query_name()+
      " bought "+order[i+1]->query_short()+" for "+PRICE(order[i+1])+
      " cc. from "+smith->query_name()+", "+ctime(time())+".\n");
*/
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
      smith->command("say You don't have enought "+pay_type+" coins, "+player->query_name()+".");
      return 0;
    }
    if (money_arr[0] == 1) {
      smith->command("say I think the "+arm+" is too expensive to only");
      smith->command("say pay for it in "+pay_type+" coins.");
      return 0;
      }
    else {
      smith->command("say The "+arm+" is too expensive for you!");
      smith->command("say All this work for naught! Begone!");
      smith->command("growl");
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

/*
 * This function was meant to replace to interface to the
 * catch_tell in Calmacil, but since catch_tell works again
 * with the new gd now, it's become obsolete.
 * Olorin, 9-jun-1993
 */
int
do_listen(string str)
{
  string verb, dummy, fixstr, *arr;

  if(!smith || !present(smith,TO)) return 0;
  verb = query_verb();
  if(verb == "'") verb = "say";
  arr = explode(verb,"");
  if(arr[0] == "'")
  {
    verb = "say";
    dummy = implode(arr[1..sizeof(arr)], "");
    if(str) str = dummy + " " + str;
    else str = dummy;
  }
  if(verb != "say") write(">>>> ERROR in do_listen, verb = " + verb);
  fixstr = TP->query_name() + " " + verb + "s: " + str;
  smith->new_catch_tell(fixstr);
  return 0;
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

  set_alarm(1.0,0.0,&info_pay_for_armour(({ob,PRICE(order[i+1])})));
  return;
}

void
info_pay_for_armour(mixed *arr)
{
  object ob;
  int price;
  ob = arr[0];
  price = arr[1];
  smith->command("say Ah - "+ob->query_nonmet_name()+"!");
  smith->command("smile");
  smith->command("say Your armour is now finished!");
  smith->command("say It will cost you "+price+" coppers.");
  smith->command("say Just 'pay for armour', and you will get it.");
  return;
}
