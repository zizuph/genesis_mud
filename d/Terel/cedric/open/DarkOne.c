inherit "/std/monster";

#include <stdproperties.h>
#include <wa_types.h>
#include <ss_types.h>
#include "/d/Terel/common/terel_defs.h"

#define A_BITE  0
#define A_CLAW 1
#define A_SWORD 2

#define H_HEAD 0
#define H_BODY 1

#define TP		this_player
#define BS(message)	break_string(message,70)

void
create_monster()
{
    add_name(({"One", "one", "presence", "thane_dark_one"}));
    set_adj("dark");
    set_race_name("presence");
    set_short("the Dark One itself");
    set_long(BS("Before you stands a Presence so black your eye cannot even "
    + "discern its boundaries. It is in fact none other than your ancient Enemy, "
    + "the Darkness that fills the hearts of your fellow realmwalkers, the "
    + "human race. The end of your ancient quest draws nigh; slay this vile "
    + "thing, and your kind and the humans may yet learn to coexist in peace.\n"));
    /*          str, con, dex, int, wis, dis */
    set_stats(({150, 150, 150, 150, 150,  150}));
    
    set_skill(SS_DEFENCE, 100);
    set_alignment(-1000);
    set_aggressive(1);
    set_gender(2); /* male = 0, female = 1, other = 2 */
    set_hp(10000);
    set_whimpy(0);
    add_prop(LIVE_I_NO_CORPSE, 1);
   
    set_hitloc_unarmed(H_HEAD, ({ 15, 25, 20, 20 }), 20, "head");
    set_hitloc_unarmed(H_BODY, ({ 10, 15, 30, 20 }), 80, "body");
    set_chat_time(5);
    
    add_chat("You can't win, Cael-lin.");
    add_chat("Give up now and I may spare your worthless soul, elf-thing.");
    add_chat("It is the tide of history itself you are fighting, elf. Submit!");
    add_chat(BS("Elf, your time is through. I am all that is dark and barbaric in "
    + "the human race; you can never defeat me!"));
    add_chat("A puny sword made by dead elves is no match for me, Cael-lin!");
}

void
do_die(object killer)
{
    if (interactive(killer))
    {
	if (killer->test_bit("Terel", QUEST_TH1_GROUP, QUEST_TH1_BIT))
	    if (!killer->test_bit("Terel", QUEST_TH2_GROUP, QUEST_TH2_BIT))
	    {
		killer->set_bit(QUEST_TH2_GROUP, QUEST_TH2_BIT);
		killer->add_exp(QUEST_TH2_EXP, 0);
		seteuid(getuid(this_object()));
		write_file(QUEST_LOG,killer->query_name()+
                " solved part 2 of Thane quest ("+ctime(time())+")\n");
	    }
	killer->catch_msg(BS("With a flash of holy brilliance, "
	+ "LightBringer cleaves through the Dark One. A clap of thunder throws "
	+ "you across the room, but even louder is the scream of triumph that "
	+ "echos through your mind. Both sword and Darkness vanish in a blast "
	+ "that seems to shake the very fabric of the universe, and suddenly "
	+ "all is quiet. You feel a great burden lifted off your shoulders, "
	+ "and emerge a wiser, more experienced "+killer->query_race()+".\n"));
	present("thane_quest_sword", killer)->remove_object();
    }
    else
	remove_object();
    ::do_die();
}
