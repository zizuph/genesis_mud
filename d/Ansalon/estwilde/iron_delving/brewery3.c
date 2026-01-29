#include "/d/Ansalon/common/defs.h"
#include "../local.h"
#include <macros.h>
#include <stdproperties.h>

#include "/d/Ansalon/guild/neidar/guild.h"

#define BREWCRAFTER_PATH "/d/Ansalon/estwilde/living/brewcrafter.c"
#define BREWER_I_HAS_TRACED_TIERMAZE "_brewer_i_has_traced_tiermaze"

#define DWARFRUNE "/d/Ansalon/estwilde/obj/dwarf_rune*"

inherit DWARF_IN;

object brewcrafter;

string
trace_tier_maze()
{
    int iaccess;

    write("Searching for meaning in the stone-carved map of the tiers "+
          "arrayed within the great barrel vault...");

    iaccess = 1;

    if( !TP->query_guild_member("Dwarven Warriors of the Neidar Clan") &&
        !TP->query_guild_member("Shieldbearers of Iron Delving") &&
        (TP->query_wiz_level() == 0))
    {
        iaccess = 0;
        foreach(object invitem: all_inventory(TP))
        {
            if ( wildmatch(DWARFRUNE, file_name(invitem)) )
            {
                iaccess = 1;
                break;
            }
        }
    }

    if ( !iaccess )
    {
        return " you find none -- perhaps some obscure "+
              "dwarvish logic applies? Who can say?\n";
    }
    else
    {
        TP->add_prop(BREWER_I_HAS_TRACED_TIERMAZE,1);
        return " your eyes trace out a clear path <east> through the maze of "+
          "tiers that would take you to the heart of the vault.\n";
    }
}


lost_if_not_found()
{
    if (TP->query_prop(BREWER_I_HAS_TRACED_TIERMAZE))
        return 0;
    write("The towering ranks of tiers endlessly turn "+
        "through the great barrel vault, offering "+
        "no clear path ahead.\n");
    return 1;
}

unseen_if_not_found()
{
    if (TP->query_prop(BREWER_I_HAS_TRACED_TIERMAZE))
        return 0;
    return 1;
}


void
reset_dwarf_room()
{
    if(!objectp(brewcrafter))
    {
        brewcrafter = clone_object(BREWCRAFTER_PATH);
        brewcrafter->move(TO);
    }
    return;
}


public void
hook_smelled(string str)
{
    write("The magic of fermentation fills the air with anticipation.\n");
}

void
create_dwarf_room()
{
    set_short("@@short_descr");
    set_long("@@long_descr");

    add_item(({"tank","tanks","copper tank","copper tanks"}),
     "Huge copper tanks stand in ranks across the polished floor "+
     "of the brewchamber -- each surmounted by a sturdy scaffold "+
     "to allow dwarfs to tend the brewing process.\n");

    add_item(({"pipe","pipes","copper pipe","copper pipes"}),
     "A network of gleaming copper pipes runs overhead and "+
     "underfoot between the great array of tanks allowing the "+
     "the transfer of liquid between stages of brewing. Some of "+
     "the pipes run to a series of taps, centrally located.\n");

    add_item(({"tap","taps","barrel","barrels"}),
     "Huge barrels are filled under an array of copper taps "+
     "at the centre of the brewchamber. The filling of the barrels "+
     "is overseen by the Brewcrafter, at which point she decides "+
     "where they should be stored in the great barrel vault for "+
     "aging.\n");

    add_item(({"chamber","brew chamber"}),
     "While the Great Barrel Vault may be the cool contemplative soul of "+
     "the Brewery, the Brewchamber is its hot beating heart; "+
     "filled as much with driving enterprise and innovation as "+
     "tanks and pipes and taps and dwarves by the dozen.\n");

    add_item(({"vault","barrel vault","great barrel vault","great vault"}),
     "The Great Barrel Vault of the Brewery is one of the "+
     "largest underground spaces in all of Krynn -- occupying the entireity "+
     "of a large hill in Iron Delving. It stretches off into darkness to the "+
     "immediate east of the brewchamber, its far extent being farther than "+
     "the mortal eye can see. It is filled to great height by towering barrel "+
     "tiers, where innumerable barrels of brew age in storage to proof " +
     "their quality. A standing stone marks the entrance to the Vault.\n");

    add_item(({"tiers","barrel tiers","tier","barrel tier"}),
      "The barrel tiers of the Vault are taller than a dragon stands and are packed "+
      "closely together in the cool darkness. The narrow passages between the "+
      "tiers turn this way and that without apparent rhyme nor reason. It would be "+
      "easy to become hopelessly lost in such a place if one did not know what one "+
      "was doing. At the entrance to the Vault, a carved map is upon a standing stone.\n");

    add_item(({"tier map","carved map","standing stone"}),
      "A standing stone of dwarven-height is placed at the dark opening between the "+
      "the first tiers of the vault. It is covered in a carved map. "+
      "It probably pertains to the dark passages within -- perhaps it can "+
      "be searched to find the way through the labyrinth to places of interest.\n");

    add_exit(IRON + "brewery1","west");
    add_exit(IRON + "brewery2","north");
    add_exit(IRON + "brewery4","east","@@lost_if_not_found",0,"@@unseen_if_not_found");

    add_search(({"tier map","carved map","standing stone"}), 3, "trace_tier_maze", 1);

    set_tell_time(500);
    add_tell("A party of dwarves roll a huge barrel into the dark "+
             "opening between the first tiers of the vault.\n");
    add_tell("A pungent fume of fermented goodness is released from a nearby tank.\n");
    add_tell("A dwarf climbs a scaffold to attend to the top of a bubbling tank.\n");

    INSIDE

    reset_dwarf_room();
}

string
short_descr()
{
    return "brew chamber and great barrel vault of the Iron Delving Brewery";
}

string
long_descr()
{
    return "The excellence of dwarven "+
        "craftsmanship is evident throughout this place. "+ 
        "Bubbling sounds and the aromas of hops, malted grain, "+
        "and fermentation assail the senses within the gigantic brew "+
        "chamber of the Iron Delving Brewery. Large copper tanks "+
        "hold different types of beers as the magic of fermentation "+
        "takes place. Dwarven brewers swarm about the room, grunting "+
        "and singing to themselves as they ply their celebrated craft. "+
        "Copper pipes connect the tanks and arrays of taps on platforms "+
        "where huge barrels -- three dwarves across and more -- are "+
        "filled and sealed. Small knots of dwarves can be seen rolling "+
        "these immense barrels away to age in peace and quiet so as to "+
        "build in flavour and potency. The barrels are stored in tier "+
        "upon tier to an immense height in the Great Vault which stretches "+
        "away to the east as far as the eye can see. The Great Vault must "+
        "be one of the largest underground spaces you have ever seen. "+
        "An ornate stone portal leads north from the brew chamber "+
        "to a small office.\n";
}


void
enter_inv(object ob, object from)
{
    ::enter_inv(ob, from);
    if (interactive(ob))
        start_room_tells();
}


