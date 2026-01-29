inherit "/std/armour";
#include "/d/Raumdor/defs.h"
/* diry black helm, by Sarr */

void
create_armour()
{
    ::create_armour();
    set_name("helm");
    set_adj("dirty");
    add_adj("black");
    set_short("dirty black helm");
    set_long("This helm, made of blackened steel, looks worn and used. "+
    "It has some dents in it, and is covered in filth. Looking closer, "+
    "you can see a picture of a grim skull on it.\n");
    set_ac(30);
    set_at(A_HEAD);
    set_am(({-2,1,-2}));
    add_prop(OBJ_I_WEIGHT,5000);
    add_prop(OBJ_I_VOLUME,3000);
    add_prop(OBJ_I_VALUE,50);
}
