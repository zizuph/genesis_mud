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
make_knife_low(int arg)
{
  int pen, hit;

  if((arg < 0) || (arg > 14)) return;

  num = arg;
  switch(arg)
  {
    case 0:
      hit = 6+random(5);
      pen = 7+random(5);
      set_name(({"knife"}));
      set_pname(({"knives","weapons"}));
      set_adj(({"small"}));
      set_short("small knife");
      set_pshort("small knives");
      set_long("An ordinary knife with a single cutting edge. "+
		"Only a little smaller.\n");
      set_dt(W_SLASH);
      set_hands(W_ANYH);
      break;
    case 1:
      hit = 8+random(5);
      pen = 9+random(5);
      set_name(({"knife"}));
      set_pname(({"knives","weapons"}));
      set_adj(({}));
      set_short("knife");
      set_pshort("knives");
      set_long("An ordinary knife with a single cutting edge.\n");
      set_dt(W_SLASH);
      set_hands(W_ANYH);
      break;
    case 2:
      hit = 10+random(5);
      pen = 11+random(5);
      set_name(({"knife"}));
      set_pname(({"knives","weapons"}));
      set_adj(({"large"}));
      set_short("large knife");
      set_pshort("large knives");
      set_long("An ordinary knife with a single cutting edge. "+
		"Only a little larger.\n");
      set_dt(W_SLASH);
      set_hands(W_ANYH);
      break;
    case 3:
      hit = 8+random(5);
      pen = 10+random(5);
      set_name(({"knife"}));
      set_pname(({"knives","weapons"}));
      set_adj(({"ballock"}));
      set_short("ballock knife");
      set_pshort("ballock knives");
      set_long("A knife with two large protuberances where the grip joins blade.\n");
      set_dt(W_SLASH);
      set_hands(W_ANYH);
      break;
    case 4:
      hit = 10+random(5);
      pen = 10+random(5);
      set_name(({"dagger","knife"}));
      set_pname(({"daggers","knives","weapons"}));
      set_adj(({"small"}));
      set_short("small dagger");
      set_pshort("small daggers");
      set_long("It has two cutting edges and a blade tapering to a point.\n");
      set_dt(W_SLASH | W_IMPALE);
      set_hands(W_ANYH);
      break;
    case 5:
      hit = 12+random(5);
      pen = 12+random(5);
      set_name(({"dagger","knife"}));
      set_pname(({"daggers","knives","weapons"}));
      set_adj(({}));
      set_short("dagger");
      set_pshort("daggers");
      set_long("It has two cutting edges and a blade tapering to a point.\n");
      set_dt(W_SLASH | W_IMPALE);
      set_hands(W_ANYH);
      break;
    case 6:
      hit = 14+random(5);
      pen = 14+random(5);
      set_name(({"dagger","knife"}));
      set_pname(({"daggers","knives","weapons"}));
      set_adj(({"big"}));
      set_short("big dagger");
      set_pshort("big daggers");
      set_long("It has two cutting edges and a blade tapering to a point.\n");
      set_dt(W_SLASH | W_IMPALE);
      set_hands(W_ANYH);
      break;
    case 7:
      hit = 12+random(5);
      pen = 13+random(5);
      set_name(({"dagger","knife"}));
      set_pname(({"daggers","knives","weapons"}));
      set_adj(({"rondel"}));
      set_short("rondel dagger");
      set_pshort("rondel daggers");
      set_long("This dagger has round discs of metal for a pommel and "+
		"crossguard.\n");
      set_dt(W_SLASH | W_IMPALE);
      set_hands(W_ANYH);
      break;
    case 8:
      hit = 12+random(5);
      pen = 13+random(5);
      set_name(({"dagger","knife"}));
      set_pname(({"daggers","knives","weapons"}));
      set_adj(({"swiss"}));
      set_short("swiss dagger");
      set_pshort("swiss daggers");
      set_long("This dagger has half-moon shaped pommel and crossguard.\n");
      set_dt(W_SLASH | W_IMPALE);
      set_hands(W_ANYH);
      break;
    case 9:
      hit = 12+random(5);
      pen = 11+random(5);
      set_name(({"dirk","knife"}));
      set_pname(({"dirks","knives","weapons"}));
      set_adj(({}));
      set_short("dirk");
      set_pshort("dirks");
      set_long("This is an improved version of the ballock knife.\n");
      set_dt(W_SLASH | W_IMPALE);
      set_hands(W_ANYH);
      break;
    case 10:
      hit = 12+random(5);
      pen = 12+random(5);
      set_name(({"gauche","knife"}));
      set_pname(({"gauches","knives","weapons"}));
      set_adj(({"main"}));
      set_short("main gauche");
      set_pshort("main gauches");
      set_long("A dagger with a large downward curved crossguard, used in "+
		"the left hand usually in conjunction with a sword.\n");
      set_dt(W_SLASH | W_IMPALE);
      set_hands(W_LEFT);
      break;
    case 11:
      hit = 14+random(5);
      pen = 12+random(5);
      set_name(({"cinquedea","knife"}));
      set_pname(({"cinquedeas","knives","weapons"}));
      set_adj(({}));
      set_short("cinquedea");
      set_pshort("cinquedeas");
      set_long("A large and broad dagger. It can be very dangerous.\n");
      set_dt(W_SLASH | W_IMPALE);
      set_hands(W_ANYH);
      break;
    case 12:
      hit = 10+random(5);
      pen = 14+random(5);
      set_name(({"stilleto","knife"}));
      set_pname(({"stilletos","knives","weapons"}));
      set_adj(({}));
      set_short("stilleto");
      set_pshort("stilletos");
      set_long("It is a thin and narrow bladed weapon with very sharp point.\n");
      set_dt(W_IMPALE);
      set_hands(W_ANYH);
      break;
    case 13:
      hit = 10+random(5);
      pen = 14+random(5);
      set_name(({"misericord","knife"}));
      set_pname(({"misericords","knives","weapons"}));
      set_adj(({}));
      set_short("misericord");
      set_pshort("misericords");
      set_long("A stilleto used to give the coup-de-grace to a stunned opponent.\n");
      set_dt(W_IMPALE);
      set_hands(W_ANYH);
      break;
    case 14:
      hit = 10+random(5);
      pen = 12+random(5);
      set_name(({"bodkin","knife"}));
      set_pname(({"bodkins","knives","weapons"}));
      set_adj(({"small"}));
      set_short("bodkin");
      set_pshort("bodkins");
      set_long("A small stilleto without the edge.\n");
      set_dt(W_IMPALE);
      set_hands(W_ANYH);
      break;
  }
  set_hit(hit);
  set_pen(pen);
  set_wt(W_KNIFE);
  add_prop(OBJ_I_VALUE, F_VALUE_WEAPON(hit, pen) * (90+random(21)) / 100);
}

void
create_weapon()
{
  num = random(15);
  make_knife_low(num);
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
  make_knife_low(num);
  if(h) set_hit(h);
  if(p) set_pen(p);
  if(v) add_prop(OBJ_I_VALUE, v);
}
