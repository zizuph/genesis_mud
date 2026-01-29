/*
* Wayreth.
* 
* meditation.c ------------
* 
* Coded ........: 95/06/02 By ...........: Jeremiah
* 
* Latest update : 95/08/08 By ...........: Jeremiah
* 
*/

#include "/d/Ansalon/common/defs.h"
#include "/d/Ansalon/balifor/port_balifor/local.h"
#include <macros.h>
#include <ss_types.h>

inherit         BALIFOR_IN;
inherit "/lib/guild_support";
inherit "/lib/skill_raise";


/*
* prototypes.
*/
void            set_up_skills();


void
reset_balifor_room()
{
    return;
}

void
create_balifor_room()
{
    set_short("Adventurer's Guild");
    set_long("This is the Adventurer's guild of the Port City of " +
      "Balifor. Here you can train your skills; 'learn' will give " +
      "you a list of learnable skills and 'improve' will give you a " +
      "list of trainable skills.\n");

    add_exit(BROOM + "city09","south","@@remove_medi_props");

    create_skill_raise();
    set_up_skills();

    reset_balifor_room();
}


int
remove_medi_props()
{
    TP->remove_prop(LIVE_I_MEDITATES);
    TP->remove_prop(LIVE_S_EXTRA_SHORT);
}


void
init()
{
    init_guild_support();
    add_action("gs_meditate", "meditate");
    init_skill_raise();
    ::init();
}


void
gs_hook_start_meditate()
{
    write("You start to concentrate solely upon your own mind and you " +
      "block off all your senses. A feeling of great ease and self " +
      "control falls upon you as you slowly sink into a deep " +
      "trance. You may now set the learning preferences at your "+
      "own desire.\n");

    say(QCTNAME(TP) + " enters into a trance and slowly kneels " +
      "down. " + C(PRONOUN(TP)) + " sinks into a deep trance and " +
      "seems lost to the world around " + OBJECTIVE(TP) + ".\n");
}


int
gs_hook_rise()
{
    write("As if ascending from a great depth, you rise to the surface " +
      "of your consciousness. You exhale and feel very relaxed as " +
      "you get up and prepare yourself for whatever may lie ahead. " +
      " \n");
    say(QCTNAME(TP)+ " rises from " +HIS(TP)+ " trance.\n");

}


void
leave_inv(object ob, object to)
{
    gs_leave_inv(ob, to);
    ::leave_inv(ob, to);
}


void
set_up_skills()
{
    sk_add_train(SS_WEP_POLEARM, "use a polearm", 0, 0, 20);
    sk_add_train(SS_WEP_SWORD, "use a sword", 0, 0, 27);
    sk_add_train(SS_WEP_KNIFE, "use a knife", 0, 0, 30);
    sk_add_train(SS_ACROBAT, "move acrobatically", 0, 0, 20);
    sk_add_train(SS_HIDE, "hide in a room", 0, 0, 20);
    sk_add_train(SS_SNEAK,"sneak into rooms", 0, 0, 20);
    sk_add_train(SS_SWIM, "swim", 0, 0, 30);
    sk_add_train(SS_AWARENESS, "be more wary", 0, 0, 30);
    sk_add_train(SS_CLIMB, "climb", 0, 0, 30);
    sk_add_train(SS_TRADING, "make deals", 0, 0, 30);
}

int
sk_improve(string sk)
{
    return ::sk_improve(sk);
}

int
sk_query_max(int snum)
{
    int            *skills_available_here;
    mixed           skval;

    skills_available_here = sk_query_train();

    if (member_array(snum, skills_available_here) == -1)
	return 0;

    if (!mappingp(sk_default))
	return 0;
    skval = sk_trains[snum];
    if (sizeof(skval) > 2)
	return skval[2];
    else
	return 0;
}


int
sk_hood_improved_max(string skill)
{
    notify_fail("You cannot raise this skill any further " +
      "here, you have to \n" + "seek knowledge elsewhere. \n");
    return 0;
}
