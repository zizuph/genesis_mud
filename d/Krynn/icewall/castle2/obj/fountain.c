// this should be used everywhere (foces you to do proper casting)
#pragma strict_types

inherit "/std/object";
#include "/d/Krynn/common/defs.h"
#include <macros.h>

object *had_drunk = ({ });

void
end_cold_enchantment(object who, int amount)
{
    had_drunk -= ({ who });
    if (!objectp(who)) // player might have quitted...
	return;

    // we reset property and notify player slightly
    who->add_prop(MAGIC_I_RES_COLD, who->query_prop(MAGIC_I_RES_COLD) - amount);
    who->command("$shiver");
    if (who->query_wiz_level()) // you cant force wizard with command
	who->catch_tell("MAGIC_I_RES_COLD reset back.\n");
}

void
notify_has_drunk(object who, int amount)
{
    if (!objectp(who))
	return;
	
    // player is already enchanted
    if (member_array(who, had_drunk) > -1)
    {
	who->catch_tell(".\n");
	return;
    }

    who->catch_tell(" and a warm feeling spreads through your body.\n");
    had_drunk += ({ who });
    who->add_prop(MAGIC_I_RES_COLD, who->query_prop(MAGIC_I_RES_COLD) + amount);
    set_alarm(itof(35*(amount+random(amount))), 0.0, &end_cold_enchantment(who, amount));    

    if (who->query_wiz_level())
	who->catch_tell("MAGIC_I_RES_COLD upped by "+amount+".\n");
}

void
create_object()
{
    set_name("fountain");
    set_short("wondrous dragon fountain");
    set_long("The fountain has been artfully cut out of white marble. " +
      "It features four " +
      "dragons sitting on their hunches, with their wings folded " +
      "over their sides. Their necks extend " +
      "upwards, as if the beasts were gazing at the stars, and " +
      "sparkling water spouts from their widely open, fanged mouths. " +
      "Strangely, all is frozen, but the fountain runs with clear, " +
      "fresh water. You could drink from the fountain...\n\n" +
      "If you trust the water, that is.\n");

    add_item(({"water","fresh water"}),"The water is pure, fresh, " +
      "and warm! It also has a most uncharacteristic smell...\n\n" +
      "It smells of spring!!\n");

    add_prop(OBJ_I_VALUE, 0);
    add_prop(OBJ_I_WEIGHT, 100000);
    add_prop(OBJ_I_VOLUME, 30000);
    add_prop(OBJ_M_NO_GET, "Only a giant could attempt that!\n");
    add_prop(OBJ_M_NO_STEAL, "It is simply too big...\n");
    add_prop(MAGIC_AM_MAGIC, ({50, "enchantment"}));
    add_prop(MAGIC_AM_ID_INFO, ({"This fountain is definitely " +
      "magical.\n", 1, "You feel the residual  " +
      "magic of the simple enchantment cast who knows how " +
      "many centuries ago upon this fountain. The dweomer " +
      "seems somehow alien to your understanding...\n " +
      "But you realize that it meant the water to be always " +
      "pure and refreshing. Drinking it will provide comfort " +
      "against the vicious cold - both normal and magical.\n", 30})); 
    add_prop(OBJ_S_WIZINFO, "Long ago, Icewall was a warmer land. " +
      "This fountain was a merry present from a friendly dragon to " +
      "the lord of the castle, whos wife has just ran away with a " +
      "troubadour. As the dragon said 'At least now you'll not " +
      "feel so cold at night...' In the current age, this " +
      "is a treasured possesion.\n");
}

int
drink_fountain(string str)
{
    int maxam, curam, am;

    // has player passed proper command?
    if (!strlen(str))
    {
        notify_fail("Drink what?\n");
        return 0;
    }
    str = lower_case(str);
    if (parse_command(str, ({ }), " [water] [from] [the] [wondrous] [dragon] 'fountain' "))
    {
	maxam = TP->query_prop(LIVE_I_MAX_DRINK);
	curam = TP->query_soaked();
	am = MIN(maxam - curam, maxam / 15);
	
	if (am <= 0) // player can't drink at all
	{
	    write("Hmm, you are not thirsty at all at the moment.\n");
	    return 1;
	}
	// can player drink (is he thirsty?)
	if (TP->drink_soft(am))
	{
	    if (am < 100) // not enough for enchantment
	    {
		say(QCTNAME(TP) + " drinks little from the fountain.\n");
		write("You manage to drink little from the fountain " +
                 "but you are just not thirsty enough.\n");
		return 1;
	    }
	    say(QCTNAME(TP) + " drinks deeply from the fountain and looks " +
		"invigorated.\n");
	    write("You drink deeply from the fountain");
	    // notify_has_drunk will finish the message
	    notify_has_drunk(TP, am / 20);
	}
	else
	    write("For some strange reason you can't drink.\n");
	// whether thirsty or not he passed proper command and we end
	// with success
	return 1;
    }
    // player passed bad argument so we return 0 (fail) and possibly
    // display fail message
    NF("Drink from where?\n");
    // note that drink is standard mudlib command and so this NF is
    // likely going to be replaced by standard "Drink what?" message
    // and so it is desirable that there is good hint for player to find
    // out proper syntax
    return 0;
}

void
init()
{
    ::init();
    add_action(drink_fountain, "drink");
}
        
