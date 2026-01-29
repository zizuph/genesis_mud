/*
 * /d/Gondor/common/lib/river.c
 * 
 * Inherit this if you want to make a river with a current. 
 * Created by Elessar, Jan 94 - June 95.
 * Modification log:
 * Cleaned up a bit and moved from Elessar's home dir to ~Gondor/common/lib
 */
inherit "/d/Gondor/common/room";
#include <stdproperties.h>
#include <ss_types.h>
#include <macros.h>
#include <formulas.h>
#include <composite.h>
#include "/d/Gondor/defs.h"

#define LIVE_I_SWIM_HERE	"_live_i_swim_here"
#define LIVE_I_UNCONSCIOUS	"_live_i_unconscious"

string  rivertype,
        landname,
        cur_dir,
        up_dir,
       *shore,
        rivername,
        extraline;
int     cur_str;

/* prototypes */
string roomobj(string cdir);
int downstream(object obj, int fati, int swim);
int upstream(object obj, int fati);
int decr_hp(object pl, int fati);
void current(object obj);
void boat_current(object obj);
void object_current(object obj);
void sink(object obj);

string 
convert_dir(string dir)
{
    switch(dir) 
    {
    case "n":
        return "north"; 
        break;
    case "ne":
        return "northeast"; 
        break;
    case "e":
        return "east"; 
        break;
    case "se":
        return "southeast"; 
        break;
    case "s":
        return "south"; 
        break;
    case "sw":
        return "southwest"; 
        break;
    case "w":
        return "west"; 
        break;
    case "nw":
        return "northwest"; 
        break;
    case "u":
        return "up"; 
        break;
    case "d":
        return "down"; 
        break;
    default:
        return dir;
        break;
    }
}

int 
query_exit_fatigue(string dir)
{
    int i;
    mixed *exit_arr = query_exit();
    while (i < sizeof(exit_arr) / 3) 
    {
        if (dir == exit_arr[i * 3 + 1]) 
            return exit_arr[i * 3 + 2];
        i++;
    }
    return 0;
}

int 
exist_dir(string dir)
{
    mixed *exit_arr = query_exit();
    int i;

    while (i < sizeof(exit_arr) / 3) 
    {
        if (dir == exit_arr[i * 3 + 1]) 
            return 1;
        i++;
    }
    return 0;
}

int 
do_drown(object pl)
{
    pl->catch_tell("You drowned!\n"); /* To be implemented */
    pl->set_hp(0);
    pl->remove_prop(LIVE_I_UNCONSCIOUS);
    pl->do_die(TO);
    log_file("drown", capitalize(pl->query_real_name()) + " (" + 
        pl->query_avg_stat() + ") drowned in the river " + rivername + ", on " + 
        ctime(time())+".\n  Swim skill: " + pl->query_skill(SS_SWIM) + ", " +
        " and the current was " + cur_str + " strong.\n");
    return 1;
}

int 
can_swim(string dir, object pl)
{
    int cs, 
        ss = pl->query_skill(SS_SWIM), 
        fl;

    
    if (pl->query_prop(LIVE_I_UNCONSCIOUS))
        return decr_hp(pl, 500);

    if (dir == cur_dir) 
    { 
        fl = cur_str / 10 - ss / 10; 
        cs = cur_str - 10; 
    }
    else if (dir == up_dir) 
    { 
        fl = cur_str / 4 - ss / 6; 
        cs = cur_str + 10; 
    }
    else 
    { 
        cs = cur_str; 
        fl = cur_str / 4 - ss / 5; 
    }
 
    if (fl < 5) 
        fl = 5;

    if (cs > ss) 
    {
        pl->add_fatigue(-fl);
        return 0;
    }
    else if (fl > pl->query_fatigue())
        return decr_hp(pl, fl);

    pl->add_fatigue(-fl);
    return 1;
}

int 
try_swim(object pl, string dir)
{
    int i = can_swim(dir,pl);
    string txt,
           room;

    dir = convert_dir(lower_case(dir));

    if (i > 0) 
    {
        room = roomobj(dir);
        if (member_array(dir, shore)) 
        {
            write("You swim " + dir + ", and manage to climb ashore.\n");
            tell_room(room, QCNAME(pl) + " comes swimming, and climbs out " +
                "of the water, dripping wet.\n", pl);
        }
        else 
        {
            write("You swim further " + dir + ".\n");
            tell_room(room, QCNAME(pl) + " comes swimming.\n", pl);
        }

        pl->move_living("M", room, 1, 0);
        return 1;
    }
    else if (!i) 
        txt = "The current proves too strong for you,";
    else 
        txt = "You are too tired to resist the pull of the current,";

    write(txt + " and you are washed away downstream.\n");
    downstream(pl, query_exit_fatigue(dir), 0);
    return 1;
}

int 
query_float(object obj)
{
    if (obj->query_prop(OBJ_I_WEIGHT) < obj->query_prop(OBJ_I_VOLUME)) 
        return 1;
    else
        return 0;
}

string 
roomobj(string cdir)
{
    int n;
    string *exit_arr = TO->query_exit();

    while (n < sizeof(exit_arr) / 3) 
    {
        if (exit_arr[n * 3 + 1] == cdir)
            return exit_arr[n * 3];
        n++;
    }
}

string 
cur_adj(int cs)
{
    cs = cs / 10;

    switch(cs)
    {
    case 0:
        return "stagnant";
        break;
    case 1:
        return "quiet";
        break;
    case 2:
        return "slight";
        break;
    case 3:
        return "gentle";
        break;
    case 4:
        return "moderate";
        break;
    case 5:
        return "swift";
        break;
    case 6:
        return "rough";
        break;
    case 7:
        return "strong";
        break;
    case 8:
        return "rapid";
        break;
    case 9:
        return "wild";
        break;
    case 10:
        return "torrential";
        break;
    default:
        return "ferocious"; 
        break;
    }
}

int 
do_swim(string dir)
{
    if (!dir && query_verb() != "swim") 
        dir = query_verb();

    if (!dir || dir == "here") 
    {
        this_player()->add_prop(LIVE_I_SWIM_HERE, 1);
        write("You start swimming in attempt to stay against the "
          + cur_adj(cur_str) + " current.\n");
        say(QCTNAME(this_player()) + " starts swimming not to get washed " +
            "away by the " + cur_adj(cur_str) + " current.\n", this_player());
        return 1;
    }

    dir = convert_dir(dir);
    if (!exist_dir(dir)) 
    {
        notify_fail("It is impossible to swim in that direction!\n");
        return 0;
    }

    if (dir == cur_dir) 
        downstream(this_player(), query_exit_fatigue(dir), 1);
    else if (dir == up_dir) 
        upstream(this_player(), query_exit_fatigue(dir));
    else 
        try_swim(this_player(), dir);
    return 1;
}

string 
short_func()
{
    return "In a " + cur_adj(cur_str) + " part of the " + rivertype + " " + 
        rivername;
}

string 
describe()
{
    string txt = "You are floating in the " + rivername + ". The current " +
        "in the " + rivertype + " is " + cur_adj(cur_str) + " here, " + 
        "continuing " + cur_dir + " through " + landname + ". ";

    if (shore) 
    {
        txt = txt + "To the ";
        if (sizeof(shore) == 1) 
            txt = txt + shore[0] + " is the shore. ";
        else 
            txt = txt + COMPOSITE_WORDS(shore);
    }

    if (extraline) 
        return (txt + extraline + "\n");
    else 
        return (txt + "\n");
}

void 
make_the_room()
{
    set_short("@@short_func@@");
    set_long("@@describe@@");
    set_noshow_obvious(1);
    add_prop(ROOM_I_TYPE, ROOM_IN_WATER);
}

void 
init()
{
    ::init();
    add_action("do_swim","swim");
}

void 
enter_inv(object obj, object from)
{
    ::enter_inv(obj, from);

    if (living(obj))
        set_alarm(itof(110 - cur_str), 0.0, &current(obj));
    else if (obj->query_boat())
        set_alarm(itof(160 - cur_str), 0.0, &boat_current(obj));
    else if (query_float(obj))
        set_alarm(itof(110 - cur_str), 0.0, &object_current(obj));
    else
        set_alarm(4.0 + rnd()*10.0, 0.0, &sink(obj));
}

void
current(object obj)
{
    int fat, swimskill;

    if (!objectp(obj) || ENV(obj) != TO) 
        return;

    swimskill = obj->query_skill(SS_SWIM);
    fat = cur_str / 5 - swimskill / 5;
    if (fat < cur_str / 10) 
        fat = cur_str/10; 

    if (obj->query_prop(LIVE_I_SWIM_HERE))
    {
        if (obj->query_fatigue() < fat)
	{
            obj->catch_tell("You are too fatigued to keep swimming " +
                "against the current.\n");
            downstream(obj, fat, 0);
            return;
	}
        obj->add_fatigue(-fat);
        obj->catch_tell("You continue swimming to keep up with the current.\n");
        tell_room(TO, QCTNAME(obj) + " swims to keep up with the current.\n",
            obj);
        return;
    }

    downstream(obj, fat, 0);
}

int 
decr_hp(object pl, int fati)
{
    pl->set_hp(-(fati * 2));
    pl->catch_tell("You swallow some water and feel that you are drowning!\n");
    tell_room(TO, QCTNAME(pl) + " is coughing and sputtering water!\n", pl);

    if (pl->query_hp() < 0)
    {
        do_drown(pl);
        return -2;
    }

    return -1;
}

varargs int
downstream(object pl, int fati, int swim = 0)
{
    int result = can_swim(cur_dir, pl);

    /* If player drowned, stop further swimming :) */
    if (result == -2) 
        return 1; 

    if (!swim || (result <= 0))
    {
        pl->catch_tell("You are pulled by the " + cur_adj(cur_str) +
            " current " + cur_dir + ".\n");
        say(QCTNAME(pl) + " is pulled by the " + cur_adj(cur_str) + 
            " current " + cur_dir + ".\n", pl);
    }
    else 
    {  
        pl->catch_tell("You swim " + cur_dir + " with the water current.\n");
        say(QCTNAME(pl) + " swims " + cur_dir + " with the water current.\n",
            pl);
    }

    tell_room(roomobj(cur_dir), QCTNAME(pl) + " comes floating down the " +
        rivertype + ".\n");
    pl->move_living("M", roomobj(cur_dir), 1, 0);
    return 1;
}

int 
upstream(object pl, int fati)
{
    int result = can_swim(up_dir, pl);

    if (result == -2) 
        return 1;
    else if (result == -1) 
    {
        pl->catch_tell("You were too exhausted to swim up against the " +
            "current.\n");
        return 1;
    }
    else if (!result) 
    {
        pl->catch_tell("The current is too strong for you to swim up " +
            "against.\n");
        return 1;
    }

    pl->catch_tell("You swim up the " + rivertype + " against the " + 
        cur_adj(cur_str) + " current, " + up_dir + "wards.\n");
    say(QCTNAME(pl) + " swims away " + up_dir + " against the " + 
        cur_adj(cur_str) + " current.\n");
    tell_room(roomobj(up_dir), QCNAME(pl) + " comes swimming against the " +
        "current.\n");
    pl->move_living("M", roomobj(up_dir), 1, 0);
    return 1;
}

void
object_current(object obj)
{
    tell_room(TO, LANG_THESHORT(obj) + " floats down the " + cur_dir +
        " with the " + cur_adj(cur_str) + " current.\n");
    obj->move(roomobj(cur_dir), 1);
    tell_room(roomobj(cur_dir), LANG_THESHORT(obj) + " comes floating down " +
        "the " + rivertype + ".\n");
}

void
sink(object obj)
{
    tell_room(TO, LANG_THESHORT(obj) + " sinks down to the bottom of the " + 
        rivertype + ".\n");
    (ANDUIN_DIR + "river_bottom")->teleledningsanka();
    obj->move(ANDUIN_DIR + "river_bottom", 1);
}

void
boat_current(object boat)
{
    boat->notify_inv("The " + boat->query_name() + " floats with the "+
        cur_adj(cur_str) + " " + cur_dir + " down the " + rivertype + ".\n");
    object_current(boat);
}

int 
query_cur_str()
{ 
    return cur_str; 
}

string 
query_cur_dir()
{ 
    return cur_dir; 
}

string 
query_up_dir()
{ 
    return up_dir; 
}

