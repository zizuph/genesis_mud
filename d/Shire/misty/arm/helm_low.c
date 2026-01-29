#pragma save_binary

inherit "/std/armour";
inherit "/lib/keep";

#include "/d/Shire/sys/defs.h"
#include <formulas.h>
#include <wa_types.h>

int num;

/*
 * this function actually creates armour
 */
void
make_helm_low(int arg)
{
  int ac;

  if((arg < 0) || (arg > 4)) return;

  num = arg;
  switch(arg)
  {
   case 0:
     ac = 2+random(3);
     set_name("cap");
     set_short("soft leather cap");
     set_pshort("soft leather caps");
     set_adj(({"soft","leather"}));
     set_long("This cap is made from soft leather.\n");
     break;
   case 1:
     ac = 4+random(4);
     set_name("cap");
     set_short("hard leather cap");
     set_pshort("hard leather caps");
     set_adj(({"soft","leather"}));
     set_long("This cap is made from hard leather.\n");
     break;
   case 2:
     ac = 4+random(4);
     set_name("cap");
     set_short("woven cord cap");
     set_pshort("woven cord caps");
     set_adj(({"soft","leather"}));
     set_long("This cap is made from woven cords.\n");
     break;
   case 3:
     ac = 5+random(4);
     set_name("cap");
     set_short("thick reed cap");
     set_pshort("thick reed caps");
     set_adj(({"thick","reed"}));
     set_long("This cap is made from thick reeds.\n");
     break;
   case 4:
     ac = 6+random(4);
     set_name("cap");
     set_short("quilt cap");
     set_pshort("quilt caps");
     set_adj(({"quilt"}));
     set_long("This cap is made of two layers of cloth with some "+
              "filler material.\n");
     break;
  }
  set_ac(ac);
  set_at(A_HEAD);
  add_prop(OBJ_I_WEIGHT, ac*100*(90+random(21)) / 100);
  add_prop(OBJ_I_VOLUME, ac*100*(70+random(21)) / 100);
  add_prop(OBJ_I_VALUE, F_VALUE_ARMOUR(ac) * (90+random(21)) / 100);
}
void
create_armour()
{
  num = random(5);
  make_helm_low(num);
}

string
query_recover()
{
  return MASTER+":"+query_arm_recover()+"#n#"+num+"#a#"+query_ac()+
         "#v#"+query_prop(OBJ_I_VALUE)+"#";
}

void
init_recover(string arg)
{
  string foobar;
  int a,v;

  init_arm_recover(arg);
  sscanf(arg, "%s#n#%d#a#%d#v#%d#%s", foobar, num, a, v, foobar);
  make_helm_low(num);
  if(a) set_ac(a);
  if(v) add_prop(OBJ_I_VALUE, v);
}
