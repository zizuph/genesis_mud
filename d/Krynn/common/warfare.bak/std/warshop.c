/*
 * Filename:    /d/Krynn/common/warfare/std/warshop
 * Description: Allows for an army to tax a shop in a wararea
 *
 * Copyright (c) April 2000 by Daniel W. Mathiasen alias Boron
 *
 * Revision history:
 *-----------------------
 */
#pragma strict_types

#include "/d/Krynn/common/defs.h"
#include <macros.h>
#include <composite.h>


inherit RECRUITBASE;

#define DEBUG(x)        find_player("boron")->catch_tell(x)
#define MAXLIST     30
#define TAX         15
#define MAX_TAX     50

private int tax;
private string sArea;



/*
 * Function name:   set_shop_war_area
 * Description:     Sets what war area the shop is located in
 * Arguments:       the war area is defined in WARFARE.h
 * Returns:         Nothing (void)
 */
public void
set_shop_war_area(string area)
{
    sArea = area;
}

/*
 * Function name:   query_shop_war_area
 * Description:     What war area the shop is located in
 * Returns:         The set wararea, default is Solace
 */
public string
query_shop_war_area()
{
    return sArea;
}

/*
 * Function name:   query_tax
 * Description:     Gives the current tax level, in percentage, this shop is
 *                  paying to the army.
 * Returns:         The current tax
 */
public int
query_tax()
{
    return tax;
}

/*
 * Function name:   set_tax
 * Description:     Sets the tax, in percentage, which is paying
 *                  no more then MAX_TAX though.
 * Arguments:       int new_tax, the new tax eg. 15 for 15%
 * Returns:         Nothing (void)
 */
public void
set_tax(int new_tax)
{
    tax =  (new_tax > MAX_TAX) ? MAX_TAX : new_tax;
}


/*
 * Function name: shop_hook_bought_items
 * Description:   Called when player has bought something
 * Arguments:     arr - The array of objects
 * Returns:       1
 */
public int
shop_hook_bought_items(object *arr)
{
    int i;
    int value = 0;
    int price = 0;
    int tmp = 0;
    int taxed = 0;

    // Update the army
    set_army( ARMYMASTER->army_in_area( query_shop_war_area() ) );

    for (i = 0; i < (sizeof(arr)); i++)
    {
        value += arr[i]->query_value();
        price += TO->query_buy_price(arr[i]);
    }
    // Since we devide with integer we have to make sure we don't
    // recive a 0 which we would pass on to a multiplication
    tmp = ( (price - value) / 100 );
    if (tmp == 0)
       tmp = 1;

    taxed = ( tmp * query_tax() );

    add_fund(taxed * 500);

    write(break_string("You bought " + COMPOSITE_DEAD(arr) + ".\n", 75));
    say(QCTNAME(this_player()) + " bought " + QCOMPDEAD + ".\n");

    return 1;
}


/*
 * Function name: shop_hook_sold_items
 * Description:   Hook that is called when player sold something
 * Arguments:     item - The item array player sold
 * Returns:       1
 */
public int
shop_hook_sold_items(object *arr)
{
    int i;
    int value = 0;
    int price = 0;
    int tmp = 0;
    int taxed = 0;

    // Update the army
    set_army( ARMYMASTER->army_in_area( query_shop_war_area() ) );

    for (i = 0; i < (sizeof(arr)); i++)
    {
        value += arr[i]->query_value();
        price += TO->query_sell_price(arr[i]);


    }

    // Since we devide with integer we have to make sure we don't
    // recive a 0 which we would pass on to a multiplication
    tmp = ( (value - price) / 100 );
    if (tmp == 0)
       tmp = 1;

    taxed = ( tmp * query_tax() );


  /* To allow the tax to be visible in the funds we */
  /* have a modifier to the actual tax */
    add_fund(taxed * 500);

    write(break_string("You sold " + COMPOSITE_DEAD(arr) + ".\n", 75));
    say(QCTNAME(this_player()) + " sold " + QCOMPDEAD + ".\n");
    return 1;
}
