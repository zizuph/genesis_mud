
/*
 * Based on:
 * /std/shadow.c
 *
 * This is a shadow object curse 
 *  ... "/d/Krynn/turbidus_ocean/obj/tavernkeeper_shipurse"
 * which allows for onboard mishaps
 * (std_boat_in.c)...
 * on ships as a result of a cursed player boarding
 *  ... "/d/Krynn/turbidus_ocean/obj/tavernkeeper_sailorcurse"
 *
 * Vitwitch 2021
 */

#pragma save_binary
#pragma strict_types

#include "/sys/macros.h"
#include <math.h>
#include <time.h>
#include <gmcp.h>
#include <filter_funs.h>
#include "/d/Krynn/std/boats/std_boat_defs.h"

// where objects from sunken ships are catalogued:
#define TAVOBJDIR "/d/Krynn/turbidus_ocean/obj/"
#define TREASUREMAP "tavern_treasuremap"
#define MAXNUMTREASURES 100

static object	shadow_ship;	/* ship (inner) object which are we shadowing */
static object   shadow_ship_outer;  /* ship (outer) for the shadowed obj */
static object   shadow_ship_locn;  /* sea room location for ship outer */
static object   shadow_ship_lastlocn; /* prior sea room location for ship outer */
static object   *cursed_sailor; /* occupants of the ship related to this shadow */

static int      gCurseSize;
static int      gSizeCrew;
static int      gCompletingMove = 0;

// where items from sunken ships are catalogued
mapping sunken_treasure_map;

/* prototypes */
static int shadow_double(string fname, object ob);
public void remove_object();
public void remove_shadow();
public varargs int shadow_me(mixed to_shadow);
public object query_shadow_who();
public object query_shadow_ship();
int is_ship_curse_shadow();
int is_a_shadow_cursed_ship();
public void remove_ship_curse_shadow();
int curse_incr( object plyr );
int update_complement();
void lift_ships_curse();
void complete_movement(object tp, string direc, string to_path);
int curse_modifier(object tp);
void announce_it( object player, string str0, string str1 );
void carry_out_row(string direc, string to_path);
void enter_inv(object ob, object from);
void get_treasuremap();
void put_treasuremap();
int update_treasuremap();
void sink_ship();


/*
 * Function name: shadow_double
 * Description  : Checks whether a certain shadow(file) is already
 *                shadowing a certain object.
 * Arguments    : string fname - the filename of the shadow to check.
 *                object ob    - the object to check whether it is already
 *                               shadowed by fname.
 * Returns      : int 1/0 - true if the ob is already shadowed by fname.
 */
static int
shadow_double(string fname, object ob)
{
    while (objectp(ob = shadow(ob, 0)))
    {
	if (fname == MASTER_OB(ob))
	{
	    return 1;
	}
    }

    return 0;
}    

/*
 * Function   : remove_object
 * Description: Ensure that we remove the shadow object too
 */
public void 
remove_object() 
{ 
    if (objectp(shadow_ship))
    {
        shadow_ship->remove_object();
    }
    destruct();
}

public void 
remove_shadow()
{
    destruct();
}

public varargs int
shadow_me(mixed to_shadow)
{
    int valid_shadowing;

    if (stringp(to_shadow))
    {
	to_shadow = find_object(to_shadow);
    }
    
    if ((!objectp(shadow_ship)) &&
	(!shadow_double(MASTER, to_shadow)))
    {
	if (shadow(to_shadow, 1))
	{
	    shadow_ship = to_shadow;

            cursed_sailor = ({});
            cursed_sailor = cursed_sailor 
                  + ({previous_object()->query_shadow_who()});

            shadow_ship_outer = shadow_ship->query_boat_out(); 

            valid_shadowing = objectp(cursed_sailor[0]) && 
               objectp(shadow_ship) && objectp(shadow_ship_outer);

            if ( valid_shadowing ) 
            {
                update_complement();
                return 1;
            }
	}
    }
    return 0;
}


public object
query_shadow_who()
{
    return shadow_ship;
}

public object
query_shadow_ship()
{
    return shadow_ship;
}

int
is_ship_curse_shadow()
{
    return 1;
}

int
is_a_shadow_cursed_ship()
{
    return 1;
}

public void 
remove_ship_curse_shadow()
{
    this_object()->remove_shadow();
}

int
curse_incr( object plyr )
{
    int incr = ftoi(log(itof(plyr->query_exp())/100000.0) / log(10.0));
    return max(1,incr);
}

int
update_complement()
{
    object *inv;
    object *players;
    int    nplyr;

    gCurseSize = 0;
    cursed_sailor = ({});

    inv = all_inventory(shadow_ship);
    players = FILTER_PLAYERS(inv);
    nplyr = sizeof( players );

    gSizeCrew = 
       shadow_ship->query_size() - 1 
     + sizeof( filter(inv,living) ) - nplyr;

    foreach(object player: players)
    {
        if ( player->is_a_shadow_cursed_sailor() )
            if ( member_array(player,cursed_sailor) == -1 )
            {
                cursed_sailor = cursed_sailor + ({player});
                gCurseSize += curse_incr( player );
            }
    }
    return nplyr;
}


void
lift_ships_curse()
{
    string str = "There is a lull in the wind; yet the timbers and rigging "+
      "of the vessel sing in relief. All aboard feel warm in the absence of "+
      "the cold salt wind.\n"; 
    tell_room(shadow_ship,str);
    this_object()->remove_shadow();
}


void
complete_movement(object tp, string direc, string to_path)
{
    object *players;

    tell_room(shadow_ship, QCTNAME(tp) + " sails " +
        LANG_THESHORT(shadow_ship_outer) + " " + direc + ".\n", tp);

    tp->catch_msg("You sail " + LANG_THESHORT(shadow_ship_outer) 
          + " " + direc + ".\n");

    shadow_ship_outer->set_direc(direc);
    shadow_ship_outer->move(to_path);

    shadow_ship->set_boat_loc(find_object(to_path));

    shadow_ship->remove_exit("out");
    shadow_ship->add_exit(to_path, "out");

    tell_room(shadow_ship, shadow_ship->view_long());

    /* Advise the GMCP of the new room. */
    players = FILTER_PLAYERS(all_inventory(shadow_ship));
    foreach(object player: players)
    {
        if (player->query_gmcp(GMCP_ROOM))
        {
            shadow_ship->gmcp_room_info(player);
        }
    }

    gCompletingMove = 0;
}


int
curse_modifier(object tp)
{
/* from /d/Krynn/std/boats/std_boat_defs.h :
    SHIP SAILING DIFFICULTY-----------------
    #define DIFFICULTY_NONE          0
    #define DIFFICULTY_NOVICE        9
    #define DIFFICULTY_LAYMAN        29
    #define DIFFICULTY_JOURNEYMAN    49
    #define DIFFICULTY_PROFESSIONAL  69
    #define DIFFICULTY_MASTER        89
    #define DIFFICULTY_GURU          99
    LOCATION SAILING DIFFICULTY-------------
    #define CONDITIONS_NORMAL             0
    #define CONDITIONS_TRICKY             30
    #define CONDITIONS_CHALLENGING        51
    #define CONDITIONS_EXT_CHALLENGING    76
    #define CONDITIONS_NEAR_IMPOSSIBLE    91
    SHIP SIZE-------------------------------
    #define SLOOP         1
    #define CUTTER        2
    #define SCHOONER      3
    #define CORVETTE      4
    #define FRIGATE       6
    #define MAN_OF_WAR    8
*/
    int ival = tp->query_skill(SAILING_SKILL) 
       + 5 * ( min(shadow_ship->query_size(),
            shadow_ship->query_num_passengers()) - 1 )
       - shadow_ship->query_sailing_difficulty()
       - shadow_ship_locn->query_sailing_difficulty();

    // range = [0,5]
    return ftoi( itof( min(0,ival) ) * -0.025 ); 
}


void
announce_it( object player, string str0, string str1 )
{
    string str;
    if ( gSizeCrew == 0 )
        str = "\nThis vessel creaks as though in pain "+
              "at the tread of those aboard.\n\n";
    else
        str = "\nThis vessel creaks as though in pain. "+
              "The crew grumbles, discontented.\n\n";
    tell_room(shadow_ship,str);
    player->catch_msg(str0);
    tell_room(shadow_ship,str1,player);
    return;
}


void
carry_out_row(string direc, string to_path)
{
    int effect; 
    float feff;
    string str0, str1; 
    object tp = shadow_ship->query_owner();

    if (!tp)
      tp = this_player();

    if (!stringp(to_path)) return;

    if ( gCompletingMove ) return;

    shadow_ship_lastlocn = shadow_ship_locn; 
    shadow_ship_locn = environment(shadow_ship_outer); 
    if ( !objectp(shadow_ship_locn) ) return;

    update_complement();

    if ( gCurseSize == 0 ) 
    {
        complete_movement(tp,direc,to_path);
        set_alarm(2.0,0.0,&lift_ships_curse());
    }
    else
    {
        // effects are move slowly, cannot move, sink

        effect = gCurseSize + curse_modifier(tp) + random(10);

        switch( effect )
        {
            case 0..2:
                str0 = "You feel a cold salt wind swirl about.\n\n";
                str1 = "A cold salt wind swirls about.\n\n";
                announce_it(tp,str0,str1);
                complete_movement(tp,direc,to_path);
                break;
            case 3..9:
                str0 = "You feel a cold salt wind box the compass, "+
                       "you struggle to hold the vessel on course.\n\n";
                str1 = "A cold salt wind boxes the compass. The vessel "+
                       "struggles to hold course.\n\n";
                announce_it(tp,str0,str1);
                gCompletingMove = 1;
                feff = itof(effect);
//VW 
                set_alarm(feff,0.0,&complete_movement(tp,direc,to_path));
                break;
            case 10..11:
                str0 = "You feel a cold salt wind batter the vessel "+
                       "with violence from all sides. You cannot "+
                       "follow your intended course. Water forces "+
                       "its way between timbers below deck.\n\n";
                str1 = "A cold salt wind batters the vessel "+
                       "with violence from all sides. The vessel makes "+
                       "no way on its intended course. Water forces "+
                       "its way between timbers below deck.\n\n";
                announce_it(tp,str0,str1);
                break;
            default:
                // sink
                str1 = "A cold salt wind batters and tosses "+
                       "the vessel about. Ranks of whitehorses charge "+
                       "the hull, slamming it hard. Mountains of roiling "+
                       "water surround the vessel on all sides. "+
                       "Stinging spume blasts across the deck.\n\n"+
                       "Below deck, the vessel's "+
                       "timbers finally separate with a groan and the vengeful "+
                       "sea pours in to claim another victim!\n\n";
                str0 = str1;

                set_alarm(4.5,0.0,&announce_it(tp,str0,str1));
                update_treasuremap();
                set_alarm(5.0,0.0,&sink_ship(tp));
                break;
        }
    }
}



void
enter_inv(object ob, object from)
{
    string str0, str1;

    shadow_ship->enter_inv(ob, from);

    if ( !interactive(ob) ) return;

    update_complement();

    if ( ob->is_a_shadow_cursed_sailor() ) return;

    str0 = "A cold salt wind blows over "+
          "your soul. You shiver in dread, "+
          "feeling that this vessel has been cursed.";
    str1 = "A cold salt wind blows.\n";

    if ( gCurseSize == 0 ) 
        str0 = sprintf("%s %s\n",str0,"Perhaps the curse seems to be fading, "+
                 "like untended paint on ships woodwork.\n");
    else
        str0 = sprintf("%s %s\n",str0,"The curse throbs malign in the very "+
                 "timbers and rigging of the vessel, offended by those who "+
                 "would set sail.\n");
    announce_it(ob,str0,str1);

    return;
}


void
get_treasuremap()
{
   setuid();
   seteuid(getuid());
   sunken_treasure_map = restore_map( TAVOBJDIR + TREASUREMAP );
   return;
}

void
put_treasuremap()
{
   int n, i;
   mixed ind, idx;

   ind = m_indices(sunken_treasure_map);
   n = sizeof(ind) - MAXNUMTREASURES;
   if ( n > 0 )
   {
       idx = sort_array(ind);
       for ( i=0;i<n;i++ )
           sunken_treasure_map = m_delete(sunken_treasure_map,idx[i]); 
   }

   setuid();
   seteuid(getuid());
   save_map( sunken_treasure_map, TAVOBJDIR + TREASUREMAP );
   return;
}

int
update_treasuremap()
{
    string mapname, iname, foo, indstr;
    int count;
    object *inv;

    count = 0;

    inv = filter(deep_inventory(shadow_ship),&->check_weapon());
    if ( !sizeof(inv) ) return count;

    get_treasuremap();

    foreach(object item: inv)
    {
        iname = file_name(item);
        if ( !iname ) continue;

        if ( !wildmatch("*#*",iname) )
            mapname = iname;
        else
            sscanf(iname,"%s#%s",mapname,foo);

        indstr = val2str(time()*10+count);
        sunken_treasure_map[indstr] = mapname;

        count++;
    }

    put_treasuremap();

    return count;
}


void
sink_ship()
{
    shadow_ship_outer->remove_object();
    remove_shadow();
}

