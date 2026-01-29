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
make_club_low(int arg)
{
  int pen, hit;

  if((arg < 0) || (arg > 2)) return;

  num = arg;
  switch(arg)
  {
    case 0:
      hit = 14+random(5);
      pen = 8+random(6);
      set_name(({"stick","club"}));
      set_adj(({"wooden","big","simple"}));
      set_short("big wooden stick");
      set_pshort("big wooden sticks");
      set_long("This is simple big wooden stick used as a club.\n");
      set_dt(W_BLUDGEON);
      set_hands(W_ANYH);
      break;
    case 1:
      hit = 18+random(5);
      pen = 15+random(5);
      set_name(({"club"}));
      set_adj(({"wooden","spiked"}));
      set_short("spiked club");
      set_pshort("spiked clubs");
      set_long("This is wooden club with metal spikes for bigger damage.\n");
      set_dt(W_BLUDGEON | W_IMPALE);
      set_hands(W_ANYH);
      break;
    case 2:
      hit = 16+random(5);
      pen = 18+random(5);
      set_name(({"flail","club"}));
      set_adj(({"wooden","small"}));
      set_short("wooden flail");
      set_pshort("wooden flails");
      set_long("This is small wooden flail quite common on a farm.\n");
      set_dt(W_BLUDGEON);
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
  make_club_low(num);
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
  make_club_low(num);
  if(h) set_hit(h);
  if(p) set_pen(p);
  if(v) add_prop(OBJ_I_VALUE, v);
}
