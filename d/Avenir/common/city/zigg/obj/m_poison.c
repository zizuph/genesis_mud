// file name:   m_poison.c
// creator(s):  Zielia Sept 2006
// last update:
// purpose: poison for maree's thorns
// note:
// bug(s):
// to-do:
#pragma strict_types

#include <poison_types.h>
#include <macros.h>
#include "zigg.h"

#define TR(x) tell_room(environment(poisonee), (x), poisonee);

inherit "/std/poison_effect";

public void
create_poison_effect(void)
{
    set_name("maree_trap");
    set_interval(60);
    set_time(600);
    add_prop(OBJ_M_NO_DROP,"Drop what?");
    set_strength(100);
    set_damage(({POISON_HP, 600, POISON_USER_DEF,1}));
    set_no_cleanse();
    set_poison_type("standard");
    set_silent(0);
}

public void
special_damage(int damage)
{
    int msg_num = random( 6 );

    // player and room tells
    switch (msg_num)
    {
	case 0:
	    poisonee->catch_tell("A terrible burning pain radiates from "+
		"your legs and to your stomach.\n");
	    TR(QCTNAME(poisonee) + " holds " + HIS(poisonee) +
		" hands to "+ HIS(poisonee) + " stomach.\n");
	    break;
	case 1:
	    poisonee->catch_tell(
		"It feels as though your blood is boiling, burning you "+
		"from within.\n" );
	    TR(QCTPNAME(poisonee) + " face goes looks flushed, and "+
		HE(poisonee) +" begins to sweat.\n");
	    break;
	case 2:
	    poisonee->catch_tell("Your legs seem to barely support you, "+
		"the muscles feeling suddenly weak.\n");
	    TR(QCTNAME(poisonee) + " sways as though "+ HE(poisonee)+
		"might fall down.\n");
	    poisonee->add_fatigue(-50);
	    break;
	case 3:
	    poisonee->catch_tell("You moan pitifully as another wave of "+
		"pain washes over you.\n");
	    TR(QCTNAME(poisonee) + " moans pitifully.\n");
	    break;
	case 4:
	    poisonee->catch_tell("Your head throbs with pain.\n");
	    TR(QCTNAME(poisonee) +
		" grabs " + HIS(poisonee) + " head.\n");
	    poisonee->command("$wince");
	    break;
	case 5:
	    poisonee->catch_tell("You feel feverish and weak.\n");
	    TR(QCTNAME(poisonee) + " begins to shake and looks feverish.\n");
	    break;
	default:
	    poisonee->catch_tell( "You feel violently ill.\n");
	    break;
    }
}

public void
reconfig_me(int hitp)
{
  set_damage(({POISON_HP, hitp, POISON_USER_DEF,1}));
}

public void
timeout(void)
{
  poisonee->catch_msg("Your blood feels clean again.\n");
  ::timeout();
}

public void
kill_player(void)
{
// It won't kill them, just leave them vulnerable for a while.
}
