#include "/d/Terel/include/Terel.h"
#include "../bhunters.h"
#include <tasks.h>

inherit "/std/shadow";

public void remove_poison_shadow()
{
	remove_shadow();
}

public int drink_soft(int amount, int ask)
{
	return 0;
}

public int eat_food(int amount, int ask)
{
	return 0;
}