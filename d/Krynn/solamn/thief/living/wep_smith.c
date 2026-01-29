/* created by Aridor, 06/10/94 */
/*
 * Added support for the commerce module in July 2002, by Boron
 */

#include "../local.h"
inherit M_FILE

inherit "/d/Genesis/lib/commerce";

#include <macros.h>
#include <money.h>
#include <ss_types.h>
#include <wa_types.h>
#include <formulas.h>

#define  ABOUT         OBJ + "about/"
#define MY_WEAPON      OBJ + "pweapon"

/*prototype*/
void arm_me();

int alrm; /* the alarm while working on the weapon */
mapping stock = ([ ]);
int good = 0;
mixed my_own = ({});
int enter_alrm = 0;

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

void
create_krynn_monster()
{
    set_name("darrag");
    set_living_name("darrag");
    add_name("smith");
    set_adj("massive");
    add_adj("dark");
    add_adj("dwarven");
    set_gender(0);
    set_short("@@query_adjects@@ smith");
    set_long("This is a @@query_adjects@@ smith. The expression on his face " +
         "lets you think this guy must have been here under this " +
         "mountain all his life. He looks just as hard as the rock " +
         "around him, probably even harder! He is the weapon and tool" +
         "smith of this clan. You can enquire about weapons here and " +
         "also order them.\n");
    set_race_name("dwarf");
    set_title("the Blacksmith of Vingaard Mountains");
    default_config_mobile(120);
    set_all_attack_unarmed(20, 60);
    set_all_hitloc_unarmed(60);
    set_skill(SS_WEP_CLUB, 100);
    add_prop(LIVE_I_SEE_DARK, 2);
    set_alignment(-random(20) - 40);
    set_knight_prestige(1440);
    add_prop(NPC_I_NO_LOOKS,1);
    set_introduce(1);


    // Add commerce support
    set_commerce_savefile("/d/Krynn/common/commerce/darrag_data");
    config_default_trade();

    add_demanded_commodity("goldpiece", 11, 100, 1.5);
    set_commodity_amount("goldpiece", 10);
    set_commodity_reserve("goldpiece", 10);

    add_demanded_commodity("silverpiece", 10, 100, 1.5);
    set_commodity_amount("silverpiece", 10);
    set_commodity_reserve("silverpiece", 20);

    add_demanded_commodity("carbonpiece", 9, 100, 1.5);
    set_commodity_amount("carbonpiece", 10);
    set_commodity_reserve("carbonpiece", 20);

    add_demanded_commodity("ironpiece", 8, 100, 1.5);
    set_commodity_amount("ironpiece", 10);
    set_commodity_reserve("ironpiece", 30);


    add_supplied_commodity ("gold bar", 16, 15, 0.2);
    add_supplied_commodity ("silver bar", 15, 15, 0.2);
    add_supplied_commodity ("carbon bar", 14, 15, 0.2);
    add_supplied_commodity ("iron bar", 13, 15, 0.2);

    add_supply_requirement("gold bar", ({"goldpiece", 2 }) );
    add_supply_requirement("silver bar", ({"silverpiece", 2 }) );
    add_supply_requirement("carbon bar", ({"carbonpiece", 2 }) );
    add_supply_requirement("iron bar", ({"ironpiece", 2 }) );

    set_commodity_amount("iron bar", 11);
    set_commodity_amount("carbon bar", 4);


    set_act_time(10);
    add_act("emote hammers on a glowing piece of metal.");
    add_act("emote holds a glowing piece of metal into a bucket.");
    add_act("emote wipes the sweat from his brows.");
    add_act("smile contentedly");
    add_act("grumble");
    add_act("emote gets something out of the forge.");
    add_act("emote puts something into the forge.");
    add_act("emote hammers on a piece of metal.");
    add_act("emote checks a tub filled with steaming fluid metal.");
    add_act("say I'll buy metal nuggets if ya find'em!");
    add_act("say If I get nuff'nuggets I'll make a bar, easier to work with bars.");
    add_act("say From time to time I sell of my stock of metal bars.");

    add_ask("[about] [how] [to] [do] [i] 'order' / 'ordering'",
        "say Type 'order <weapon> from <material> of <quality> " +
        "quality'. You can ask me about weapons, materials and " +
        "qualities of course, too.",1);
    add_ask("[about] 'weapon' / 'weapons'",
        "@@do_enquire:" + file_name(TO) + "|weapons@@",1);
    add_ask("[about] 'axe' / 'axes'",
        "@@do_enquire:" + file_name(TO) + "|axes@@",1);
    add_ask("[about] 'hammer' / 'hammers'",
        "@@do_enquire:" + file_name(TO) + "|hammers@@",1);
    add_ask("[about] 'sword' / 'swords'",
        "@@do_enquire:" + file_name(TO) + "|swords@@",1);
    add_ask("[about] 'knife' / 'knives'",
        "@@do_enquire:" + file_name(TO) + "|knives@@",1);
    add_ask("[about] [weapon] 'material' / 'materials'",
        "@@do_enquire:" + file_name(TO) + "|materials@@",1);
    add_ask("[about] [weapon] 'quality' / 'qualities'",
        "@@do_enquire:" + file_name(TO) + "|quality@@",1);
    add_ask("[about] [weapon] 'type' / 'types'",
        "@@do_enquire:" + file_name(TO) + "|types@@",1);
    add_ask("[about] [weapon] 'cost' / 'price' / 'prices'",
        "@@do_enquire:" + file_name(TO) + "|prices@@",1);
    add_ask("[about] 'cogwheel' / 'cogwheels'",
        "say You need a cogwheel? Well, that's easy. Just make yourself " +
        "one.",1);
    set_default_answer(VBFC_ME("def_answer"));
    if (IS_CLONE)
      set_alarm(2.0,0.0,"arm_me");

}

string
def_answer()
{
    command("say I don't know a thing about that!");
    return "";
}

void
arm_me()
{
    object ob;
    seteuid(getuid(TO));
    ob = MONEY_MAKE_GC(random(10));
    my_own += ({ ob });
    ob->move(TO,1);
    ob = MONEY_MAKE_SC(random(20));
    my_own += ({ ob });
    ob->move(TO,1);
    ob = clone_object(OBJ + "hammer2");
    my_own += ({ob});
    ob->move(TO,1);
    ob = clone_object(OBJ + "smail2");
    my_own += ({ob });
    ob->move(TO,1);
    remove_prop(NPC_M_NO_ACCEPT_GIVE);
    command("wear all");
    command("wield all");
}

int
handle_given_object(object what, object who)
{
    enter_alrm = 0;
    if (member_array(what,my_own) >= 0)
      return 0;
    if (member_array(what,m_values(stock)) >= 0)
      return 0;
    if (!what)
      {
      command("say Why thank you!");
      return 0;
      }
    if (!what->is_blunt())
      {
      command("say I have no use for this " + what->short());
      command("drop " + what->query_name());
      return 0;
      }
    if (alrm)
      {
      command("say I am currently very busy with this other order here.");
      command("drop " + what->query_name());
      command("say Please come back when I am finished.");
      return 0;
      }
    command("nod hap");
    command("say I see you made that yourself. Very nice!");
    command("say I assume you want me to forge this for you?");
    command("say Ok, here's the deal: This should take a little while " +
        "to work on, but if you take a little time and enjoy the " +
        "area, I'll have it ready for you when you come back.");
    alrm = set_alarm(120.0,0.0,"give_out_weapon", who->query_real_name(),
             what, 0, what->query_reduce_pay());
    return 1;
}

void
enter_inv(object ob, object from)
{
    enter_alrm = set_alarm(2.0,0.0,"handle_given_object",ob,((from && interactive(from)) ? from : TP));
    ::enter_inv(ob,from);
}

string
query_adjects()
{
  return query_adjs()[0] + " " + query_adjs()[1] + " " + query_adjs()[2];
}


void
init_living()
{
    add_action("order","order");
    add_action("enquire","enquire");
    add_action("collect","collect");
    ::init_living();

    init_commerce();
}

public string
stat_living()
{
    return ::stat_living() + stat_commerce();
}

int
collect(string str)
{
    object wep;
    if (alrm)
      {
      command("say I'm already very busy. You have to wait until I " +
          "have finished this piece of art.");
      return 1;
      }
    command("say Ahh yes, you want to pick up your ordered weapon?");
    command("say I'll go look for it right away.");
    command("emote turns around and starts searching a rack full of weapons.");
    wep = stock[TP->query_real_name()];
    alrm = set_alarm(10.0,0.0,"give_out_weapon",TP->query_real_name(),
             wep, 1, wep->query_reduce_pay());
    return 1;
}

/* returns an array: ({ wep type, type of hit, wep_hit, wep_pen, time to make})
 */
mixed *
compute_all_necessary_weapon_data(string typ, string mat, string qual)
{
    int m,q,t,typ1,typ2,mod1,mod2;
    switch(mat)
      {
    case "bronze":
    case "iron":
      m = 1;
      break;
    case "silver":
      m = 2;
      break;
    case "gold":
      m = 3;
      break;
    case "platinum":
      m = 4;
      break;
    case "steel":
      m = 5;
      break;
    default: command("say I'm sorry, I didn't understand what material you wanted.");
      m = 0;
      }

    switch(qual)
      {
    case "very poor":
    case "poor":
      q = 1;
      break;
    case "standard":
      q = 3;
      break;
    case "good":
      q = 4;
      break;
    case "very good":
      q = 5;
      break;
    case "extremely good":
      q = 6;
      break;
     case "excellent":
      q = 7;
      break;
     case "superior":
      q = 9;
      break;
    default: command("say I'm sorry, I didn't understand what quality you wanted.");
      q = 0;
      }

    switch(typ)
      {
    case "knife":   typ1 = W_KNIFE;
                    typ2 = W_IMPALE;
                    mod1 = 1;
                    mod2 = 0;
                    t = 1;
                        break;
    case "sword":   typ1 = W_SWORD;
                    typ2 = W_SLASH | W_IMPALE;
                        mod1 = 9;
                    mod2 = 8;
                    t = 4;
                        break;
    case "axe":     typ1 = W_AXE;
                    typ2 = W_BLUDGEON | W_SLASH;
                    mod1 = 3;
                    mod2 = 8;
                    t = 3;
                        break;
    case "hammer":  typ1 = W_CLUB;
                    typ2 = W_BLUDGEON;
                    mod1 = 1;
                    mod2 = 7;
                    t = 2;
                    break;
    default:        command("say I'm sorry, but I didn't understand what type of weapon you wanted.");
                    t = 0;
      }
    if (t && m && q)
      return ({ typ1, typ2, 4 + q * 2 + m + mod1,
          4 + q * 2 + m + mod2, 60 + 5 * q * m * t });
    else
      return 0;
/*check formulas again!*/
}

/*
 * Description: ob can either be the weapon itself or an array with
 * ({ wep_hit, wep_pen }), reduce means the blank was given and to
 * reduce the price.
 */
int
calculate_price(mixed ob, object for_who, int reduce)
{
    int price;
    if (objectp(ob))
      price = F_VALUE_WEAPON(ob->query_hit(), ob->query_pen());
    else
      price = F_VALUE_WEAPON(ob[0],ob[1]);
    if (SGN(for_who->query_alignment()) == SGN(query_alignment()))
      price = price * 4 / 5;
    else
      price = price * 6 / 5;
    price = price * (300 - for_who->query_skill(SS_TRADING)) / 200;
    price = (price > 100 ? price - 10 + random(20) : price);
    return price * (100 - reduce) / 100;
}

void
give_out_weapon(string who_name, object wep, int flag, int reduce)
{
    int price,i;
    string typ;
    object who;
    string what_is_it = (wep->id("cogwheel") ? "cogwheel" : "weapon");

    if (who_name)
      who = find_player(who_name);
    if (!who || E(TO) != E(who))
      {
      if (flag)
        command("say Now, wasn't there someone here just a second ago " +
            "asking me for a " + what_is_it + "?");
      else
        command("say Now, where'd go? Gosh, they don't wanna witness " +
            "the finishing of a " + what_is_it + "?");
      command("gasp");
      if (wep)
        {
        if (flag)
          command("say Oh, well, I'll just put it back in stock.");
        else
          {
              command("say Oh, well, I'll just put it in stock till " +
                  "whoever comes to collect it.");
              stock += ([ who_name:wep ]);
          }
        }
      command("shrug");
      alrm = 0;
      return;
      }
    if (!wep)
      {
      if (flag)
        command("say I'm sorry, but I cannot find a " + what_is_it + " ordered by " +
            "you.");
      else
        command("say I'm sorry, but something went wrong with your " +
            "order.");
      command("shrug");
      alrm = 0;
      return;
      }
    wep->move(TO);
    command("say Ahh, an excellent piece of art, this " + what_is_it + "!");
    alrm = 0;

    /*pay in here!*/
    price = calculate_price(wep, who, reduce);
    if (!MONEY_ADD(who, -price))
      {
      command("say I'm sorry, but it seems you can't pay!");
      command("say I'll keep the " + what_is_it + " here for you in stock.");
      wep->move(VOID);
      stock += ([ who_name:wep ]);
      return;
      }
    who->catch_msg("You pay the price of " + price + " copper coins.\n");
    i = wep->query_wt();
    switch(i)
      {
    case 0: typ = "sword";
            break;
    case 2: typ = "axe";
            break;
    case 3: typ = "knife";
            break;
    case 4: typ = "hammer";
            break;
    default: typ = "weapon";
      }

    wep->remove_shadow();
    if (wep->id("cogwheel"))
      command("say There you are, a really fine cogwheel.");
    else
      command("say There you are, your weapon, a really fine " + typ + ".");
    if (!command("give " + wep->query_name() + " to " + who_name))
      command("drop " + wep->query_name());
    stock = m_delete(stock, who_name);
    if (enter_alrm)
      {
      remove_alarm(enter_alrm);
      enter_alrm = 0;
      }
}

int
order(string str)
{
    string typ, mat, qual, time_to_wait;
    mixed *ret_arr;
    int c;
    if (alrm)
      {
      command("say I'm already very busy. Please wait with your " +
          "order until I have finished this piece of art.");
      return 1;
      }
    NF(C(query_verb()) + " what?\n");
    if (!str)
      return 0;
    if (stock[TP->query_real_name()])
      {
      NF("There is already a weapon in stock for you! Why don't you " +
         "collect it first?\n");
      return 0;
      }
    /* syntax is: 'order <type> from <material> of <quality> quality' */
    c = sscanf(str, "%s from %s of %s quality", typ, mat, qual);
    NF(C(query_verb()) + " what from what material of what quality?\n");
    if (c < 3 || c > 3)
      return 0;

    ret_arr = compute_all_necessary_weapon_data(typ, mat, qual);
    if (ret_arr)
      {
      alrm = set_alarm(itof(ret_arr[4]),0.0,"finished_weapon",
               TP->query_real_name(),typ,mat,
               qual,ret_arr[2],ret_arr[3],ret_arr[0],ret_arr[1]);
      write("You order your weapon.\n");
      say(QCTNAME(TP) + " orders a weapon.\n");
      if (ret_arr[4] > 120)
        time_to_wait = "This might take quite long. It's probably better if " +
          "you just come back later to 'collect' your weapon.";
      else
        time_to_wait = "This might take a while. You can either wait or come back later and 'collect' your order'.";
      command("say " + time_to_wait);
      return 1;
      }
    NF("You failed to order a weapon.\n");
    return 0;
}

void
finished_weapon(string for_who, string typ, string mat, string qual,
        int wp_hit, int wp_pen, int wp_typ, int wp_style)
{
    int wgt;
    object wep = clone_object(MY_WEAPON);
    wep->set_weapon_data(typ + "&&" +
             qual + "&&" +
             mat + "&&" +
             for_who + "&&" +
             wp_hit + "&&" +
             wp_pen + "&&" +
             wp_typ + "&&" +
             wp_style);
    give_out_weapon(for_who, wep, 0, 0);
}

void
relate_message(string what)
{
    string *arr;
    int i;
    arr = explode(what,"\n");
    for(i=0;i<sizeof(arr);i++)
      if (arr[i])
    command(arr[i]);
}

int
enquire(string str)
{
    int c, price, time;
    string reply = 0,typ,mat,qual;
    mixed *ret_arr;
    NF(C(query_verb()) + " about what?\n");
    if (!str)
      return 0;
    switch(str)
      {
    case "about weapon":
    case "about weapons":
      reply = read_file(ABOUT + "weapons");
      break;
    case "about axe":
    case  "about axes":
      reply = read_file(ABOUT + "axes");
      break;
    case "about hammer":
    case "about hammers":
      reply = read_file(ABOUT + "hammers");
      break;
    case "about sword":
    case "about swords":
      reply = read_file(ABOUT + "swords");
      break;
    case "about knife":
    case "about knives":
      reply = read_file(ABOUT + "knives");
      break;
    case "about material":
    case "about materials":
    case "about weapon material":
    case "about weapon materials":
      reply = read_file(ABOUT + "materials");
      break;
    case "about quality":
        case "about qualities":
    case "about weapon quality":
        case "about weapon qualities":
      reply = read_file(ABOUT + "quality");
      break;
    case "about weapon types":
    case "about types":
      reply = read_file(ABOUT + "types");
      break;
    case "about weapon prices":
    case "about prices":
      reply = read_file(ABOUT + "prices");
      break;
      }
    if (reply && reply != "")
      {
      relate_message(reply);
      return 1;
      }

    /* syntax is: 'enquire about <type> from <material> of <quality> quality' */
    c = sscanf(str, "about %s from %s of %s quality", typ, mat, qual);
    NF("I don't know a thing about that!\n");
    if (c <= 0)
      return 0;
    NF(C(query_verb()) + " about what from what material?\n");
    if (c == 1)
      return 0;
    NF(C(query_verb()) + " about what from what material of what quality?\n");
    if (c == 2)
      return 0;
    if (c == 3)
      {
      ret_arr = compute_all_necessary_weapon_data(typ, mat, qual);
      if (ret_arr)
        {
        price = calculate_price(({ret_arr[2], ret_arr[3]}),TP,0);
        time = (ret_arr[4] / 60) + 1;
        command("say Let me think...");
        command("emote murmurs something about good, evil and the " +
            "hammer of Reorx.");
        command("nod");
        command("hmm");
        command("say Well, I estimate the price for this weapon " +
            "would be " + price + " coppers. Give or take some.");
        command("say The time to make this weapon will be " +
            "approximately " + time + " minutes. You decide if " +
            "you want to wait.");
        }
      return 1;
      }
    NF("I don't know a thing about that!\n");
    return 0;
}

string
do_enquire(string str)
{
    if (enquire("about " + str))
      return "";
    else
      return 0;
}

void
make_good()
{
    if (good)
      return;
    good = 1;
    remove_adj("dark");
    add_adj("friendly");
    set_long("This is a @@query_adjects@@ dwarf. From the expression on his face " +
         "you wouldn't think this guy has been here under this " +
         "mountain all his life. He looks friendly and has a merry twinkle in " +
         "his eyes, blinking at you from above his beard. He is the weapon and tool" +
         "smith of this clan. You can enquire about weapons here and " +
         "also order them.\n");
    set_alignment(random(20) + 40);
    set_knight_prestige(-1);
    command("emote cheers up visibly as his aura shifts from dark to light.");
    command("smile");
}

void
make_evil()
{
    if (!good)
      return;
    good = 0;
    remove_adj("friendly");
    add_adj("dark");
    set_long("This is a @@query_adjects@@ dwarf. The expression on his face " +
         "lets you think this guy must have been here under this " +
         "mountain all his life. He looks just as hard as the rock " +
         "around him, probably even harder! He is the weapon and tool" +
         "smith of this clan. You can enquire about weapons here and " +
         "also order them.\n");
    set_alignment(-random(20) - 40);
    set_knight_prestige(1440);
    command("emote moans and chokes back a scream as his aura shifts from light to dark.");
    command("grin");
}
