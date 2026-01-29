/*
 * A wardrobe for thr entrance
 * Finwe, April 2020
 */

inherit "/std/receptacle";
#include <macros.h>
#include "/sys/stdproperties.h";

void
create_receptacle()
{
    setuid(); 
    seteuid(getuid());

    set_name("wardrobe");
    set_adj("large");
    add_adj("wooden");
    set_pshort("large wooden wardrobe");
    set_long("This is a large wooden wardrobe. It is used to store coats, cloaks, boots, and other things used for travels. It is made of wood and decorated with ornate carvings.\n");

    set_no_show_composite(1);

    add_prop(CONT_I_WEIGHT, 10000); /* Not too heavy to carry */
    add_prop(CONT_I_MAX_WEIGHT, 100000); /* Let us put things in it */
    add_prop(CONT_I_VOLUME, 100000000); /* Pretty darn big */
    add_prop(CONT_I_MAX_VOLUME, 10000000000); /* Put things in it */
    add_prop(CONT_I_RIGID, 1); /* Desks are rigid */
    add_prop(CONT_I_CLOSED, 1); /* Start with it closed */
    add_prop(CONT_I_TRANSP,0);

}

query_recover() { return MASTER + ":"; }

