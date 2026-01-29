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
make_pole_low(int arg)
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
	hit = 32+random(5);
	pen = 8+random(5);
	set_name(({"quarterstaff","pole","polearm"}));
	set_adj(({"long","stout"}));
	set_short("quarterstaff");
	set_pshort("quarterstaffs");
	set_long("It is simply a long and stout pole. Very easy to hit with it.\n");
	set_dt(W_BLUDGEON);
	set_hands(W_BOTH);
	break;
    case 1:
	hit = 20+random(5);
	pen = 14+random(5);
	set_name(({"spear","polearm"}));
	set_adj(({"strong"}));
	set_short("strong spear");
	set_pshort("strong spears");
	set_long("It has sharp steel point for thrusting or hurling.\n");
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
    num = random(2);
    make_pole_low(num);
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
    make_pole_low(num);
    if(h) set_hit(h);
    if(p) set_pen(p);
    if(v) add_prop(OBJ_I_VALUE, v);
}
