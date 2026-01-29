#pragma save_binary

inherit "/std/weapon";
inherit "/lib/keep";

#include "/sys/stdproperties.h"
#include "/sys/wa_types.h"
#include "/sys/macros.h"
#include "/sys/formulas.h"
#include "/d/Shire/sys/defs.h"

int num;

/*
 * this function actually creates weapon
 */
void
make_sword_med(int arg)
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
	hit = 22+random(5);
	pen = 19+random(7);
	set_name(({"estoc","sword"}));
	set_adj(({"iron","thrusting"}));
	set_short("iron estoc");
	set_pshort("iron estocs");
	set_long("It is without edge, thrusting only sword.\n");
	set_dt(W_IMPALE);
	set_hands(W_BOTH);
	break;
    case 1:
	hit = 27+random(7);
	pen = 19+random(5);
	set_name(({"longsword","sword"}));
	set_adj(({"early","slashing"}));
	set_short("early longsword");
	set_pshort("early longswords");
	set_long("It is early slashing longsword without point.\n");
	set_dt(W_SLASH);
	set_hands(W_ANYH);
	break;
    case 2:
	hit = 27+random(7);
	pen = 19+random(5);
	set_name(({"scimitar","sword"}));
	set_adj(({"curved","light","single","edged","single-edged"}));
	set_short("curved scimitar");
	set_pshort("curved scimitars");
	set_long("It is light curved single-edged slashing sword.\n");
	set_dt(W_SLASH);
	set_hands(W_ANYH);
	break;
    case 3:
	hit = 20+random(5);
	pen = 23+random(5);
	set_name(({"falchion","sword"}));
	set_adj(({"heavy","single","edged","single-edged"}));
	set_short("heavy falchion");
	set_pshort("heavy falchions");
	set_long("It is curved single-edged, heavy slashing sword.\n");
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
    num = random(4);
    make_sword_med(num);
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
    make_sword_med(num);
    if(h) set_hit(h);
    if(p) set_pen(p);
    if(v) add_prop(OBJ_I_VALUE, v);
}
