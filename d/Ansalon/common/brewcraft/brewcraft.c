/* 
 *  BREWCRAFT daemon for the Iron Delving Brewery
 *  serving Ansalon and Krynn and anywhere else
 *  /d/Ansalon/common/brewcraft/brewcraft.c
 *
 *  this object provides the functionality
 *  for craft brewing and distribution 
 *
 *  Vitwitch 01/2021
 */

#pragma no_clone
#pragma no_inherit
#pragma strict_types

inherit "/std/object";

#include "brewcraft.h"
#include "/d/Ansalon/common/defs.h"
#include <stdproperties.h>
#include <macros.h>
#include <math.h>
#include <time.h>
#include <mail.h>
#include <language.h>

#define BREWCRAFT_PATH "/d/Ansalon/common/brewcraft/"
#define NEWBEERMAP "newbeermap"
#define TOPNTAPMAP "topntapmap"

/* GLOBAL VARIABLES */

// Storage maps
mapping newbeermap;
mapping topntapmap;

// Ranking map
static mapping brewermap;
static mapping notifymap;

// Beer characteristics
static string *gBeerType = BEERTYPES;
static string *gBeerTaste = BEERTASTES;
static string *gBeerColour = BEERCOLOURS;

// Brewer/Brew determinants
static int gQuesterScoreBonus = 3000;
static int gMaxRawScore = 1000;
static int gAgingFactor = 3;
static int gReserveAge = 60;
static int gLostAge = 90;
static int gTimeNow; 
static int gQuesterExporter;
static int gExportRoyaltyPaid = 0;
static int gChampionsRoyaltyPaid = 0;
static int gNIdx = 3;
static int gIdxTap = 0, gIdxTop = 1, gIdxRnd = 2, gIdxSmp = 3;  
static int *gRawScore = ({0,0,0,0}),
           *gBeerIndex = ({0,0,0,0}),
           *gBeerTime = ({0,0,0,0}),
           *gAlign = ({0,0,0,0});
static string *gBrwrName = ({"","","",""}), 
              *gRace = ({"","","",""});

/* PROTOTYPES */
void update_maps();
void get_newbeermap();
void put_newbeermap();
void get_topntapmap();
void put_topntapmap();
void notify_newchamp_brewer();
void notify_export_brewer();
void notify_brewer( string brwrname, int beerindex, int in, int nn );
string brew_colour( int beerindex );
string brew_adverb( int score );
string brew_ageadj( int beertime );
string brew_opinion( int score );
string brew_improvement( int rawscore, int beertime );
string brew_smell( string race );
string brew_taste( int beerindex, string adverb );
string brew_aftertaste( string race );
string brewer_honorific( int brwrscore );
int overaged( int beertime );
int aged_score( int rawscore, int beertime );
public int brewcraft_export_quester();
public int add_newbeer( string bname, string brace, int balign,
  int bindex, int quester );
public string brewer_list();
public string type_list();
public string brew_list();
public int brewcraft_export_royalty( string brwrname );
public int brewcraft_champions_royalty( string brwrname );
public varargs string brewcraft_brewer_name(int i);
public varargs string brewcraft_brewer_race(int i);
public varargs string brewcraft_beer_colour(int i);
public varargs string brewcraft_beer_taste(int i);
public varargs string brewcraft_beer_aftertaste(int i);
public varargs string brewcraft_beer_smell(int i);
public varargs int brewcraft_brew_score(int i);
public varargs string brewcraft_brew_type(int i);
public varargs int brewcraft_brewer_align(int i);
public varargs string brewcraft_long(int i);
public varargs string brewcraft_short(int i);
public varargs string brewcraft_menuentry(int i);
public varargs int load_sample(int catalog);


/* FUNCTIONS */

void
create_object()
{
    set_name( "brewcraft" );
    add_name( "irondelving brewcraft" );

    set_adj("Ansalon");
    set_short("IronDelving Brewcraft");
    set_long("This is the brewcraft daemon for Ansalon and Krynn.\n");

    setuid();
    seteuid(getuid(TO));

    // update beer maps every Krynn month (24 hours IRL)
    set_alarm(1.0, 86400.0, update_maps);
}


void
notify_newchamp_brewer()
{
    string contents;
    string brwrname = gBrwrName[gIdxTop];
    string beertype = gBeerType[gBeerIndex[gIdxTop]];

    contents = "Your " + capitalize(beertype) + " has been"+
               " recognised as the\n"+
               "    ----<   CHAMPIONSHIP BREW   >----\n"+
               "of all Iron Delving, and hence all the\n"+
               "Realms themselves! You can collect your\n"+ 
               "special royalty from the Brewcrafter at\n"+
               "the start of each month in Krynn, while\n"+
               "you retain the championship.";

    CREATE_MAIL("You are our CHAMPION Brewer!", "IDBrewery",
                brwrname, "",
                "========================================================="
              + "======================\n"
              + "Greetings " + capitalize(brwrname) + "!\n\n"
              + contents + "\n\n"
              + "IDB Judging Panel\n"
              + "========================================================="
              + "======================\n\n");

    return;
}


void
notify_export_brewer()
{
    string contents;
    string brwrname = gBrwrName[gIdxTap];
    string beertype = gBeerType[gBeerIndex[gIdxTap]];

    if ( gQuesterExporter ) 
    {
        contents = "Your " + capitalize(beertype) + " has been"+
               " selected as the\n"+
               "           ---- EXPORT BREW ---- \n"+
               "from Iron Delving for all this Krynnish month.\n"+
               "The Brewcrafter loves a fresh culture borne in\n"+
               "by a quest. Hurry to can toast your beginners luck\n"+
               "in brewing with ole' Rusty at the Inn of the Last Home!";
    }
    else
    {
        contents = "Your " + capitalize(beertype) + " has been"+
               " selected as the\n"+
               "           ---- EXPORT BREW ---- \n"+
               "from Iron Delving for all this Krynnish month.\n"+
               "Hurry to collect your export royalty from\n"+
               "from the Brewcrafter before the end of the\n"+
               "the month! You can toast your brewing prowess\n"+
               "with friends wherever good beer is sold!";
    }

    CREATE_MAIL("You are our EXPORT Brewer!", "IDBrewery",
                brwrname, "",
                "========================================================="
              + "======================\n"
              + "Greetings " + capitalize(brwrname) + "!\n\n"
              + contents + "\n\n"
              + "IDB Judging Panel\n"
              + "========================================================="
              + "======================\n\n");

    return;
}


void
notify_brewer( string brwrname, int beerindex, int in, int nn )
{
    string contents;
    string beertype = gBeerType[beerindex];
    int ord = nn - in;
    
    if ( gQuesterExporter ) 
    {
        contents = "A " + capitalize(beertype) + " has been"+
               " brewed from your yeasty culture.\n" +
               "Of the "+
               LANG_NUM2WORD(nn) + " cultures brewed this month,\n"+
               "yours was judged in " + LANG_ORD2WORD(ord) + " place.\n"+
               "Don't be downhearted, we suspect the Number One\n"+
               "brewer this month benefitted from beginners luck.\n"+
               "We recommend you sample the brews from the barrels\n"+
               "list in Brewcrafters office. We recommend that brewers\n"+
               "with horrible or ordinary products should try a\n" +
               "different beer style next month.\n";
    }
    else
    {
        contents = "A " + capitalize(beertype) + " has been"+
               " brewed from your yeasty culture.\n" +
               "Of the "+
               LANG_NUM2WORD(nn) + " cultures brewed this month,\n"+
               "yours was judged in " + LANG_ORD2WORD(ord) + " place.\n"+
               "We recommend you sample the *fresh* brews\n"+
               "from the barrels list in Brewcrafters office\n"+
               "to compare with your fellows' fresh efforts.\n"+
               "We always recommend that brewers with horrible\n"+
               "or ordinary products should try a different beer\n"+
               "style next month.\n";
    }

    CREATE_MAIL("Brew Culture Judgment", "IDBrewery",
                brwrname, "",
                "========================================================="
              + "======================\n"
              + "Greetings " + capitalize(brwrname) + "!\n\n"
              + contents + "\n\n"
              + "IDB Judging Panel\n"
              + "========================================================="
              + "======================\n\n");

    return;
}


void
update_maps()
{
    int score, qscore;
    int ib, nb, tt, catalog, ns, is, nt, it, in, nn;
    int topscore, tapscore, dwfscore, absscore;
    int beerindex, brwralign;
    int nbeer_type, int1, int2, int3;
    int beertime, found_new_champion;
    int brewquester;
    float b1111;
    string topindex, tapindex, dwfindex, absindex;
    string brwrname, brwrrace, str, ts;
    string scorestr;
    string *loadindex;
    mixed indb, valb, indt, indtp, idxs, indn; 

    nbeer_type = sizeof(gBeerType);

    get_newbeermap();
    get_topntapmap();

    indb = m_indexes(newbeermap);
    valb = m_values(newbeermap);

    tapindex = "-1";
    tapscore = -1;

    notifymap = ([]); 

    nb = sizeof(indb);
    for (ib=0;ib<nb;ib++)
    {
        if ( wildmatch("*_*",indb[ib]) ) continue;

        // unpack the newbeermap value string 

        if ( (sscanf(valb[ib],"%d | %d | %d | %s",
                beerindex,beertime,brwralign,brwrrace) != 4) )
        {
            // exception
            write("There is a strangeness in the spacetime fabric of brewing?!\n");
            return;
        } 

        brewquester = 0;

        if ( beerindex < 0 ) 
        {
            // invalid beerindex used to signify a quester-brewer
            // but needs correction before further use and
            // entry into the topntapmap 
            beerindex = beerindex + 10; 
            brewquester = 1;
        }

        if ( beerindex < 0 || beerindex > nbeer_type ) 
        {
            write("There is a strangeness in the spacetime fabric of beer itself!\n");
            return;
        }

        catalog = NAME_TO_RANDOM(indb[ib],999,999) + ( beerindex + 1 ) * 1000; 

        // new beers have no aging addition to score 
        b1111 = sqrt(itof(beerindex * 11111111111));
        score = NAME_TO_RANDOM(indb[ib],ftoi(b1111),gMaxRawScore);
        // used to be 8/2 ... now 5/5
        score = ( 5 * score + 5 * random(gMaxRawScore) ) / 10;

        // questers get a bonus to help them get selected
        qscore = score + brewquester * gQuesterScoreBonus;
        if ( qscore > tapscore )
        {
           tapscore = qscore;
           tapindex = val2str(catalog);
        }

        notifymap[score] = val2str(catalog);

        topntapmap[val2str(catalog)] = sprintf("%s | %d | %d | %d | %d | %s",
              indb[ib],score,beerindex,beertime,brwralign,brwrrace);
    }


    // delete all but null brew
    for (ib=0;ib<nb;ib++)
        if ( !wildmatch("*_*",indb[ib]) )
            newbeermap = m_delete(newbeermap,indb[ib]);

    put_newbeermap();


    // find top scoring brew, find random +ve align brew for dwarves,
    // delete over-age brews and generate brewermap

    brewermap = ([]); 

    gTimeNow = time();

    indt = m_indexes(topntapmap);
    nt = sizeof(indt);

    for ( absscore=-1,dwfscore=-1,topscore=-1,it=0;it<nt;it++ )
    {
        ts = indt[it];
        if( sscanf(topntapmap[ts],"%s | %d | %d | %d | %d | %s",
           brwrname,score,beerindex,beertime,brwralign,brwrrace) != 6 )
        {
            // exception
            write("There is a strangeness in the spacetime fabric "+
                     "of the brewery?!\n");
            return;
        }

        score = aged_score( score, beertime );

        if ( score > absscore ) 
        {
            absscore = score;
            absindex = ts;
        }

        if ( overaged(beertime) )
            topntapmap = m_delete(topntapmap,ts);
        else
        { 
            if ( score > topscore ) 
            {
                topscore = score;
                topindex = ts;
            }

            if (!brewermap[brwrname])
                brewermap[brwrname] = 0;
            brewermap[brwrname] += score;

            if ( brwralign > 100 ) 
            {
                score = random(100);
                if ( score > dwfscore )
                {
                    dwfscore = score; 
                    dwfindex = ts; 
                }
            }

        } // not over-aged
    }

    indtp = m_indexes(topntapmap);

    // if new beer map was empty...
    // use random selection from topntapmap for export
    if ( tapscore == -1 )
        tapindex = indtp[random(sizeof(indtp))];

    // record if export brewer was a quester
    gQuesterExporter = 0;
    if ( tapscore > gQuesterScoreBonus ) 
        gQuesterExporter = 1;

    // if no +ve align brew was found for dwarves,
    // they get whatever...
    if ( dwfscore == -1 ) 
        dwfindex = indtp[random(sizeof(indtp))];
 
    loadindex = allocate(gNIdx);
    loadindex[gIdxTap] = tapindex;          // export
    loadindex[gIdxTop] = topindex;          // top of all
    loadindex[gIdxRnd] = dwfindex;          // random +ve align, for dwarves

    // load selectable beers into arrays for regular use
    // note: tt==gIdxSmp --> reserved for taste sampling
    for (tt=0;tt<gNIdx;tt++) 
    {
        if( (sscanf(topntapmap[loadindex[tt]],"%s | %d | %d | %d | %d | %s",
       gBrwrName[tt],gRawScore[tt],gBeerIndex[tt],gBeerTime[tt],gAlign[tt],gRace[tt]) != 6) )
        {
            // exception
            write("There is a strangeness in the spacetime fabric of the brewery?!\n");
            return;
        }
    }

    gExportRoyaltyPaid = 0;
    gChampionsRoyaltyPaid = 0;

    put_topntapmap();

    // notify brewers of the outcomes of this round

    found_new_champion = ( absscore != topscore );

    indn = m_indexes(notifymap);
    nn = sizeof(indn); 
    if ( nn > 0 ) 
    {
        idxs = sort_array(indn);

        if ( idxs[nn-1] == topscore ) 
            found_new_champion = 1;

        for (in=0;in<nn-1;in++) 
        {
            ts = notifymap[idxs[in]];
            if( sscanf(topntapmap[ts],"%s | %d | %d | %d | %d | %s",
              brwrname,score,beerindex,beertime,brwralign,brwrrace) != 6 )
            {
            // exception
            write("There is a strangeness in the fabric "+
                     "of brewery notifications?!\n");
            return;
            }
            notify_brewer( brwrname, beerindex, in, nn );
        }
    }

    notify_export_brewer();

    if ( found_new_champion ) 
        notify_newchamp_brewer();

    return;

}


public varargs int
load_sample(int catalog)
{
    int i;
    string ts;
    mixed ind;

    get_topntapmap();
    ind = m_indexes(topntapmap);

    if ( !catalog )
        ts = ind[random(sizeof(ind))]; 
    else 
    {
        ts = val2str(catalog);
        if ( member_array(ts,ind) == -1 ) 
        {
            ts = ind[random(sizeof(ind))]; 
            catalog = 0;
        }
    }

    i = gIdxSmp;
    if ( (sscanf(topntapmap[ts],"%s | %d | %d | %d | %d | %s",
        gBrwrName[i],gRawScore[i],gBeerIndex[i],gBeerTime[i],gAlign[i],gRace[i]) != 6) )
    {
        // exception
        write("There is a strangeness in the spacetime fabric of the brewery?!\n");
        return 0;
    }

    return catalog;
}


public int
add_newbeer( string brewername, string brewerrace, int breweralign, int beerindex, int quester )
{
    int myalign;
    string *oldnames;
    int ibdx, ibalign;
    string bwrace;

    if ( !brewername ) return -1;
    if ( !brewerrace ) return -1;
    if ( beerindex < 0 ) return -1;

    get_newbeermap();

    oldnames = m_indices(newbeermap);

    if ( member_array(brewername,oldnames) == -1 ) 
    { 
        // add/update entry to newbeermap

        if ( quester ) beerindex = beerindex - 10;
        newbeermap[brewername] = sprintf("%d | %d | %d | %s",
                       beerindex,time(),breweralign,brewerrace);

        put_newbeermap();

        return 1;
    }
    else
        return 0;
}


void
get_newbeermap()
{
   setuid();
   seteuid(getuid());
   newbeermap = restore_map( BREWCRAFT_PATH + NEWBEERMAP );
   return;
}

void
get_topntapmap()
{
   setuid();
   seteuid(getuid());
   topntapmap = restore_map( BREWCRAFT_PATH + TOPNTAPMAP );
   return;
}

void
put_newbeermap()
{
   setuid();
   seteuid(getuid());
   save_map( newbeermap, BREWCRAFT_PATH + NEWBEERMAP );
   return;
}

void
put_topntapmap()
{
   setuid();
   seteuid(getuid());
   save_map( topntapmap, BREWCRAFT_PATH + TOPNTAPMAP );
   return;
}

string
brewer_honorific( int brwrscore )
{
    string str;
    int rank = brwrscore / 400;

    switch (rank)
    {
        case 0..1:
        str = "raw Freshslater";
        break;

        case 2..3:
        str = "bold Petridisher";
        break;

        case 4..5:
        str = "respected Ripentender";
        break;

        case 6..7:
        str = "esteemed Culturemaven";
        break;

        default:
        str = "overwhelming Yeastsovereign";
    }

    return str;
}

public string
brewer_list()
{
    string str;
    int n, i;
    mixed ind, idx;

    ind = m_indices(brewermap);
    idx = sort_array(ind);

    n = m_sizeof(brewermap);

    str = "";

    for (i=0;i<n;i++)
    {
        str = sprintf( "%s %-15s... %15s\n", str, capitalize(idx[i]), 
            brewer_honorific(brewermap[idx[i]]) );
    }

    return str;
}


public string
type_list()
{
    string str;
    int n, i;

    n = sizeof(gBeerType);
    str = "";

    for (i=0;i<n;i++)
    {
        str = sprintf("%s\n %s",str,capitalize(gBeerType[i]));
    }
 
    return str;
}


public string
brew_list()
{
    string str, bstr;
    mixed ind, idx;
    int n, i;
    string BrwrName, BrwrRace;
    int RawScore, BeerIndex, BeerTime, Align;

    get_topntapmap();

    ind = m_indices(topntapmap);

    n = sizeof(ind);
    idx = sort_array(ind);
    str = "";

    for (i=0;i<n;i++)
    {
        if ( (sscanf(topntapmap[idx[i]],"%s | %d | %d | %d | %d | %s",
            BrwrName,RawScore,BeerIndex,BeerTime,Align,BrwrRace) == 6) )
        {
            bstr = sprintf("%s's %s", capitalize(BrwrName),capitalize(gBeerType[BeerIndex]));
            str = sprintf("%s\n Tier:%s -- %26s  (%s)",
                  str,idx[i],bstr, brew_ageadj(BeerTime) );
        }
    }
 
    return sprintf("%s\n\n --Old Reserve stocks may run out at any time --\n",str);
}

string
brew_colour( int beerindex )
{
    return gBeerColour[beerindex];
}

public varargs string
brewcraft_beer_colour(int i)
{
    return brew_colour(gBeerIndex[i]);
}

string
brew_taste( int beerindex, string adverb )
{
    return sprintf("%s brewed %s",adverb,gBeerTaste[beerindex]);
}

public varargs string
brewcraft_beer_taste(int i)
{
    return brew_taste(gBeerIndex[i],brew_adverb(aged_score(gRawScore[i],gBeerTime[i])));
}


string
brew_aftertaste( string race )
{
    string str;

    switch (race)
    {
        case "goblin":
        str = "ash and blood";
        break;

        case "human":
        str = "sweat and tears";
        break;

        case "dwarf":
        str = "steel and stone";
        break;

        case "elf":
        str = "forest greenery";
        break;

        case "gnome":
        str = "mineral oil";
        break;

        case "hobbit":
        str = "sweet smoke";
        break;

        default:
    }
    return str;
}

public varargs string
brewcraft_beer_aftertaste(int i)
{
    return brew_aftertaste(gRace[i]);
}


string
brew_smell( string race )
{
    // for now, can be varied
    return brew_aftertaste( race );
}

public varargs string
brewcraft_beer_smell(int i)
{
    return brew_smell(gRace[i]);
}


string
brew_adverb( int score )
{
    string adv;

    switch (score)
    {
        case 0..250:
        adv = "piss-weakly";
        break;

        case 251..500:
        adv = "weakly";
        break;

        case 501..750:
        adv = "skillfully";
        break;

        case 751..900:
        adv = "superbly";
        break;

        default:
        adv = "mythically";
        }
    return adv;
}


string
brew_opinion( int score )
{
    string appellation;

    switch (score)
    {
        case 0..250:
        appellation = "horrible";
        break;

        case 251..500:
        appellation = "ordinary";
        break;

        case 501..750:
        appellation = "superior";
        break;

        case 751..950:
        appellation = "outstanding";
        break;

        default:
        appellation = "legendary";
    }
    return appellation;
}

string
brew_improvement( int rawscore, int beertime )
{
    int rank, diff;
    string str;

    rank = aged_score(rawscore,beertime) / 250;
    diff = rank - rawscore / 250;

    switch (rank)
    {
        case 0..1:
        str = "spitefully not improved much if at all";
        if ( diff > 0 ) 
            str = "improved enough to be just drinkable";
        break;

        case 2:
        str = "not much improved yet";
        if ( diff > 0 ) 
            str = "improved enough to be quite pleasing";
        if ( diff > 1 ) 
            str = "improved far beyond its humble beginnings";
        break;

        default:
        str = "not improved much, not that it needs it";
        if ( diff > 0 ) 
            str = "improved to be quite the thing";
        if ( diff > 1 ) 
            str = "improved superbly, building on excellence";
    }

    return str;
}


string
brew_ageadj( int beertime )
{
    string str;
    int *agearr; 

    agearr = TIME2NUM(abs(beertime - gTimeNow));

    if ( agearr[0] > gReserveAge ) 
        return "old reserve";

    switch (agearr[0])
    {
        case 0..2:
        str = "fresh";
        break;

        case 3..14:
        str = "new";
        break;

        default:
        str = "old";
    }
    return str;
}


public varargs int
brewcraft_brew_score(int i)
{
    return aged_score(gRawScore[i],gBeerTime[i]);
}

public int
brewcraft_export_quester()
{
    return gQuesterExporter;
}

public varargs string
brewcraft_brew_type(int i)
{
    return gBeerType[gBeerIndex[i]];
}

public varargs int
brewcraft_brewer_align(int i)
{
    return gAlign[i];
}

public varargs string
brewcraft_brewer_race(int i)
{
    return gRace[i];
}

public varargs string
brewcraft_brewer_name(int i)
{
    return gBrwrName[i];
}

public varargs string
brewcraft_long(int i)
{
    string str, astr, fmtstr, opstr0, opstr1;

    astr = brew_ageadj(gBeerTime[i]);

    fmtstr = "%s's %s %s -- a product of the "+
             "Iron Delving Brewery -- %s crafted. The beer is "+
             "%s in colour and bears the faintest whiff of %s about it.";

    str = sprintf(fmtstr,
                  capitalize(gBrwrName[i]),astr,capitalize(gBeerType[gBeerIndex[i]]),
                  brew_adverb(gRawScore[i]),
                  brew_colour(gBeerIndex[i]),
                  brew_smell(gRace[i]) );

    opstr0 = brew_opinion(gRawScore[i]);
    opstr1 = brew_opinion(aged_score(gRawScore[i],gBeerTime[i]));

    if ( opstr0 != opstr1 ) 
    {
       fmtstr = "%s This particular brew was widely considered to be %s at "+
                "first, but with time spent maturing in the vault, "+
                "connoisseurs now call it %s.\n";
       str = sprintf(fmtstr,str,opstr0,opstr1);
    }
    else
    {
       fmtstr = "%s This particular brew is widely considered to be %s.\n";
       str = sprintf(fmtstr,str,opstr1);
    }

    return str;
}

public varargs string
brewcraft_short(int i)
{
    string str;

    str = brew_ageadj(gBeerTime[i]);

    return sprintf("%s's %s %s", 
     capitalize(gBrwrName[i]),str,capitalize(gBeerType[gBeerIndex[i]]));
}

public varargs string
brewcraft_menuentry(int i)
{
    string str;

    str = brew_ageadj(gBeerTime[i]);

    return sprintf("%s's %s %s", 
     capitalize(gBrwrName[i]),str,capitalize(gBeerType[gBeerIndex[i]]));
}

int
overaged( int beertime )
{
    int lostage;
    int *agearr; 

    lostage = gReserveAge + random( (gLostAge - gReserveAge) ); 
    agearr = TIME2NUM(abs(beertime-gTimeNow));
    return ( agearr[0] > lostage );
}

int
aged_score( int rawscore, int beertime )
{
    int *agearr; 

    agearr = TIME2NUM(abs(beertime-gTimeNow));
    if ( agearr[0] > gReserveAge ) agearr[0] = gReserveAge;

    return rawscore + agearr[0] * gAgingFactor;
}

public int
brewcraft_export_royalty( string brwrname )
{
    int rval = 0;

    if ( (gQuesterExporter == 0) && (gExportRoyaltyPaid == 0) && (brwrname == gBrwrName[gIdxTap]) )
    {
        gExportRoyaltyPaid = 1;
        rval = 1;
    }

    return rval;
}

public int
brewcraft_champions_royalty( string brwrname )
{
    int rval = 0;

    if ( (gChampionsRoyaltyPaid == 0) && (brwrname == gBrwrName[gIdxTop]) )
    {
        gChampionsRoyaltyPaid = 1;
        rval = 1;
    }

    return rval;
}

