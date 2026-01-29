
/* 
 * sword.c
 * Ergothian longsword
 * City of Gulfport, Northern Ergoth
 * Tibbit, 2 May 1998
 */

inherit "/std/weapon";
#include <wa_types.h> /* Some weapon-specific defs */
#include <stdproperties.h>

void
create_weapon()
{
    set_name("longsword");
    add_name("sword");
    set_adj("Ergothian");
    add_adj("ergothian");

    set_short("Ergothian longsword");
    set_pshort("Ergothian longswords");

    set_long("A well-crafted longsword from the "+
        "lands of Northern Ergoth, where they specialize in "+
        "tools (and weapons) of bronze and steel.  "+
        "This sword has a nice weight to it, "+
        "and fits comfortably into the human hand "+
        "(being a bit large for kender, dwarves and the "+
        "like; and a bit small for ogres and such).\n");

    set_hit(29);
    set_pen(25);

    set_dt(W_IMPALE | W_SLASH);
    set_wt(W_SWORD);

    set_hands(W_ANYH);

    /* Props for value, volume, weight may be set if you like */
    add_prop(OBJ_I_VALUE,400);
    add_prop(OBJ_I_WEIGHT,750);
    add_prop(OBJ_I_VOLUME,700);
}
