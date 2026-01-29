// Bazaar Armoury (/d/Avenir/common/bazaar/armr.c)
// creator(s):   Triana 1994
// revisions:    Lilith Dec 97: added hilt-enchancement
//               Tepisch Nov 94
// purpose:      weapon repair               
// note:         heavily borrowed from the solamnic armoury
// bug(s):
// to-do:        

inherit "/std/room";
inherit "/lib/trade";

#include "/d/Avenir/common/bazaar/bazaar.h"
#include "/sys/cmdparse.h"
#include "/sys/language.h"
#include "/sys/formulas.h"
#include "/sys/money.h"
#include "/sys/stdproperties.h"
#include "/sys/ss_types.h"
#include "/sys/macros.h"

#define MEND_COST      75	
#define WAX_COST       15
#define SHARPEN_COST   15
#define ORNAMENT_COST  30

object iron1, tp, wep, gem;
int alarm_id;

/* prototypes */
int calc_sharpen_value(object obj);
int calc_wax_value(object obj);
int calc_mend_value(object obj);
int calc_ornament_value(object obj);
int distort(int price);
int do_finish(int value);
int do_cancel(string str);

void
create_room()
{
    set_short("Bazaar Island Forge");
    set_long("A very warm, dark room from the back of which an " +
        "intense heat radiates.  Metal glows red-gold upon the fire, " +
        "the only source of light.  The sighing of the bellows can be " +
        "heard between the clangs of the blacksmith's hammer upon the " +
        "anvil.  Here, a blacksmith and his apprentice toil to fix "+
        "weapons for adventurers who are in the area.\nA sign hangs "+
        "from the ceiling.\n");

    add_item(({"list","sign"}), "@@sign_long");
    add_item(({"forge","fire"}), "It throws flickering light upon "+
        "the walls.\n");  
    add_item(({"man","human","smith","blacksmith"}), 
        "Shrouded in shadow, all that you can make out clearly " +
        "are the muscles bulging upon his forearms as he pounds " +
        "his hammer against the anvil, and the sheen of sweat upon " +
        "his face.\n");
    add_item(({"apprentice", "boy"}), "He is a miniature version of " +
        "the blacksmith, facing the intense heat stoically.\n");
    add_item(({"walls", "wall"}), 
        "Shadows dance upon the walls which radiate an intense heat.\n");
    add_item(({"bellow", "bellows"}),
        "A hard-working apprentice mans the bellows, fanning the fire " +
        "hotter and hotter.\n");
    add_item("metal", "It glows red-gold in the fire.\n");
    add_item("hammer", "It is huge and very heavy-looking.\n");

    IN
    AE(EXTR + "str3", "east", 0);

    config_default_trade();
    set_money_give_max(100000);
    set_money_give_out(   ({ 10000,   700,  40,    1 }));
    set_money_give_reduce(({     0,     7,   4,    4 })); 
    set_money_greed_sell("@@favour");
    reset();
}

string
sign_long()
{
    return
          "Bazaar Forge Weapon Enhancement:\n"
        + "^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^\n"
        + "     Sharpen dull weapons\n"
        + "     Wax corroded weapons\n"
        + "     Ornament any weapon\n\n"
        + "All prices depend upon the value of the weapon.\n"
        + "Do \"cost <weapon>\" to see the cost for a service.\n\n"
        + "I will ornament the hilt or haft of any weapon.\n"
        + "Do \"ornament <weapon> with <gem>\".\n"
        + "\n";
}

int
do_read(string str)
{
    notify_fail("Read what?\n");
    if (str != "list" && str != "pricelist" &&
        str != "sign" && str != "little sign")
        return 0;

    write(sign_long());
    return 1;
}

void
reset_order()
{
    wep = 0;
    gem = 0;
    tp = 0; 
    alarm_id = 0;
}

int
do_cancel(string str)
{
    NF("Cancel what? Your order?\n");
    if (str != "order")
        return 0;

    if (TP != tp)
    {
        TP->catch_tell("You have no order to cancel!\n");
        return 1;
    }
    
    tp->catch_tell("Ok, "+ TP->query_race_name() +", I will cancel your "+
        "order.\n");
    remove_alarm(alarm_id);
    reset_order();
    return 1;
}

int
no_mend(string str)
{
   notify_fail("Mend what?\n");
   write("The blacksmith regrets to inform you that he is forbidden "+
          "from mending weapons and armours.\n");
   return 1;
}    

int
do_cost(string str)
{
   object *weapon, tp;
   int v1, v2, v3;

   tp = this_player();

   notify_fail("Which weapon?\n");
   if (!str || !(weapon = FIND_STR_IN_OBJECT(str,tp)) ||
       !sizeof(weapon))
      return 0;

   notify_fail("Be more specific. Which one?\n");
   if (sizeof(weapon) > 1)
      return 0;

   notify_fail("That is not really a weapon.\n");
   if (function_exists("create_object",weapon[0]) != "/std/weapon")
      return 0;

   v1 = calc_sharpen_value(weapon[0]);
   v2 = calc_wax_value(weapon[0]);
   v3 = calc_mend_value(weapon[0]);

   write("Sharpening that " + weapon[0]->short() + " "
       + ((v1 == -1) ? "is not necessary.\n"
                     : ("would cost about " + distort(v1) + " coppers.\n"))
       + "Waxing it "
       + ((v2 == -1) ? "is not necessary.\n"
                     : ("would cost about " + distort(v2) + " coppers.\n"))
       + "Mending it "
       + ((v3 == -1) ? "is not necessary.\n"
                     : ("would cost about " + distort(v3) + " coppers.\n")));
   return 1;
}

int
do_fix(string str)
{
   object *weapon, tp;
   int int_str, value, *money_arr;
   string item_name, pay_type, get_type, coin_pay_text, coin_get_text,
          verb;

   verb = query_verb();

   notify_fail(capitalize(verb) + " what?\n");
   if (!str)
      return 0;

   tp = this_player();

   if (sscanf(str, "%s for %s and get %s",item_name,pay_type,get_type) != 3)
   {
      get_type = "";
      if (sscanf(str, "%s for %s", item_name, pay_type) != 2)
      {
         pay_type = "";
         item_name = str;
      }
   }

   if (pay_type != "")
   {
      if (member_array(pay_type, MONEY_TYPES) < 0)
      {
         tell_room(this_object(), break_string(
            "The smith says: I don't accept those " + pay_type + " coins, "
          + tp->query_nonmet_name() + ".\n",70));
         return 1;
      }
   }

   if (get_type != "")
   {
      if (member_array(get_type, MONEY_TYPES) < 0)
      {
         tell_room(this_object(), break_string(
            "The smith says: " + capitalize(get_type) + " coins? Never "
          + "heard of those. You must be a surface-dweller.\n",70));
         return 1;
      }
   }

   notify_fail("Mend what?\n");
   if (!(weapon = FIND_STR_IN_OBJECT(str,this_player())) ||
       !sizeof(weapon))
      return 0;

   notify_fail("Be more specific. Which one?\n");
   if (sizeof(weapon) > 1)
      return 0;

   notify_fail("That is not really a weapon.\n");
   if (function_exists("create_object",weapon[0]) != "/std/weapon")
      return 0;

   value = call_other(this_object(), "calc_"+verb+"_value", weapon[0]);

   notify_fail("The smith says: I cannot " + verb + " that any further.\n");
   if (value == -1)
      return 0;

   if (sizeof(money_arr = pay(value, tp, pay_type, 0, 0, get_type)) == 1)
   {
      if (money_arr[0] == 1)
      {
         tell_room(this_object(), break_string(
            "The smith says: I think that " + weapon[0]->short() + 
            " is a bit "+ "more expensive, " + tp->query_nonmet_name() +
            ".\n",70));
         return 1;
      }
      if (money_arr[0] == 2)
      {
         tell_room(this_object(), break_string(
            "The smith says: You do not have any " + pay_type + " coins, "
          + tp->query_nonmet_name() + ".\n",70));
         return 1;
      }
      else
      {
         tell_room(this_object(), "The smith says: I think that "+ 
          weapon[0]->short() + " is a bit "
          + "too expensive for you, " + tp->query_nonmet_name() + ".\n");
         return 1;
      }
   }

   value = call_other(this_object(), "fix_"+verb, weapon[0]);

   write("You give the smith the " + weapon[0]->short() + ".\n");
   say(QCTNAME(tp) + " gives the smith " + tp->query_possessive() +
       " " + weapon[0]->short() + ".\n");

   tell_room(this_object(),
        "The smith " + verb + ((verb == "sharpen") ? "s" : "es") + " the "
      + weapon[0]->short() + ".\n"
      + "The smith gives the weapon back.\n");

   coin_pay_text = text(exclude_array(money_arr, sizeof(MONEY_TYPES), 
			sizeof(MONEY_TYPES)*2-1));
   coin_get_text = text(exclude_array(money_arr, 0, sizeof(MONEY_TYPES)-1));
   write("You pay the smith " +coin_pay_text+ ".\n");
   if (coin_get_text)
      write("You get " + coin_get_text + " in return.\n");

   return 1;
}

int
do_ornament(string str)
{
    object *weapons, *gems;
    string wep_name, gem_name, verb;
    int value;

    verb = query_verb();
    notify_fail(capitalize(verb) + " <weapon> with <gem>?\n");
    if (!str)
        return 0;

    notify_fail("I'm doing work for someone else. You'll have to "+
        "wait a minute.\n");
    if (tp || alarm_id)
        return 0;
        
    sscanf(str, "%s with %s", wep_name, gem_name);
    if (!strlen(wep_name))
    {
        notify_fail("You need to specify which weapon you want "+
            "ornamented.\n");
        return 0;
    }   
    if (!strlen(gem_name))
    {
        notify_fail("Please use: ornament <weapon> with <gem>.\n");
        return 0;
    }
    if (!(weapons = FIND_STR_IN_OBJECT(wep_name, this_player())) ||
        !sizeof(weapons))
    {
        notify_fail("Specify which weapon you want ornamented.\n");
        return 0;
    }
    if (sizeof(weapons) > 1)
    {
        notify_fail("Be more specific. Which weapon?\n");
        return 0;
    }
    if (function_exists("create_object", weapons[0]) != "/std/weapon")
    {
        notify_fail("That is not really a weapon.\n");
        return 0;
    }

    if (!(gems = FIND_STR_IN_OBJECT(gem_name, this_player())) ||
        !sizeof(gems))
    {
        notify_fail("Specify gem uou want to ornament your "+ 
            "weapon with.\n");
        return 0;
    }
    if (sizeof(gems) > 1)
    {
        notify_fail("Be more specific. Which gem?\n");
        return 0;
    }

    tp = this_player();
    wep = weapons[0];
    gem = gems[0];
    if (gem->query_prop(MAGIC_AM_MAGIC))
    {
        /* So we don't use the zodiac gem or other quest items */ 
        notify_fail("I can't use "+ LANG_THESHORT(gem) +" for "+
            "ornamentation. Sorry.\n");
        return 0;
    }
    value = call_other(this_object(), "calc_ornament_value", wep);
    tp->catch_tell("I will ornament your "+ wep->short() +
        " with "+ LANG_THESHORT(gem) +". It will cost you "+ value +
        " cc.\n");
    tp->catch_tell("I will begin work now. You have one minute to "+
        "<cancel order> if this is not satisfactory.\n");
    alarm_id = set_alarm(60.0, 0.0, &do_finish(value));
    return 1;
}    
   
int
do_finish(int value)
{
    string gLong, gShort, wShort, wLong;
    int *result;

    if (!present(tp))
    {
        reset_order();
        return 0;
    }

    result = pay(value, tp);
    if (sizeof(result) == 1)
    {
        tp->catch_tell("You don't have enough money! Cancelling "+
            "your order.\n");       
        reset_order();       
        return 0;
    }

    say(QCTNAME(TP) + " pays for "+ POSSESS(TP) +" order.\n");
    write("You pay for your order.\n");

    if (gem->query_gem_type())
        gShort = gem->query_gem_type();
    else
        gShort = gem->query_short();       
    gLong = gem->query_long();

    /* Lets deal with heaps here */
    if (gem->num_heap() > 1)
        gem->set_heap_size((gem->num_heap()) - 1);
    else
        gem->remove_object();

    tp->catch_tell("The smith takes your "+ gShort +" and fits "+
        "it into the setting he prepared on your "+ wep->short() +".\n");

    switch(wep->query_wt())
    {
        case W_SWORD:   wShort = "sword";    break;
        case W_POLEARM: wShort = "polearm";  break;
        case W_AXE:     wShort = "axe";      break;
        case W_KNIFE:   wShort = "knife";    break;    
        case W_CLUB:     wShort = "club";     break;
    }
    if (wShort == "knife" || wShort == "sword")
        wLong = "hilt";
    else
        wLong = "haft";

    wep->set_short(gShort +" encrusted "+ wShort);
    wep->set_long(wep->query_long() +"   The "+ wLong +" of this "+ wShort +
        " has been fitted with a "+ gShort +" of the highest "+
        "quality. The setting is both elaborate and of remarkable "+
        "craftsmanship.\n");
    wep->add_adj(gShort);
    wep->add_item(gShort, gLong);
    wep->add_item("setting", "It is both elaborate and of remarkable "+
        "craftsmanship, with a "+ gShort +" at the center.\n");

    tp->catch_tell("The smith presents you with a "+ wep->short() +".\n");
    reset_order();
    return 1;
}

int
calc_wax_value(object obj)
{
   if (obj->query_prop(OBJ_I_BROKEN))
      return -1;

   if (!F_LEGAL_WEAPON_REPAIR_CORR(obj->query_repair_corr()+1,
                                  obj->query_corroded()))
      return -1;
   return (obj->query_prop(OBJ_I_VALUE) * WAX_COST) / 100;
}

int
calc_sharpen_value(object obj)
{
   if (obj->query_prop(OBJ_I_BROKEN))
      return -1;

   if (!F_LEGAL_WEAPON_REPAIR_DULL(obj->query_repair_dull()+1,
                                  obj->query_dull()))
      return -1;
   return (obj->query_prop(OBJ_I_VALUE) * SHARPEN_COST) / 100;
}

int 
calc_mend_value(object obj)
{
   if (!(obj->query_prop(OBJ_I_BROKEN)))
      return -1;
   return (F_VALUE_WEAPON(obj->query_pen(), obj->query_hit()) * MEND_COST)/100;
}

int
calc_ornament_value(object obj)
{
   return (obj->query_prop(OBJ_I_VALUE) * ORNAMENT_COST) / 100;
}

void
fix_wax(object obj)
{
   obj->set_repair_corr(obj->query_repair_corr() + 1);
}

void 
fix_sharpen(object obj)
{
   obj->set_repair_dull(obj->query_repair_dull() + 1);
}

void
fix_mend(object obj)
{
   obj->remove_prop(OBJ_I_BROKEN);
}

#define F_RANGE_RANDOM(orig, max, min, value) \
       ((orig) - (orig)*((min)*100 + ((max)-(min)) * (100-(value)))/10000  \
     + random(2*(orig)*((min)*100 + ((max)-(min)) * (100-(value))) / 10000))

int
distort(int price)
{
   int trading;

   trading = this_player()->query_skill(SS_TRADING);
   if (trading < 10)
      trading = 10;
   if (trading > 100)
      trading = 100;

    return F_RANGE_RANDOM(price, 30, 2, trading);
}

int
favour()
{
    string race;
    race = this_player()->query_race();
    
    /* This is a servant of the Shadow Elves, thus elves do well; and 
       humans are treated fairly because the smith is human  */
    if (race == "elf")
        return 90;
    if (race == "human")
        return 100;
    return 115;
}

void
reset_room()
{
    if (!present("iron"))
    {
        iron1 = clone_object(BAZAAR + "Obj/misc/iron.c");
        iron1->move(this_object());
    }
}

void
init()
{
    ::init();
    add_action(no_mend, "mend",0);
    add_action(do_fix,"sharpen",0);
    add_action(do_fix,"wax",0);
    add_action(do_read,"read",0);
    add_action(do_cost,"cost",0);
    add_action(do_cancel, "cancel", 0);
    add_action(do_ornament, "ornament", 0);
}
