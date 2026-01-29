inherit "/std/food";
#include <stdproperties.h>

/*
 * Function name: create_food()
 * Description  : Constructor.  Creates the food.
 */
create_food()
{
    set_name("bisque");
    add_name("seafood bisque");
    set_adj("seafood");
    set_short("seafood bisque");
    set_pshort("seafood bisques");
    set_long("A white cream broth thickened with blonde rue containing"
    +" shrimp, clams, crab meat and whitefish. A blend of herbs and"
    +" spices complete the flavor combination.\n");
    set_amount(212);
}

