#include "defs.h"

int smashed;

CONSTRUCT_ROOM {
    set_short("Southern Ballroom");
    set_long("This is the southern end of the ballroom. @@long_mirror@@\n");
    add_item("mirror","@@exa_mirror@@");
    add_call(({"touch", "feel"}), "[the] [huge] 'mirror'", "do_touch");
    add_call(({"press","push"}), "[the] [huge] 'mirror'", "do_touch");
    add_call(({"smash", "break"}), "[the] [huge] 'mirror'", "do_smash");
    NORTH("ballr");
}

RESET_ROOM {
    if (smashed) {
	tell_room(TO, "The mirrors magically gains its former form!\n");
	smashed = 0;
    }
}

int
do_touch()
{
    if (smashed)
	return notify_fail("Hmm, the mirror is smashed!"+
			   "You wouldn't want to touch it now.\n");

    write("You "+query_verb()+" the mirror gently.\n");
    say(QCTNAME(TP)+" touches the mirror gently.\n");
    if ((MINES_DIR + "ballrn")->produce_key())
	write("You get a sensational tingling feeling!\n");
    
   TP->add_prop("i_touched_mirror",1);
    write("Nothing else happens.\n");
    return 1;
}

int
do_smash()
{
    if (smashed)
	return notify_fail("It's allready broken.\n");

    write("You forcibly smash the beautiful mirror!!\n");
    say(QCTNAME(TP) + " forcibly smashes the beutiful mirror!\n");
    tell_room(TO, "The mirror breaks into thousands of fragments.\n");
    smashed = 1;
    return 1;
}

string
exa_mirror()
{
    if (smashed)
	return "This once beautiful mirror seems to have been destroyed by " +
	    "foul orcs!\n";
    else
	return "My, you look ugly!";
}

string
long_mirror()
{
    if (!smashed) 
	return "On the wall, there is a huge mirror, in which you can see the gallery to the "+
	     "left and the ballroom in front of you.";
    else
	return "On the wall hangs a huge smashed mirror, only to show the bare wall behind. "+
	       "The ballroom extends northwards, and up to the northeast you see the overlooking " +
	       "gallery.";
}




