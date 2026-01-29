/* Configurable guild knife
 * Updated Aug 28, 2003 by Lilith
 * -added prop to make this an offering for Jazur.
 */
#pragma strict_types

#include "../defs.h"
#include "/d/Avenir/include/deities.h"

inherit "/d/Avenir/inherit/weapon";
inherit "/lib/keep";

#include <macros.h>
#include <formulas.h>
#include <language.h>
#include <stdproperties.h>

public string type, mat, wep;
public string *mats = ({ "copper", "iron", "bronze", "steel" }),
       	      *types = ({ "slender", "light", "long", "curved" }),
	      *weps = ({ "dagger", "dirk", "knife" });


public void
set_type(string str)	{ type = str; }

public void
set_mat(string str)	{ mat = str; }

public void
set_wep(string str)	{ wep = str; }

public void
init_knife(void)
{
    int weight, hit, pen, dt;

    set_name(wep);
    set_short(type + " " + mat + " " + wep);
    add_adj(({ type, mat, "union" }));
    add_name(({ type, "_union_heph_knife" }));
    set_long("It is " + LANG_ADDART(type) + " " + wep +
	", finely crafted from " + mat + " to make a "+
	"sharp point and a keen blade.\nThe metal seems "+
	"to be tinged dull, as if some cloudy substance "+
	"was used to finish it.\n");

    /* Defaults */
    hit = 8;
    pen = 8;
    weight = 1000;
    dt = W_IMPALE;

    switch(mat)
    {
    case "iron":
	weight = 1000;
	set_likely_dull(10);
	break;
    case "steel":
	weight = 800;
	set_likely_dull(2);
	break;
    case "bronze":
	weight = 900;
	set_likely_dull(5);
	break;
    case "copper":
	weight = 600;
	set_likely_dull(3);
	break;
    }

    switch(type)
    {
    case "slender":
	hit = 10;
	pen = 13;
	break;
    case "light":
	hit = 10;
	pen = 8;
	weight -= 300;
	break;
    case "long":
	hit = 8;
	pen = 12;
	weight += 220;
	break;
    case "curved":
	hit = 15;
	pen = 9;
	break;
    }

    switch(wep)
    {
    case "dirk":
	dt = W_IMPALE;
	hit += 3;
	pen -= 3;
	break;
    case "knife":
	dt = (W_IMPALE | W_SLASH);
	pen += 1;
	break;
    case "dagger":
	dt = W_IMPALE;
	pen += 4;
	hit -= 2;
	break;
    }

    set_dt(dt);
    set_hit(hit);
    set_pen(pen);
    add_prop(OBJ_I_VOLUME, 1200);
    add_prop(OBJ_I_WEIGHT, weight);
    add_prop(OBJ_I_VALUE, F_VALUE_WEAPON(hit, pen) + random(50));
}

public void
randomize(void)
{
    mat  = one_of_list(mats);
    wep  = one_of_list(weps);
    type = one_of_list(types);

    init_knife();
}

public void
create_weapon(void)
{
    set_name(({"blade"}));
    set_wt(W_KNIFE);
    add_prop(JAZUR_OFFERING, 1);
}

public string
query_recover(void)
{
    return MASTER + ":" + query_wep_recover() +
	"#MAT#"+mat+"#WEP#"+wep+"#TYPE#"+type+"#";
}

public void
init_recover(string arg)
{
    string foo;

    init_wep_recover(arg);
    sscanf(arg, "%s#MAT#%s#WEP#%s#TYPE#%s#", foo, mat, wep, type);

    if (!mat)  mat  = "iron";
    if (!wep)  wep  = "knife";
    if (!type) type = "long";

    init_knife();
}
