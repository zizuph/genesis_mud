#pragma save_binary

inherit "/std/weapon";
inherit "/lib/keep";

#include "/sys/stdproperties.h"
#include "/sys/wa_types.h"
#include "/sys/formulas.h"
#include "/sys/macros.h"
#include "/d/Rhovanion/defs.h"
#include "knock_down.h"

int num;

/*
 * this function actually creates weapon
 */
void
make_club_sup(int arg)
{
  int pen, hit;

  if((arg < 0) || (arg > 1)) return;

  num = arg;
  switch(arg)
  {
    case 0:
      hit = 32+random(5);
      pen = 39+random(8);
      set_name(({"morning-star","star","morningstar","club"}));
      set_adj(({"double","spiked","iron","morning"}));
      set_short("double morning-star");
      set_pshort("double morning-stars");
      set_long("This club has two spiked iron balls chained to the "+
               "iron handle.\n");
      set_dt(W_BLUDGEON);
      set_hands(W_ANYH);
      break;
    case 1:
      hit = 35+random(5);
      pen = 41+random(9);
      set_name(({"club"}));
      set_adj(({"heavy","steel"}));
      set_short("heavy steel club"); set_pshort("heavy steel clubs");
      set_long("It is good to have this steel club. It may be very "+
            "uncomfortable for your enemy when you hit his head with it.\n");
      set_dt(W_BLUDGEON);
      set_hands(W_ANYH);
      break;
  }
  set_hit(hit);
  set_pen(pen);
  set_wt(W_CLUB);
  add_prop(OBJ_I_VALUE, F_VALUE_WEAPON(hit, pen) * (120+random(21)) / 100);
  add_prop(OBJ_I_WEIGHT, F_WEIGHT_DEFAULT_WEAPON(pen, W_CLUB));
}

void
create_weapon()
{
  add_magic_properties();
  num = random(2);
  make_club_sup(num);
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
  make_club_sup(num);
  if(h) set_hit(h);
  if(p) set_pen(p);
  if(v) add_prop(OBJ_I_VALUE, v);
}

void remove_broken()
{
  if(num == 1) return;
  ::remove_broken();
}

static int
set_dull(int du)
{
  return ::set_dull(du);
}
