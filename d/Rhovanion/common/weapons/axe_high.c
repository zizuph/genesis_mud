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
make_axe_high(int arg)
{
  int pen, hit;

  if((arg < 0) || (arg > 3)) return;

  num = arg;
  switch(arg)
  {
    case 0:
      hit = 20+random(5);
      pen = 27+random(5);
      set_name(({"axe"}));
      set_adj(({"battle"}));
      set_short("battle axe");
      set_pshort("battle axes");
      set_long("Its head is balanced by a small hammer at the back.\n");
      set_dt(W_SLASH | W_BLUDGEON);
      set_hands(W_ANYH);
      break;
    case 1:
      hit = 19+random(6);
      pen = 34+random(6);
      set_name(({"axe"}));
      set_adj(({"broad"}));
      set_short("broad axe");
      set_pshort("broad axes");
      set_long("This broad axe has wickedly curved head near the top.\n");
      set_dt(W_SLASH | W_BLUDGEON);
      set_hands(W_BOTH);
      break;
    case 2:
      hit = 19+random(5);
      pen = 29+random(6);
      set_name(({"bardiche","axe"}));
      set_adj(({"curved"}));
      set_short("curved bardiche");
      set_pshort("curved bardiches");
      set_long("This axe has a long curved head with the lower end of the "+
		"blade fastened to the shaft.\n");
      set_dt(W_SLASH | W_BLUDGEON);
      set_hands(W_BOTH);
      break;
    case 3:
      hit = 23+random(5);
      pen = 33+random(6);
      set_name(({"axe"}));
      set_adj(({"lochaber"}));
      set_short("lochaber axe");
      set_pshort("lochaber axes");
      set_long("This axe has a nasty head. The end of the blade can be used "+
		"to impale with and it has a hook on the back.\n");
      set_dt(W_SLASH | W_BLUDGEON | W_IMPALE);
      set_hands(W_BOTH);
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
  num = random(4);
  make_axe_high(num);
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
  make_axe_high(num);
  if(h) set_hit(h);
  if(p) set_pen(p);
  if(v) add_prop(OBJ_I_VALUE, v);
}
