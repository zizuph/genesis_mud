// file name:      /d/Avenir/common/dead/obj/poison_thief.c
// creator(s):     Lilith, July 2021              
// purpose:        A deadly poison for thieves who tried to steal from
//                 Mascarvin. There is no escaping death.
// note:           cloned through the prevent_leave function in the
//                 /d/Avenir/common/dead/obj/table_goddess file.
// revisions:   Lilith Mar 2022: boosted hp drain to make sure the 
//                 uber myths dont escape death.

#include <poison_types.h>
#include <macros.h>
#include "/d/Avenir/common/dead/mascarvin/defs.h"

#define TR(x) tell_room(environment(poisonee), (x), poisonee);

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
    set_name(POISON_ID);
    add_name("_Poison_for_idiots_and_thieves");
    set_interval(6);
    set_time(360);  // 6 minutes should be long enough to kill them.
    add_prop(OBJ_M_NO_DROP, "Drop what?");
    set_strength(100);
    set_damage(({POISON_HP, 500, POISON_USER_DEF, 1}));
    set_poison_type("Retribution_of_the_Goddess_Mascarvin");
    set_silent(1);
	set_no_cleanse();
	set_alarm(2.0,0.0, start_me_up);
}

/* This is going to leave them a mess but it won't kill them */
void
special_damage (int damage)
{
    int msg_num = random(5);

    // player and room tells
     // player tells
    switch (msg_num)
    {
        case 0:
		    poisonee->add_mana(-100);
			poisonee->catch_msg("You are seriously regretting stealing "+
			    "from the Goddess Mascarvin.\n");
            poisonee->catch_msg("You suddenly feel very dizzy.\n");
            break;
        case 1:
		    poisonee->heal_hp(-500);
			poisonee->catch_msg("Mascarvin's laughter lilts in your mind.\n"+
			    "You feel certain that she finds this entertaining.\n");
            poisonee->catch_msg("You feel as though your soul will "+
			    "leave your body momentarily.\n" );
            break;
        case 2:
		    poisonee->add_fatigue(-100);
			poisonee->catch_msg("Will the goddess show mercy, or will "+
			    "you die?\n");
            poisonee->catch_msg("A wave of numbness flows through you.\n");
            break;
        case 3:
		    poisonee->add_panic(100);
			poisonee->catch_msg("A voice in your mind torments you: "+
			   "When you steal from me, you forfeit your life.\n");
            poisonee->catch_msg("Certain death awaits you and this "+
			    "awareness causes panic.\n");
            break;
        case 4:
		    poisonee->heal_hp(-500);
			poisonee->catch_msg("Mascarvin's voice tickles between your ears:"+
			    "I've changed my mind...I'm enjoying watching you die...\n");
            poisonee->catch_msg("Dark spots dance at the edge of your "
               +"vision. You will die any moment now.\n");
            break;
        default:
		    poisonee->heal_hp(-500);
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
    set_damage(({POISON_FATIGUE, newstr, POISON_USER_DEF, 1}));
}

public varargs void
start_poison(object poisoner)
{
    ::start_poison(poisoner);
	
	seteuid(getuid());
    object para;
	
	if (!present(PARA_ID, all_inventory(poisonee)))
	{
        //If the accompanying paralyze is missing somehow, clone it.		
		para = clone_object(PARA);
		para->set_remove_time(300);
		para->move(poisonee, 1);
		poisonee->add_prop(BAAAD_MORTAL, 1);
	}
	// One of the purposes of this poison is to bring players
	// who went Linkdead or quit or otherwise "escaped" Mascarvin
	// back to face the music.
	if (!present("mascarvin"), ENV(poisonee))
		poisonee->move_living("X", RAGING);	
}
