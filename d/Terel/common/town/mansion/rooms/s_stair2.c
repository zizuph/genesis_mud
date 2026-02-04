/* A secret staircase no 2 */
inherit "/std/room";
#include <stdproperties.h>
#include <macros.h>
#include <ss_types.h>
#include <cmdparse.h>
#include "/d/Terel/common/terel_defs.h"

#define BS(message)    break_string(message, 70)
#define BSN(message)   break_string(message + "\n", 70)
#define TP             this_player()
#define TO             this_object()
#define WALL_HARDNESS  350

int wall, no_wall;

init()
{
    ::init();
    add_action("do_hit", "hit");
    add_action("do_hit", "break");
    add_action("do_hit", "smash");
    add_action("do_hit", "destroy");
}

void
reset_room()
{
    object bat;

    if (!present("bat")) {
        bat = clone_object(MORTRICIADIR + "creatures/bat");
        bat -> move(TO);
    }
}

void
create_room()
{
    set_short("Secret staircase");
    set_long("@@my_long");

    add_item(({"wall", "southern wall"}), "@@my_wall");
    add_item("opening", "@@my_hole");

    add_prop(ROOM_I_INSIDE, 1);

    add_exit(MANSION + "rooms/s_stair1", "up", 0);

    wall = WALL_HARDNESS;
    no_wall = 0;
    reset_room();
}

my_long()
{
    string s;

    s = "You are standing at the lower end of the secret stairs.";
    if (wall == WALL_HARDNESS) {
	s += " It appears to be a dead end. " +
	     "The southern wall looks a lot newer than the other " +
	     "walls, and must have been made quite recently.";
    }
    if (wall < WALL_HARDNESS && wall > 0 ) {
	s += " It appears to be a dead end. " +
	     "The southern wall looks a lot newer than the other " +
	     "walls, and must have been made quite recently. " +
	     "Someone has started to make an opening in it.";
    }
    if (wall <= 0) {
	s += " There is a lot of debris here, just if as someone " +
	     "quite recently has torn down the southern wall.";
    }
    return BSN(s);
}

my_wall()
{
    string s;

    if (wall == WALL_HARDNESS) {
	s = "The southern wall isn't as robust as the other walls. " +
	    "Maybe you can destroy it? Though you would probably " +
	    "need something like a battering ram...";
    }
    if (wall < WALL_HARDNESS && wall > 0 ) {
	s = "Someone must recently tried to remove southern wall, " +
	    "since there is a small opening in it. " +
	    "Chunks of the wall lie on the floor.";
    }
    if (wall <= 0) {
	s = "The remants of the southern wall lie on the floor.";
    }
    return BSN(s);
}

my_hole()
{
    string s;

    if (wall == WALL_HARDNESS) {
	s = "You find no opening.";
    }
    if (wall < WALL_HARDNESS && wall > WALL_HARDNESS/2) {
	s = "The opening is small, and it is impossible " +
	    "enter it.";
    }
    if (wall <= WALL_HARDNESS/2 && wall > 0) {
	s = "The opening is somewhat bigger now, but still " +
	    "too small for you to enter.";
    }
    if (wall <= 0) {
	s = "You find no opening.";
    }
    return BSN(s);
}

do_hit(string what)
{
    int tp_str;
    object *obs, ram;
    string str1, str2;

    if (!what) return 0;

    notify_fail("What do you want to try to hit with what?\n");
    if (sscanf(what, "%s with %s", str1, str2) != 2) {
	return 0;
    }
    if (str1 != "wall" && str1 != "southern wall") {
	write("Hit what?\n");
	return 1;
    }
    if (no_wall) {
	write("The wall that could be hit is already torn down!\n");
	return 1;
    }
    if (str2 != "ram" && str2 != "battering ram" &&
	str2 != "heavy ram" && str2 != "heavy battering ram") {
	obs = FIND_STR_IN_OBJECT(str2, TP);
	if (sizeof(obs) == 0) {
	    write("Hit wall with what?\n");
	    return 1;
	}
	write("You hit the wall with your " + str2 + ".\n");
	say(QCTNAME(TP) + " hits the wall with " +
	    TP->query_possessive() + " " + str2 + ".\n");
	write("The wall remains intact though.\n");
	write("Maybe the "+str2+" isn't good for tearing down walls.\n");
	return 1;
    }
    ram = present("ram", TP);
    if (!ram) {
	write("You don't have that!\n");
	return 1;
    }
    if (!(ram->query_wielded())) {
	write("You must wield the battering ram first!\n");
	return 1;
    }
    tp_str = (TP->query_stat(SS_STR) + TP->query_stat(SS_CON))/4 +
	      TP->query_skill(SS_WEP_POLEARM);
    write("You hit the " + str1 + " with the " + str2 + ".\n");
    say(QCTNAME(TP) + " hits the wall.\n");
    tell_room(TO, "BANG!\n");
    wall -= tp_str;
    if (wall <= 0) {
	wall = 0;
	tell_room(TO, "CRASH!\n");
	write("Oops! Suddenly the whole wall fell!\n");
	say(QCTNAME(TP) + " managed to break the wall in one " +
	    "single stroke!\n");
	open_south();
    } else {
	tell_room(TO, "Some chunks of the wall fell down.\n");
    }
    return 1;
}

open_south()
{
    TO -> add_exit(MANSION + "rooms/b_wall", "south", 0);
    no_wall = 1;
}

later()
{
    write("This area is still under construction... visit it later.\n");
/*
    write("A strong magic field prevents you from going there.\n");
*/
    return 1;
}
