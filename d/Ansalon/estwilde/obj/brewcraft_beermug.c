/*
 *  /d/Ansalon/estwilde/obj/brewcraft_beermug.c
 *  Mug of beer crafted by mortal apprentices to the...
 *  ....Brewcrafter at the Iron Delving Brewery
 *  /d/Ansalon/estwilde/living/brewcrafter.c
 *
 *  intended for use wherever good beers are sold
 *  throughout Krynn 
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
public void hook_smelled(string str);

public string
query_recover()
{
    // no recovery
    return 0;
}

public void
remove_drink()
{
    ::remove_drink();
}

public void
create_drink()
{
    set_name(({"brew"}));
    add_name("mug");
    add_name("_brewcraft_beermug");
    set_adj(({"crafted"}));

    set_short("mug of " + BREWCRAFT_SHORT); 
    set_pshort("mugs of " + BREWCRAFT_SHORT); 
    set_long("This is a mug of " + BREWCRAFT_LONG);

    gBrewSmell = "even more beeriness which fills your nostrils";

    set_soft_amount(100);
    set_alco_amount(20);
    add_prop(OBJ_I_WEIGHT, 100);
    add_prop(OBJ_I_VOLUME, 100);
}

public void
enter_env(object dest, object old)
{
    string fmtstr;
    ::enter_env(dest, old);
    if (interactive(dest) && !gSet)
    {
        gBrewSmell = BREWCRAFT_SMELL;
        gBrewAlign = BREWCRAFT_ALIGN;
        gBrewScore = BREWCRAFT_SCORE;
        gBeerType = BREWCRAFT_STYLE;

        fmtstr = "You down all the %s at once, slaking your thirst. "+
                 "You revel in its %s on your tongue on the way down," +
                 " but are left with a faint taste of %s in your mouth afterwards.\n";

        gDrinkMsg = sprintf(fmtstr,gBeerType,BREWCRAFT_TASTE,
                              BREWCRAFT_AFTERTASTE);

        gSet = 1;
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

    this_player()->catch_msg(gDrinkMsg);

    palign = this_player()->query_alignment();

    feff = itof(palign) * itof(gBrewAlign) / 100000.0;

    if ( feff < 0.0 ) 
        this_player()->catch_msg("... you feel an unhappy rumbling within ...\n");
    else
        this_player()->catch_msg("... you feel a happy burbling within ...\n");

    stat_effects(this_player(),feff);

    return;
}


