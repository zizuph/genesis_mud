#pragma save_binary
#pragma strict_types

inherit "/std/food.c";
#include <macros.h>
#include <composite.h>

string vorare;

public void
create_food()
{
    set_name("food");
    set_pname(({"foods"}));
    add_adj(({"pet"}));
    set_short("pet food");
    set_pshort("pet foods");
    set_long(".\n");
    
    add_prop(OBJ_M_NO_SELL, 1);
    
    set_amount(120);
}

public int
query_value()
{
    return 2500;
}

public string
set_vorare(string str)
{
    vorare = str;
}