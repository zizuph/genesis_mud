#pragma save_binary

inherit "/std/armour";
inherit "/lib/keep";

#include <formulas.h>
#include <wa_types.h>
#include "/d/Shire/sys/defs.h"

int num;

/*
 * this function actually creates armour
 */
void
make_shield_high(int arg)
{
    int ac;

    if((arg < 0) || (arg > 6)) return;

    num = arg;
    switch(arg)
    {
    case 0:
	ac = 25+random(4);
	set_name("shield");
	set_short("small alloyed steel shield");
	set_adj(({"small","steel","alloyed"}));
	set_long("This is a small shield from alloyed steel.\n");
	break;
    case 1:
	ac = 23+random(4);
	set_name("shield");
	set_short("tempered iron shield");
	set_adj(({"tempered","iron","medium"}));
	set_long("This medium sized shield is made of tempered iron.\n");
	break;
    case 2:
	ac = 25+random(4);
	set_name("shield");
	set_short("steel kite shield");
	set_pshort("steel kite shields");
	set_adj(({"steel","kite","medium"}));
	set_long("This medium shield is made of steel.\n");
	break;
    case 3:
	ac = 27+random(4);
	set_name("shield");
	set_short("steel shield");
	set_adj(({"steel","kite","alloyed"}));
	set_long("This kite shield is made of alloyed steel.\n");
	break;
    case 4:
	ac = 20+random(4);
	set_name("shield");
	set_short("big iron shield");
	set_adj(({"big","iron"}));
	set_long("This is a big iron shield.\n");
	break;
    case 5:
	ac = 22+random(5);
	set_name("shield");
	set_short("iron footmans shield");
	set_adj(({"big","iron","footmans","tempered"}));
	set_long("This big shield is made of tempered iron.\n");
	break;
    case 6:
	ac = 24+random(5);
	set_name("shield");
	set_short("huge bronze shield");
	set_adj(({"huge","bronze"}));
	set_long("This is a really huge bronze shield.\n");
	break;
    }

    set_ac(ac);
    set_at(A_SHIELD);
    if(arg > 5)
    {
	add_prop(OBJ_I_WEIGHT, ac*142*(180+random(21)) / 100);
	add_prop(OBJ_I_VOLUME, ac*142*(130+random(21)) / 100);
	add_prop(OBJ_I_VALUE, F_VALUE_ARMOUR(ac) * (130+random(21)) / 100);
    }
    else if(arg > 3)
    {
	add_prop(OBJ_I_WEIGHT, ac*142*(150+random(21)) / 100);
	add_prop(OBJ_I_VOLUME, ac*142*(110+random(21)) / 100);
	add_prop(OBJ_I_VALUE, F_VALUE_ARMOUR(ac) * (110+random(21)) / 100);
    }
    else if(arg > 0)
    {
	add_prop(OBJ_I_WEIGHT, ac*142*(120+random(21)) / 100);
	add_prop(OBJ_I_VOLUME, ac*142*(90+random(21)) / 100);
	add_prop(OBJ_I_VALUE, F_VALUE_ARMOUR(ac) * (110+random(21)) / 100);
    }
    else
    {
	add_prop(OBJ_I_WEIGHT, ac*142*(80+random(21)) / 100);
	add_prop(OBJ_I_VOLUME, ac*142*(60+random(21)) / 100);
	add_prop(OBJ_I_VALUE, F_VALUE_ARMOUR(ac) * (90+random(21)) / 100);
    }
}

void
create_armour()
{
    num = random(7);
    make_shield_high(num);
}

int *
query_shield_slots()
{
    if(num > 5)
	return (::query_shield_slots() + ({ A_BODY }) );
    return ::query_shield_slots();
}

string
query_recover()
{
    return MASTER+":"+query_arm_recover()+"#n#"+num+"#a#"+query_ac()+
    "#v#"+query_prop(OBJ_I_VALUE)+"#";
}

void
init_recover(string arg)
{
    string foobar;
    int a,v;

    init_arm_recover(arg);
    sscanf(arg, "%s#n#%d#a#%d#v#%d#%s", foobar, num, a, v, foobar);
    make_shield_high(num);
    if(a) set_ac(a);
    if(v) add_prop(OBJ_I_VALUE, v);
}
