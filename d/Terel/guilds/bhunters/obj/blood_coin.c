inherit "/std/object";

#include <stdproperties.h>

public void create_object()
{
	set_name("rectangle");
	add_name("coin");
	set_short("small black rectangle");
	set_adj(({"steel", "small", "black", "blood"}));
	set_long("A long piece of black metal, with human skull engraved on it. Someone pierced a small hole " +
			"through the middle of the rectangle, so it can be threaded on a string or tape of some kind.\n" +
			"It feels heavier then it looks.\n");
	add_prop(OBJ_I_VALUE, 0);
	add_prop(OBJ_I_WEIGHT, 100);
	add_prop(OBJ_I_VOLUME, 20);
	add_prop(OBJ_M_NO_SELL, 1);
	add_prop(OBJ_M_NO_BUY, 1);
}

public int is_blood_money()
{
	return 1;
}