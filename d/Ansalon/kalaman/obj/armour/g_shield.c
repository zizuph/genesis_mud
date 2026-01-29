inherit "/std/armour";
#include <stdproperties.h>
#include <wa_types.h>
#include <formulas.h>
#include <macros.h>
#include "/d/Ansalon/common/defs.h"

inherit "/lib/keep";

void
create_armour()
{
    set_name("shield");

    set_adj("heavy");
    add_adj("golden");

    set_short("heavy golden shield");
    set_long("This large shield is made of the finest " +
      "steel, and is coated with a thin layer of gold that " +
      "sparkles even when there is little light. A winged " +
      "silver dragon design has been artfully worked across " +
      "the face of the shield, giving it an impressive appearance. " +
      "You can 'raiseshield' and 'readyshield'.\n");

    add_prop(OBJ_I_IS_MAGIC_ARMOUR, 1);
    add_prop(MAGIC_AM_ID_INFO,
      ({"This shield has been enchanted to offer better protection " +
	"against attacks.\n",30}));
    add_prop(MAGIC_AM_MAGIC, ({30,"enchantment"}));

    set_ac(45);
    set_at(A_SHIELD);

    add_prop(OBJ_I_WEIGHT, 10000);
    add_prop(OBJ_I_VOLUME, 2500);
    add_prop(OBJ_I_VALUE, F_VALUE_ARMOUR(45));
}

public int *
query_shield_slots()
{
    return (::query_shield_slots() + ({ A_BODY, A_LEGS }) );
}

void
init()
{
    ::init();
    ADA("raiseshield");
    ADA("readyshield");
}

int
raiseshield(string str)
{
    if(str)
	return 0;

    if(!TO->query_worn())
    {
	NF("You have to be wearing the shield to do that.\n");
	return 0;
    }
    write("You raise the heavy golden shield into the air as you " +
      "exult your victory!\n");
    say(QCTNAME(TP) + " raises " +HIS(TP)+ " heavy golden shield " +
      "into the air as " +HE(TP)+ " exults " +HIS(TP)+ " victory.\n");
    return 1;
}

int
readyshield(string str)
{
    if(str)
	return 0;

    if(!TO->query_worn())
    {
	NF("You have to be wearing the shield to do that.\n");
	return 0;
    }

    write("You ready the heavy golden shield in preparation for " +
      "battle!\n");
    say(QCTNAME(TP) + " brings " +HIS(TP)+ " heavy golden " +
      "shield to the ready, the silver dragon emblem sparkling " +
      "brightly in the light.\n");
    return 1;
}
