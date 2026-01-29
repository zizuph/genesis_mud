/*
 * This is based on the mirror in /d/doc/examples/obj/mirror.c
 * It was originally coded by Mercade in 1994
 * Modified by Finwe for the scavenger hunt in October 2004
 */

inherit "/std/object";

#include <composite.h>
#include <formulas.h>
#include <language.h>
#include <stdproperties.h>
#include <wa_types.h>

#define SCAR_IN_FACE ({ "forehead", "left cheek", "right cheek", "nose" })

void
create_object()
{
    set_name("mirror");
    add_name("_shire_mirror_");
    set_adj("plain");
    add_adj("oval");
    set_long("@@mirror_description@@");

    add_prop(OBJ_I_VALUE,  200);
    add_prop(OBJ_I_VOLUME, 200);
    add_prop(OBJ_I_WEIGHT, 500);
}

string
beauty_description()
{
    int    i;
    int    scar = this_player()->query_scar();
    object armour;
    string *scar_desc = ({ });
    string *armours = ({ });
    string beauty;
    string scars;
    string wearing = "";

    beauty = call_other("/cmd/live/state", "beauty_text",
	(this_player()->my_opinion(this_player())),
	!this_player()->query_gender());

    if (objectp(armour = this_player()->query_armour(TS_NECK)))
	    armours += ({ LANG_ADDART(armour->short(this_player())) +
	        " around your neck" });
    if (objectp(armour = this_player()->query_armour(TS_HEAD)))
	    armours += ({ LANG_ADDART(armour->short(this_player())) +
	        " on your head" });
    if (sizeof(armours))
	    wearing = ". There is " + COMPOSITE_WORDS(armours);

    for (i = 1; i < F_MAX_SCAR; i++)
	if (scar && (i * 2))
	   scar_desc += ({ F_SCAR_DESCS[i] });
    scar_desc -= (scar_desc - SCAR_IN_FACE);

    if (sizeof(scar_desc))
    	scars = "There " + ((sizeof(scar_desc) == 1) ? "is a scar" : "are scars") +
	        " on your " + COMPOSITE_WORDS(scar_desc) +". You ";
    else
	scars = "You ";

    return scars + "think you look " + beauty + wearing +
	". You seem to be " +
	call_other("/cmd/live/state", "show_subloc_health", this_player(),
	this_player()) + ".\n";
}


string
mirror_description()
{
    string description;

    description = "This is a plain oval mirror. The glass is cut and " +
        "attached to am oval piece of wood. The wood is dark and smooth. " +
        "Looking into the mirror, you see yourself as " +
        LANG_ADDART(this_player()->query_nonmet_name()) + ". " + 
        beauty_description() + "\n";

    return description;
}
