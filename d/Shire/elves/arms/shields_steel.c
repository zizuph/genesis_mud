/*
 * Random shields for traveling elves
 * Adapted from /d/Shire/misty/arm/shield_sup.c
 * Finwe, February 2018
 */
#pragma save_binary

inherit "/std/armour";
inherit "/lib/keep";

#include <wa_types.h>
#include <formulas.h>
#include "/d/Shire/sys/defs.h"

int num;
int ac;
int max_shields = 3;

/*
 * this function actually creates armour
 */
void
make_shield_sup(int arg)
{
    int ac;

    if((arg < 0) || (arg > max_shields)) return;

    num = arg;
    switch(arg)
    {
        case 0:
            set_name("shield");
            set_short("large tower shield");
            set_pshort("large tower shields");
            set_adj(({"large","tower"}));
            set_long("This is a " + short() + ". It was forged of high-steel " +
                "by the elves of Middle-earth. The shield is rectangular in " +
                "shape and fits over your arm. It is curves inward and " +
                "protects most of your body.\n");
            break;
        case 1:
            set_name("shield");
            set_short("broad steel shield");
            set_pshort("broad steel shields");
            set_adj(({"broad","steel"}));
            set_long("This " + short() + " was forged from steel by the " +
                "elves of Middle-earth in ages past. It is " +
                "rectangular shaped with rounded corners. At the top and " +
                "centered on the shield is a crescent moon. Beneath the " +
                "moon is a sun, and beneath the sun is a heart. The shield " +
                "is polished, and has a few visible dents around the edges.\n");
            break;
        case 2:
            set_name("shield");
            set_short("grand steel shield");
            set_pshort("grand steel shields");
            set_adj(({"grand","steel"}));
            set_long("This " + short() + " was forged by the elves of " +
                "Middle-earth. It is long and oval shaped and designed " +
                "to protect most of the body. The shield is plain except " +
                "for a large sun engraved in the center.\n");
            break;
        case 3:
            set_name("shield");
            set_short("round steel shield");
            set_pshort("round huge shields");
            set_adj(({"round","steel"}));
            set_long("This " + short() + " is crafted of high-steel by " +
                "the elves of Middle-earth. A large star is engraved " +
                "into the center of the shield. The shield is polished " +
                "and bears a few scratches and nicks around the edge.\n");
            break;
    }

    set_ac(ac);
    set_at(A_SHIELD);

    if(arg > max_shields)
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
    ac = 32 + random(5);
    make_shield_sup(num);
    set_keep();
}

int *
query_shield_slots()
{
    if(num > 2)
    {
    	return (::query_shield_slots() + ({ A_BODY }) );
    }
    return ::query_shield_slots();
}

string
query_recover()
{
    return MASTER + ":" + query_arm_recover() + 
        "#n#" + num + 
        "#a#" + query_ac() + 
        "#v#" + query_prop(OBJ_I_VALUE) + "#";
}

void
init_recover(string arg)
{
    string foobar;
    int a,v;

    init_arm_recover(arg);
    sscanf(arg, "%s#n#%d#a#%d#v#%d#%s", foobar, num, a, v, foobar);
    make_shield_sup(num);

    if(a) 
    {
        set_ac(a);
    }

    if(v)
    {   
        add_prop(OBJ_I_VALUE, v);
    }
}
