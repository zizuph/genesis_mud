/*   larsether_base.c
 *
 *   Base location for the succession of rooms
 *   above the Realms, in a circular journey around
 *   the Donut by way of Lars's Ether.
 *
 *   Vitwitch, 2022
 */

#include <macros.h>
#include "../defs.h"

inherit "/std/room";

static float gSecondsPerStage;

int
is_lgellirroom()
{
    return 1;
}

int
is_lgellirroom_larsether()
{
    return 1;
}

string
otherworld()
{
    return LGELLIR_ETHER_INACTION_MESG;
}


nomask void
reset_room()
{
    gSecondsPerStage = itof(LARSETHER_SECSPERST);
    return;
}


nomask void
create_room()
{
    set_short(" ");
    set_long("\n");

    add_prop(ROOM_I_INSIDE, 0);
    add_prop(ROOM_I_LIGHT,1); 
    add_prop(ROOM_M_NO_ATTACK, "@@otherworld");
    add_prop(ROOM_M_NO_MAGIC, "@@otherworld");
    add_prop(ROOM_M_NO_TELEPORT_FROM, "@@otherworld");
    add_prop(ROOM_M_NO_TELEPORT_TO, 1);
    add_prop(ROOM_M_NO_SCRY, 1);

    add_prop( ROOM_I_NO_ALLOW_STEED, 1 );

    reset_room();

    return;
}


void
transfer_to_next(object ob, object from)
{
    int idom, ndom;
    int numtry = 0;
    int maxtry = 5;
    string movelocn = "";

    if ( living(ob) )
    {
        string pname = ob->query_real_name();

	// index definition error condition
        if ( LARSETHER_ENDINGIDX >= LARSETHER_STTINGIDX ) 
            movelocn = LARSETHER_ENDLOCDEF;

        int way_stage = ob->query_prop(LGELLIR_LARSETHER_INDEX);
        ob->remove_prop(LGELLIR_LARSETHER_INDEX);

        if ( (way_stage % LARSETHER_AWARDSDIV) == 0 ) 
	{
	    // award gxp if property has been set by club_gapeth.c
	    int gxp_incr = ob->query_prop(LGELLIR_PROP_GXP_INCREMENT);
            if ( gxp_incr > 0 ) 
	    {
	        ob->add_exp_general(gxp_incr);
                int count = ob->query_prop(LGELLIR_PROP_INCR_COUNT);
		count++;
                ob->add_prop(LGELLIR_PROP_INCR_COUNT,count);
            }

            // the Larsether sustains all mortal needs
	    // ... don't want anyone dying in transit
	    // that would be thematically tricky ...
            ob->set_hp(ob->query_max_hp());
            ob->set_mana(ob->query_max_mana());
            ob->set_fatigue(ob->query_max_fatigue());
	}

        if ( way_stage == LARSETHER_ENDINGIDX )
        {
            movelocn = LGELLIRROOM + "larsether_dest";
        }
        else
        {
            way_stage += 1;
            if ( way_stage > LARSETHER_MAXNUMIDX ) way_stage = 0;

            ob->catch_msg( LGELLIR_GET_ETHERMSG(way_stage) );
            ob->add_prop(LGELLIR_LARSETHER_INDEX,way_stage);
            movelocn = sprintf("%s%02d",LARSETHER_FILESTUB,way_stage);

        }

        ob->move_living("M", movelocn, 1, 0);
    }
    else
        ob->remove_object(); // not living
}


void
enter_inv(object ob, object from)
{
    ::enter_inv(ob, from);

    if ( interactive(ob) )
        set_alarm(gSecondsPerStage,0.0,&transfer_to_next(ob,from));
}


int
disfunction_it( string str )
{
    write( LGELLIR_ETHER_INACTION_MESG );
    return 1;
}


void
init()
{
    ::init();

    add_action("disfunction_it","block");
    add_action("disfunction_it","hide");
    add_action("disfunction_it","sneak");
    add_action("disfunction_it","track");
    add_action("disfunction_it","search");
}


