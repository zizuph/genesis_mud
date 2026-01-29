// file name:      /d/Avenir/common/dead/obj/poison_rude.c
// creator(s):     Lilith, July 2021              
// update history:
// purpose:        A deadly poison for those who were unforgivably
//                 rude to Mascarvin. There is no escaping death.
//                 Her long desc warns players to be on their best
//                 behavior.
// note:           Cloned through goddess herself
//                 /d/Avenir/common/dead/mascarvin/mascarvin.c
//        
// bug(s):
// to-do:

#include <poison_types.h>
#include <macros.h>
#include "/d/Avenir/common/dead/mascarvin/defs.h"

#define TR(x) tell_room(environment(poisonee), (x), poisonee);
#define DEATH_LOG "/d/Avenir/log/deaths/rudeness"

inherit "/std/poison_effect";
void
start_me_up()
{
	start_poison();
}	

void
create_poison_effect()
{
	if (!IS_CLONE)
		return;
    set_name(RIPO_ID);
    add_name("_Poison_for_the_rude-and_offensive");
    set_interval(6);
    set_time(360);  // 6 minutes should be long enough to kill them.
    add_prop(OBJ_M_NO_DROP, "Drop what?");
    set_strength(100);
    set_damage(({POISON_HP, 250, POISON_USER_DEF, 1}));
    set_poison_type("Retribution_of_the_Goddess_Mascarvin");
    set_silent(1);
	set_no_cleanse();
	set_alarm(2.0,0.0, start_me_up);
}

/* This will kill them */
void
special_damage (int damage)
{
    int msg_num = random(5);

    // player tells
    switch (msg_num)
    {
        case 0:
		    poisonee->add_mana(-100);
			poisonee->catch_msg("You are seriously regretting angering "+
			    "the Goddess Mascarvin.\n");
            poisonee->catch_msg("You suddenly feel very dizzy.\n");
            break;
        case 1:
		    poisonee->heal_hp(-400);
			poisonee->catch_msg("Mascarvin's laughter lilts in your mind.");
            poisonee->catch_msg("You feel as though your soul will "+
			    "leave your body momentarily.\n" );
            break;
        case 2:
		    poisonee->add_fatigue(-100);
			poisonee->catch_msg("Next time you come across a god you "+
			    "should use your manners.\n");
            poisonee->catch_msg("A wave of numbness flows through you.\n");
            break;
        case 3:
		    poisonee->add_panic(100);
			poisonee->catch_msg("A voice in your mind torments you: "+
			   "There is no escaping me. I am death, after all.\n");
            poisonee->catch_msg("Certain death awaits you and this "+
			    "awareness causes panic.\n");
            break;
        case 4:
		    poisonee->heal_hp(-400);
			poisonee->catch_msg("Mascarvin's voice tickles between your ears:"+
			    "I changed my mind. I'm enjoying watching you die...\n");
            poisonee->catch_msg("Dark spots dance at the edge of your "
               +"vision. You will die any moment now.\n");
            break;
        default:
		    poisonee->heal_hp(-400);
            poisonee->catch_msg("You feel the need to be violently ill.\n");
			poisonee->catch_msg("You can hear the Goddess Mascarvin humming "+
			    "happily.\n");
            break;
    }

}

void
timeout()
{
    poisonee->catch_msg("The icy grip upon you fades away to nothingness.\n");
    ::timeout();
}

void
reconfig_me(int newstr)
{
    set_damage(({POISON_HP, newstr, POISON_USER_DEF, 1}));
}

public varargs void
start_poison(object poisoner)
{
    ::start_poison(poisoner);
	
	poisonee->add_prop(BAAAD_MORTAL, 1);
	
}
