inherit "/std/object";
#include "defs.h"

int strength;

void here_is_the_dwarf(object saver);


create_object()
{
    set_name("slab");
    add_name("rock");
    add_adj(({"huge", "golden", "gold"}));
    set_short("huge slab of gold");
    set_long(
	"You are looking at the largest slab of gold in this room. " +
	"It is quite large, in fact, it is cubed with sides around " +
	"1-2 meters (3'-6'). It would be impossible to carry this " +
	"around, unless you had at least a band of trolls to help " +
    "you.  Down here in the mines, it should feel cold.\n");
    add_prop(MAGIC_AM_MAGIC, ({ 50, "conjuration" }));
    add_prop(MAGIC_AM_ID_INFO, ({
	"It seems somehow to radiate magic!\n", 1,
	"The magic seems to be of conjuration.\n", 50,
	"You feel the presence of a living body inside it!\n", 75,
	"It seems that something evil has imprisoned a dwarf " +
	    "inside the golden slab of rock!\n", 90,
	"You should consider dispelling the slab to " + 
	    "free the poor soul.\n", 95
	    }));
    add_prop(OBJ_I_VOLUME, 120 * 150 * 189);
    add_prop(OBJ_I_WEIGHT, query_prop(OBJ_I_VOLUME) * 6);
    add_prop(OBJ_I_VALUE,  query_prop(OBJ_I_VOLUME) * 10);
    strength = 100;
}

/*
 * The only way to dispel the magic is in this
 * function. The power should be a number from
 * 0 to 100.
 */
int
dispel_magic(int power)
{
    strength -= random(power);
    if (strength <= 0) {
	tell_room(ETO, "The room explodes in a flash of golden sparks!\n" +
		  "The huge slab of rock vanishes in front of you!\n");
    set_alarm(3.0, 0.0, &here_is_the_dwarf(TP));
	return 1;
    } else {
      tell_room(ETO, "The room radiates briefly in golden sparks!\n");
      return 0;
    }
}

void
here_is_the_dwarf(object saver)
{
    tell_room(ETO, "A startling view appears from within the before "+
	           "slab of gold!\nA dwarf appears from it!!\n");
    TO->remove_object();
    CONTROL->register_alchemist(saver, ETO);
}
