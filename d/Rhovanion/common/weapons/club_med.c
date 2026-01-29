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
make_club_med(int arg)
{
  int pen, hit;

  if((arg < 0) || (arg > 2)) return;

  num = arg;
  switch(arg)
  {
    case 0:
      hit = 22+random(5);
      pen = 25+random(5);
      set_name(({"morning-star","star","morningstar","club"}));
      set_adj(({"stone","morning"}));
      set_short("stone morning-star"); set_pshort("stone morning-stars");
      set_long("This club consists of stone ball chained to the "+
               "wooden handle.\n");
      set_dt(W_BLUDGEON);
      set_hands(W_ANYH);
      break;
    case 1:
      hit = 27+random(5);
      pen = 18+random(5);
      set_name(({"mace","club"}));
      set_adj(({"iron"}));
      set_short("iron mace"); set_pshort("iron maces");
      set_long("This is nasty metal club with a winged head.\n");
      set_dt(W_BLUDGEON);
      set_hands(W_ANYH);
      break;
    case 2:
      hit = 19+random(5);
      pen = 28+random(5);
      set_name(({"warhammer","club"}));
      set_adj(({"large","pick"}));
      set_short("large warhammer"); set_pshort("large warhammers");
      set_long("This hammer-pick has a beak to punch through armour with "+
               "and a large hammer head on the back.\n");
      set_dt(W_BLUDGEON | W_IMPALE);
      set_hands(W_ANYH);
      break;
  }
  set_hit(hit);
  set_pen(pen);
  set_wt(W_CLUB);
  add_prop(OBJ_I_VALUE, F_VALUE_WEAPON(hit, pen) * (90+random(21)) / 100);
}

void
create_weapon()
{
  num = random(3);
  make_club_med(num);
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
  make_club_med(num);
  if(h) set_hit(h);
  if(p) set_pen(p);
  if(v) add_prop(OBJ_I_VALUE, v);
}
