/*   the witch's helper, Ten Albers
     coded by Amelia, 4/12/97
*/

#pragma strict_types

inherit "/d/Earthsea/std/monster";
inherit "/d/Earthsea/lib/width_height";
inherit "/d/Earthsea/lib/remember";

#include <macros.h>
#include <stdproperties.h>

public void
create_earthsea_monster()
{
    set_name("eryndel");
    add_name("storekeeper");
    set_gender(G_MALE);
    set_race_name("human");
    set_height("tall");
    set_width("skinny");
    add_adj(({"thin", "weathered"}));
    set_long("A thin weathered man, who looks like a "+
        "craftsman. He has hands scarred and calloused from working "+
        "with leather and tools.\n");
    set_living_name("_storekeeper2_");
    set_stats(({40,40,40,40,40,40}));
    add_prop(OBJ_M_NO_ATTACK, "You feel this man is protected "+
        "by the wizards of this region.\n");
    add_prop(OBJ_M_NO_MAGIC_ATTACK, "The man holds up "+
        "his hand palm outward and shouts loudly, Avert!!\n"+
        "The spell falls harmlessly on empty air.\n");
    set_act_time(60);
    set_chat_time(90);
    add_act("emote pokes a hole in a piece of leather with "+
        "an awl.");
    add_act("emote polishes a new backpack, getting it ready "+
        "for sale.");
    add_chat("I only sell new equipment here. Read the sign, "+
        "if you can read, that is.");
    add_act("emote whistles softly as he works.");
}
