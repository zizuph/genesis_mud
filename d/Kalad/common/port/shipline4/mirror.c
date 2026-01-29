inherit "/std/object";

#include "../default.h"
#include <composite.h>
#include <formulas.h>
#include <language.h>
#include <stdproperties.h>
#include <wa_types.h>

void
create_object()
{
    set_name("mirror");
    set_adj("large");
    add_adj("ornamented");
    set_long("@@mirror_description@@");

    add_prop(OBJ_I_VALUE,480);
    add_prop(OBJ_I_VOLUME,5000);
    add_prop(OBJ_I_WEIGHT,5000);
    add_prop(OBJ_I_NO_GET,"Its bolted to the floor!\n");
}

#define SCAR_IN_FACE ({ "forehead", "left cheek", "right cheek", "nose" })

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
	wearing = ", wearing " + COMPOSITE_WORDS(armours);

    for (i = 1; i < F_MAX_SCAR; i++)
	if (scar && (i * 2))
	    scar_desc += ({ F_SCAR_DESCS[i] });
    scar_desc -= (scar_desc - SCAR_IN_FACE);

    if (sizeof(scar_desc))
	scars = "You have " + ((sizeof(scar_desc) == 1) ? "a scar" : "scars") +
	" on your " + COMPOSITE_WORDS(scar_desc) +
	" and you ";
    else
	scars = "You ";

    return scars + "think that you look " + beauty + wearing +
    ". You seem to be " +
    call_other("/cmd/live/state", "show_subloc_health", this_player(),
      this_player()) + ".\n";
}

string
mirror_description()
{
    string description;

    description = break_string("You look into the mirror and see yourself, " +
      LANG_ADDART(this_player()->query_nonmet_name()) + ". " +
      beauty_description(), 75) + "\n";

    return description;
}

