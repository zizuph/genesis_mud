#pragma strict_types

#include <macros.h>
#include <money.h>
#include <cmdparse.h>
#include <formulas.h>

inherit "/lib/trade";

object gSmith;
int gSmithSet = 0;
int gWaxPrice =  60;
int gMendPrice = 80;
int gSharPrice = 60;

void
SmithSpeak(string text)
{
    if(objectp(gSmith))
    {
        gSmith->command("say "+text);
    }
    else
    {
        write(text+"\n");
    }
}

void
set_smith(object ob)
{
    gSmith = ob;
    gSmithSet = 1;
}

void
set_sharp_price(int i)
{
   if(i < 1 || i > 100)
        return;

   gSharPrice = i;
}

void
set_wax_price(int i)
{
    if(i < 1 || i > 100)
        return;
    gWaxPrice = i;
}

void
set_mend_price(int i)
{
    if(i < 1 || i > 100)
        return;
    gMendPrice = i;
}

int
calc_wax_value(object obj)
{
   if (obj->query_prop(OBJ_I_BROKEN))
      return -1;

   if (!F_LEGAL_WEAPON_REPAIR_CORR(obj->query_repair_corr()+1,
                                  obj->query_corroded()))
      return -1;
   return (obj->query_prop(OBJ_I_VALUE) * gWaxPrice) / 100;
}

int
calc_sharpen_value(object obj)
{
   if (obj->query_prop(OBJ_I_BROKEN))
      return -1;

   if (!F_LEGAL_WEAPON_REPAIR_DULL(obj->query_repair_dull()+1,
                                  obj->query_dull()))
      return -1;
   return (obj->query_prop(OBJ_I_VALUE) * gSharPrice) / 100;
}

int
calc_mend_value(object obj)
{
   if (obj->query_prop(OBJ_I_BROKEN))
      return -1;

   if (!F_LEGAL_ARMOUR_REPAIR(obj->query_repair()+1,
                                  obj->query_condition()))
      return -1;

   return (obj->query_prop(OBJ_I_VALUE) * gMendPrice) / 100;
}

int
FailIt(string verb)
{
    SmithSpeak("I cannot "+verb+" that any further.");
    return 1;
}


int
Payed(object tp, int cost)
{
    int *money_arr;
    string coin_pay_text, coin_get_text;

    if(sizeof(money_arr = pay(cost, tp, "", 0, 0, "")) == 1)
    {
        if(money_arr[0] >= 1)
        {
            SmithSpeak("Come back when you get the money.");
            return 0;
        }

        tell_object(tp,"Something went wrong.");
        return 0;
    }

    coin_pay_text = text(exclude_array(money_arr, sizeof(MONEY_TYPES),
                        sizeof(MONEY_TYPES)*2-1));
    coin_get_text = text(exclude_array(money_arr, 0, sizeof(MONEY_TYPES)-1));

    tell_object(tp,"You pay the smith " +coin_pay_text+ ".\n");

    if (coin_get_text)
        tell_object(tp,"You get " + coin_get_text + " in return.\n");

    return 1;
}

void
FixIt(object tp, object item, string verb, function fixit)
{
    tell_object(tp,"You give the smith the " + item->short() + ".\n");

    say(QCTNAME(tp) + " gives the smith " + tp->query_possessive() +
       " " + item->short() + ".\n");

    fixit(item);

    tell_object(tp, "The smith " + ((verb == "wax") ? "waxes"
                     : (verb+"s"))
       + " the "+item->short()+".\nThe smith then gives it back.\n");
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
   obj->set_repair(obj->query_repair() + 1);
}

int
do_fix(string str)
{
    object *items, tp;
    int int_str, value;
    string item_name, pay_type, get_type, verb;

    verb = query_verb();

    notify_fail(capitalize(verb) + " what?\n");

    if (!str)
       return 0;

    tp = this_player();

    if (gSmithSet && !(present(gSmith, environment(tp))))
    {
        notify_fail("The smith isn't here.\n");
        return 0;
    }

    if( !sizeof(items = FIND_STR_IN_OBJECT(str,tp)))
        return 0;

    notify_fail("Be more specific. Which one?\n");

    if (sizeof(items) > 1)
        return 0;

    if (function_exists("create_object",items[0]) != "/std/weapon" && 
        function_exists("create_object",items[0]) != "/std/armour")
    {
        SmithSpeak("I can only work on weapons and armours.");
        return 1;
    }

    if(verb == "sharpen")
    { 
        value = calc_sharpen_value(items[0]);
        if (value == -1)
            return FailIt(verb);

        if(Payed(tp,value))
        {
            FixIt(tp,items[0],verb, fix_sharpen);
        }
        else
            return 1;
    }
    if(verb == "wax")
    {
        value = calc_wax_value(items[0]);
        if (value == -1)
            return FailIt(verb);

        if(Payed(tp,value))
        {
            FixIt(tp,items[0],verb, fix_wax);
        }
        else
            return 1;
    }
    if(verb == "mend")
    {
        value = calc_mend_value(items[0]);
        if (value == -1)
            return FailIt(verb);

        if(Payed(tp,value))
        {
            FixIt(tp,items[0],verb, fix_mend);
        }
        else
            return 1;
    }

    SmithSpeak("Thank you for your business.");

    return 1;
}


int
do_cost(string str)
{
    object *items, tp;
    int v1, v2;

    tp = this_player();

    if (gSmithSet && !present(gSmith, environment(tp)))
    {
        notify_fail("The smith isn't here.\n");
        return 0;
    }

    notify_fail("Cost what?\n");

    if(!str || !sizeof(items = FIND_STR_IN_OBJECT(str,tp)) )
        return 0;

    if (sizeof(items) > 1)
    {
        SmithSpeak("Be more specific. Which one?");
        return 1;
    }

    if(function_exists("create_object",items[0]) == "/std/weapon")
    {
        v1 = calc_sharpen_value(items[0]);
        v2 = calc_wax_value(items[0]);

        SmithSpeak("Sharpening that " + items[0]->short() + " "
        + ((v1 == -1) ? "is not necessary."
                     : ("would cost " +v1+ " coppers."))
        + " Waxing it "
        + ((v2 == -1) ? "is not necessary."
                     : ("would cost " +v2+ " coppers.")));
        return 1;
    }

    if (function_exists("create_object",items[0]) == "/std/armour")
    {
        v1 = calc_mend_value(items[0]);

        SmithSpeak("Mending that " + items[0]->short() + " "
        + ((v1 == -1) ? "is not necessary."
                     : ("would cost " +v1+ " coppers.")));
        return 1;
    }

    SmithSpeak("I only work on weapons and armours.");

    return 1;  
}

void
init_smith()
{
    add_action(do_fix,"sharpen",0);
    add_action(do_fix,"wax",0);
    add_action(do_fix,"mend",0);
    add_action(do_cost,"cost",0);
    config_default_trade();
}
