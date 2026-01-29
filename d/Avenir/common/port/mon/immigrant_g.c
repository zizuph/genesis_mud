// -*-C++-*-
// file name: ~Avenir/common/port/mon/immigrant_g.c
// purpose:    NPC for port area

#include <ss_types.h>
#include <macros.h>
#include <money.h>
#include <wa_types.h>

inherit "/std/monster";


void
create_monster() 
{
    add_name("immigrant");
    set_adj(one_of_list(({
	"hopeful", "cheerful", "buoyant", "confident", "positive" })));
    set_race_name(one_of_list(({
	"human", "elf", "half-elf", "gnome", "dwarf", "goblin" })));

    default_config_npc(random(40) + 20);

    set_chat_time(15);
    add_chat("I am fleeing the endless war-making!");
    add_chat("I have heard that in Sybarus a citizen can live in peace.");
    add_chat("I do so want to live some place peaceful. I hope the "+
      "Sybarites will let me in.");
    add_chat("I have heard they worship strange Gods, but then I suppose "+
      "my Gods are strange to them, too.");
    add_chat("They are making us stay here until the Hegemon decides if "+
      "we can immigrate.");
    add_chat("I have lost all my loved-ones to war.");
    add_chat("I can't believe they think we're criminals or some other "+
      "bad people. We're trying to get away from evil.");
    add_chat("I just want to live a quiet life.");  
    add_chat("I think I could get used to shadows.");
    add_chat("I feel the same.");
    add_chat("I heard that the races live apart, in places called sokes.");
    add_chat("I wonder if I'll be able to use the Bath soon?");
    add_chat("Some of the other immigrants aren't nice people.");
    add_chat("They say that sybarites don't drink much, but there's no "+
      "shortage of good drink at the pub.");
    add_chat("Do you suppose they'd let me practice my trade here?");
    add_chat("I can understand why they call us Outlanders.");
    add_chat("I suppose there are worse things than being called 'outlander'.");
    add_chat("I'm looking forward to ordering some new clothes.");
    add_chat("If they let me in I want to become a fully-integrated member "+
      "of society. I wonder if they'll accept me into a House.");
    add_chat("Do they marry for love in Sybarus?");
    add_chat("They say that people can kill in Sybarus, but if the Gods are "+
      "displeased, a murderer will find it a damned inconvenient place to be.");
    add_chat("No theives! Can you believe it? Stealing is a capital crime.");
    add_chat("Shocking, I admit, but an not entirely unwelcome idea.");
    add_chat("They say the only thieves are outlander scum. Hopefully they "+
      "won't let that sort immigrate.");
    add_chat("Ah, to have the protection of real gods!");
    add_chat("I'm sure I'll be able to re-build my life here.");
    add_chat("I hope they let me.");

    set_gender(random(2));

    set_act_time(60 + random(99));
    add_act("sigh tired");
    add_act("stare");
    add_act("nod sincere");
    add_act("sniffle");
    add_act("scratch nose");
    add_act("smile wist");  
    add_act("laugh soft");
    add_act("grin agree");

    set_skill( SS_DEFENSE, 30 );
    set_skill( SS_UNARM_COMBAT, 40 );
    set_skill( SS_AWARENESS, 40 );
}
