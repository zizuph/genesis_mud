/* created by Aridor, 06/10/94 */
#include "/d/Krynn/common/defs.h"
#include "/d/Ansalon/goodlund/nethosak/city/local.h"

inherit M_FILE
#include <macros.h>
#include <money.h>
#include <ss_types.h>
#include <wa_types.h>
#include <formulas.h>

#define MY_WEAPON      OBJ + "pweapon"
#define OBJ            "/d/Ansalon/goodlund/nethosak/city/obj/"

/*prototype*/
void arm_me();

int alrm; /* the alarm while working on the weapon */
mapping stock = ([ ]);
int good = 0;
mixed my_own = ({});
int enter_alrm = 0;

void
create_krynn_monster()
{
    set_name("shawn");
    set_living_name("shawn");
    set_race_name("human");
    set_title("the Weapon Maker of Nethosak");
    set_gender(0);
    set_long("This is the weapon maker of Nethosak. He looks very experienced "+
	     "in the arts of making weapons. It is possible to order weapons "+
             "here, or collect a weapon, if you already have purchased one.\n");
    set_race_name("human");
    default_config_mobile(120);
    set_all_attack_unarmed(20, 60);
    set_all_hitloc_unarmed(60);
    set_skill(SS_WEP_CLUB, 100);
    set_alignment(100);

    set_introduce(1);
    set_act_time(14);
    add_act("emote hammers on a glowing piece of metal.");
    add_act("emote holds a glowing piece of metal into a barrel.");
    add_act("emote wipes the sweat from his brows.");
    add_act("emote hammers on a piece of metal.");

    set_default_answer("emote briefly looks at you before he points "+
        "at the sign with his hammer.");

}

void
arm_me()
{
    object ob;
    seteuid(getuid(TO));
    clone_object(MWEP + "hammer.c")->move(this_object(),1);
    remove_prop(NPC_M_NO_ACCEPT_GIVE);
    command("wear all");
    command("wield all");
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
    add_action("collect","collect");
    ::init_living();
}

int
collect(string str)
{
    object wep;
    if (alrm)
      {
	  command("say I'm already working on something, you'll have to "+
                  "until I'm finished.");
	  return 1;
      }
    command("say Ahh yes, you want to pick up the weapon you ordered?");
    command("say I'll go look for it right away.");
    command("emote leaves into the wagon.");
    command("emote arrives from the wagon.");
    command("emote smiles.");
    wep = stock[TP->query_real_name()];
    alrm = set_alarm(5.0,0.0,"give_out_weapon",TP->query_real_name(),
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
	case "steel":
	  m = 4;
	  break;
	case "tempered":
	  m = 5;
	  break;
	default: command("say I'm sorry, I didn't understand what material you wanted.");
	  m = 0;
      }

    switch(qual)
      {
	case "short":
	case "broad":
	  q = 6;
	  break;
	case "long":
	  q = 9;
	  break;
	case "serrated":
	  q = 9;
	  break;
	default: command("say I'm sorry, I didn't understand what blade you wanted.");
	  q = 0;
      }

    switch(typ)
      {
	case "dagger":   typ1 = W_KNIFE;
	                typ2 = W_IMPALE;
	                mod1 = 6;
	                mod2 = 0;
	                t = 1;
                        break;
	case "sword":   typ1 = W_SWORD;
	                typ2 = W_SLASH | W_IMPALE;
                        mod1 = 9;
	                mod2 = 8;
	                t = 1;
                        break;
	case "axe":     typ1 = W_AXE;
	                typ2 = W_BLUDGEON | W_SLASH;
	                mod1 = 9;
	                mod2 = 8;
	                t = 1;
                        break;
	case "hammer":  typ1 = W_CLUB;
	                typ2 = W_BLUDGEON;
	                mod1 = 3;
	                mod2 = 7;
	                t = 1;
	                break;
	default:        command("say I'm sorry, but I didn't understand what type of weapon you wanted.");
	                t = 0;
      }
    if (t && m && q)
      return ({ typ1, typ2, 4 + q * 2 + m + mod1,
		  4 + q * 2 + m + mod2, 60 });
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
	  command("say I'm sorry, but haven't got the money to pay for this weapon.");
	  command("say I'll keep the " + what_is_it + " here for you in stock.");
          command("say You can collect it later if you still want it.");
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
	case 3: typ = "dagger";
	        break;
	case 4: typ = "hammer";
	        break;
	default: typ = "weapon";
      }

    wep->remove_shadow();
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
	  command("say I'm very busy making a weapon. Please wait a while.");
	  return 1;
      }
    NF(C(query_verb()) + " what?\n");
    if (!str)
      return 0;
    if (stock[TP->query_real_name()])
      {
	  NF("There is already a weapon in stock for you! You have to " +
	     "collect it first.\n");
	  return 0;
      }

    /* syntax is: 'order <type> from <material> with <blade> blade' */
    c = sscanf(str, "%s from %s with %s blade", typ, mat, qual);
    NF(C(query_verb()) + " what from what material with which blade?\n");
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
	  if (ret_arr[4] > 60)
	    time_to_wait = "A weapon of that quality might take some time. "+
                           "You might aswell just come back later to 'collect' "+
                           "your weapon.";
	  else
	    time_to_wait = "This might take some time. You can either wait or "+
                           "come back later and 'collect' your order'.";
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
