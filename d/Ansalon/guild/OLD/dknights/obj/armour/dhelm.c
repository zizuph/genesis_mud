/******************************************************
 *  Solamnic helm for The Death Knights of Krynn      *
 *  By Elmore, April - 2001                           *
 ******************************************************/

inherit "/std/armour";
inherit "/lib/keep";

#include <stdproperties.h>
#include <ss_types.h>
#include <wa_types.h>
#include <macros.h>
#include <formulas.h>
#include <filter_funs.h>
#include <options.h>
#include "/d/Ansalon/common/defs.h"
#include "../../local.h"

#define SUBLOC "_obj_dknights_helmet_subloc_"

void
create_armour()
{
    set_name("full helm");
    add_name(DKNIGHT_ARMOUR);
    add_name("helm");
    set_ac(20);
    set_af(TO);
    set_at(A_HEAD | A_NECK);
    set_am( ({ 10, 10, 3 }) );
    set_adj("blackened");
    add_adj("solamnic");
    set_short("blackened solamnic full helm");
    set_long("This is a solamnic full helm, made from hardened steel "+
      "and covered with beautiful ornate covering the surface."+
      "A bundle of black hair emerges from the top of the helm "+
      "and a visor covers the face, only allowing for the eyes "+
      "to be visible. This piece of armour however seems to "+
      "have been thrown into a fire. The once flawless steel has "+
      "been charred black.\n");    

    add_prop(OBJ_I_VOLUME, 2550);
    add_prop(OBJ_I_WEIGHT, F_WEIGHT_DEFAULT_ARMOUR(35, A_HEAD));
    add_prop(OBJ_I_VALUE, F_VALUE_ARMOUR(35));
}


/*
mixed 
wear(object what)
{
    if (TP->query_guild_name_occ() == GUILD_NAME)
	TP->add_subloc(SUBLOC, TO);
    write("You wear the blackened solamnic full helm.\n");
    say(QCTNAME(TP)+ " wears the blackened solamnic full helm.\n");
    return 1;
}


mixed
remove(object what)
{
    if (TP->query_guild_name_occ() == GUILD_NAME)
	TP->remove_subloc(SUBLOC);
    write("You remove the blackened solamnic full helm.\n");
    say(QCTNAME(TP)+ " removes the blackened solamnic full helm.\n");
    return 1;
}


string
show_subloc(string subloc, object carrier, object for_obj)
{
    string str;

    if (carrier->query_prop(TEMP_SUBLOC_SHOW_ONLY_THINGS))
	return "";

    if (for_obj == carrier)
	str = "Your eyes glows deep orange beneath your "+short()+".\n";
    else
	str = capitalize(HIS(carrier)) + " eyes glows "+
	      "deep orange beneath "+HIS(carrier)+ " "+short()+".\n";

    return str;
}
*/
