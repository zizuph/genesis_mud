/*   An large backpack for the hardware store in Calia

    coder(s):   Maniac

    history:    
            31.1.94    Created                                Maniac
            2.2.95     Adapted to include standard backpack 
                       code                                   Maniac
    purpose:    hold items

    to do:      none
    bug:        none known
*/


inherit "/d/Calia/maniac/std/backpack";
#include <stdproperties.h>
#include <macros.h>
#include <composite.h>
#include "defs.h"

object this;

void
create_backpack()
{
    set_name("backpack");
    set_pname("backpacks");
    set_short("large backpack");
    set_pshort("large backpacks");
    set_adj("large");
    set_long("A large backpack ideal for the travelling warrior, " +
             "such as are common in Calia where it was made.  " +
             "It looks as though it can hold a lot of stuff.  " +
             "Typing \"packhelp\" will give you a list of commands.\n");

    add_prop(CONT_I_WEIGHT, 4500); 	/* grams */
    add_prop(CONT_I_MAX_WEIGHT, 150000); /* grams */
    add_prop(CONT_I_VOLUME, 8000); 	/* ml */
    add_prop(CONT_I_MAX_VOLUME, 150000); /* ml */

    add_prop(OBJ_I_VALUE, 450); 		/* Worth 450 cc */
    add_prop(OBJ_M_NO_SELL, "If you want to be able to sell this pack, " +
                            "type \"packsell\".  After this you may sell " +
                            "it as normal.\n");
 
    add_name("_calia_hardware_shop_");
    this = THIS;
}

/* Filter out certain objects when shifting stuff in or out of backpack */
int
a_filter(object ob)
{
    if  (    (ob->query_prop(OBJ_M_NO_SELL))
          || (ob->query_prop(OBJ_M_NO_GIVE))
          || (ob->query_prop(OBJ_M_NO_DROP))
          || (ob->query_prop(CONT_I_IN)) /* containers */
          || (ob->query_worn())
          || (!(ob->query_prop(OBJ_I_VALUE)))
          || (ob->query_wielded())
          || (ob->query_prop(LIVE_I_IS))
          || (ob->query_name() == "backpack")
          || (ob->query_name() == "message"))
        return 0;
    else
	return 1;
}

/* Enable player to sell the backpack */
int
packsell()
{
    object tp;

    tp = TP;
    if (!present(this, tp))
    {
        NF("You don't have it!\n");
        return 0;
    }
         
    tp->catch_msg("You may now sell the backpack.\n"); 
    remove_prop(OBJ_M_NO_SELL); 
    return 1;
}

/* Tell player about how to use the backpack */ 
int 
packhelp()
{
    object tp;

    tp = TP;
    if (!present(this, tp))
    {
        NF("You don't have it!\n");
        return 0;
    }

    tp->catch_msg("How to use the backpack:\n" +
        "\"packsell\" will make the backpack sellable, " +
        "\"packhold\" will make it non-sellable.    " +
        "\"packstore\" puts all unworn and unwielded items " +
        "excluding coins and other containers for example " +
        "into the backpack.    \"packget\" gets all such items " +
        "from the backpack into your main inventory.    " +    
        "\"packhelp\" gets this message.\n"); 
    return 1;
}

string
query_recover()
{
    return MASTER + ":" + query_container_recover();
}

void
init_recover(string arg)
{
    init_container_recover(arg);
}


/* Store selected items in the backpack */
int
packstore()
{
    object tp;
    object *conts, *moved;
    int x, y;

    tp = TP;
    if (!present(this, tp))
    {
        NF("You don't have it!\n");
        return 0;
    }

    conts = ({ });
    moved = ({ });

    conts = filter(all_inventory(tp), "a_filter", this);
    
    for (x = 0; x < sizeof(conts); x++)
    {
        conts[x]->move(this); 
        if (present(conts[x], this))
            moved += ({ conts[x] }) ;     /* successful move */
    }     
    
    if (sizeof(moved) == 0)
        tp->catch_msg("You didn't put anything in the backpack.\n");
    else
    {
        tp->catch_msg("You store " + COMPOSITE_DEAD(moved) + 
            " in the large backpack.\n");
        tell_room(environment(tp), QCTNAME(tp) + " stores " + 
            COMPOSITE_DEAD(moved) + " in the large backpack.\n", tp);
    }

    return 1;
}

/* Retrieve selected items from the backpack */
int
packget()
{
    object tp;
    object *conts, *moved;
    int x;
    
    tp = TP;
    if (!present(this, tp))
    {
         NF("You don't have it!\n");
         return 0;
    }

    conts = ({ });
    moved = ({ });

    conts = filter(all_inventory(this), "a_filter", this);
    
    for (x = 0; x < sizeof(conts); x++)
    {
        conts[x]->move(tp); 
        if (present(conts[x], tp))
            moved += ({ conts[x] }) ;     /* successful move */
    }     

    if (sizeof(moved) == 0)
        tp->catch_msg("You didn't retrieve anything from the backpack.\n");
    else
    {
        tp->catch_msg("You retrieve " + COMPOSITE_DEAD(moved) + 
            " from the large backpack.\n");
        tell_room(environment(tp), QCTNAME(tp) + " retrieves " + 
            COMPOSITE_DEAD(moved) + " from the large backpack.\n", tp);
    }

    return 1;
}

int
packhold()
{
    object tp;

    tp = TP;
    tp->catch_msg("The backpack is now non-sellable.\n"); 
    add_prop(OBJ_M_NO_SELL, "If you want to be able to sell this pack, " +
        "type \"packsell\".    After this you may sell it as normal.\n");
    return 1;
}

void
init()
{
     ::init();
     add_action("packsell", "packsell");
     add_action("packhold", "packhold");
     add_action("packstore", "packstore");
     add_action("packget", "packget");
     add_action("packhelp", "packhelp"); 
} 
