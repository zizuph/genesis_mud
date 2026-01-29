#pragma save_binary

inherit "/std/weapon";
inherit "/lib/keep";

#include "/sys/stdproperties.h"
#include "/sys/wa_types.h"
#include "/sys/formulas.h"
#include "/sys/macros.h"
#include "/d/Shire/sys/defs.h"

int num;

void
make_pole_high(int arg)
{
    int pen, hit, i;
    string *names;

    if((arg < 0) || (arg > 3)) return;

    names = TO->query_names();
    for (i=0; i<sizeof(names); i++)
    {
	TO->remove_name(names[i]);
    }
    TO->add_name("weapon");

    num = arg;
    switch(arg)
    {
    case 0:
	hit = 21+random(5);
	pen = 28+random(5);
	set_name(({"fauchard","polearm"}));
	set_adj(({}));
	set_short("fauchard");
	set_pshort("fauchards");
	set_long("This polearm has a single-edged blade mounted upon a pole "+
	  "with a bladecatcher. Its end can be used to impale with.\n");
	set_dt(W_SLASH | W_IMPALE);
	set_hands(W_BOTH);
	break;
    case 1:
	hit = 25+random(5);
	pen = 30+random(5);
	set_name(({"guisarme","polearm"}));
	set_adj(({}));
	set_short("guisarme");
	set_long("This polearm has a long concave edge with a hook at the "+
	  "back and its shaft terminates in a spear-head.\n");
	set_dt(W_SLASH | W_IMPALE);
	set_hands(W_BOTH);
	break;
    case 2:
	hit = 24+random(5);
	pen = 36+random(5);
	set_name(({"halberd","polearm"}));
	set_adj(({"standard"}));
	set_short("standard halberd");
	set_pshort("standard halberds");
	set_long("This polearm has a large axe blade, a spear-head at the "+
	  "end and a hook on the back.\n");
	set_dt(W_SLASH | W_IMPALE);
	set_hands(W_BOTH);
	break;
    case 3:
	hit = 21+random(5);
	pen = 32+random(5);
	set_name(({"hammer","polearm"}));
	set_adj(({"luzern"}));
	set_short("luzern hammer");
	set_pshort("luzern hammers");
	set_long("This polearm has a beak to punch through armour, a "+
	  "spear-head at the end and four small points at the back.\n");
	set_dt(W_IMPALE);
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
    num = random(4);
    make_pole_high(num);
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
    make_pole_high(num);
    if(h) set_hit(h);
    if(p) set_pen(p);
    if(v) add_prop(OBJ_I_VALUE, v);
}
