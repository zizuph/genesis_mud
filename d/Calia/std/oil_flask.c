/*
 *    oil_flask.c
 *
 *   A standard oil flask. 
 *
 *  This is a standard oil_flask that you can inherit
 *  and use for various oil lanterns and lamps. It works
 *  for both the calian standard I made and the gondorian
 *  version who seems to be somewhat of a global standard.
 *
 *  Baldacin@Genesis, Feb 2004.
 */
inherit "/std/object";
inherit "/lib/keep";
#include <macros.h>
#include <stdproperties.h>

int gOil_amount,
    gMax_hold;

void set_how_full(int amount);
int query_how_full();
void set_max_hold(int amount);
int query_max_hold();

int this_is_oil_flask() { return 1; }

/*
 * Function name: create_oil_flask
 * Description  : Creates the oil flask. Use this to create the flask
 *                and not the create_object function.
 */
void
create_oil_flask()
{
}

/*
 * Function name: create_object
 * Description  : Creates the object. You can't create the flask
 *                by using this function since it is declared nomask,
 *                use create_oil_flask().
 */
nomask void
create_object()
{
    set_name("flask");
    add_name("oil");
    add_name("_gondorian_flask_with_oil_");
    set_long("This is an oil flask. it is @@query_amount_str@@\n");
    
    set_how_full(2000);
    set_max_hold(2000);
    
    add_prop(OBJ_I_VALUE,  "@@compute_value");
    add_prop(OBJ_I_WEIGHT, "@@compute_weight");
    add_prop(OBJ_I_VOLUME, "@@compute_volume");
    
    set_keep(1);
    create_oil_flask();
}

int
compute_weight()
{
    /* 300 for the flask and 2 gram per 6 ml oil */
    return (300 + (2 * gOil_amount / 6));
}

int
compute_volume()
{
    /* the glass flask IS rigid - differs from Gondoran */
    return (150 + gMax_hold);
}
 
int
compute_value()
{
    /* 40 for the flask and 1 cc per 30 ml oil */
    return (40 + (gOil_amount / 30));
}

/*
 * Function name: set_how_full
 * Description  : Sets the amount of oil it contains
 * Arguments    : int amount - the amount.
 */
void
set_how_full(int amount)
{	
    gOil_amount = amount;
}

/*
 * Function name: query_how_full
 * Description  : Queries the amount of oil it contains
 * Returns      : int - the amount.
 */
int
query_how_full()
{
    return gOil_amount;
}

/*
 * Function name: set_max_hold
 * Description  : Sets the max amount of oil it can contain
 * Arguments    : int amount - the max amount.
 */
void
set_max_hold(int amount)
{
    gMax_hold = amount;
}

/*
 * Function name: query_max_hold
 * Description  : Queries the max amount of oil it can contain
 * Returns      : int - the max amount.
 */
int
query_max_hold()
{
    return gMax_hold;
}

/*
 * Function name: query_amount
 * Description  : Queries the amount of oil it contains
 * Returns      : string - the amount.
 */
string
query_amount_str()
{
    int how_full;
    
    how_full = (query_how_full() * 100) / query_max_hold();
    
    switch(how_full)
    {
        case -1..0:
            return "empty of oil.";
        break;
        
        case 1..20:
            return "nearly empty of oil.";
        break;
                
        case 21..40:
            return "about one-third filled with oil.";
        break;
                
        case 41..60:
            return "half filled with oil.";
        break;
                
        case 61..80:
            return "about two-thirds filled with oil.";
        break;
                
        case 81..99:
            return "nearly filled with oil.";
        break;
        
        default:
            return "filled with oil.";
        break;
    }
}


/* 
 * The following functions are only here to make it compatible 
 * with the Gondor flask and oil.
 */

/*
 * Function name: query_amount
 * Description  : Queries the amount of oil it contains
 * Returns      : int - the amount.
 */
int
query_amount()
{
    return gOil_amount;
}

/*
 * Function name: remove_oil
 * Description  : Removes (int)amount of oil from the flask
 * Arguments    : int amount - the amount.
 */
void
remove_oil(int amount)
{	
    gOil_amount -= amount;
}

