
/*
 *  /d/Ansalon/estwilde/obj/brewcraft_beervessel_empty.c
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

#define BEERVESSEL_M_DUSTY "_beervessel_m_dusty"

int gSet = 0;
string gBrewSmell;

/* PROTOTYPES */

public void create_drink();
public void enter_env(object dest, object old);
public void hook_smelled(string str);
public string query_recover();
public mixed command_drink();
public void remove_drink();
int slip_it();
void shatter( object player );
void init();
string residue_descr();
string pshort_descr();
string short_descr();
string long_descr();
int taste_it( string str );

/* FUNCTIONS */

public string
query_recover()
{
    // no recovery
    return 0;
}

public void
remove_drink()
{
}

public mixed
command_drink()
{
    return "You cannot drink from an empty vessel!\n";
}

string
residue_descr()
{
    if ( !query_prop(BEERVESSEL_M_DUSTY) ) 
        return "There is hardly any trace of residue "+
           "at the bottom of the vessel.\n";
    else
        return "There is a pool of residue at the bottom "+
         "of the vessel, clouded with dark dust. You may "+
         "like to <taste> it.\n";
}


string
pshort_descr()
{
    return "empty crystal vessels";
}

string
short_descr()
{
    return "empty crystal vessel";
}

string
long_descr()
{
    string preamble = "This is a crystal vessel, shaped like a "+
      "deep-draught canoe. It bears an inlaid mosaic of lapis lazuli "+
      "depicting two rivers of blue. Holding its "+
      "stem and stern in each hand, you can drink from its centre.";

    return preamble + " Unfortunately, it is empty but for a "+
          "trace of dark residue.\n";
}

public void
create_drink()
{

    set_name("empty vessel");
    add_name("vessel");
    add_name("_brewcraft_beer_vessel_empty");
    set_adj("crystal");

    set_short("@@short_descr"); 
    set_pshort("@@pshort_descr"); 
    set_long("@@long_descr");

    add_prop(OBJ_M_NO_DROP,"@@slip_it");
    add_prop(BEERVESSEL_M_DUSTY,1);

    add_item(({"residue","dark residue","trace of residue"}), 
             "@@residue_descr");

    set_soft_amount(0);
    set_alco_amount(0);
    add_prop(OBJ_I_WEIGHT, 5);
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

        gSet = 1;
    }
    return;
}


public void
hook_smelled(string str)
{
    write("Underlying the residual malt and hops and yeast there is a trace of "
            + gBrewSmell + ".\n");
}


void
shatter( object player )
{
    string outcome;

    outcome = "crystal shatters into "+
                "a thousand glittering fragments";

    outcome += ". They disappear from sight "+
              "as though taken up by an unseen force.\n";

    this_player()->catch_msg("Ethereal " + outcome);

    tell_room(environment(this_player()),
         QCNAME(this_player()) + "'s " + outcome,
          this_player());

    remove_object();

    return 0;
}


int
slip_it()
{
    set_alarm(0.5,0.0,&shatter(this_player()));
    return 0;
}

int
taste_it( string str )
{
    int alco_amount = 10;
    int food_amount = 60;
    int intox;

    if ( (str == "dust") || (str == "residue") || (str == "pool") )
    {
        notify_fail("There is not enough dusty residue in the "+
                       "vessel to taste it properly.\n");
        if ( !query_prop(BEERVESSEL_M_DUSTY) ) return 0;

        if ( !this_player()->eat_food(food_amount) )
        {
            this_player()->catch_msg("You are too full to taste "+
             "the dusty residue at the bottom of the vessel.\n");
        }
        else
        {
            intox = this_player()->query_intoxicated() - random(alco_amount);
            intox = max( intox, this_player()->query_prop(LIVE_I_MIN_INTOX) );
            this_player()->set_intoxicated(intox);
            remove_prop(BEERVESSEL_M_DUSTY);

            this_player()->catch_msg("In tasting the dusty residue at the "+
              "bottom of the vessel you taste a dry dreary existence. You are "+
              "nourished in the manner of the Dead of Kur. You find it to be a "+
              "sobering experience.\n");
        }

        return 1;
    }

    return 0;
}

void
init()
{
    ::init();
    add_action("taste_it","taste");
}

