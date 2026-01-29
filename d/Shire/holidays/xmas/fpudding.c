/*
 * Holiday food from Bree
 * Finwe, December 2002
 */
 
inherit "/std/food";
 
#include <stdproperties.h>
#include <macros.h>
#include "/d/Shire/sys/defs.h"
 
create_food()
{
    setuid();
    seteuid(getuid());

    set_name("pudding");
    add_name("figgy pudding");
    add_name("bowl of figgy pudding");
    set_pname("puddings");
    add_pname("figgy puddings");
    add_pname("bowls of figgy pudding");
    set_adj("figgy");
    set_short("bowl of figgy pudding");
    set_pshort("bowls of figgy pudding");
    set_long("This is a bowl of figgy pudding, a popular holiday " +
        "desert. It is thick, made from breadcrumbs, dried figs, " +
        "milk, sugar, and sweet spices like cinammon, allspice, " +
        "and nutmeg.\n");
    set_amount(100); 
}
