/* The Soldiers of God's Cross */

inherit "/std/object";
inherit "/d/Wiz/rastlin/open/spells/spellcasting";

#include "/d/Kalad/defs.h"
#include <tasks.h>



public int
kill_access(object ob)
{
    if (!living(ob) || ob->query_ghost() || ob == query_caster())
        return 0;
    return 1;
}

public int
query_spell_mess(string verb, string arg)
{
    switch(verb)
    {
        case "hlight":
	    write("You clasp your "+short()+" in your hands, and "+
            "mutter a prayer to God.\n");
	    say(QCTNAME(TP)+" clasps "+HIS(TP)+" "+short()+" in "+
            HIS(TP)+" hands and utters a prayer to God.\n");
	    return 1;
	    break;
        case "hreveal":
            write("You clasp your "+short()+" in your hands, and "+
            "call upon God to reveal the evil nature of those around "+
            "you.\n");
            say(QCTNAME(TP)+" clasps "+HIS(TP)+" "+short()+" in "+
            HIS(TP)+" hands and calls upon God to reveal the evil "+
            "nature of those around "+HIM(TP)+".\n");
            return 1;
            break;
        case "heyel":case "heyeg":
            write("You clasp your "+short()+" in your hands, and "+
            "utter: Oh Lord, with Thy divine eyes, show us those who "+    
            "seek to be privy among us.\n");
            say(QCTNAME(TP)+" clasps "+HIS(TP)+" "+short()+" in "+
            HIS(TP)+" hands and utters: Oh Lord, with They divine eyes, "+
            "show us those who seek to be privy among us.\n");
            return 1;
            break;
    }
    return 0;
}

#include "light.c"
#include "hreveal.c"
#include "heyel.c"
#include "heyeg.c"

void
create_object()
{
    set_name("cross");
    set_adj("bright");
    add_adj("steel");
    set_long("As you gaze upon this magnificant, ornate cross made "+
    "of steel, a feeling of holiness surrounds you. An agelesss might "+
    "of strong will seems to make its presence inside of you. The "+
    "cross shines with a holy, inner glow. There are runes "+
    "engraved along the sides, and tiny red rubies are placed at "+
    "each end of the cross. In the very center, there is a white, "+
    "pure diamond.\n");
    add_item(({"diamond","pure diamond","white diamond"}),"The diamond "+
    "seems to be real, and sparkles in the light.\n");
    add_item("runes","The runes on your cross are magical, holy words "+
    "of God. The protect the cross, and provide you with the way to "+
    "communicate with God. You notice a couple important words: "+
    "'help god'.\n");
    add_item(({"rubies","red rubies"}),"They are tiny rubies "+
    "and are embedded inside the steel of the cross.\n");
    set_short("bright steel cross");
    set_pshort("bright steel crosses");

    add_spell("hlight",do_light,"    Holy Light             - Create a "+
    "lighted aura.\n");
    add_spell("hreveal",do_hreveal,"   Reveal Evil            -  Reveal "+
    "the fiends of Hell.\n");
    add_spell("heyel",do_heyel,"     Eyes of God (Lesser)   - Reveal the "+
    "privy.");
    add_spell("heyeg",do_heyeg,"     Eyes of God (Greater)   - Reveal the "+
    "privy and divinely privy.");
    

}



