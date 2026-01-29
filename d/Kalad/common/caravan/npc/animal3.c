/*
* /d/Kalad/common/caravan/npc/animal3.c
*
* Parakeet Coded by someone. Not sure who, but not me.
* 
* Change Log - Added a log for birdtalk and stopped it from being able
*              to speak in the Sparkle church.
*
*/

#include "default.h"
inherit "/std/object";

string str;

void
create_object()
{
    seteuid(getuid());

    set_name("parakeet");
	add_name("bird");
    set_adj("small");
    set_adj("blue");
    set_short("small blue parakeet");
    set_pshort("small blue parakeets");
    set_long("An absolutely adorable little bird.\n"+
      "A tiny tag on one of its feet has the following words written on it:\n"+
      "You can 'pet' the parakeet or try 'birdchirp' to make it chirp. Also "+
      "you can do 'birdtalk <str>' to make it speak.\n");

    add_prop(OBJ_I_WEIGHT, 50);
    add_prop(OBJ_I_VOLUME, 50);
    add_prop(OBJ_I_VALUE, 432);
    add_prop(OBJ_M_NO_SELL, 1);
}

int
pet(string str)
{
    if((str == "parakeet" || "bird"))
    {
    write("You gently pet the small blue parakeet. It chirps noisily.\n");
    say(QCTNAME(TP) + " pets the small blue parakeet. It chirps noisily.\n");
    }
    return 1;
}

int
kill_animal(string str)
{
    if((str == "parakeet" || "bird"))
    {
    write("You mercilessly crush the small blue parakeet in your hand.\n");
    say(QCTNAME(TP) + " mercilessly crushes the small blue parakeet in " + TP->query_possessive() + " hand.\n");
    remove_object();
    return 1;
    }
    return 0;
}

int
chirp()
{
    write("The small blue parakeet chirps merrily.\n");
    say("The small blue parakeet chirps merrily.\n");
    return 1;
}

int
talk(string str)
{
    if (TP->query_prop(LIVE_M_MOUTH_BLOCKED))
    {
        write("You can't talk to tell the bird what to say.\n");
		return 1;
    }
    write("The small blue parakeet chirps: " + str + "\n");
    say("The small blue parakeet chirps: " + str + "\n");
    if (file_size("/d/Kalad/log/birdchirp") > 100000)
    rename("/d/Kalad/log/birdchirp", "/d/Kalad/log/birdchirp.old");
    write_file("/d/Kalad/log/birdchirp", ctime(time())
      + " " + this_player()->query_name() + " - made the bird say: " + 
      str+"\n");
    return 1;
    
}

void
init()
{
    ::init();
    add_action(pet, "pet");
    add_action(kill_animal, "kill");
    add_action(chirp, "birdchirp");
    add_action(talk, "birdtalk");
}
