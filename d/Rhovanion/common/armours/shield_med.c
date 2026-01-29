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
make_shield_med(int arg)
{
  int ac;

  if((arg < 0) || (arg > 7)) return;

  num = arg;
  switch(arg)
  {
   case 0:
     ac = 13+random(7);
     set_name(({"buckler","shield"}));
     set_short("reinforced wooden buckler");
     set_pshort("reinforced wooden bucklers");
     set_adj(({"small","reinforced","wooden"}));
     set_long("This small wooden shield is reinforced by copper plates.\n");
     break;
   case 1:
     ac = 17+random(4);
     set_name(({"buckler","shield"}));
     set_short("bronze buckler");
     set_pshort("bronze bucklers");
     set_adj(({"small","bronze"}));
     set_long("This small shield is made of bronze.\n");
     break;
   case 2:
     ac = 20+random(4);
     set_name("shield");
     set_short("small steel shield");
     set_pshort("small steel shields");
     set_adj(({"small","steel"}));
     set_long("This is small steel shield.\n");
     break;
   case 3:
     ac = 16+random(4);
     set_name("shield");
     set_short("medium copper shield");
     set_pshort("medium copper shields");
     set_adj(({"medium","copper"}));
     set_long("This medium shield has green colour of oxidated copper.\n");
     break;
   case 4:
     ac = 17+random(4);
     set_name("shield");
     set_short("bronze kite shield");
     set_pshort("bronze kite shields");
     set_adj(({"medium","bronze","kite"}));
     set_long("This medium shield is made of bronze.\n");
     break;
   case 5:
     ac = 17+random(4);
     set_name("shield");
     set_short("brass shield");
     set_pshort("brass shields");
     set_adj(({"brass","kite"}));
     set_long("This kite shield is made of brass.\n");
     break;
   case 6:
     ac = 19+random(4);
     set_name("shield");
     set_short("iron shield");
     set_pshort("iron shields");
     set_adj(({"medium","iron"}));
     set_long("This is medium iron shield.\n");
     break;
   case 7:
     ac = 15+random(5);
     set_name("shield");
     set_short("wooden footmans shield");
     set_pshort("wooden footmans shields");
     set_adj(({"big","wooden","footmans"}));
     set_long("This big wooden shield is made of wood reinforced by brass.\n");
     break;
  }

  set_ac(ac);
  set_at(A_SHIELD);
  if(arg > 6)
  {
    add_prop(OBJ_I_WEIGHT, ac*142*(150+random(21)) / 100);
    add_prop(OBJ_I_VOLUME, ac*142*(110+random(21)) / 100);
    add_prop(OBJ_I_VALUE, F_VALUE_ARMOUR(ac) * (110+random(21)) / 100);
  }
  else if(arg > 2)
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
  num = random(8);
  make_shield_med(num);
}

int *
query_shield_slots()
{
  if(num > 6)
    return (::query_shield_slots() + ({ A_BODY , A_LEGS }) );
  if(num > 2)
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
  make_shield_med(num);
  if(a) set_ac(a);
  if(v) add_prop(OBJ_I_VALUE, v);
}
