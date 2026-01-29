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
make_pole_med(int arg)
{
  int pen, hit;

  if((arg < 0) || (arg > 4)) return;

  num = arg;
  switch(arg)
  {
    case 0:
      hit = 21+random(5);
      pen = 18+random(5);
      set_name(({"partisan","polearm"}));
      set_adj(({}));
      set_short("partisan");
      set_pshort("partisans");
      set_long("This polearm has a broad spear-head with two small blades "+
		"like ears projecting out at the base of the head.\n");
      set_dt(W_IMPALE);
      set_hands(W_BOTH);
      break;
    case 1:
      hit = 23+random(5);
      pen = 19+random(5);
      set_name(({"roncone","polearm"}));
      set_adj(({}));
      set_short("roncone");
      set_pshort("roncones");
      set_long("This polearm has a broad spear-head with the \"ears\" like "+
		"partysan - only larger and curved to point backwards.\n");
      set_dt(W_IMPALE);
      set_hands(W_BOTH);
      break;
    case 2:
      hit = 22+random(5);
      pen = 23+random(5);
      set_name(({"corseques","polearm"}));
      set_adj(({}));
      set_short("corseques");
      set_pshort("corsequeses");
      set_long("This polearm has a broad spear-head with the \"ears\" like "+
		"partysan - only larger, straight and pointy.\n");
      set_dt(W_IMPALE);
      set_hands(W_BOTH);
      break;
    case 3:
      hit = 20+random(5);
      pen = 20+random(5);
      set_name(({"fork","polearm"}));
      set_adj(({"military"}));
      set_short("military fork");
      set_pshort("military forks");
      set_long("This polearm, developed from the pitchfork, has two long "+
		"prongs and two backward hooks to parry and catch weapons "+
		"with.\n");
      set_dt(W_IMPALE);
      set_hands(W_BOTH);
      break;
    case 4:
      hit = 19+random(5);
      pen = 26+random(5);
      set_name(({"glaive","polearm"}));
      set_adj(({"nasty"}));
      set_short("nasty glaive");
      set_pshort("nasty glaives");
      set_long("This polearm has a single-edged blade mounted upon a pole.\n");
      set_dt(W_SLASH);
      set_hands(W_BOTH);
      break;
  }
  set_hit(hit);
  set_pen(pen);
  set_wt(W_POLEARM);
  add_prop(OBJ_I_VALUE, F_VALUE_WEAPON(hit, pen) * (90+random(21)) / 100);
}

void
create_weapon()
{
  num = random(5);
  make_pole_med(num);
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
  make_pole_med(num);
  if(h) set_hit(h);
  if(p) set_pen(p);
  if(v) add_prop(OBJ_I_VALUE, v);
}
