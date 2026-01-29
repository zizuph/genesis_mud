#include "defs.h"

inherit MONASTERY_BASE;

#include <ss_types.h>
#include <stdproperties.h>

void
create_m2_room()
{
}

public string
exa_vials()
{
    switch (this_player()->query_skill(SS_ELEMENT_DEATH) +
            this_player()->query_skill(SS_SPELLCRAFT))
    {
        case 0..80:
            return "The vials contain a number of liquids and powders " +
                "of various kinds.\n";
        case 81..150:
            return "The vials contain a number of liquids and powders " +
                "which you quickly identify as likely components for " +
                "death magic.\n";
        default:
            return "You instantly recognize the substances contained " +
                "within the vials as the components for a variety of " +
                "necromancy spells.\n";
    }
}

public string
exa_scrolls()
{
    switch (this_player()->query_skill(SS_ELEMENT_DEATH) +
            this_player()->query_skill(SS_SPELLCRAFT))
    {           
        case 0..80:
            return "The scrolls contain some strange, perhaps magic, " +
                " writing and a number of illustrations.\n";
        case 81..150:
            return "The scrolls describe various dark rituals.  The " +
                "illustrations indicate that they involve corpses " +
                "somehow.\n";
        default:
 	    return "The scrolls are written in a strange hand, but you " +
                "recognize them as notes for various necromancy spells " +
                "and rituals.\n";
    }
}
            
nomask void
create_monastery_room()
{
    set_short("Meditation chamber");
    set_em_long("A large, spacious room which was once used for group " +
        "worship and meditation.  It has been changed, however, into some " +
        "sort of ghastly magical laboratory.  Tables are strewn with vials " +
        "containing myriad strange chemicals, scrolls enscribed with " +
        "strange symbols, and various frightening implements with " +
        "unimaginable--but most definitely sinister--uses.  The few tables " +
        "that are not occupied are stained and encrusted with dried blood, " +
        "mucus, and other unidentifiable substances.  The sickening stench " +
        "of decay permeates the air.\n");

    add_item("tables",
        "Tables are strewn with vials " +
        "containing myriad strange chemicals, scrolls enscribed with " +
        "strange symbols, and various frightening implements with " +
        "unimagineable--but most definitely sinister--uses.  The few tables " +
        "that are not occupied are stained and encrusted with dried blood, " +
        "mucus, and other unidentifiable substances.\n");

    add_item(({ "vials", "chemicals", "strange chemicals" }), exa_vials);

    add_item(({ "scrolls", "symbols", "strange symbols" }), exa_scrolls);

    add_item(({ "implements", "frightening implements" }),
        "A large array of tools of various shapes and sizes, mostly " +
        "with sharp, cutting edges.  They appear to be some sort of " +
        "bizarre surgical instruments.\n");

    add_item(({ "blood", "mucus", "substances" }),
        "A mixture of blood, mucus, and other--apparently unnatural--" +
        "substances forms a repulsive, dried crust on some of the larger " +
        "tables.\n");

    add_prop(ROOM_I_INSIDE, 1);

    create_m2_room();
}
