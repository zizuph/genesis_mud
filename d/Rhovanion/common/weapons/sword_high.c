#pragma save_binary

inherit "/std/weapon";
inherit "/lib/keep";

#include "/sys/stdproperties.h"
#include "/sys/wa_types.h"
#include "/sys/macros.h"
#include "/sys/formulas.h"
#include "/d/Rhovanion/defs.h"

int num;

/*
 * this function actually creates weapon
 */
void
make_sword_high(int arg)
{
  int pen, hit;

  if((arg < 0) || (arg > 3)) return;

  num = arg;
  switch(arg)
  {
    case 0:
      hit = 33+random(5);
      pen = 19+random(5);
      set_name(({"rapier","sword","blade"}));
      set_adj(({"light","narrow"}));
      set_short("light narrow rapier");
      set_pshort("light narrow rapiers");
      set_long("It is light narrow blade designed for using its point.\n");
      set_dt(W_IMPALE);
      set_hands(W_ANYH);
      break;
    case 1:
      hit = 28+random(5);
      pen = 24+random(5);
      set_name(({"longsword","sword"}));
      set_adj(({"nice","ordinary"}));
      set_short("nice longsword");
      set_pshort("nice longswords");
      set_long("It is ordinary longsword, the common sword of the knights.\n");
      set_dt(W_SLASH | W_IMPALE);
      set_hands(W_ANYH);
      break;
    case 2:
      hit = 29+random(7);
      pen = 26+random(5);
      set_name(({"sword"}));
      set_adj(({"bastard","broad"}));
      set_short("bastard sword");
      set_pshort("bastard swords");
      set_long("This broad double-edged sword is also known as "+
               "hand-and-half sword.\n");
      set_dt(W_SLASH | W_IMPALE);
      set_hands(W_BOTH);
      break;
    case 3:
      hit = 27+random(5);
      pen = 26+random(5);
      set_name(({"broadsword","sword"}));
      set_adj(({"broad","slashing","simple"}));
      set_short("broadsword");
      set_pshort("broadswords");
      set_long("This is simple broad slashing sword.\n");
      set_dt(W_SLASH);
      set_hands(W_ANYH);
      break;
  }
  set_hit(hit);
  set_pen(pen);
  set_wt(W_SWORD);
  add_prop(OBJ_I_VALUE, F_VALUE_WEAPON(hit, pen) * (90+random(21)) / 100);
}

void
create_weapon()
{
  num = random(4);
  make_sword_high(num);
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
  sscanf(arg, "%s#n#%d#p#%d#h#%d#%s", foobar, num, p, h, v, foobar);
  make_sword_high(num);
  if(h) set_hit(h);
  if(p) set_pen(p);
  if(v) add_prop(OBJ_I_VALUE, v);
}
