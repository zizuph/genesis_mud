/* 
  This room was shamelessly copied from Styles. 
  /Quis -- 6 May 1992
*/


#include "goblins.h"
#pragma save_binary

inherit "/std/room";
#include "/sys/language.h";
move_out(arg);

create_room()
{
 
  set_short("Welcome to Genesis 3.0");

  set_long("\n\n"+
    "Welcome to Genesis 3.0\n\n"+
    "You are passing through a gray void on your way into the world.\n\n"+
    "All goblins enroute to Genesis pass this way. Like so many goblins\n"+
    "have done before you, you might initially feel somewhat confused.\n"+
    "Don't panic!  We will have you maurauding the countryside in no time.\n"+
    "Here are a few helpful hints.\n\n"+
    "    You can get help using 'help'.\t\t\t(help topics)\n"+
    "    'help <command>' gives help on available commands.\t(help commune)\n"+
    "    It is advisable to read the help info before using a command.\n"+
    "    You move around by typing a direction.\t\t(n, e, w, s, u, d)\n"+
    "    You talk to people by typing 'say <message>'.\t(say Sod off!)\n"+
    "    You can most often look at things around you.\t(look at floor)\n"+
    "    Many items can be picked up if found somewhere.\t(get sword)\n"+
    "    Remember to do:\tintroduce myself\n\t\tand\tremember [name]\n"+
    "    in order to get aquainted with other players. It is quite useful.\n"+
    "    You can also do things like: kick, puke, point, fart, "+
    "grin or cackle.\n\n"+
    "You can try this right now or you can type 'down'\n"+
    "if you wish to enter the world.\n");
    
    add_item(({"void" }),"Everything is gray in all directions so "+
	     "there isn't very much to see.\n");
}

init() {
    add_action("down","down");
    ::init();
}

down() { 
    string race;

    race = this_player()->query_race();

    if (race != "goblin") {
	write("You are not goblin and should not be here.\n"+
	      "Join your fellow "+ LANG_PWORD(race) +" instead.\n\n");
 
        set_alarm(1.0, 0.0, &move_out(({this_player(), 
            this_player()->query_def_start()})));
	return 1;
    }
    write("You experience a feeling! It is quite new and hard to define.\n");
    announce_new_goblin();
    set_alarm(3.0, 0.0, &move_out(({this_player(), 
        this_player()->query_def_start()})));
    return 1;
}


move_out(arg) {
    arg[0]->add_prop("just_created", 0);  /*Shouldn't come back here again. */

    tell_object(arg[0],
	"\nSlowly the gray void swirles as the world forms around you.\n\n");
    arg[0]->move_living("drifting away into the void", arg[1]);

}

ktid() {
    string dummy, month, date, hh, mm, dummy2;
    sscanf(ctime(time()), "%s %s %d %s:%s:%d",
        dummy, month, date, hh, mm, dummy2);
    return(date +" "+ month +" "+ hh +":"+ mm);
}

announce_new_goblin() {
    /* Remove find_object below when tell_room(str,str) works properly. */
    tell_room(find_object(GOBLIN_DIR + "quarters"),
	      "\nAnother goblin wakes up with dreams of conquest.\n\n");
}
