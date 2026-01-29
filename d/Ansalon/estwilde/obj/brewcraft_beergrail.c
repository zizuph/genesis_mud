/*
 *  /d/Ansalon/estwilde/obj/brewcraft_beergrail.c
 *
 *  Grail-shaped faintly glowing volume of 
 *  championship IDB brew 
 *  /d/Ansalon/common/brewcraft/
 *
 *  This libation to holy Ninkasi
 *  is held in its glowing grail-shaped
 *  form by the Sign of Zoot.
 *
 *  Note that this object will change
 *  with the update of the brewcraft
 *  topntapmap.o if a new champion
 *  brew is found. 
 *
 *  This item recovers.
 *
 *  It is also the 'key' which will
 *  open the speak-easy hidden in the brewery. 
 *
 *  Too large to drink by a mortal...
 *
 *  Vitwitch 02/2021
 */


#pragma strict_types
inherit "/std/drink";
#include <stdproperties.h>
#include <filter_funs.h>
#include <ss_types.h>
#include <composite.h>
#include "/d/Ansalon/common/brewcraft/brewcraft.h"

int gBrewAlign, gBrewScore;
string gBeerType;
string gDrinkMsg, gBrewSmell;

/*prototypes */
public void create_drink();
void stat_effects(object ob, float effect);
public void special_effect(int amount);
public void enter_env(object dest, object old);
public void hook_smelled(string str);

public void
remove_drink()
{
    ::remove_drink();
}

public void
create_drink()
{
    // 60kg mass, commensurate volume (60L)
    // can be carried by STR 50, otherwise unencumbered
    // effectively too large for a mortal to drink
    // alcohol content consistent with beer

    add_prop(OBJ_I_WEIGHT, 60000);
    add_prop(OBJ_I_VOLUME, 60000);
    set_soft_amount(60000);
    set_alco_amount(12000);

    add_prop(OBJ_I_LIGHT,1);   // glows - std daylight
    add_prop(OBJ_M_NO_SELL,1); 
    add_prop(OBJ_M_NO_BUY,1);   

    set_name("grail");
    add_name(({"brew","libation"}));
    set_adj("swirling");
    add_adj(({"grail-shaped","magic","two-handled","glowing"}));

    set_short("swirling grail of " + BREWCRAFT_SHORTG); 
    set_pshort("swirling grails of " + BREWCRAFT_SHORTG); 

    set_long("This is not a physical grail as such. Rather it is a " +
             "large 'grail-shaped' swirling volume of beer, held in an " +
             "upright two-handled form by a magick mark. " +
             "It eerily glows " + BREWCRAFT_COLOURG + " to attract " +
             "attention to its prize-winning contents. " + 
             "They being a long hundredweight of " +
              BREWCRAFT_LONGG);

    add_item(({"magick mark","mark"}),"The magick mark "+
             "has the form of a label shimmering over the swirling volume. "+
             "It reads:\n\nO Ninkasi, accept this libation...\n"+
             "which I've just remembered is grail-shaped...\n"+
             "its not the first time we've had this problem...\n\n -- "+
             "Zoot the Naughty.\n\n");
}


public void
enter_env(object dest, object old)
{
    string fmtstr;
    ::enter_env(dest, old);
    if ( interactive(dest) )
    {
        gBrewSmell = BREWCRAFT_SMELLG;
        gBrewAlign = BREWCRAFT_ALIGNG;
        gBrewScore = BREWCRAFT_SCOREG;
        gBeerType = BREWCRAFT_STYLEG;

        fmtstr = "You somehow ingest all the %s at once, slaking an "+
                 "immortal's thirst. "+
                 "You revel in its %s on your tongue on the way down, " +
                 "but are left with a faint taste of %s in your mouth afterwards. "+
                 "Expended, the grail-shaped libation to Ninkasi is gone.\n";

        gDrinkMsg = sprintf(fmtstr,gBeerType,BREWCRAFT_TASTEG,
                              BREWCRAFT_AFTERTASTEG);

    }
    return;
}

public void
hook_smelled(string str)
{
    write("Underlying the malt and hops and yeast there is a trace of " + gBrewSmell + ".\n");
}


void
stat_effects(object ob, float effect)
{
    // +/- to discipline, - to wisdom

    int ieffD, ieffW ;
    int maxieff;  // max. allowed effect (/std/living/stats.c)
    int duration; //in HP HEALING INTERVALS

    duration = ( gBrewScore * (5 + random(3)) ) / 200;  // cannot exceed 30

    maxieff = 9 + ( 11 * ob->query_base_stat(SS_DIS) ) / 10 - ob->query_stat(SS_DIS);
    ieffD = min( maxieff, ftoi(effect) );
    ob->add_tmp_stat(SS_DIS, ieffD, duration);

    ieffW = -1 * abs(ftoi(effect));
    ob->add_tmp_stat(SS_WIS, ieffW, duration);

    if ( ieffD == 0 ) return;
    if ( ieffD > 0 )
        write("... you are emboldened; fit to take on all the world!\n");
    else
        write("... you are enfeebled; fit to hide from all the world!\n");

    return;
}


public void
special_effect(int amount)
{
    // Agreement between gBrewAlign && TP alignment
    // has effect on TP DIS level.  Any +- DIS effect
    // results in a -ve WIS effect

    int palign;
    float feff; 

    write(gDrinkMsg);

    palign = this_player()->query_alignment();

    feff = 600.0 * itof(palign) * itof(gBrewAlign) / 100000.0;

    if ( feff < 0.0 ) 
        this_player()->catch_msg("... you feel an unhappy rumbling within ...\n");
    else
        this_player()->catch_msg("... you feel a happy burbling within ...\n");

    stat_effects(this_player(),feff);

    return;
}

