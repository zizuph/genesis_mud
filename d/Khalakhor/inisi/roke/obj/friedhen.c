/*
 * friedhen.c
 *
 * Used in obj/deadhen.c
 *
 * This was once a part of the domain Roke.
 * Cleaned up and moved into Khalakhor by Glindor, Nov 2001.
 */

#pragma save_binary
#pragma strict_types

inherit "/std/food";

void
create_food()
{
    set_short("fried hen");
    set_name("hen");
    set_adj("fried");
    set_long("A fried hen. It looks delicious.\n");
    set_amount(30);
}
