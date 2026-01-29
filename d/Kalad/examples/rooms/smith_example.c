/* An example of a smith who fixes weapons and armours.     */
/* Modified by Sarr from Unknown.                           */
/* 13.Apr.97       Kalad Example                            */
/* This smith room can fix weapons by sharpening them, or   */
/* wax them if corroded, or fix armours.                    */


#include "/d/Kalad/defs.h"
#pragma save_binary
#pragma strict_types

#define WAX_COST      5 /* Waxing costs 10% per point */
#define SHARPEN_COST 10 /* Sharpening as well */
#define AREPAIR_COST  5 /* Fixing armour */


inherit "/d/Kalad/room_std";
inherit "/lib/trade";

int calc_repair_value(object ob);
int calc_wax_value(object ob);
int calc_sharpen_value(object ob);


void
create_room()
{
    set_short("In the forge room");
    
    set_long("\n  You are in a small smith's room. There is "+
    "a large anvil next to a forge. It is very hot in here. A "+
    "sign on the wall has instructions.\n\n");
    
    add_item("sign","It can be read.\n");
    add_cmd_item("sign","read","In this smith you can do:\n"+
    "repair <armour>   -  Repair an armour \n"+
    "wax <weapon>      -  Wax a corroded weapon \n"+
    "sharpen <weapon>  -  Fix a damaged weapon \n"+
    "cost <item>       -  Determin how much it costs to repair, fix or wax an item\n"+
    "\n");
   
    INSIDE;

    config_default_trade();
}


void
init()
{
    ::init();
    add_action("do_fix","sharpen",0);
    add_action("do_fix","wax",0);
    add_action("do_cost","cost",0);
    add_action("do_fix","repair",0);
}

int
do_cost(string str)
{
    object *weapon;
    int v1, v2;

  
    notify_fail("Which weapon?\n");

    /* Find the armour or weapon. Variable is called weapon, although it */
    /* can be a weapon or armour. */

    if (!str || !(weapon = FIND_STR_IN_OBJECT(str,TP)) ||
        !sizeof(weapon))
        return 0;

    notify_fail("Be more specific. Which one?\n");
    if (sizeof(weapon) > 1)
        return 0;

    /* Is it an armour ? */
    if(function_exists("create_object",weapon[0]) == "/std/armour")
    {

        v1 = calc_repair_value(weapon[0]); // see if we can repair it

        if(v1 == -1) // we can't
            write("I cannot repair that "+
            weapon[0]->short()+" further.\n");
        else
            write("To repair that "+weapon[0]->short()+", it would cost "+
            "you "+v1+" coppers.\n");
        return 1;
    }

    /* Ok, if its not an armour, is it a weapon ? */
    notify_fail("That is not a weapon or armour.\n");
    if (function_exists("create_object",weapon[0]) != "/std/weapon")
        return 0;

    /* see if we can wax or repair it */

    v1 = calc_sharpen_value(weapon[0]);
    v2 = calc_wax_value(weapon[0]);
    

    write("Sharpening that " + weapon[0]->short()+ " "
       + ((v1 == -1) ? "is not possible for me.\n"
                     : ("would cost about "+v1+" coppers.\n"))
       + "Waxing it "
       + ((v2 == -1) ? "is not possible for me.\n"
                     : ("would cost about " + v2+ " coppers.\n")));
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

    /*   Check if the player defines what she wants to pay with
     *   and what you would like in return. */

    if (sscanf(str, "%s for %s and get %s",item_name,pay_type,get_type) != 3)
    {
        get_type = "";
        /* Hmmm... Maybe she only wishes to pay with a certain type */
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
            write("I don't accept those " +
            pay_type + " coins, "+ TP->query_name() + ".\n");
            return 1;
        }
    }

    if (get_type != "")
    {
        if (member_array(get_type, MONEY_TYPES) < 0)
        {
            write("emote rumbles: "+C((get_type)) + 
            " coins? Never heard of those.\n");
            return 1;
        }
    }

    /* Find the weapon or armour */

    notify_fail(capitalize(verb) + " what?\n");
    if (!(weapon = FIND_STR_IN_OBJECT(str,this_player())) ||
        !sizeof(weapon))
        return 0;

    notify_fail("Be more specific. Which one?\n");
    if (sizeof(weapon) > 1)
        return 0;

   /* is it a weapon or armour ? */
    notify_fail("That is not a weapon or armour.\n");
    if (function_exists("create_object",weapon[0]) != "/std/weapon" &&
        function_exists("create_object",weapon[0]) != "/std/armour")
        return 0;

   /* Call the appropriate function, depending on what the verb is */
   /* that the player called. If he wanted to 'sharpen', we would call */
   /* calc_sharpen_value, or if 'repair', calc_repair_value, or if     */
   /* 'wax', call calc_wax_value                                   */
    value = call_other(this_object(), "calc_"+verb+"_value", weapon[0]);

   /* Can we do what they ask ? */
    notify_fail("I cannot " + verb + " that any further.\n");
    if (value == -1)
        return 0;

    /* Try to take the money */
    if (sizeof(money_arr = pay(value, tp, pay_type, 0, 0, get_type)) == 1)
    {
        if (money_arr[0] == 1)
        {
            write("You can't afford it.\n");
            return 1;
        }
        if (money_arr[0] == 2)
        {
            write("You don't have any "+pay_type+" coins.\n"); 
            return 1;
        }
        else
        {
            write("You can't afford it.");         
            return 1;
        }
    }

    /* It is paid for, so let's fix the weapon */

    /* again, call the appropriate function depending on the verb */
    call_other(this_object(), "fix_"+verb, weapon[0]);

    write("You give the smith the "+weapon[0]->short()+".\n");
    say(QCTNAME(TP) + " gives the smith "+HIS(TP) +
       " " + weapon[0]->short() + ".\n");

    tell_room(this_object(),
        "The smith "+verb + ((verb == "sharpen") ? "s" : "s") + " the "
      + weapon[0]->short() + ".\n"
      + "The smith gives the "+weapon[0]->short()+" back.\n");

    coin_pay_text = text(exclude_array(money_arr, sizeof(MONEY_TYPES),
                        sizeof(MONEY_TYPES)*2-1));
    coin_get_text = text(exclude_array(money_arr, 0, sizeof(MONEY_TYPES)-1));
    write("You pay " +coin_pay_text+ ".\n");
    if (coin_get_text)
        write("You get " + coin_get_text + " in return.\n");
    return 1;
}

/* Can we wax the weapon? We have to check to see if the weapon is */
/* still within the legal bounds. Return -1 if not legal, the cost */
/* if it is.                     				   */

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

/* Can we repair the armour? We have to check to see if the armour */
/* is still within the legal bounds. Eventually the armour will    */
/* wear down to an unrepairable state. Return -1 if not lega, the  */
/* cost if it is. 						   */
int
calc_repair_value(object obj)
{
    if(obj->query_prop(OBJ_I_BROKEN))
        return -1;
    if(!F_LEGAL_ARMOUR_REPAIR(obj->query_repair()+1,obj->query_condition()))  
        return -1;
    return (obj->query_prop(OBJ_I_VALUE) * AREPAIR_COST) / 100;
}
/* Can we fix the weapon ? We have to check to see if the armour   */
/* is still within the legal bounds. Eventually the weapon will    */
/* wear down to an unrepairable state. Return -1 if not legal, the */
/* cost if it is. 						   */
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

/* Repair them by adding 1 to the repair factor */

void
fix_repair(object obj)
{
    obj->set_repair(obj->query_repair() + 1);
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

