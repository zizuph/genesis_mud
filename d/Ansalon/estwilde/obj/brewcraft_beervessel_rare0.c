
/*
 *  /d/Ansalon/estwilde/obj/brewcraft_beervessel_ethereal.c
 *  Beer crafted by mortal apprentices to the...
 *  ....Brewcrafter at the Iron Delving Brewery
 *
 *  Recoverable item
 *
 *  Based on brewcraft_beervessel_empty.c
 *   it is the seldom-found special version
 * 
 *  This is a reward item obtainable from brewery5.c
 *
 *  Vitwitch 03/2021
 */

#pragma strict_types
inherit "/std/object";

#include <stdproperties.h>
#include <filter_funs.h>
#include <ss_types.h>
#include <macros.h>
#include <composite.h>
#include <language.h>
#include "/d/Genesis/gsl_ships/ships.h"

#define ETH_VESSEL_ID "_brewcraft_beer_vessel_ethereal"

#define VESSEL_FLIT_LOG "/d/Ansalon/estwilde/obj/brewcraft_bvr0_LOG"

#define VESSEL_LOSS_CHANCE_PCT 1

static string *pierpairs = ({ 
    "/d/Krynn/solace/ship/pier",
    "/d/Krynn/que/newports/pier3",
    "/d/Krynn/que/newports/pier4",
    "/d/Ansalon/taman_busuk/sanction/room/city/pier07",
    "/d/Ansalon/taman_busuk/sanction/room/city/pier04",
    "/d/Ansalon/balifor/port_balifor/room/pier02",
    "/d/Ansalon/balifor/port_balifor/room/pier04",
    "/d/Ansalon/silvanesti/new_kurinost/rooms/pier",
    "/d/Ansalon/balifor/flotsam/room/street09",
    "/d/Ansalon/goodlund/nethosak/city/room/pier2",
    "/d/Ansalon/balifor/flotsam/room/street08",
    "/d/Ansalon/kalaman/room/dock4",
    "/d/Ansalon/kalaman/room/dock5",
    "/d/Krynn/solamn/splains/room/pier",
    "/d/Krynn/solamn/splains/room/ferry",
    "/d/Krynn/solamn/eplains/rooms/eplain-4-21-V",
    "/d/Ansalon/kalaman/room/dock6",
    "/d/Krynn/solamn/palan/shipX/flotsam_pier",
    "/d/Krynn/solamn/palan/city/icewall_pier",
    "/d/Krynn/icewall/castle2/rooms/snow_plain11",
    "/d/Krynn/solamn/palan/ship4/pier",
    "/d/Calia/ships/krynn/pier",
    "/d/Genesis/start/human/town/pier10",
    "/d/Ansalon/balifor/flotsam/room/street05",
    "/d/Emerald/telberin/dock/ferry_dock",
    "/d/Emerald/north_shore/dock",
    "/d/Avenir/common/ships/bazaar/boat_path2",
    "/d/Avenir/common/bazaar/pier/float",
    "/d/Genesis/start/human/town/pier13",
    "/d/Faerun/highroad/rooms/beach01",
    "/d/Genesis/start/human/town/pier12",
    "/d/Khalakhor/inisi/roke/nyreese/cadu_b2",
    "/d/Genesis/start/human/town/pier14",
    "/d/Genesis/start/human/town/pier14",
    "/d/Krynn/solamn/palanthas/shipping/p08",
    "/d/Genesis/start/human/town/pier18",
    "/d/Genesis/start/human/town/pier16",
    "/d/Raumdor/common/beach/dock3"});

/* PROTOTYPES */

string query_recover();
void init_recover(string arg);
public void create_object();
public void hook_smelled(string str);
void vanish_it( object player );
int transport_across( object plyr );
int flick_it(string str);
int drink_it(string str);
int flit_it();
public void enter_env(object dest, object old);
void init();

/* FUNCTIONS */

string
query_recover()
{
    return MASTER + ":" + VESSEL_LOSS_CHANCE_PCT;
}

void
init_recover(string arg)
{
}

public void
create_object()
{
    set_name("ethereal vessel");
    add_name(ETH_VESSEL_ID);
    set_adj("crystal");

    set_short("ethereal crystal vessel"); 
    set_pshort("ethereal crystal vessels"); 

    set_long("" +
      "This is a crystal vessel, shaped like a "+
      "deep-draught canoe. Holding its "+
      "stem and stern in each hand, you can feel a throbbing aura "+
      "of ethereal power emanating from its centre. "+
      "The scent of the centre indicates it once bore a "+
      "charge of fine brew. "+
      "An intricate mosaic adorns the vessel.\n");

    add_item(({"centre"}),
      "The hollow at the centre of the vessel is empty, but "+
      "for the scent of brew and an ethereal aura "+
      "bathing the surrounding crystal. The crystal "+
      "vessel is riven by flickering fingers of lightning.\n");

    add_item(({"mosaic"}),
      "The mosaic adorning the vessel is of lapis lazuli "+
      "and depicts two broad rivers of blue. Vessels ply the "+
      "rivers, ferrying folk from place to place. Gazing at "+
      "the mosaic... your mind's eye sees you and your companions "+
      "standing at the waters' edge, set to <flit> across "+
      "to the other side.\n");

    add_prop(OBJ_M_NO_SELL,1);
    add_prop(OBJ_M_NO_DROP,"The ethereal vessel is bound "+
       "to you by unseen force. You can give it the <flick> "+
       "if you no longer wish to have it.\n");

    add_prop(OBJ_I_WEIGHT, 5);
    add_prop(OBJ_I_VOLUME, 50);

    add_prop(MAGIC_AM_ID_INFO,
        ({ "This vessel allows the holder and team to teleport "+
           "between ports along ship-line routes ~50 times.", 60}));

    add_prop(MAGIC_AM_MAGIC, ({ 70, "conjuration" }));

    add_prop(OBJ_S_WIZINFO, 
       "This item is rarely encountered when drinking in the "+
       "Iron Delving Brewery. It has no direct combat usage. "+
       "It is available to all players. It is not "+
       "transferrable between players. It recovers. It teleports "+
       "the holder and team between ports along ship-line routes. "+
       "It has a 1% chance of loss per teleport, giving ~50 uses on "+
       "average.\n");

     set_may_recover();
     remove_item_expiration();

}

public void
hook_smelled(string str)
{
    write("An electric scent of malt and aromatic "+
           "cedar tickles the nose.\n");
}


void
vanish_it( object player )
{
    string outcome;

    outcome = "ethereal vessel vanishes in "+
              "a flash of lightning";

    outcome += ". Disappearing from sight "+
              "-- taken from this world by unseen force.\n";

    this_player()->catch_msg("The " + outcome);

    tell_room(environment(this_player()),
         QCNAME(this_player()) + "'s " + outcome,
          this_player());

    remove_object();

    return 0;
}

int
flick_it(string str)
{
    string what, where;
    int i;

    if (!str || !strlen(str))
    {
        notify_fail("Flick what?\n");
        return 0;
    }
    if ( str == "it" || str == "vessel" || str == "ethereal vessel" )
    {
        this_player()->catch_msg("You give your ethereal "+
                      "vessel the <flick>.\n");
        set_alarm(0.5,0.0,&vanish_it(this_player()));
        return 1;
    }
}


int
transport_across( object plyr )
{
    // cross from a pier to the pier's
    // ship's destination without any
    // delay

    int ndest, npp, ipp;
    int ipier, npiers, inext;
    string locfile, *destfiles;
    string str0, str1, str2, strp;
    mixed *ships;
    object locn;
    object *teammates;

    locn = environment(plyr);
    locfile = file_name( locn );
    destfiles = ({});

    // search non-GSL piers
    // and 'irregular' GSL piers
    // in pairs

    npp = sizeof( pierpairs );  // npp must be even 
    for ( ipp=0;ipp<npp;ipp++ ) 
    {
        if ( pierpairs[ipp] == locfile )
        {
            if ( (ipp+1) % 2 )  // 1 --> odd match, dest must be 2nd in pair
                destfiles += ({ pierpairs[ipp+1] });
            else                // 0 --> even match, dest must be 1st in pair
                destfiles += ({ pierpairs[ipp-1] });
            break;
        }
    }

    ndest = sizeof(destfiles);

    if ( ndest == 0 ) 
    {
        // GSL search

        ships = SHIP_DATABASE->query_rows( ([ ]) );
        foreach (mapping ship : ships)
        {
            npiers = sizeof(ship["piers"]);
            for (ipier=0;ipier<npiers;ipier++)
            {
                if ( wildmatch(sprintf("%s*",ship["piers"][ipier]),locfile) )
                {
                    inext = ipier + 1;
                    if (inext == npiers) inext = 0;
                    destfiles += ({ship["piers"][inext]});
                }
            }
        }
    }  // GSL search

    ndest = sizeof(destfiles);

    if ( ndest == 0 ) 
        write("\nYour ethereal vessel remains inert -- finding no "+
              "interface here through which to cross to another Realm.\n\n");
    else
    {
        str0 = "\nThe aura of ";
        str1 = "ethereal vessel ";
        str2 = "engulfs your surroundings;"+
               " causing them to abruptly shift.\n\n";

        teammates = FILTER_PRESENT(plyr->query_team());
        teammates += ({plyr});

        int nteamm = sizeof(teammates) - 1;

        if ( !nteamm ) 
            strp = "a figure";
        else
            strp = "a number of figures";

        tell_room(environment(plyr),
             str0 + QNAME(plyr) + "'s " + str1 + 
              "expands, engulfing all, causing " + strp + " to vanish.\n", 
               teammates);

        int idest = random(ndest);
        foreach ( object teammate : teammates )
        {
            teammate->catch_msg(str0 + QNAME(plyr) + "'s " + str1 + str2);
            teammate->move_living("M", destfiles[idest]);
        }

        write_file( VESSEL_FLIT_LOG, ctime(time()) + " "
                + plyr->query_real_name() + " transported "
                + sizeof(teammates) + " persons from "
                + locfile + " to " + destfiles[idest] + "\n\n" );

        tell_room(environment(plyr),
           "An ethereal aura expands from a pinpoint, then dies away leaving " 
             + strp + " in its afterglow.\n",teammates);

        // how many ethereal vessels in total are held by the plyr
        int nethv = sizeof( filter(deep_inventory(plyr),&->id(ETH_VESSEL_ID)) );

        switch ( nethv )
        {
            case 1:
                break;
            case 2:
                write("\nYour ethereal vessel struggled to drag" 
                   + " another ethereal vessel along with it.\n");
                break;
            default:
                write("\nYour ethereal vessel struggled hard to drag " 
                    + LANG_NUM2WORD(nethv-1) 
                    + " other ethereal vessels along with it.\n");
        }

        if ( random(100) < (int) (VESSEL_LOSS_CHANCE_PCT * ( nteamm + nethv )) )
        {
            write("\nYour ethereal vessel has reached the end of the line!\n");
            set_alarm(0.5,0.0,&vanish_it(this_player()));
        }

    } 

    return 1;
}


int
flit_it()
{
    set_alarm(0.5,0.0,&transport_across(this_player()));
    return 1;
}


int
drink_it( string str )
{
    if ( !str || !strlen(str) ) return 0;

    if ( str == "the ethereal vessel" || str == "ethereal vessel" )
    {
        write("There is nothing to drink in this vessel. Its centre "+
         "pulses with an aura that flickers outward in fingers of "+
         "lightning.\n");
        return 1;
    }

    return 0;
}


public void
enter_env(object dest, object old)
{
    string fmtstr;
    ::enter_env(dest, old);
    if (interactive(dest))
    {
        dest->catch_msg("Receiving the vessel in your "+
        "hands, it pulses with an ethereal aura. You feel its power "+
        "bind to you.\n");

        int nethv = sizeof( filter(deep_inventory(dest),&->id(ETH_VESSEL_ID)) );

        switch ( nethv )
        {
            case 1:
                break;
            case 2:
                dest->catch_msg("The new vessel struggles to be in" 
                   + " the presence of another ethereal vessel.\n");
                break;
            default:
                dest->catch_msg("The new vessel struggles"
                    + " significantly to be in the presence of " 
                    + LANG_NUM2WORD(nethv-1) 
                    + " other ethereal vessels.\n");
        }

    }
    return;
}


void
init()
{
    ::init();
    add_action("flit_it","flit");
    add_action("flick_it","flick");
    add_action("drink_it","drink");
}
