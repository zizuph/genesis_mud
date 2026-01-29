/*
 * CPAPER.C
 * This is a piece of paper which has some wax on it.
 * Part of the Candle Quest
 * Alaron Feb 1997
 */

#include "../default.h"
#include "/d/Emerald/lib/bit.h"

inherit "/std/object";

int give_paper(string str);
void
create_object()
{
    set_name("paper");
    
    add_name("_unique_candle_quest_paper_");
    
    set_adj("torn");
    set_short("torn piece of paper");

    set_long("It is a small piece of torn paper with some wax on "+
	     "it.\n");

    add_item("wax",
	     "It is the melted wax from a white candle.\n");

    add_prop(OBJ_M_NO_DROP,"@@blow_away@@");

    add_prop(OBJ_I_WEIGHT, 10);
    add_prop(OBJ_I_VOLUME, 3);
    add_prop(OBJ_I_VALUE, 0);
}

init()
{
    ::init();
    add_action(give_paper, "give");
}

int
give_paper(string str)
{
    object guide;

    if (!str)
	return 0;

    if ( (str!="paper to guide") &&
	(str!="paper to river guide") &&
	(str!="paper to detorrut") )
    {
	notify_fail("Give paper to whom?\n");
	return 0;
    }

    guide = present("detorrut", environment(TP));
    if (!guide)
    {
	notify_fail("There is no one to give the paper to.\n");
	return 0;
    }

    write("You give the paper to the river guide.\n");

    if (!TP->test_bit("Emerald", CANDLE_GROUP, CANDLE_GOT_QUEST))
    {
        guide->command("say to "+TP->query_real_name()+" I have no "+
		       "need of your paper. It was not done for my "+
		       "relatives, but for yours.\n");
	write("The guide gives you the paper back.\n");
	return 1;
    }
    else {
       if (TP->test_bit("Emerald", CANDLE_GROUP, CANDLE_FINISHED_QUEST))
	{
	    guide->command("thank "+TP->query_real_name());
	    guide->command("say to "+TP->query_real_name()+" Thank You! "+
			   "I appreciate the extra help you have given "+
			   "me.");
	    set_alarm(1.0, 0.0, remove_object);
	    return 1;
	}
	guide->command("thank "+TP->query_real_name());
	guide->command("say to "+TP->query_real_name()+" Thank you! You "+
		       "have given me a tear from my relatives! I am "+
		       "in your debt!");
	TP->add_exp(CANDLE_XP,0);
	reset_euid();
	TP->set_bit(CANDLE_GROUP, CANDLE_FINISHED_QUEST);
	write("You feel more experienced.\n");
	set_alarm(1.0, 0.0, remove_object);
	return 1;
    }
}

	
