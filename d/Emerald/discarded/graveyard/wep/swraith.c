/* A Wraith sword - another classic from Tulix's Armoury inc. */
/* coded 26/1/1992 */
/* graveyard/wep/swraith.c  is clone by graveyard/npc/wraith.c */
 
 
#include "/sys/stdproperties.h" /* I've looked through lots of examples. */
inherit "/std/weapon";          /* It seems all weapons start with these */
#include "/sys/wa_types.h"      /* so why should mine be different? #:-) */
 
void
create_weapon()
{
    /* Set name, short description and long description */
    set_name("sword");
    set_short("wraith sword"); /* Yup. Its a wraith sword */
    set_long( "It's a fairly basic sword.  "
        +"You don't see anything special about it.  "
        + "It looks like you could hurt someone with it.\n" );
 
    /* Better add an adverb or two */
    set_adj("wraith");
 
    /* Set 'to hit' and 'penetration' values */
    set_hit(25);
    set_pen(25); /* just a simple sword. */
 
    /* Set weapon type & damage type */
    set_wt(W_SWORD);/* It's a type of sword */
    set_dt(W_IMPALE|W_SLASH);
    /* It's a sword:impale & slash only */
 
    /* How is it wielded */
    set_hands(W_ANYH);    /* Looks like you can wield it in either hand */
 
    /* Set physical attributes */
    add_prop(OBJ_I_WEIGHT, 5000); /* sword weighs 5kg            */
    add_prop(OBJ_I_VOLUME, 800);  /* <weapon> takes up 0.8litres */
 
}
