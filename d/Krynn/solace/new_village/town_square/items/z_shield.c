/*
** Zahrtok's Shield
** Created By Leia
** June 22, 2005
*/

/* 
** Last Updated By:
** Leia
** July 1, 2005
*/

inherit "/std/armour";
#include <stdproperties.h>
#include <wa_types.h>
#include <formulas.h>
#include <macros.h>

void
create_armour()
{
    set_name("shield");

    set_adj("heavy");
    add_adj("steel");

    set_short("heavy steel shield");
    set_long("This is a large, heavy alloyed-steel shield. The shield has two very tight leather straps to hold it in place on the arm of the wearer. The shield smells terrible. You recognize it as the smell of a goblin.\n");

    set_ac(20);
    set_at(A_SHIELD);

    add_prop(OBJ_I_WEIGHT, 5000);
    add_prop(OBJ_I_VOLUME, 2500);
    add_prop(OBJ_I_VALUE,F_VALUE_ARMOUR(35));
}
