
/* 
 *  BREWCRAFTER at the Iron Delving Brewery
 *  /d/Ansalon/estwilde/living/brewcrafter.c
 *
 *  this object provides most of the functionality for craft brewing 
 *
 *  Vitwitch 01/2021
 */

#include "/d/Ansalon/common/brewcraft/brewcraft.h"
#include "/d/Ansalon/common/defs.h"
#include <cmdparse.h>
#include <ss_types.h>
#include <wa_types.h>
#include <composite.h>
#include <money.h>
#include "../local.h"
#include <stdproperties.h>
#include <macros.h>
#include <math.h>

#define BRWCNAME "jade"
#define BRWCTITL "Forgewater, Brewcrafter of Iron Delving"

#define BREWCRAFTER_PATH "/d/Ansalon/estwilde/living/brewcrafter/"
#define BREWCRAFT_GRAIL "/d/Ansalon/estwilde/obj/brewcraft_beergrail.c"
#define EXPORT_PLAT_ROYALTY 10

#define BREWER_I_HAS_GIVEN_OFFENCE   "_brewer_i_has_given_offence"
#define BREWER_I_HAS_MADE_INTRO   "_brewer_i_has_made_intro"

#define BREWCRAFT_QUEST1 "_brewcraft_quest1"

inherit "/d/Krynn/std/monster";

static int *armourloc;

/* PROTOTYPES */
int reward_due(object player);
int culture_slot( int islot );

/* FUNCTIONS */

int
is_a_brewquester( object player )
{
    return player->query_prop(BREWCRAFT_QUEST1);
}

string
no_attack()
{
    if(TP->query_npc()) return 0;
    return "As you approach with hostile intent...\n" +
       "you feel a rumbling in your nethers " +
       "as if all your sphincters are about to let go...\n" +
       "you retreat in consternation, clutching at yourself...\n";
}

string
say_offer_opinion()
{
    tell_room(environment(this_object()),
     QCTNAME(TO) + " looks about the place -- scanning for visitors to her brewery.\n");
    command("say Real brewin' can't be taught! It's either in yer culture or it aint!"); 
    return "";
}

string
say_living_culture()
{
    command("say A good brew has the living culture of its brewer inside it... I always says"); 
    return "";
}

string
say_barrel_direct()
{
    tell_room(environment(this_object()),
     QCTNAME(TO) + " gestures towards a party of dwarves -- " + 
        "rolling a huge barrel east towards the vault.\n");
    command("say Put it right at the back! It's got a ton o' " +
              "aging to do afore it'll drink right!"); 
    return "";
}

string
say_onto_something()
{
    tell_room(environment(this_object()),
     QCTNAME(TO) + " sniffs the air about -- her sharp nose turned towards openings in armour.\n");
    command("say Hmmm, there's some bite about, sure enough..."); 
    return "";
}

string
say_keepin_clean()
{
    command("chuckle ironically"); 
    command("say Folks say the secret to brewing is having clean coppers and glass and such..."); 
    return "";
}

public void
hook_smelled(string str)
{
    write("The diversity and intensity of smells emanating from this dwarf beggars belief.\n");
}


int
cannot_see_speaker()
{
    if ( !CAN_SEE(TO, TP) )
    {
        command("say Is someone there?... I cannot see yer face...");
        return 1;
    }
    return 0;
}


public string
ask_brewcrafter(string question)
{
    string str = "";

    if ( cannot_see_speaker() ) return "...";

    if (!(TP->query_prop(BREWER_I_HAS_MADE_INTRO)))
    {
        command("emote raises a red eyebrow.");
        if ( is_a_brewquester(TP) ) 
            str = "Welcome... we're always questing for diversity in brewers... "; 
        return str + "Who exactly might you be sweetie? ... before we go any further."; 
    }

    if ((TP->query_prop(BREWER_I_HAS_MADE_INTRO)))
    {
        if ( reward_due(TP) ) 
        {
            command("emote smiles broadly.");
            command("pat " + OB_NAME(TP));
            return "Well first things first... you've earned it..."; 
        }
    }

    switch(question)
    {
        default:
        case "no_info":
            command("emote nods absentmindedly at your question... while busy brewin'");
            set_alarm(1.0,0.0,
              &command("say Of course you might find information in me office...\n"));
            return(one_of_list( ({
                "Hmmm?",
                "Yes, yes... I'm sure you know best... ",
                "Err ... I'm a bit busy here to get into that",
                "Maybe you'll find a dwarf around here who knows about that?",
                }) ));
            break;
        case "tunnel":
            command("peer");
            return "I don't see no tunnel around here... must be someplace else "+
                    "if there be one at all!";
            break;
        case "goblin":
            command("peer");
            return "Well it takes all sorts o' culture to find the perfect brew... "+
                    "wouldn't want to limit the search now would we?";
            break;
        case "export":
            command("grin");
            return "We export the best of the new brews every month... "+
                    "folks get real thirsty out there! "+
                    "The export brewer's name is in me office...";
            break;
        case "champion":
            command("grin");
            return "The champion is the brewer o' the champion brew... "+
                    "the best in all the vault as decided by experts each month... "+
                    "champions get grails as prizes when I sees 'em... "+
                    "Their name is in me office.";
            break;
        case "ninkasi":
            command("grin faintly");
            return "Well I'm sure I don't know anything about her... "+
                    "I mean that... I don't know anything about that!";
            break;
        case "grail":
            command("smile warm");
            return "Every little while I award one of me special grails for the champion brew... "+
                    "they be funny lookin' but folks seem to like 'em.";
            break;
        case "royalties":
            command("nod agree");
            return "If'n you e'er be owed anythin'... " +
              "I'll be sure to give'it ya... that's a promise.";
            break;
        case "armour":
            command("smell"); 
            return "Armours full o' nooks n' crannies, full o' culture, all lived in... "+
                   "the best culture comes from the oldest armour...  diffr'nt bits grow "+
                   "diffr'nt culture for diffr'nt styles of brew... "+
                   " I like a tasty stout m'self... "+
                   "cultured from feet kept in boots through a long grinding march.";
            break;
        case "vault":
            command("emote peers thoughtfully to the east.");
            return "The vault is where we keep all them barrels... " +
                  "its dark and twisty in there... best not venture " +
                  "there if you don't know what you are about.";
            break;
        case "monster":
            command("ponder");
            return "Monster? Monster you say? Well the vault is a big place, "+
                   "even I don't know it all that well.";
            break;
        case "beers":
            return "There's a list of barrels by tier-number in me office...";
            break;
        case "office":
            command("emote points north");
            return "Me office?... just a short stagger from 'ere.";
            break;
        case "brew":
            command("emote scratches her chin."); 
            return "Well if ye be interested learnin' brewin'... "+
                   "first ye need to test your brew culture."; 
            break;
        case "culture":
            command("peer at " + OB_NAME(TP)); 
            return " to " + OB_NAME(TP) + " I suppose I could try yer out... <culture> you..."+
                   " yer might ave somefin tasty on yer... it takes about a moon after that"+
                   " to know fer sure... of course yer know about armour?"; 
            break;
        case "sample":
            command("grin"); 
            return "You can <sample> any of the brews in the vault... "+
                   "just need a barrel-tier number from me office."; 
            break;
    }
}


brewcrafter_default_answer()
{
    command("say " + ask_brewcrafter("no_info"));
    return "";
}


void
create_krynn_monster()
{
    if(!IS_CLONE)
        return;

    set_name( BRWCNAME );
    set_living_name( BRWCNAME );
    set_title(BRWCTITL);
    set_race_name("dwarf");

    set_adj("venerable");
    set_adj("green-eyed");
    add_adj("red-haired");
    add_adj("sharp-nosed");

    set_gender(1);  // female

    add_prop(NPC_I_NO_LOOKS, 1);
    add_prop(CONT_I_HEIGHT, 95);

    set_long("Before you, a venerable she-dwarf is busy directing and supervising all the brewing "+
             "that takes place in Iron Delving. Also venerable is her armour and its odour; " +
             "perhaps crafted in an earlier age, certainly not removed for any length of time nor "+
             "ever exposed to the ravages of soap and water. "+
             "All the many dwarves hereabouts show her great "+
             "deference; following her instructions asiduously and with an excited energy. " +
             "Ever keen to expand the brewery's line of "+
             "award-winning beers, her green-eyes and sharp nose are quick to appraise "+
             "visitors' brewing potential. She stands with a brace of sample vials.\n");

    set_short("venerable she-dwarf");

    set_act_time(30);
    add_act("@@say_offer_opinion");
    add_act("@@say_keepin_clean");
    add_act("@@say_living_culture");
    add_act("@@say_onto_something");
    add_act("@@say_barrel_direct");

    trig_new("%w 'introduces' %s","react_to_intro");

    set_default_answer("@@brewcrafter_default_answer");

    add_ask(({"goblin","goblins"}), "say " + "@@ask_brewcrafter|goblin@@", 1);
    add_ask(({"tunnel","bootleg tunnel"}), "say " + "@@ask_brewcrafter|tunnel@@", 1);

    add_ask("ninkasi", "say " + "@@ask_brewcrafter|ninkasi@@", 1);
    add_ask("grail", "say " + "@@ask_brewcrafter|grail@@", 1);
    add_ask("armour", "say " + "@@ask_brewcrafter|armour@@", 1);
    add_ask("monster", "say " + "@@ask_brewcrafter|monster@@", 1);
    add_ask("office", "say " + "@@ask_brewcrafter|office@@", 1);

    add_ask(({"champion", "championship brew", "championship"}), "say " + 
                 "@@ask_brewcrafter|champion@@", 1);
    add_ask(({"export", "export brew"}), "say " + 
                 "@@ask_brewcrafter|export@@", 1);

    add_ask(({"royalty","royalties","reward","rewards"}), "say " + 
                 "@@ask_brewcrafter|royalties@@", 1);
    add_ask(({"vault","barrel vault","great barrel vault","maze"}), "say " + 
                  "@@ask_brewcrafter|vault@@", 1);
    add_ask("beers", "say " + "@@ask_brewcrafter|beers@@", 1 );
    add_ask(({"brew","brew beer","brewing","learn","teach","potential"}), "say " + 
               "@@ask_brewcrafter|brew@@",1);
    add_ask(({"brew culture","secret","culture","yeast","odour"}), "say " + 
                "@@ask_brewcrafter|culture@@",1);
    add_ask(({"beer","sample","taste","vials","sample vials","vial"}), "say " + 
                 "@@ask_brewcrafter|sample@@",1);

    set_alignment(100);

    set_stats(({90,160,400,400,400,200}));
    set_hp(query_max_hp());

    add_prop(OBJ_I_NO_ATTACK, "@@no_attack");
    add_prop(OBJ_I_NO_MAGIC, 1);
    add_prop(OBJ_I_NO_DROP, 1);
    add_prop(OBJ_I_NO_GIVE, 1);
    add_prop(OBJ_I_NO_GET, 1);
    add_prop(OBJ_I_NO_STEAL, 1);
    add_prop(OBJ_I_NO_TELEPORT, 1);
    add_prop(OBJ_I_NO_BUY, 1);
    add_prop(OBJ_I_NO_SELL, 1);
    add_prop(NPC_I_NO_RUN_AWAY,1);
    add_prop(NPC_M_NO_ACCEPT_GIVE,1);

    remove_prop(LIVE_I_NEVERKNOWN);

    // array used in culturing brew
    armourloc = allocate(8);
    armourloc[0] = TS_ROBE;
    armourloc[1] = TS_HEAD;
    armourloc[2] = TS_RARM;
    armourloc[3] = TS_CHEST;
    armourloc[4] = TS_WAIST;
    armourloc[5] = TS_LEGS;
    armourloc[6] = TS_RHAND;
    armourloc[7] = TS_RFOOT;

    setuid();
    seteuid(getuid(TO));
}

public void
react_offensive()
{
    command(one_of_list( ({
        "say A wise dwarf once said, don't piss off someone who brews beer...",
        "say I am a humble brewer... and not deserving of that",
        "say You are cut off, ye ungrateful wretch.",
        "say Errr ...",
        }) ));
} 

public void
react_ingratiatory()
{
    command(one_of_list( ({
        "say Well now, ye don' often see that kind of thing here...",
        "say Oh my... I am but a humble brewer",
        "say You are too kind.",
        "say Errr ...",
        }) ));
} 

public void
emote_hook(string emote, object actor, string adverb, object *oblist,     
           int cmd_attr, int target)
{
    if (ACTION_INGRATIATORY & cmd_attr)
    {
        react_ingratiatory();
        TP->remove_prop(BREWER_I_HAS_GIVEN_OFFENCE,1);
    }
    if (ACTION_THREATENING & cmd_attr)
    {
        react_offensive();
        TP->add_prop(BREWER_I_HAS_GIVEN_OFFENCE,1);

    }
    if (ACTION_OFFENSIVE & cmd_attr)
    {
        react_offensive();
        TP->add_prop(BREWER_I_HAS_GIVEN_OFFENCE,1);
    }
    if (ACTION_INTIMATE & cmd_attr)
    {
        react_ingratiatory();
        TP->remove_prop(BREWER_I_HAS_GIVEN_OFFENCE,1);
    }
} 

void
intro_me(string who)
{
    who = L(who);
    if (P(who,E(TO)))
    {
       command("introduce myself");
    }
}

void
react_to_intro(string who,string garbage)
{
    set_alarm(1.0,0.0,"intro_me",who);
    TP->add_prop(BREWER_I_HAS_MADE_INTRO,1);
}

/*
 * filter function for armour locations
 *   in get_culture()
 */
int
culture_slot( int islot )
{
    return (member_array(islot,armourloc) != -1);
}


int
get_culture(object brewer)
{
    int ni, ii, i100;
    int *islot;
    int nsl, isl, iripesc, iripelc, iloc;
    int icond, iworstloc, iworstcond;
    int iBeerType;
    string wornloc, whisper, tongs;
    string str;
    object *inv;
    object wearer;

    if (!interactive(brewer)) return -2;

    str = "";
    iworstloc = -1;
    iworstcond = -1;

    inv = all_inventory(brewer);
    ni = sizeof(inv);

    for (ii=0;ii<ni;ii++)
    {
       if (inv[ii]->query_wearable_item())
       {
           if ( inv[ii]->query_at() == A_SHIELD ) continue;

           // is the armour being worn?
           wearer = inv[ii]->query_worn();
           if ( !wearer ) continue;
           if (OB_NAME(brewer) != OB_NAME(wearer)) continue;

           icond = inv[ii]->query_condition();
           if ( icond > iworstcond )
           {
               iworstcond = icond;

               // loop through valid culture slots
               // under worst item of armour and
               // randomly select one of the
               // slots it covers
  
               islot = filter(inv[ii]->query_slots(),culture_slot);
               nsl = sizeof(islot);

               iripesc = -1;

               for (isl=0;isl<nsl;isl++)
               {
                   iloc = islot[isl];
                   wornloc = inv[ii]->wear_how(iloc);

                   if (strlen(wornloc)>0)
                   {
                       i100 = random(100);
                       if ( i100 > iripesc )
                       {
                           iripesc = i100;
                           iripelc = iloc;
                       } 
                       str = sprintf("%s... %s under your %s",
                          str,wornloc,inv[ii]->query_short());
                   } // if worn

               } // isl

               iworstloc = iripelc;
 
           } // if icond > iworstcond

       } // if wearable
    } // ii

    tongs = "suddenly produces a very long pair of "+
            "copper tongs clasping a ragged old cloth";

    if ( strlen(str) > 0 ) 
       str = sprintf("%s %s and proceeds to swab you; swabbing %s\n",
                         QCTNAME(this_object()),tongs,str);
    else
       str = sprintf("%s %s and proceeds to swab you; all over!\n",
                         QCTNAME(this_object()),tongs);

    TP->catch_msg(str);
    tell_room(environment(brewer),QCTNAME(TO) + " " + tongs + 
               " and swabs all over " + QTNAME(brewer) + ".\n",brewer);

    // use worst condition armour location to choose beertype
    // ... ie. where is the mankiest yeast?
    iBeerType = member_array(iworstloc,armourloc);

    if ( iBeerType < 0 ) 
        whisper = "you come here cleanly sweetheart, you have no brew culture I can work with...";
    else
        whisper = sprintf("hmmm, you may well have the yeasty makings of a fine %s here...",
                 BEERTYPES[iBeerType]);

    tell_room(environment(brewer), QCTNAME(TO)
         + " sniffs her tong-rag critically, before inserting it in a copper tube at her belt.\n");

    whisper = sprintf("whisper to %s %s",brewer->query_real_name(), whisper);
    command(whisper);

    return iBeerType;
}


int
culture_it( string str )
{
    int beerindex;
    int newbrewflag;
    string brewername, brewerrace;
    int breweralign;
    int questbrewer;

    if ( cannot_see_speaker() ) return 0;

    if(!strlen(str) || str != "me")
    {
        write("Culture what? Culture you?\n");
        return 1;
    }

    if (!(TP->query_prop(BREWER_I_HAS_MADE_INTRO)))
    {
        command("say to " + OB_NAME(this_player())
                 + " Who exactly might you be sweetie? ... before we get to any o' that."); 
        command("emote raises a red eyebrow.");
        return 1;
    }

    if (TP->query_prop(BREWER_I_HAS_GIVEN_OFFENCE))
    {
        command("say to " + OB_NAME(this_player())
                 + " I aint brewin' nought from you -- yer good fer nothin'."); 
        return 1;
    }

    // attempt to add new brew

    command("say to " + OB_NAME(this_player())
          + " Very well! Let's examine your brewing culture..."); 

    beerindex = get_culture(TP);
    if ( beerindex < 0 ) return 1;

    brewername = TP->query_real_name();
    brewerrace = TP->query_race();
    breweralign = TP->query_alignment();
    questbrewer = is_a_brewquester(TP);
    
    newbrewflag = BREWCRAFT->add_newbeer(brewername,brewerrace,breweralign,
                     beerindex,questbrewer);

    switch ( newbrewflag )
    {
        case 0:
            command("say to " + OB_NAME(this_player())
              + " Ere, hang-on! You already got a brew culture in the works right now! "
              + "It'll be ready for samplin' and judgin' at next moon... then we can "
              + "try brewin' something else."); 
            return 1;
            break;
        case 1:
            command("say to " + OB_NAME(this_player())
              + " Leave it with me, we'll make what we can o' yer culture... "
              + "come back at the next moon (about 24 hours in Nether reckoning) "
              + "an' we'll see if anything turns up."); 
            command("emote summons a dwarf to retrieve the copper tube " 
              + "and carry it out of sight in the great brew chamber.");
            return 1;
            break;
        default:
            command("say to " + OB_NAME(this_player())
              + " Something aint quite right with you and me and the fabric of space!"
              + " Go tell the Wizard Vitwitch that things are awry!");
            return 0;
            break;
    }
}


void
sample_comment( int score )
{
    command( "say Well, that was " + BREWCRAFT->brew_opinion(score) + "... don't yer think?");
    if ( score < 400 )
    {
        command( "emote tosses her sample vial away with a shudder.");  
    }
    else
    {
        command( "emote tosses her sample vial away with a smile.");  
    }
}


void
sample_reaction( int balign )
{
    int palign;
    float feff;

    palign = TP->query_alignment();

    feff = itof(palign) * itof(balign) / 100000.0;

    if ( feff < 0.0 )
        TP->catch_msg("You feel an unhappy rumbling within your belly.\n\n");
    else
        TP->catch_msg("You feel a happy burbling within your belly.\n\n");
}


void
sample_taste( string tastestr )
{
    TP->catch_msg("\nYou and " + QTNAME(this_object()) + " taste your sample vials together.\n\n");
    tell_room(environment(TP),
        QCTNAME(this_object()) + " and " + QTNAME(TP) + " down their sample vials.\n", TP);
    TP->catch_msg( tastestr );
}


int
try_sample(string short, string taste, int align, int score )
{

    tell_room(environment(TO),
    "\nA dwarf assistant hurries up to " + QTNAME(TO) + " and gives her vials of brew, "+
    "fresh-tapped from a barrel within the vault.\n\n");

    if ( environment(TP) != environment(TO) )
    {
        command("emote peers about for the missing taste tester."); 
        command("emote shrugs and while downing both vials herself.");
        return 1;
    }

    TP->catch_msg( QCTNAME(TO) + " gives you a vial of " + short + ".\n");

    tell_room(environment(TO),
        QCTNAME(TO) + " gives " + QTNAME(TP) + " a vial of brew.\n",TP);

    set_alarm(2.0,0.0,&sample_taste(taste));
    set_alarm(4.0,0.0,&sample_reaction(align));
    set_alarm(6.0,0.0,&sample_comment(score));

    return 1;
}


int
sample_it(string catalog_str)
{
    string *ind;
    int catalog;
    int loaded;
    int badref;
    string ts;
    string BrwrName, BrwrRace, SmplrName, short, tastestr, fmtstr;
    int Score, BeerIndex, Again, Align;

    if ( cannot_see_speaker() ) return 0;

    SmplrName = TP->query_real_name();

    if (!(TP->query_prop(BREWER_I_HAS_MADE_INTRO)))
    {
        command("say to " + OB_NAME(this_player())
                 + " Who exactly might you be sweetie? ... before we get to any o' that."); 
        command("emote raises a red eyebrow.");
        return 1;
    }

    if (TP->query_prop(BREWER_I_HAS_GIVEN_OFFENCE))
    {
        command("say to " + OB_NAME(this_player())
                 + " I aint got no samples fer you -- yer ungrateful good fer nothin'."); 
        return 1;
    }

    badref = (!catalog_str || !sscanf(catalog_str,"%d",catalog));
    badref = ( badref || catalog < 1000 );

    if ( badref ) 
    {
        loaded = BREWCRAFT->load_sample();
    }
    else
    {
        loaded = BREWCRAFT->load_sample(catalog);
    }

    if ( badref || loaded != catalog )
    {
        command("grin");
        command("say to " + OB_NAME(this_player())
                + " I don't know what you want to sample... so I'll choose some'int");
        command("ponder");
    }

    Align = BREWCRAFT_ALIGNZ;
    Score = BREWCRAFT_SCOREZ;
    BrwrName = BREWCRAFT_NAMEZ;

    if ( BrwrName == SmplrName )
        short = "your brew";
    else
        short = capitalize(BREWCRAFT_SHORTZ);
 
    command("say to " + OB_NAME(this_player())
         + " Very well... let's sample " + short + ".\n");

    tell_room(environment(TP),
        QCTNAME(this_object()) + " sends an assistant with empty vials to the barrel vault " +
        "to fetch some brew.\n");

    fmtstr = "You appraise your sample of %s, "+
             "tasting %s on the way down...\n" +
             "leaving your palate with a faint but lingering flavour of %s.\n\n";

    tastestr = sprintf(fmtstr,
                    BREWCRAFT_STYLEZ,
                    BREWCRAFT_TASTEZ,
                    BREWCRAFT_AFTERTASTEZ);

    set_alarm(15.0,0.0,&try_sample(short,tastestr,Align,Score));

    return 1;
}


int
reward_due( object player )
{
    int iexport, ichampion;
    string PlyrName;
    object grail, coins;

    PlyrName = player->query_real_name();

    iexport =  BREWCRAFT->brewcraft_export_royalty(PlyrName);
    ichampion =  BREWCRAFT->brewcraft_champions_royalty(PlyrName);

    if ( iexport )
    {
        coins = MONEY_MAKE_PC(EXPORT_PLAT_ROYALTY);
        coins->move(TO);
        command("give coins to " + OB_NAME(player));
        if (environment(coins) == TO) 
        {
            command("say Oops...");
            command("drop coins");
        }
    }

    if ( ichampion )
    {
        grail = clone_object(BREWCRAFT_GRAIL);
        grail->move(TO);
        command("give grail to " + OB_NAME(player));
        if (environment(grail) == TO)
        {
            command("say Oops... it's a heavy one");
            command("drop grail");
        }
    }

    return min(1,(iexport+ichampion));
}


void
init_living()
{
    ::init_living();
    add_action("culture_it","culture");
    add_action("sample_it","sample");
}

