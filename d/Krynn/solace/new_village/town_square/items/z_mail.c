/*
** Zahrtok's Chainmail
** Created By Leia
** June 22, 2005
*/

/* 
** Last Updated By:
** Leia
** July 1, 2005
*/

inherit "/std/armour";
#include "/sys/wa_types.h"
#include "/sys/stdproperties.h"
#include <formulas.h>
#include <macros.h>

void
create_armour()
{
    set_name("chainmail");
    add_name("mail");
    set_short("dark alloyed-steel chainmail");
    set_pshort("dark alloyed-steel chainmails");
    set_long("This is a set of dark alloyed-steel chainmail. The metal is smooth and cold to the touch. It is held together by leather straps, and it smells disgusting. You recognize the smell as that of a goblin.\n");
    set_adj("dark");
    add_adj("alloyed-steel");
    add_adj("alloyed steel");
    set_ac(38);
    set_am(({-2, 3, 1}));
    set_at(A_BODY);
    add_prop(OBJ_I_VALUE, F_VALUE_ARMOUR(55));
    add_prop(OBJ_I_VOLUME, 3000);
    add_prop(OBJ_I_WEIGHT, 2500);
}
