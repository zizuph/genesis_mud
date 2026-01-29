// file name:  /d/Avenir/common/outpost/obj/lsource.c
// creator(s): 	Kazz   May 1995
// updates:	June 1995	added set_volume() & adjectives
// purpose: 	To provide light for newbies and others.
// note:	When enough are in same inventory, they light the environment.
//		They 'crumble' if they are too far from the main Vein.
//		('stat crystal' provides more wizard info)
// using:	If you clone this, and want to assign a certain volume,
//		first call set_volume( int vol ) and then move the lsource
//		into the npc or room so that enter_env() is called.
// bug(s):	I can't get the WRITE_MISC_LOG to work though similar code
//		works in other outpost stuff.  Anybody know why?
//
// to-do:	* ? make this a 'magic' object?  Is the Source magic? (no)
//		* ? have the peddler sell pieces ?
//		* ? possessing pieces is illegal and guards will attack ?
//		* quest: find shards for someone.
//			 after completing quest, player can find them somewhere
//			 else, but only enough
//		* locations? :
//			* weak beetle is using one to attract many females.
//				(most beetle pieces are too small to use)
//		    	* Jadestone Doll has 3 for her light?

inherit "/std/object";
#include "/d/Avenir/common/outpost/outpost.h"

#undef DEBUG

#ifdef DEBUG
#define D(x) find_player("kazz")->catch_msg("lsource debug: " + (x))
#else
#define D(x)
#endif

#define LIGHT_LOG_FILE 			"/d/Avenir/log/lsource"

#define LIGHT_SOURCE_ID			"_avenir_Source_gives_light_"
#define VOLUME_FOR_LIGHT		15

// whether light_off() should tell_room() ... Depends on when called.
#define NOISY				1
#define QUIET				0

// number of seconds before crystals burst  600 seconds = 10 minutes.
#define DESTRUCT_TIME			600.0
// check closeness to Avenir Source vein every 300 seconds = 5 minutes
#define VEIN_CHECK_TIME			300.0

#define DIM_LONG     "This crystal has a dim glow emanating from it."
#define BRIGHT_LONG  "This crystal is glowing brightly, pulsing sporadically."
#define CRACK_TEXT   "Small fractures run through the crystal."
#define DIM_SHORT    		" crystal"
#define BRIGHT_SHORT 		" glowing crystal"
#define DIM_CRACKED_SHORT    	" cracked crystal"
#define BRIGHT_CRACKED_SHORT 	" glowing cracked crystal"

void   start_destruct_timer();
void   set_vein_check_timer();
void   check_near_vein();
// string rand_adj();

// whether it is already ticking toward 'crumbling'
// int destruct_timer_set = 0;

int lit, cracked;

init()
{
    ::init();
    // any commands?  probably not needed
    lit = 0;
    cracked = 0;
} // init()


create_object()
{
    set_name("crystal");
    add_name("piece");
    add_name("shard");
    add_name("source");
    add_name( LIGHT_SOURCE_ID );
    set_volume( random(5) + 1 );
    set_short( "@@crystal_short@@" );
    set_long( "@@crystal_long@@\n" );
    
    add_prop( OBJ_S_WIZINFO,
        "These pieces will glow when their volume reaches "+
	VOLUME_FOR_LIGHT +". A timer checks every "+
	"5 minutes "+	  	// VEIN_CHECK_TIME +
	"for whether the piece is no "+
        "longer near the main Source vein of Avenir.  If it is found to be "+
	"outside of Avenir then the timer will start, and after "+
	"10 minutes"+		// DESTRUCT_TIME
	", the crystal will crumble. Returning to Avenir will not stop the "+
	"timer as the crystals will have been weakened too much.\n" );

    // set a timer to periodically check if this is still close to Avenir.
    if (IS_CLONE)
	set_vein_check_timer();

} // create_object()


string
crystal_short()
{
    string short_str;
    
    if (lit) {
	if (cracked) 
    	    short_str = query_adj(0) + BRIGHT_CRACKED_SHORT;
	else
    	    short_str = query_adj(0) + BRIGHT_SHORT;
    } else {
	if (cracked)
    	    short_str = query_adj(0) + DIM_CRACKED_SHORT;
	else
    	    short_str = query_adj(0) + DIM_SHORT;
    }
    return short_str;
    
} // crystal_short()

string
crystal_long()
{
    string long_str;
    
    if (lit) {
    	long_str = BRIGHT_LONG;
    } else {
    	long_str = DIM_LONG;
    }
    
    if (cracked) {
        return long_str + " "+ CRACK_TEXT;
    } else {
    	return long_str;
    }
    
} // crystal_long()


// actually make this one glow enough to light the way.
void
light_on( int flag )
{
    D( "in light_on(), turning on a crystal.\n" );
    if (flag == NOISY) {
	tell_room( environment(this_object()),
		   "The crystals glow brightly.\n" );
    }
    add_prop( OBJ_I_LIGHT, 1 );
    environment(this_object())->update_light( 0 );

    lit = 1;

//    WRITE_MISC_LOG( LIGHT_LOG_FILE, "Created light with source pieces.\n" );
    
} // set_light()


// turn off the light in this piece.
void
light_off( int flag )
{
    if ((int)query_prop( OBJ_I_LIGHT ) == 1) {
	D( "in light_off(), turning off a glowing crystal.\n" );
	if (flag == NOISY) {
	    tell_room( environment(this_object()),
		   "The light from the crystals fades away.\n" );
	}
	remove_prop( OBJ_I_LIGHT );
	environment( this_object())->update_light( 0 );

//	WRITE_MISC_LOG( LIGHT_LOG_FILE, "- Source light turned off.\n" );
    } 
    // change the Source's text to show it isn't glowing brightly enough.
    lit = 0;

} // light_off()


// to test whether other pieces of Source are in this inventory.
// if so, calculate the light they provide.
void
enter_env( object to, object from )
{
    object *items;
    int    i;
    int	   volume = 0;

    // let it enter the inventory.
    ::enter_env( to, from );

    // special code so 'cc lsource' works
    if (to == 0)  return;

    items = all_inventory( to );
    // check whether there are other Source pieces in the same inventory.
    for (i = 0; i < sizeof(items); i++ ) {
        if (items[i]->id(LIGHT_SOURCE_ID)) {
            volume += (int)items[i]->query_prop( OBJ_I_VOLUME );
        }
    } // for

    D( "enter_env(): volume = "+volume+"\n" );
    if (volume < VOLUME_FOR_LIGHT) {
	return;
    }

    // run through and change the other pieces to show glowing in text.
    for (i = 0; i < sizeof(items); i++ ) {
        if (items[i]->id(LIGHT_SOURCE_ID)) {
	    // set only the 'last' one to glow so total light only == 1
	    items[i]->light_off( QUIET );
            // but change each piece's description to 'look' like it glows.
    	    items[i]->set_lit();		// see: crystal_short()
        }
    } // for

    // make this item the only one really giving light (only 1 in group).
    light_on( NOISY );

} // enter_env()



// when Source piece leaves an environment, see if the remaining pieces
//   are too few to provide light.
// note: This would have been nicer code if there was a function like
//   present() that returned an array of objects.  It would prevent
//   having to run the 'for loop' twice.
void
leave_env( object from, object to )
{
    object *items;
    int    i;
    int    volume = 0;
    int	   first = 0;
    object a_second_crystal = 0;
    
    // special code so 'cc lsource' works
    if (from == 0)  return;

    items = all_inventory( from );
    // check whether there are other Source pieces in the same inventory.
    for (i = 0; i < sizeof(items); i++ ) {
	if (items[i]->id(LIGHT_SOURCE_ID)) {
	    // skip the volume of object being dropped.
	    if (items[i] != TO) {
                a_second_crystal = items[i];
		volume += (int)items[i]->query_prop( OBJ_I_VOLUME );
	    }
	}
    } // for
    
    D( "leave_env(): remaining volume = "+ volume +"\n" );

    // if enough other pieces, just need to make sure one still glows
    if (volume >= VOLUME_FOR_LIGHT) {
        // if this object being dropped was lit, make sure to light another
        //    piece in the inventory.
	if ((int)query_prop( OBJ_I_LIGHT ) && a_second_crystal) {
	    D("leave_env(): turning on a secondary crystal\n" );	    
            a_second_crystal->light_on( QUIET );
	    light_off( QUIET );
        } else
	    light_off( NOISY );
	::leave_env( from, to );
	return;
    }

    // Not enough volume to provide light anymore.
    // run through and decrease the light for the remaining pieces.
    for (i = 0; i < sizeof(items); i++ ) {
        if (items[i]->id(LIGHT_SOURCE_ID)) {
	    items[i]->light_off( NOISY );
        }
    } // for
    
    // move it out of the inventory.
    ::leave_env( from, to );

} // leave_env()



void
start_destruct_timer()
{
    set_alarm( DESTRUCT_TIME, 0.0, "self_destruct" );
//    destruct_timer_set = 1;
    
} // start_destruct_timer()



// these little pieces of a Source vein can crumble.
void
self_destruct()
{
    object *envs;
    object current_room;

    envs = all_environment(this_object());
    current_room = envs[sizeof(envs) - 1];

    tell_room( current_room, "The crystal crumbles to dust.\n" );
    light_off( NOISY );
    remove_object();

} // self_destruct()


void
set_vein_check_timer()
{
    set_alarm( VEIN_CHECK_TIME, 0.0, "check_near_vein" );
} // set_vein_check_timer


// if the piece is not near the Avenir Source vein, the crystal will
// be damaged and eventually destruct.
void
check_near_vein()
{
    string room_filename;
    object *envs;
    object current_room;

    // Courtesy of Mercade:
    // get the filename of the current room
    //   (whether we are in a player inventory, or on a room's floor)
    envs = all_environment(this_object());
    current_room = envs[sizeof(envs) - 1];
    room_filename = file_name( current_room );

//    D( "check_near_vein(): room_filename = "+ room_filename+ "\n" );
    
    // check if we are 'close enough' to the Avenir main vein.
    // (ie. in either directory path)
    if (wildmatch("/d/Avenir/*", room_filename)) {
	// still in range of vein, no problem.
	set_vein_check_timer();
	return;
    }
	
    // piece is too far from main vein, crack it and set destruct timer
    tell_room( current_room,
	       "You hear a faint cracking noise.\n" );
    cracked = 1;
    add_adj( "cracked" );
    
    start_destruct_timer();
    
} // check_near_vein()


void
set_lit()
{
    lit = 1;
} // set_lit()



// called by the cloning room if a specific volume is desired.
void
set_volume( int vol )
{
    // change the randomly chosen volume to this specific one.
    add_prop( OBJ_I_VOLUME, vol );

    // set an adjective appropriate to the size
    if (vol < 3)
    	set_adj( "tiny" );
    else if (vol < 6)
    	set_adj( "small" );
    else if (vol < 10)
    	set_adj( "medium-sized" );
    else if (vol < 15)
    	set_adj( "large" );
    else 
    	set_adj( "huge" );
} // set_volume()
