/*
 * This is the central object for things to happen in the mines.
 *     1. Meet elves.
 *     2. Meet dwarves.
 */

inherit "/std/object";

#include "defs.h"
#include <macros.h>
#include <filter_funs.h>
#include <filepath.h>

#define HIDE "hide"

/*
 * Positioning of places.
 */

#ifdef NOT_SAVED_IN_MAPPING
static mapping room_pos = ([
    "stair0"   : ({    0,    0, -200 }),
    "stair1"   : ({    0,  100, -100 }),
    "stair2"   : ({    0,  200,    0 }),
    "mjunc"    : ({    0,  300,    0 }),
    "cavern"   : ({ -100,  300,  -25 }),
    "study"    : ({ -100,  335,  -35, HIDE }),
    "widepas1" : ({ -100,  200,  -30 }),
    "widepas2" : ({ -200,  200,  -45 }),
    "cross"    : ({ -300,  200,  -75 }),
    "privclos" : ({ -350,  200,  -90 }),
    "roundchb" : ({ -300,  300, -100 }),
    "lake_w"   : ({ -400,  300, -140 }),
    "islet"    : ({ -400,  400, -140 }),
    "litt"     : ({    0,  400,    0 }),
    "longr1"   : ({    0,  500,    0 }),
    "pyramid"  : ({ -100,  500,    0, HIDE }),
    "rattrap"  : ({ -100,  550,    0, HIDE }),
    "dwelling" : ({ -150,  550,    0, HIDE }),
    "longr2"   : ({    0,  600,    0 }),
    "corridor" : ({    0,  700,    0 }),
    "corr1"    : ({    0,  800,  -30 }),
    "corr2"    : ({    0,  900,  -60 }),
    "corr3"    : ({    0, 1000,  -90 }),
    "corr4"    : ({    0, 1100, -120 }),
    "corr5"    : ({    0, 1200, -150 }),
    "corr6"    : ({    0, 1300, -155 }),

    "gallhall" : ({ -100, 1100, -100 }),
    "gall_e"   : ({ -100, 1130, -100 }),
    "gall_s"   : ({ -150, 1100, -100 }),
    "gallcrck" : ({ -150, 1085, -100 }),
    "bighalln" : ({ -150, 1100, -200 }),
    "bighalls" : ({ -200, 1100, -200 }),
    "archway"  : ({ -300, 1100, -180 }),
    "stneslab" : ({ -400, 1100, -150 }),
    "byhole"   : ({ -440, 1100, -180 }),
    "inhole"   : ({ -450, 1100, -182 }),
    "lake_e"   : ({ -400, 1000, -140 }),

    "dirthole" : ({  -50, 1300, -160 }),
    "slime"    : ({  -50, 1250, -150 }),
    "clampass" : ({ -100, 1300, -165 }),
    "partoff"  : ({ -100, 1340, -170 }),
    "depress"  : ({ -175, 1300, -185 }),
    "lowroom"  : ({ -180, 1200, -190 }),
    "west_dep" : ({ -190, 1100, -160 }),
    "narrfiss" : ({ -200, 1000, -150 }),
    "fiss_s"   : ({ -250, 1000, -140 }),
    "fiss_n"   : ({ -150, 1000, -140 }),
    "easthall" : ({ -200,  900, -135 }),
    "westhall" : ({ -200,  700, -135 }),
    "narrpass" : ({ -200,  500, -125 }),
    "maritime" : ({ -100,  500, -100 }),
    "smhollow" : ({    0,  500, -100 }),
    "eelpass"  : ({    0,  400, -100 }),
    "deep/shaft1": ({    0,  300, -100 }),

    "cornerch" : ({  100,  500, -100 }),
    "boring"   : ({  100,  600, -100 }),
    "dopening" : ({  200,  600, -100 }),
    "big_hall" : ({  200,  700, -100 }),
    "ovalroom" : ({  200,  800, -100 }),
    "suddenst" : ({  170,  800,    0 }),
    "lpass2"   : ({  150,  700,    0 }),
    "lpass1"   : ({  130,  600,    0 }),
    "stonechb" : ({  110,  500,    0 }),	  /* S: corr1  0, 800, -30 */
    "sqchambe" : ({  100,  400,    0 }),
    "npass1"   : ({  100,  300,   15 }),
    "npass2"   : ({  200,  300,   30 }),
    "throne"   : ({  200,  400,   45 }),
    "draperies": ({  185,  400,   45 }),
    "durhall"  : ({  200,  500,   40 }),
    "guestroom": ({  100,  450,   40 }),	  /* D: sqchambe 100, 400, 0 */
    "crosroad" : ({  200,  600,   50 }),
    "goldroom" : ({  250,  600,   50 }),
    "bat_cave" : ({  200,  700,   50 }),
    "cave_n"   : ({  250,  700,   50 }),
    "cave_e"   : ({  200,  750,   50 }),
    "dome"     : ({  150,  700,   50 }),
    "dirtrock" : ({  150,  600,   50 }),
    "dwarf"    : ({  170,  600,   55 }),
    "behblock" : ({  150,  550,   60 }),
    "gstairs1" : ({  160,  750,   40 }),
    "terrace"  : ({  170,  800,   30 }),	 /* D: suddenst 170, 800, 0 */

    "spirals"  : ({    0,  300,   75 }),
    "swindow"  : ({   50,  300,  150 }),
    "window"   : ({  130,  300,  150 }),
    "onblock"  : ({  160,  300,   60 }),

    "deep/shaftbot" : ({    0,  400, -1100 }),
    "deep/deadend"  : ({   50,  400, -1100 }),
    "deep/sheast"   : ({    0,  300, -1100 }),
    "deep/darkpass" : ({ -100,	300, -1100 }),
    "deep/longnar1" : ({ -100,	200, -1100 }),
    "deep/longnar2" : ({ -200,	200, -1100 }),
    "deep/shgall2"  : ({ -180,	320, -1030 }),
    "deep/shgall1"  : ({ -120,	320, -1030 }),
    "deep/shnarrw"  : ({ -200,	300, -1140 }),
    "deep/boilwat"  : ({ -200,	290, -1150, HIDE }),
    "deep/plateau"  : ({ -200,	280, -1140, HIDE }),
   
    "deep/shroomsw" : ({ -200,	400, -1105 }),
    "deep/shroomse" : ({ -200,	500, -1105 }),
    "deep/shroomnw" : ({ -100,	400, -1100 }),
    "deep/shroomne" : ({ -100,	500, -1100 }),

    "deep/uruks"    : ({    0,  500, -1090, HIDE }),
    "deep/urukfore" : ({  100,  500, -1080, HIDE }),
    "deep/ringroom" : ({  130,  500, -1080, HIDE }),
    "deep/sholdpr"  : ({  140,  520, -1120, HIDE }),
    "deep/prison"   : ({  100,  540, -1080, HIDE }),
    "deep/prison2"  : ({   50,  540, -1120, HIDE }),
    "deep/shnarhol" : ({  -25,  540, -1110 }),
    "deep/shcrawl"  : ({ -100,	535, -1100 })
]);
#else

static mapping room_pos = ([]);

create_object() { 
    set_name("orb");
    call_out("restore_data", 0); 
}

remove_object() { 
    TO->save_data();
    ::remove_object();
}
#endif

//
// Now comes the interface for the rooms positions and types.
//
#define POS_NS 0
#define POS_EW 1
#define POS_UD 2
#define POS_HIDDEN 3

#define MAP_DATA (MORIA_DIR + "map/map.data")

void
save_data()
{
    FIXEUID;
    save_map(room_pos, MAP_DATA);
    find_player("rogon")->catch_msg("happen.c: Saved data in " + MAP_DATA + ".o\n");
}

void
restore_data()
{
    FIXEUID;
    room_pos = restore_map(MAP_DATA);
    find_player("rogon")->catch_msg("happen.c: Restored data in " + MAP_DATA + ".o\n");
}

void
add_data(mixed where, ...)
{
    mixed *value;

    if (objectp(where)) 
	where = MASTER_OB(where);

    else if (strlen(where)) 
	where = FPATH(MINES_DIR, where);
    
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
    
    write(sprintf("Trying: room_pos[%s] = %O\n", where, value));
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

    if (sscanf(room, MINES_DIR + "%s", pure) != 1)
	return ({ -1, -1, -1});

    if (sscanf(file_name(room), MINES_DIR + "shaftcor#%s", dummy) == 1)
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
dist(object room1, object room2)
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
direction_plane(object from, object to)
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
direction_string(object from, object to)
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
	default        : return 0;
    }
}

#define MAX_INT 2147483647
#define MIN_INT -2147483648

int
rize(object from, object to)
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
inside_moria(object who)
{
    string dummy;
    return who && ENV(who) && sscanf(file_name(ENV(who)), MINES_DIR+"%s", dummy)==1;
}

int
not_ok_room(object r)
{
    string where = file_name(r);
    string room, dummy;

    if (sscanf(where, MINES_DIR+"%s#%s", room, dummy)!=2)
	if (sscanf(where, MINES_DIR+"%s", room)!=1)
	    return 0;
    return member_array("where", r_not_ok)==-1 && query_where(r)!=R_SHAFT;
}

int runno;

void
run_loop()
{
    object *p=users();
    int i;

    if (find_call_out("run_loop") != -1)
	return;

    p = filter(p, "inside_moria", TO);

    if (!sizeof(p)) {
	call_out("run_loop", 60);
	return;
    }

    if (runno == 4)
    {
	call_out("try_make_orc", 1);
    }

    i = random(sizeof(p));

    if (runno%100 == 60)
	TO->meet_elves(p[i]);
    else if (runno%40 == 14)
	TO->meet_dwarves(p[i]);
    else if (runno%20 == 4)
	call_out("try_make_orc",1);
    else if (runno%30 == 5)
	p->catch_msg("A drumming can be heard from a distance.\n" +
		     "        Doom - doom - doom.\n" +
		     "The drumming echoes from deep inside the mountain.\n");
    runno++;
    call_out("run_loop", 10);
}

void
set_runno(int i) { runno = i; }

int
start_loop()
{
    if (find_call_out("run_loop") > -1)
	return 0;

    runno = 1;
    run_loop();
}

void
meet_elves(object who)
{
    object hat, crown;

    set_this_player(who);

    if (not_ok_room(ETP))
	return;

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
	TP->catch_msg("Glorfindel asks you: Are you the Ring-bearer?\n");
	tell_room(ETP, "Glorfindel asks "+QCTNAME(TP)+" a question.\n", TP);
	TP->catch_msg("Answer [yes/no] : ");
	input_to("answer_elves", 0);
	return;
    }
    tell_room(ETP,
	"\nAn elf shouts in terror: A troll!!!\n"+
	"All elves and music disappears..\n");
}

void answer_elves(string ans)
{
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
	    "    tales say that there is a greater power in the Rings of Power, and if\n"+
	    "    you also have the revenging power of the ancient dwarves,\n"+
	    "    you might defeat him.\n"+
	    "\n");
	TP->catch_msg(
	    "Glorfindel whispers to you:\n"+
	    "    From us you get this valueable mithril coat-mail.\n"+
	    "    It might help against trolls and other dangers!\n\n"+
	    "Glorfindel gives you a shining mail.\n"
	);
	tell_room(ETP,
	    "Glorfindel whispers something to "+QTNAME(TP)+".\n"+
	    "Glorfindel hands over a mail to "+HIM_HER(TP)+".\n", TP);
	/* Give TP a mail */
	tell_room(ETP,
	    "Glorfindel bows deeply and bids you farwell.\n"+
	    "Glorfindel and the group of elves leaves.\n");
    }
    else if (ans=="no") {
	tell_room(ETP,
	    "The elf gets solemn:\n"+
	    "    We do not allow anyone but the Ring-bearer to share our knowledge.\n"+
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
    set_this_player(who);
    if (not_ok_room(ETP))
	return;
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
	call_out("dwarf_attack",0,TP);
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
    call_out("place_axe", 10*60, axe);
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
    (MINES_DIR+"orc_lair")->create_soldier();
}
