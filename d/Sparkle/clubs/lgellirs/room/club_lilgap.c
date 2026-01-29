
/*
 *  Club Special Function Room for the Gellirs of Lars
 *
 *  Vitwitch 2022
 */

#pragma save_binary
#pragma strict_types

#include <macros.h>
#include <stdproperties.h>
#include <ss_types.h>

#include "../defs.h"

inherit "/std/room";

/* functions */


int
is_lgellirroom()
{
    return 1;
}


public void
hook_smelled(string str)
{
    write("The clean empty air smells of nothing much at all really.\n");
}


void
reset_room()
{
}


public void
create_room()
{
    set_short("on the edge of an abyss");

    set_long(
             "The surrounding land "+
	     "lies only a few heartbeats fall below, "+
	     "but the Litillgap adds its depth to "+
	     "the height of your vantage point. "+
	     "Looking down from the precipice, the place where "+
	     "the abyss pierces the earth is strangely indistinct -- "+
	     "shrouded in shifting mist. The depths beyond are "+
             "hazy with sheer distance. If there is a "+
	     "bottom, it is lost to sight -- lost to the world itself, "+
	     "perhaps. All here is absolutely silent. The birds "+
	     "in the sky make no cry. The trees of the forest, "+
	     "all stand quiet -- every leaf and twig motionless. "+
	     "Footprints lead up to the edge of the abyss.\n");

    add_item(({"footprints","footprint"}),"A number of sets of "+
              "footprints lead from the edge of the forest to the "+
              "edge of the abyss. They overlap "+
	      "in the crumbly soil atop the precipice; clearly left "+
	      "by different folk at different times. Many lead up "+
	      "to the edge, few return downhill. Deeper prints at "+
	      "the edge suggest folk stood there looking at the abyss.\n");

    add_item(({"abyss","the abyss","depths","litillgap",
            "the litillgap","down","depths of the abyss","depths of abyss"}),
           "The depths of the abyss before you, the Litillgap, are lost to "+
           "sight. Like the mysteries beyond the veil of sky above, there lie "+
	   "mysteries beyond the deeps below. You look up... you look down "+
	   "again... you wonder if you should <leap off>.\n");

    add_item(({"land","surrounding land"}),
           "Broad expanses of the lands of Sparkle are laid out before you. "+
           "You can see far into the wilderness that you have trodden in "+ 
	   "your past wandering.\n");

    add_item(({"birds","the birds"}),
           "Dark birds wheel silently in the column of empty air from "+
	   "far below to the sky above.\n");

    add_item(({"sky","air","column of air","column of empty air"}),
           "The sky above is much like that you have seen throughout "+
	   "your life -- entirely familiar and yet you know not what lies "+
	   "beyond it at all. The mystery of what lies beyond the veil of "+
	   "the sky is like the mystery of what lies beyond mortal sight "+
	   "in the abyss below. You sense a curious silent wind about you.\n");

    add_item(({"ether","ether of lars","larsether","curious silent wind",
               "curious wind","silent wind","wind"}),
           "A curious silent wind wafts about you, pulling "+
	   "at your spirit in chill gusts. Nothing in sight seems "+
	   "disturbed by it but you. You recognise it as the Ether of Lars. "+
	   "The curious medium of creation which surrounds the world. "+
	   "You wonder if you have the favour of Lars to be borne by it... "+
	   "should you <leap off>.\n");

    add_item(({"forest","the forest","trees","the trees"}),
           "The trees of the forest, of the Askelund, stand motionless "+
	   "in a phalanx downhill from here.\n");

    // not enough room on the precipice
    // for a steed nor teleport
    add_prop( ROOM_I_NO_ALLOW_STEED, 1 );
    add_prop( ROOM_M_NO_TELEPORT_TO, 1 );
    add_prop( ROOM_I_INSIDE, 0 );

    add_exit( LGELLIRROOM + "club_wandr2", "downhill" );

    reset_room();
}


void
ether_rise( object p )
{

    p->catch_msg("\nIn mid leap, you suddenly find yourself caught in "+
            "the chill updraft of the Larsether! You zoom heaven-wards at "+
	    "an unearthly rate!\n\n");

    tell_room(this_object(),
         QCTNAME(p) + " is caught in a sudden gust out of thin air -- "+
	  "quickly flying upward out of sight.\n",p);

    string movelocn = LGELLIRROOM + "club_gapeth";
    tell_room(movelocn, QCNAME(p) + " is lifted up from below.\n");
    p->move_living("M",movelocn, 1, 0);

    return;
}


void
death_fall( object p )
{

    p->catch_msg("\nYour leap ends after a short distance... just as your "+
                 "long fall into the Litillgap begins.\n\n");
    tell_room(this_object(),
         QCTNAME(p) + " arcs upwards a short way before rapidly "+
	   "plummeting out of sight into the abyss.\n",p);

    string movelocn = LGELLIRROOM + "club_gapfll";
    tell_room(movelocn, QCNAME(p) + " falls from above.\n");
    p->move_living("M",movelocn, 1, 0);

    return;
}


int
leap_it( string str )
{
    if ( !strlen(str) ) return 0;

    if ( !wildmatch("* litillgap*",lower_case(str)) 
              && lower_case(str) != "off" )
    {
        write("Leap where? Leap off? Leap into the Litillgap?\n");
        return 1;
    }

    object p = this_player();

    // check if is a gellir, non-gellirs should not be here
    // but don't want them to die if they somehow get here

    if ( IS_A_LARSGELLIR(p) < 1 )
    {
        p->catch_msg("The urge to <leap off> crosses your mind but your body "+
	             "remains motionless. Apparently it values your mortal "+
		     "existence even if you do not.\n");
        tell_room(this_object(),QCTNAME(p) + " stares into the void "+
	          "with intent but does not otherwise move.\n",p);
        return 1;
    }

    int has_ether_access = LGELLIR_ETHER_ACCESS(p);
    int has_been_warned = p->query_prop(LGELLIR_PROP_LEAP_WARNING);

    string galdrmapname = sprintf("%d_%s",0,p->query_real_name());
    mapping pGALDRmap = restore_map( LGELLIRGALDRAR + galdrmapname ); 
   
    // check if a falling gellir has a <bind>ed galdr, check daemon
    // processing has not been suspended by a Wizard-admin... these
    // safety checks only apply here... gellirs die unwarned elsewhere

    int all_set_to_fall = 1;
    if ( !LGELLIR_PROCESS_ENABLED() || !m_sizeof(pGALDRmap) 
          || pGALDRmap["MDEFINED"] == "0" ) all_set_to_fall = 0;
    
    if ( !has_ether_access && !all_set_to_fall )
    {
        if( !has_been_warned )
        {
	    p->add_prop(LGELLIR_PROP_LEAP_WARNING,1);

            p->catch_msg("\nAs the urge to <leap off> crosses your mind "+
	       "you suddenly you realise you have forgotten to <bind> "+
	       "a Larsgaldr. You wonder if you are so careless "+
	       "as to go to Death so unprepared. If you are indeed "+
	       "that careless, the urge to <leap off> will surely come again.\n");

            return 1;
        }
	else
            p->remove_prop(LGELLIR_PROP_LEAP_WARNING);
    }
    else if ( has_ether_access > 0 ) 
    {
        if( !has_been_warned )
        {
	    p->add_prop(LGELLIR_PROP_LEAP_WARNING,1);

            p->catch_msg("\nAs the urge to <leap off> crosses your mind "+
	       "you feel the chill stirrings of the Larsether gather more "+
	       "strongly about you. "+
	       "You wonder if you are truly prepared to be lifted above "+
	       "the mortal realms so to claim the boon of Lars. If you "+
	       "are indeed prepared, the urge to <leap off> will surely "+
	       "come again shortly.\n");

            return 1;
        }
	else
            p->remove_prop(LGELLIR_PROP_LEAP_WARNING);
    }

    // act of leaping

    p->catch_msg("\nThe urge to <leap off> crosses your mind... " +
               "your body tenses "+
                "and you leap beyond the brink into empty space!\n\n");
    tell_room(this_object(),
        QCTNAME(p) + " suddenly leaps beyond the brink of the "+
	     "abyss into empty space.\n",p);

    // outcomes....

    if ( !has_ether_access )
        set_alarm(1.0,0.0,&death_fall(p));
    else
        set_alarm(1.0,0.0,&ether_rise(p));

    return 1;
}


int
block_it( string str )
{
    write("There are too many ways to block someone from leaving.\n");
    return 1;
}


void 
init()
{
    ::init();
    add_action(leap_it,"leap");
    add_action(block_it,"block");
}

