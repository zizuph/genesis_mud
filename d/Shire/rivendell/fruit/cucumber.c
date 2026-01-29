/*
 * Vegetables from Garden
 * Coded by Finwe, February 1998
 */
 
inherit "/std/food";
 
#include <stdproperties.h>
#include <macros.h>
#include "/d/Shire/sys/defs.h"
 
 
create_food()
{
    set_name("cucumber");
    set_adj(({"long", "green"}));
    set_short("long green cucumber");
    set_long("This large cucumber is perfectly shaped. Its rind " +
        "is a deep green color and the fruit looks like it " +
        "would be tasty.\n");
    add_name("vegetable");
    set_amount(150);
    add_prop(OBJ_I_WEIGHT, 200);
    add_prop(OBJ_I_VOLUME, 150);
}                             
