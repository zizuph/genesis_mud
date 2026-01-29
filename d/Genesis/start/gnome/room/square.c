#include "../gnome.h"
#include "language.h"
#include "const.h"

#pragma save_binary

inherit  LIB;
inherit  "/std/room";

status is_fed;

void
reset_room() {
    if (is_fed) {
	tell_room(this_object(), "The statue quivers ever so slightly.\n");
	is_fed = 0;
    }
    reset_guards();
}

void
init() {
    add_action("read", "read");
    add_action("give", "give");
    ::init();
}

void
create_room() {
    set_short("The southern square");
    set_long(BS(" Here a square room has been dug into the hill and the " +
		"ceiling is high above you. A statue is raised towards one " +
		"wall, a large bonfire is burning in the middle of the " +
		"square, and benches are placed in a circle around it.\n"));
    add_item("statue",
	     BS(" The statue towers above you. It is clearly a gnome, and " +
		"of quite generous proportions - at least his waistline is. " +
		"There is a small plaque at the base of the statue.\n") +
	     "@@check_bit");
    add_item("plaque",
	     " The plaque reads : Fatty, King of Gnomes and " +
	     "Founder of Gnomehome.\n");
    add_item("bonfire",
	     BS(" The bonfire makes the room uncomfortably hot but it gives " +
		"a nice mood to the large but enclosed space.\n"));
    add_item("benches",
	     " They are just plain wooden benches.\n");
    add_exit(ROOM_DIR + "merch2", "north", 0);

    guard_settings = ({ 2 }) + DEFAULT_GUARD_SETTINGS;
    reset_room();
    set_noshow_obvious(1);
}

string
lassorlad() {
    if ((int)this_player()->query_gender() == G_MALE) {
	return "lad";
    } else {
	return "lass";
    }
}

string
check_bit() {
    if (is_fed || this_player()->check_bit(QG_STATUE, QB_STATUE)) {
	return "";
    } else {
	return BS(" The statue seems to stir and you hear a metallic " +
		  "voice... 'See here, " + lassorlad() + ", I am starved " +
		  "for a proper donut... Get me a good and crunchy one " +
		  "and I'll reward you.\n");
    }
}

status
read(string str) {
    if (str == "plaque") {
	write(long(str));
	return 1;
    } else {
	notify_fail("Read what?\n");
	return 0;
    }
}

#define DONUT_ADJ ({ "sugary", "thin", "twisted", "brown", "hot" })

void
donut_rain() {
    /*
     * Simply rain donuts over this_player().
     */

    object donut;
    int    i;

    write(" Suddenly, donuts start raining around you!\n");
    say("Suddenly, donuts start raining around " + 
	this_player()->query_name() + "!\n");

    for (i = 0; i < 5; i ++) {
	donut = clone_object("/std/food");
	donut->set_name("donut");
	donut->set_short(DONUT_ADJ[i] + " donut");
	donut->set_long("A freshly baked, steaming donut.\n");
	donut->set_amount(40);
	donut->move(environment(this_player()));
    }
}

status
give(string str) {
    object ob;
    if (parse_command(str, this_player(), "%o 'to' 'statue'", ob)) {
	if (!ob->id("donut") && !ob->id("doughnut")) {
	    if (!ob->move(environment(this_player()))) {
		say(this_player()->query_name() + " tries to give " +
		    LANG_ADDART((string)ob->short()) + " to the statue, " +
		    "but it drops to the ground.\n");
		write(" The statue doesn't move. The " + ob->short() + 
		      " falls to the ground.\n");
	    } else {
		write(" The statue won't accept it.\n");
	    }
	    return 1;
	}
	if (!ob->is_rocky_donut(1)) {
	    if (ob->is_rocky_donut(0)) {
		write(BS(" The statue seems to sense your offering, but " +
			 "apart from a small wrinkle of its nose that may " +
			 "have been there before, you don't know why it " +
			 "won't accept it.\n"));
	    } else {
		write(BS(" The statue looks completely uninterested.\n"));
	    }
	    say(this_player()->query_name() + " foolishly offers the " +
		"statue " + LANG_ADDART((string)ob->short()) + ".\n");
	    return 1;
	}

	if (is_fed) {
	    write(" The statue is passive. It looks sort of smug.\n");
	    return 1;
	}
	is_fed = 1;
	say(this_player()->query_name() + " hands over a donut-shaped " +
	    "rock to the statue.\n");
	write(BS(" You hand over the donut-shaped rock to the statue, " +
		 "which with a creaking noise moves it to its mouth and " +
		 "showing a stiff but happy smile munches it down.\n"));
	write(BS(" Thanks, " + this_player()->query_name() + ", this " +
		 "really hit the spot. Here is a little something for " +
		 "your troubles. May they warm your belly and make you " +
		 "a happier " + this_player()->query_race_name() + "!\n"));
	donut_rain();
	ob->remove_object();
	if (!this_player()->test_bit(geteuid(), QG_STATUE, QB_STATUE)) {
	    write(" You feel you've accomplished something.\n");
	    this_player()->set_bit(QG_STATUE, QB_STATUE);
	    this_player()->add_exp(75);
	}
	return 1;
    }
    return 0;
}

status
do_clear_bit() {
    return (status)this_player()->clear_bit(QG_STATUE, QB_STATUE);
}