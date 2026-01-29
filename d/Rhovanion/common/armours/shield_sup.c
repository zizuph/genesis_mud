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
make_shield_sup(int arg)
{
  int ac;

  if((arg < 0) || (arg > 4)) return;

  num = arg;
  switch(arg)
  {
   case 0:
     ac = 25+random(4);
     set_name("shield");
     set_short("alloyed steel shield");
     set_pshort("alloyed steel shields");
     set_adj(({"steel","kite","alloyed"}));
     set_long("This kite shield is made of alloyed steel.\n");
     break;
   case 1:
     ac = 22+random(4);
     set_name("shield");
     set_short("big tempered iron shield");
     set_pshort("big tempered iron shields");
     set_adj(({"big","iron","tempered"}));
     set_long("This shield is made of tempered iron.\n");
     break;
   case 2:
     ac = 23+random(4);
     set_name("shield");
     set_short("big steel shield");
     set_pshort("big steel shields");
     set_adj(({"steel","big"}));
     set_long("This big shield is made of steel.\n");
     break;
   case 3:
     ac = 33+random(5);
     set_name("shield");
     set_short("huge mithril shield");
     set_pshort("huge mithril shields");
     set_adj(({"huge","mithril"}));
     set_long("This huge mithril shield can cover you almost perfectly.\n");
     break;
   case 4:
     ac = 29+random(5);
     set_name("shield");
     set_short("massive steel shield");
     set_pshort("massive steel shields");
     set_adj(({"massive","steel"}));
     set_long("This shield made of alloyed steel offers good protection.\n");
     break;
  }

  set_ac(ac);
  set_at(A_SHIELD);
  if(arg > 2)
  {
    add_prop(OBJ_I_WEIGHT, ac*142*(180+random(21)) / 100);
    add_prop(OBJ_I_VOLUME, ac*142*(130+random(21)) / 100);
    add_prop(OBJ_I_VALUE, F_VALUE_ARMOUR(ac) * (130+random(21)) / 100);
  }
  else if(arg > 0)
  {
    add_prop(OBJ_I_WEIGHT, ac*142*(150+random(21)) / 100);
    add_prop(OBJ_I_VOLUME, ac*142*(110+random(21)) / 100);
    add_prop(OBJ_I_VALUE, F_VALUE_ARMOUR(ac) * (110+random(21)) / 100);
  }
  else 
  {
    add_prop(OBJ_I_WEIGHT, ac*142*(120+random(21)) / 100);
    add_prop(OBJ_I_VOLUME, ac*142*(90+random(21)) / 100);
    add_prop(OBJ_I_VALUE, F_VALUE_ARMOUR(ac) * (110+random(21)) / 100);
  }
}

void
create_armour()
{
  num = random(5);
  make_shield_sup(num);
}

int *
query_shield_slots()
{
  if(num > 2)
    return (::query_shield_slots() + ({ A_BODY , A_LEGS , A_HEAD }) );
  if(num > 0)
    return (::query_shield_slots() + ({ A_BODY , A_LEGS }) );
  return (::query_shield_slots() + ({ A_BODY }) );
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
  make_shield_sup(num);
  if(a) set_ac(a);
  if(v) add_prop(OBJ_I_VALUE, v);
}

static int
set_condition(int cond)
{
  return ::set_condition(cond);
}

void
remove_broken()
{
  if(num == 3) return;
  ::remove_broken();
}

int
add_prop_obj_i_broken(mixed arg)
{
  if(num == 3) return 1;
  return 0;
}
