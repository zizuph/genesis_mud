/*
 *  /d/Ansalon/estwilde/obj/brewcraft_beerbottle.c
 *  Beer crafted by mortal apprentices to the...
 *  ....Brewcrafter at the Iron Delving Brewery
 *  /d/Ansalon/estwilde/living/brewcrafter.c
 *
 *  intended as a bottle of beer tapped from
 *  an unknown barrel in the darkness of the
 *  great barrel vault
 *
 *  Vitwitch 12/2020
 */

#pragma strict_types
inherit "/std/drink";
#include <stdproperties.h>
#include <filter_funs.h>
#include <ss_types.h>
#include <math.h>
#include <composite.h>
#include "/d/Ansalon/common/brewcraft/brewcraft.h"

int gSet = 0;
int gBrewAlign, gBrewScore;
string gBeerType;
string gDrinkMsg;
string gBrewSmell;

/*prototypes */
public void create_drink();
void stat_effects(object ob, float effect);
public void special_effect(int amount);
public void enter_env(object dest, object old);

public void
create_drink()
{
    set_name("bottle");
    add_name("brew");
    add_name("_brewcraft_beer_bottle");
    set_adj(({"crafted"}));

    set_short("bottle of brew tapped from somewhere in the vault");
    set_pshort("bottles of brew tapped from somewhere in the vault");

    set_long("This bottle was tapped from some barrel somewhere in the "+
             "darkness of the Great Barrel Vault of the Iron Delving "+
             "Brewery. There is only one way to determine if it is "+
             "worthy of drinking!\n");

    set_soft_amount(300);
    set_alco_amount(60);
    add_prop(OBJ_I_WEIGHT, 300);
    add_prop(OBJ_I_VOLUME, 300);
}

public void
enter_env(object dest, object old)
{
    string fmtstr;
    ::enter_env(dest, old);
    if (interactive(dest) && !gSet)
    {
        gBrewSmell = BREWCRAFT_SMELLB;
        gBrewAlign = BREWCRAFT_ALIGNB;
        gBrewScore = BREWCRAFT_SCOREB;
        gBeerType = BREWCRAFT_STYLEB;

        fmtstr = "You down the bottle entire, slaking your "+
                 "thirst with long draughts of %s...\n" +
                 "leaving an aftertaste of %s in your mouth...\n"+
                 "You toss the empty "+
                 "bottle away into darkness with a dwarven cheer!\n";

        gDrinkMsg = sprintf(fmtstr,BREWCRAFT_TASTEB,
                              BREWCRAFT_AFTERTASTEB);

        gSet = 1;
    }
    return;
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

    this_player()->catch_msg(gDrinkMsg);

    palign = this_player()->query_alignment();

    feff = 3.0 * itof(palign) * itof(gBrewAlign) / 100000.0;

    if ( feff < 0.0 ) 
        this_player()->catch_msg("... you feel an unhappy rumbling within ...\n");
    else
        this_player()->catch_msg("... you feel a happy burbling within ...\n");

    stat_effects(this_player(),feff);

    return;
}


