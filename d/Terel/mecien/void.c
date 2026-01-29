inherit "/std/room";
#include <macros.h>
#include <stdproperties.h>

#define TP       this_player()
#define ETP      environment(TP)
#define TO       this_object()
#define DIRS     ({"north", "east", "south", "west",\
		   "northwest", "southwest", "northeast",\
		   "southeast", "up", "down"})
#define KEYS     ({2, 3, 0, 1, 7, 6, 5, 4, 9, 8})
#define MAXSOLVE 6

public void set_leave_key(string key);
public void set_last_room(object room);

int nexits, nsolved, exit_key;
string leave_key="", last_room="";

void
init()
{
    ::init();
    if (strlen(leave_key))
	add_action("do_leave", "regret", 0);
}

void
create_room()
{
    int i;

    set_short("Void");
    set_long(break_string(
     "All about abyssmal shadows beget unfathomable clouds of eerie "
    +"white mist. Wretched in its enthralling agony, this place wails in "
    +"its own mysterious misery, a confine of illicit solitude. Born of "
    +"deceitful and merciless primordial days, this is a void.\n", 72));

    for (i=0; i<sizeof(DIRS); i++)
	add_exit(file_name(TO), DIRS[i], "@@my_exit|"+i+"@@");

    set_noshow_obvious(1);
    exit_key = -1;
    nexits = 0;
    nsolved = 0;
    set_alarm(itof(10+random(60)), -1.0, "change_key");
}

void
enter_inv(object ob, object from)
{
    ::enter_inv(ob, from);
    if (!ob || interactive(ob)) return;
    if (living(ob)) {
        ob->remove_object();
        set_alarm(1.0, -1.0, "remove_object");
    } else {
	set_alarm(1.0, -1.0, "destroy_thing", ob);
    }
}

void
destroy_thing(object ob)
{
    if (!ob || environment(ob) != TO || interactive(ob)) return;
    tell_room(TO, "The " + ob->short() + " vanishes in the void.\n");
    ob->remove_object();
}

public void
set_leave_key(string key)
{
    leave_key = lower_case(key);
}

public void
set_last_room(object room)
{
    last_room = file_name(room);
}

void
change_key()
{
    if (nsolved >= MAXSOLVE && nsolved > nexits && strlen(leave_key)) {
	tell_room(TO, "You have defeated the deceitful mist.\n");
	tell_room(TO, "Perhaps being regretful to " +
		  capitalize(leave_key) + " will help you to " +
		  "leave the mysterious void.\n");
	return;
    }

    exit_key = random(sizeof(DIRS));
    tell_room(TO, "Suddenly you think you see an opening in the " +
		  "deceitful mist " + DIRS[exit_key] + "wards.\n");
    set_alarm(itof(10+random(60)), -1.0, "change_key");
}

int
my_exit(string exit_no)
{
    int i;

    sscanf(exit_no, "%d", i);

    if (exit_key < 0 || exit_key >= sizeof(KEYS)) return 0;

    if (KEYS[i] == exit_key) 
	nsolved++;
    else
        nexits++;

    exit_key = -1;
    return 0;
}

int
do_leave(string str)
{
    string whom;
    object who;

    if (!str || !strlen(leave_key)) return 0;

    if (nsolved < MAXSOLVE && nsolved <= nexits) return 0;

    notify_fail("Regret to whom?\n");
    if (sscanf(str, "to %s", whom) != 1) return 0;
    if (lower_case(whom) != leave_key) return 0;

    who = find_player(leave_key);

    write("As you regret to " + capitalize(leave_key) +
	  " you leave the ancient void.\n");
    if (who)
	who->catch_msg(QCTNAME(TP) + " is regretful and leaves the void.\n");

    if (!strlen(last_room))
	last_room = TP->query_default_start_location();
    if (TP->move_living("M", last_room, 1, 1))
        TP->move_living("M", TP->query_default_start_location(), 1, 1);

    tell_room(ETP, QCTNAME(TP) + " returns from the ancient void.\n", TP);

    set_alarm(2.0, -1.0, "remove_object");
    return 1;
}
