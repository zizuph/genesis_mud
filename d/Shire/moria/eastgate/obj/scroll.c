/*
 * A scroll abuot Moria
 * /d/Shire/moria/eastgate/obj/scroll.c
 *
 * Varian - May, 2020
 */

#pragma strict_types
#pragma save_binary

inherit "/std/object";

#include <stdproperties.h>
#include <formulas.h>
#include <macros.h>
#include <files.h>
#include "/d/Gondor/met_defs.h"
#include "../defs.h"

#define SKILL_INCREASE     99

int do_read(string str);

public void
create_object()
{
	set_name("scroll");
	add_name( ({"_scroll_of_moria_", "book"}) );
	set_adj("small");
	add_adj("brown");

	set_short("small brown scroll");
    set_long("Written in the clear and precise hand of dwarf " +
        "named Farin son of Borin, this scroll appears to " +
        "provide a brief history of Moria. You can " +
        "read it if you like.\n");
}

int
do_read(string str)
{

    if (!str || !strlen(str)) 
    {
        notify_fail("Read what?\n");
        return 0;
    }

    if (!id(str))
    {
        notify_fail("Read what?\n");
        return 0;
    }

    if(environment(this_object()) == this_player())
    {
        this_player()->set_skill(SS_MORIA_LORE, SKILL_INCREASE);
        write("Khazad-dum, the Dwarrowdelf, most magnificent of our " +
            "mansions. Now only remembered to the world as Moria, " +
            "the black pit.\n\n" +
            "But that is not how I would have it remembered, and I " +
            "know that one day we Longbeards shall come back in " +
            "strength to take back these halls from Durin's Bane.\n\n" +
            "It was in the first age, perhaps eight millenia past, " +
            "when my forefather Durin, named the Deathless, first " +
            "marched into Azanulbizar, which men call Dimrill Dale. " +
            "He stood near the banks of Kheled-zaram, that which " +
            "men name Mirrormere, which revealed a crown of stars " +
            "reflected atop those palcid waters. It was clearly a " +
            "sign of what Mahal wished to be, and into the walls " +
            "of mighty Zirakzigil Durin delved, building the Great " +
            "Gates and the First Hall.\n\n" +
            "For more than eighty centuries our folk dug deeper " +
            "into Zirakzigil, along with cruel Barazinbar and " +
            "misty Bundushathur. Khazad-dum was rich in deposits, " +
            "with iron, jewels and even gold in abundance. Yet, far " +
            "below Barazinbar in the seventh deep was where we found " +
            "Mithril. Mithril, whose strength and beauty always left " +
            "us yearning for more.\n\n" +
            "Seven deeps there were, measured from how far below " +
            "the First Hall they ran. Seven levels there were too, " +
            "each counted for how high they rose above the First " +
            "Hall. Everything in Khazad-dum was always measured " +
            "from the First Hall and the Great Gates.\n\n" +
            "It was in the second age when Durin's Doors were " +
            "built, named for Durin II who had kept expanding his " +
            "father's mansion, and Khazad-dum now ran east to west " +
            "for forty miles beneath the silvery peaks of " +
            "Zirakzigil. Many passages were built, and dozens of " +
            "chambers in the levels above for our folk to live " +
            "in.\n\n" +
            "Yet it was in the third age when tragedy arrived. " +
            "Digging ever deeper into the roots of Barazinbar we " +
            "expanded the seventh deep in our desire to continue " +
            "harvesting the great lode of mithril. And it was down " +
            "there that a large cavern was opened, and inside we " +
            "awoke Durin's Bane. Alas, our folk suffered greatly. " +
            "We tried, but we could not defend our home. Khazad-dum " +
            "was lost to this nameless horror, our riches taken, " +
            "our home destroyed.\n\n" +
            "Now, seven centuries and more later, only Moria " +
            "remains. Orcs, filthy, murderous orcs have made their " +
            "homes in our halls, allying themselves with Durin's " +
            "Bane in some fashion. The Black Pit. Moria. We shall " +
            "take it back one day.\n\n" +
            "Farin, son of Borin, T.A. 2705\n");
        SAYBB(" reads a small brown scroll.");
        return 1;
    }

    if(environment(this_object()) != this_player())
    {
        this_player()->catch_tell("You would need to be holding the " +
        	"scroll in order to read it.\n");
        return 1;
    }

    notify_fail("You are unable to read this language.\n");
    return 0;
}

public void
init()
{
    ::init();
    add_action("do_read", "read");
    add_action("do_read", "study");
}
