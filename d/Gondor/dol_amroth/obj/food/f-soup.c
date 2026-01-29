/* 
 *  f-soup.c
 *
 * By Skippern 20(c)02
 *  Amount 570, price 576 cc.
 */
#pragma save_binary
#pragma strict_types

inherit "/std/food";

#include <stdproperties.h>

public void
create_food()
{
    set_name("soup");
    add_name("fish");
    add_name("bowl");
    set_pname("soups");
    add_pname("fish");
    add_pname("bowls");
    set_adj("hot");
    set_short("bowl of fish soup");
    set_pshort("bowls of fish soup");
    set_long("This is a bowl of fish soup, made the traditional way. " +
        "Chunks of carrots celery, and onions swim a fragrant broth.\n");
    add_prop(OBJ_I_VALUE, 0);
    set_amount(570);
    add_prop(OBJ_I_WEIGHT, 560);
    add_prop(OBJ_I_VOLUME, 480);
}
