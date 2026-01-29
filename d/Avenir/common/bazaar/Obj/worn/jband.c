// ruby-eyed band for jadestone doll
//    -Ilyian, May 1995
//    -Updated, Cirion, Aug 1996 - made the ring provide some
//                                 magic resistance
//    Feb 2009 Lucius: Minor cleanups / fixups.
//    May 2013 Petros: Removed notifications when wizards are checking
//                     resistances.
//    Jun 2017 Lucius: Modify layers/looseness to be more permissive.
//
// Provides the following resistances to the wearer:
//        MAGIC_I_RES_FIRE:  15 (additive)
//        MAGIC_I_RES_AIR:    8 (additive)
//        MAGIC_I_RES_MAGIC:  3 (non-additive)

#include <files.h>

inherit "/std/armour";
inherit "/lib/keep";

#include "/d/Avenir/common/common.h"

public int last_tell = 0;

public void
create_armour()
{
    set_short("ruby-eyed snake ring");
    set_pshort("ruby-eyed snake rings");
    set_name(({"band","ring"}));
    set_adj(({"ruby","ruby-eyed","snake"}));

    set_long("This is a ring made beautifully crafted from "+
      "intertwining dozens of lengths of silver cord. It "+
      "twines around the ring, making it look like a "+
      "snake, and the snake's eye is a tiny, glittering ruby.\n");
    add_item(({"ruby","eye"}),"It is a tiny, glittering ruby that "
      +"seems to cast a deep red glow about.\n");

    set_ac(3);
    set_at(A_R_FINGER);
    set_af(TO);

    set_layers(1);
    set_looseness(6);

    add_prop(OBJ_I_VALUE, 1500);
    add_prop(OBJ_I_WEIGHT, 200);
    add_prop(OBJ_I_VOLUME, 100);   // It is small, after all...

    add_prop(OBJ_I_IS_MAGIC_ARMOUR, 1);
    add_prop(MAGIC_AM_MAGIC, ({ 20, "water", 40, "enchantment",
	15, "earth" }));
    add_prop(OBJ_S_WIZINFO, "This necklace "+
      "conveys the following resistances to "+
      "the wearer:\n"+
      "  MAGIC_I_RES_FIRE:  15 (additive)\n"+
      "  MAGIC_I_RES_AIR:    8 (additive)\n"+
      "  MAGIC_I_RES_MAGIC:  3 (non-additive)\n");

    add_prop(MAGIC_AM_ID_INFO,({
	"The "+short()+" is enchanted with the power of earth and water.\n",1,
	"Great protection is bestowed upon he who wears it.\n",10,
	"The "+short()+" shields the wearer from fires, be "+
	"they magical or natural.\n", 50,
	"The air shall hold no power over he who "+
	"wears the ring, for he shall be protected from it.\n",70}));
}

int wear(object to)
{
    TP->catch_msg("You slide the "+QSHORT(TO)+
      " onto your finger.\nYour hand feels slightly cold.\n");
    say(QCTNAME(TP)+" slides "+
      LANG_ADDART(QSHORT(TO))+" onto "+POSSESS(TP)+" finger.\n", TP);

    if (wearer)
	wearer->remove_magic_effect(TO);

    TP->add_magic_effect(TO);
    return 1;
}

int remove(object to)
{
    if (wearer == TP)
	wearer->catch_tell("You feel a bit warmer.\n");

    wearer->remove_magic_effect(TO);
    return 0;
}

void leave_env(object to, object from)
{
    ::leave_env(to, from);

    if (!living(from))
	return;

    from->remove_magic_effect(TO);
}

public object
find_player_source()
{
    object prev_object;
    int prev_count = 0;
    while (objectp(prev_object = calling_object(prev_count--)))
    {
        if (IS_PLAYER_OBJECT(prev_object))
            return prev_object;
    }
    return 0; 
}

mixed query_magic_protection(string prop, object what)
{
    if (!worn || what != wearer || !stringp(prop))
	return 0;
	
    int bDisplayMessage = 1;
    object player_source = find_player_source();

    if (objectp(player_source) && player_source->query_wiz_level())
    {
	// Wizards who are checking resistances should not
	// cause players to be notified.
	bDisplayMessage = 0;
    }
	
    /*
     * NB: I put messages in the parts where you check the
     *     player's magic resistance, which will hopefully 
     *     look nice when it is checked.
     */
    switch(prop)
    {
    case MAGIC_I_RES_AIR:
	if (time() - last_tell > 4)
	{
	    last_tell = time();
	    if (bDisplayMessage)
	    {
		wearer->catch_tell("The eye on your ring glitters with a "+
		    "cold red light.\n");
	    }
	}
	return ({8, 1});

    case MAGIC_I_RES_FIRE:
	if (time() - last_tell > 4)
	{
	    last_tell = time();
	    if (bDisplayMessage)
	    {
		wearer->catch_tell("The eye on your ring flashes brightly "+
		    "for a moment, casting about a dull red glow.\n");
	    }
	}
	return ({15, 1});

    case MAGIC_I_RES_MAGIC:
	if (time() - last_tell > 4)
	{
	    last_tell = time();
	    if (bDisplayMessage)
	    {
		wearer->catch_tell("Your ring feels warm on your hand.\n");
	    }
	}
	return ({3, 0});
    }

    return 0;
}

int dispel_magic(int power)
{
    if (power < query_prop(MAGIC_I_RES_MAGIC))
	return 0;

    query_worn()->catch_tell("Your ring suddenly glows red hot and melts!\n");
    query_worn()->heal_hp(-40);
    remove_broken(1);
    return 1;
}

