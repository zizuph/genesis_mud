#pragma strict_types

inherit "/std/object";

#include "/sys/stdproperties.h"
#include "/d/Gondor/defs.h"

string  random_adj();     
string  random_rock();

public void
create_object()
{
string rock = random_rock(),
       rock2 = rock,
       adj = random_adj(),
       adja = adj;

    set_name(rock);
    add_name("rock");
    set_adj(adj);
    set_adj("smooth");
    set_adj("river");
    set_short("smooth " +adja+ " " +rock2);
    set_pshort("smoth " +adja+ " " +rock2+ "s");
    set_long("This is a smooth " +adja+ " " +rock2+ ".");
    add_prop(OBJ_I_VOLUME,1000 + random(1000));
    add_prop(OBJ_I_WEIGHT,5000 + random(1000));
    add_prop(OBJ_I_VALUE,0);


    set_long("This is a smooth "+adja+" "+rock2+ ", probably "
        + "gathered from a beach or riverbed.\n");

}

string    /* List of forms for the wisp. */
random_rock()
{
    string *rock = ({"rock", "rock", "stone"});

    return ONE_OF_LIST(rock);
}

string    /* List of adjectives for the wisp. */
random_adj() 
{
    string *adj = ({"round", "river", "brown", "granite", "round",
        "grey"});

    return ONE_OF_LIST(adj);
}

