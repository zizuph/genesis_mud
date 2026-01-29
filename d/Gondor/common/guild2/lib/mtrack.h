/*
 *  mtrack.h
 *  Olorin of Gondor, Aug 1994.
 *
 *  Copied from /d/Gondor/common/guild/lib/rtrack.h
 *
 *  Revision history:
 *  10.08.2001 - minor maintenance changes by Chmee
 * 24.03.2009 - changed the tellroom to allbb to allow for sniffing while in 
 *                         the realm of shadows without revealing the pressence.
 */
#define COST   4                /* Mana-cost for tracking.                */
#define RACES  ({"dwarf","elf","gnome","goblin","hobbit","human","animal"})
#define EXTRA  ", sniffing on the ground"
#define LIVE_S_EXTRA_SHORT_OLD    "_live_s_extra_short_old"

#include <terrain.h>

int sniff_alarm;

void sniff_now( object room, object player, int track_skill )
{
 string *track_arr, result, old_prop, dir, race;
 int i;
 mixed  *exits;

    result = "You do not smell any tracks.\n";
    old_prop = 0;
    remove_alarm( sniff_alarm );
    sniff_alarm = 0;

    if (!objectp( player ))
    {
        return;
    }
    track_arr = room->query_prop( ROOM_S_DIR );
    if (player->query_wiz_level())
    {
        write( "Wizinfo: "+ player->query_name()+ ": tracking skill "+
            track_skill+ ", "+ implode( track_arr, ", " )+ "\n" );
    }
                                /* just in case, but presently,
                                 *ROOM_I_INSIDE prevents setting of
                                 *ROOM_S_DIR                              */
    if (room->query_prop( ROOM_I_INSIDE ))
    {
        track_skill -= 50;
    }
    if (this_player()->query_morgul_invis())
    {
        track_skill += 50;
    }
    track_skill /= 2;
    track_skill += random( track_skill );

    if (pointerp( track_arr ) && track_skill > 0)
    {
        dir = track_arr[0];
        if (dir == "X" || dir == "M")
        {
            dir = "nowhere";
        }
        race = track_arr[1];
        result = "You can smell some tracks on the ground.\n";
        switch (track_skill)
        {
        case  1..10:
            break;
        case 11..20:
            if (random( 2 ))
            {
                exits = room->query_exit();
                if (i = sizeof( exits ))
                {
                    dir = exits[random( i/ 3 )* 3+ 1]; 
                }   
            }
            result += "They are probably leading " + dir + ".\n";
            break;
        case 21..50:
            result += "They are leading "+ dir+ ".\n";
            break;
        case 51..75:
            if (random( 2 ))
            {
                race = RACES[random( sizeof( RACES ) )];
            }
            result += "They were probably made by "+ LANG_ADDART( race )+
                " and are leading "+ dir+ ".\n";
            break;
        case 76..150:
            result += "They were made by "+ LANG_ADDART( race ) + 
                " and are leading "+ dir+ ".\n";
            break;
        }
    }
         
    player->catch_msg( result );
    if (old_prop = player->query_prop( LIVE_S_EXTRA_SHORT_OLD ))
    {
        player->change_prop( LIVE_S_EXTRA_SHORT, old_prop );
    }
    else
    {
        player->remove_prop( LIVE_S_EXTRA_SHORT );
    }
    
    set_this_player(player);
    allbb(" rises again.");
    return;
}

int
do_msniff()
{
 object paralyze, _here;
 int time, track_skill;
 string  old_prop = 0, msg = "";

    _here = environment( this_player() );
    if (!_here->query_prop( ROOM_I_IS ))
    {
        msg = ", but you do cannot smell anything";
    }
    if (_here->query_prop( ROOM_I_INSIDE ))
    {
        msg = ", but since you are inside a room, you cannot smell "+
            "anything";
    }
    if (_here->terrain_includes_any( TERRAIN_UNDERWATER ))
    {
        msg = ", but you only pulled in some water through your nose";
    }
    if (_here->terrain_includes_any( TERRAIN_ONVEHICLE ))
    {
        msg = ", but except the presence of dust you can't feel anything";
    }
    if (this_player()->query_mana() < 2*COST)
    {
        msg = ", but you are mentally too exhausted";
    }
    write( "You lower yourself to the ground and start sniffing for tracks"+
        msg+ ".\n" );
    allbb( " lowers "+ this_player()->query_objective()+ "self to the "+
		"ground and seems to sniff for something, as if hunting." );

    if (strlen( msg ))
    {
        return 1;
    }
    old_prop = this_player()->query_prop( LIVE_S_EXTRA_SHORT );
    if(old_prop == EXTRA)
    {
        old_prop = 0;
    }
    if(stringp( old_prop ))
    {
        this_player()->add_prop( LIVE_S_EXTRA_SHORT_OLD, old_prop );
    }
    this_player()->add_prop( LIVE_S_EXTRA_SHORT, EXTRA );
    this_player()->add_mana( -COST );
    time = _here->query_prop( OBJ_I_SEARCH_TIME );
    if (time < 1)
    {
        time = 10;
    }
    else
    {
        time += 5;
    }
    track_skill = this_player()->query_skill( SS_TRACKING );
    time -= track_skill/ 10;
    if (time < 1)
    {
        sniff_now( _here, this_player(), track_skill );
    }
    else
    {
        sniff_alarm = set_alarm( itof( time ), 0.0, &sniff_now( _here,
            this_player(), track_skill ) );
        setuid();
        seteuid( getuid() );
        paralyze = clone_object( "/std/paralyze" );
        paralyze->set_standard_paralyze( "tracking" );
        paralyze->set_stop_fun( "stop_sniff" );
        paralyze->set_stop_verb( "stop" );
        paralyze->set_stop_message( "You stop sniffing for tracks on the "+
            "ground.\n" );
        paralyze->set_remove_time( time );
        paralyze->set_fail_message( "You are busy sniffing for tracks. "+
            "You must 'stop' to do something else.\n" );
        paralyze->move( this_player(), 1 );
    }
    return 1;
}

varargs int stop_sniff( mixed arg )
{
 string old_prop;

    if(!objectp( arg ))
    {
        remove_alarm( sniff_alarm );
    }
    sniff_alarm = 0;
    allbb(" stops sniffing for tracks on the ground.");

    if (old_prop = this_player()->query_prop( LIVE_S_EXTRA_SHORT_OLD ))
    {
        this_player()->change_prop( LIVE_S_EXTRA_SHORT, old_prop );
    }
    else
    {
        this_player()->remove_prop( LIVE_S_EXTRA_SHORT );
    }
    return 0;
}
