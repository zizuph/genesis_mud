inherit "/std/armour";
#include <wa_types.h>
#include <formulas.h>
#include <stdproperties.h>
#include <macros.h>

string *gAdj1 = ({"blue","green",
  "red","white","black","plain","pale blue","grey"});
string *gAdj2 = ({"silk","sweaty","clean","woolen",
  "puffy","dirty","expensive","embroidered","frilly",
  "ordinary","high-necked","black-buttoned",
  "golden-cuffed","torn","patchy"});

#ifndef ONE_OF
#define ONE_OF(x)  (x[random(sizeof(x))])
#endif

create_armour()
{
  string adj1, adj2;
  
    set_name("shirt");
    adj1=(ONE_OF(gAdj1));
    adj2=(ONE_OF(gAdj2));
    set_adj(adj1);
    add_adj(adj2);
//    set_short(implode(query_adjs()," ") + " shirt"); // nice one but it gets
//    							all adj - including
//    							unworn :P
    set_short(adj1+ " " + adj2 + " shirt");
    set_pshort(adj1+ " " + adj2 + " shirts");
    set_long("This is a " +short()+ " typically worn by " +
      "male citizens of Kalaman.\n");
    set_ac(2);
    set_am(({0,0,0}));
    set_at(A_BODY);
    add_prop(OBJ_I_VALUE, 200);
    add_prop(OBJ_I_VOLUME, 200);
    add_prop(OBJ_I_WEIGHT, 250);
}
