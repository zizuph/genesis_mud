/*
 * Generic armours, such as helms, bracers, and greaves,
 * found on hidden corpses. 
 * They are very low powered and provide no magical
 * abilities, despite the descriptions.
 * -- Finwe, July 2001
 */
#pragma save_binary

inherit "/std/armour";
inherit "/lib/keep";

#include "/sys/stdproperties.h"
#include "/sys/wa_types.h"
#include "/sys/formulas.h"
#include "/sys/macros.h"
#include "/d/Shire/cypress/sys/defs.h"

#define MAX_ARMOURS 3
#define ARMOUR_CLASS random(6)+6

int num;

void
make_armour(int arg)
{
    int i;
    string *names;

    if((arg < 0) || (arg > 3)) return;

    names = TO->query_names();
    for (i=0; i<sizeof(names); i++)
    {
	TO->remove_name(names[i]);
    }
    TO->add_name("armour");

    num = arg;
    switch(arg)
    {
        case 0:
            set_name("cracked helmet");
            add_name("helmet");
            set_adj(({"steel"}));
            set_short("cracked steel helmet");
            set_pshort("cracked steel helmets");
            set_long("This "+short()+" is made from some plates " +
                "of steel. It is cracked down the side and dull.\n");
            set_am( ({ -3, 0, 3 }) );
            set_at(A_HEAD);

        break;

        case 1:
            set_name(({"tempered bracers", "bracers"}));
            set_adj(({"tempered", "iron"}));
            set_short("pair of tempered iron bracers");
            set_pshort("pairs of tempered iron bracerses");
            set_long("The "+short()+" are battered looking. They " +
                "are made of tempered iron and are rusty. The "+
                short()+" cover and offer protection to the arms.\n");
            set_am( ({ -3, 0, 3 }) );
            set_at(A_ARMS);
        break;

        case 2:
            set_name(({"brass greaves", "greaves"}));
            set_adj(({"battered", "ancient"}));
            set_short("pair of battered ancient greaves");
            set_pshort("pairs of battered ancient greaveses");
            set_long("The "+short()+" are ancient looking. They " +
                "are dull and unpolished. The "+short()+" cover " +
                "and offer protection to the legs.\n");
            set_am( ({ -3, 0, 3 }) );
            set_at(A_LEGS);
        break;

    }
    
}

void
create_armour()
{
    set_ac(ARMOUR_CLASS);
    num = random(MAX_ARMOURS);
    make_armour(num);
    set_keep();
}
