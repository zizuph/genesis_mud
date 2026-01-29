#pragma save_binary

inherit "/std/armour";
inherit "/lib/keep";

#include <wa_types.h>
#include <formulas.h>
#include "/d/Shire/sys/defs.h"

int num;

/*
 * this function actually creates armour
 */
void
make_shield_sup(int arg)
{
    int ac;

    if((arg < 0) || (arg > 4)) return;

    num = arg;
    switch(arg)
    {
    case 0:
	ac = 27+random(4);
	set_name("shield");
	set_short("alloyed steel shield");
	set_pshort("alloyed steel shields");
	set_adj(({"steel","kite","alloyed"}));
	set_long("This kite shield is made of alloyed steel. The top of " +
        "the shield is rounded, with the bottom forming a point. It " +
        "curves inward to enclose the body.\n");
	break;
    case 1:
	ac = 25+random(4);
	set_name("shield");
	set_short("big tempered iron shield");
	set_pshort("big tempered iron shields");
	set_adj(({"big","iron","tempered"}));
	set_long("This shield is made of tempered iron. It is round and " +
        "plain looking. Dents are visible across the edges where it " +
        "has been hit during many battles.\n");
	break;
    case 2:
	ac = 22+random(4);
	set_name("shield");
	set_short("big steel shield");
	set_pshort("big steel shields");
	set_adj(({"steel","big"}));
	set_long("This big shield is made of steel. It is rectangular shaped " +
        "and flat. There is dried blood smeared across the front of the shield.\n");
	break;
    case 3:
	ac = 34+random(5);
	set_name("shield");
	set_short("huge mithril shield");
	set_pshort("huge mithril shields");
	set_adj(({"huge","mithril"}));
	set_long("This huge mithril shield can cover you almost perfectly. " +
        "It is light and polished to a bright shine. There are no " +
        "visible marks or scratches on the surface, and looks like it was " +
        "just forged yesterday.\n");
	break;
    case 4:
	ac = 32+random(5);
	set_name("shield");
	set_short("massive steel shield");
	set_pshort("massive steel shields");
	set_adj(({"massive","steel"}));
	set_long("This shield made of alloyed steel offers good protection. " +
        "It is long and oval shaped. A large spike is set on the middle " +
        "of the shield.\n");
	break;
    }

    set_ac(ac);
    set_at(A_SHIELD);
    if(arg > 2)
    {
	add_prop(OBJ_I_WEIGHT, ac*142*(180+random(21)) / 100);
	add_prop(OBJ_I_VOLUME, ac*142*(130+random(21)) / 100);
	add_prop(OBJ_I_VALUE, F_VALUE_ARMOUR(ac) * (130+random(21)) / 100);
    }
    else if(arg > 0)
    {
	add_prop(OBJ_I_WEIGHT, ac*142*(150+random(21)) / 100);
	add_prop(OBJ_I_VOLUME, ac*142*(110+random(21)) / 100);
	add_prop(OBJ_I_VALUE, F_VALUE_ARMOUR(ac) * (110+random(21)) / 100);
    }
    else 
    {
	add_prop(OBJ_I_WEIGHT, ac*142*(120+random(21)) / 100);
	add_prop(OBJ_I_VOLUME, ac*142*(90+random(21)) / 100);
	add_prop(OBJ_I_VALUE, F_VALUE_ARMOUR(ac) * (110+random(21)) / 100);
    }
}

void
create_armour()
{
    num = random(5);
    make_shield_sup(num);
    set_keep();
}

int *
query_shield_slots()
{
    if(num > 2)
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
    make_shield_sup(num);
    if(a) set_ac(a);
    if(v) add_prop(OBJ_I_VALUE, v);
}
