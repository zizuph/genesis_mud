/*
 *    /d/Gondor/guilds/morgulmage/soul/emotes.c
 *
 *    This file is part of the command soul for the Morgul mages.
 *    The emotes in the soul of the Morgul mages.
 *
 *    Created: Olorin, 06-jan-1994
 *    Copyright (c) 1994, 1995, 1996 by Christian Markus (Olorin)
 *
 *    Modification log:
 *    Mercade 
 *    Morbeche Dec 1999 - Fixed rasp/mrasp and mhiss/hsay
 *    Chmee 11.07.2001  - removed some obsolete things.
 *
 * Feb 8, 2006: Altrus
 *   Added in the source for the 'msay' command, allowing mages
 *   speak in the dialect of the orc and uruk race guilds.
 * 
 * Oct 30, 2006: Toby
 *   Added 'mgrab' and 'mcircle'. Suggestions from Society on
 *   request that they collect ideas to find more ways to
 *   express themselves.
 *
 * Apr 30, 2009: Eowul
 *   Moved to the new guild directory and split into only 
 *   emotes. Other functionality added to their own files.
 */

#define SOULDESC(x) (this_player()->add_prop( LIVE_S_SOULEXTRA, x ))
#define ADV_DUMMY   "ADVERB"

#define HE(x)  (x)->query_pronoun()
#define HIS(x) (x)->query_possessive()
#define HIM(x) (x)->query_objective()
#define TP_HE  (this_player()->query_pronoun())
#define TP_HIS (this_player()->query_possessive())
#define TP_HIM (this_player()->query_objective())


/*
 * ACTIVITY_EMOTIONs, ordered alphabetically
 */
public int
approve( string str )
{
    object *oblist;
    string *how;

    how = parse_adverb_with_space( str, "grimly", 0 );

    if (!strlen( how[0] ))
    {
        notify_fail( "Approve of whom?\n" );
        return 0;
    }

    oblist = parse_this( how[0], "[of] [the] %l" );
    oblist -= ({ this_player() });

    if (!sizeof( oblist ))
    {
        notify_fail( "Approve of whom?\n" );
        return 0;
    }

    actor( "You look"+ how[1]+ " at", oblist, ", showing your dark "+
        "approval." );
    targetbb( " looks"+ how[1]+ " at you, pleased with your services to "+
        "the Dark Lord.", oblist );
    all2actbb( " looks"+ how[1]+ " at", oblist, ", showing "+ TP_HIS+
        " dark approval of services rendered unto the Dark Lord." );
    MORGUL_MASTER->increase_activity( this_player(), ACTIVITY_EMOTION );

    return 1;
}

public int
aware( string str )
{
    int dis;
    object *oblist, *higher_dis, *same_dis, *lower_dis;
    string *how;

    how = parse_adverb_with_space( str, "suddenly", 0 );

    if (!strlen( how[0] ))
    {
        notify_fail( "Become aware of whose presence?\n" );
        return 0;
    }

    oblist = parse_this( how[0], "[of] [the] %l" );
    oblist -= ({ this_player() });

    if (!sizeof( oblist ))
    {
        notify_fail( "Become aware of whose presence?\n" );
        return 0;
    }

    dis = this_player()->query_stat( SS_DIS );
    higher_dis = filter( oblist, &f_higher_dis( , dis) );
    lower_dis = filter( oblist, &f_lower_dis( , dis) );
    same_dis = oblist - higher_dis - lower_dis;

    actor( "You are" + how[1] + " aware of the presence of", oblist, "." );
    if (sizeof( lower_dis ))
    {
        target( " is, to your dismay and terror," + how[1] +
            " aware of your presence!", lower_dis );
        lower_dis->command( "$blanch fearful" );
    }
    if (sizeof( same_dis ))
    {
        targetbb( " is"+ how[1]+ " aware of your presence, much to your "+
            "displeasure.", same_dis );
    }
    all2act( " is"+ how[1]+ " aware of the presence of", oblist, "." );
    if (sizeof( higher_dis ))
    {
        target( " is"+ how[1]+ " aware of you, and you acknoledge " +
            TP_HIS+ " presence sternly.", higher_dis );
        write( capitalize( COMPOSITE_LIVE( higher_dis ) )+
            " acknowledges you sternly.\n" );
        higher_dis->command( "$scowl sternly" );
    }
    MORGUL_MASTER->increase_activity( this_player(), ACTIVITY_EMOTION );
    return 1;
}

public int mbeckon( string str )
{
 object *oblist;
 string *how, temp;

    if (temp = this_player()->query_prop( LIVE_M_MOUTH_BLOCKED ))
    {
        write( stringp( temp ) ? temp :
            "You are gagged and cannot speak.\n" );
        return 1;
    }
    if (!strlen( str ))
    {
        notify_fail( "Beckon to whom?\n" );
        return 0;
    }
    oblist = parse_this( str, "[to] [the] %i" );
    oblist -= ({ this_player() });

    if (!sizeof( oblist ))
    {
        notify_fail( "Beckon to whom?\n" );
        return 0;
    }
    actor( "You beckon to", oblist, ", rasping: Come back... come back... "+
        "to Mordor we will take you!" );
    target( " beckons to you, rasping: Come back... come back... "+
        "to Mordor we will take you!", oblist );
    all2act( " beckons to", oblist, ", rasping: Come back... come back... "+
        "to Mordor we will take you!" );
    MORGUL_MASTER->increase_activity( this_player(), ACTIVITY_EMOTION );
    return 1;
}

public int
mcall( string str )
{
 int so;
 object *oblist;
 string *how, poss;

    if (poss = this_player()->query_prop( LIVE_M_MOUTH_BLOCKED ))
    {
        write( stringp( poss ) ? poss :
            "You are gagged and cannot speak.\n" );
        return 1;
    }
    how = parse_adverb_with_space( str, "softly", 0 );

    if (!strlen( how[0] ))
    {
        how[0] = "all";
    }
    oblist = parse_this( how[0], "[the] %i" );

    if (!(so = sizeof( oblist )))
    {
        notify_fail( "Call whom/what?\n" );
        return 0;
    }

    if (so > 1)
    {
        poss = "their";
    }
    else
    {
        poss = oblist[0]->query_possessive();
    }
    actor( "You call"+ how[1]+ " to", oblist, " in an effort to break "+
        poss+ " will." );
    target( " calls"+ how[1]+ " to you in low hypnotic tones.", oblist );
    all2act( " calls"+ how[1]+ " to", oblist, " in low hypnotic tones." );
    MORGUL_MASTER->increase_activity( this_player(), ACTIVITY_EMOTION );
    return 1;
}

public int curse( string str )
{
 object *oblist;
 string *how, temp;

    if (temp = this_player()->query_prop( LIVE_M_MOUTH_BLOCKED ))
    {
        write( stringp( temp ) ? temp :
            "You are gagged and cannot speak.\n" );
        return 1;
    }
    how = parse_adverb_with_space( str, "violently", 0 );
    SOULDESC( "cursing" + how[1] );

    if (!strlen( how[0] ))
    {
        write( "You curse"+ how[1]+ " such open defiance of the Dark "+
            "Lord.\n" );
        all( " curses" + how[1]+ " such open defiance of the Dark Lord." );
        return 1;
    }

    oblist = parse_this( how[0], "[at] [the] %i" );
    oblist -= ({ this_player() });

    if (!sizeof( oblist ))
    {
        notify_fail( capitalize( query_verb() )+ " at whom/what?\n" );
        return 0;
    }

    target( " curses you"+ how[1]+ " for defying the Dark "+ "Lord's will.",
        oblist );
    actor( "You curse", oblist, how[1]+ " for defying the Dark Lord's "+
        "will." );
    all2act( " curses", oblist, how[1]+ " for defying the Dark Lord's "+
        "will." );
    MORGUL_MASTER->increase_activity( this_player(), ACTIVITY_EMOTION );
    return 1;
}

public int damn( string str )
{
 string temp;
 object *oblist;

    if (temp = this_player()->query_prop( LIVE_M_MOUTH_BLOCKED ))
    {
        write( stringp( temp ) ? temp :
            "You are gagged and cannot speak.\n" );
        return 1;
    }
    if (!strlen( str ))
    {
        notify_fail( capitalize( query_verb() )+ " whom?\n" );
        return 0;
    }

    oblist = parse_this( str, "[the] %i" );
    oblist -= ({ this_player() });

    if (!sizeof( oblist ))
    {
        notify_fail( capitalize( query_verb())+ " whom/what?\n" );
        return 0;
    }

    target( " raises "+ TP_HIS+ " hand and damns you to burn in the dungeons "+
        "of Barad-Dur.", oblist );
    actor( "Calling to the Dark Lord you damn", oblist,
        " to eternal pain in the dungeons of Barad-Dur." );
    all2act( " damns", oblist, " to horrible suffering in the dungeons "+
        "of Barad-Dur." );
    MORGUL_MASTER->increase_activity( this_player(), ACTIVITY_EMOTION );
    return 1;
}

public int exalt( string str )
{
 int s;
 object *all, *good, *evil;
 string *how, temp;

    if (temp = this_player()->query_prop( LIVE_M_MOUTH_BLOCKED ))
    {
        write( stringp( temp ) ? temp :
            "You are gagged and cannot shout.\n" );
        return 1;
    }
    how = parse_adverb_with_space( str, "exuberantly", 0 );

    if (strlen( how[0] ))
    {
        notify_fail( "What do you want to exalt?\n" );
        return 0;
    }

    all = FILTER_LIVE( all_inventory( environment( this_player() ) ) );
    all -= ({ this_player() });
    good = filter( all, good_align );
    evil = all - good;
    write( "You exalt"+ how[1]+ " the power of the Dark Lord.\n" );
    if (sizeof( evil ))
    {
        target( " throws "+ TP_HIS+ " head back and raises "+ TP_HIS+
            " arms, exalting"+ how[1]+ " the name of Melkor.", evil );
    }
    if (s = sizeof( good ))
    {
        target( " throws "+ TP_HIS+ " head back and raises "+ TP_HIS+ " arms, "+
            "exalting"+ how[1]+ " the name of Morgoth.\nYou are forced to "+
            "look away.", good );
        good = FILTER_CAN_SEE( good, this_player() );
        if (sizeof( good ) > 0)
        {
            write( capitalize( COMPOSITE_LIVE( good ) )+ " avert"+
                (s == 1 ? "s "+ good[0]->query_possessive() : " their")+
                  " eyes.\n" );
        }
    }
    MORGUL_MASTER->increase_activity( this_player(), ACTIVITY_EMOTION );
    return 1;
}

/*
 * Suggested by Chmee, coded by Olorin, 29-may-1995
 */
public int fog( string str )
{
 string temp;
 object *oblist = ({}),
 tp = this_player();

    if (temp = this_player()->query_prop( LIVE_M_MOUTH_BLOCKED ))
    {
        write( stringp( temp ) ? temp :
            "You are gagged and cannot chant.\n" );
        return 1;
    }
    if (tp->query_prop( "Morgul_fog_cast" ))
    {
        notify_fail( "You cannot conjure another ball of fog right "+
            "now.\n" );
        return 0;
    }

    if (strlen( str ))
    {
        oblist = parse_this( str, "[at] [the] %l" );
        oblist -= ({ tp });
        oblist = FILTER_CAN_SEE( oblist, tp );
    }

    if (!sizeof( oblist ))
    {
        set_alarm( 5.0, 0.0, "delay_fog", tp );
    }
    else if (sizeof( oblist ) == 1)
    {
        set_alarm( 5.0, 0.0, "delay_fog", tp, oblist );
    }
    else
    {
        notify_fail( "You cannot cast fog at more than one person at "+
            "a time!" );
        return 0;
    }

    tp->add_prop( "Morgul_fog_cast", 1 );
    write( "You chant the words \"tulo mith morn\" and conjure a ball of "+
        "black fog in your hand.\n" );
    all( " begins a hissing chant and a ball of black fog appears in "+
        TP_HIS + " hand." );
    MORGUL_MASTER->increase_activity( this_player(), ACTIVITY_EMOTION );
    return 1;
}

varargs void delay_fog( object tp, object *target = ({}) )
{
 object *livings, room;

    tp->remove_prop( "Morgul_fog_cast" );

    if (!objectp( tp ) || !objectp( room = environment( tp ) ))
    {
        return;
    }
    livings = FILTER_LIVE( all_inventory( room ) );

                                /*target[0] not in this room anymore!     */
    if (sizeof( target ) && member_array( target[0], livings ) == -1)
    {
        target = ({});
    }
    if (sizeof( target ))
    {
        livings -= target;

        tp->catch_msg( "With a slight movement of your hand, you throw "+
            "the ball of fog into the direction of "+ QTNAME(target[0])+
            ".\n" );
        tell_room( room, "You feel your hair rising as the fog slowly "+
            "blows into your direction while it disperses.\n", livings );
        tell_room( room, "You feel your hair rising as the fog slowly "+
            "blows into the direction of "+ QTNAME(target[0])+ ".\n",
            ({ tp }) + target );
        if (target[0]->query_stat( SS_CON ) < random( 100 ))
        {
            target[0]->command( "$puke" );
        }
    }
    else
    {
        tell_room( room, "You feel your hair rising as the fog slowly "+
            "blows around while it disperses.\n", tp );
        tp->catch_msg( "With a slight movement of your hand, you let the "+
            "ball of fog disperse.\n" );
    }
}

public int gaze( string str )
{
 object *oblist;
 string *how, target_str, actor_str, all2act_str;

    how = parse_adverb_with_space( str, "intimidatingly", 0 );

    if (!strlen( how[0] ))
    {
        write( "You gaze"+ how[1] +" at your surroundings, looking for "+
            "a victim.\n" );
        allbb( " gazes"+ how[1]+ " at "+ TP_HIS+ " surroundings, looking "+
            "for a victim." );
        MORGUL_MASTER->increase_activity( this_player(), ACTIVITY_EMOTION );
        return 1;
    }

    oblist = parse_this( how[0], "[at] [the] %l" );
    oblist -= ({ this_player() });

    if (sizeof( oblist ) != 1)
    {
        notify_fail( capitalize( query_verb() )+ " at whom?\n" );
        return 0;
    }

    target_str = " gazes"+ how[1]+ " at you.\n";
    actor_str = ".\n";

    if (oblist[0]->query_alignment() < 0)
    {
        if (F_DARE_ATTACK( oblist[0], this_player() ))
        {
            target_str += "You feel great respect for "+ TP_HIM+ ".";
            actor_str += capitalize( HE( oblist[0] ) )+ " returns the "+
                "look respectfully.";
            all2act_str = QCTNAME( oblist[0] )+ " returns the look "+
                "respectfully.";
        }
        else
        {
            target_str += "You feel overwhelmed by "+ TP_HIS+ " powerful "+
                "presence and kneel in front of "+ TP_HIM+ ".";
            actor_str += "Under your gaze, "+ HE( oblist[0] )+ " kneels "+
                "down in front of you.";
            all2act_str = QCTNAME( oblist[0] )+ " is overwhelmed by "+
                QTNAME( this_player() )+ "'s powerful presence and kneels "+
                "in front of "+ TP_HIM+ ".";
        }
    }
    else
    {
        if (F_DARE_ATTACK( oblist[0], this_player()) )
        {
            target_str += "You feel tainted by that gaze.";
            actor_str += capitalize( HE( oblist[0] ) )+ " looks like "+
                HE( oblist[0] )+ " did not like that gaze.";
            all2act_str = QCTNAME( oblist[0] )+ " looks like "+
                HE( oblist[0] )+ " did not like "+ QTNAME( this_player() )+
                "'s gaze.";
        }
        else
        {
            target_str += "You tremble with fear, and your face turns "+
                "white.";
            oblist[0]->add_prop( LIVE_S_SOULEXTRA, "trembling with fear" );
            actor_str += capitalize( HE( oblist[0] ) )+ " trembles with "+
                "fear, and "+ HIS( oblist[0] )+ " face turns white.";
            all2act_str = QCTNAME( oblist[0] )+ " trembles with fear, and "+
                HIS( oblist[0] )+ " face turns white.";
        }
    }

    targetbb( target_str, oblist );
    actor( "You gaze"+ how[1]+ " at", oblist, actor_str );
    tell_room( environment( this_player() ), QCTNAME( this_player() )+
        " gazes"+ how[1]+ " at "+ QNAME( oblist[0] )+".\n"+ all2act_str+
        "\n", ({this_player(),oblist[0]}) );
    MORGUL_MASTER->increase_activity( this_player(), ACTIVITY_EMOTION );
    return 1;
}

public int hail( string str )
{
 string temp;
 int level, olevel;
 object *oblist, *non, *higher, *lower, *mem, *wiz;

    if (temp = this_player()->query_prop( LIVE_M_MOUTH_BLOCKED ))
    {
        write( stringp( temp ) ? temp :
            "You are gagged and cannot speak.\n" );
        return 1;
    }
    if (!strlen( str ))
    {
        write( "You hail everybody in the name of Melkor.\n" );
        all( " gazes around threateningly, hissing: Hail Melkor!" );
        MORGUL_MASTER->increase_activity( this_player(), ACTIVITY_EMOTION );
        return 1;
    }
    oblist = parse_this( str, "[the] %l" );
    oblist -= ({ this_player() });

    if (!sizeof( oblist ))
    {
        notify_fail( "Hail who?\n" );
        return 0;
    }
    mem = filter( oblist, member_filter );
    mem += filter( oblist - mem, special_wizard_filter );
    non = oblist - mem;

    if (sizeof( non ))
    {
        actor( "You hail", non, " in the name of Melkor." );
        target( " glares at you haughtily, hissing: Hail Melkor!", non );
        all2act( " glares at", non, " haughtily, hissing: Hail Melkor!" );
    }
    if (sizeof( mem ) > 1)
    {
        higher = filter( mem, higher_rank );
        lower = mem - higher;
        
        if (sizeof( higher ))
        {
            actor( "You hail", higher, " in the name of Melkor." );
            target( " cowers submissively before you, hissing: Hail "+
                "Melkor!", higher );
            all2act( " cowers submissively before", higher, " hissing: "+
                "Hail Melkor!" );
        }
    if (sizeof( lower ))
    {
        actor( "You hail", lower, " in the name of Melkor." );
        target( " greets you with mild contempt, hissing: Hail Melkor!",
            lower );
        all2act( " greets", lower, " with mild contempt, hissing: Hail "+
            "Melkor!" );
        }
    }
    else if (sizeof( mem ))
    {
        level  = this_player()->query_morgul_level( -1 );
        olevel = mem[0]->query_morgul_level( -1 );

        if(special_wizard_filter(mem[0]))
            olevel = 100;
        if(special_wizard_filter(this_player()))
            level = 100;

        if (olevel < (level/2))
        {
            actor( "You hail", mem, " condescendingly in the name of "+
                "Melkor." );
            target( " deigns condescendingly to notice you, hissing: Hail "+
                "Melkor!", mem );
            all2act( " deigns condescendingly to notice", mem,
                ", hissing: Hail Melkor!" );
        }
        else if (olevel < (level-1))
        {
            actor( "You hail", mem, " in the name of Melkor with mild "+
                "annoyance.");
            target( " greets you with mild annoyance, hissing: Hail "+
                "Melkor!", mem );
            all2act( " greets", mem, " with mild annoyance, hissing: Hail "+
                "Melkor!" );
        }
        else if (olevel < (level+2))
        {
            actor( "You hail", mem, " in the name of Melkor." );
            target( " greets you, hissing: Hail Melkor!", mem );
            all2act( " greets", mem, ", hissing: Hail Melkor!" );
        }
        else if (olevel < (3*level/2))
        {
            actor( "You hail", mem, " subserviently in the name of "+
                "Melkor." );
            target( " greets you with subservience, hissing: Hail Melkor!",
                mem );
            all2act( " greets", mem, " with subservience, hissing: Hail "+
                "Melkor!" );
        }
        else
        {
            actor( "You prostrate yourself before", mem, "." );
            target( " prostrates "+ TP_HIM+ "self before you, hissing: "+
                "Hail Melkor!", mem );
            all2act( " prostrates "+ TP_HIM+ "self before", mem,
                " hissing: Hail Melkor!" );
        }
    }
    
    mem->hook_morgul_hail(this_player());
    non->hook_morgul_hail(this_player());
    
    MORGUL_MASTER->increase_activity( this_player(), ACTIVITY_EMOTION );
    return 1;
}

/*
 *    marm [<adverb>] [<target>]
 *
 *    Idea by Toby and Denbarra.
 *    Coded by Olorin, 28-Oct-1996
 */
public int marm( string str )
{
 object *oblist, *all, *undead, *prot, *watch, tp = this_player();
 string  pow, *how, pron, text1, text2, text3, react;

    how = parse_adverb_with_space( str, "menacingly", 0 );

    switch ( tp->query_morgul_level() )
    {
    case  0..12:
        pow = "a great deal";
        break;
    case 13..24:
        pow = "some";
        break;
    default:     
    case 25..99: 
        pow = "a little";
        break;
    }
    if (!strlen( how[0] ))
    {
        write( "You raise your arm"+ how[1]+ " and put forth "+ pow+
            " of your power.\nA chill begins to grow and take hold around "+
            "you, reminding you of Mordor.\n" );
        allbb( " raises "+ TP_HIS+ " arm"+ how[1]+ "." );
        all = FILTER_LIVE( all_inventory( environment( tp ) ) ) - ({ tp });
        if (sizeof( all ))
        {
            undead = filter( all, &->query_prop( LIVE_I_UNDEAD ));
            all -= undead;
            if (sizeof( all ))
            {
                prot = filter( all, &->query_magic_res( MAGIC_I_RES_COLD ));
                all -= prot;
            }
        }
        if (sizeof( all ))
        {
            all->catch_msg( "Suddenly a sharp chill grows and takes hold "+
                "around you, causing your skin to recede and bumps to "+
                "rise along your limbs.\n" );
        }
        if (sizeof( undead ))
        {
            undead->catch_msg( "Suddenly a sharp chill grows and takes "+
                "hold around you, chilling you comfortably.\n" );
        }
        if (sizeof( prot ))
        {
            prot->catch_msg( "Suddenly a sharp chill grows and takes hold "+
                "around you, not affecting you in the slightest.\n" );
        }
        MORGUL_MASTER->increase_activity( this_player(), ACTIVITY_EMOTION );
        return 1;
    }

    oblist = parse_this( how[0], "[at] [the] %l" );
    if (!sizeof( oblist ))
    {
        notify_fail( "Raise your arm at whom?\n" );
        return 0;
    }
    else if (sizeof( oblist ) > 1)
    {
        pron = "them";
    }
    else
    {
        pron = HIM( oblist[0] );
    }
    all = oblist;
    undead = filter( all, &->query_prop( LIVE_I_UNDEAD ) );
    all -= undead;
    if (sizeof( all ))
    {
        prot = filter( all, &->query_magic_res( MAGIC_I_RES_COLD ) );
        all -= prot;
    }
    actor( "You raise you arm"+ how[1]+ " and put forth "+ pow+
        " of your power about", oblist, "." );
    targetbb( " raises "+ TP_HIS+ " arm"+ how[1]+ " toward you.", oblist );
    all2actbb( " raises "+ TP_HIS+ " arm"+ how[1]+ " toward", oblist, "." );

    text1 = "A chill envelops "+ pron+ ", causing "+ pron;
    text2 = "Suddenly the air around you is very, very cold, causing your "+
        "breath to condense and causing you ";
    text3 = "You feel a slight chill, swirl about the room";

    watch = FILTER_CAN_SEE_IN_ROOM( all_inventory( environment( tp ) )-
        ({ tp }) - oblist );
    if (sizeof( all ))
    {
        write( text1+ " to shiver.\n" );
        all->catch_msg( text2+ "to shiver.\n" );
        watch->catch_msg( text3+ ".\n" );
        all->command( "$shiver" );
    }
    if (sizeof( undead ))
    {
        write( text1+ " to smile slightly.\n" );
        undead->catch_msg( text2+ "to smile slightly.\n" );
        watch->catch_msg( text3+ ".\n" );
        undead->command( "$smile slight*" );
    }
    if (sizeof( prot ))
    {
        write( text1+ " no discomfort.\n" );
        prot->catch_msg( text2+ "no discomfort.\n" );
        watch->catch_msg( text3+ ".\n" );
    }
    MORGUL_MASTER->increase_activity( this_player(), ACTIVITY_EMOTION );
    return 1;
}

/*
 * Function name: mdismiss
 * Description:   Aug 25 1997 Locklear
 *                Dismiss someone. Full mages only.
 * Argument:      string str - command line argument
 * Returns:       1/0
 */
public int mdismiss( string str )
{
 object *oblist;
 string *how;

    how = parse_adverb_with_space( str, "absentmindedly", 0 );

    if (this_player()->query_morgul_level() <= APPRENTICE_LEVEL)
    {
        return 0;
    }
    if (!strlen( how[0] ))
    {
        str = "all";
    }
    oblist = parse_this( how[0], "[the] %l" );

    if (sizeof( oblist ) != 1)
    {
        notify_fail( "Dismiss whom?\n" );
        return 0;
    }

    actor( "You dismiss", oblist, how[1]+" with a wave of your hand." );
    targetbb( " dismisses you"+ how[1]+ " with a wave of "+ TP_HIS+
        " hand.", oblist );
    all2actbb( " dismisses", oblist, how[1]+ " with a wave of "+ TP_HIS+
        " hand." );
    MORGUL_MASTER->increase_activity( this_player(), ACTIVITY_EMOTION );
    return 1;
}

public int mgaze( string str )
{
 object *oblist;

    if (this_player()->query_morgul_level() <= APPRENTICE_LEVEL)
    {
        return 0;
    }
    if (!strlen( str ))
    {
        str = "all";
    }
    oblist = parse_this( str, "[at] [the] %l" );
    oblist -= ({ this_player() });

    if (sizeof( oblist ) != 1)
    {
        notify_fail( "Gaze at whom?\n" );
        return 0;
    }

    actor( "Through force of will, you hold", oblist, "'s gaze, "+
        "searching for any signs of weakness." );
    targetbb( " holds you with "+ TP_HIS+ " gaze through the force of "+
        TP_HIS+ " will, searching your soul for any signs of weakness.",
        oblist );
    tell_room( environment( this_player() ), QCTNAME( oblist[0] )+
        " suddenly stiffens after a brief struggle as "+
        QTNAME( this_player() )+ " forces "+ TP_HIS+ " will upon "+
           HIM( oblist[0] ) + ".\n", ({ this_player() }) + oblist );

    if ((oblist[0]->query_alignment() < MORGUL_I_ALIGN_JOIN) ||
        (oblist[0]->query_guild_name_occ() == GUILD_NAME))
    {
        write(oblist[0]->query_The_name( this_player() )+ " looks at you "+
            "respectfully.\n" );
        oblist[0]->catch_msg( "You look at "+ QTNAME( this_player() )+
            " with new respect.\n" );
        tell_room( environment( this_player() ), QCTNAME( oblist[0] )+
            " looks at "+ QTNAME( this_player() )+ " respectfully.\n",
            ({ this_player() }) + oblist );
    }
    else
    {
        write(oblist[0]->query_The_name( this_player() )+ " looks at you "+
            "fearfully.\n" );
        oblist[0]->catch_msg( "You look at "+ QTNAME( this_player() )+
            " with renewed terror.\n" );
        tell_room( environment( this_player() ), QCTNAME( oblist[0] )+
            " looks at "+ QTNAME( this_player() )+ " fearfully.\n",
            ({ this_player() }) + oblist );
    }
    MORGUL_MASTER->increase_activity( this_player(), ACTIVITY_EMOTION );
    return 1;
}

public int mglare( string str )
{
 object *oblist;

    if (!strlen( str ))
    {
        str = "all";
    }
    oblist = parse_this( str, "[at] [the] %i" );
    oblist -= ({ this_player() });

    if (!sizeof( oblist ))
    {
        notify_fail( "Glare at whom/what?\n" );
        return 0;
    }

    actor( "You glare at", oblist, " in fury." );
    targetbb( " glares at you, "+ TP_HIS+ " face contorted with fury.",
        oblist );
    all2actbb( " glares at", oblist, ", "+ TP_HIS+ " face contorted with "+
        "fury." );
    MORGUL_MASTER->increase_activity( this_player(), ACTIVITY_EMOTION );
    return 1;
}

/*
 *    mgrab <target>
 *
 *    Coded by Toby, 30-Oct-2006
 */
public int mgrab( string str )
{
    object *oblist, *watch, tp = this_player();
    string str_extraa = ".", str_extrat = ".", str_extraw = ".", face;

    if (tp->query_morgul_level() <= APPRENTICE_LEVEL)
    {
        return 0;
    }

    oblist = parse_this( str, "[the] %l" );
    oblist -= ({ tp });

    if (!sizeof( oblist ))
    {
        notify_fail( "Grab whom?\n" );
        return 0;
    }

    if (!(oblist[0]->query_prop( LIVE_I_UNDEAD )))
    {
        str_extraa = ". Dark pleasure surges through the core of your " +
                     "undead body as the power your being radiates " +
                     "causes " +oblist[0]->query_the_name(tp);
        str_extrat = ". The grip is that of cold steel and the chill of " +
                     "death seeping out from " +tp->query_the_name(oblist[0])+
                     "'s being ";
        str_extraw = ". ";

       if (oblist[0]->query_magic_res( MAGIC_I_RES_COLD ))
       {
           str_extraa += " slight discomfort in your iron grip.";
           str_extrat += " sends slight shivers down your spine.";
           str_extraw += HE_SHE(oblist[0])+ " shivers slightly " +
                         "in the iron grip.";
       }
       else
       {
           str_extraa += " obvious discomfort in your iron grip.";
           str_extrat += " sends violent shivers down your spine.";
           str_extraw += CAP(HE_SHE(oblist[0]))+ " shivers violently " +
                      "in the death grip.";
       }
    }
    if(tp->query_hooded())
       face = "hooded face";
    else
       face = "face";
        
    actor( "With a swift move you reach out and grab", oblist, "'s throat, " +
           "drawing " + HIM_HER(oblist[0]) + " close to your " +face + str_extraa  );
    target(" reaches out, with a swift move, and grabs a hold of your throat, drawing " +
           "you close to " +HIS_HER(tp)+ " " +face+ " and burning eyes" +str_extrat, oblist );
    all2actbb( " reaches out, with a swift move, and grabs a hold of", oblist, "'s throat, " +
               "drawing " +HIM_HER(oblist[0])+ " close to " +HIS_HER(tp)+ " " +face+ 
               " and burning eyes" +str_extraw);

    MORGUL_MASTER->increase_activity( this_player(), ACTIVITY_EMOTION );
    return 1;
}

// This is to hiss at someone or something
public int hiss_emote( string str )
{
 object *oblist;
 string *how, temp;

    if (temp = this_player()->query_prop( LIVE_M_MOUTH_BLOCKED ))
    {
        write( stringp( temp ) ? temp :
            "You are gagged and cannot hiss.\n" );
        return 1;
    }
    how = parse_adverb_with_space( str, "dangerously", 0 );
    SOULDESC( "hissing" + how[1] );

    if (!strlen( how[0] ))
    {
        write( "You hiss"+ how[1]+ ".\n" );
        all( " hisses"+ how[1]+ "." );
        MORGUL_MASTER->increase_activity( this_player(), ACTIVITY_EMOTION );
        return 1;
    }

    oblist = parse_this( how[0], "[at] [the] %i" );    
    oblist -= ({ this_player() });

    if (sizeof( oblist ) == 1)
    {
        target( " hisses"+ how[1]+ " at you.", oblist );
        actor( "You hiss"+ how[1]+ " at", oblist, "." );
        all2act( " hisses"+ how[1]+ " at", oblist, "." );
        MORGUL_MASTER->increase_activity( this_player(), ACTIVITY_EMOTION );
        return 1;
    }

    if (sizeof( oblist ) > 1)
    {
        notify_fail( "You should only hiss at one thing.\n" );
        return 0;
    }

    notify_fail( "Hiss at whom or what?\n" );
    if (!parse_command( how[0], environment( this_player() ),
        " 'at' [the] %i ", oblist ))
    {
        return 0;
    }
}

/*
 * Function name: mhood
 * Description  : Suggestion by Toby
 */
public int mhood( string str )
{
 object *oblist;
 string *how, extra = "";

    if (!this_player()->query_hooded())
    {
        notify_fail( "You are not wearing a hood.\n" );
        return 0;
    }
    how = parse_adverb_with_space( str, "restlessly", 0 );
    oblist = parse_this( how[0], "[at] [the] %i" );
    if (!sizeof( oblist ))
    {
        write( "You move"+ how[1]+ " under your hood.\n" );
        allbb( " moves"+ how[1]+ " under "+ TP_HIS+ " hood." );
        MORGUL_MASTER->increase_activity( this_player(), ACTIVITY_EMOTION );
        return 1;
    }

    // Have all of them look with piercing eyes, until we can 
    // come up with something better: 
    //    if (this_player()->query_morgul_level() <= APPRENTICE_LEVEL)
    extra = " with piercing eyes";

    actor( "You move"+ how[1]+ " under your hood, looking at", oblist,
        extra+ "." );
    targetbb( " moves"+ how[1]+ " under "+ TP_HIS+ " hood, looking at you"+
        extra+ ".", oblist );
    all2actbb( " moves"+ how[1]+ " under "+ TP_HIS+ " hood, looking at",
        oblist, extra + "." );
    MORGUL_MASTER->increase_activity( this_player(), ACTIVITY_EMOTION );
    return 1;
}

public int leer( string str )
{
 object *oblist;
 string text, *how;

    how = parse_adverb_with_space( str, "creepily", 0 );
    text = " with the unholy light of corruption in ";

    if (!strlen( how[0] ))
    {
        write( "You leer"+ how[1]+ text+ "your eyes.\n" );
        allbb( " leers"+ how[1]+ text+ TP_HIS+ " eyes." );
        MORGUL_MASTER->increase_activity( this_player(), ACTIVITY_EMOTION );
        return 1;
    }
    oblist = parse_this( how[0], "[at] [the] %i" );
    oblist -= ({ this_player() });
    if (!sizeof( oblist ))
    {
        notify_fail( "Leer at whom/what?\n" );
        return 0;
    }

    targetbb( " leers"+ how[1]+ " at you"+ text+ TP_HIS+ " eyes.", oblist );
    actor( "You leer"+ how[1]+ " at", oblist, text+ "your eyes." );
    all2actbb( " leers"+ how[1]+ " at", oblist, text+ TP_HIS+ " eyes." );
    MORGUL_MASTER->increase_activity( this_player(), ACTIVITY_EMOTION );
    return 1;
}

/*
 * minspect - Louie inspects a <item> with piercing eyes,
 *            rasping silently. (perhaps could also appraise).
 *
 * Idea by Louie, 12-Oct-1996
 * Coded by Olorin, 12-Oct-1996
 */
public int minspect( string str )
{
 object *oblist = ({}), *items, tp = this_player();
 string  item_str;

    if (!strlen( str ))
    {
        notify_fail( "Inspect what?\n" );
        return 0;
    }
    str = lower_case( str );
    if (parse_command( str, environment( tp ), "%i", items ))
    {
        items = NORMAL_ACCESS( items, 0, 0 );
        items = FILTER_DEAD( items );

        if (!sizeof( items ))
        {
            notify_fail( "Inspect what?\n" );
            return 0;
        }
        item_str = COMPOSITE_DEAD( items );
    }
    else
    {
        notify_fail( "Inspect what?\n" );
        return 0;
    }
    write( "You inspect "+ item_str+ " closely.\n" );
    items->appraise_object();
    allbb( " inspects "+ item_str+ " with piercing eyes." );
    MORGUL_MASTER->increase_activity( tp, ACTIVITY_EMOTION );
    return 1;
}

public int mlook( string str )
{
 object *oblist;
 string *how;

    how = parse_adverb_with_space( str, "grimly", 0 );
    if (!strlen( how[0] ))
    {
        how[0] = "all";
    }
    oblist = parse_this( how[0], "[at] [the] %i" );
    if (!sizeof( oblist ))
    {
        notify_fail( "Look at whom/what?\n" );
        return 0;
    }
    actor( "You look"+ how[1]+ " at", oblist, "." );
    if (!this_player()->query_hooded())
    {
        targetbb( " looks"+ how[1]+ " at you, "+ TP_HIS+
            " eyes but burning red coals.", oblist );
        all2actbb( " looks"+ how[1]+ " at", oblist, " "+ TP_HIS+
            " eyes but burning red coals." );
        MORGUL_MASTER->increase_activity( this_player(), ACTIVITY_EMOTION );
        return 1;
    }
    targetbb( " looks"+ how[1]+ " at you, "+ TP_HIS+
        " eyes but burning red coals beneath "+ TP_HIS+ " hood.", oblist );
    all2actbb( " looks"+ how[1]+ " at", oblist, " "+ TP_HIS+
        " eyes but burning red coals beneath "+ TP_HIS+ " hood." );
    MORGUL_MASTER->increase_activity( this_player(), ACTIVITY_EMOTION );
    return 1;
}

public int loom( string str )
{
 object *oblist;
 string *how, poss;

    how = parse_adverb_with_space( str, "threateningly", 0 );
    if (!strlen( how[0] ))
    {
        how[0] = "all";
    }
    oblist = parse_this( how[0], "[over] [the] %l" );
    oblist -= ({ this_player() });
    if (!sizeof( oblist ))
    {
        notify_fail( "Loom over whom?\n" );
        return 0;
    }

    if (sizeof( oblist ) > 1)
    {
        poss = "their";
    }
    else
    {
        poss = HIS( oblist[0] );
    }
    targetbb( " looms"+ how[1]+ " over you like a vulture in anticipation "+
        "of your death.", oblist );
    actor( "You loom"+ how[1]+ " over", oblist, " in anticipation of "+
        poss+ " death." );
    all2actbb( " looms"+ how[1]+ " over", oblist, " in anticipation of "+
        poss+ " death." );
    MORGUL_MASTER->increase_activity( this_player(), ACTIVITY_EMOTION );
    return 1;
}

public int mage_remember( string str )
{
 string *how;

    how = parse_adverb_with_space( str, "gingerly", 0 );
    if (strlen( how[0] ))
    {
        notify_fail( "What do you want to remember?\n" );
        return 0;
    }
    write( "You"+ how[1]+ " rub a spot on your chest, remembering the day "+
        "when you sacrificed your old being and entered the service of "+
        "the Dark Lord.\n" );
    allbb( how[1]+ " rubs a spot on "+ TP_HIS+ " chest, remembering "+
        "the day when\n"+ TP_HE+ " sacrificed "+ TP_HIS+ " old being and "+
        "entered the service of the Dark Lord." );
    MORGUL_MASTER->increase_activity( this_player(), ACTIVITY_EMOTION );
    return 1;
}

public int mage_scoff( string str )
{
 object *oblist;
 string *how, temp;

    if (temp = this_player()->query_prop( LIVE_M_MOUTH_BLOCKED ))
    {
        write( stringp( temp ) ? temp :
            "You are gagged and cannot scoff.\n" );
        return 1;
    }
    how = parse_adverb_with_space( str, "scornfully", 0 );
    SOULDESC( "scoffing"+ how[1] );

    if (!strlen( how[0] ))
    {
        write( "You scoff"+ how[1]+ ", knowing that you cannot "+
            "be defeated.\n" );
        all( " scoffs"+ how[1]+ ", knowing that "+ TP_HE+
            " cannot be defeated." );
        MORGUL_MASTER->increase_activity( this_player(), ACTIVITY_EMOTION );
        return 1;
    }

    oblist = parse_this( how[0], "[at] [the] %i" );
    oblist -= ({ this_player() });
    if (!sizeof( oblist ))
    {
        notify_fail( "Scoff at whom/what?\n" );
        return 0;
    }

    target( " scoffs"+ how[1]+ " at you, viewing you as no threat.",
        oblist );
    actor( "You scoff"+ how[1]+ " at", oblist, ", viewing "+ (sizeof(
        oblist ) > 1 ? "them" : HIM( oblist[0]) )+ " as no threat." );
    all2act( " scoffs"+ how[1]+ " at", oblist, ", viewing "+ (sizeof(
        oblist ) > 1 ? "them" : HIM( oblist[0] ))+ " as no threat." );
    MORGUL_MASTER->increase_activity( this_player(), ACTIVITY_EMOTION );
    return 1;
}

public int mage_smile( string str )
{
 object *oblist;
 string *how;

    how = parse_adverb_with_space( str, "coldly", 0 );
    SOULDESC( "smiling" + how[1] );

    if (!strlen( how[0] ))
    {
        write( "You smile"+ how[1]+ ", secure in the knowledge that "+
            "the power of the Dark Lord protects you.\n" );
        allbb( " smiles"+ how[1]+ ", the power of the Dark Lord apparent "+
            "in "+ TP_HIS+ " eyes." );
        MORGUL_MASTER->increase_activity( this_player(), ACTIVITY_EMOTION );
        return 1;
    }

    oblist = parse_this( how[0], "[at] [the] %i" );
    oblist -= ({ this_player() });

    if (!sizeof( oblist ))
    {
        notify_fail( capitalize( query_verb() )+ " at whom/what?\n" );
        return 0;
    }
    targetbb( " smiles"+ how[1]+ " at you, and you can see the power of "+
        "the Dark Lord in "+ TP_HIS+ " eyes.", oblist );
    actor( "You smile"+ how[1]+ " at", oblist, ", feeling the power of "+
        "the Dark Lord flowing through your undead body." );
    all2actbb( " smiles"+ how[1]+ " at", oblist, ", the power of "+
        "the Dark Lord apparent in "+ TP_HIS+ " eyes." );
    MORGUL_MASTER->increase_activity( this_player(), ACTIVITY_EMOTION );
    return 1;
}

public int mamuse( string str )
{
    if (this_player()->query_morgul_level() <= APPRENTICE_LEVEL)
    {
        return 0;
    }
    if (strlen( str ))
    {
        notify_fail( "Just show your amusement. It's really that simple!\n" );
        return 0;
    }

    write( "Your eyes flicker like brightly glowing embers, betraying "+
        "your dark amusement.\n" );
    allbb( "'s eyes flicker with dark amusement like brightly glowing "+
        "embers." );
    MORGUL_MASTER->increase_activity( this_player(), ACTIVITY_EMOTION );
    return 1;
}

public int manger( string str )
{
 int rank, i;
 object *oblist, *higher, *lower = ({});
 string *how, temp;

    if (temp = this_player()->query_prop( LIVE_M_MOUTH_BLOCKED ))
    {
        write( stringp( temp ) ? temp :
            "You are gagged and cannot curse.\n" );
        return 1;
    }
    how = parse_adverb_with_space( str, "angrily", 0 );
    SOULDESC( "cursing"+ how[1] );

    if (!strlen( how[0] ))
    {
        how[0] = "all";
    }
    oblist = parse_this( how[0], "[at] [the] %l" );
    oblist -= ({ this_player() });

    if (!sizeof( oblist ))
    {
        notify_fail( "Curse whom?\n" );
        return 0;
    }

    actor( "You curse", oblist, how[1]+ " for being an incompetent fool." );
    target( " curses you"+ how[1]+ " for being an incompetent fool.",
        oblist );
    all2act( " curses", oblist, how[1]+ " for being an incompetent fool." );
    MORGUL_MASTER->increase_activity( this_player(), ACTIVITY_EMOTION );
    higher = filter( oblist, higher_rank );
    oblist -= higher;

    if (!(i = sizeof( oblist )))
    {
        return 1;
    }
    rank = this_player()->query_morgul_level();
    higher = ({});
    while (i--)
    {
        if (oblist[i]->query_morgul_level() > rank/2)
        {
            higher += ({ oblist[i] });
        }
        else
        {
            lower += ({ oblist[i] });
        }
    }
    higher->command( "$blush" );
    lower->command( "$cower" );
    return 1;
}

public int mlaugh( string str )
{
 object *oblist, tp = this_player();
 string  msg1, msg2;

    if (msg2 = this_player()->query_prop( LIVE_M_MOUTH_BLOCKED ))
    {
        write( "You try to laugh but the effect is rather miserable.\n" );
        allbb( " laughs soundlessly." );
        return 1;
    }
    if (!strlen( str ))
    {
        if ((tp == present( MORGUL_S_GUILD_OBJECT, tp )->query_worn()) &&
            tp->query_hooded())
        {
            msg1 = "A hard edged, hollow sounding maniacal laughter rings "+
                "from beneath ";
            msg2 = "'s hood.";
            say( ({ msg1+ METNAME+ msg2+ "\n", msg1+
                lower_case( TART_NONMETNAME )+ msg2+ "\n", msg1+
                lower_case( UNSEEN_NAME )+ msg2 + "\n" }) );
            write( "You laugh maniacally from beneath your hood.\n" );
            MORGUL_MASTER->increase_activity( tp, ACTIVITY_EMOTION );
            return 1;
        }
        write( "You laugh maniacally.\n" );
        all( " laughs maniacally." );
        MORGUL_MASTER->increase_activity( tp, ACTIVITY_EMOTION );
        return 1;
    }
    oblist = parse_this( str, "[at] [the] %i" );
    oblist -= ({ this_player() });
    if (!sizeof( oblist ))
    {
        notify_fail( "Laugh at whom/what?\n" );
        return 0;
    }

    if ((tp == present( MORGUL_S_GUILD_OBJECT, tp )->query_worn()))
    {
        target( " turns into your direction and a hard edged, hollow "+
            "sounding maniacal laughter rings from beneath "+ TP_HIS+
            " hood.", oblist );
        actor( "You turn in the direction of", oblist,
            ", laughing maniacally from beneath your hood." );
        all2act( " turns in the direction of", oblist, " and a hard "+
            "edged, hollow sounding maniacal laughter rings from beneath "+
            TP_HIS+ " hood." );
        return 1;
    }
    target( " laughs maniacally in your direction.", oblist );
    actor( "You laugh maniacally in", oblist, "'s direction." );
    all2act( " laughs maniacally in", oblist, "'s direction." );
    MORGUL_MASTER->increase_activity( tp, ACTIVITY_EMOTION );
    return 1;
}

public int mnarrow( string str )
{
 string *how, thood = "", ohood = "";

    if (this_player()->query_morgul_level() <= APPRENTICE_LEVEL)
    {
        return 0;
    }
    how = parse_adverb_with_space( str, "coldly", 0 );

    if (strlen( how[0] ))
    {
        notify_fail( "Narrow what?\n" );
        return 0;
    }
    if (this_player()->query_hooded())
    {
        thood = " beneath your hood";
        ohood = " beneath "+ TP_HIS+ " hood";
    }
    write( "Your burning red eyes narrow"+ how[1]+ thood+ ".\n" );
    allbb( "'s burning red eyes narrow"+ how[1]+ ohood+ "." );
    MORGUL_MASTER->increase_activity( this_player(), ACTIVITY_EMOTION );
    return 1;
}

public int mordor( string str )
{
 string *how;

    how = parse_adverb_with_space( str, "gravely", 0 );
    if (strlen( how[0] ))
    {
        notify_fail( "Where do you want to stare?\n" );
        return 0;
    }
    write( "You turn to the East, and stare"+ how[1]+ " into the eye "+
        "of your Master.\n" );
    allbb( " turns to the East and stares"+ how[1]+ " towards Mordor." );
    MORGUL_MASTER->increase_activity( this_player(), ACTIVITY_EMOTION );
	
	environment(this_player())->performed_mordor_emote();
    return 1;
}

/*
 * Function name: mturn
 * Description  : Suggestion by Toby and Louie
 */
public int mturn( string str )
{
 object *oblist;
 string *how, extra = "";

    if (!this_player()->query_hooded())
    {
        notify_fail( "You are not wearing a hood!\n" );
        return 0;
    }
    how = parse_adverb_with_space( str, "piercingly", 0 );

    oblist = parse_this( how[0], "[at] [the] %i" );
    if (!sizeof( oblist ))
    {
        notify_fail( "Turn your eyes onto whom/what?\n" );
        return 0;
    }

    actor( "You turn your hooded head and look"+ how[1]+ " at", oblist,
        "." );
    targetbb( " turns toward you under "+ TP_HIS+ " hood, "+ "and you "+
        "feel "+ TP_HIS+ " gaze tear"+ how[1]+ " into your soul.", oblist );
    all2actbb( " turns under "+ TP_HIS+ " hood toward", oblist, "." );
    MORGUL_MASTER->increase_activity( this_player(), ACTIVITY_EMOTION );
    return 1;
}

// This is to rasp at someone or something
public int rasp_emote( string str )
{
 object *oblist;
 string *how, temp;

    if (temp = this_player()->query_prop( LIVE_M_MOUTH_BLOCKED ))
    {
        write( stringp( temp ) ? temp :
            "You are gagged and cannot rasp.\n" );
        return 1;
    }
    how = parse_adverb_with_space( str, "threateningly", 0 );
    SOULDESC( "rasping"+ how[1] );
    if (!strlen( how[0] ))
    {
        write( "You rasp"+ how[1]+ ".\n" );
        all( " rasps"+ how[1]+ "." );
        MORGUL_MASTER->increase_activity( this_player(), ACTIVITY_EMOTION );
        return 1;
    }

    oblist = parse_this( how[0], "[at] [the] %i" );    
    oblist -= ({ this_player() });

    if (sizeof( oblist ) == 1)
    {
        target( " rasps"+ how[1]+ " at you.", oblist );
        actor( "You rasp"+ how[1]+ " at", oblist, "." );
        all2act( " rasps"+ how[1]+ " at", oblist, "." );
        MORGUL_MASTER->increase_activity( this_player(), ACTIVITY_EMOTION );
        return 1;
    }

    if (sizeof( oblist ) > 1)
    {
        notify_fail( "You should only rasp at one thing.\n" );
        return 0;
    }
    notify_fail( "Rasp at whom or what?\n" );
    if (!parse_command( how[0], environment( this_player() ),
        " 'at' [the] %i ", oblist ))
    {
        return 0;
    }
}

public int hgaze( string str )
{
 object *oblist, rname;
 string  adj = 0;

    if (!strlen( str ))
    {
        notify_fail( "Gaze at whom?\n" );
        return 0;
    }
    oblist = parse_this( str, "[at] [the] %l" );
    oblist -= ({ this_player() });

    if (sizeof(oblist) != 1)
    {
        notify_fail( "Gaze at whom?" );
        return 0;
    }
    switch (oblist[0]->query_race())
    {
    case "elf":
        if (oblist[0]->query_race_name() == "orc")
        {
            adj = "orcish";
            actor(    "With cruel pleasure, you gaze upon", oblist,
                "'s hideously twisted "+ adj+ " features." );
            target( " gazes upon your hideously twisted "+ adj+
                " features with cruel pleasure.", oblist );
            all2actbb( " gazes upon", oblist, "'s hideously twisted "+ adj+
                " features with cruel pleasure." );
            break;
        }
        write( "You stare with hatred at the accursed elf.\n" );
        targetbb( " stares at you, hatred burning in "+ TP_HIS+ " eyes.",
            oblist );
        all2actbb( " stares at", oblist, " with hatred in "+ TP_HIS+
            " eyes." );
        break;
    case "human":
    case "dwarf":
        if (oblist[0]->query_alignment() < MORGUL_I_ALIGN_JOIN)
        {
            actor( "You gaze upon", oblist,
                "'s dark countenance with glee." );
            target( " looks at you with glee.", oblist );
            all2actbb( " looks gleefully upon", oblist,
                "'s dark countenance." );
        }
        else
        {
            actor( "You gaze at", oblist, " with contempt." );
            target( " gazes at you with contempt.", oblist );
            all2actbb( " looks upon", oblist, " with contempt." );
        }
        break;
    case "hobbit":
        actor( "You regard", oblist, " with utter scorn." );
        target( " regards you scornfully.", oblist );
        all2actbb( " regards", oblist, " scornfully." );
        break;
    case "orc":
    case "goblin":
        adj = "orcish";
    case "troll":
        if (!( adj ))
        {
            adj = "trollish";
        }
        actor(    "With cruel pleasure, you gaze upon", oblist,
            "'s hideously twisted "+ adj+ " features." );
        target( " gazes upon your hideously twisted "+ adj+
            " features with cruel pleasure.", oblist );
        all2actbb( " gazes upon", oblist, "'s hideously twisted "+ adj+
            " features with cruel pleasure." );
        break;
    case "gnome":
    default:
        actor( "You look at", oblist, " without interest." );
        target( " looks at you without interest.", oblist);
        all2actbb( " looks at", oblist, " without interest." );
        break;
    }
    MORGUL_MASTER->increase_activity( this_player(), ACTIVITY_EMOTION );
    return 1;
}
public int msneer( string str )
{
 object *oblist;
 string *how, temp;

    if (temp = this_player()->query_prop( LIVE_M_MOUTH_BLOCKED ))
    {
        write( stringp( temp ) ? temp :
            "You are gagged and cannot sneer.\n" );
        return 1;
    }
    how = parse_adverb_with_space( str, "derisively", 0 );
    if (!strlen( how[0] ))
    {
        write( "You sneer"+ how[1]+ ".\n" );
        all( " sneers"+ how[1]+ "." );
        return 1;
    }

    oblist = parse_this( how[0], "[at] [the] %i" );
    oblist -= ({ this_player() });
    if (!sizeof( oblist ))
    {
        notify_fail( "Sneer at whom/what?\n" );
        return 0;
    }

    target( " sneers"+ how[1]+ " at you, a pitiful excuse for a humanoid.",
        oblist );
    actor( "You sneer"+ how[1]+ " at", oblist, ".");
    all2act( " sneers"+ how[1]+ " at", oblist, ".");
    MORGUL_MASTER->increase_activity( this_player(), ACTIVITY_EMOTION );
    return 1;
}

void delay_summon(object tp, object *oblist, int stage)
{
 int i, s;
 float delay = 5.0;

                                /*Remove empty pointers from the array
                                 *(objects removed). oblist -= ({ 0 }); will
                                 *_not_ do the job. Don't ask me why, but it
                                 *won't. Olorin                           */
    oblist = filter( oblist, objectp );

    s=sizeof( oblist );
    switch (stage)
    {
    case 0:
        for (i=0;i<s;i++)
        {
            if (!(environment( oblist[i] )->query_prop( ROOM_I_INSIDE )))
            {
                oblist[i]->catch_msg( "You shiver, suddenly aware that "+
                    "something horrible and powerful is searching for "+
                    "you from the sky.\n" );
            }
        }
        break;
    case 1:
        for (i=0;i<s;i++)
        {
            if (!(environment( oblist[i] )->query_prop( ROOM_I_INSIDE )))
            {
                oblist[i]->catch_msg( "You are suddenly aware of a great "+
                    "horrible Red Eye searching for you from the sky!\n"+
                    "Panic grips you!\nIt is becoming difficult for you "+
                    "to breathe!\n" );
            }
        }
        delay = 10.0;
        break;
    case 2:
        for (i=0;i<s;i++)
        {
            if (!(environment( oblist[i] )->query_prop( ROOM_I_INSIDE )))
            {
                oblist[i]->catch_msg( "The Red Eye seems to have "+
                    "overlooked you, for now.\nPerhaps it found you to be "+
                    "too insignificant to warrant its attention.\nYou "+
                    "feel your breath returning.\n");
            }
        }
        break;
    }
    if (stage++ < 3)
    {
        set_alarm( delay, 0.0, &delay_summon( tp, oblist, stage ) );
    }
}

public int msummon( string str )
{
 int  red_eye;
 object *oblist, *mages, room;

    room = environment( this_player() );
    if (room->query_prop( ROOM_I_INSIDE ))
    {
        if (!room->query_red_eye())
        {
            notify_fail( "You cannot summon the Red Eye's awareness "+
                "here!\n" );
            return 0;
        }
        else
        {
            red_eye = 1;
        }
    }
    if (room->query_prop( ROOM_M_NO_MAGIC ))
    {
        notify_fail( "A power greater than the Dark Lord prevents you "+
            "from doing this!\n" );
        return 0;
    }

    if (!strlen( str ))
    {
        str = "all";
    }
    oblist = parse_this( str, "[for] [the] %l" );
    if (!sizeof( oblist ))
    {
        notify_fail( "Summon the Red Eye's awareness on which "+
            "creature?\n" );
        return 0;
    }
    mages = filter( oblist, member_filter );
    oblist -= mages;

    if (!sizeof( oblist ))
    {
        notify_fail( "You cannot summon the Red Eye's awareness on your "+
            "fellow mages!\n" );
        return 0;
    }

    write( "You offer a silent prayer unto the Red Eye, certain that you "+
        "have found something of interest.\n" );
    allbb( " draws power from the realm of the shadows." );

    if ( red_eye )
    {
        room->do_summon_red_eye( this_player(), oblist );
    }
    else
    {
        set_alarm( 5.0, 0.0, &delay_summon( this_player(), oblist, 0 ) );
    }
    MORGUL_MASTER->increase_activity( this_player(), ACTIVITY_EMOTION );
    return 1;
}

public int tempt( string str )
{
 object *oblist;
 int  intel, odis, oalign;
 string astr, sstr, tstr;

    oblist = parse_this( str, "[the] %l" );
    oblist -= ({ this_player() });

    if (!sizeof( oblist ))
    {
        notify_fail( "Tempt whom?\n" );
        return 0;
    }
    if (sizeof( oblist ) > 1)
    {
        notify_fail( "You can only tempt one person at a time!\n" );
        return 0;
    }
    if (oblist[0]->query_guild_name_occ() == GUILD_NAME)
    {
        notify_fail( "You cannot tempt servants of the Dark Lord!\n" );
        return 0;
    }

    intel = this_player()->query_stat( SS_INT );
    odis = oblist[0]->query_stat( SS_DIS );
    oalign = oblist[0]->query_alignment();

    if (odis < ((2* intel)/ 3))
    {
        if (oalign < -200)
        {
            astr = capitalize( HE( oblist[0] ) )+ " seems ready to join "+
                "the forces of the Dark Lord.";
            tstr = "You feel the call of the Dark Lord within you.";
            sstr = " seems to hear the call of the Dark Lord.";
        }
        else if (oalign > 200)
        {
            astr = capitalize( HIS( oblist[0] ) )+
                " soul is torn by temptation.";
            tstr = "Your most fundamental beliefs are shattered.";
            sstr = " shrieks as the reality of evil hits "+
                HIM( oblist[0] )+" fully.";
        }
        else
        {
            astr = capitalize( HIS( oblist[0] ) )+ " soul is defiled by "+
                "the temptation.";
            tstr = "Your soul is torn by temptation.";
            sstr = " seems to be torn by temptation.";
        }
        actor( "Using the power the Dark Lord has bestowed on you, "+
            "you corrupt", oblist, ".\n" + astr );
        target( " invades your being with the presence of the Dark Lord. "+
            tstr, oblist );
        tell_room( environment( this_player() ), QCTNAME( this_player() )+
            " calls "+ QTNAME( oblist[0] )+ " with the power of the Dark "+
            "Lord, who"+ sstr+ "\n", ({ this_player(), oblist[0] }));
    }
    else if (odis < intel)
    {
        if (oalign < 0)
        {
            astr = capitalize( HE( oblist[0] ) )+ " hears the call of the "+
                "Dark Lord.";
        }
        else
        {
            astr = capitalize( HIS( oblist[0] ) )+
                " convictions are shaken.";
        }
        actor( "You call to", oblist, " with Dark Power. "+ astr );
        target( " beckons to you with the Dark Lord's might. You struggle "+
            "to resist, but your beliefs have been challenged.", oblist );
        tell_room( environment( this_player() ), QCTNAME( this_player() )+
            " beckons to "+ QTNAME( oblist[0] )+ " with the power of "+
            "Morgul. "+ QCTNAME( oblist[0] )+ " stands shaken by this "+
            "challenge.\n", ({ this_player(), oblist[0] }) ); 
    }
    else if (odis < ((3* intel)/ 2))
    {
        tstr = (oalign < 0 ? "tempts" : "threatens");
        actor( "You tempt", oblist, " with the Dark Lord's might, "+
            "but "+ HE( oblist[0] )+ " resists you." );
        target( " "+ tstr+ " you with the power of the Dark Lord. You "+
            "break "+ TP_HIS+ " sway after a momentary struggle.", oblist );
        tell_room( environment( this_player() ), QCTNAME( this_player() )+
            " "+ tstr+ " "+ QTNAME( oblist[0] )+ " with Dark Sorcery.  "+
            QCTNAME( oblist[0] )+ "struggles for a moment, but stands "+
            "firm.\n", ({ this_player(),oblist[0] }) );
    }
    else
    {
        actor( "You attempt to sway", oblist, " with the power of the "+
            "Dark Lord, but "+ HIS( oblist[0] )+ " will is too strong." );
        target( " calls to you with the Power of the Dark Lord but you "+
            "easily shrug off "+ HIS( oblist[0] )+ " influence.", oblist );
        tell_room( environment( this_player() ), QCTNAME( this_player() )+
            " tempts "+ QTNAME( oblist[0] )+ " with "+ HIS( this_player() )+
            " power, but "+ QTNAME( oblist[0] )+ " laughs in "+
            HIS( this_player() )+ " face.\n", ({ this_player(),
            oblist[0] }) );    
    }
    MORGUL_MASTER->increase_activity( this_player(), ACTIVITY_EMOTION );
    return 1;
}

public int torture( string str )
{
 object *oblist;
 string  *how;

    how = parse_adverb_with_space(str, ADV_DUMMY, 0);

    if (!strlen(how[0]))
    {
        switch (random( 2 ))
        {
        case 0:
            if (how[1] == " " + ADV_DUMMY)
            {
                how[1] = " with delight";
            }
            write( "You grin"+ how[1]+ " at the thought of your last "+
                "victim's screams.\n" );
            allbb( " grins"+ how[1]+ " at the thought of "+ TP_HIS+
                " last victim's screams." );
            break;
        case 1:
            if (how[1] == " " + ADV_DUMMY)
            {
                how[1] = " sadistically";
            }
            write( "You contemplate"+ how[1]+ " how easily needles can "+
                "slip under someone's fingernails.\n" );
            allbb( " contemplates"+ how[1]+ " how easily needles can slip "+
                "under someone's fingernails." );
            break;
        }
        MORGUL_MASTER->increase_activity( this_player(), ACTIVITY_EMOTION );
        return 1;
    }

    oblist = parse_this( how[0], "[the] %l" );
    oblist -= ({ this_player() });
    if (!sizeof( oblist ))
    {
        notify_fail( "Torture whom?\n" );
        return 0;
    }

    switch (random( 4 ))
    {
    case 0:
        if(how[1] == " " + ADV_DUMMY)
        {
            how[1] = " with delight";
        }
        target( " chuckles"+ how[1]+ " at the thought of putting you on "+
            "the rack.", oblist );
        actor( "You chuckle"+ how[1]+ " at the thought of putting", oblist,
            " on the rack." );
        all2act( " chuckles"+ how[1]+ " at the thought of putting", oblist,
            " on the rack." );
        break;
    case 1:
        if (how[1] == " " + ADV_DUMMY)
        {
            how[1] = " dreamingly";
        }
        target( " wonders"+ how[1]+ " how you would respond to a bed of "+
            "white hot coals.", oblist );
        actor( "You wonder"+ how[1]+ " how", oblist, " would respond to "+
            "a bed of white hot coals." );
        all2act( " wonders"+ how[1]+ " how", oblist, " would respond to "+
            "a bed of white hot coals." );
        break;
    case 2:
        if(how[1] == " " + ADV_DUMMY)
        {
            how[1] = " wistfully";
        }
        targetbb( " thinks of "+ TP_HIS+ " new thumb-screws while staring "+
            "at you"+ how[1]+ ".", oblist );
        actor( "You think of your new thumb-screws while staring at",
            oblist, how[1]+ "." );
        all2actbb( " thinks of "+ TP_HIS+ " new thumb-screws while "+
            "staring at", oblist, how[1]+ "." );
        break;
    case 3:
        if(how[1] == " " + ADV_DUMMY)
        {
            how[1] = " fondly";
        }
        targetbb( " thinks"+ how[1]+ " of removing your skin, piece by "+
            "tiny piece.", oblist );
        actor( "You think"+ how[1]+ " of removing", oblist, "'s skin, "+
            "piece by tiny piece." );
        all2actbb( " thinks"+ how[1]+ " of removing", oblist, "'s skin, "+
            "piece by tiny piece." );
        break;
    }
    MORGUL_MASTER->increase_activity( this_player(), ACTIVITY_EMOTION );
    return 1;
}

public int mwail( string str )
{
 string *how, temp;

    if (temp = this_player()->query_prop( LIVE_M_MOUTH_BLOCKED ))
    {
        write( stringp( temp ) ? temp :
            "You are gagged and cannot wail.\n" );
        return 1;
    }
    how = parse_adverb_with_space( str, "shrilly", 0 );
    SOULDESC( "shrieking"+ how[1] );

    if (strlen( how[0] ))
    {
        return 0;
    }
    write( "You reach for the sky, shrieking"+ how[1]+ " in fury!\n" );
    all( " reaches for the sky, shrieking"+ how[1]+ " in fury!" );
    MORGUL_MASTER->increase_activity( this_player(), ACTIVITY_EMOTION );
    return 1;
}

public int withdraw( string str )
{
 string *how;

    how = parse_adverb_with_space( str, "haughtily", 0 );

    if (strlen( how[0] ))
    {
        return 0;
    }
    write( "You withdraw"+ how[1]+ " into the shadows of your robe, "+
        "remaining silent but watchful.\n" );
    allbb(" withdraws"+ how[1]+ " into the shadows of "+ TP_HIS+ " robe, "+
        "remaining silent but watchful." );

    MORGUL_MASTER->increase_activity( this_player(), ACTIVITY_EMOTION );
    return 1;
}

public int wrath( string str )
{
 object *oblist;
 string *how;

    how = parse_adverb_with_space( str, "wildly", 0 );

    if (!strlen( how[0] ))
    {
        notify_fail( "Call wrath down upon whom?\n" );
        return 0;
    }

    oblist = parse_this( how[0], "[on] [at] [the] %i" );
    oblist -= ({ this_player() });

    if (!sizeof( oblist ))
    {
        notify_fail( "Call wrath down upon whom/what?\n" );
        return 0;
    }

    targetbb( " dances"+ how[1]+ " as "+ TP_HE+ " calls down the wrath of "+
        "Sauron upon you.", oblist );
    actor( "You dance"+ how[1]+ " as you call down the wrath of Sauron "+
        "upon", oblist, "." );
    all2actbb( " dances"+ how[1]+ " as "+ TP_HE+ " calls down the wrath "+
        "of Sauron upon", oblist, "." );

    MORGUL_MASTER->increase_activity( this_player(), ACTIVITY_EMOTION );
    return 1;
}

public int mslap(string str)
{
    object *oblist;
    string *how;

    if (this_player()->query_morgul_level() <= APPRENTICE_LEVEL)
    {
        return 0;
    }
    
    how = parse_adverb_with_space( str, "mercilessly", 0 );
    if (!strlen( how[0] ))
    {
        how[0] = "all";
    }

    oblist = parse_this( how[0], "[at] [the] %l" );
    oblist -= ({ this_player() });
    if(sizeof(oblist) != 1) 
    {
        notify_fail( "Slap whom?\n" );
        return 0;
    }
    
    actor("You"+ how[1]+ " slap", oblist, " across the face, punishing "
        + HIM(oblist[0]) + " for " + HIS(oblist[0]) + " insolence." );
    targetbb( how[1]+ " slaps you across the face, punishing you for "
        + "your insolence.", oblist );
    all2actbb(how[1] + " slaps", oblist, " punishing " + HIM(oblist[0])
        + " for " + HIS(oblist[0]) + " insolence." );
    MORGUL_MASTER->increase_activity( this_player(), ACTIVITY_EMOTION );
    return 1;

}


public int mbrood( string str )
{
    mixed   parse_result;
    object *oblist = ({});
    string *how = ({ "the darkness to come.", " darkly" });

    if(str && strlen(str))
    {
        string  message;
        how = parse_adverb_with_space( str, "darkly", 0 );

        if(strlen(how[0])) 
        {
            if(parse_command(how[0], environment(this_player()), "[at] [the] %l %s",
                parse_result, message)) 
            {
                oblist = NORMAL_ACCESS(parse_result, 0, 0);
                how[0] = message;
            }
        }
        
        if(!strlen(how[0])) 
        {
            how[0] = "the darkness to come.";
        }
    } 

    string text;
    if((how[0] != "the darkness to come.") && 
       (text = this_player()->query_prop( LIVE_M_MOUTH_BLOCKED )))
    {
        write( stringp( text ) ? text :
            "You are gagged and cannot hiss.\n" );
        return 1;
    }
    
    if(sizeof(oblist)) 
    {
        if (this_player()->query_hooded()) {
            actor( "You brood" + how[1] + " beneath your hood, your gaze "
                + "focusing upon", oblist, " as you contemplate "
                + how[0]);
            target(" broods"+ how[1]+ " beneath " + TP_HIS + " hood, "
                + TP_HIS + " gaze focusing on you as " + TP_HE + " contemplates "
                + how[0], oblist);
            all2act(" broods" + how[1] + " beneath " + TP_HIS + " hood, "
                + TP_HIS + " gaze focusing on", oblist, " as " + TP_HE 
                + " contemplates " + how[0]);
        } else {
            actor( "You brood" + how[1] + ", your gaze "
                + "focusing upon", oblist, " as you contemplate "
                + how[0]);
            target(" broods"+ how[1]+ ", "
                + TP_HIS + " gaze focusing on you as " + TP_HE + " contemplates "
                + how[0], oblist);
            all2act(" broods" + how[1] + ", "
                + TP_HIS + " gaze focusing on", oblist, " as " + TP_HE 
                + " contemplates " + how[0]);
        }
    }
    else
    {
        if (this_player()->query_hooded()) {
            write("You brood" + how[1] + " beneath your hood as you contemplate "
                + how[0] + "\n");
            all(" broods" + how[1] + " beneath " + TP_HIS + " hood as "
                + TP_HE + " contemplates " + how[0], how[1]);
        } else {
            write("You brood" + how[1] + " as you contemplate "
                + how[0] + "\n");
            all(" broods" + how[1] + " as "
                + TP_HE + " contemplates " + how[0], how[1]);
        }
    }
    
    MORGUL_MASTER->increase_activity( this_player(), ACTIVITY_EMOTION );
    return 1;
}
