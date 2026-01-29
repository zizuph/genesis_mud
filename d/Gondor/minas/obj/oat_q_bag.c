/*
 * /d/Gondor/minas/obj/oat_q_bag.c
 *
 * oats for the Oat Quest
 *
 * Alto, 12 May 2001
 *
 */


inherit "/std/food";
#include "/sys/stdproperties.h"

void
create_food()
{
    set_name("oats");
    add_name("_oat_quest_bag_");
    add_name("bag");
    set_pname("oats");
    add_pname("bags");
    set_short("bag of oats");
    set_pshort("bags of oats");
    set_long("A large bag of oats from the Lossarnach. From the odour "
        + "wafting up from the bag, they seem almost good enough for a "
        + "person to eat, although you know they are meant for animals.\n");
    set_amount(300);
}
