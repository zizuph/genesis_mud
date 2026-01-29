/*
 *    /d/Gondor/common/guild2/npc/steed.c
 *
 * The steed of the nazgul.
 * 
 * In principle it works like a teleport spell from all outside rooms
 * not protected against magic or teleportation to predefined rooms.
 *
 *    Copyright (c) 1995, 1996, 1997 by Christian Markus
 *
 *    Olorin, 1995 
 *
 * Modification log:
 * 13-aug-1997, Olorin: Neraka location in Krynn removed
 *                      Added Vingaard Mountains location.
 * 5-dec-1999, Gorboth: Reduced task difficulty levels by 1/3 to
 *                      adress the failures that have resulted from
 *                      the change to resolve_task
 * 8-mar-1999, Gnadnar: remove Emerald dest until it reopens,
 *
 * Nov 13, 2000, Igneous: Minor changes done for the new spells.
 *            remove all references to Roke 
 * 04.06.2002, Chmee: Some general updates and code moderniations.
 * 1-sep-2004, Mercade: removed masking of query_nonmet_name().
 * September 2004, Eowul: Allowed steeds to circle locations
 * August 2007, Gorboth: Added destination Chaos Gate at the Army of Darkness
 * Oktober 2008, Eowul: Added a call to the destination room upon landing and
 *                      take off.
 * 05-Jun-2010, ?? : Previous update
 * 12-Feb-2011, Lavellan: Added obsolete /std/living function "fights" to fix
 *                        errors in /lplog and allow rider to see fights in
 * 
 */
/*
 * Distances:
 *            Gon Shi Rho Kry Ans Gen Rok Cir Kal Ter Ave Cal Eme
 * Gondor      *   N   N   S   F   S   S   F   S   F   F   S   F    3
 * Shire       N   *   N   S   F   S   S   F   S   F   F   S   F    2
 * Rhovanion   N   N   *   F   F   F   F   F   F   F   F   F   S    1
 * Krynn       S   S   F   *   N   S   S   F   F   S   F   S   S    2
 * Ansalon     F   F   F   N   *   F   F   F   F   F   F   F   F    1
 * Sparkle     S   S   F   S   F   *   S   F   F   S   F   N   S    1
 * Cirath      F   F   F   F   F   F   N   *   F   F   F   F   F    -
 * Kalad       S   S   F   F   F   F   S   F   *   S   F   F   F    2
 * Terel       F   F   F   S   F   S   F   F   S   *   N   F   F    2
 * Avenir      F   F   F   F   F   F   F   F   F   N   *   F   F    1
 * Calia       S   S   F   S   F   S   F   F   F   F   F   *   F    1
 * Emerald     F   F   S   S   F   S   F   F   F   F   F   F   *    0/?
 *
 * Faerie > Krynn
 * Hobbiton > Shire
 * Dwarfheim > ?
 * Goblin Caves > Sparkle
 * Gnome starting area?
 * Kalad: 
 */
#pragma save_binary
#pragma strict_types

inherit "/std/creature";
inherit "/std/combat/unarmed";
inherit "/d/Gondor/common/lib/time.c";

#include <cmdparse.h>
#include <composite.h>
#include <filter_funs.h>
#include <living_desc.h>
#include <macros.h>
#include <ss_types.h>
#include <options.h>
#include <stdproperties.h>
#include <tasks.h>
#include <wa_types.h>

#include "/d/Gondor/defs.h"
#include "/d/Gondor/common/guild2/lib/morgul_defs.h"
#include "../spells.h"

// header files from other domains for name and filename of
// destinations there: 
#include "/d/Avenir/include/steed.h"
#ifndef AVENIR_PORT_NAME
#define AVENIR_PORT_NAME    "Avenir"
#endif
#ifndef AVENIR_PORT_PATH
#define AVENIR_PORT_PATH    "/d/Avenir/dummy"
#endif
// /d/Avenir/common/port/port3
// #include "/d/Emerald/open/nazgul_steed.h"
#ifndef EMERALD_NAME
#define EMERALD_NAME    "blackwall mountains"
#endif
#ifndef EMERALD_PATH
#define EMERALD_PATH    "/d/Emerald/common/guild/aod/rooms/chaos_area"
#endif

#define HE(x)   (x)->query_pronoun()
#define HIS(x)  (x)->query_possessive()

// Skill-level required to be able to mount
#define MOUNT_LVL    20

// Skill-level required to be able to direct
#define DIRECT_LVL    40

// Define our own fighting means
#define ATT_BEAK  0
#define ATT_CLAWS 1

// Define where we can be hit
#define HIT_HEAD  0
#define HIT_BODY  1
#define HIT_LWING 2
#define HIT_RWING 3
#define HIT_LCLAW 4
#define HIT_RCLAW 5

#define MAX_DIST     60
#define MIN_DIST     30
#define SHIP_DIST    60
#define NEAR_DIST    45

// Prototypes
public  int     do_mount( string str );
public  int     do_time( string str );
public  int		do_shriek( string str );
nomask  int     do_dismount( string str );
        int     do_command( string dir );
        int     do_dismiss( string str );
        int     query_flight_time( string from_file, string to_file );
        int     query_flight_time_to_domain( string from_file, string to_domain );
        int     query_domain_dist( string dom1, string dom2 );
varargs int     throw_off( object rider );
public  string  long_desc();
static  string  pinion_desc();
static  string  view_desc();
        void    land();
        void    circle();
        void    land_announce( int i );
        void    random_message();
static  mixed   fights(object me, object enemy);

// Global variables
int gRemoving = 0, gFlying = 0, land_alarm = 0, anno_alarm = 0, gCircling = 0, gStartedCircling = 0;
string  gWhere = 0, gCirclingWhere = 0, gOwner = 0, *random_messages = ({}), *random_circle_messages = ({});
object *spotted_players = ({});

// Allow the nine to circle their steeds over certain locations
mapping CircleLocations =
([
    "southern ithilien" :
    ({
        // Starting domain
        "Gondor",
        // Paths that are included in the circling
        ({ 
            "/d/Gondor/ithilien/sforest",
            "/d/Gondor/ithilien/emyn-arnen",
            "/d/Gondor/ithilien/forest",
            "/d/Gondor/ithilien/poros"
        }),
    }),

    "northern ithilien" :
    ({
        "Gondor",
        ({ 
            "/d/Gondor/ithilien/dagorlad",
            "/d/Gondor/ithilien/nforest",
            "/d/Gondor/ithilien/camp"
        }),
    }),

    "harondor" :
    ({
        "Gondor",
        ({ 
            "/d/Gondor/harondor/room/bridge01",
            "/d/Gondor/harondor/room/camp/room/trail07",
            "/d/Gondor/harondor/room/camp/room/campchief",
            "/d/Gondor/harondor/room/camp/room/s05",
            "/d/Gondor/harondor/room/road11s"
        }),
    }),
]);

/*
 * Mapping with destinations.
 * Removed until reopening:
 * EMERALD_NAME    : EMERALD_PATH,
 */
mapping Dest =
([
    "minas morgul"   : (MORGUL_DIR + "city/square"),
    "black tower"    : "/d/Gondor/guilds/morgulmage/rooms/tower_7c",
    "morannon"       : (ITH_DIR + "road/nr12"),
    "lebennin"       : "/d/Gondor/lebennin/road/fieldr7",
    "isengard"       : "/d/Gondor/dunland/ford/eyot",
    "evendim"        : "/d/Shire/evendim/ev3",
    "trollshaws"     : "/d/Shire/common/trollsh/riv6no",
    "vingaard mountains" : "/d/Krynn/solamn/vin_mount/room/road12",
    "icewall"        : "/d/Krynn/icewall/forest/forest_11",
    "pax tharkas"    : "/d/Krynn/pax/valley/forest6",
    "flotsam"        : "/d/Ansalon/balifor/flotsam_forest/coastline/road9",
    "neraka"         : "/d/Ansalon/taman_busuk/neraka/outer/main/r6",
    "sanction"       : "/d/Ansalon/taman_busuk/sanction/room/city/slum5",
    "eastwilde"      : "/d/Ansalon/estwilde/plains/3a",
    "sparkle"        : "/d/Genesis/start/human/wild2/peninsula",
    "hespyre mountains" : "/d/Kalad/common/wild/pass/w21",
    "raumdor"        : "/d/Raumdor/common/wforest/wf17",
    "underdark"      : "/d/Terel/mountains/ridge",
    "graveyard"      : "/d/Terel/common/town/mansion/graveyard/grv3",
    AVENIR_PORT_NAME : AVENIR_PORT_PATH,
    "argos"          : "/d/Calia/argos/swterr/rooms/for10",
    EMERALD_NAME     : EMERALD_PATH,
    "desert"         : "/d/Cirath/ridge/desert/d24",
    "gont"           : "/d/Earthsea/gont/tenalders/high_fall/ne6",
    "mithas"         : "/d/Ansalon/goodlund/nethosak/forest/room/forest23",
    "palanthas"      : "/d/Krynn/solamn/moor/room/moor3",
    "cadu"           : "/d/Khalakhor/inisi/roke/wild/q5"
]);

mapping gDist =
([
    "Gondor": 
    ({
        "Shire",     NEAR_DIST, 
        "Rhovanion", NEAR_DIST, 
        "Krynn",     SHIP_DIST, 
        "Ansalon",   MAX_DIST,
        "Genesis",   SHIP_DIST, 
        "Cirath",    MAX_DIST,
        "Kalad",     SHIP_DIST, 
        "Terel",     MAX_DIST,
        "Avenir",    MAX_DIST,
        "Calia",     SHIP_DIST, 
        "Emerald",   MAX_DIST, 
    }), 
    "Shire": 
    ({
        "Rhovanion", NEAR_DIST, 
        "Krynn",     SHIP_DIST, 
        "Ansalon",   MAX_DIST,
        "Genesis",   SHIP_DIST, 
        "Cirath",    MAX_DIST,
        "Kalad",     SHIP_DIST, 
        "Terel",     MAX_DIST, 
        "Avenir",    MAX_DIST,
        "Calia",     SHIP_DIST, 
        "Emerald",   MAX_DIST, 
    }), 
    "Rhovanion": 
    ({
        "Krynn",     MAX_DIST, 
        "Ansalon",   MAX_DIST,
        "Genesis",   MAX_DIST, 
        "Cirath",    MAX_DIST,
        "Kalad",     MAX_DIST, 
        "Terel",     MAX_DIST, 
        "Avenir",    MAX_DIST,
        "Calia",     MAX_DIST, 
        "Emerald",   SHIP_DIST, 
    }), 
    "Krynn": 
    ({
        "Ansalon",   NEAR_DIST,
        "Genesis",   SHIP_DIST, 
        "Cirath",    MAX_DIST,
        "Kalad",     MAX_DIST, 
        "Terel",     SHIP_DIST, 
        "Avenir",    MAX_DIST,
        "Calia",     SHIP_DIST, 
        "Emerald",   SHIP_DIST, 
    }), 
    "Ansalon": 
    ({
        "Genesis",   MAX_DIST, 
        "Cirath",    MAX_DIST,
        "Kalad",     MAX_DIST, 
        "Terel",     MAX_DIST, 
        "Avenir",    MAX_DIST,
        "Calia",     MAX_DIST, 
        "Emerald",   MAX_DIST, 
    }), 
    "Genesis": 
    ({
        "Cirath",    MAX_DIST,
        "Kalad",     MAX_DIST, 
        "Terel",     SHIP_DIST, 
        "Avenir",    MAX_DIST,
        "Calia",     SHIP_DIST, 
        "Emerald",   SHIP_DIST, 
    }), 
    "Cirath": 
    ({
        "Kalad",     MAX_DIST, 
        "Terel",     MAX_DIST, 
        "Avenir",    MAX_DIST,
        "Calia",     MAX_DIST, 
        "Emerald",   MAX_DIST, 
    }), 
    "Kalad": 
    ({
        "Terel",     SHIP_DIST, 
        "Avenir",    MAX_DIST,
        "Calia",     MAX_DIST, 
        "Emerald",   MAX_DIST, 
    }), 
    "Terel": 
    ({
        "Avenir",    NEAR_DIST,
        "Calia",     MAX_DIST, 
        "Emerald",   MAX_DIST, 
    }), 
    "Avenir": 
    ({
        "Calia",     MAX_DIST, 
        "Emerald",   MAX_DIST, 
    }), 
    "Calia":
    ({
        "Emerald",   MAX_DIST, 
    }), 
]);

public void create_creature()
{
 int ind;
 string *places;

    set_name( "steed" );
    add_name( ({ "creature", "bird", "beast", "wyrm" }) );
    set_adj( ({ "fell", "black", "winged", "dark", "monstrous", "naked",
        "huge" }) );

    set_race_name( "winged steed" );
    set_short( "huge winged beast" );
    set_long( long_desc );

    set_gender( 2 );

    add_item( ({ "wing", "wings", "pinions", "pinion", }), pinion_desc );
    add_item( ({ "creature", "beast", "bird", "winged creature", "steed",
        "winged steed", "fell beast", "wyrm" }), long_desc );

    add_item( ({ "view", "room" }), view_desc );

    // low stats
    set_stats( ({  80, 20, 20,  5,  5, 10, }) );

    set_skill( SS_UNARM_COMBAT, 10 );
    set_skill( SS_DEFENCE, 10 );

    set_whimpy( 80 );
    set_alignment( -700 );

    set_attack_unarmed( ATT_BEAK,  10, 10, W_IMPALE,           30, "beak" );
    set_attack_unarmed( ATT_CLAWS, 10, 10, W_IMPALE | W_SLASH, 70, "claws" );

    set_hitloc_unarmed( HIT_HEAD,  ({ 10, 10,  5, }), 12, "head" );
    set_hitloc_unarmed( HIT_BODY,  ({  5,  5,  5, }), 16, "body" );
    set_hitloc_unarmed( HIT_LWING, ({ 15,  5, 10, }), 24, "left pinion" );
    set_hitloc_unarmed( HIT_RWING, ({ 15,  5, 10, }), 24, "right pinion" );
    set_hitloc_unarmed( HIT_LCLAW, ({ 15,  5,  5, }), 12, "left claw" );
    set_hitloc_unarmed( HIT_RCLAW, ({ 15,  5,  5, }), 12, "right claw" );

    add_prop( CONT_I_VOLUME,      100* 1000 );
    add_prop( CONT_I_MAX_VOLUME, 1000* 1000 );
    add_prop( CONT_I_WEIGHT,       89* 1000 );
    add_prop( CONT_I_MAX_WEIGHT, 1000* 1000 );
    add_prop( CONT_I_LIGHT, 1 );
    add_prop( LIVE_I_NEVERKNOWN, 1 );

    setuid();
    seteuid( getuid() );
    // Check all values of the Dest mapping:
    ind = sizeof( places = m_indexes( Dest ) );
    while (ind--)
    {
        if (!strlen( places[ind] ) || 
            !strlen( Dest[places[ind]] ))
        {
            SPELL_INHERIT->log_spell( "yalarochrama", "Error in Dest: "+
                places[ind]+ " : "+ Dest[places[ind]]+ ".\n" );
            Dest = m_delete( Dest, places[ind] );
        }
        else
        {
            catch( Dest[places[ind]]->load_me());
            if (!objectp( find_object( Dest[places[ind]] ) ))
            {
                SPELL_INHERIT->log_spell( "yalarochrama", "Load error: "+
                    places[ind]+ " : "+ Dest[places[ind]]+  ".\n" );
                Dest = m_delete(Dest, places[ind]);
            }
        }
    }
}

public mapping query_dest()
{
    return Dest;
}

public void init_living()
{
    ::init_living();
    add_action( do_mount,    "mount" );
    add_action( do_dismount, "dismount" );
    add_action( do_command,  "command" );
    add_action( do_time,     "time" );
	add_action( do_shriek,	 "mwail" );
    add_action( do_shriek,	 "shriek" );
    add_action( do_dismiss,  "dismiss" );
}

public string long_desc()
{
 object tp = this_player(), ob;
 string  desc;

    if (environment( tp ) == this_object())
    {
        if (gFlying)
        {
            return "You are mounted on the monstrous winged creature, "+
                "sitting on the naked body between the featherless "+
                "leathery pinions and the long naked neck. The creature "+
                "is high in the air, flying at an incredible speed, and "+
                "an icy wind is blowing into your face.\n";
        }
        else
        {
            return "You are mounted on the monstrous winged creature, "+
                "sitting on the naked body between the featherless "+
                "leathery pinions and the long naked neck. The creature "+
                "is standing on the ground, so you can leave it by "+
                "dismounting.\n";
        }
    }
    desc = "A winged creature: if bird, then greater than all other "+
        "birds, and it is naked, bearing neither quill nor feather, and "+
        "its vast pinions are as webs of hide between horned fingers. A "+
        "creature of an older world maybe it is, whose kind, lingering "+
        "in forgotten mountains cold beneath the Moon, outstayed their "+
        "day, and in hideous eyrie bred this last untimely brood, apt to "+
        "evil."; 

    if (stringp( gOwner ))
    {
        ob = find_player( lower_case( gOwner ) );
        if (objectp( ob ) && (environment( ob ) == this_object()))
        {
            desc += " "+ ob->query_The_name( tp )+ " is mounted "+
                "on "+ query_objective()+ ".";
        }
        else if (tp->query_name() == gOwner)
        {
            desc += " It is waiting for you to mount it.";
        }
    }
    return desc+ "\n";
}

/*
 * Examine the steed directly if you want any extra info about it.
 * Right now this mask simply returns the local mask of long().
 * I found spending a lot of time  for coding not really important details
 * unreasonable.
 */
nomask public varargs string short( object for_obj )
{
    if (!objectp( for_obj ))
    {
        for_obj = this_player();
    }
    if (environment( for_obj ) == this_object())
    {
        return long( for_obj )[0..-3];
    }
    else
    {
        return ::short( for_obj );
    }
}

public string exits_description()
{
    return "The only obvious exit is to dismount your winged steed.\n";
}

/*
 * Function name:   long
 * Description:     Returns the long-description of this living, and shows
 *                  also the inventory. Handles invisibility and met/nonmet.
 *                  Note that the function does not do any writes! It only
 *                  returns the correct string.
 * Arguments:       string for_obj: return an item-description
 *                  object for_obj: return the living-description
 * Returns:         The description string
 */
nomask varargs string long( mixed for_obj )
{
 int brief, i, j, max;
 object tp = this_player(), env = environment( this_object() ), ob,
     *ob_list, *lv, *dd;
 string str, tmp, *a, where, item, it, *ctants;
    
    if (stringp( for_obj ))
    {
        return ::long( for_obj );
    }
    if (!objectp( for_obj ))
    {
        for_obj = tp;
    }
    if (environment( for_obj ) == this_object())
    {
        brief = tp->query_option( OPT_BRIEF );
        if (brief)
        {
            str = "You are astride your "+ query_race_name()+ ". ";
        }
        else
        {
            str = long_desc();
        }
        str += "From here you can see:\n";

        if (gFlying)
        {
            a = explode( gWhere, " " );
            j = sizeof( a );
            for (i=0; i<j;i++)
            {
                a[i] = capitalize( a[i] );
            }
            where = implode( a, " " );
            if(!gStartedCircling)
            {
                str += "Your winged steed is flying through the air high "+
                    "above the ground. All you can see are clouds below you "+
                    "while you are hurtling towards "+ where+ ".\n";
            }
            else
            {
                str += "Your winged steed is slowly circling " + where + ".\n";
            }

        }
        else
        {
            if (tp->query_wiz_level())
            {
                tmp = file_name( env );
                if (strlen( env->query_prop( OBJ_S_WIZINFO ) ))
                {
                    tmp = "Wizinfo "+ tmp;
                }
                str += tmp+ "\n";
            }

            if (!(env) && (env->query_prop( OBJ_I_LIGHT ) >
                -(tp->query_prop( LIVE_I_SEE_DARK ))))
            {
                str += LD_DARK_LONG;
            }
            else
            {
                ob = env;
                if (!ob->check_seen( tp ))
                    str += LD_CANT_SEE;
                else
                {
                    if (brief)
                    {
                        str += ob->short()+ ".\n";
                        if (!ob->query_noshow_obvious())
                        {
                            str += ob->exits_description();
                        }
                    }
                    else
                    {
                        str += ob->long();
                    }
                    ob_list = all_inventory( env );
                    lv = FILTER_OTHER_LIVE( ob_list );
                    if (sizeof( lv ))
                    {
                        lv -= ({ this_object() });
                    }
                    dd = FILTER_DEAD( ob_list );
                    dd = FILTER_SHOWN( dd );

                    item = COMPOSITE_FILE->desc_dead( dd, 1 );
                    if (item)
                    {
                        str += capitalize( item )+ ".\n";
                    }
                    item = COMPOSITE_FILE->desc_live( lv, 1 );
                    if (item)
                    {
                        str += capitalize( item )+ ".\n";
                    }
                    j = sizeof(lv);
                    for (max=0;max<j;max++)
                    {
                        ctants = map( lv[max]->query_enemy( -1 ), "fights",
                            this_object(), lv[max] );
                        if (sizeof( ctants ))
                        {
                            ctants -= ({ 0 });
                        }
                        if (sizeof( ctants ) == 1)
                        {
                            item = LD_FIGHT1( ctants[0] );
                        }
                        else if (sizeof( ctants ) > 1)
                        {
                            item = LD_FIGHT_MANY( ctants );
                        }
                        else
                        {
                            item = 0;
                        }
                        if (item)
                        {
                            str += LD_FIGHT_DESC( item, lv[max] );
                        }
                    }
                }
            }
        }
    }
    else
    {
        return ::long( for_obj );
    }
    return str;
}

/*
 * This is a mask of the /std/container.c function required to properly
 * observe the environment of this object while mounted. We don't want
 * the output trashed as we generate it anew in the local mask of long()
 */
public void show_visible_contents( object for_obj )
{
    if (environment( for_obj ) == this_object())
    {
        return;
    }
    else
    {
        ::show_visible_contents( for_obj );
    }
}

string pinion_desc()
{
    if (gFlying)
    {
        return "The vast pinions are as webs of hide between horned "+
            "fingers. Their span must be twenty feet or more.\n";
    }
    else
    {
        return "The vast pinions are as webs of hide between horned "+
            "fingers, and the mighty beast is beating them restlessly.\n";
    }
}

static string view_desc()
{
 int i, j;
 object tp = this_player();
 string desc, *a, where;

    if (environment( tp ) != this_object())
    {
        return "You find no view.\n";
    }
    if (gFlying)
    {
        a = explode( gWhere, " " );
        j<sizeof( a );
        for (i=0;i<j;i++)
        {
            a[i] = capitalize( a[i] );
        }
        where = implode( a, " " );

		if(!gStartedCircling)
		{
			desc = "Your winged steed is flying through the air high " +
				"above the ground. All you can see are clouds below you " +
				"while you are hurtling towards "+ where+ ".\n";
		}
		else
		{
			desc = "Your winged steed is slowly circling " + where + ".\n";
		}
    }
    else
    {
        desc = environment( this_object() )->long();
    }
    return desc;
}

string choose_random_dest()
{
    string  dest = gWhere;

    while ((dest == gWhere) ||
        (Dest[dest] == file_name( environment( this_object() ) ) ))
    {
        dest = one_of_list( m_indexes( Dest ) );
    }
    return dest;
}

int in_region(string filename, object player)
{
	object env;

	env = environment(player);
	if(!objectp(env)) return 0;
	return wildmatch(filename, file_name(env));
}

object *find_players_in_region(string region, int ignore_hidden = 0)
{
    object *all_users, *ignored_users, *remaining_users;
    int i;

    all_users = users();
    ignored_users = all_users;

	if(member_array(region, m_indexes(CircleLocations)) == -1)
		return ({});

    // Find all players in this region
    for(i=0;i<sizeof(CircleLocations[region][1]);i++)
    {
        // Keep all users that are not in this region
        ignored_users = filter(ignored_users, not @
            &in_region(CircleLocations[region][1][i] + "*"));
    }

    // All users that are not ignored are the ones in our region
    remaining_users = all_users - ignored_users;

    // Filter out all inside users
    remaining_users = filter(remaining_users,
        not @ &->query_prop(ROOM_I_INSIDE) @ environment);

    // See if we need to ignore hidden and invis users
    if(ignore_hidden)
    {
        // Filter invis users
        remaining_users = filter(remaining_users,
            not @ &->query_prop(OBJ_I_INVIS));

        // Filter hidden users
        remaining_users = filter(remaining_users,
            &operator(<=)(, 15) @ &->query_prop(OBJ_I_HIDE));
    }

// Temporary filter for users and jr's
// ignored_users = remaining_users;
// ignored_users = filter(ignored_users, not @ &->query_wiz_level());
// ignored_users = filter(ignored_users, not @ &wildmatch("*jr") @ &->query_real_name());
// remaining_users -= ignored_users;

    return remaining_users;
}

void take_off()
{
 int delay, i, j, dist;
 object room = environment( this_object() ), rider, *players;
 string  msg, *rooms, startDomain, startFilename;

    while (!room->query_prop( ROOM_I_IS ))
    {
        room = environment( room );
    }
    if (strlen( gOwner ))
    {
        rider = find_player( gOwner );
    }
    if (gFlying)
    {
        tell_room( this_object(), "Your winged steed wheels through "+
            "a large circle, finds the new course and shoots away like an "+
            "arrow towards the new destination.\n", ({ this_object() }) );
        remove_alarm( land_alarm );
        remove_alarm( anno_alarm );

        // Notify the region that the shape left again
        if(gStartedCircling)
        {
            players = find_players_in_region(gCirclingWhere);
            players->catch_tell("The fell beast races above, turns, and " +
				"then is gone, flying away with the speed of a wraith " +
				"of Mordor. Behind it the wind roars away, leaving the " +
				"sky bare and bleak.\n" );
        }
                                            /* Same formula as in query_flight_time   */
        delay = (30* MAX_DIST+ 5)/ 20 - (50+ MAX_DIST* random( rider->
            query_skill( SS_ANI_HANDL ) ))/ 100;
        if(!gCircling)
        {
            if(gStartedCircling)
            {
                // We have already arrived in a domain, use that to calculate distance
                delay = query_flight_time_to_domain( Dest[gWhere], 
                    CircleLocations[gCirclingWhere][0]);
                gStartedCircling = 0;
            }
            land_alarm = set_alarm( itof( delay ), 0.0, land );
            anno_alarm = set_alarm( itof( delay- 10 ), 0.0, &land_announce(1));
            return;
        }
        else
        {
                                    /* Same formula as in query_flight_time   */
            if(gStartedCircling)
            {
                // Determine the distance
                if(CircleLocations[gCirclingWhere][0] == CircleLocations[gWhere][0])
                    dist = NEAR_DIST;
                else
                    dist = query_domain_dist(CircleLocations[gCirclingWhere][0],
                        CircleLocations[gWhere][0]);

                delay = (30* dist+ 5)/ 20 - (50+ dist* random( find_player( gOwner )->
                    query_skill( SS_ANI_HANDL ) ))/ 100;
                gStartedCircling = 0;
            }
            anno_alarm = set_alarm( itof( delay- 10 ), 0.0, &land_announce(1));
            land_alarm = set_alarm( itof( delay ), 0.0, circle );
            return;
        }
    }

    room->notify_winged_steed_take_off();
    tell_room( room, "The winged beast stretches its pinions and flies "+
        "off into the sky.\n", ({ this_object(), rider, }) );
    rooms = room->query_exit_rooms();
    j = sizeof( rooms );
    for (i=0;i<j;i++)
    {
        if (!(find_object( rooms[i] )->query_prop( ROOM_I_INSIDE )))
        {
            tell_room( rooms[i], "A dark, winged shape rises into the sky "+
                "like a dark cloud and flies off into the distance.\n" );
        }
    }

    tell_room( this_object(), "Your winged steed stretches its pinions "+
        "and takes off into the sky, carrying you with it.\n",
        ({ this_object() }) );
    gFlying = 1;
    move_living( "M", STEED_ROOM );

    if(!gCircling)
    {
        delay = query_flight_time( file_name( room ), Dest[gWhere] );

        while (delay < 1)
        {
            SPELL_INHERIT->log_spell( "yalarochrama", "Error in take_off().\n"+
                "\tOwner: "+ gOwner + "\n"+
                "\tFrom : "+ file_name( room )+ "\n"+
                "\tDest : "+ Dest[gWhere]+ "\n"+
                "\tDebugger info : "+ gFlying+ ", "+ delay+ "\n" );
            msg = "Your steed does not know the direction to "+
                capitalize( gWhere );
            gWhere = choose_random_dest();
            delay = query_flight_time( file_name( room ), Dest[gWhere] );
            msg += ", therefore it decides to fly to "+ capitalize (gWhere)+
                " instead.\n";
            tell_room( this_object(), msg, ({ this_object() }) );
        }

        set_alarm( itof( 5+ random( 10 ) ), 0.0, random_message );
        anno_alarm = set_alarm( itof( delay- 10 ), 0.0, &land_announce( 1 ));
        land_alarm = set_alarm( itof( delay ), 0.0, land );
    }
    else
    {
        delay = query_flight_time_to_domain( file_name(room), 
            CircleLocations[gWhere][0]);

        set_alarm( itof( 5+ random( 10 ) ), 0.0, random_message );
        land_alarm = set_alarm( itof( delay ), 0.0, circle );
        anno_alarm = set_alarm( itof( delay- 10 ), 0.0, &land_announce(1));
    }
}

void circle()
{
    string	msg;
	object	*dest_users;
	object	rider;

	// Reward the nazgul with a tiny bit
	if (strlen( gOwner ))
	{
		rider = find_player( gOwner );
		if(objectp(rider))
			IDLENESS->increase_activity( rider, RARE_SPELL );
	}


	// Notify the users
	dest_users = find_players_in_region(gWhere);
	msg = "The winged figure curves in an arc through the lowest clouds " +
		"then gracefully begins circling in the air above.\n";
	dest_users->catch_msg(msg);

	// Write to the nazgul
    msg = "Your winged steed decends and starts circling over " + 
		implode(map(explode(gWhere, " "), capitalize), " ") + ".\n";
    tell_room( this_object(), msg, ({ this_object() }) );
    gStartedCircling = 1;
    gCircling = 1;
    gCirclingWhere = gWhere;
}

void land()
{
 int i, j;
 string *rooms, site_descr;
 object _wyrm, _here;

    remove_alarm( land_alarm );
    land_alarm = 0;
    move_living( "M", Dest[gWhere] );
    _wyrm = this_object();
    _here = environment( _wyrm );
    tell_room( _here, "A huge winged beast descends from the sky and "+
        "lands here.\n", ({ _wyrm }) );

    rooms = _here->query_exit_rooms();
    j = sizeof( rooms );
    for (i=0;i<j;i++)
    {
        if (!(find_object( rooms[i] )->query_prop( ROOM_I_INSIDE )))
        {
            tell_room( rooms[i], "A huge winged beast descends from the "+
                "sky and seems to land not far from here.\n" );
        }
    }
    
    _here->notify_winged_steed_landing();
/*
    tell_room( _wyrm, "And then, suddenly, your steed lands with a mighty "+
        "beating of the pinions and you are back on solid earth.\n",
        ({ _wyrm }) );
*/
    gFlying = 0;

    switch (gWhere)
    {
    case "minas morgul":
        site_descr = "The dread tower shoots rapidly high to the sky and "+
            "you find yourself in the Angmar Square in Minas Morgul.\n";
        break;
    case "black tower":
        site_descr = "The dread tower shoots rapidly high to the sky and "+
            "you find yourself at the bestiary atop the Black Tower of Minas Morgul.\n";
        break;
    case "morannon":
        site_descr = "You have landed by a cobbled road somewhere in "+
            "Ithilien in Gondor.\n";
        break;
    case "lebennin":
        site_descr = "The flat plain of grass quickly approaches as you "+
            "land in the middle of a green field.\n";
        break;
    case "isengard":
        site_descr = "You have landed on the rocky slope of a small "+
            "island.\n";
        break;
    case "evendim":
        site_descr = "A grassy rolling hills suddenly grow up from an "+
            "apparenlty flat surface as your perspective changes during "+
            "the landing. You have landed on a track on top of a rolling "+
            "hill in the Shire.\n";
        break;
    case "trollshaws":
        site_descr = "You have landed in the middle of a grove of trees, "+
            "near some huge rocks.\n";
        break;
    case "vingaard mountains":
        site_descr = "The wyrm rapidly loses the speed and lands on the "+
            "top of a mount in the Vingaard Mountains.\n";
        break;
    case "icewall":
        site_descr = "You can see nothing but swirling patches of snow as "+
            "you decend upon the drift and land below it.\n";
        break;
    case "pax tharkas":
        site_descr = "Branches crack scraching the tide of your steed "+
            "as you break through the canopy of trees crowns. You have "+
            "landed in a light forest near the fortress of Pax Tharkas.\n";
        break;
    case "flotsam":
        site_descr = "You have landed by the end of some eroding road in "+
            "an evergreen forrest.\n";
        break;
    case "neraka":
        site_descr = "You have landed in the White Dragonarmy camp within "+
            "Neraka.\n";
        break;
    case "sparkle":
        site_descr = "A fresh, see breeze blows at your face as you land "+
            "on a peninsula.\n";
        break;
    case "hespyre mountains":
        site_descr = "You have landed in a barren valley surrounded by "+
            "the mighty Hespyre mountains.\n";
        break;
    case "raumdor":
        site_descr = "You have landed in the middle of the grim Forest of "+
            "Shadows.\n";
        break;
    case "underdark":
        site_descr = "You have landed on an icy ridge.\n";
        break;
    case "graveyard":
        site_descr = "Tombstones rise around you as you land in a "+
            "graveyard near a dark mansion.\n";
        break;
    case AVENIR_PORT_NAME:
        site_descr = "The ilumination changes rapidly as you reach the "+
            "very caverns of Avenir. Seconds later you land on a ledge of "+
            "a cliff along the cavern's wall.\n";
        break;
    case "argos":
        site_descr = "You have landed on a small clearing surrounded by "+
            "tall, dark pines.\n";
        break;
    case "desert":
        site_descr = "As your steed slows and the mounds of sand quickly "+
            "approach, you feel the searing Athasian heat growing more "+
            "intense.  You land your steed atop the largest dune.\n";
    case EMERALD_NAME:
        site_descr = "Below, a gigantic orange structure looms into view."
          + " You instantly sense the presence of a powerful and malevolent"
          + " spirit similar, yet different to your Lord and Master's."
          + " Feeling this is an appropriate place for your business, you"
          + " direct your steed downward where you land beside the immense"
          + " glowing orifice.\n";
        break;
    default:
        site_descr = "You have landed somewhere. If you want a better "+
            "landing descriptions here don't be lazy and submit one.\n";
    }    
    tell_room( _wyrm, site_descr, ({ _wyrm }) );
}

int do_shriek( string str )
{
	object	*dest_users;
	string	*msg;

	// This will only work when we are circling
	if(!gStartedCircling) return 0;

	// We cannot give adverbs
	if(strlen(str))
	{
		write("You cannot specify an adverb when mounted on your steed.\n");
		return 1;
	}

	dest_users = find_players_in_region(gWhere);

	msg = ({ "The figure atop the winged beast rasps at his steed. The " +
		"winged beast shrieks terribly. Blind fear mixed with unheard of terror and deadly cold " +
		"descend upon you.\n",

		"The fell wraith atop the winged shape shrieks shrilly. You " +
		"struggle with fright and madness for mastery of your actions.\n" });
	dest_users->catch_msg(one_of_list(msg));

    if(query_verb() != "shriek")
    {
        tell_room(this_object(),
            "You shriek shrilly, blanketing the land below with the dread " +
            "of the Nine.\n");
        return 1;
    }
    else
    {
        // Let the original shriek command take over
        return 0;
    }
}

int do_mount( string str )
{
 int i;
 object tp = this_player(), *o, *e;

    if (gFlying)
    {
        return 0;
    }
    notify_fail( "Mount what?\n" );
    if (!strlen( str ))
    {
        return 0;
    }
    str = lower_case( str );

    if (!parse_command( str, environment( tp ), "[the] %l", o ))
    {
        return 0;
    }
    o = NORMAL_ACCESS( o, 0, 0 );

    if (sizeof( o ) != 1)
    {
        return 0;
    }
    if (o[0] != this_object())
    {
        return 0;
    }
    if (environment( tp ) == this_object())
    {
        return 0;
    }
    if(gRemoving)
    {
        return 0;
    }
    
    if (environment( tp )->query_prop( ROOM_I_INSIDE ) && 
        (environment( this_object() )->query_domain() != "Avenir"))
    {
        notify_fail( "There is not enough room to mount your "+
            query_race_name()+ " here.\n" );
        return 0;
    }

    if (tp->query_attack())
    {
        write( "You are too busy fighting to do that.\n" );
        return 1;
    }

    if (this_object()->query_attack())
    {
        write( QCTNAME( this_object() )+ " is fighting, you cannot mount "+
            "it now!\n" );
        return 1;
    }

    if (tp->query_name() != gOwner)
    {
        write( "The fell beast does not accept you as its rider.\n" );
        return 1;
    }

    if (tp->query_skill( SS_ANI_HANDL ) < MOUNT_LVL)
    {
        write( "Trying to mount this fell beast would be your certain "+
            "doom, since you cannot control it properly!\n" );
        return 1;
    }

    if (tp->resolve_task( TASK_ROUTINE,
        ({ TS_DEX, SS_RIDING, SS_ANI_HANDL })) <= 0)
    {
        write( "Your clumsy attempt to mount the fell beast fails and you "+
            "are thrown off.\n" );
        say( QCTNAME( tp )+ "'s clumsy attempt to mount the fell beast "+
            "fails and "+ HE( tp )+ " is thrown off.\n" );
        return 1;
    }

    add_prop( ROOM_I_IS, 1 );
    tp->remove_prop( OBJ_M_NO_GET );
    tell_room( environment( this_object() ), QCTNAME( tp )+ " mounts "+
        HIS( tp )+ " winged steed.\n", ({ this_object(), tp }) );

    if (tp->move_living( "M", this_object(), 1, 1 ))
    {
        write( "Your "+ query_race_name()+ " is unable to carry you.\n" );
    }
    else
    {
        write( "You mount your "+ query_race_name()+ ".\n" );
        e = tp->query_enemy( -1 );
        if (!combat_extern)
        {
            combat_reload();
        }
        for (i=0;i<sizeof( e );i++)
        {
            combat_extern->cb_add_enemy( e[i], 1 );
        }
        tp->stop_fight( e );
    }
    tp->add_prop( OBJ_M_NO_GET, 1 );
    remove_prop( ROOM_I_IS );

    return 1;
}

/*
 * Function name: do_dismount
 * Description:   Dismount the steed
 * Arguments:     arg - the rest of the command string
 * Returns:       1 - command succesful
 *                0 - command not succesful
 */
nomask int do_dismount( string str )
{
 int i;
 object tp = this_player(), cb_obj, enemy, *enemies;

    if (strlen( str ) && !id( str ))
    {
        notify_fail( "Dismount what?\n" );
        return 0;
    }

    if (environment( tp ) != this_object())
    {
        notify_fail( "But you are not mounted on the steed!\n" );
        return 0;
    }

    if (gFlying)
    {
        notify_fail( "The fell beast is flying through the air!\n"+
            "Dismounting now would be your doom!\n" );
        return 0;
    }

    tell_room( environment( this_object() ), QCTNAME( tp )+ " dismounts "+
        HIS( tp )+ " "+ query_race_name()+ ".\n", ({ this_object(), tp }));
    write( "You dismount your "+ query_race_name()+ ".\n" );
    tp->move_living( "M", environment( this_object() ), 1, 1 );
    tp->command( "$look" );
    enemy = query_attack();
    if (enemy)
    {
        stop_fight( enemy );
        enemy->stop_fight( this_object() );
//      tp->catch_msg( "You attack " + QTNAME( enemy )+ ".\n" );
        tp->attack_object( enemy );
    }

    enemies = query_enemy( -1 );
    cb_obj = tp->query_combat_object();
    for (i=0;i<sizeof( enemies );i++)
    {
        cb_obj->cb_add_enemy( enemies[i], 1 );
    }
    stop_fight( enemies );
    return 1;
}

void take_off_and_remove()
{
    string *rooms;
    object room = environment( this_object() );
     while (!room->query_prop( ROOM_I_IS ))
    {
        room = environment( room );
    }
 
    room->notify_winged_steed_take_off();
    tell_room( room, "The winged beast stretches its pinions and flies "+
        "off into the sky.\n", ({ this_object() }) );
    rooms = room->query_exit_rooms();
    int j = sizeof( rooms );
    for (int i=0;i<j;i++)
    {
        if (!(find_object( rooms[i] )->query_prop( ROOM_I_INSIDE )))
        {
            tell_room( rooms[i], "A dark, winged shape rises into the sky "+
                "like a dark cloud and flies off into the distance.\n" );
        }
    }
    
    remove_object();
}

int do_dismiss( string str )
{
    object tp = this_player();
    mixed o;
    
    notify_fail( "Dismiss what?\n" ); 
    if (!str || !strlen( str ))
    {
        return 0;
    }

    if (!parse_command( str, environment( tp ), "[the] %l", o ))
    {
        notify_fail( "Dismiss what 1?\n" );
        return 0;
    }
    o = NORMAL_ACCESS( o, 0, 0 );

    if (sizeof( o ) != 1)
    {
    notify_fail( "Dismiss what 2?\n" );
        return 0;
    }
    
    if (o[0] != this_object())
    {
    notify_fail( "Dismiss what 3?\n" );
        return 0;
    }
    
    if (environment( tp ) == this_object())
    {
        notify_fail( "But you are mounted on the steed!\n" );
        return 0;
    }

    if (tp->query_name() != gOwner)
    {
        write( "The fell beast does not accept you as its rider.\n" );
        return 1;
    }

    write("You dismiss the " + o[0]->short() + ".\n");
    gRemoving = 1;
    set_alarm( 2.0, 0.0, take_off_and_remove );
    return 1;
}

int do_command( string dir )
{
    int i, j, circle = 0;
    mixed  *o;
    object  tp = this_player();
    string *a, *dest, where, Where;

    if (environment( tp ) != this_object())
    {
        return 0;
    }
    
    if (!strlen( dir ))
    {
        notify_fail( "Command whom to go where?\n" );
        return 0;
    }

    dir = lower_case( dir );
    if (dir == "destinations")
    {
        dest = m_indexes( Dest );
        where = "Your steed recognizes these destinations:\n";
        for (i=0; i < sizeof( dest ); i++)
        {
            a = explode( dest[i], " " );
            for (j=0; j < sizeof( a ); j++)
            {
                a[j] = capitalize( a[j] );
            }
            dest[i] = implode( a, " " );
        }
        where += break_string( COMPOSITE_WORDS( dest )+ ".\n", 60, "\t" );

		// List circle locations
		where += "Additionally you can order your steed to circle these " +
			"regions:\n";
		dest = m_indexes(CircleLocations);
        for (i=0; i < sizeof( dest ); i++)
        {
            a = explode( dest[i], " " );
            for (j=0; j < sizeof( a ); j++)
            {
                a[j] = capitalize( a[j] );
            }
            dest[i] = implode( a, " " );
        }
		where += break_string( COMPOSITE_WORDS( dest )+ ".\n", 60, "\t" );

        write( where );
        return 1;
    }

    if (!parse_command( dir, environment( this_object() ),
        "%l [to] 'circle' %s", o, where ))
    {
        if (!parse_command( dir, environment( this_object() ),
            "%l [to] [go] / [fly] [to] %s", o, where ))
        {
            notify_fail( "Command whom to go to where?\n" );
            return 0; 
        }
    }
    else
    {
        circle = 1;
    }

    if (o[0] != 1)
    {
        notify_fail( "Command whom to fly where?\n" );
        return 0;
    }

    o = o[1..];
    if (member_array( this_object(), o ) < 0)
    {
        notify_fail( "Command whom?\n" );
        return 0;
    }

    a = explode( where, " " );
    for (i=0;i<sizeof( a );i++)
    {
        a[i] = capitalize( a[i] );
    }
    Where = implode( a, " " );

    if(circle)
    {
        // Circling a region
        if (member_array( where, m_indexes( CircleLocations ) ) < 0)
        {
            notify_fail( Where+ " is not a possible region!\n" );
            return 0;
        }

        if (environment( this_object() )->query_prop( ROOM_I_INSIDE ) && 
            (environment( this_object() )->query_domain() != "Avenir") )
        {
            notify_fail( "Your "+ query_race_name()+ " cannot take off in "+
                "a closed room!\n" );
            return 0;
        }

        // Make sure the domain is the same

        write( "You command your winged steed to circle "+ Where+ ".\n" );

        // Use the players animal-handling skill
        if (tp->resolve_task( TASK_ROUTINE,
            ({ TS_DEX, SKILL_AVG, TS_DIS, SS_ANI_HANDL, SKILL_END })) <= 0)
        {
            gCircling = 0;
            gWhere = choose_random_dest();
            write( "Your winged steed does not obey your command.\n" );
        }
        else
        {
            gCircling = 1;
            gWhere = where;
        }

    }
    else
    {
        // Normal flight

        if (member_array( where, m_indexes( Dest ) ) < 0)
        {
            notify_fail( Where+ " is not a possible direction!\n" );
            return 0;
        }

        if (environment( this_object() )->query_prop( ROOM_I_INSIDE ) && 
            (environment( this_object() )->query_domain() != "Avenir") )
        {
            notify_fail( "Your "+ query_race_name()+ " cannot take off in "+
                "a closed room!\n" );
            return 0;
        }

        catch( Dest[where]->load_me() );
        if (!objectp( find_object( Dest[where] ) ))
        {
            notify_fail( "Your steed does not know the direction to "+ Where+
                "!\nPlease make a bug report!\n" );
            return 0;
        }

        // No longer circling
        gCircling = 0;

        write( "You command your winged steed to bring you to "+ Where+ ".\n" );

        // Use the players animal-handling skill
        if (tp->resolve_task( TASK_ROUTINE,
            ({ TS_DEX, SKILL_AVG, TS_DIS, SS_ANI_HANDL, SKILL_END })) <= 0)
        {
            gWhere = choose_random_dest();
            write( "Your winged steed does not obey your command.\n" );
        }
        else
        {
            gWhere = where;
        }
        
    }

    set_alarm( 2.0, 0.0, take_off );
    return 1;
}

int query_gFlying()
{
    return gFlying;
}

string  query_gWhere()
{
    return gWhere;
}

string  query_location()
{
    return file_name( environment( this_object() ) );
}

string  query_destination()
{
    return Dest[gWhere];
}

int query_domain_dist( string dom1, string dom2 )
{
 int j;
 string tmp;

    if ((j = member_array( dom2, gDist[dom1] )) < 0)
    {
        tmp = dom1;
        dom1 = dom2;
        dom2 = tmp;
        if ((j = member_array( dom2, gDist[dom1] )) < 0)
        {
            return MAX_DIST;
        }
    }
    return gDist[dom1][j+1];
}

/* Function   : query_flight_time
 * Description: Determine the time in flight from one location to
 *              another
 * Arguments:   string from_file: Filename of departure room
 *              string to_file: Filename of destination room
 * Returns:     < 0: error
 *              > 0: time in secs
 */
int
query_flight_time( string from_file, string to_file )
{
 int     dist;
 object  from, to;
 string *a_from, *a_to;

    if (!strlen( from_file ))
    {
        from = environment( this_object() );
        while (!from->query_prop( ROOM_I_IS ))
        {
            from = environment( from );
        }
        from_file = file_name( from );
    }
    else
    {
        from = find_object( from_file );
    }
    if (!strlen( to_file ))
    {
        return -1;
    }
    to_file->load_me();
    if (!objectp( to = find_object( to_file ) ))
    {
        return -4;
    }
    if (!(from->query_prop( ROOM_I_IS )) || !(to->query_prop( ROOM_I_IS )))
    {
        return -2;
    }
    a_from = explode( from_file, "/" );
    a_to = explode( to_file, "/" );

                                /* Not a domain room.                     */
    if ((sizeof( a_from ) < 4) || (a_from[1] != "d"))
    {
        return -3;
    }
                                /* Different domains                      */
    if (a_from[2] != a_to[2])
    {
        dist = query_domain_dist( a_from[2], a_to[2] );
    }
    else
    {
        dist = MIN_DIST;
    }

                                /* 0.5dist + dist*(1- rand( ani_handl ))  */
    dist = (30* dist+ 5)/ 20 - (50+ dist* random( find_player( gOwner )->
        query_skill( SS_ANI_HANDL ) ))/ 100;

    return dist;
}

/* Function   : query_flight_time_to_domain
 * Description: Determine the time in flight from one location to
 *              another
 * Arguments:   string from_file: Filename of departure room
 *              string to_domain: Domain of the destination room
 * Returns:     < 0: error
 *              > 0: time in secs
 */
int
query_flight_time_to_domain( string from_file, string to_domain )
{
 int     dist;
 object  from;
 string *a_from;

    if (!strlen( from_file ))
    {
        from = environment( this_object() );
        while (!from->query_prop( ROOM_I_IS ))
        {
            from = environment( from );
        }
        from_file = file_name( from );
    }
    else
    {
        from = find_object( from_file );
    }

    if (!(from->query_prop( ROOM_I_IS )))
    {
        return -2;
    }

    a_from = explode( from_file, "/" );

                                /* Not a domain room.                     */
    if ((sizeof( a_from ) < 4) || (a_from[1] != "d"))
    {
        return -3;
    }
                                /* Different domains                      */
    if (a_from[2] != to_domain)
    {
        dist = query_domain_dist( a_from[2], to_domain );
    }
    else
    {
        dist = MIN_DIST;
    }

                                /* 0.5dist + dist*(1- rand( ani_handl ))  */
    dist = (30* dist+ 5)/ 20 - (50+ dist* random( find_player( gOwner )->
        query_skill( SS_ANI_HANDL ) ))/ 100;

    return dist;
}

int set_owner( mixed o )
{
 int maxl;

    if (stringp( o ))
    {
        o = lower_case( o );
        o = find_player( o );
    }
    if (!objectp( o ))
    {
        return 0;
    }
    maxl = 24;
    if (!o->query_nazgul() && (o->query_morgul_level() < maxl) &&  
        !o->query_wiz_level())
    {
        return 0;
    }
    gOwner = o->query_name();
    return 1;
}

string query_owner()
{
    return gOwner;
}

void land_announce( int i )
{
    string msg;
    object *dest_users;

    anno_alarm = 0;

	if(gCircling)
	{
		dest_users = find_players_in_region(gWhere);
		switch(i)
		{
			case 1:
			{
				msg = "A distant bird-like shape streaks down from the " +
					"clouds overhead at dizzying speeds. Horror stiffens " +
					"every muscle in your body.\n";
				dest_users->catch_tell(msg);
				tell_room( this_object(), "You order your steed lower to " +
					"scout " + implode(map(explode( 
					gWhere, " "), capitalize), " ") + ".\n" );
				return;
				break;
			}
			default:
			{
				return;
				break;
			}
		}
	}
	else
	{
		switch (i)
		{
			case 1:
			{
				msg = "A dark shape, like a cloud and yet not "+
					"like a cloud, for it moves far too quickly, is coming " +
					"out of the sky, speeding towards you, blocking out all " +
					"light as it approaches.\n";
				tell_room( Dest[gWhere],  msg);
				tell_room( this_object(), "Your fell beast is beginning to "+
					"descend again.\n" );
                Dest[gWhere]->notify_winged_steed_approach(2);
				break;
			}
			case 2:
			{
				msg = "Blind fear and deadly cold embrace you as the dark " +
					"shape draws nearer.\n";
				tell_room( Dest[gWhere],  msg);
				tell_room( this_object(), "Down, down the beast falls out of the "+
					"sky almost like a rock, diving through the air to the "+
					"ground.\n" );
                Dest[gWhere]->notify_winged_steed_approach(1);
				return;
				break;
			}
			default:
			{
				return;
				break;
			}
		}
	}

	set_alarm( 5.0, 0.0, &land_announce( i+1 ) );
}

void add_spotted_player(object player)
{
	// Make sure we have only four members
	if(sizeof(spotted_players) > 4)
		spotted_players = exclude_array(spotted_players, 4, 
			sizeof(spotted_players));

	// Add the player to the beginning of the array
	spotted_players = ({ player }) + spotted_players;
}

int spot_player()
{
	object	*dest_users;
	object	player;

	// Find all visible users
	dest_users = find_players_in_region(gWhere, 1);

	// Remove all previously spotted players
	dest_users -= spotted_players;

	// We don't always spot players
	if((random(100) > 70) || (!sizeof(dest_users)))
	{
		add_spotted_player(0);
		return 0;
	}

	// Find a player to spot
	player = one_of_list(dest_users);
	add_spotted_player(player);

	player->catch_msg("The shadow of horror wheels and turns, passing " +
		"lower now and sweeping past with its enormous wings. The rider " +
		"atop the winged steed looks directly at you and jerks the reins " +
		"in your direction. As he nears you, the wraith hisses " +
		"threateningly in your direction and rasps loudly to his bird-like " +
		"steed. The steed skillfully rises to the heavens once again.\n");
	tell_room(environment(player),
		"The shadow of horror wheels and turns, passing lower now and " +
		"sweeping past with its enormous wings. The rider atop the " +
		"winged steed looks directly at " + QTNAME(player) + " and jerks " +
		"the reins in " + player->query_possessive() + " direction. As he " +
		"nears " + player->query_objective() + ", the wraith hisses " +
		"threateningly in " + player->query_possessive() + " direction and " +
		"rasps loudly to his bird-like steed. The steed skillfully rises to " +
		"the heavens once again.\n", player);
	tell_room( this_object(), "Your fell steed wheels and turns, passing " +
		"lower now and sweeping down with its enormous wings. You hiss as " +
		"you sight " + QNAME(player) + " below and inform your steed of " +
		player->query_possessive() + " presence with a sharp rasp.\n");
	return 1;
}

void random_message()
{
	mixed	txt;
	object	*dest_users;
	

    if (!gFlying)
    {
        return;
    }

    if(!gStartedCircling)
    {
        if (!sizeof( random_messages ))
        {
            random_messages =
            ({
                "The chilly wind is blowing icily into your face.\n",
                "Far below your steed, clouds are passing.\n",
                "Beating its pinions slowly, your steed is carrying you "+
                    "swiftly to your destination.\n",
                "Like a dark cloud out of Mordor you and your steed are "+
                    "passing across the realms.\n",
                "Your steed utters a harsh croaking scream, spreading "+
                    "terror in the lands below.\n",
                "Faster than any wind your winged steed carries you onwards.\n"
            });
        }
        txt = one_of_list( random_messages );
        tell_room( this_object(), txt );
        random_messages -= ({ txt });

	    set_alarm( itof( 10+ random( 10 ) ), 0.0, random_message );
    }
    else
    {
		if(!sizeof(random_circle_messages))
		{
			random_circle_messages = 
				({
					({ // User message
					"The winged beast slowly spirals down examining an " +
					"area a short distance away.\n",
					// Nazgul message
					"Your winged beast slowly spirals down to examine an " +
					"area, but you note nothing of importance.\n" 
					}),

					({ 
					"The winged beast circles high above yet the fear " +
					"and terror emanating from it is quite palpable.\n",
					"Your winged beast soars high searching for prey.\n"
					}),

					({
					"The winged beast wheels abruptly and approaches you. " +
					"The desire to hide tightly grips your mind.\n",
					"Your steed wheels abruptly, its great pinions beating " +
					"slowly. Terror spreads across the lands below.\n" 
					}),

					({
					"The winged beast rushes past barely overhead, its " +
					"ghastly pinions beating slowly. A dark hooded figure " +
					"mounted on its back peers intently from side to side " +
					"at the ground. They swiftly pass out of sight.\n",
					"Your steed wheels abruptly, its great pinions beating " +
					"slowly. You peer intently at the ground, but you fail " +
					"to locate suitable prey.\n"
					}),

					({
					"The winged beast suddenly dives down over a nearby " +
					"point. Seconds later it rockets skyward.\n",
					"Your beast spots something on the ground and spirals " +
					"downward. You see nothing of interest and order it to " +
					"ascend once again.\n"
					}),

					({
					"The winged beast effortlessly glides in tight circles " +
					"not far from you, letting out a guttural croak. As the " +
					"circles widen, it angles farther and farther away.\n",
					"Your winged steed glides effortlessly in tight circles, " +
					"then angles wider and wider to scan an increasingly " +
					"broad area.\n"
					})
				});
		}

		// Spot a player or write a random message
		if(!spot_player())
		{
			txt = one_of_list( random_circle_messages );
			random_circle_messages -= ({ txt });

			// Write to the nazgul and the players in the region
			dest_users = find_players_in_region(gWhere);	
			dest_users->catch_msg(txt[0]);
			tell_room( this_object(), txt[1] );
		}

	    set_alarm( itof( 30+ random( 10 ) ), 0.0, random_message );
    }
}

void remove_steed()
{
 int i, s;
 object *inv = all_inventory( this_object() ), *liv,
     env = environment( this_object() );

    if (gFlying)
    {
        return;
    }  
    if (sizeof( inv ))
    {
        liv = FILTER_LIVE( inv );
        inv -= liv;

        s = sizeof( inv );
        for (i=0;i<s;i++)
        {
            if (inv[i]->move( env ))
            {
                inv[i]->move(env, 1);
            }
        }
        if (s)
        {
            tell_room( env, capitalize( COMPOSITE_DEAD( inv ) )+ " fall"+
                (s == 1 ? "s " : " ")+ "down from the back of the "+
                short()+ ".\n" );
        }

        if ((s = sizeof( liv )))
        {
            for (i=0;i<s;i++)
            {
                throw_off( liv[i] );
            }
        }
    }
    tell_room( env, "The winged beast stretches its pinions and flies off "+
        "into the sky.\n" );
    set_alarm( 0.1, 0.0, remove_object );
}

public void run_away()
{
    throw_off();
    remove_steed();
}

public void attacked_by( object ob )
{
    throw_off();
    ::attacked_by( ob );
    remove_steed();
}

varargs int throw_off( object rider )
{
 int i;
 object  env = environment( this_object() ), tp = this_player(), cb_obj,
     enemy, *enemies;

                                /* Can't throw off someone during a flight*/
    if (gFlying)
    {
        return 0;
    }
    if (!objectp( rider ) && stringp( gOwner ))
    {
        rider = find_player( lower_case( gOwner ) );
    }

    if (!objectp( rider ) || (environment( rider ) != this_object()))
    {
        return 0;
    }

    tell_room( env, QCTNAME(rider)+ " is thrown off "+ HIS( rider )+
        " "+ query_race_name()+ ".\n", ({ this_object(), rider }) );
    rider->catch_msg( "You are thrown off your "+ query_race_name()+ ".\n");
    rider->move_living( "M", env, 1, 1 );
    rider->command( "$look" );

    enemy = query_attack();
    if (enemy)
    {
        stop_fight( enemy );
        enemy->stop_fight( this_object() );
//        rider->catch_msg( "You attack "+ QTNAME( enemy )+ ".\n" );
        rider->attack_object( enemy );
    }

    enemies = query_enemy( -1 );
    cb_obj = rider->query_combat_object();
    for (i=0;i<sizeof( enemies );i++)
    {
        cb_obj->cb_add_enemy( enemies[i], 1 );
    }
    stop_fight( enemies );
    return 1;
}

/*
 * Function name: catch_msg (mask)
 * Description:   This function is called for normal messages sent to
 *                the steed.  Used for forwarding say's and the like.
 * Arguments:     str    - the message
 *                player - The object generating the message
 */
void catch_msg( mixed str, object player )
{
    if (!player)
    {
        player = this_player();
    }
    ::catch_msg( str, player );
    if (player == this_object())
    {
        return;
    }
    if (player && environment( player ) == this_object())
    {
        tell_room( environment(), str, this_object(), player );
    }
    else
    {
        tell_room( this_object(), str, this_object(), player );
    }
}

/*
 * Function name: enter_inv (mask)
 * Description  : Not sure. It looks like rejecting extra/illegal/tele-
 *                porting passengers/items.
 */
public void enter_inv( object ob, object from )
{
    ::enter_inv( ob, from );

    if (!objectp( ob ) || !objectp( from ) || living( ob ))
    {
        return;
    }
    ob->move( environment( this_object() ), 1 );
}

nomask string query_domain()
{
    return "Gondor";
}

/*
 * Function name: query_ip_number
 * Description  : Not sure, but it seems it checks for the passengers.
 */
public string query_ip_number( object player )
{
 object *dummy;

    if (player == this_object())
    {
        dummy = FILTER_PLAYERS( all_inventory( this_object() ) );
        if (sizeof( dummy ))
        {
            return query_ip_number( dummy[0] );
        }
        else
        {
            return 0;
        }
    }
    return query_ip_number( player );
}

/*
 * Function name: do_time
 * Description  : Checks the Gondor time in the wyrm's environment.
 */
public int do_time( string str )
{
    if (environment( this_player() ) != this_object())
    {
        return 0;
    }

	// Checking time while circling
	if(gStartedCircling && (member_array(CircleLocations[gWhere][0],
		({ "Shire", "Gondor" }) ) != -1))
		return check_time(str);

    return environment( this_object() )->check_time();
}

mixed query_circling_region()
{
    if(!gStartedCircling) return 0;
    return gWhere;
}


// This was once in /std/living/description.c, and I have replaced it here as
//  this object still used it, causing
//  "Function used in map could not be found: fights" in /lplog
/*
 * Function name:   fights
 * Description:	    Find out who fights who.
 * Arguments:       me, enemy: The fighting folks
 * Returns:         "you" if the enemy is fighting me, or else his name
 */
static mixed
fights(object me, object enemy)
{
    if (!objectp(me))
	return 0;

    if (me->query_enemy(0) == enemy)
    {
	if (me == this_object())
	    return "you";
	else
	    return me->query_the_name(this_object());
    }
    else
	return 0;
}
