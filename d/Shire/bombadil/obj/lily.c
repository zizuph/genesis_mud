/*
 * Lilies for Tom Bombadil
 * Cloning the lily will result in different types and colors
 * By Finwe, January 2002
 *
 * Added these lillies as a herb component for a Herald spell
 * inherited /lib/keep.c
 * made weight variable
 * Arman - June 2018
 */
 
#include "/d/Shire/sys/defs.h" 
#include "../local.h"
inherit "/std/object";
inherit "/lib/keep";

#include <macros.h>
#include <ss_types.h>
#include <wa_types.h>
#include "/sys/ss_types.h"

void
create_object()
{
    set_keep();

/*
 * creates x,y, and z as integers, 
 * and color, size, and type as string variables
 */
    int x,y,z;
    string *color, *size, *type;
/*
 * sets up arrays for different adjectives and types
 */ 
    color = ({"white", "lavender", "pink", "pale yellow", "pale blue", "light orange"});
    size  = ({"large", "medium", "small"});
    type  = ({"lots of petals", "some petals", "few petals"});
 
/* 
 * randomly chooses adjectives and types
 */
    x = random(sizeof(size));
    y = random(sizeof(color));
    z = random(sizeof(type));
 
    add_adj(size[x]);
    add_adj(color[y]);
    add_adj(type[z]);
    add_prop(LIVE_I_NEVERKNOWN, 1);
 
    set_name("lily");
    add_name("water lily");
    add_name(LILY_PROP);
    add_name("_spell_ingredient");

   add_prop(OBJ_I_VALUE, 50+random(50));
   add_prop(OBJ_I_VOLUME, 2500);
   add_prop(OBJ_I_WEIGHT, 50 + random(450));


    set_short(color[y] +" water lily");
    set_long("This is a "+short()+". It grows along side slow moving " +
        "rivers. The flower is "+size[x]+" with "+type[z]+". The flower " +
        "grows on a long, slender green stem and is partially open. The " +
        "blossom is lighty fragrant.\n");

}
