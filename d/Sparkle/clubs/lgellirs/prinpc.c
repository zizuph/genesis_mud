
/*
 * "/d/Sparkle/clubs/lgellirs/prinpc.c"
 *
 *  PRImary NPC for Gellirs of Lars (club)
 *
 *  Former mortal of Sparkle, now immortal
 *  through aeons of growth as the first
 *  Larsgellir
 *
 *  Vitwitch 2022
 */

#include <ss_types.h>
#include <macros.h>
#include <stdproperties.h>
#include <cmdparse.h>

#include "defs.h"

#define CLUBNPC_INTROD "_lgellir_npc_introd"
#define CLUBNPC_WELCOM "_lgellir_npc_welcome"
#define CLUBNPC_IGNORE "_lgellir_npc_ignore"

#define SHOW_INTEREST_PCT 20
#define INTEREST_ITEM_BLACKLIST ({"dragon tattoo"})

inherit "/std/monster";

static int gRecitAlarmID = 0;
static int gNRecitGaldrar = 0; 
static int gIRecitGaldrar = 0; 
static int gNumArtGaldrar = 0;
static string *gArtGaldrar = ({});
static string *gArtGaldrRm = ({});

/* PROTOTYPES */

void create_monster();
string formatmsg( string str, string *adjl );
string tender_message( string msgstr );
string gellir_message( string msgstr, string whostr );
public void recite_galdr();
void galdrar_cycle();
void intro_response( string whostr );
public void emote_hook(string emote, object actor, string adverb, 
          object *oblist, int cmd_attr, int target);
void welcome_gesture( object who );
void react_to_intro( string who, string garbage );
string clubnpc_default_answer();
string *explode_strip_string( string str );
public void kraftords_murmur( string kraftords, object plyr );
public void item_kraftords( object obj, object plyr );
int item_ok( object obj );
public void show_hook( object obj );
void show_interest( object who );
public void do_answer( string what, object who );
public string ask_something( string str );
void init_living();

/* FUNCTIONS */

void
create_monster()
{
    if(!IS_CLONE)
	return;

    set_living_name(LGELLIR_NPC_NAME);
    set_name(LGELLIR_NPC_NAME);

    set_race_name(LGELLIR_NPC_RACENAME);
    set_adj(LGELLIR_NPC_ADJ0);
    add_adj(LGELLIR_NPC_ADJ1);

    set_gender(G_FEMALE);

    set_short(LGELLIR_NPC_ADJ0 + " " + LGELLIR_NPC_ADJ1 +
                " " + LGELLIR_NPC_RACENAME);

    set_long("The " + LGELLIR_NPC_ADJ0 + " " + LGELLIR_NPC_ADJ1 +
             " " + LGELLIR_NPC_RACENAME + " " +
	     "is a lean figure silhouetted by flame -- tending the "+
	     "fire in the clearing. She possesses the usual number "+
             "of heads and hands and arms and legs that the mortal races "+
	     "are accorded; but all are changed. Blackened and "+
	     "hardened by fire -- all tenderness and youth, long since "+
	     "been driven off. Golden eyes stare out from a "+
	     "face adorned in ash and ember; from a head hard black "+
	     "with locks and lashes lacking. The eyes stare alternately "+
	     "into the fire and into the distance, seemingly seeing beyond "+
	     "the press of trees crowding all around. "+
	     "A cockade of smouldering leaves surround each pointed ear, "+
	     "twitching at the slightest sound. She is clad close in "+
	     "leaves of gold and brown, all asmoulder, spotted black by "+
	     "errant sparks here and there. She is bathed by rising smoke "+
	     "in which she lives and breathes. "+
	     "She tends the fire like a child.\n");

    add_item(({"skin","body","figure"}),
             "The body of the " + LGELLIR_NPC_RACENAME + " "+
             "is lean and slightly shorter than the average. Her skin is "+
	     "smooth and blackened like fire-hardened wood -- wood hardened "+
	     "by this very fire down through the ages.\n");

    add_item(({"head","face"}),
             "The " + LGELLIR_NPC_RACENAME + " "+
             "has a head without hair; neither locks nor lashes. Like that "+
	     "of the rest of her body, her skin is smooth and ebon black. "+
	     "She has adorned her head and face with streaks of ash and "+
	     "glistening embers from the fire. Eyes stare from the ashen "+
	     "streaks of her face, about a narrow nose above a small mouth. "+
	     "Her ears are cockaded by leaves.\n");

    add_item(({"mouth"}),
             "The " + LGELLIR_NPC_RACENAME + " "+
             "has a small mouth. Her thin lips are "+
             "adorned with grey ash and a smile worn beyond meaning. "+
	     "From time to time, a thin stream of smoke escapes her "+
	     "mouth in a murmur.\n");

    add_item(({"nose"}),
             "The " + LGELLIR_NPC_RACENAME + " "+
             "has a narrow nose. Her nostrils visibly flare as she "+
             "inhales the smoke which rises all about her from the fire.\n");

    add_item(({"eyes","golden eyes"}),
             "The eyes of the " + LGELLIR_NPC_RACENAME + " "+
             "are golden and bright. They flick between staring into the "+
	     "fire and into the infinite, "+
             "seldom focussing on mundane things right before them.\n");

    add_item(({"ears","cockade","pointed ears","cockades","ear"}),
             "The pointed ears of the " + LGELLIR_NPC_RACENAME + " "+
             "are surrounded by palm-sized cockades of dry smouldering "+
	     "leaves. The cockades cup the ears like shallow bowls, "+
             "perhaps helping to carry sound from further afield.\n");

    add_item(({"feet","legs"}),
             "The " + LGELLIR_NPC_RACENAME + " "+
             "is barefoot. Her feet and legs are lean and hard like the "+
	     "rest of her body. They seem immune to the fire next to which "+
             "they stand.\n");

    add_item(({"hands","arms"}),
             "The hands of the " + LGELLIR_NPC_RACENAME + " "+
             "dally in the fire tending the burning logs and embers. "+
             "Her hands and arms arms are lean and hard like the "+
	     "rest of her body.\n");

    add_item(({"cladding","leaves","clothes","clothing"}),
             "The " + LGELLIR_NPC_RACENAME + " "+
             "is clothed in dry leaves of gold and brown. They smoulder "+
             "and even catch alight here and there, without their "+
	     "wearer seeming to notice. It is not easy to tell whether "+
	     "the leaves fall upon her and cling, a gift from the trees, "+
	     "or they grow out from her body itself.\n");

    set_stats(({1000,1000,1000,1000,1000,1000}));
    set_hp(query_max_hp());
    set_skill(SS_DEFENCE, 100);
    set_skill(SS_PARRY, 100);
    set_skill(SS_AWARENESS, 100);
    set_skill(SS_LANGUAGE, 100);

    remove_prop(LIVE_I_NEVERKNOWN);

    add_prop(OBJ_M_NO_ATTACK,
       "...a whip-like crack from the Fire stays your actions..." );
    add_prop(NPC_M_NO_ACCEPT_GIVE,
       QCTNAME(this_object()) + " seems strangely out of reach.");

    add_prop(LIVE_I_SEE_DARK, 100);

    set_alignment(0);

    trig_new("%w 'introduces' %s","react_to_intro");
    set_default_answer("@@clubnpc_default_answer");

    add_ask(({"help","quest","task"}), "@@ask_something|help@@");
    add_ask(({LGELLIR_NPC_NAME}), "@@ask_something|clubnpc@@");
    add_ask(({"lars"}), "@@ask_something|lars@@");
    add_ask(({"death"}), "@@ask_something|death@@");
    add_ask(({"in extremis","extremis"}), "@@ask_something|extremis@@");
    add_ask(({"choice","place of choice"}), "@@ask_something|choice@@");
    add_ask(({"column","the column"}), "@@ask_something|column@@");
    add_ask(({"portal","the portal"}), "@@ask_something|portal@@");
    add_ask(({"to return","return"}), "@@ask_something|return@@");
    add_ask(({"ravens","two ravens","ravens two"}), "@@ask_something|ravens@@");
    add_ask(({"woodsman","the woodsman"}), "@@ask_something|woodsman@@");
    add_ask(({"gellirs","larsgellirs","larsgellir","the larsgellir",
              "the gellirs of lars","gellirs of lars","wise","the wise"}),
	      "@@ask_something|larsgellirs@@");
    add_ask(({"inspired","club","the club"}), "@@ask_something|club@@");
    add_ask(({"join","joining","join the club"}),"@@ask_something|joining@@");
    add_ask(({"leave","leaving","leave the club"}),"@@ask_something|leaving@@");
    add_ask(({"fire","the fire"}), "@@ask_something|fire@@");
    add_ask(({"clearing","the clearing"}), "@@ask_something|clearing@@");
    add_ask(({"ether","the ether","larsether","the larsether"}),
               "@@ask_something|larsether@@");
    add_ask(({"smoke","reykr","larsreykr","the larsreykr"}),
               "@@ask_something|larsreykr@@");
    add_ask(({"logs","wood"}), "@@ask_something|logs@@");
    add_ask(({"age","new age"}), "@@ask_something|age@@");
    add_ask(({"wisest"}), "@@ask_something|wisest@@");
    add_ask(({"inspire"}), "@@ask_something|inspire@@");
    add_ask(({"remade"}), "@@ask_something|remade@@");
    add_ask(({"galdr","larsgaldr","larsgaldrar","galdrar"}), 
                    "@@ask_something|larsgaldr@@");
    add_ask(({"favour","favour of lars","favoured"}), 
                    "@@ask_something|favour@@");
    add_ask(({"armageddon"}), "@@ask_something|armageddon@@");
    add_ask(({"incantations","incantation","chant","chants"}), 
                    "@@ask_something|incantation@@");
    add_ask(({"creation"}), "@@ask_something|creation@@");
    add_ask(({"destruction"}), "@@ask_something|destruction@@");
    add_ask(({"covenant","the covenant"}), "@@ask_something|covenant@@");
    add_ask(({"folk","the folk"}),"@@ask_something|folk@@");
    add_ask(({"the lost","lost"}),"@@ask_something|lost@@");
    add_ask(({"beings","all beings"}),"@@ask_something|beings@@");
    add_ask(({"mortals","mortal"}),"@@ask_something|mortals@@");
    add_ask(({"name","names"}), "@@ask_something|names@@");
    add_ask(({"kraftord","kraftords"}), "@@ask_something|kraftord@@");
    add_ask(({"grove","ash grove","askelund","the askelund"}), 
                    "@@ask_something|askelund@@");
    add_ask(({"trees","ash trees"}), "@@ask_something|trees@@");
    add_ask(({"askverold","the askverold"}), "@@ask_something|askverold@@");
    add_ask(({"abyss","litillgap","the litillgap"}),
           "@@ask_something|litillgap@@");
    add_ask(({"mikillgap","the mikillgap"}), "@@ask_something|mikillgap@@");

    set_act_time(30);
    add_act("emote handles logs on the fire -- shifting them so the flames "+
             "burn higher.");
    add_act("emote blows on the flames -- smoke streaming from her mouth.");
    add_act("emote idly steps into the fire to stoke it.");

    gArtGaldrar = LGELLIR_ART_GALDRAR();
    gNumArtGaldrar = sizeof(gArtGaldrar);
    gArtGaldrRm = ({LGELLIRROOM+"club_asklnd",LGELLIRROOM+"club_wandr1",
                    LGELLIRROOM+"club_wandr2",LGELLIRROOM+"club_lilgap",
		    LGELLIR_OPENING_LOC}); 
}


string
formatmsg( string msg, string *adjl )
{
    int i;
    int n = strlen(msg);
    string outstr = "";
    if (!n) return outstr;

    outstr += one_of_list(adjl) + "... ";

    for ( i=0;i<n;i++ )
        outstr += "~";

    outstr += "\n    " + msg + "\n";

    for ( i=0;i<n;i++ )
        outstr += "~";

    outstr += " ..." + one_of_list(adjl)+ "\n";

    return outstr; 
}


string
tender_message( string msgstr )
{
    return "\n" + LGELLIR_NPC_MESGSTART + "\n\n" +
           msgstr + "\n\n";
}


string
gellir_message( string msgstr, string whostr )
{
    return "\n" + LGELLIR_NPC_MESGSTART + "\n\n" +
           capitalize(one_of_list(LGELLIR_NPC_MORTALADDR)) + " " +
           LGELLIR_PETNAME(whostr) + ":\n" + msgstr + "\n\n";
}


public void
recite_galdr()
{
    if ( gIRecitGaldrar >= gNRecitGaldrar )
    {
        gIRecitGaldrar = 0;
        remove_alarm(gRecitAlarmID);
	return;
    }

    string galdr = gArtGaldrar[gIRecitGaldrar];
    if ( !strlen(galdr) ) 
        return;
    
    gIRecitGaldrar++;

    tell_room(environment(this_object()),
        "A stream of smoke issues from " + QTNAME(this_object()) +
        " as she whispers something.\n");

    foreach ( string room : gArtGaldrRm )
        tell_room(room,"\n...a smoky voice whispers:\n\n" + galdr + "\n");

    gRecitAlarmID = set_alarm(30.0,0.0,&recite_galdr());

    return;
}


void
galdrar_cycle()
{
    if ( !gNumArtGaldrar ) 
        return;

    if ( gRecitAlarmID )
        remove_alarm(gRecitAlarmID);

    gNRecitGaldrar = max( 3, gNumArtGaldrar );
    if ( !gNRecitGaldrar ) return;
    gIRecitGaldrar = 0;

    gRecitAlarmID = set_alarm(30.0,0.0,&recite_galdr());

    return;
}



void
intro_response( string whostr )
{
    whostr = lower_case(whostr);
    object who = find_player(whostr);

    if ( who->query_prop(CLUBNPC_IGNORE) )
        return;

    if ( present(who,environment(this_object())) 
                    && CAN_SEE(this_object(), who) )
    {
        set_alarm( 2.0, 0.0, &welcome_gesture(who) );

        if ( IS_A_LARSGELLIR(who) > 0 ) 
	{
            string *adjl = ({"welcome","recognised","familiar","returning"});
	    string msg = "Hail and well met";
            who->catch_msg(gellir_message(formatmsg(msg,adjl),
                   who->query_real_name()));
            who->add_introduced(LGELLIR_NPC_NAME);
	}
	else
	{
            if ( !who->query_prop(CLUBNPC_INTROD) )
	    {
                who->add_prop(CLUBNPC_INTROD,1);
                who->catch_msg( QCTNAME(this_object()) +
                      " murmurs while gesturing to herself...\n"+
		      "... you can just hear '" + 
                      capitalize(LGELLIR_NPC_ADJ0) + "-" +
		      capitalize(LGELLIR_NPC_ADJ1) +
		      "' over the sound of the crackling fire.\n");
            }
	    else
	    {
                who->catch_msg( QCTNAME(this_object()) +
                      " murmurs while gesturing at you...\n"+
		      "... you can just hear '" + 
                      LGELLIR_PETNAME(whostr) +
		      "' over the sound of the crackling fire.\n");
	    }

            tell_room(environment(this_object()),
                  " murmurs something...\n",who);
	}

    }

    return;
}


public void
emote_hook(string emote, object actor, string adverb, object *oblist,     
           int cmd_attr, int target)
{
    object e = environment(this_object());

    if (ACTION_CONTACT & cmd_attr)
        tell_room(e, QCTNAME(this_object()) +
            " seems strangely out of reach.\n");

    if (ACTION_OFFENSIVE & cmd_attr)
    {
        tell_room(e, QCTNAME(this_object()) +
         " truns her back on " + QTNAME(actor) + ".\n");
        actor->add_prop(CLUBNPC_IGNORE,1);
    }

    if (ACTION_INTIMATE & cmd_attr)
        tell_room(e, QCTNAME(this_object()) +
            " is silent like a burnt tree in a forest.\n");

    if (ACTION_INGRATIATORY & cmd_attr)
        tell_room(e, QCTNAME(this_object()) +
         " blows a thin stream of smoke in the face of "
	   + QTNAME(actor) + ".\n");

} 


void 
welcome_gesture( object who )
{
    if ( who->query_prop(CLUBNPC_IGNORE))
        return;

    if (!who->query_prop(CLUBNPC_WELCOM))
    {
        command("$emote gestures to a warm spot by the fire");
	who->add_prop(CLUBNPC_WELCOM,1);
    }
    return;
}


void
react_to_intro( string who, string garbage )
{
    set_alarm( 2.0, 0.0, &intro_response(who) );

    return;
}


string
clubnpc_default_answer()
{
    string msg = "this is not known";
    string *adjl = ({"puzzling","strange","curious",
                     "mystifying","inexplicable",
                     "baffling","perplexing"});
    object p = this_player();
    object TO = this_object();

    if ( p->query_prop(CLUBNPC_IGNORE) )
        p->catch_msg(QCTNAME(TO) + " ignores you.\n");
    else if ( IS_A_LARSGELLIR(p) > 0 )
        p->catch_msg(gellir_message(formatmsg(msg,adjl),
              p->query_real_name()));
    else if ( p->query_prop(LGELLIR_PROP_TENDED_FIRE) )
        p->catch_msg(tender_message(formatmsg(msg,adjl)));
    else
        p->catch_msg(QCTNAME(TO) +
           " murmurs something in response...\n");

    set_alarm( 2.0, 0.0, &welcome_gesture(p) );

    return " ";
}


string
*explode_strip_string( string str )
{
    int n = 0;
    string *outarr = ({""});

    if ( !strlen(str) ) return outarr;

    foreach ( string char : explode(lower_case(str),"") )
    {
        if ( wildmatch("[^abcdefghijklmnopqrstuvwxyz]",char) )
        {
           outarr += ({""});
           n++;
        }
        else
	{
           outarr[n] = sprintf("%s%s",outarr[n],char);
        }
    }

    outarr += ({""});
    n++;

    return outarr;
}


public void
kraftords_murmur( string kraftords, object plyr )
{
    if ( strlen(kraftords) > 0 )
    {

        int val0 = LGELLIR_GALDR_POWER(kraftords);
        int val1 = LGELLIR_GALDR_POWER(LGELLIR_DEFAULT_RARITY_WORD);

        int idiff01 = val0 - val1;
        string str; 

        if ( idiff01 <= 2 ) 
	    str = "with little";
	else
	{
            switch (idiff01)
	    {
	    case 3..6:
	        str = "with some";
	        break;
	    case 7..10:
	        str = "with much";
	        break;
	    case 11..14:
	        str = "with great";
	        break;
            default:
	        str = "with very great";
	        break;
	    }
	}

        tell_room(environment(this_object()), "\n" + QCTNAME(this_object()) +
          " murmurs " + str + " interest:\n" + kraftords + "\n\n");
    }

    tell_room(environment(this_object()), QCTNAME(this_object()) +
          " returns to tending the fire.\n\n");

    return;
}


public void
item_kraftords(object obj, object plyr)
{
    string kraftords = "";

    tell_room(environment(this_object()), QCTNAME(this_object()) +
          " examines a " + obj->short() +
          " in the possession of " + QCNAME(plyr) + ".\n",plyr);

    plyr->catch_msg( QCTNAME(this_object()) +
          " examines a " + obj->short() +
          " in your possession.\n");

    foreach ( string word : explode_strip_string(obj->long()) )
    {
        if ( IS_A_KRAFTORD(word) )
	    kraftords += sprintf("...%s ",word); 
    }

    set_alarm(2.0,0.0,&kraftords_murmur(kraftords,plyr));

    return;
}


int
item_ok( object obj )
{
    foreach ( string item : INTEREST_ITEM_BLACKLIST )
        if ( obj->id(item) ) return 0;

    return 1;
}


public void
show_hook( object obj )
{
    object p = this_player();

    if ( p->query_prop(CLUBNPC_IGNORE) )
        return;

    if ( item_ok(obj) ) 
        set_alarm(1.0, 0.0, &item_kraftords(obj,p) );

    return;
}


void
show_interest( object who )
{
    if ( this_player()->query_prop(CLUBNPC_IGNORE) )
        return;

    object *inv = filter( all_inventory(who), item_ok );
    int n = sizeof(inv);
    if ( !n ) return;

    object TO = this_object();
    string *adjl;

    if ( IS_A_LARSGELLIR(who) > 0 )
    {
        adjl = ({"curious","intriguing","singular"});
        string lgmsgstr = "show that " + inv[random(n)]->short() + " to me";
        who->catch_msg(gellir_message(formatmsg(lgmsgstr,adjl),
              who->query_real_name()));
    }
    else
        who->catch_msg("The eyes of " + QTNAME(TO) + " fix upon a " +
             inv[random(n)]->short() + " in your possession. You wonder "+
	     "if you should show it to her.\n");

    tell_room(environment(TO),"The eyes of " + QTNAME(TO) + 
         " fix upon a possession of " + QTNAME(who) + ".\n",who);

    return;
}


public void
do_answer( string what, object who )
{
    int interruptable;
    object TO = this_object();

    if ( !objectp(who) || environment(who) != environment(TO) )
        return;   /* We wont respond if the player is gone */

    if ( who->query_prop(CLUBNPC_IGNORE) )
    {
        who->catch_msg( QCTNAME(this_object()) + " ignores you.\n");
	tell_room(environment(TO),QCTNAME(this_object()) + " ignores " +
	    QTNAME(who) + ".\n",who);
	return;
    }

    string emotest0 = "welcomes all to <tend the fire> with her";
    string emotestr = "";
    string lgmsgstr;
    string *adjl;

    interruptable = 0;

    switch ( what )
    {

    case "creation":
        emotestr = "looks all about";
	adjl = ({"growing","living","burgeoning","thriving"});
        lgmsgstr = "place of Lars";
        break;

    case "destruction":
        emotestr = "looks all about";
	adjl = ({"lost","gone","faded","extinct"});
        lgmsgstr = "place of Death";
        break;

    case "lars":
        emotestr = "peers about quizzically";
	adjl = ({"distant","farsighted","original","obscure"});
        lgmsgstr = "lord of Creation";
        break;

    case "busy":
	string insertstr = " ";
        if ( LGELLIR_PROCESS_ENABLED() ) insertstr = " sometimes ";  
        emotestr = "scowls";
	adjl = ({"vexing","annoying","perplexing","disappointing"});
        lgmsgstr = "wizards" + insertstr + "occupy Lars elsewhere";
        break;

    case "death":
        emotestr = "nods slowly";
	adjl = ({"patient","certain","thankless","unseen","unknown"});
        lgmsgstr = "lord of Destruction";
        break;

    case "ravens":
        emotestr = "peers into the forest";
	adjl = ({"carping","gossipy","nosey","wise","canny"});
        lgmsgstr = "heralds of Lars";
        break;

    case "woodsman":
        emotestr = "peers into the forest";
	adjl = ({"sharp","sudden","sleepless","sure"});
        lgmsgstr = "harbinger of Death";
        break;

    case "clearing":
        emotestr = "looks all about";
	adjl = ({"firelit","smoky","wide","flat"});
        lgmsgstr = "Joining space for all Larsgellirs";
        break;

    case "fire":
        emotestr = "looks pointedly at the fire";
	adjl = ({"warm","illuminating","bright","crackling"});
        lgmsgstr = "source of Larsreykr in the Clearing";
        break;

    case "logs":
        emotestr = "glances at the woodpile";
	adjl = ({"stacked","ordered","trimmed","cut"});
        lgmsgstr = "gift of the Woodsman";
        break;

    case "trees":
        emotestr = "contemplates a large ash tree at the clearing's edge";
	adjl = ({"tall","wild","holy","sacred"});
        lgmsgstr = "home of the Ravens two";
        break;

    case "larsgaldr":
        emotestr = "smiles, murmuring some kind of chant... "+
	           "borne on a thin stream of smoke";
	adjl = ({"imploring","entreating","hopeful","soulful"});
        lgmsgstr = "Incantation borne on Larsreykr in Extremis";
        break;

    case "extremis":
        emotestr = "nods in remembrance";
	adjl = ({"circular","inevitable","illuminated","closed"});
        lgmsgstr = "place of Choice between Death and life";
        break;

    case "choice":
        emotestr = "nods in remembrance";
	adjl = ({"circular","light","bleak","shimmering"});
        lgmsgstr = "between the Column and the Portal in Extremis";
        break;

    case "column":
        emotestr = "nods in remembrance";
	adjl = ({"beside","light","white","eerie"});
        lgmsgstr = "Return in a body unchanged";
        break;

    case "portal":
        emotestr = "nods in remembrance";
	adjl = ({"transforming","central","blue","shimmering"});
        lgmsgstr = "Return in a changed body";
        break;

    case "incantation":
        emotestr = "smiles, murmuring some kind of chant... "+
	           "borne on a thin stream of smoke";
	adjl = ({"lyric","crafted","cunning","clever"});
        lgmsgstr = "weaving of Name and Kraftord seeking Favour";
        break;

    case "names":
        emotestr = "puts a finger to her lips... a thin stream of "+
	      "smoke issues from her mouth in a sshhh";
	adjl = ({"real","true","common","useful"});
        lgmsgstr = "soul handles of all Folk";
        break;

    case "lost":
        emotestr = "shrugs...";
	adjl = ({"mysterious","unnatural","uncommon","queer"});
        lgmsgstr = "those lost to Death in Creation";
        break;

    case "beings":
        emotestr = "spreads her arms to encompass all...";
	adjl = ({"ubiquitous","widespread","common","legion"});
        lgmsgstr = "Mortals and the Lost";
        break;

    case "mortal":
        emotestr = "listens for the sound of the axe...";
	adjl = ({"ubiquitous","gifted","common","limited"});
        lgmsgstr = "called by Death, whether Folk or not";
        break;

    case "folk":
        emotestr = "smiles in recognition... she stares "+
	      "into the long distance beyond the trees";
	adjl = ({"building","burning","making","destroying"});
        lgmsgstr = "all Beings bound by the Covenant";
        break;

    case "covenant":
        emotestr = "ponders in the light of the fire...";
	adjl = ({"constant","everlasting","active","eternal"});
        lgmsgstr = "bound to Return in service of Lars and Death";
        break;

    case "return":
        emotestr = "runs a finger along a scar ";
	adjl = ({"reprieved","extended","amusing","playful"});
        lgmsgstr = "return to life from Extremis";
        break;

    case "kraftord":
        emotestr = "smiles and whispers a word or two";
	adjl = ({"arcane","captivating","enchanting","amusing"});
        lgmsgstr = "words of power placed in Creation by Lars";
        break;

    case "askelund":
        emotestr = "looks all about";
	adjl = ({"venerated","crowded","enclosed","ancient"});
        lgmsgstr = "remnant of Askverold, place of the Fire";
        break;

    case "litillgap":
        emotestr = "looks uphill";
	adjl = ({"clear","empty","open","desolate"});
        lgmsgstr = "remnant of Mikillgap, blown by the Larsether";
        break;

    case "askverold":
        emotestr = "seems momentarily distracted";
	adjl = ({"primordial","shrouded","wild","untamed"});
        lgmsgstr = "forest that spanned all Creation";
        break;

    case "mikillgap":
        emotestr = "seems momentarily distracted";
	adjl = ({"yawning","bottomless","jagged","dark"});
        lgmsgstr = "abyss that was Destruction manifest";
        break;

    case "larsgellirs":
        emotestr = "smiles in welcome";
	adjl = ({"bold","wise","desperate","daring"});
        lgmsgstr = "the Inspired yellers of Larsgaldrar";
        break;

    case "age":
        emotestr = "nods in acknowledgement";
	adjl = ({"cyclic","eternal","regular","dated"});
        lgmsgstr = "time between one Armageddon and the next";
        break;

    case "remade":
        emotestr = "breaks logs with slender hands to feed the fire";
	adjl = ({"momentous","transforming","energising","empowering"});
        lgmsgstr = "at the end of the Age, the Wisest wins Favour";
        break;

    case "wisest":
        emotestr = "muses intensely upon her surroundings";
	adjl = ({"seeking","secret","fearless","devoted"});
        lgmsgstr = "whose Larsgaldr bears the greatest Kraftord of the Age";
        break;

    case "club":
        emotestr = "inhales and exhales smoke from the fire";
	adjl = ({"open","inclusive","seeking","enchanting"});
        lgmsgstr = "Join or Leave the Gellirs of Lars";
        break;

    case "inspire":
        emotestr = "inhales smoke from the fire";
	adjl = ({"momentous","decisive","resolute","critical"});
        lgmsgstr = "Join the Gellirs of Lars";
        interruptable = 1;
        break;

    case "joining":
        emotestr = "inhales smoke from the fire";
	adjl = ({"momentous","decisive","resolute","critical"});
        lgmsgstr = "<inspire> the Larsreykr";
        interruptable = 1;
        break;

    case "leaving":
        emotestr = "exhales a thin stream of smoke";
	adjl = ({"momentous","decisive","resolute","critical"});
        lgmsgstr = "<expire> the Larsreykr";
        break;

    case "larsreykr":
        emotestr = "inhales smoke from the fire";
	adjl = ({"essential","elemental","infusing","smoky"});
        lgmsgstr = "breath of Creation liberated by the Fire";
        break;

    case "favour":
        emotestr = "breaks a log in two in her hands, "+
	           "steps into the fire and places the pieces";
	adjl = ({"deserved","merited","rare","great"});
        lgmsgstr = "growth by the hand of Lars after Armageddon";
        break;

    case "armageddon":
        emotestr = "nods wisely";
	adjl = ({"catastrophic","irresistable","potent","timely"});
        lgmsgstr = "breaking and remaking of all Creation";
        break;

    case "larsether":
        emotestr = "looks uphill";
	adjl = ({"cold","gusting","turbulent","strong"});
        lgmsgstr = "wind of Lars encircling Creation";
        break;

    case "clubnpc":
        emotestr = "points at herself";
	adjl = ({LGELLIR_NPC_ADJ0,LGELLIR_NPC_ADJ1});
        lgmsgstr = "tender of the Fire in the Clearing";
        break;

    case "help":
        if ( LGELLIR_QUEST_ENABLED() && !who->test_bit(LGELLIR_QUEST_DOMAIN,
               LGELLIR_QUEST_GROUP,LGELLIR_QUEST_BIT) )
            emotestr = "points toward the fire ";
        else if ( IS_A_LARSGELLIR(who) > 0 )
	{
            // provide command help pointer for existing member
            emotestr = "stares pensive into the fire";
	    adjl = ({"instructive","telling","didactic","informative"});
            lgmsgstr = "<"+ LARSREYKR_ACTION_WORD + " help>";
        }
	else
	{
            // assume a fire tender wants to join club
            // NB: all fire tenders have completed the quest
            emotestr = "rubs her chin";
            adjl = ({"independent","empowered","growing","living"});
            lgmsgstr = "Join to help yourself";
	}
        break;

    } // switch

    if ( interruptable && !LGELLIR_PROCESS_ENABLED() )
    {
        emotestr = "shrugs and pokes the fire";
	adjl = ({"vexing","annoying","perplexing","disappointing"});
        lgmsgstr = "Lars is too Busy";
    }

    if ( IS_A_LARSGELLIR(who) > 0 )
    {
        command("$emote " + emotestr );
        who->catch_msg(gellir_message(formatmsg(lgmsgstr,adjl),
	         who->query_real_name()));
	tell_room(environment(TO),QCTNAME(TO) + " murmurs "+
           "something you cannot hear over the sound of the fire.\n",who);
    }
    else if ( who->query_prop(LGELLIR_PROP_TENDED_FIRE) )
    {
        command("$emote " + emotestr );
        who->catch_msg(tender_message(formatmsg(lgmsgstr,adjl)));
	tell_room(environment(TO),QCTNAME(TO) + " murmurs "+
           "something you cannot hear over the sound of the fire.\n",who);
    }
    else
    {
        if ( !strlen(emotestr) ) 
            emotestr = emotest0;
        else
            emotestr = emotestr + "... she " + emotest0;

        command("$emote " + emotestr );
    }

    if ( random(100) < SHOW_INTEREST_PCT )
        set_alarm( 2.0, 0.0, &show_interest(who) );
    else
        set_alarm( 2.0, 0.0, &welcome_gesture(who) );

    return;
}


public string
ask_something( string str )
{
    set_alarm( 2.0, 0.0, &do_answer(str, this_player()) );
    return "";
}


void
init_living()
{
    ::init_living();
}
