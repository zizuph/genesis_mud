inherit "/std/receptacle.c";
#include "/d/Raumdor/defs.h"
/* SARR */

void
create_receptacle()
{
    set_name("chest");
    set_adj("wooden");
    add_adj("black");
    set_short("black wooden chest");
    add_prop(CONT_I_MAX_WEIGHT,2000);
    add_prop(CONT_I_MAX_VOLUME,2000);
    add_prop(CONT_I_WEIGHT,500);
    add_prop(CONT_I_VOLUME,500);    
    add_prop(CONT_I_CLOSED,1);
    set_long("This is a small wooden chest made of black oak. The "+
    "top of it is adorned with red runes. It has a large iron lock "+
    "set on it.\n");
}

