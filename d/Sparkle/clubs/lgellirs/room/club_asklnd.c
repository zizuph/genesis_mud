
/*
 *  Club Joining Room for the Gellirs of Lars
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

object clubnpc;

/* prototypes */

int is_lgellirroom();
public void hook_smelled(string str);
int uphill_exit_see();
int uphill_exit_use();
void reset_room();
public void create_room();
void resolve_quest( object plyr );
void flame_mesg( int i, object p );
int tend_it( string str );
string formatmsg( string msg, string *adjl );
void inspire_larsreykr( object p );
int inspire_it( string str );
void expire_larsreykr( object p );
int expire_it( string str );
int block_it( string str );
int wizact_it( string str );
void init();
void warning_to_larsgellir( object plyr );
void welcome_to_larsgellir( object plyr );
void welcome_to_wizard( object plyr );
void enter_inv( object ob, object from );

/* functions */

int 
is_lgellirroom()
{
    return 1;
}


public void
hook_smelled(string str)
{
    write("Wood smoke, bearing an odd ethereal scent, lingers all "+
            "about this place.\n");
}


int
uphill_exit_see()
{
  object p = this_player();
  if ( IS_A_LARSGELLIR(p) > 0 || p->query_wiz_level() > 0 )
      return 0;
  else
      return 1;
}


int
uphill_exit_use()
{
  object p = this_player();
  if ( IS_A_LARSGELLIR(p) > 0 || p->query_wiz_level() > 0 )
      return 0;
  else
  {
      p->catch_msg("You cannot see a trail leading uphill.\n");
      return 1;
  }
}


void
reset_room()
{

    if ( !LGELLIR_IS_DAEMON() ) 
    {
        if ( present(clubnpc) )
	{
            tell_room(this_object(),
            QCTNAME(clubnpc) + " abruptly vanishes up in smoke.\n");
            clubnpc->remove_object();
	}

        add_item(({"fire","fire in the clearing","fire in clearing",
               "the fire","the fire in the clearing"}),
               "A fire burns in the middle of the clearing, " +  
               "surrounded by a circle of stones, a few strides across. "+
               "Low flames flicker weakly over dying embers amid a "+
	       "bed of ash. The fire is in need of tending lest it "+
	       "burn out.\n");
    }
    else
    {
        if ( !clubnpc )
        {
            setuid();
            seteuid(getuid());
            clubnpc = clone_object( LGELLIRPRINPC );
            clubnpc->move(this_object());

            tell_room(this_object(),
                "Someone, " + LGELLIR_NPC_ADJ0 + " and " + 
	         LGELLIR_NPC_ADJ1 + " , draws near the fire.\n");
        }

        add_item(({"fire","fire in the clearing","fire in clearing",
               "the fire","the fire in the clearing"}),
               "A simple fire burns in the middle of the clearing, " +  
               "surrounded by a circle of stones, a few strides across. "+
               "Flames rise from the glowing coals at its heart, to dance "+
               "before the still-moist wood at its edge. The moisture "+
               "sings through fissures in the wood, driven out by the "+
               "heat which warms all who would gather round. "+
               "Singing and crackling and dancing bright, the fire "+
               "is the centre of attention.\n");

    }

}


public void
create_room()
{
    set_short("clearing in an densely wooded ash grove");

    set_long("Primordial ash trees surround the clearing; growing tall and " +
             "tangled in a dense press of foliage. After the struggle " +
	     "to make any way through the forest, the clearing provides "+
	     "welcome respite to rest and reorder oneself. The clearing's "+
	     "edge bears a ring of tree stumps and trailheads hewn by "+
	     "some unseen agency. Many trails lead away from the clearing; "+
	     "uphill and down. A tidy pile of cut wood stands a "+
	     "scant dragonlength from the treeline, in the middle of the "+
	     "clearing, arranged beside a fire. Smoke rises from the fire.\n");

     add_item(({"clearing","the clearing"}),
              "The open space of the clearing welcomes contemplation "+
	      "and repose after the tangled chaos of the enclosing forest. "+
	      "The clearing spans two dragonlengths of soft mossy ground "+
	      "littered with leaves. A pile of cut logs stands "+
	      "in the middle of the clearing. A well-tended fire burns "+
	      "beside it. A stream of smoke rises from the fire.\n");

     add_item(({"trees","ash trees","primordial ash trees","forest","grove"}),
                "The light of the fire in the open clearing "+
                "makes the surrounding forest appear all the more dark, "+
		"dense and disordered. The flicker of the flames seems "+
		"to pick up movement here and there in the trees... or "+
		"is that only in your imagination?\n");

     add_item(({"smoke","the smoke","smoke rising from the fire",
                "stream of smoke","stream"}),
                "A thin stream of pale smoke rises from the fire in "+
                "the clearing. It possesses a scent you've not smelled "+
		"outside of this grove. The smoke seems to dissipate "+
		"entirely but a short distance, half a dragonlength or so, "+
		"above the flames.\n");

     add_item(({"logs","cut wood","wood","woodpile","cut logs"}),
                "The pile of cut logs has been stacked in an orderly row "+
		"beside the fire. They are all of the same length, half a "+
		"stride, and split neatly in two exposing pale wood. "+
		"There is no axe nearby nor any sign of whoever might have "+
		"wielded one to create this source of fuel for the fire.\n");

     add_item(({"stumps","treestumps","stump","treestump"}),
                "A ring of stumps, two or three deep, line the edge of "+
                "the clearing. Though a full stride across, each stump "+
		"seems clean cut as though by a single blow. There is "+
		"no sign of the woodsman who may have delivered such "+
		"blows.\n");

     add_item(({"trailhead","trailheads","trails","trail"}),
                "Out past the treestumps, the press of trunks and branches "+
		"and leaves is interrupted in a handful of places by "+
                "openings hewn into the forest. Narrow trails lead from "+
		"these places, containing more stumps along their way. "+
		"Whether they progress downhill or up "+
		"is hard to tell since each trail soon twists out of sight "+
		"among the trees.\n");

     add_item(({"uphill","up"}),
                "Presumably one of the trails might continue uphill "+
		"from the clearing.\n");

     add_item(({"downhill","down"}),
                "There seems to be one trail that obviously leads back "+
                "downhill out of the clearing and the ash forest.\n");

     add_item(({"ravens","two ravens","ravens two","the ravens","birds"}),
                "Perhaps there is movement in the branches, but it could "+
                "just be the play of the firelight on the trees.\n");

     add_item(({"woodsman","the woodsman"}),
                "No prints mark the ground of the clearing, save "+
                "those you can account for personally. The logs for the fire, "+
		"the treestumps and trails; all must have been cut by "+
		"someone or something not now in sight nor earshot.\n");

    // light of "the Fire" always fills this place
    add_prop( ROOM_I_LIGHT, ALWAYS_LIGHT );
    add_prop(ROOM_I_INSIDE, 0);

    add_exit( LGELLIRROOM + "club_wandr1", "downhill");
    add_exit( LGELLIRROOM + "club_wandr2", "uphill", 
               uphill_exit_use, 0, uphill_exit_see );

    reset_room();
}


void
resolve_quest( object plyr )
{
    if ( !LGELLIR_QUEST_ENABLED() ) return;

    if ( plyr->test_bit(LGELLIR_QUEST_DOMAIN,
                        LGELLIR_QUEST_GROUP,
                        LGELLIR_QUEST_BIT) ) return;

    string preamble = "\n\nYou remember knowing, "+
                   "somehow without ever being told, the story of "+
                   "what you have now seen in the Fire.\n\n";

    plyr->catch_msg(preamble + "You feel slightly more experienced.\n\n");
    tell_room(this_object(), QCTNAME(plyr) +
                " looks slightly more experienced.\n", plyr);

    plyr->add_exp_quest(LGELLIR_QUEST_XP);
    plyr->set_bit(LGELLIR_QUEST_GROUP, LGELLIR_QUEST_BIT);

    write_file( LGELLIR_QUEST_LOG, ctime(time()) + " "
               + plyr->query_real_name() + " completed the quest"
               + " receiving " + val2str(LGELLIR_QUEST_XP) + "points.\n");
    return;

}


void
flame_mesg( int i, object p )
{
    // shows relevant sections of the story "The Fire and the Folk" 

    switch (i)
    {
    case 0:
        p->catch_msg("\n\n... the world turns before your eyes -- "+
          "covered by a single great ash forest, the Askverold...\n");
        break;
    case 1:
        p->catch_msg("\n\n...the forest is everywhere growing -- writhing "+
          "against itself, Creation without end...\n");
        break;
    case 2:
        p->catch_msg("\n\n...wild things dwell there -- "+
          "as innocent of thought as the trees themselves...\n");
        break;
    case 3:
        p->catch_msg("\n\n...before the writhing Askverold " +
          "there opens a bottomless abyss -- the Mikillgap...\n");
        break;
    case 4:
        p->catch_msg("\n\n...Mindless -- creation without end in the "+
            "Askverold meets destruction without end in the Mikillgap...\n");
        break;
    case 5:
        p->catch_msg("\n\n...long ages pass beyond counting -- "+
            "for the wild things have not the wit to count...\n");
        break;
    case 6:
        p->catch_msg("\n\n...then change comes from above -- " +
            "a bolt of lightning sets a tree in the forest aflame...\n");
        break;
    case 7:
        p->catch_msg("\n\n...the wild things pressed about the tree "+
            "see creation and destruction together for the first time...\n");
        break;
    case 8:
        p->catch_msg("\n\n...they inspire the smoke of this union --  "+
            "and they are inspired...\n");
        break;
    case 9:
        p->catch_msg("\n\n...tending the fire they come to know --  "+
          "to know the comfort and terror of conscious thought...\n");
        break;
    case 10:
        p->catch_msg("\n\n...two ravens fly down from above --  "+
          "a raven-dark figure emerges from below...\n");
        break;
    case 11:
        p->catch_msg("\n\n...they visit by the Fire --  "+
          "they become known to the folk of the Fire...\n");
        break;
    case 12:
        p->catch_msg("\n\n...the two ravens caw of sights unseen --  "+
          "the folk yearn to make their own way in the world...\n");
        break;
    case 13:
        p->catch_msg("\n\n...the dark figure wields a blade -- "+
          "trees fall so that paths can be taken by the folk...\n");
        break;
    case 14:
        p->catch_msg("\n\n...some of the folk fall to the blade also -- "+
          "as is the due of the dark figure...\n");
        break;
    case 15:
        p->catch_msg("\n\n...with the Fire and the Ravens and the Woodsman "+
          "-- a new order settles across the world...\n");
        break;
    case 16:
        p->catch_msg("\n\n...the Askverold writhes no more -- replaced by "+
          "field and fold and lesser woods and works...\n");
        break;
    case 17:
        p->catch_msg("\n\n...the Mikillgap finds its depth -- filled by "+
          "river and rain, widening into seas and oceans...\n");
        break;
    case 18:
        p->catch_msg("\n\n...the folk spread throughout the world -- bearing "+
          "fire before them, creating and destroying at will...\n");
        break;
    case 19:
        p->catch_msg("\n\n...they are created and destroyed over and again "+
          "-- changed in form in ways beyond their imagining...\n");
        break;
    case 20:
        p->catch_msg("\n\n...by Litillgap, last of Mikillgap, "+
          "in Askelund, last of Askverold -- some folk return...\n");
        break;
    case 21:
        p->catch_msg("\n\n...with each new Age they tend the Fire "+
          "-- in covenant with the Ravens Two and the Woodsman...\n");
        break;
    case 22:
        p->catch_msg("\n\n...the wise among them heed the Ravens Two "+
          "-- learning of creation and the Creator...\n");
        break;
    case 23:
        p->catch_msg("\n\n...the wise <inspire> the reykr rising from "+
          "the Fire -- so to implore His favour at their meetings...\n");
        break;
    case 24:
        p->catch_msg("\n\n...the wisest among them know His words "+
          "-- they are remade more mighty with each new age...\n");
        break;
    case 25:
        p->catch_msg("\n\n...the oldest of the wise dwells by the Fire "+
          "-- grown to suffer no more the Woodman's due...\n");
        break;
    default:
        p->add_prop(LGELLIR_PROP_TENDED_FIRE,1);
        resolve_quest(p);
        p->catch_msg("\nGiven new vision, you turn to look again "+
                     "at the old tender of the Fire. You see she is "+
		     "looking right back at you. A name fills your "+
		     "mind : " + capitalize(LGELLIR_NPC_NAME) + "\n");
        p->add_introduced(LGELLIR_NPC_NAME);
        tell_room(this_object(), QCTNAME(p) + 
          " turns to look into the staring eyes of the old tender "+
	  "of the fire.\n",p);
        return;
    }

    i++;
    set_alarm( 5.0, 0.0, &flame_mesg(i,p) );
    return;
}


int
tend_it( string str )
{
    if ( !LGELLIR_IS_DAEMON() ) return 0;

    if ( !strlen(str) ) return 0; 

    if ( !wildmatch("* fire*",lower_case(str)) )
    {
        write("Tend what? Tend the fire?\n");
        return 1; 
    }

    object p = this_player();

    p->catch_msg("You tend to the fire burning in the clearing.\n");
    tell_room(this_object(),
        QCTNAME(p) + " tends to the fire burning in the clearing.\n",p);

    if ( IS_A_LARSGELLIR(p) != 0 )
    {
        p->catch_msg("\nThe singing and crackling and dancing of fire is "+
                     "a boon to the mortal heart.\n");

        tell_room(this_object(), QCTNAME(p) + 
          " looks into the staring eyes of the old tender "+
	  "of the fire. The old tender clears her throat.\n",p);

        p->catch_msg("\nShe clears her throat with a cough and a puff "+
                     "of smoke.\n");

        clubnpc->galdrar_cycle(p);
        return 1;
    }

    if ( p->query_prop(LGELLIR_PROP_TENDED_FIRE) ) return 1;

    p->catch_msg("\n\nThe singing and crackling and dancing of the fire holds "+
        "your attention entirely. A vision stirs within:\n\n");

    tell_room(this_object(), "\nAfter a time, " +
        QTNAME(p) + " remains motionless; staring into the flames.\n",p);

    set_alarm( 4.0, 0.0, &flame_mesg(0,p) );

    return 1;    
}


string
formatmsg( string msg, string *adjl )
{
    int i;
    int n = strlen(msg);
    if (!n) return "";

    string outstr = "\n" + LGELLIR_NPC_MESGSTART + "\n";

    outstr += one_of_list(adjl) + "... ";

    for ( i=0;i<n;i++ )
        outstr += "~";

    outstr += "\n " + msg + "\n";

    for ( i=0;i<n;i++ )
        outstr += "~";

    outstr += " ..." + one_of_list(adjl)+ "\n\n";

    return outstr;
}


void
inspire_larsreykr( object p )
{
    if ( IS_A_LARSGELLIR(p) < 0 )
    {
        p->catch_msg("\n\nThe Larsreykr passes over you -- "+
          "but is not inspired by your essence. You lean back again.\n");
        tell_room(this_object(),
          QCTNAME(p) + 
	  ", leans back from the smoke, seemingly disappointed.\n",p);
        return;
    }

    string lg_mesg;
    string pname = p->query_real_name(); 
    string *adjl = ({"inspiring","warming","forming","binding"});

    string recogstr = "\n\n" + QCTNAME(clubnpc) +
        " inclines her head towards you in recognition";

    string inspstr = "\n\nA stream of primordial smoke -- the Larsreykr -- "+
              "is inspired by your essence";

    tell_room(this_object(),
	  "While tending the fire, " + QTNAME(clubnpc) + " inclines her head "+
	  "towards " + QTNAME(p) + " in silent recognition.\n",p);

    if ( IS_A_LARSGELLIR(p) )
    {
        p->catch_msg(inspstr + " anew.\n");

        p->catch_msg(recogstr + " renewed.\n");

        lg_mesg = sprintf("%s, %s", capitalize(pname),LARSGELLIR_DESCR(pname));

        p->catch_msg( formatmsg(lg_mesg,adjl) );

        // in case a gellir has lost their larsreykr somehow...
        if ( !sizeof(filter( all_inventory(p), &->id(LGELLIR_OBJ_ID) )) )
	{
            setuid();
            seteuid(getuid());
            object club_obj = clone_object( LGELLIRMEMOBJ );
            club_obj->move(p,1);
	}

        return;
    }

    p->catch_msg(inspstr + ".\n");
    p->catch_msg(recogstr + ".\n");

    LGELLIR_INSPIRE(p);

    string pdesc = LARSGELLIR_DESCR(pname);

    if ( !strlen(pdesc) )
        lg_mesg = sprintf( "%s... %s... I %s will <help> you.",
                  capitalize(pname), LGELLIR_PETNAME(pname),
		  capitalize(LGELLIR_NPC_NAME) );
    else
        lg_mesg = sprintf( "%s, %s... I %s will <help> you.",
                  capitalize(pname), pdesc,
		  capitalize(LGELLIR_NPC_NAME) );

    p->catch_msg( formatmsg(lg_mesg,adjl) );
    p->add_introduced(LGELLIR_NPC_NAME);

    // clone larsreykr and move to player
    // (it sets up club soul and shadow)

    setuid();
    seteuid(getuid());
    object club_obj = clone_object( LGELLIRMEMOBJ );
    club_obj->move(p,1);

    return;
}


int
inspire_it( string str )
{
    if ( !strlen(str) ) return 0; 

    if ( !wildmatch("*reykr*",lower_case(str)) )
    {
        write("Inspire what? Inspire the Larsreykr?\n");
        return 1; 
    }

    object p = this_player();

    p->catch_msg("\nYou lean over the fire so that its thin "+
                 "stream of rising smoke engulfs you.\n\n");

    tell_room(this_object(),
        QCTNAME(p) + " leans over the fire and is engulfed " + 
        "by the smoke rising up from it.\n",p);

    if ( !LGELLIR_IS_DAEMON() || !LGELLIR_PROCESS_ENABLED() )
    {
        p->catch_msg("\nThe Larsreykr idles in your senses "+
            "but does not bind with you. Perhaps Lars is busy.\n\n");

        tell_room(this_object(),
            QCTNAME(p) + " leans back from the fire, disappointed.\n",p);

        return 1;
    }

    set_alarm( 2.0, 0.0, &inspire_larsreykr(p) );

    return 1;    
}


void
expire_larsreykr( object p )
{
    tell_room(this_object(),
          QCTNAME(clubnpc) + 
	  " extends a hand towards " + QTNAME(p) +
          ", lifting them to their feet again. Pursing her lips, "+
	  "she draws a thin stream of smoke from the mortal "+
	  "form of " + QTNAME(p) + ".\n",p);

    p->catch_msg( capitalize(LGELLIR_NPC_NAME) +
	  " extends a hand towards you, lifting you to your feet again. "+
	  "Pursing her lips, "+
	  "she draws a thin stream of smoke from your mortal form.\n");

    // inactivate membership
    LGELLIR_EXPIRE(p);

    tell_room(this_object(),
          "\n" + QCTNAME(clubnpc) + 
	  " withdraws an ashen ember from the fire and uses it "+
	  "to freshen up her lips.\n");

    // remove club membership object(s)
    object *club_objs = filter( all_inventory(p), &->id(LGELLIR_OBJ_ID) );
    if ( !sizeof(club_objs) ) return;
    foreach ( object club_obj : club_objs )
        club_obj->remove_object();

    return;
}


int
expire_it( string str )
{
    if ( !LGELLIR_IS_DAEMON() || !clubnpc ) return 0;

    if ( !strlen(str) ) return 0; 

    if ( !wildmatch("* larsreykr*",lower_case(str)) )
    {
        write("Expire what? Expire the Larsreykr?\n");
        return 1; 
    }

    object p = this_player();

    if ( IS_A_LARSGELLIR(p) == 0 )
    {
        p->catch_msg("You have no Larsreykr to expire.\n");
        return 1; 
    }

    p->catch_msg("\nFalling to the ground, you try with all your "+
                 "might to expire and expel the otherworldly "+
                 "smoke bound within you.\n\n");

    tell_room(this_object(),
        QCTNAME(p) + " falls to the ground heaving with effort, " + 
        "convulsing as though to expel something.\n",p);

    set_alarm( 2.0, 0.0, &expire_larsreykr(p) );

    return 1;    
}


int
block_it( string str )
{
    write("There are too many ways to block someone from leaving.\n");
    return 1;
}


int
wizact_it( string str )
{
    string args;
    object plyr = this_player();

    if ( !plyr->query_wiz_level() )
        return 0;

    if ( !strlen(str) )
        plyr->catch_msg("\nWizard commands for the Gellirs of Lars use "+
	             "a two-three word syntax, "+
                     "eg. <lgwiz xx yy> where 'xx' is the "+
                     "name of a desired action and 'yy' is an argument. "+
		     "Some commands are restricted to the administering "+
		     "wizards. Also, see <lgwiz help> for help.\n");
    else
    {
        string *wd = explode(lower_case(str)," ");
        int n = sizeof(wd) - 1;
        args = implode(wd[1..n]," ");

        string wd1 = "";
        if ( sizeof(wd) > 1 ) wd1 = wd[1];

        string wd2 = "";
        if ( sizeof(wd) > 2 ) wd2 = wd[2];

        switch (wd[0])
        {
        case "help":
	    string helpstr = "\nHELP: <lgwiz> commands are as follows:\n\n" +
            "enable_quest -- enables the introduction quest\n"+
            "disable_quest -- disables the introduction quest\n"+
            "query_quest -- queries if the quest is enabled\n"+
            "introduce_word 'yy' -- introduces the word 'yy' to the list\n"+
            "suspend_word 'yy' -- suspends the word 'yy' from the list\n"+
            "except_names 'yy..' -- are excepted from exist_player protection\n"+
            "show_exceptions -- show all excepted from exist_player protection\n"+
            "query_process -- queries daemon map processing status (scoring)\n"+
            "suspend_process -- suspends daemon map processing (scoring)\n"+
            "resume_process -- resumes daemon map processing (scoring)\n"+
            "show_log -- displays the daemon log for the current Arma cycle\n"+
            "more_logs -- displays daemon logs for all Arma cycles\n"+
            "more_galdrar 'yy' -- displays galdrar of the gellir 'yy'\n"+
            "vote_galdr 'yy' -- vote for artistic merit of galdr 'yy'\n"+
            "more_gellirs -- displays club-details of gellirs\n"+
            "ban_gellir 'yy' -- bans gellir 'yy' from activity in the club\n"+
            "unban_gellir 'yy' -- lifts the ban from gellir 'yy'\n"+
            "import_wordmap 'yy' -- imports file 'yy', writes it as a wordmap"+
            "\n\nSome commands are restricted to the administering wizards.";
            plyr->more(helpstr); 
            break;
        case "enable_quest":
            LGELLIR_ENABLE_QUEST();
            break;
        case "disable_quest":
            LGELLIR_DISABLE_QUEST();
            break;
        case "query_quest":
            LGELLIR_QUERY_QUEST();
            break;
        case "introduce_word":
            LGELLIR_NEW_KRAFTORD(wd1,wd2);
            break;
        case "suspend_word":
            LGELLIR_BAN_KRAFTORD(wd1);
            break;
        case "show_exceptions":
	    LGELLIR_SHOW_EXCEPTED();
            break;
        case "except_names":
            LGELLIR_EXCEPT_NAMES(args);
            break;
        case "query_process":
            LGELLIR_QUERY_PROCESS();
            break;
        case "suspend_process":
            LGELLIR_PROCESS_SUSPENSION();
            break;
        case "resume_process":
            LGELLIR_PROCESS_RESUMPTION();
            break;
        case "show_log":
            LGELLIR_DAEMON_SHOWLOG();
            break;
        case "more_logs":
            LGELLIR_DAEMON_MORELOGS();
            break;
        case "more_galdrar":
            LGELLIR_MORE_GALDRAR(wd1);
            break;
        case "vote_galdr":
            LGELLIR_VOTE_FOR_GALDR(wd1);
            break;
        case "more_gellirs":
            LGELLIR_MORE_GELLIRS();
            break;
        case "ban_gellir":
            LGELLIR_BAN_GELLIR(wd1);
            break;
        case "unban_gellir":
            LGELLIR_UNBAN_GELLIR(wd1);
            break;
        case "import_wordmap":
	    LGELLIR_NEW_WMAP(wd1);
	    break;
        default:
            plyr->catch_msg( "<lgwiz " + wd[0] + 
	                     "> not recognised. For help, see " +
			     "<lgwiz help>.\n");
            break;
        }
    }

    return 1;
}


void
init()
{
    ::init();
    add_action(tend_it,"tend");
    add_action(inspire_it,"inspire");
    add_action(expire_it,"expire");
    add_action(block_it,"block");
    add_action(wizact_it,"lgwiz");

}


void
warning_to_larsgellir( object plyr )
{
    string *adjl = ({"halting","warning"});
    string pname = plyr->query_real_name();

    string mesg = "Lars too busy for Larsgellirs now";

    plyr->catch_msg( "\n\n" + formatmsg(mesg,adjl) );
    plyr->add_introduced(LGELLIR_NPC_NAME);

    return;
}


void
welcome_to_larsgellir( object plyr )
{
    string *adjl = ({"musing","yelling","forming","binding"});
    string pname = plyr->query_real_name();

    string mesg = "Welcome <" + LARSREYKR_ACTION_WORD + "> Larsgellir";

    plyr->catch_msg( formatmsg(mesg,adjl) );
    plyr->add_introduced(LGELLIR_NPC_NAME);

    if ( !LGELLIR_PROCESS_ENABLED() )
        warning_to_larsgellir( plyr );

    return;
}


void
welcome_to_wizard( object plyr )
{
    plyr->catch_msg("\n\n...<lgwiz help> for wizard-administration "+
	                  "club functions...\n\n");
    return;
}


void
enter_inv(object ob, object from)
{
    ::enter_inv(ob, from);

    if ( interactive(ob) ) 
    {
        if ( IS_A_LARSGELLIR(ob) > 0 )
            set_alarm(2.0,0.0,&welcome_to_larsgellir(ob));

        if ( ob->query_wiz_level() > 0 )
            set_alarm(2.0,0.0,&welcome_to_wizard(ob));
    }

    return;
}


