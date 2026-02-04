inherit "/std/room";

#include <stdproperties.h>
#include <macros.h>
#include <ss_types.h>
#include <wa_types.h>
#include <cmdparse.h>
#include <language.h>
#include <filter_funs.h>
#include <composite.h>

#define TP              this_player()
#define TO              this_object()
#define ETP             environment(TP)
#define AH(xx)          (xx->query_skill(SS_ANI_HANDL))
#define TP_AH           (TP->query_skill(SS_ANI_HANDL))
#define NF(xx)          notify_fail(xx + "\n")
#define RIDE_PROP       "_can_ride_here"
#define HORSE_SHADOW    "/d/Terel/mortricia/horses/hsh"
#define CMDS            ({"w", "west",  "nw", "northwest", \
			  "s", "south", "sw", "southwest", \
			  "e", "east",  "ne", "northeast", \
			  "n", "north", "se", "southeast", \
			  "u", "up", \
			  "d", "down", \
			  "halt"})

static object horse;
static object shadow;
static int running;
static int speed;
static int max_speed;
static int alarm_id=0;
static int hlt_flg;
static int weight;
static int max_weight;

public  void   set_horse(object ob);
public  object query_horse();
public  int    query_running();
public  int    query_max_speed();
public  int    query_max_weight();
public  string get_desc(string type, object who, object where);
private int    cmd_check(string s1, string s2);
private string check_dir_cmd(string d, object where);
private string get_dir_cmd(string d, object where);
public  void   halt_horse();
private void   make_horse_go(string dir);
private int    half_ran(int i);
public  void   fall_of_horse();
private void   remove_thing(object ob);
public  int    do_cmd(string str);
public  int    do_pre_cmd(string str);

public void
init()
{
    int i;

    ::init();
    add_action("dismount", "dismount");
    add_action("do_shout", "shout");
    add_action("do_cmd",   "command");
    add_action("do_cmd",   "cmd");

    for (i=0; i<sizeof(CMDS); i++)
	add_action("do_pre_cmd", CMDS[i]);
}

public void
create_room()
{
    set_short("@@my_short");
    set_long("@@my_long");

    set_noshow_obvious(1);
    add_prop(ROOM_I_INSIDE, 0);

    add_item("horse", "@@my_horse");
    add_prop(OBJ_S_WIZINFO,
        "This horse can be commanded by:\n" +
        "   cmd <dir> [<how>]\n" +
        "where <dir> is a valid exit, and <how> is either\n" +
        "   slowly, gently, quickly, or rapidly\n" +
        "which indicates the speed. The horse will then start to move,\n" +
        "at the selected speed, in the direction <dir>. If the <dir>\n" +
        "doesn't exist, it will try to move in neighbouring directions.\n" +
        "For instance; 'cmd n gently' will also try ne and nw. The horse\n" +
        "will stop when no exits are available. If <how> is omitted then\n" +
        "the horse will take one step in the direction <dir>. This will\n" +
        "also work if <dir> = 'enter', and 'enter' is an exit. Moreover,\n" +
        "it is impossible to ride the horse in an indoor room unless the\n" +
        "room has a special property set (\"_can_ride_here\").\n" +
        "Some other commands are:\n" +
        "    cmd halt              will stop the horse from running\n" +
        "    cmd disembark         will work on ships\n" +
        "    cmd enter mist        may also work if triggered by the room\n" +
        "    mount horse\n" +
        "    dismount\n" +
        "Certain commands, i.e. shout and say, will be heard outside the\n" +
        "horse. In its present version no emotional commands will be heard.\n" +
        "Cheers, Mortricia\n\n"
    );
}

public string
my_short()
{
    if (horse) return get_desc("s", TP, environment(horse));
    return "This shouldn't happen, something is wrong";
}

public string
my_long()
{
    if (horse) return get_desc("l", TP, environment(horse));
    return "This shouldn't happen, something is wrong.\n";
}

public string
my_horse()
{
    if (!horse) return "This shouldn't happen, something is wrong.\n";
    return horse->long();
}

public void
add_my_name_item(string pet_name)
{
    add_item(pet_name, "@@my_horse");
}

public void
enter_inv(object ob, object from)
{
    int new_weight;

    ::enter_inv(ob, from);
    if (!living(ob)) {
	new_weight = weight + ob->query_prop(OBJ_I_WEIGHT);
	if (new_weight > max_weight) {
            set_alarm(1.0, -1.0, &remove_thing(ob));
	} else {
	    weight = new_weight;
	}
    }
    if (!horse) return;
    if (horse->query_mounted() == ob) {
        seteuid(getuid());
        shadow = clone_object(HORSE_SHADOW);
        if (!shadow->shadow_me(ob)) {
            shadow->remove_shadow();
        }
    }
}

private void
remove_thing(object ob)
{
    if (!ob) return;
    if (!horse) {
	ob->remove_object();
	return;
    }
    ob->move(environment(horse));
    tell_room(environment(horse), capitalize(LANG_ADDART(
	      ob->short())) + " falls of the " +
	      horse->short() + ".\n");
}

public void
leave_inv(object ob, object to)
{
    ::leave_inv(ob, to);
    if (!living(ob)) {
	weight -= ob->query_prop(OBJ_I_WEIGHT);
    }
    if (!horse) return;
    if (horse->query_mounted() == ob) {
        if (shadow) shadow->remove_shadow();
        horse->set_rider(0);
    }
}

public int
do_shout(string str)
{
    object *dumb;
    
    NF("Shout what?");
    if (!str) return 0;

    if (TP->query_get_echo()) {
        write("You shout: "+str+"\n");
    } else {
	write("Ok.\n");
    }
    say(QCTNAME(TP) + " shouts: " + str + "\n");
    if (!horse) return 1;
    dumb = ({ TP, horse });
    if (horse->query_horse_flea()) dumb += ({ horse->query_horse_flea() });
    tell_room(environment(horse), QCTNAME(TP) +
			 " shouts: " + str + "\n", dumb);
    return 1;
}

public int
dismount(string str)
{
    object *obs;

    NF(capitalize(query_verb()) + " what?");
    if (!horse) return 0;
    if (str) {
        obs = FIND_STR_IN_OBJECT(str, environment(horse));
        if (sizeof(obs) == 0 || sizeof(obs) > 1) return 0;
        if (obs[0] != horse) return 0;
    }

    if (running) {
        if (TP == horse->query_mounted()) {
	    write("You better halt the "+horse->short()+" first.\n");
        } else {
	    write("The "+horse->short()+" is running!\n");
	}
	return 1;
    }

    write("You dismount the "+horse->short()+".\n");
    say(QCTNAME(TP) + " dismounts the "+horse->short()+".\n");
    TP->move_living("M", environment(horse));
    say(QCTNAME(TP) + " dismounts the "+horse->short()+".\n");
    return 1;
}

public int
do_pre_cmd(string str)
{
    string arg;

    arg = query_verb();
    if (strlen(str)) arg += " " + str;

    return do_cmd(arg);
}

public int
do_cmd(string str)
{
    int i;
    string s1="", s2="";
    string dir_cmd, how;

    NF("What ?");
    if (!str || !horse) return 0;
    if (TP != horse->query_mounted() && TP->query_wiz_level() < 15) return 0;

    NF("Command where how?");
    if (sscanf(str, "%s %s", s1, s2) != 2) {
	s2 = "";
	if (sscanf(str, "%s", s1) != 1) return 0;
    }

    if (s1 == "halt") {
	NF("It's not running.");
	if (!running) return 0;
	if (half_ran(TP_AH) < 10) {
	    write("The "+horse->short()+ " doesn't obey you!\n");
	    return 1;
	}
	write("You halt the " + horse->short()+".\n");
	say(QCTNAME(TP) + " halts the " + horse->short() + ".\n");
	halt_horse();
	return 1;
    }
    if (i = cmd_check(s1, s2)) {
	if (running) halt_horse();
	if (i == 1) {
	    write("You command the "+horse->short()+
	          " to "+s1+".\n");
	    say(QCTNAME(TP) + " commands the "+horse->short()+
	          " to "+s1+".\n");
	    horse->command(s1);
	}
	if (i == 2) {
	    write("You command the "+horse->short()+
	          " to "+s1+" the "+s2+".\n");
	    say(QCTNAME(TP)+" commands the "+horse->short()+
	          " to "+s1+" the "+s2+".\n");
	    horse->command(s1 + " " + s2);
	}
	return 1;
    }
    if (!strlen(s2)) {
        dir_cmd = check_dir_cmd(s1, environment(horse));
        NF("Command what/where?");
        if (strlen(dir_cmd) == 0) return 0;
	NF("You cannot ride there!");
	if (dir_cmd == "_indoor_") return 0;
        if (half_ran(TP_AH) < 10) {
	    write("The "+horse->short()+ " doesn't obey you!\n");
	    return 1;
	}
	if (running) halt_horse();
	write("You command the "+horse->short()+
	      " to the "+dir_cmd+".\n");
	say(QCTNAME(TP)+" commands the "+horse->short()+
	      " to the "+dir_cmd+".\n");
	horse->command(dir_cmd);
	return 1;
    }
    dir_cmd = get_dir_cmd(s1, environment(horse));
    NF("Command where how?");
    if (strlen(dir_cmd) == 0) return 0;
    NF("You cannot ride there!");
    if (dir_cmd == "_indoor_") return 0;
    speed = 0;
    if (s2 == "slow"   || s2 == "slowly")  {speed = 1; how = "slowly";}
    if (s2 == "gentle" || s2 == "gently")  {speed = 2; how = "gently";}
    if (s2 == "quick"  || s2 == "quickly") {speed = 3; how = "quickly";}
    if (s2 == "rapid"  || s2 == "rapidly") {speed = 6; how = "rapidly";}
    NF("Command "+s1+" how?");
    if (speed == 0) return 0;
    if (half_ran(TP_AH) < 10 || speed > max_speed) {
	write("The "+horse->short()+ " doesn't obey you!\n");
	return 1;
    }
    write("You command the " + horse->short() + " to " + how +
	  " go to the " + dir_cmd + ".\n");
    say(QCTNAME(TP)+" commands the " + horse->short() + " to " + how +
	  " go to the " + dir_cmd + ".\n");
    hlt_flg = 0;
    if (alarm_id) {
        remove_alarm(alarm_id);
        alarm_id = 0;
    }
    make_horse_go(s1);
    return 1;
}

public void
halt_horse()
{
    hlt_flg = 1;
    if (!running) return;
    if (alarm_id) {
        remove_alarm(alarm_id);
        alarm_id = 0;
    }
    running = 0;
}

private void
make_horse_go(string dir)
{
    string dir_cmd;
    object ob;

    if (hlt_flg || !horse) {
	hlt_flg = 0;
	return;
    }

    dir_cmd = get_dir_cmd(dir, environment(horse));
    ob = horse->query_mounted();
    if (!strlen(dir_cmd) || dir_cmd == "_indoor_") {
	halt_horse();
	if (ob) ob->catch_msg("The " + horse->short() +
		      " halts and looks irresolute.\n");
	return;
    }
    running = 1;
    if (ob) {
	if (half_ran(AH(ob)) < 2 * speed + 15) fall_of_horse();
    }
    horse->command(dir_cmd);
    
    alarm_id = set_alarm(itof(12/speed), -1.0, &make_horse_go(dir));
    return;
}

public void
fall_of_horse()
{
    object ob;

    if (!horse) return;
    ob = horse->query_mounted();
    if (!ob || environment(ob) != TO) return;

    ob->catch_msg("Oops! You fall off the "+horse->short()+"!\n");
    say(QCTNAME(ob) + " falls of the " + horse->short() + ".\n", ob);
    ob->move_living("M", environment(horse));
    say(QCTNAME(ob) + " falls of the " + horse->short() + ".\n", ob);
}

public void
set_horse(object ob)
{
    horse = ob;
    switch (ob->query_stat(SS_DEX)) {
        case 0..20:
            max_speed = 1;
            break;
        case 21..40:
            max_speed = 2;
            break;
        case 41..60:
            max_speed = 3;
            break;
        case 61..9999:
            max_speed = 6;
            break;
        default:
            max_speed = 1;
            break;
    }
    max_weight = 1000*(ob->query_stat(SS_STR));
}

public object
query_horse()
{
    return horse;
}

public int
query_running()
{
    if (!running) return 0;
    return speed;
}

public string
get_desc(string type, object who, object where)
{
    int i;
    string s, item;
    object *ob, *dd, *lv;

    if (type == "l") s = where->long();
    if (type == "s") {
	s = where->short() +".\n";
	if (!where->query_noshow_obvious()) s += where->exits_description();
    }
    ob = all_inventory(where);

    dd = FILTER_DEAD(ob);
    dd = FILTER_CAN_SEE(dd, who);
    item = (string) COMPOSITE_FILE->desc_dead(dd, 1);
    if (item) s += break_string(capitalize(item) + ".", 76) + "\n";

    lv = FILTER_LIVE(ob);
    lv = FILTER_CAN_SEE(lv, who);
    i = member_array(horse, lv);
    if (i >= 0) lv = exclude_array(lv, i, i);
    item = (string) COMPOSITE_FILE->desc_live(lv, 1);
    if (item) s += break_string(capitalize(item) + ".", 76) + "\n";

    return s;
}

private string
check_dir_cmd(string d, object where)
{
    int i, j;
    string r="", s="";
    string *paths, file;
    object togo;

    s = d;
    if (d == "n"  || d == "north")     s = "north";
    if (d == "w"  || d == "west")      s = "west";
    if (d == "s"  || d == "south")     s = "south";
    if (d == "e"  || d == "east")      s = "east";
    if (d == "nw" || d == "northwest") s = "northwest";
    if (d == "ne" || d == "northeast") s = "northeast";
    if (d == "sw" || d == "southwest") s = "southwest";
    if (d == "se" || d == "southeast") s = "southeast";
    if (d == "u") s = "up";
    if (d == "d") s = "down";

    j = member_array(s, where->query_exit_cmds());
    if (j < 0) {
	for (i=0; i<sizeof(CMDS); i++)
	    if (s == CMDS[i]) return s;
	return r;
    }
    paths = where->query_exit_rooms();
    file = process_string(paths[j]);
    file->short();
    togo = find_object(file);
    if (!togo) return r;
    if (togo->query_prop(ROOM_I_INSIDE)==0 || togo->query_prop(RIDE_PROP)) {
        r = s;
    } else {
	r = "_indoor_";
    }
    return r;
}

private string
get_dir_cmd(string d, object where)
{
    int i, j, ef_val;
    string r="", s, file;
    string *arr, *paths;
    mixed *qef;
    object togo;

    s = d;
    if (d == "n"  || d == "north")     s = "north";
    if (d == "nw" || d == "northwest") s = "northwest";
    if (d == "w"  || d == "west")      s = "west";
    if (d == "sw" || d == "southwest") s = "southwest";
    if (d == "s"  || d == "south")     s = "south";
    if (d == "se" || d == "southeast") s = "southeast";
    if (d == "e"  || d == "east")      s = "east";
    if (d == "ne" || d == "northeast") s = "northeast";
    if (d == "u") s = "up";
    if (d == "d") s = "down";

    arr = ({ s });
    if (s == "north")     arr = ({"north", "northwest", "northeast"});
    if (s == "northwest") arr = ({"northwest", "north", "west"});
    if (s == "west")      arr = ({"west", "northwest", "southwest"});
    if (s == "southwest") arr = ({"southwest", "west", "south"});
    if (s == "south")     arr = ({"south", "southwest", "southeast"});
    if (s == "southeast") arr = ({"southeast", "south", "east"});
    if (s == "east")      arr = ({"east", "southeast", "northeast"});
    if (s == "northeast") arr = ({"northeast", "east", "north"});
    if (s == "up")        arr = ({"up"});
    if (s == "down")      arr = ({"down"});

    for (i=0; i<sizeof(arr); i++) {
	 j = member_array(arr[i], where->query_exit_cmds());
	 if (j < 0) continue;
	 qef = where->query_exit_functions();
	 if (intp(qef[j])) {
	     ef_val = qef[j];
	 } else if (stringp(qef[j])) {
	     ef_val = process_value(qef[j]);
	 } else {
	     ef_val = 1;
	 }
	 if (ef_val != 0) continue;
	 paths = where->query_exit_rooms();
	 file = process_string(paths[j]);
	 file->short();
	 togo = find_object(file);
	 if (!togo) continue;
         if (togo->query_prop(ROOM_I_INSIDE)==0 ||
             togo->query_prop(RIDE_PROP)) {
	     r = arr[i];
	     break;
	 } else {
             r = "_indoor_";
	 }
    }

    return r;
}

private int
half_ran(int i)
{
    if (i==0) return 0;
    return (i + random(i))/2;
}

private int
cmd_check(string s1, string s2)
{
    if (s1 == "enter" ||
        s1 == "board" ||
        s1 == "disembark" ||
        s1 == "exit" ||
        s1 == "leave") {
	if (strlen(s2)) return 2;
	return 1;
    }
    return 0;
}

public int
query_max_speed()
{
    return max_speed;
}

public int
query_max_weight()
{
    return max_weight;
}
