// -*-C++-*-
// file name: worm_armor.c
// file name: ~Avenir/common/dark/obj/worm_armour
// creator(s):  Boriska 
// last update: Mar 14 1995
// purpose:     Armor set that can be made from worm leftovers in
//              ~Avenir/common/dark/lair/entrance.
// note:        magic

#include <wa_types.h>
#include <stdproperties.h>
#include <macros.h>
#include "/d/Avenir/include/worm.h"

inherit "/std/armour";

// the order is HEAD, BODY, TAIL from worm.h
static string *names = ({"helmet", "robe", "shield" }); 

static string *shorts = ({"scarlet-gold scaled helmet",
			  "scarlet-gold soft robe",
			  "scarlet-gold scaled shield"});

static string *longs = ({
  "Fine and light helmet made from thin yet strong material.\n",
  "This unusually colored robe is sparkling with golden light.\n",
  "Unusually light shield having an aura of ancient magic about it.\n",
});

static int part, *a_types = ({ A_HEAD, A_ROBE, A_SHIELD });

void
create_armour()
{
    if ( !IS_CLONE )
	return;

    //these provide correct descriptions when recovering the armor
    set_name("armour");
    set_short("armour");
    set_long("An armour.\n");
    set_af(this_object()); // need for wear/remove func
}

// has to be called when cloning the armor in room code
void
configure_me(int p)
{
    if ( p < 0 || p >= sizeof(names) )
	part = 0;
    else
	part = p;

    set_name(names[p]);
    set_short(shorts[p]);
    set_long(longs[p]);
    add_adj( ({"scarlet-gold", "light"}) );
    
    if (p == 1)
	add_adj(({"soft"}));
    else
	add_adj(({"scaled"}));
	
    set_ac (30);

    // Thin armour provides much higher resistance to
    //impale than to slash and bludgeon.
    set_am (({5, -2, -3}));
    set_at ( a_types[p] );

    add_prop (OBJ_M_NO_BUY, "This armour is not for sale.\n");
    add_prop (OBJ_I_WEIGHT, 4444);
    add_prop (OBJ_I_VOLUME, 3333);
    add_prop (OBJ_I_VALUE,  2222);

    add_prop (MAGIC_AM_MAGIC, ({ 40, "enchantment" }) );

    add_prop (MAGIC_AM_ID_INFO , ({40,
	"You notice a trace of non-human magic about that piece of armour.\n" +
	"You feel it could help you to stand against forces of nature.\n"}) );

    // is is made from worm skin, so its resistant to some things
    add_prop( OBJ_I_IS_MAGIC_ARMOUR, 1);
    add_prop( MAGIC_I_RES_ACID, 30 );
    add_prop( MAGIC_I_RES_FIRE, 25 );

    set_likely_cond (8);  // another drawback, is worn down faster then default
}

int
wear(object ob)
{
    object tp = environment(ob);

    if (living(tp))
	tp->add_magic_effect(this_object());

    return 0;
}

int
remove(object to)
{
    object tp = query_worn();

    if (living(tp))
	tp->remove_magic_effect(this_object());

    return 0;
}

void
init_recover(string arg)
{
    string foo;
    int p;

    sscanf( arg, "%shjhj#%d%s", foo, p, foo);
    init_arm_recover(arg);
    configure_me(p);  
}

string
query_recover()
{
    return MASTER + ":" +
	query_arm_recover() +
	sprintf("hjhj#%d", part);
}
