#pragma save_binary

inherit "/std/weapon";
inherit "/lib/keep";

#include "/sys/stdproperties.h"
#include "/sys/wa_types.h"
#include "/sys/formulas.h"
#include "/sys/macros.h"
#include "/d/Rhovanion/defs.h"

int num;

void
make_axe_low(int arg)
{
  int pen, hit;

  if((arg < 0) || (arg > 2)) return;

  num = arg;
  switch(arg)
  {
    case 0:
      hit = 10+random(4);
      pen = 14+random(4);
      set_name(({"axe"}));
      set_adj(({"small","iron"}));
      set_short("small iron axe");
      set_pshort("small iron axes");
      set_long("An ordinary axe... Only little smaller than usual.\n");
      set_dt(W_SLASH | W_BLUDGEON);
      set_hands(W_ANYH);
      break;
    case 1:
      hit = 13+random(5);
      pen = 17+random(6);
      set_name(({"axe"}));
      set_adj(({"iron"}));
      set_short("iron axe");
      set_pshort("iron axes");
      set_long("An ordinary axe... This kind of tool is very common.\n");
      set_dt(W_SLASH | W_BLUDGEON);
      set_hands(W_ANYH);
      break;
    case 2:
      hit = 13+random(5);
      pen = 17+random(6);
      set_name(({"axe"}));
      set_adj(({"woodcutter"}));
      set_short("woodcutter axe");
      set_pshort("woodcutter axes");
      set_long("You would use this especially for chopping trees.\n");
      set_dt(W_SLASH | W_BLUDGEON);
      set_hands(W_ANYH);
      break;
  }
  set_hit(hit);
  set_pen(pen);
  set_wt(W_AXE);
  add_prop(OBJ_I_VALUE, F_VALUE_WEAPON(hit, pen) * (90+random(21)) / 100);
}

void
create_weapon()
{
  num = random(3);
  make_axe_low(num);
}

string
query_recover()
{
  return MASTER+":"+query_wep_recover()+"#n#"+num+"#p#"+query_pen()+
        "#h#"+query_hit()+"#v#"+query_prop(OBJ_I_VALUE)+"#";
}

void
init_recover(string arg)
{
  string foobar;
  int p,h,v;

  init_wep_recover(arg);
  sscanf(arg, "%s#n#%d#p#%d#h#%d#v#%d#%s", foobar, num, p, h, v, foobar);
  make_axe_low(num);
  if(h) set_hit(h);
  if(p) set_pen(p);
  if(v) add_prop(OBJ_I_VALUE, v);
}
