#pragma strict_types

inherit "/std/object";
inherit "/lib/keep";
inherit "/cmd/std/command_driver";

#include "/d/Krynn/common/defs.h"

#include <wa_types.h>
#include <macros.h>
#include <ss_types.h>
#include <stdproperties.h>
#include <composite.h>
#include <language.h>
#include <filter_funs.h>

// Ensign ensign_short, ensign_long, ensign_names (has to be 4), allowed_guild
#define DEFAULT_ENSIGN   "black Jolly Roger", \
     "Flying from the main mast is a black ensign with twin " + \
     "crossbones underneath a skull - the infamous Jolly Roger of " + \
     "the Bloodsea Pirates, flown by Captain ", \
     "Neatly folded is a black ensign with twin " + \
     "crossbones underneath a skull - the infamous Jolly Roger of " + \
     "the Bloodsea Pirates! ", \
     ({ "black ensign", "ensign", "jolly roger", "main mast" }), \
     "Pirate of the Bloodsea"

string recover_string, ensign_short, ensign_long1, ensign_long2;
string * ensign_names, expiration, allowed_guild;

mixed * ensign_details = ({ DEFAULT_ENSIGN });


mixed *
query_ensign_details()
{
    return ensign_details;
}

public void
set_ensign_details(mixed array)
{
    if(sizeof(array) < 5)
        return;

    ensign_details = ({ array[0], array[1], array[2], array[3], array[4] });
}

void
create_object()
{
    add_name(({"flag","ensign","_krynn_sailing_ensign"}));
}

void
set_ensign_data(string data)
{
    seteuid(getuid());
 
    mixed * txt = explode(data,"&&");
    ensign_short = txt[0];
    ensign_long1 = txt[1];
    ensign_long2 = txt[2];
    ensign_names = ({ txt[3], txt[4], txt[5], txt[6] });
    allowed_guild = txt[7];
    
    add_prop(OBJ_I_WEIGHT, 8000);
    add_prop(OBJ_I_VOLUME, 12000);
    add_prop(OBJ_I_VALUE, 86400); // 50 platinum cost

    add_name(ensign_names);
    add_adj(ensign_names);
    set_short(ensign_short);
    set_long(ensign_long2 + "You can <hoist> this ensign " +
        "on your ship, letting everyone know you are its " +
        "captain! Once hoisted you can also <lower> it.\n");

    set_ensign_details( ({ ensign_short, ensign_long1, 
        ensign_long2, ensign_names, allowed_guild }) );

    set_keep(1);

    recover_string = data;
}

void
create_the_ensign()
{
    mixed * ensign_data = query_ensign_details();

    ensign_short = ensign_data[0];
    ensign_long1 = ensign_data[1];
    ensign_long2 = ensign_data[2];
    ensign_names = ensign_data[3];
    allowed_guild = ensign_data[4];

    set_ensign_data(ensign_short+"&&"+ensign_long1+"&&"+
        ensign_long2+"&&"+ensign_names[0]+"&&"+ensign_names[1]+
        "&&"+ensign_names[2]+"&&"+ensign_names[3]+"&&"+allowed_guild);
}

string
query_recover()
{
    return MASTER + ":" + recover_string + "&&" +
        query_item_expiration_recover();
}

void
init_recover(string arg)
{
    ::init_keep_recover(arg);
    mixed *a = explode(arg, "&&");
    string b = "";
    string c = "";

    if(sizeof(a) > 8)
       b = a[8];

    if(!strlen(b))
        b = query_item_expiration_recover();

    c = a[0] + "&&" + a[1] + "&&" + a[2] + "&&" + a[3] +
        "&&" + a[4] + "&&" + a[5] + "&&" + a[6] + "&&" + a[7];

    set_ensign_data(c);
    init_item_expiration_recover(b);
}

