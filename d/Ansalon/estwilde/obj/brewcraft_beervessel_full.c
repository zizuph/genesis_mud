
/*
 *  /d/Ansalon/estwilde/obj/brewcraft_beervessel_full.c
 *  Beer crafted by mortal apprentices to the...
 *  ....Brewcrafter at the Iron Delving Brewery
 *  /d/Ansalon/estwilde/living/brewcrafter.c
 *
 *  this is a quest item for the Iron Delving Brewery
 *
 *  Vitwitch 02/2021
 */

#pragma strict_types
inherit "/std/drink";
#include <stdproperties.h>
#include <filter_funs.h>
#include <ss_types.h>
#include <macros.h>
#include <composite.h>
#include "/d/Ansalon/common/brewcraft/brewcraft.h"

#define EMPTYV "/d/Ansalon/estwilde/obj/brewcraft_beervessel_empty.c"

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
public string query_recover();
public mixed command_drink();

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

public mixed
command_drink()
{
    object nextv;
    mixed err;
    int am1, am2;

    am1 = query_soft_amount();
    am2 = query_alco_amount();

    if (err = this_player()->query_prop(LIVE_M_NO_DRINK))
    {
        if (strlen(err))
            return err;
        else
            return "You are unable to " + query_verb() + " anything.\n";
    }

    if (!this_player()->drink_soft(am1))
    {
        return "The " + singular_short() + " is too much for you.\n";
    }

    if (!this_player()->drink_alco(am2))
    {
        this_player()->drink_soft(-am1);
        return "The " + singular_short() + " is too strong for you.\n";
    }

    this_object()->special_effect(1);

    setuid();
    seteuid(getuid());
    nextv = clone_object(EMPTYV);
    nextv->move(this_player(),1);

    return 1;
}

string
pshort_descr()
{
    return "crystal vessels of " + BREWCRAFT_SHORTG;
}

string
short_descr()
{
    return "crystal vessel of " + BREWCRAFT_SHORTG;
}

string
long_descr()
{
    string preamble = "This is a crystal vessel, shaped like a "+
      "deep-draught canoe. It bears an inlaid mosaic of lapis lazuli "+
      "depicting two rivers of blue. Holding its "+
      "stem and stern in each hand, you can drink from its centre. "+
      "It has an aura of otherworldliness about it.";

    return preamble + " It contains a generous quantity of " 
                 + BREWCRAFT_LONGG;
}

public void
create_drink()
{

    set_name("full vessel");
    add_name("vessel");
    add_name("brew");
    add_name("_brewcraft_beer_vessel_full");
    set_adj("full");
    set_adj("crystal");

    set_short("@@short_descr"); 
    set_pshort("@@pshort_descr"); 
    set_long("@@long_descr");

    gBrewSmell = "even more beeriness which fills your nostrils";

    set_soft_amount(50);
    set_alco_amount(10);

    add_prop(OBJ_M_NO_INS, "Putting a full vessel inside a " +
              "container would cause its goodness to spill out! " +
              "Best to put it inside your belly.\n");

    add_prop(OBJ_I_WEIGHT, 50);
    add_prop(OBJ_I_VOLUME, 50);
}

public void
enter_env(object dest, object old)
{
    string fmtstr;
    ::enter_env(dest, old);
    if (interactive(dest) && !gSet)
    {
        gBrewSmell = BREWCRAFT_SMELLG;
        gBrewAlign = BREWCRAFT_ALIGNG;
        gBrewScore = BREWCRAFT_SCOREG;
        gBeerType = BREWCRAFT_STYLEG;

        fmtstr = "You down all the %s at once, slaking your thirst. "+
                 "You revel in its %s on your tongue on the way down," +
                 " but are left with a faint taste of %s in your mouth"+
                 " afterwards.\n";

        gDrinkMsg = sprintf(fmtstr,gBeerType,BREWCRAFT_TASTEG,
                              BREWCRAFT_AFTERTASTEG);

        gSet = 1;
    }
    return;
}

public void
hook_smelled(string str)
{
    write("Underlying the malt and hops and yeast there is a trace of "
            + gBrewSmell + ".\n");
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

    if ( !amount ) return;

    write(gDrinkMsg);

    palign = this_player()->query_alignment();

    feff = 0.5 * itof(palign) * itof(gBrewAlign) / 100000.0;

    if ( feff < 0.0 ) 
        this_player()->catch_msg("... you feel an unhappy rumbling within ...\n");
    else
        this_player()->catch_msg("... you feel a happy burbling within ...\n");

    stat_effects(this_player(),feff);

    return;
}

