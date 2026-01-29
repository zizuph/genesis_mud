/* graveyard/wep/aghoul.c is cloned by graveyard/npc/ghoul.c */
 
inherit "/std/weapon";          /* It seems all weapons start with these */
#include <wa_types.h>      /* so why should mine be different? #:-)      */
#include "/d/Emerald/defs.h"
 
void
create_weapon()
{
    /* Set name, short description and long description */
    set_name("axe");
    set_pname("axes"); /* Just in case there's more than one */
    set_short("ghoul axe"); /* Yup. Its a ghoul axe */
    set_pshort("ghoul axes");
    set_long("It's an axe, and it is one of evil origin.  "
        + "The axe head is quite heavy, and looks like cast iron.  "
        + "It is usually wielded by evil ghouls that inhabit dark places.  "
        + "It looks like you could hurt someone with it.\n");
 
    /* Better add an adverb or two */
    set_adj("ghoul");
 
    /* Set 'to hit' and 'penetration' values */
    set_hit(20);
    set_pen(30);
 
    /* Set weapon type & damage type */
    set_wt(W_AXE);/* It's a type of axe */
    set_dt(W_SLASH|W_BLUDGEON);
    /* It's an axe:slash & bludgeon only */
 
    /* How is it wielded */
    set_hands(W_ANYH);    /* Looks like you can wield it in either hand */
 
    /* Set physical attributes */
    add_prop(OBJ_I_WEIGHT, 9000); /* axe weighs 8kg      */
    add_prop(OBJ_I_VOLUME, 2000); /* axe takes up 2litres */
 
}
