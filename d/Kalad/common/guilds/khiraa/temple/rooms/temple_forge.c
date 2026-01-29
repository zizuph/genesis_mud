#include "/d/Kalad/defs.h"
#include "/d/Kalad/common/guilds/khiraa/khiraa_defs.h"
#pragma save_binary
#pragma strict_types

#define WAX_COST      5 /* Waxing costs 10% per point */
#define SHARPEN_COST 10 /* Sharpening as well */
#define AREPAIR_COST  5 /* Fixing armour */



inherit "/d/Kalad/room_std";
inherit "/lib/trade";

object vile;

int calc_repair_value(object ob);
int calc_wax_value(object ob);
int calc_sharpen_value(object ob);

void
create_room()
{
    set_short("In the forge room");
    
    set_long("\n   You have entered the only hot place in this normally "+
    "dark and cold temple. This is because of the blazing red furnace "+
    "at the far southeast corner of the room. Next to it, a large black "+
    "anvil rests, its smooth surface reflecting the red light of the "+
    "furnace. A stack of metal rests against another well, next to "+
    "a pile of leather and cloth.\n"+
    "   This is where the armour smith of the Khiraa works without "+
    "and and fatigue to construct and repair armours. A small pool "+
    "of water bubbles in a basin next to you.\n\n");

    add_item("furnace","The furnace is large and resembles a "+
    "well. Bright red light glows from within.\n");
    add_item("anvil","A black iron anvil, its smooth surface "+
    "reflecting the red light of the furnace.\n");
    add_item(({"stack","metal"}),"The metal used to construct "+
    "weapons and armour.\n");
    add_item(({"pile","cloth","leather"}),"This is also used to "+
    "construct armour.\n");
    add_item(({"pool","basin","water"}),"The water bubbles from the "+
    "heat of the hot metal that is at the bottom.\n");
    add_item("ceiling","The ceiling is made of solid black stone.\n");
    add_item("walls","The walls are made of dark black stone.\n");
    add_item("floor","The floor is of solid polished black marble.\n");
   
    INSIDE;
    add_prop(ROOM_I_LIGHT,1);
    clone_object(KHIRAA_DIR(temple/doors/forgedoor2))->move(TO); 
    vile = clone_object(KHIRAA_DIR(temple/obj/vile));
    vile->move_living("xxx",TO);
    config_default_trade();
    clone_object(KHIRAA_DIR(temple/obj/forge))->move(TO);
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
    if (!str || !(weapon = FIND_STR_IN_OBJECT(str,TP)) ||
        !sizeof(weapon))
        return 0;

    notify_fail("Be more specific. Which one?\n");
    if (sizeof(weapon) > 1)
        return 0;

    if(function_exists("create_object",weapon[0]) == "/std/armour")
    {
        v1 = calc_repair_value(weapon[0]);
        if(v1 == -1)
            vile->command("emote rumbles: I cannot repair that "+
            weapon[0]->short()+" further.");
        else
            vile->command("emote rumbles: To repair that "+
            weapon[0]->short()+", it would cost you "+v1+" coppers.");
        return 1;
    }

    notify_fail("That is not a weapon or armour.\n");
    if (function_exists("create_object",weapon[0]) != "/std/weapon")
        return 0;

    v1 = calc_sharpen_value(weapon[0]);
    v2 = calc_wax_value(weapon[0]);
    

    vile->command("emote rumbles: Sharpening that " + weapon[0]->short()+ " "
       + ((v1 == -1) ? "is not possible for me."
                     : ("would cost about "+v1+" coppers."))
       + "Waxing it "
       + ((v2 == -1) ? "is not possible for me."
                     : ("would cost about " + v2+ " coppers.")));
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
            vile->command("emote rumbles: I don't accept those " +
            pay_type + " coins, "+ TP->query_name() + ".");
            return 1;
        }
    }

    if (get_type != "")
    {
        if (member_array(get_type, MONEY_TYPES) < 0)
        {
            vile->command("emote rumbles: "+C((get_type)) + 
            " coins? Never heard of those.");
            return 1;
        }
    }

    notify_fail(capitalize(verb) + " what?\n");
    if (!(weapon = FIND_STR_IN_OBJECT(str,this_player())) ||
        !sizeof(weapon))
        return 0;

    notify_fail("Be more specific. Which one?\n");
    if (sizeof(weapon) > 1)
        return 0;

    notify_fail("That is not a weapon or armour.\n");
    if (function_exists("create_object",weapon[0]) != "/std/weapon" &&
        function_exists("create_object",weapon[0]) != "/std/armour")
        return 0;

    value = call_other(this_object(), "calc_"+verb+"_value", weapon[0]);

    notify_fail("Vile rumbles: I cannot " + verb + " that any further.\n");
    if (value == -1)
        return 0;

    /* Try to take the money */
    if (sizeof(money_arr = pay(value, tp, pay_type, 0, 0, get_type)) == 1)
    {
        if (money_arr[0] == 1)
        {
            vile->command("emote rumbles: You can't afford it.");
            return 1;
        }
        if (money_arr[0] == 2)
        {
            vile->command("emote rumbles: You don't have any "+
            pay_type+" coins."); 
            return 1;
        }
        else
        {
            vile->command("emote rumbles: You can't afford it.");         
            return 1;
        }
    }

    /* It is paid for, so let's fix the weapon */
    call_other(this_object(), "fix_"+verb, weapon[0]);

    write("You give "+vile->query_the_name(TP)+" the "+weapon[0]->short()+".\n");
    say(QCTNAME(TP) + " gives "+QTNAME(vile)+" "+HIS(TP) +
       " " + weapon[0]->short() + ".\n");

    tell_room(this_object(),
        QCTNAME(vile)+" "+verb + ((verb == "sharpen") ? "s" : "s") + " the "
      + weapon[0]->short() + ".\n"
      + QCTNAME(vile)+" gives the "+weapon[0]->short()+" back.\n");

    coin_pay_text = text(exclude_array(money_arr, sizeof(MONEY_TYPES),
                        sizeof(MONEY_TYPES)*2-1));
    coin_get_text = text(exclude_array(money_arr, 0, sizeof(MONEY_TYPES)-1));
    write("You pay " +coin_pay_text+ ".\n");
    if (coin_get_text)
        write("You get " + coin_get_text + " in return.\n");
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
calc_repair_value(object obj)
{
    if(obj->query_prop(OBJ_I_BROKEN))
        return -1;
    if(!F_LEGAL_ARMOUR_REPAIR(obj->query_repair()+1,obj->query_condition()))  
        return -1;
    return (obj->query_prop(OBJ_I_VALUE) * AREPAIR_COST) / 100;
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

