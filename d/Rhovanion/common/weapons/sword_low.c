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
make_sword_low(int arg)
{
  int pen, hit;

  if((arg < 0) || (arg > 2)) return;

  num = arg;
  switch(arg)
  {
    case 0:
      hit = 17+random(5);
      pen = 12+random(8);
      set_name(({"blade","sword"}));
      set_adj(({"iron","short"}));
      set_short("iron blade");
      set_pshort("iron blades");
      set_long("This short iron sword has sharpened both edges.\n");
      set_dt(W_SLASH | W_IMPALE);
      set_hands(W_ANYH);
      break;
    case 1:
      hit = 19+random(5);
      pen = 12+random(10);
      set_name(({"gladius","sword"}));
      set_adj(({"double-edged","double","edged","short"}));
      set_short("double-edged gladius");
      set_pshort("double-edged gladiuses");
      set_long("It is double-edged shortsword with a sharp point.\n");
      set_dt(W_IMPALE);
      set_hands(W_ANYH);
      break;
    case 2:
      hit = 15+random(5);
      pen = 17+random(5);
      set_name(({"scramasax","sword"}));
      set_adj(({"curved","single","edged","single-edged"}));
      set_short("curved scramasax");
      set_pshort("curved scramasaxes");
      set_long("It is old designed single-edged curved shortsword.\n");
      set_dt(W_SLASH);
      set_hands(W_ANYH);
      break;
  }
  set_hit(hit);
  set_pen(pen);
  set_wt(W_SWORD);
  add_prop(OBJ_I_VALUE, F_VALUE_WEAPON(hit,pen)*(90+random(21))/100);
}

void
create_weapon()
{
  num = random(3);
  make_sword_low(num);
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
  make_sword_low(num);
  if(h) set_hit(h);
  if(p) set_pen(p);
  if(v) add_prop(OBJ_I_VALUE, v);
}
