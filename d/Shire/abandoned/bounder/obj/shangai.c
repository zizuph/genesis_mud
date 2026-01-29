#pragma save_binary

inherit "/std/object";
#include "/d/Shire/common/defs.h"
#include <stdproperties.h> 

create_object()
{

    set_name("shangai");
    set_adj("leather-bound");
    add_name("_bounder_lay_guild_sling_");
    add_adj(({"sling","sling shot","slingshot","leather"}));
    set_short("leather-bound shangai");
    set_long("This "+short()+", typically regarded as a child's toy, "+
      "can be deadly in the hands of a practiced user. It consists of "+
      "a Y-shaped fork of yew, with an embroidered leather patch "+
      "strapped to the wood with some type of treated, springy animal "+
      "gut.\n");

    add_prop(OBJ_M_NO_DROP, 1);
    add_prop(OBJ_I_VOLUME, 1000);
    add_prop(OBJ_I_WEIGHT, 800); 
    add_prop(OBJ_I_VALUE, 0);

}
