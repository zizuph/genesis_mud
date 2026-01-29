#pragma save_binary

#include "/sys/stdproperties.h"
#include "/sys/wa_types.h"
#include "/sys/formulas.h"
#include "/sys/macros.h"
#include "/d/Shire/sys/defs.h"

inherit "/std/weapon";
inherit "/d/Shire/misty/wep/knock_down.c";
inherit "/lib/keep";

int num;

/*
 * this function actually creates weapon
 */
void
make_club_high(int arg)
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
	hit = 27+random(5);
	pen = 30+random(5);
	set_name(({"morning-star","star","morningstar","club"}));
	set_adj(({"spiked","iron","morning"}));
	set_short("spiked morning-star");
	set_pshort("spiked morning-stars");
	set_long("This club consists of spiked iron ball chained to the "+
	  "iron handle.\n");
	set_dt(W_BLUDGEON);
	set_hands(W_ANYH);
	break;
    case 1:
	hit = 23+random(5);
	pen = 31+random(5);
	set_name(({"warhammer","club"}));
	set_adj(({"huge","pick"}));
	set_short("huge warhammer");
	set_pshort("huge warhammers");
	set_long("This hammer-pick has a beak to punch through armour with "+
	  "and a huge hammer head on the back.\n");
	set_dt(W_BLUDGEON | W_IMPALE);
	set_hands(W_ANYH);
	break;
    case 2:
	hit = 29+random(5);
	pen = 30+random(5);
	set_name(({"flail","club"}));
	set_adj(({"spiked","big","iron"}));
	set_short("big spiked flail");
	set_pshort("big spiked flails");
	set_long("This is big flail with spiked iron head.\n");
	set_dt(W_BLUDGEON | W_IMPALE);
	set_hands(W_ANYH);
	break;
    }

    set_hit(hit);
    set_pen(pen);
    set_wt(W_CLUB);
    add_prop(OBJ_I_VALUE, F_VALUE_WEAPON(hit, pen) * (110+random(21)) / 100);
    add_prop(OBJ_I_WEIGHT, F_WEIGHT_DEFAULT_WEAPON(pen, W_CLUB));
}

void
create_weapon()
{
    add_magic_properties();
    add_prop(OBJ_M_NO_BUY, 1);
    num = random(3);
    make_club_high(num);
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
    make_club_high(num);
    if(h) set_hit(h);
    if(p) set_pen(p);
    if(v) add_prop(OBJ_I_VALUE, v);
}
