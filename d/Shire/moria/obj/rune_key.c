#include <stdproperties.h>
#include <ss_types.h>
#include <macros.h>
#include "defs.h"
#include "/d/Shire/bits.h"

inherit "/std/object";

#define QUEST_NAME "moria_exit"
#define HOLLIN_EXIT "/d/Shire/common/hollin/crevice"
#define TEST_EXIT "/d/Shire/moria/chute"

/* Function prototypes */
void reward_moria_quest(object player);
int test_moria_quest(object player);

create_object()
{
    set_name("key");
    add_name("rune_key_mxplw");
    set_short("golden rune key");
    add_adj(({"golden", "rune"}));
    set_long("You are looking at a golden rune key.\n" +
	     "It is inscribed with the runes: \"MXPLW\".\n" +
	     "Wonder what that means...\n");
    add_prop(OBJ_I_WEIGHT, 340);
    add_prop(OBJ_I_VOLUME,  90);
    add_prop(OBJ_I_VALUE,   23);
    setuid(); seteuid(getuid());
}

init()
{
    ::init();
    add_action("do_place", "place");
}

int
do_place(string arg)
{
    object what, *objs;
    int i;
    string dummy;

    if (!strlen(arg))
	return notify_fail("Place what?\n");

    if (file_name(ETP) != MINES_DIR + "exit3")
	return notify_fail("Eh. What?\n");

    if (!parse_command(arg, ETP, 
		       "[the] %o 'on' / 'onto' / 'at' / 'in' [the] 'runes' / 'sign'", 
		       what) || what != TO)
	return notify_fail("Place <what> on <what>?\n");



    // Ok, he did it!
    // If the test says no, (i.e. 0), we stop by returning 1.
    if (!test_moria_quest(TP))
	return 1;
    
    write("You place the rune key upon the runes on the wall.\n");
    say(QCTNAME(TP)+ " places a rune key upon the wall.\n");

    tell_room(ETP, "A sharp click can be heard from underneath!!\n" +
	           "The floor breaks under, and you fall through it!!\n");
    tell_room(HOLLIN_EXIT,
	      "A rumble can be heard from above!!\n"+ 
	      "You can hear something sliding down from above! WATCH OUT!\n");

    objs = all_inventory(ETP);

    for (i=0; i<sizeof(objs); i++) {
	if (living(objs[i])) {
	    if (sscanf(MASTER_OB(objs[i]), MORIA_DIR+"%s", dummy) != 1)
		objs[i]->move_living("M", HOLLIN_EXIT);
	}
        else 
	    objs[i]->move(HOLLIN_EXIT);
    }
    tell_room(ETO, "The rune key breaks into thousands of fragments!\n");
    TO->remove_object();
    return 1;
}

/*
 * Test if quest is done, if not, reward.
 * Returns 1 if the players should get out.
 */
int
test_moria_quest(object player)
{
    int i;
    string dummy;

    object *objs;

    if (player->test_bit("Shire", EASTERN_GROUP, MORIA_EXIT_BIT)) 
    {
	write("This time you know a better way to go out.\n");
	say(QCTNAME(TP)+ " mumbles a silent word and you feel moved.\n");
	objs = all_inventory(ETP);
   
	for (i=0; i<sizeof(objs); i++) {
	    if (living(objs[i])) {
		if (sscanf(MASTER_OB(objs[i]), MORIA_DIR+"%s", dummy) != 1)
		    objs[i]->move_living("M", TEST_EXIT);
	    }
	    else
		objs[i]->move(HOLLIN_EXIT);
	}

	tell_room(ETO, "The rune key breaks into thousands of fragments!\n");
    TO->remove_object();
	return 0;
    }
    
    if (!player->query_prop("i_got_the_rune_key")) {
	say(QCTNAME(player)+ " places the key on the runes but "+
	    "nothing happens.\n");
	write("The key seems to have no magic for you.\n");
	return 0;
    }
    
    reward_moria_quest(player);
    return 1;
}

void
reward_moria_quest(object player)
{
    player->remove_prop("i_got_the_rune_key");
    player->set_bit(EASTERN_GROUP,MORIA_EXIT_BIT);
    player->add_exp(MORIA_EXIT_EXP,0);
    seteuid(getuid(TO));
    //  ~shire/log/quest/moria_entrance
    log_file("/quest/" + QUEST_NAME, 
	     sprintf("%s %s rewarded with %d exp, <%d> avg stats.\n",
		     extract(ctime(time()), 4, 15),
		     CAP(player->query_real_name()),
		     MORIA_EXIT_EXP,
		     player->query_average_stat()));
    tell_object(player,"You feel much more experienced!\n");
}

    
    
// ----------------------------------------------------------------------------------
//	    add_action("do_fail", "open");
//	    add_action("do_fail", "lock");
//	    add_action("do_fail", "unlock");
//	    add_action("do_fail", "close");
//	
//	int
//	do_fail(string arg)
//	{
//	    string vrb = query_verb();
//	
//	    if (!id(arg))
//		return 0;
//	
//	    write("Sorry, but this rune key does not look like an ordinary key. " +
//	          "It is simply a 3 by 3 by 6 cm long piece of metal with " +
//		  "runes inscribed on it. You can't \""+ vrb + "\" something " +
//		  "with it.\n");
//	    return 1;
//	}
// ----------------------------------------------------------------------------------
