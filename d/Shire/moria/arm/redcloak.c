#include "defs.h"
#include <stdproperties.h>
#include <macros.h>
#include <wa_types.h>
#include <formulas.h>
#include <ss_types.h>

#define DEXRISE     10
#define QRISE	   100

// NOTE! This piece of armour is not in the game. 

inherit BASE_ARMOUR;

object wearer;
int qrise;
int dexrise;

CONSTRUCT_ARMOUR
{
    set_name( ({"cloak"}) );
    set_short("red cloak");
    set_adj( ({ "red", "magic", "velvet", "magical" }) );
    set_long(
	"It is a beautiful dark red cloak of velvet. "+
	"Obviously robbed from an Elven Lord of high rank.\n"
    );
    set_ac( 12 );
    set_at( A_ROBE );
    set_am( ({ -3, 2, 1}) );
    set_af( this_object() );

    add_prop(OBJ_I_WEIGHT, 3500);
    add_prop(OBJ_I_VALUE,  2*12*12+4*12); /* Price: 2 g 4 s */
    add_prop(OBJ_I_VOLUME, 1200);
    add_prop(MAGIC_AM_MAGIC, ({ 20, "enchantment" }));
    add_prop(MAGIC_AM_ID_INFO, ({
	"This is a beatiful magically enhanced cloak.\n", 1,
	"This is a Cloak of Speed, manifactured by the Elves " +
	    "of Lothlorien in the end of the Second Age.\n", 20
    }));
    add_prop(OBJ_I_IS_MAGIC_ARMOUR, 1);
}

wear(object to)
{
    wearer = TP;

    if(wearer->query_npc()) {
	dexrise = 30;
	qrise	= 100;
    } else {
	dexrise = 1+random(DEXRISE);
	qrise	= 1+random(QRISE);
    }

    write("You find yourself quite young and agile again!\n");
    say(QCTNAME(wearer)+" suddenly looks younger and more agile!\n",wearer);

    ADD_STAT(wearer, SS_DEX, dexrise);
    ADD_PROP(wearer, LIVE_I_QUICKNESS, qrise);
}

remove(object to)
{
    if(!living(wearer))
    {
	wearer = 0;
	return;
    }

    write("You feel normal in age and dexterity again.\n");
    tell_room(ENV(wearer),
	QCTNAME(wearer)+" doesn't look so dexterious no more.\n",wearer);
    ADD_STAT(wearer, SS_DEX, -dexrise);
    ADD_PROP(wearer, LIVE_I_QUICKNESS, -qrise);
    wearer = 0;
}

/*
 * This makes this armour non-recoverable, making the
 * players wish to visit the dreadful mines of Moria again.. :-)
 */
string
query_recover()
{
    return 0;
}

