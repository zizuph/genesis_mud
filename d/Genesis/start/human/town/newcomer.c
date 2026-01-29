/*
 * newcomer.c - the room where new players are dispatched to their
 *              starting location.
 * This comment and also information about the tutorial and the website
 * added by TAPAKAH, 05/2005
 *
 * Newbie pin cloning added
 * TAPAKAH, 09/06/2005
 */

#pragma save_binary
#pragma strict_types

inherit "/std/room";

#include <language.h>
#include <time.h>
#include <stdproperties.h>
#include <state_desc.h>

#include "../defs.h"

#define NEWBIE_PIN "/d/Genesis/start/newbie/newbie_pin"

void
create_room()
{
    set_short("Welcome to Genesis 3.0");
    set_long("\n\n"+
             "Welcome to Genesis 3.0\n"+
             "You are passing through a gray void on your way into the world.\n"+
             "All those enroute to Genesis pass this way. Like so many others\n"+
             "have done before you, you might initially feel somewhat confused.\n"+
             "Don't panic!  We will have you roaming the countryside in no time.\n"+
             "Here are a few helpful hints.\n\n"+
             "    You can get help using 'help'.\t\t\t(help topics)\n"+
             "    'help <command>' gives help on available commands.\t(help commune)\n"+
             "    It is advisable to read the help info before using a command.\n"+
             "    You move around by typing a direction.\t\t(n, e, w, s, u, d)\n"+
             "    You talk to people by typing 'say <message>'.\t(say Hi there)\n"+
             "    You can most often look at things around you.\t(look at floor)\n"+
             "    Many items can be picked up if found somewhere.\t(get sword)\n"+
             "    Remember to do:\tintroduce myself\n\t\tand\tremember <name>\n"+
             "    in order to get aquainted with other players. It is quite useful.\n"+
             "    You can also do things like: smile, laugh, giggle, bow, "+
             "tickle or sniff.\n\n"+
             "You can try this right now or you can type 'down'\n"+
             "if you wish to enter the world.\n\n"+
// Not sure where this tutorial came from ... if anywhere it should be on our
// own website. /Mercade, Dec-2014
//	     "We have compiled a tutorial for you:\n"+
//	     "http://www.foxcomm.net/web2/malaux/tutorial/index.html\n\n"+
	     "Make sure you visit our website: "+WEBSITE+"\n"
	     );
    
    add_item(({"void" }),"Everything is gray in all directions so "+
    "there isn't very much to see.\n");
    add_prop(ROOM_I_INSIDE, 0);
    add_prop(ROOM_I_TYPE, ROOM_IN_AIR);
}

void
move_out(mixed *arg)
{
    arg[0]->add_prop("just_created", 0);  /*Shouldn't come back here again. */

    tell_object(arg[0],
                "\nSlowly the gray void swirles as the world forms around you.\n\n");
    arg[0]->move_living("drifting away into the void", arg[1]);
}

void
announce_new_human()
{
    tell_room(TOWN_DIR + "church",
	      "\nBANG!\nLightning strikes the black stone, causing it to "+
	      "sparkle with electricity!\n\n");
}

int
down(string str)
{
    string race;

    race = TP->query_race();
    
    if (race != "human") {
	set_alarm(1.0, 0.0, &move_out(({ TP, TP->query_def_start()})));
	return 1;
    }
    write("You experience a feeling! It is quite new and hard to define.\n");
    announce_new_human();
    set_alarm(1.0, 0.0, &move_out(({ TP, TOWN_DIR + "church" })));
    return 1;
}

public void
give_me_pin(object who)
{
  setuid();
  seteuid(getuid());
  object pin;
  
    if(!present("Genesis_newbie_pin", who)
       && SD_IS_NEWBIE(who)) 
    {
        tell_object(who, 
            "An apparition of a Lars human wizard appears to you.\n"+
            "He tells you: this newbie pin may prove a good aid to you.\n"+
            "He tells you: use it wisely. Start with 'examine pin'.\n"+
            "The apparition disappears.\n"+
            "A small pin materializes in your hands.\n");
        pin = clone_object(NEWBIE_PIN);
        pin->move(who);
        pin->log_me(who->query_name(),"newbie");
        who->command("$wear pin");
    }
}
void
init()
{
    ::init();

    add_action(down, "down");
    set_alarm(1.0, 0.0, &give_me_pin(TP));
}
