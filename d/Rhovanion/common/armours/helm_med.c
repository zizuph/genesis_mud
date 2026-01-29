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
make_helm_med(int arg)
{
  int ac;

  if((arg < 0) || (arg > 5)) return;

  num = arg;
  switch(arg)
  {
   case 0:
     ac = 7+random(3);
     set_name("cap");
     set_short("cuir-bouili cap");
     set_pshort("cuir-bouili caps");
     set_adj(({"cuir-bouili","cuir","bouili","leather"}));
     set_long("This cap is made from leather boiled in oil.\n");
     break;
   case 1:
     ac = 8+random(3);
     set_name("cap");
     set_short("studded cap");
     set_pshort("studded caps");
     set_adj(({"studded","hard","leather"}));
     set_long("This cap has studs set in hard leather.\n");
     break;
   case 2:
     ac = 11+random(3);
     set_name("helm");
     set_short("copper ringmail helm");
     set_pshort("copper ringmail helm");
     set_adj(({"copper","ringmail","hard","leather"}));
     set_long("This cap has copper rings sewn to hard leather.\n");
     break;
   case 3:
     ac = 13+random(3);
     set_name("helm");
     set_short("iron ringmail helm");
     set_pshort("iron ringmail helm");
     set_adj(({"iron","ringmail","hard","leather"}));
     set_long("This cap has iron rings sewn to hard leather.\n");
     break;
   case 4:
     ac = 14+random(4);
     set_name("helmet");
     set_short("iron chain helmet");
     set_pshort("iron chain helmets");
     set_adj(({"iron","chain","chainmail"}));
     set_long("This helmet has iron chainmail coif worn over "+
              "leather padding.\n");
     break;
   case 5:
     ac = 16+random(4);
     set_name("helmet");
     set_short("steel chain helmet");
     set_pshort("steel chain helmets");
     set_adj(({"iron","chain","chainmail"}));
     set_long("This helmet has steel chainmail coif worn over "+
              "leather padding.\n");
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
  num = random(6);
  make_helm_med(num);
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
  make_helm_med(num);
  if(a) set_ac(a);
  if(v) add_prop(OBJ_I_VALUE, v);
}
