/*
 * This is the central object for things to happen in the mines.
 *     1. Meet elves.
 *     2. Meet dwarves.
 */

inherit "/std/object";

#include "defs.h"
#include "include/deeps.h"
#include <macros.h>
#include <filter_funs.h>
#include <filepath.h>

static mapping room_pos = ([]);

/* Prototypes */
void restore_data();
void run_loop();
void set_run_number(int i);
void meet_hawk(object who);
void meet_elves(object who);
void meet_dwarves(object who);
void dwarf_attack(object who);
void place_axe(object axe);
void try_make_orc();
void set_status(int new_status);

int alarm_id, alarm_id2, alarm_id3;



create_object()
{ 
    set_name("orb");
	set_alarm(0.0,0.0, restore_data);
}

remove_object() { 
    TO->save_data();
    ::remove_object();
}

//
// Now comes the interface for the rooms positions and types.
//

#define POS_NS 0
#define POS_EW 1
#define POS_UD 2
#define POS_HIDDEN 3

#define MAP_DATA (MORIA_DIR + "map/map.data")
#define HIDE "hide"

void
debug_message(string mesg)
{
    object wiz = find_player("odin");
    if (!wiz || !wiz->query_prop("_moria_i_wiz_message"))
	return;
    else
	wiz->catch_msg("#control# " + mesg + "\n");
}

void
save_data()
{
    FIXEUID;
    save_map(room_pos, MAP_DATA);
    debug_message("Saved data in " + MAP_DATA + ".o");
}

void
restore_data()
{
    FIXEUID;
    room_pos = restore_map(MAP_DATA);
    debug_message("Restored data from " + MAP_DATA + ".o");
}

string
get_index_name(mixed where)
{
    if (objectp(where)) 
	where = MASTER_OB(where);

    else if (strlen(where)) 
	where = FPATH(MINES_DIR, where);
    
    return where;
}

void
add_data(mixed where, ...)
{
    mixed *value;

    where = get_index_name(where);

    if (where[0..strlen(MINES_DIR)-1] != MINES_DIR) {
	write("Error in add_data(): Not a mines file: "+where+"\n");
	return;
    }
    sscanf(where, MINES_DIR + "%s", where);

    if (sizeof(argv) == 1) 
	value = argv[0];
    else
	value = argv;

    if (sizeof(value) < 3) {
	write("Error in add_data(): Too few args.\n");
	return;
    }
    
    restore_data();
    room_pos[where] = value;
    save_data();
}
	
mixed
room_position(mixed room)
{
    string pure, dummy;

    if (objectp(room))
	room = file_name(room);

    if (room[0] == '/') { 
	if (sscanf(room, MINES_DIR + "%s", pure) != 1)
	    return ({ -1, -1, -1});
    } else
	pure = room;

    if (sscanf(pure, "shaftcor#%s", dummy) == 1)
        return room->query_where()[0..2];

    if (!room_pos[pure])
	return ({ -2, -2, -2});

    return room_pos[pure][0..2];
}

string
query_data(mixed room)
{
    mixed data = room_position(room);
    return sprintf("%O\n", data);
}

#define SQRT(x) ftoi(pow(itof(temp), 0.5))

int
dist(mixed room1, mixed room2)
{
    mixed a, b;
    int i, temp=0;

    a = room_position(room1);
    b = room_position(room2);

    for (i=0;i<3;i++)
	temp += (b[i]-a[i])*(b[i]-a[i]);

    return SQRT(temp);
}

int
sorter(mixed a, mixed b)
{
    return b[1] - a[1];
}

void
find_dist(mixed from)
{
    mixed *dists = ({});
    mixed *ind = m_indexes(room_pos);
    int i;

    from = get_index_name(from);

    for(i=0; i<sizeof(ind); i++)
	dists += ({ ({ ind[i], dist(ind[i], from) }) });

    sort_array(dists, "sorter");

    for (i=sizeof(dists)-20; i<sizeof(dists); i++)
	write(sprintf("%20s : %6d %s\n", dists[i][0], dists[i][1], 
	                                 TO->short_dir(from, dists[i][0])));
}
    
int
direction_plane(mixed from, mixed to)
{
    mixed a, b;
    int x, y;

    a = room_position(from);
    b = room_position(to);

    x = b[0]-a[0];
    y = b[1]-a[1];

    if (x==0 && y==0)
	return 777;

    return ftoi(atan2(itof(y),itof(x)) * 200.0 / 3.14159);
}

string
direction_string(mixed from, mixed to)
{
    int degrees = direction_plane(from, to);

    switch (degrees) {
	case -200..-175: return "south";
	case -174..-125: return "southwest";
	case -124.. -75: return "west";
	case  -74.. -25: return "northwest";
	case  -24..  25: return "north";
	case   26..  75: return "northeast";
	case   76.. 125: return "east";
	case  126.. 175: return "southeast";
	case  176.. 200: return "south";
	default        : return "";
    }
}

#define MAX_INT 2147483647
#define MIN_INT -2147483648

int
rize(mixed from, mixed to)
{
    mixed a=room_position(from);
    mixed b=room_position(to);
    int i, temp = 0;

    for (i=0; i<2; i++)
	temp += (b[i] - a[i]) * (b[i] - a[i]);

    if (temp == 0)
	return b[2] >= a[2] ? MAX_INT : MIN_INT;

    return (b[2] - a[2]) * 100 / SQRT(temp);
}

string short_dir(mixed to, mixed from)
{
    int degrees = direction_plane(to, from);
    int rz = rize(to, from);
    string ret ="";
    switch (degrees) {
	case -200..-175: ret = "s"; break;
	case -174..-125: ret = "sw"; break;
	case -124.. -75: ret = "w"; break;
	case  -74.. -25: ret = "nw"; break;
	case  -24..  25: ret = "n"; break;
	case   26..  75: ret = "ne"; break;
	case   76.. 125: ret = "e"; break;
	case  126.. 175: ret = "se"; break;
	case  176.. 200: ret = "s"; break;    
    }

    if (rz > 60)
	return "UP";
    else if (rz > 45)
	return "UP ("+ret+")";
    else if (rz > 20)
	return "up ("+ret+")";
    else if (rz > 5)
	return ret + " (up)";
    else if (rz >= -5)
	return ret;
    else if (rz >= -20)
	return ret + " (down)";
    else if (rz >= -45)
	return "down ("+ret+")";
    else if (rz >= -60)
	return "DOWN ("+ret+")";
    else
	return "DOWN";
}

string *r_king	 =
    ({	"losttrck", "sleeping", "wardrobe", "armoury", "shieldch",
	"knightsh", "vicarage", "gallery",	"ballr", "ballrn",
	"ballrs", "ballrw" });

string *r_shaft  =
    ({	"shaftbot", "deadend", "shaftcor", "sheast", "shcrawl",
	"shgall1", "shgall2", "shnarhol", "shnarrw", "shroomne",
	"shroomnw", "shroomsw", "shroomse", "urukfore", "uruks",
	"prison", "prison2", "ringroom", "darkpass", "longnar1",
	"longnar2" });

string *r_not_ok = ({ "draglair", "mjunc", "happen", "islet" }) + r_shaft + r_king;

int
query_where(object r)					/* Level 7	1051 - 1225 */
{							/* Level 6	 876 - 1050 */
    string where, room, dummy;				/* Level 5       701 -  875 */
    mixed data;						/* Level 4	 526 -  700 */
    where = file_name(r);				/* Level 3	 351 -  525 */
							/* Level 2	 176 -  350 */
    if (sscanf(where, MINES_DIR+"%s", room)!=1)		/* Level 1         1 -  175 */
	return R_UNKNOWN;				/* Deep  1	-174 -    0 */
							/* Deep  2	-349 - -175 */
    data = room_position(r);				/* Deep  3	-524 - -350 */
    if (!data || !sizeof(data))				/* Deep  4	-699 - -525 */
	return 0;					/* Deep  5      -874 - -700 */
							/* Deep  6     -1049 - -875 */
    							/* Deep  7     -1226 - -1050 */
    return (data[2]+200)/175;				/*   Subtract:    24      24 */
}

int
mines_room(object what)
{
    string dummy;
    return what && sscanf(file_name(what), MINES_DIR + "%s", dummy)==1;
}

int
inside_moria(object who)
{
    return who && mines_room(ENV(who));
}

int
is_moria_obj(object what)
{
    string dummy;
    return what && sscanf(file_name(what), MORIA_DIR + "%s", dummy)==1;
}

int
ok_room(object r)
{
    string where = file_name(r);
    string room, dummy, dir;

    if (where[0] != '/')
	where = "/" + where;

    debug_message("ok_room: " + where + " ?");

    if (sscanf(where, MINES_DIR + "%s", dummy) != 1)
	return 0;
    
    where = dummy;

    if (sscanf(where, "%s/%s", dir, dummy) == 2)
	return 0;

    return member_array(where, r_not_ok) == -1;
}

int
in_ok_room(object who)
{
    object enemy;
    if (!objectp(who))
	return 0;
    enemy = who->query_attack();
    if (enemy && present(enemy, ENV(who)))
	return 0;
    return ok_room(ENV(who));
}


int run_number;
int run_status;

#define STATUS_VERY_SLOW 0
#define STATUS_SLOW      1
#define STATUS_FAST      2
#define STATUS_VERY_FAST 3
#define SPEED            ({ 240.0, 60.0, 20.0, 10.0 })

void
set_status(int new_status)
{
    //int time_left  = find_call_out("run_loop");
    int a;
	mixed alarm_info;
    float time_left;
	
	a = ftoi(time_left);

    alarm_info = get_alarm(alarm_id);

    if (!pointerp(alarm_info))
    {
	alarm_id = set_alarm((SPEED[new_status]), 0.0, run_loop);
	//call_out("run_loop", SPEED[new_status]);
    } 
    else
    {
	time_left = alarm_info[2];
	if (new_status > run_status && a > SPEED[run_status])
	{
	    remove_alarm(alarm_id);
	    //remove_call_out("run_loop");
	    alarm_id = set_alarm(SPEED[new_status], 0.0, run_loop);
	    //call_out("run_loop", SPEED[new_status]);
	}
	else if (new_status < run_status)
	{
	    remove_alarm(alarm_id);
	    //remove_call_out("run_loop");  /* 240 - 10 + 3 = 233 */
	    alarm_id = set_alarm((SPEED[new_status] - SPEED[run_status] + a),0.0, run_loop);
	    //call_out("run_loop", SPEED[new_status] - SPEED[run_status] + time_left);
	}
    }

    if (run_status != new_status)
    {
	debug_message("Going to status: " + run_status + ", alarm time: " + SPEED[run_status]);
    }
    run_status = new_status;
}

int
query_status()
{
    return run_status;
}

void
run_loop()
{
    object *p = users();
    int i, sz;
	mixed alarm_info;
	
	alarm_info = get_alarm(alarm_id);

    if (!pointerp(alarm_info))
	return;
	p = filter(p,inside_moria);
    //p = filter(p, "inside_moria", TO);
    sz = sizeof(p);

    if (sz == 0) {
	if (run_status > STATUS_SLOW)
	    set_status(STATUS_SLOW);
	else    
	    set_status(STATUS_VERY_SLOW);
	return;
    } else if (sz < 3) {
	set_status(STATUS_FAST);
    } else
	set_status(STATUS_VERY_FAST);

    if (run_number == 4) 
	alarm_id2 = set_alarm(1.0,0.0, try_make_orc);
	//call_out("try_make_orc", 1);

    i = random(sz);

    if (run_number%97 == 60) 
	alarm_id3 = set_alarm(1.0,0.0,&meet_elves(p[i]));
	//call_out("meet_elves", 1, p[i]);
//    else if (run_number%37 == 14) 
//	call_out("meet_dwarves", 1, p[i]);
    else if (run_number%23 == 4)
	alarm_id3 = set_alarm(1.0,0.0, try_make_orc);
	//call_out("try_make_orc", 1);
    else if (run_number%81 == 40) 
	alarm_id3 = set_alarm(1.0,0.0,&meet_hawk(p[i]));
	//call_out("meet_hawk", 1, p[i]);
    else if (run_number%31 == 5)
	p->catch_msg("A drumming can be heard from a distance.\n" +
		     "        Doom - doom - doom.\n" +
		     "The drumming echoes from deep inside the mountain.\n");
    run_number++;
}

void
set_run_number(int i)
{ 
	run_number = i; 
}

int
start_loop()
{
	mixed alarm_info;
	
	alarm_info = get_alarm(alarm_id);

	if (!pointerp(alarm_info))
    //if (find_call_out("run_loop") != -1)
	return 0;

    run_number = 1;
    run_status = STATUS_FAST;
    run_loop();
}

void
meet_elves(object who)
{
    object hat, crown, tp;
    
    if (!in_ok_room(who))
	return;

    debug_message(sprintf("Meeting elves, object: %s", who->query_name()));
    tp = TP;
    set_this_player(who);

    tell_room(ETP,
	"A group of white-clothed elves arrives singing and dancing around "+
	"a corner. Some play small golden harps, while others play flutes.\n");

    hat = present("_funny_hat_", TP);
    crown = present("_nice_crown_", TP);

    if ( (hat && hat->query_worn()) ||
	(crown && crown->query_worn()) )
    {
	tell_room(ETP,
	    "\n"+
	    "The elves sees you and the music stops at once.\n"+
	    "They stand silently for a while.\n"+
	    "A tall elf approaches and says:\n"+
	    "  I am Glorfindel, the leader of this party.\n"+
	    "  I can see from your head-dress that you are a friend of elves.\n");
	TP->catch_msg("Glorfindel asks you: Are you seeking Durin's Holy Axe?\n");
	tell_room(ETP, "Glorfindel asks "+QCTNAME(TP)+" a question.\n", TP);
	TP->catch_msg("Answer [yes/no] : ");
	input_to("answer_elves", 0);
	return;
    }
    tell_room(ETP,
	"\nAn elf shouts in terror: A troll!!!\n"+
	"All elves and music disappears..\n");
    set_this_player(tp);
}

void answer_elves(string ans)
{
    object leaf;

    if (ans=="yes")
    {
	tell_room(ETP,
	    "Glorfindel says:\n"+
	    "    We can not help you against trolls and monsters, but we can give\n"+
	    "    you some piece of advice. In the deeps of Moria, close to the\n"+
	    "    great Gates of the Dimrill Valley, there is a huge monster.\n"+
	    "    This is the Balrog, who has been in the Mountain since the dawn of time.\n"+
	    "\n"+
	    "Glorfindel continues:\n"+
	    "    No mortal have ever survived the meeting with the Balrog, but the\n"+
	    "    tales say that there is a greater power in the Axe of Durin, and if\n"+
	    "    you also have the revenging power of Aule, you might have a chance.\n"+
	    "\n");
	TP->catch_msg(
	    "Glorfindel whispers to you:\n"+
	    "    From us you get this valueable golden leaf from Lorien.\n"+
	    "    It has Powers within, which will surpass the Evil of the Enemy\n" +
	    "    and his Sorcery. You need only swirl it around something,\n"+
	    "    whereby the Evil is Undone.\n\n"+
	    "Glorfindel gives you a golden leaf.\n"
	);
	leaf = clone_object(MORIA_OBJ + "leaf");
	leaf->move(TP);
	tell_room(ETP,
	    "Glorfindel whispers something to "+QTNAME(TP)+".\n"+
	    "Glorfindel gives a golden leaf to "+HIM_HER(TP)+".\n", TP);
	tell_room(ETP,
	    "Glorfindel bows deeply and bids you farwell.\n"+
	    "Glorfindel and the group of elves leaves.\n");
    }
    else if (ans=="no") {
	tell_room(ETP,
	    "The elf gets solemn:\n"+
	    "    We do not allow anyone but revengers of Durin to share our knowledge.\n"+
	    "    Farewell!\n"+
	    "All elves disappear.\n");
    }
    else {
	TP->catch_msg("Glorfindel says: Please answer yes or no!\n"+"Answer [yes/no] : ");
	input_to("answer_elves", 0);
    }
}

meet_dwarves(object who)
{
    if (!in_ok_room(who)) {
	debug_message(sprintf("meet_dwarves : %O not OK!", ENV(who)));
	return;
    }

    debug_message(sprintf("Meeting dwarves, object: %s", who->query_name()));
    set_this_player(who);

    if (!present("_durins_axe_", TP))
	tell_room(ETP,
	    "A suspicious looking dwarf arrives around a corner.\n"+
	    "He looks at you carefully, grins and walks away.\n");
    else if (present("_the_lost_ring", TP))
	tell_room(ETP,
	    "A suspicious looking dwarf arrives around a corner.\n"+
	    "His eyes gleams when seeing the Axe of Durin!\n"+
	    "The dwarf grins and leaves.\n");
    else {
	tell_room(ETP,
	    "A suspicious looking dwarf arrives around a corner.\n"+
	    "His eyes gleams when seeing the Axe of Durin!\n"+
	    "The dwarf shouts: Naugrim enda niblim achtar Durin!!\n"+
	    "Several other dwarves comes running and attacks you!\n");
	set_alarm(0.0,0.0,&dwarf_attack(TP));
	//call_out("dwarf_attack",0,TP);
    }
}

object *dwarfs;
#define NO_DWARFS  10

object *
attacking_dwarfs()
{
    return dwarfs;
}

void
dwarf_attack(object who)
{
    int i;

    if (!dwarfs || sizeof(dwarfs)==0)
	dwarfs = allocate(NO_DWARFS);
    for(i=0;i<sizeof(dwarfs);i++)
    {
	if (!dwarfs[i] || !living(dwarfs[i]))
	{
	    dwarfs[i] = clone_object(MORIA_NPC+"dwarf");
	    dwarfs[i] -> create_me(i);
	}
	dwarfs[i] -> move_living("M", ETP);
	dwarfs[i] -> attack_object(who);
	dwarfs[i] -> add_prop(LIVE_O_ENEMY_CLING, who);
    }
}

void
dwarf_leave(object axe)
{
    int i;
    for(i=0;i<sizeof(dwarfs);i++)
    {
	if (dwarfs[i] && living(dwarfs[i]))
	    dwarfs[i]->move_living("away", MINES_DIR+"dwarfplc");
    }
	set_alarm((10*60),0.0,&place_axe(axe));
    //call_out("place_axe", 10*60, axe);
}

void
place_axe(object axe)
{
    if (!present("_durins_axe_", find_object(MINES_DIR+"kingsecr")))
	axe->move(MINES_DIR+"kingsecr");
    else
	axe->remove_object();
}

void
try_make_orc()
{
    debug_message((MINES_DIR+"orc_lair")->create_soldier());
}

object hawk;

/*
 * meet_hawk: The terrible sly hawk attacks!
 */
void
meet_hawk(object who)
{
    if (!in_ok_room(who))
	return;

    debug_message(sprintf("Meeting echo-hawk, object: %s", who->query_name()));
    set_this_player(who);

    if (!living(hawk))
	hawk = clone_object(MORIA_NPC + "echohawk");

    hawk->first_attack(who);
}

object
query_alchemist()
{
    return (MINES_DIR+"alch_home")->query_alchemist();
}

void
register_alchemist(object saver, object room)
{
    object alchemist = query_alchemist();

    FIXEUID;
    if (living(alchemist))
	alchemist->remove_object();

    alchemist = clone_object(MORIA_NPC + "alchemist");
    (MINES_DIR + "alch_home")->set_alchemist(alchemist); 
    alchemist->move_living("M", room);
    alchemist->thank_player_on_slab(saver);
}


string
stat_object()
{
    string ret = ::stat_object();
    
    ret += sprintf("Control data:\n" +
		   "-----------------------------------\n" +
		   "Running number...........: %5d\n" +
		   "Running status...........: %5d\n" +
		   "Call out time............: %5d\n" +
		   "Next call out............: %5d\n",
		   run_number, 
		   run_status,
		   SPEED[run_status],
		   find_call_out("run_loop"));

    ret += sprintf("\nMap data:\n" +
		   "----------------------------------\n" +
		   "# of rooms...............: %5d\n", m_sizeof(room_pos));

    ret += sprintf("\nMonster data:\n" +
		   "----------------------------------\n" +
		   "%s\n", (MINES_DIR + "orc_lair")->dump_soldiers());
    if (query_alchemist()) 
	ret += "Alchemist is alive in " + file_name(ENV(query_alchemist())) + "\n";

    ret += "\nWIZINFO:\n"+
	   "A handy wiz-tool for moria is /d/Shire/moria/obj/brooch.c\n";

    return ret;
}

