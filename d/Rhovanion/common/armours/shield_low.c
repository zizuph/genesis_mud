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
make_shield_low(int arg)
{
  int ac;

  if((arg < 0) || (arg > 8)) return;

  num = arg;
  switch(arg)
  {
   case 0:
     ac = 7+random(4);
     set_name("shield");
     set_short("small leather shield");
     set_pshort("small leather shields");
     set_adj(({"small","leather","hardened"}));
     set_long("This is small shield made from hardened leather over the "+
              "wooden frame.\n");
     break;
   case 1:
     ac = 7+random(4);
     set_name(({"buckler","shield"}));
     set_short("leather buckler");
     set_pshort("leather bucklers");
     set_adj(({"leather","simple"}));
     set_long("This is simple leather buckler with wooden frame.\n");
     break;
   case 2:
     ac = 10+random(7);
     set_name(({"buckler","shield"})); 
     set_short("reinforced leather buckler");
     set_pshort("reinforced leather bucklers");
     set_adj(({"reinforced","leather"}));
     set_long("This leather buckler is reinforced with sewn in copper rings.\n");
     break;
   case 3:
     ac = 12+random(7);
     set_name("shield");
     set_short("small wooden shield");
     set_pshort("small wooden shields");
     set_adj(({"small","wooden"}));
     set_long("It is carved from some type of hard wood. Probably oak.\n");
     break;
   case 4:
     ac = 14+random(7);
     set_name(({"buckler","shield"}));
     set_short("copper buckler");
     set_pshort("copper bucklers");
     set_adj(({"iron","plain"}));
     set_long("This is plain copper buckler.\n");
     break;
   case 5:
     ac = 7+random(4);
     set_name("shield");
     set_short("medium leather shield");
     set_pshort("medium leather shields");
     set_adj(({"medium","leather","hardened"}));
     set_long("This is medium shield made from hardened leather over the "+
              "wooden frame.\n");
     break;
   case 6:
     ac = 7+random(4);
     set_name("shield");
     set_short("leather kite shield");
     set_pshort("leather kite shields");
     set_adj(({"leather","kite"}));
     set_long("This is simple leather buckler with wooden frame.\n");
     break;
   case 7:
     ac = 10+random(7);
     set_name("shield");
     set_short("reinforced medium leather shield");
     set_pshort("reinforced medium leather shields");
     set_adj(({"reinforced","medium","leather"}));
     set_long("This leather shield is reinforced with sewn in copper rings.\n");
     break;
   case 8:
     ac = 12+random(7);
     set_name("shield");
     set_short("wooden kite shield");
     set_pshort("wooden kite shields");
     set_adj(({"wooden","kite"}));
     set_long("It is carved from some type of hard wood. Probably oak.\n");
     break;
  }

  set_ac(ac);
  set_at(A_SHIELD);
  if(arg > 4)
  {
    add_prop(OBJ_I_WEIGHT, ac*142*(120+random(21)) / 100);
    add_prop(OBJ_I_VOLUME, ac*142*(90+random(21)) / 100);
    add_prop(OBJ_I_VALUE, F_VALUE_ARMOUR(ac) * (110+random(21)) / 100);
  }
  else
  {
    add_prop(OBJ_I_WEIGHT, ac*142*(80+random(21)) / 100);
    add_prop(OBJ_I_VOLUME, ac*142*(60+random(21)) / 100);
    add_prop(OBJ_I_VALUE, F_VALUE_ARMOUR(ac) * (90+random(21)) / 100);
  }
}

void
create_armour()
{
  num = random(9);
  make_shield_low(num);
}

int *
query_shield_slots()
{
  if(num > 4)
    return (::query_shield_slots() + ({ A_BODY }) );
  return ::query_shield_slots();
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
  make_shield_low(num);
  if(a) set_ac(a);
  if(v) add_prop(OBJ_I_VALUE, v);
}
