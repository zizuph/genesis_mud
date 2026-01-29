/*  
*  Theros Ironfeld
*  Created By Leia
*  June 06, 2005
*/

/*
** Last Updated By:
** Leia
** July 1, 2005
*/

/* Added add_prop(OBJ_M_NO_ATTACK, 1)
 * since the smith is no longer a peace room.
 * Added the ability to fix armours, based on /d/Calia/gelan/monsters/bubba.c
 *
 */

/*
 * Added commerce support for warfare area.
 * Arman Sep 4, 2018
 */

#pragma save_binary

#include "/d/Krynn/common/defs.h"
#include "/d/Krynn/clubs/warfare/defs.h"
#include "/d/Krynn/solace/new_village/town_square/local.h"

inherit "/lib/trade";
inherit "/std/act/action";

inherit "/sys/global/money";
inherit M_FILE /* The Krynn humanoid monster file */
inherit "/d/Genesis/lib/commerce"; 
  
static string *gIntroducedTo = ({}); 

#include <stdproperties.h>
#include <ss_types.h>
#include <macros.h>
#include <formulas.h>
#include <wa_types.h>
#include <const.h>
#include <money.h>
#include <cmdparse.h>
#include <language.h>
#include <composite.h>
#include <files.h>

#define LOW(x) lower_case(x)
#define CAP(x) capitalize(x)

#define AWAITING_CUSTOMER 0

#define NOTHING 0
#define CONFIRMATION 1
#define CARRYING_OUT 2

int state; /* Current state of the blacksmith e.g. AWAITING_CUSTOMER */
int stage; /* Current stage of blacksmith in stage e.g. CARRYING_OUT */

string *known = ({ });

string customer; /* The current customer being worked for */
string working_on; /* Descr of the object being worked on */
int price; /* price on copper of the thing currently being worked on */
int *mw_price = ({ });
object finished_item;

int confirmation_alarm;
int commission_alarm = 0;

string query_npc_address_name(object player, string t);
void end_waiting();
void say_busy(object player);

#include "/d/Krynn/solace/new_village/town_square/npcs/repairs.c"

mixed *fixing;
int testing;

void
preload_commodities(string *commod)
{
    /* Currently we never preload the commodities */
    if(1) return;
    this_object()->hook_commerce_amount_update(commod[0], 0);
    set_alarm(0.5, 0.0, &preload_commodities(commod[1..]));
}

public void
remove_object()
{
    remove_commerce();

    ::remove_object();
}

/* Address player according to whether player has introd before */
string
query_npc_address_name(object player, string t)
{
    string s;

    if (member_array(player->query_real_name(), known) > -1)
        s = player->query_name();
    else 
        s = t + player->query_nonmet_name(); 

    return s;
}

/*
 * Function name : hook_commerce_buy_cannot_afford
 * Description   : notify that player doesnt have the needed money
 * Arguments     : object  - item player cannot afford
 *                 int     - the quantity of item he tried to buy
 * Returns       : int     - 0 for nofity_fail or 1 for the rest
 */
public int
hook_commerce_buy_cannot_afford(object commod, int amount)
{
    command("frown");
    command("say You are short on gold! The steel " +
        "coins are my commission, the gold price is for the materials.");       
    command("say You cannot afford " + (amount == 1 ?
        LANG_THESHORT(commod) : (LANG_WNUM(amount) + " " +
        LANG_PWORD(LANG_THESHORT(commod)))) + ".");
    command("say Come back when you have more coins on you... i'll " +
        "keep hold of your commissioning until then.");
    return 1;
}

/*
 * Function name : hook_commerce_buy_prevent_buy
 * Description   : function is the last validator in the chain of buy
 *                 validators, when it returns false specified commodity
 *                 would be bought for sure, and when it returns 1 it
 *                 would not, this hook must generate it's own messages
 *                 when returning true
 * Arguments     : object  - the master object of commodity player buys
 *                 int     - the quantity of item he tries to buy
 * Returns       : int     - 1 when buy is prevented or 0 otherwise
 */
public int
hook_commerce_buy_prevent_buy(object commod, int amount)
{
    int value;
    if (!IS_CLUB_MEMBER(TP))
    {
        command("say I only buy that sort of stuff from those " +
            "participating in the war for Krynn!");
        return 1;
    }

    return 0;
}

/*
 * Function name : appeal
 * Description   : the appeal of commerce module to a player, this hook
 *                 is supposed to open new oportunities in hooks masking
 *                 if your commercant is a goblin and he hates dwarves
 *                 badly, you could mask this hook to return "filthy
 *                 dwarven creature" for each dwarf, thus totally changing
 *                 commercant's behaviour
 * Arguments     : object  - the player commersant appeals to
 * Returns       : string  - the appeal string
 */
public varargs string
appeal(object player = this_player())
{
    string s;

    if (member_array(player->query_real_name(), known) > -1)
        s = player->query_name();
    else 
        s = player->query_nonmet_name();

    return s;
}

/*
 * Function name : hook_commerce_sell_prevent_sell
 * Description   : function is the last validator in the chain of sell
 *                 validators, when it returns false specified commodity
 *                 would be sold for sure, and when it returns 1 it
 *                 would not, this hook must generate it's own messages
 *                 when returning true (please do not destruct or split
 *                 the passed object, p.s. parsing macros split heaps)
 * Arguments     : object  - the commodity object player sells
 * Returns       : int     - 1 when sell is prevented or 0 otherwise
 */
public int
hook_commerce_sell_prevent_sell(object commod)
{
    int value;
 
    if (!IS_CLUB_MEMBER(TP))
    {
        command("say I only sell that sort of stuff to those " +
            "participating in the war for Krynn!");
        return 1;
    }
    return 0;
}

/*
 * Function name : hook_commerce_buy_faulty_amount
 * Description   : called when player tries to buy more than in stock
 * Arguments     : object  - the commodity player tries to buy
 *                 int     - the quantity player tries to buy
 *                 int     - the quantity of commodity in stock
 * Returns       : int     - 0 for nofity_fail or 1 for the rest
 */
public int
hook_commerce_buy_faulty_amount(object commod, int amount, int in_stock)
{
    if (!living(this_object()))
    {
        if (!in_stock)
        {
            write("There are no " + commod->plural_short() +
                " currently for sale.\n");
           return 1;
        }

        write("There " + (in_stock == 1 ? "is " : "are ") +
            LANG_WNUM(in_stock) + " " + (in_stock == 1 ? commod->short() :
            commod->plural_short()) + " only available for sale currently.\n");

        return 1;
    }

    if (!in_stock && TP->query_prop(MASTERWORK_PROP))
    {
        command("say I am still working on " +commod->plural_short() + 
            ", it will be ready in a moment.");
        return 1;
    }
    
    if (!in_stock)
    {
        command("say I don't have " + commod->plural_short() + 
            " for sale at the moment.");
        return 1;
    }

    command("say I have only " + LANG_WNUM(in_stock) + " " +
        (in_stock == 1 ? commod->short() : commod->plural_short()) +
        " for sale.");
 
    return 1;
}

string
query_army_equip_type(object player)
{
    string wfarmy = CLUB_MANAGER->query_warfare_army(player);

    if(player->query_guild_member("Priests of Takhisis"))
        return "pot";

    switch (wfarmy)
    {
        case "Knights":
            return "knights";
            break;
        case "Neidar Clan":
            return "neidar";
            break;
        case "Free People":
            if(player->query_race_name() == "elf")
                return "qualinesti";
            else
                return "free";
            break;
        case "Red Dragon Army":
            return "red";
            break;
        case "Blue Dragon Army":
            return "blue";
            break;
        case "Black Dragon Army":
            return "black";
            break;
        case "Green Dragon Army":
            return "green";
            break;
        case "White Dragon Army":
            return "white";
            break;
        default:
            return "free";
    }
}

/*
 * Function name : hook_commerce_buy_notify_finish
 * Description   : deliver the items from stock to the player
 * Arguments     : object* - items player bought
 *                 int*    - array of coins payed by the player
 *                 int*    - array of change player got
 * Returns       : int     - 0 for nofity_fail or 1 for the rest
 */
public int 
hook_commerce_buy_notify_finish(object *oblist, int *charge, int *change)
{
    int     number = -1, amount = sizeof(oblist);
    string  result, army;

    if (!living(this_object()))
    {
        write("You pay " + text(charge) + " for " +
            COMPOSITE_DEAD(oblist) + ".\n");
        if (strlen(result = text(change)))
        {
            write("You get " + result + " back.\n");
        }
        oblist = filter(oblist, &->move(this_player()));

        if (sizeof(oblist))
        {
            write("You drop " + COMPOSITE_DEAD(oblist) + ".\n");
            oblist->move(environment(this_player()));
        }

        return 1;
    }

    write("You pay " + this_object()->query_the_name(this_player()) +
        " " + text(charge) + ".\n");

    say(QCTNAME(this_player()) + " hands some coins to " +
        QTNAME(this_object()) + ".\n");

    if (strlen(result = text(change)))
    {
        write("You get " + result + " back.\n");
        say(QCTNAME(this_object()) + " gives some change back to " +
            QTNAME(this_player()) + ".\n");
    }

    oblist->move(this_object(), 1);
    army = CLUB_MANAGER->query_warfare_army(this_player());

    while (++number < amount)
    {
        string wfarmy = query_army_equip_type(this_player());
        string old_desc = oblist[number]->short();

        if(oblist[number]->query_krynn_warfare_armour())
        {
            oblist[number]->set_armour_faction(wfarmy);
            oblist[number]->update_warfare_armour();
        }
        else if(oblist[number]->query_krynn_warfare_wand())
        {
            oblist[number]->set_wand_faction(wfarmy);
            oblist[number]->update_warfare_wand();
        }
        else
        {
            oblist[number]->set_weapon_faction(wfarmy);
            oblist[number]->update_warfare_weapon();
        }

        if(old_desc != oblist[number]->short())
            command("say I customised it from " +
                LANG_ADDART(old_desc)+ " to " + 
                LANG_ADDART(oblist[number]->short()) + ".");
        command("give " + OB_NAME(oblist[number]) + " to " +
            OB_NAME(this_player()));
        if (environment(oblist[number]) == this_object())
        {
            command("frown");
            command("say You don't seem able to carry " +
                LANG_THESHORT(oblist[number]) + ", " + appeal() + ".");
            command("put " + OB_NAME(oblist[number]));
            while (++number < amount)
            {
                command("put " + OB_NAME(oblist[number]));
            }
        }
    }

    TP->remove_prop(MASTERWORK_PROP);

    return 1;
}

/*
 * Function name : action_commerce_buy
 * Description   : function handles attempts to buy from commerce object
 * Arguments     : string  - argument writen by the player
 * Returns       : int     - 1 for success , 0 for failure
 */
public int
action_commerce_buy(string cmdarg)
{
    mixed commod;
    string coname;
    int stocka, maxcap, number;
    int amount = 1;
    float costfa;
    mixed cost = 1.0;

    if(!TP->query_prop(MASTERWORK_PROP))
    {
        say(QCTNAME(TP)+ " asks Theros something.\n");
        command("say You need to commission my services if " +
            "you want to buy my masterwork equipment. And that " +
            "commission needs to paid with steel coins!");
        command("ponder");
        return 1;
    }

    setuid(); seteuid(getuid());
    commod = map(query_supplied_commodity(), find_commodity);

    if (!sizeof(commod = FIND_STR_IN_ARR(cmdarg, commod)))
    {
        return hook_commerce_buy_faulty_syntax(cmdarg);
    }

    commod = commod[0];
    coname = commod->query_commodity_name();

        if (TP->query_prop(MASTERWORK_PROP) != coname)
        {
            string comname = 
                find_commodity(TP->query_prop(MASTERWORK_PROP))->short();

            say(QCTNAME(TP)+ " asks Theros to buy " +
                LANG_ADDART(cmdarg)+ ".\n");
            command("say You haven't commissioned a " +
                LANG_ADDART(cmdarg)+ "! " +
                "You commissioned a " +comname+ "!");
            command("ponder");
            return 1;
        }
        else
        {
            if (!(stocka = query_commodity_amount(coname)) || 
                (amount > stocka))
            {
                command("say Give me a few moments, I am still " +
                "working on it!");
                command("emote turns back to his forging.");
                return 1;
            }
           
            ::action_commerce_buy(cmdarg);
            return 1;
        }

    ::action_commerce_buy(cmdarg);
    return 1;
}

/* Clear customer details */
void
clear_customer()
{
    customer = "";
    working_on = "";
    price = 0;
    state = AWAITING_CUSTOMER;
    stage = NOTHING;
}


/* End waiting for a confirmation/cancellation */
void
end_waiting()
{
    remove_alarm(confirmation_alarm);
    confirmation_alarm = 0;
    clear_customer();
    command("rolleyes");
    command("say Ok, next please.");
}


void
player_left(string player_name)
{
   if ((player_name == customer) && (stage == CONFIRMATION)) 
       end_waiting();
}


/* Blacksmith tells someone that he's busy right now */
void
say_busy(object player)
{
    if (!living(player))
        return;
    command("say I'm busy at the moment, " + 
            query_npc_address_name(player, "") +
            ", can't you tell that just by looking at me?");
}

void
update_comm()
{
    update_commerce();
    // CLUB_DEBUG("Update comm called.");
}

void
create_krynn_monster()
{
    int i;

    set_name("theros");
    add_name("smith");
    set_living_name("theros");
    set_race_name("human");
    set_title("Ironfeld, Solace Smith and Master Craftsman");
    set_adj("huge");
    add_adj("black-skinned");
    set_long("This smith is hard at work. The concentration on his " +
        "face is quite obvious, as he scrunches it up while he " +
        "works. With each swing of the hammer, his muscles bulge. " +
        "He seems not to notice your presence. This isn't surprising " +
        "with the noise in this shop.\n");
    set_gender(G_MALE);
    add_prop(NPC_I_NO_LOOKS, 1);
    set_introduce(1);
    add_prop(CONT_I_HEIGHT, 220);
    add_prop(CONT_I_WEIGHT, 72000);
    add_prop(CONT_I_VOLUME, 60000);

    // Add commerce support
    set_commerce_savefile("/d/Krynn/common/commerce/theros_data");
    config_default_trade();

/*
    "Call /d/Krynn/domain_link preload_link" each time new 
    commodity items are added.

    Just be aware it may duplicate ship captains at 
    /d/Krynn/solamn/eplains/rooms/eplain-4-21-V , so make sure
    you remove any additional ship captains spawned!
*/

    // Name, consume span (minutes), max capacity, cost factor
    add_demanded_commodity("iron bar", 2, 250, 1.0);
    set_commodity_amount("iron bar", 250);
    set_commodity_reserve("iron bar", 0);

    add_demanded_commodity("carbon bar", 3, 60, 1.0);
    set_commodity_amount("carbon bar", 100);
    set_commodity_reserve("carbon bar", 0); 

    add_demanded_commodity("carbonpiece", 10, 60, 1.0);
    set_commodity_amount("carbonpiece", 100);
    set_commodity_reserve("carbonpiece", 0);

    add_demanded_commodity("silver bar", 4, 200, 1.0);
    set_commodity_amount("silver bar", 200);
    set_commodity_reserve("silver bar", 0);

    add_demanded_commodity("goldpiece", 11, 100, 1.5);
    set_commodity_amount("goldpiece", 100);
    set_commodity_reserve("goldpiece", 0);

    add_demanded_commodity("silverpiece", 10, 100, 1.5);
    set_commodity_amount("silverpiece", 10);
    set_commodity_reserve("silverpiece", 0);

    add_demanded_commodity("carbonpiece", 6, 100, 1.5);
    set_commodity_amount("carbonpiece", 10);
    set_commodity_reserve("carbonpiece", 0);

    add_demanded_commodity("ironpiece", 5, 100, 1.5);
    set_commodity_amount("ironpiece", 10);
    set_commodity_reserve("ironpiece", 0);

    add_demanded_commodity("leather scrap", 6, 100, 1.5);
    set_commodity_amount("leather scrap", 250);
    set_commodity_reserve("leather scrap", 250);

    // name, increase span (minutes), max capacity, cost factor
    add_supplied_commodity ("gold bar", 6, 250, 0.2);
    add_supply_requirement("gold bar", ({"goldpiece", 2 }) );

    add_supplied_commodity ("silver bar", 5, 250, 0.2);
    add_supply_requirement("silver bar", ({"silverpiece", 2 }) );

    add_supplied_commodity ("carbon bar", 4, 250, 0.2);
    add_supply_requirement("carbon bar", ({"carbonpiece", 2 }) );

    add_supplied_commodity ("iron bar", 3, 250, 0.2);
    set_commodity_priority("iron bar", 1);
    add_supply_requirement("iron bar", ({"ironpiece", 2 }) );

    add_supplied_commodity("mw platemail", 0, 25, 5.0);
    set_commodity_amount("mw platemail", 0);
    set_commodity_reserve("mw platemail", 0);
    set_commodity_priority("mw platemail", 0);
    add_supply_requirement("mw platemail",
        ({ "silver bar", 1, "iron bar", 10, "carbon bar", 1 }) );

    add_supplied_commodity("mw chainmail", 0, 25, 5.0);
    set_commodity_amount("mw chainmail", 0);
    set_commodity_reserve("mw chainmail", 0);
    set_commodity_priority("mw chainmail", 0);
    add_supply_requirement("mw chainmail",
        ({ "silver bar", 1, "iron bar", 8, "carbon bar", 1 }) );

    add_supplied_commodity("mw lbreastplate", 0, 25, 5.0);
    set_commodity_amount("mw lbreastplate", 0);
    set_commodity_reserve("mw lbreastplate", 0);
    set_commodity_priority("mw lbreastplate", 0);
    add_supply_requirement("mw lbreastplate",
        ({ "silver bar", 1, "leather scrap", 6, "carbon bar", 1 }) );

    add_supplied_commodity("mw tunic", 0, 25, 5.0);
    set_commodity_amount("mw tunic", 0);
    set_commodity_reserve("mw tunic", 0);
    set_commodity_priority("mw tunic", 0);
    add_supply_requirement("mw tunic",
        ({ "silver bar", 1, "leather scrap", 10, "gold bar", 1 }) );

    add_supplied_commodity("mw helm", 0, 25, 5.0);
    set_commodity_amount("mw helm", 0);
    set_commodity_reserve("mw helm", 0);
    set_commodity_priority("mw helm", 0);
    add_supply_requirement("mw helm",
        ({ "silver bar", 1, "iron bar", 5, "carbon bar", 1 }) );

    add_supplied_commodity("mw chain hood", 0, 25, 5.0);
    set_commodity_amount("mw chain hood", 0);
    set_commodity_reserve("mw chain hood", 0);
    set_commodity_priority("mw chain hood", 0);
    add_supply_requirement("mw chain hood",
        ({ "silver bar", 1, "iron bar", 3, "carbon bar", 1 }) );

    add_supplied_commodity("mw coif", 0, 25, 5.0);
    set_commodity_amount("mw coif", 0);
    set_commodity_reserve("mw coif", 0);
    set_commodity_priority("mw coif", 0);
    add_supply_requirement("mw coif",
        ({ "silver bar", 1, "leather scrap", 3, "carbon bar", 1 }) );

    add_supplied_commodity("mw shield", 0, 25, 5.0);
    set_commodity_amount("mw shield", 0);
    set_commodity_reserve("mw shield", 0);
    set_commodity_priority("mw shield", 0);
    add_supply_requirement("mw shield",
        ({ "silver bar", 1, "leather scrap", 5, "iron bar", 8 }) );

    add_supplied_commodity("mw buckler", 0, 25, 5.0);
    set_commodity_amount("mw buckler", 0);
    set_commodity_reserve("mw buckler", 0);
    set_commodity_priority("mw buckler", 0);
    add_supply_requirement("mw buckler",
        ({ "silver bar", 1, "leather scrap", 5, "iron bar", 3 }) );

    add_supplied_commodity("mw pgauntlet", 0, 25, 5.0);
    set_commodity_amount("mw pgauntlet", 0);
    set_commodity_reserve("mw pgauntlet", 0);
    set_commodity_priority("mw pgauntlet", 0);
    add_supply_requirement("mw pgauntlet",
        ({ "silver bar", 1, "leather scrap", 1, "iron bar", 3 }) );

    add_supplied_commodity("mw cgloves", 0, 25, 5.0);
    set_commodity_amount("mw cgloves", 0);
    set_commodity_reserve("mw cgloves", 0);
    set_commodity_priority("mw cgloves", 0);
    add_supply_requirement("mw cgloves",
        ({ "silver bar", 1, "leather scrap", 2, "iron bar", 2 }) );

    add_supplied_commodity("mw lgloves", 0, 25, 5.0);
    set_commodity_amount("mw lgloves", 0);
    set_commodity_reserve("mw lgloves", 0);
    set_commodity_priority("mw lgloves", 0);
    add_supply_requirement("mw lgloves",
        ({ "silver bar", 1, "leather scrap", 4 }) );

    add_supplied_commodity("mw pgreaves", 0, 25, 5.0);
    set_commodity_amount("mw pgreaves", 0);
    set_commodity_reserve("mw pgreaves", 0);
    set_commodity_priority("mw pgreaves", 0);
    add_supply_requirement("mw pgreaves",
        ({ "silver bar", 1, "leather scrap", 1, "iron bar", 3 }) );

    add_supplied_commodity("mw cleggings", 0, 25, 5.0);
    set_commodity_amount("mw cleggings", 0);
    set_commodity_reserve("mw cleggings", 0);
    set_commodity_priority("mw cleggings", 0);
    add_supply_requirement("mw cleggings",
        ({ "silver bar", 1, "leather scrap", 2, "iron bar", 2 }) );

    add_supplied_commodity("mw lleggings", 0, 25, 5.0);
    set_commodity_amount("mw lleggings", 0);
    set_commodity_reserve("mw lleggings", 0);
    set_commodity_priority("mw lleggings", 0);
    add_supply_requirement("mw lleggings",
        ({ "silver bar", 1, "leather scrap", 4 }) );

    add_supplied_commodity("mw 1hspear", 0, 25, 5.0);
    set_commodity_amount("mw 1hspear", 0);
    set_commodity_reserve("mw 1hspear", 0);
    set_commodity_priority("mw 1hspear", 0);
    add_supply_requirement("mw 1hspear",
        ({ "iron bar", 8, "silver bar", 1, "leather scrap", 5 }) );

    add_supplied_commodity("mw 2hspear", 0, 25, 5.0);
    set_commodity_amount("mw 2hspear", 0);
    set_commodity_reserve("mw 2hspear", 0);
    set_commodity_priority("mw 2hspear", 0);
    add_supply_requirement("mw 2hspear",
        ({ "iron bar", 8, "silver bar", 1, "leather scrap", 5 }) );

    add_supplied_commodity("mw axe", 0, 25, 5.0);
    set_commodity_amount("mw axe", 0);
    set_commodity_reserve("mw axe", 0);
    set_commodity_priority("mw axe", 0);
    add_supply_requirement("mw axe",
        ({ "iron bar", 8, "silver bar", 1, "leather scrap", 5 }) );

    add_supplied_commodity("mw dagger", 0, 25, 5.0);
    set_commodity_amount("mw dagger", 0);
    set_commodity_reserve("mw dagger", 0);
    set_commodity_priority("mw dagger", 0);
    add_supply_requirement("mw dagger",
        ({ "iron bar", 4, "silver bar", 1, "leather scrap", 3 }) );

    add_supplied_commodity("mw greataxe", 0, 25, 5.0);
    set_commodity_amount("mw greataxe", 0);
    set_commodity_reserve("mw greataxe", 0);
    set_commodity_priority("mw greataxe", 0);
    add_supply_requirement("mw greataxe",
        ({ "iron bar", 8, "silver bar", 1, "leather scrap", 5 }) );

    add_supplied_commodity("mw greatsword", 0, 25, 5.0);
    set_commodity_amount("mw greatsword", 0);
    set_commodity_reserve("mw greatsword", 0);
    set_commodity_priority("mw greatsword", 0);
    add_supply_requirement("mw greatsword",
        ({ "iron bar", 8, "silver bar", 1, "leather scrap", 5 }) );

    add_supplied_commodity("mw hoopak", 0, 25, 5.0);
    set_commodity_amount("mw hoopak", 0);
    set_commodity_reserve("mw hoopak", 0);
    set_commodity_priority("mw hoopak", 0);
    add_supply_requirement("mw hoopak",
        ({ "iron bar", 8, "silver bar", 1, "leather scrap", 5 }) );

    add_supplied_commodity("mw longsword", 0, 25, 5.0);
    set_commodity_amount("mw longsword", 0);
    set_commodity_reserve("mw longsword", 0);
    set_commodity_priority("mw longsword", 0);
    add_supply_requirement("mw longsword",
        ({ "iron bar", 8, "silver bar", 1, "leather scrap", 5 }) );

    add_supplied_commodity("mw mace", 0, 25, 5.0);
    set_commodity_amount("mw mace", 0);
    set_commodity_reserve("mw mace", 0);
    set_commodity_priority("mw mace", 0);
    add_supply_requirement("mw mace",
        ({ "iron bar", 8, "silver bar", 1, "leather scrap", 5 }) );

    add_supplied_commodity("mw staff", 0, 25, 5.0);
    set_commodity_amount("mw staff", 0);
    set_commodity_reserve("mw staff", 0);
    set_commodity_priority("mw staff", 0);
    add_supply_requirement("mw staff",
        ({ "iron bar", 2, "silver bar", 2, "leather scrap", 5 }) );

    add_supplied_commodity("mw warhammer", 0, 25, 5.0);
    set_commodity_amount("mw warhammer", 0);
    set_commodity_reserve("mw warhammer", 0);
    set_commodity_priority("mw warhammer", 0);
    add_supply_requirement("mw warhammer",
        ({ "iron bar", 8, "silver bar", 1, "leather scrap", 5 }) );

    add_supplied_commodity("mw bow", 0, 25, 5.0);
    set_commodity_amount("mw bow", 0);
    set_commodity_reserve("mw bow", 0);
    set_commodity_priority("mw bow", 0);
    add_supply_requirement("mw bow",
        ({ "iron bar", 3, "silver bar", 2, "leather scrap", 5 }) );

    add_supplied_commodity("mw wand", 0, 25, 5.0);
    set_commodity_amount("mw wand", 0);
    set_commodity_reserve("mw wand", 0);
    set_commodity_priority("mw wand", 0);
    add_supply_requirement("mw wand",
        ({ "iron bar", 2, "silver bar", 2, "leather scrap", 5 }) );

    add_prop(OBJ_M_NO_ATTACK, 1);

    set_act_time(20);
    add_act("emote swings the hammer hard and fast. With a loud " +
        "clank, the last of the slag falls from the sword he is " +
        "crafting. He raises it, gives a nod of approval, and then " +
        "lays it aside.");
    add_act("emote picks up the sword he is working on, wrinkles up " +
        "his face in disgust, and tosses it back into the molten metal.");
    add_act("say Whadda ye need? I don't have all day here.");
    add_act("say Hah! Let's see those lizards burn this one down! " +
        "She's strong as a rock... She IS a rock!");
    add_act("say That Otik is a good fellow. I keep telling him he's " +
        "in the wrong business though. No money in food!");
    add_act("emote sighs deeply, and goes back to pounding on " +
        "some metal.");
    add_act("say Something stinks around here, and I'll give you " +
        "hints as to what it is: Gob... Lins.");
    add_act("say Step right up! Business is good and gold is better!");
    add_act(({"emote clears his throat.", "say I need an ale! I'd " +
        "love it if someone handed me an ale from the Inn!"}));

    add_ask(({"leather scrap","leather scraps","leather","scraps"}),
        "say You should be able to gather leather scraps from the " +
        "creatures of the forests around here. Also from the " +
        "minotaurs skulking around north of Solace.", 1); 

    add_ask(({"iron bar","iron bars","iron","iron pieces","iron piece",
        "gold bar","gold bars","gold","silver bar","silver bars","bars",
        "bar"}),
        "say It is a bit of a journey, but you can source iron nuggets, " +
        "iron bars, silver nuggets, silver bars, and even gold nuggets " +
        "and gold bars from the dwarven mines east of Palanthas.", 1);

    add_ask(({"steel coins","steel coin"}),
        "say Steel coins are rare. More valuable than gold and platinum! " +
        "Your best chance of getting hold of any is as spoils of war... " +
        "Conquest on the battlefields of Krynn.", 1);

    add_ask(({"commission","commission masterwork equipment","masterwork",
        "masterwork equipment" }),
        "say I can forge the finest of armours and weapons in the realm! " +
        "Masterwork equipment, fitted to allow for the affixing of " +
        "augmentation crystals!", 1);

    add_ask(({"augmentation crystals","crystals"}),
        "say Augmentation crystals are uniquely shaped gems that have " +
        "been enchanted by Wizards in the times before the Cataclysm! " +
        "Rare, but if you come across them they can be inserted in to " +
        "masterwork equipment... providing magical enhancements or " +
        "benefits!", 1);

    add_ask(({"materials","material cost","material costs"}),
        "say I can only make masterwork equipment if I have the the right " +
        "stock at hand. Iron, silver, gold, carbon bars... leather scraps... " +
        "that sort of thing. If I am short, I will need an industrious " +
"adventurer such as yourself to get some for me! I pay well!", 1);

    set_default_answer("Theros did not hear your question over the noise " +
        "of the forge.\n");
  
    set_knight_prestige(-15);
    set_alignment(800);

    for (i = 0; i < 6; i++)
        set_base_stat(i, 190+random(5));

    set_all_attack_unarmed(10, 8);
    set_all_hitloc_unarmed(2);

    // lets move default items to shop
    preload_commodities(query_supplied_commodity());

    set_alarm(20.0, 240.0, &update_comm());

}

public void
introduce_to_arrival(object who)
{
    if (present(who, environment(this_object())))
    {
        command("introduce myself to " + OB_NAME(who));
        gIntroducedTo += ({ who->query_real_name() });
    }
}

void
create_masterwork_item(string str)
{
    int smith_obs = query_commodity_amount(str) + 1;
    set_commodity_amount(str, smith_obs);
}

public void
reset_commission_alarm()
{
    commission_alarm = 0;
}

int
do_commission(string str)
{
    mixed commod;
    string coname;
    object st_coin, ob;
    int in, mw_cost, stocka, maxcap, number, com_num;
    float costfa;
    mixed cost = 1.0;
    int amount = 1;

    if (!IS_CLUB_MEMBER(TP))
    {
        say(QCTNAME(TP)+ " asks Theros something.\n");
        command("say I only sell masterwork equipment to those " +
            "participating in the war for Krynn!");
        return 1;
    }

    if(commission_alarm)
    {
        say(QCTNAME(TP)+ " asks Theros something.\n");
        say_busy(TP);
        return 1;
    }

    if(TP->query_prop(MASTERWORK_PROP))
    {
        string commod_prop = TP->query_prop(MASTERWORK_PROP);
        commod_prop = find_commodity(commod_prop)->query_short();

        say(QCTNAME(TP)+ " asks Theros something.\n");
        command("scowl suspicious");
        command("say When you've purchased the " +
            commod_prop+ " you've commissioned " +
            "i'll consider another commission from you!");
        return 1;
    }

    commod = map(query_supplied_commodity(), find_commodity);

    // WARFARE_DEBUG("String pre commod: " +str);
    if (!sizeof(commod = FIND_STR_IN_ARR(str, commod)))
    {
        say(QCTNAME(TP)+ " asks Theros something.\n");
        command("frown");
        command("say A " +str+ "? Not sure what that is.");
        return 1;
    }   

    commod = commod[0];
    coname = commod->query_commodity_name();
    str = commod->short();

    //check if there are the required supplies to make the item
    string * reqcom = query_supply_requirement(coname);
    int reqsiz = sizeof(reqcom);
    int num = -1;
    int amt, needed;
    string needed_comods = "";
    string query_comods;
    mapping comods_map = ([ ]);

    while (num < reqsiz)
    {
        query_comods = reqcom[num];
        amt  = query_commodity_amount(query_comods);
        needed  = query_supply_requirement(coname, query_comods);
        if(amt < needed)
        {
           needed = needed - amt;
           comods_map += ([ query_comods : needed ]);
        }
        num++;
    }

    if(m_sizeof(comods_map))
    {
        int msize = 0;
        foreach(string mapped_comod, int mapped_num: comods_map)
        {
            msize++;
            if(m_sizeof(comods_map) - msize == 1)
            {
                if(mapped_num == 1)
                    needed_comods += mapped_num + " " +mapped_comod+ ", and ";
                else
                    needed_comods += mapped_num + " " +mapped_comod+ "s, and ";
            }
            else if(m_sizeof(comods_map) - msize > 1)
            {
                if(mapped_num == 1)
                    needed_comods += mapped_num + " " +mapped_comod+ ", ";
                else
                    needed_comods += mapped_num + " " +mapped_comod+ "s, ";
            }
            else
            {
                if(mapped_num == 1)
                    needed_comods += mapped_num + " " +mapped_comod;
                else
                    needed_comods += mapped_num + " " +mapped_comod+ "s";
            }
        }

        say(QCTNAME(TP)+ " asks Theros something.\n");
        command("sigh");
        command("say I am short on certain materials to make a " +
            str+ ". Namely " + needed_comods + ". It will take me " +
            "some time to make these myself, but I will buy any " +
            "you bring to me.");
        return 1;
    }    

    // The following estimates the cost of the equipment
    stocka = (query_commodity_amount(coname) + 1);
    number  = -1;
    maxcap  = query_commodity_capacity(coname);
    costfa  = itof(commod->query_commodity_value());
    costfa *= query_commodity_costf(coname);

    while (++number < amount)
    {
        cost += ((1.0 - (itof(stocka - number) / itof(maxcap))) / 0.5);
    }

    cost *= costfa;
    mw_price = MONEY_SPLIT(ftoi(cost));
    mw_cost = MASTERWORK_STEEL_PRICES[str];

    if (!mw_cost)
    {
        say(QCTNAME(TP)+ " asks Theros something.\n");
        TO->command("say Order from my list of weapons, armours, or wands!");
        TO->command("say I'll then customise to suit the client!");
        return 1; 
    }

    if (!objectp(st_coin = present("_krynn_warfare_token", TP)))
    {
        say(QCTNAME(TP)+ " asks Theros something.\n");
        TO->command("say You want to commission a " +str+ "? " +
            "Well for that I'll need steel coins on top of " +
            "material cost! " +C(LANG_WNUM(mw_cost))+ 
            " steel coins in fact!");
        TO->command("say Come back to me when you have them!");
        return 1; 
    }

    if ((in = st_coin->num_heap()) < mw_cost)
    {
        say(QCTNAME(TP)+ " asks Theros something.\n");
        TO->command("say You don't have " +LANG_WNUM(mw_cost)+ 
            " steel coins to commission that work!");
        TO->command("say Come back to me when you have them!");
        return 1; 
    }

    if (in > mw_cost)
        st_coin->set_heap_size(in - mw_cost);
    else
        st_coin->remove_object();

    TP->catch_msg("You hand over " +LANG_WNUM(mw_cost)+ " steel " +
        "coins to Theros.\n");
    say(QCTNAME(TP)+ " hands over " +LANG_WNUM(mw_cost)+ " steel " +
        "coins to Theros.\n");
    TO->command("emote counts the steel coins carefully.");
    TO->command("nod approving");
    TO->command("say " +C(LANG_WNUM(mw_cost))+ " cold steel " +
        "coins! I'll start working on it right away.");
    TO->command("say You will be able to buy it from me in " +
        "just a moment.");
    TP->add_prop(MASTERWORK_PROP, coname);

    commission_alarm = 1;

    // Removing the materials required to make it from Theros' stock
    num = -1;
    while (num < reqsiz)
    {
        query_comods = reqcom[num];
        needed  = query_supply_requirement(coname, query_comods);
        amt  = query_commodity_amount(query_comods);
        amt = amt - needed;
        set_commodity_amount(query_comods, amt);
        // CLUB_DEBUG("Reduce " +query_comods+ " by " +needed+ " to " +amt);
        num++;
    }

    set_alarm(1.5,0.0, &command("emote turns to his forge and " +
        "begins work crafting " +LANG_ADDART(str)+ "."));
    set_alarm(15.5,0.0, &command("emote wipes his brow as he " +
        "crafts " +LANG_ADDART(str)+ "."));
    set_alarm(30.5,0.0, &command("emote pounds tirelessly with " +
        "his smiths hammer as the " +str+ " starts to take shape."));
    set_alarm(45.5,0.0, &command("say Almost finished! Just need " +
        "to customise it!"));
    set_alarm(60.5,0.0, &command("emote completes work on " +
        "the " +str+ ", customising it according to the style of " +
        "the army supported on the battlefields.\n\nIt can now be " +
        "purchased for a cost of " +
        mw_price[3]+ " platinum, " +mw_price[2]+ " gold, " +
        mw_price[1]+ " silver, and " +mw_price[0]+ " copper."));
    set_alarm(60.5,0.0, &create_masterwork_item(coname));
    set_alarm(60.5,0.0, &reset_commission_alarm());
    return 1;
}

int
do_list(string str)
{
    setuid(); seteuid(getuid());
    string * commodity_list = query_supplied_commodity();
    object st_coin;
    int can_buy = 0;

    if (!str || ((str != "weapons") && (str != "armours") && 
        (str != "wands")) )
    {
        command("say For those participating in the War of the Lance, they can " +
             "<commission> me to craft masterwork items.");
        command("say I take commission in steel coins, and you will also need " +
             "to pay for material costs.");
        command("say I can make weapons, armours, and wands.");
        command("say Specify what you want listed to find out commission " +
            "details.");
        return 1; 
    }

    if (!objectp(st_coin = present("_krynn_warfare_token", TP)))
    {
        command("say It doesn't look like you have any steel coins.");
        command("frown");
        command("say Come back to me when you do, and I'll tell you " +
            "what I can make for you.");
        return 1; 
    }

    command("say Based on how many steel coins you have, I can make you...");

    commodity_list -= ({ "silver bar", "iron bar", "gold bar", "carbon bar" });

    foreach(string commodity: commodity_list)
    {
        string coname;
        int mw_cost;

        if (!objectp(find_commodity(commodity)))
        {
            command("say Urgh... I actually don't have that" + commodity);
        }
        else
        {            
            coname = find_commodity(commodity)->query_short();
            mw_cost = MASTERWORK_STEEL_PRICES[coname];

            if(find_commodity(commodity)->query_krynn_warfare_armour() &&
                (str == "armours"))
            {
                if((mw_cost <= st_coin->num_heap()) && (mw_cost != 0))
                {
                    command("say " +C(LANG_ADDART(coname))+ " for a " + 
                        mw_cost+ " steel coin commission.");
                    can_buy += 1;
                }
            }

            if(find_commodity(commodity)->query_krynn_warfare_weapon() &&
                (str == "weapons"))
            {
                if((mw_cost <= st_coin->num_heap()) && (mw_cost != 0))
                {
                    command("say " +C(LANG_ADDART(coname))+ " for a " + 
                        mw_cost+ " steel coin commission.");
                    can_buy += 1;
                }
            }

            if(find_commodity(commodity)->query_krynn_warfare_wand() &&
                (str == "wands"))
            {
                if((mw_cost <= st_coin->num_heap()) && (mw_cost != 0))
                {
                    command("say " +C(LANG_ADDART(coname))+ " for a " + 
                        mw_cost+ " steel coin commission.");
                    can_buy += 1;
                }
            }
        }
    }

    if(!can_buy)
    {
        command("say Nothing!");
        command("chortle");
        command("say Doesn't look like you have enough " +
            "steel coins for you to be able to commission " +
            "anything! Come back to me when you have more!");
        return 1;
    }

    command("say I'll customise your commission based on the army you " +
        "support.");
    command("emote flexes his large muscles.");
    command("say Just be aware that you also have to pay for material costs, " +
        "which can change depending on what I have in stock.");

    return 1;
}

public void
init_living()
{
    ::init_living();

    if (member_array(this_player()->query_real_name(), 
        gIntroducedTo) == -1)
    {
        set_alarm(1.0, 0.0, &introduce_to_arrival(this_player()));
    }

    /* weapon repair */
    add_action(do_w_fix,"sharpen");
    add_action(do_w_fix,"wax");
    add_action(do_w_cost,"wcost");

    /* armour repair */
    add_action(do_a_fix, "fix");
    add_action(do_a_cost, "acost");

    init_commerce();
    add_action("do_commission", "commission");
    add_action("do_list", "list");

}

/*
 * This function will return a percentage of what is in
 * stock of the pass commodity.
 */
public int
query_stock(string commod)
{
    int cap;
    int amo;
    int res;

    // write_debug("Query stock on " + commod + "\n");
    if (!exist_demanded_commodity(commod))
      return 0;

    cap = query_commodity_capacity(commod);
    amo = query_commodity_amount(commod);
    res = amo * 100;

    // write_debug("cap " + cap + "\tamo " + amo + " -- "); 
    // write_debug("res = amo * 100: " + amo * 100 + "  -- ");

    if ( res <= 0 )
       return 0;

    // write_debug("res / cap: Percentage: " + res / cap + "\n");
    return (res / cap);
}

public string
stat_living()
{
    return ::stat_living() + stat_commerce();
}
