#pragma save_binary

inherit "/std/armour";
inherit "/lib/keep";

#include "/sys/stdproperties.h"
#include "/sys/wa_types.h"
#include "/sys/formulas.h"
#include "/sys/macros.h"
#include "/d/Rhovanion/defs.h"

int num;

/*
 * this function actually creates armour
 */
void
make_helm_sup(int arg)
{
  int ac;

  if((arg < 0) || (arg > 6)) return;

  num = arg;
  switch(arg)
  {
   case 0:
     ac = 22+random(3);
     set_name("helmet");
     set_short("steel plate helmet");
     set_pshort("steel plate helmets");
     set_adj(({"steel","plate"}));
     set_long("This helmet is made from from sheet of steel.\n");
     break;
   case 1:
     ac = 23+random(3);
     set_name("helmet");
     set_short("iron tabard helmet");
     set_pshort("iron tabard helmets");
     set_adj(({"iron","tabard"}));
     set_long("This helmet is made from from sheet of iron. It has a "+
              "nose guard for better protection.\n");
     break;
   case 2:
     ac = 25+random(3);
     set_name("helmet");
     set_short("steel tabard helmet");
     set_pshort("steel tabard helmets");
     set_adj(({"steel","tabard"}));
     set_long("This helmet is made from from sheet of steel. It has a "+
              "nose guard for better protection.\n");
     break;
   case 3:
     ac = 26+random(3);
     set_name("helmet");
     set_short("bronze visored helmet");
     set_pshort("bronze visored helmets");
     set_adj(({"bronze","visored"}));
     set_long("This helmet is made from from sheet of bronze. It covers "+
              "your face and you can see through visor.\n");
     break;
   case 4:
     ac = 27+random(3);
     set_name("helmet");
     set_short("steel visored helmet");
     set_pshort("steel visored helmets");
     set_adj(({"steel","visored"}));
     set_long("This helmet is made from from sheet of steel. It covers "+
              "your face and you can see through visor.\n");
     break;
   case 5:
     ac = 29+random(3);
     set_name("helmet");
     set_short("great iron helmet");
     set_pshort("great iron  helmets");
     set_adj(({"great","iron"}));
     set_long("This is extra large helmet from sheet of iron. It covers "+
              "your face and you can see through visor.\n");
     break;
   case 6:
     ac = 33+random(3);
     set_name("helmet");
     set_short("great steel helmet");
     set_pshort("great steel  helmets");
     set_adj(({"great","steel"}));
     set_long("This is extra large helmet from sheet of alloyed steel. "+
              "It covers your face and you can see through visor.\n");
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
  num = random(7);
  make_helm_sup(num);
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
  make_helm_sup(num);
  if(a) set_ac(a);
  if(v) add_prop(OBJ_I_VALUE, v);
}
