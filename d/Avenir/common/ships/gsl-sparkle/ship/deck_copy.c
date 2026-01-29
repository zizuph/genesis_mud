#pragma strict_types
// file name: Deck   /d/Avenir/common/ships/sparkle/deck.c
// creator(s):       Tepsich   Oct 1994
// purpose:          Deck of the Melancholy
// last update:         Boriska, Mar 23 1995
//
// Ported to the new ship system, 05/2009
#include "/d/Genesis/gsl_ships/ships.h"
#include "../ship.h"

inherit STDSHIPROOM;

int thief_called = 0;
int query_thief_called();

public void
create_room(void)
{
    create_shiproom();
    set_deck_sound("@@sounds@@");
    set_is_deck(1);

    set_short("On the G.S. Melancholy");
    set_long("@@desc_long");

    add_item("sails", "Square-rigged on three masts, they resemble " +
      "blood-stained shrouds.\n");
    add_item("deck", "The wood is dry and sunbleached. Fortunately " +
      "there doesn't seem to be any rot.\n");
    add_item("barque", "A ghostly-looking sailing ship with square-rigged "   +
      "masts. A decaying bust of indeterminate gender decorates the "  +
      "prow.On either side of the prow the letters 'G.S. MELANCHOLY' " +
      "are printed in fading gold paint.\n");
    add_item(({"mast", "masts", "mainmast"}), "There are three masts, the " +
      "largest of which looks like a hangman's post.\n");
	add_item("sailor", "@@desc_sailor");

    add_exit(CABIN, "aft");
}

string
desc_long()
{
	string text;
    text = "The air is deathly still.  The deck of this ghostly barque " +
      "is dry and pale as dead men's bones.  Shroud-like sails, "   +
      "stained with blood-red streaks, creak and groan in the "     +
      "non-existent wind.  The mainmast thrusts up from the deck, " +
      "ominously resembling a gibbet. ";
    if (!(query_thief_called()))
        text += "Close to the reel is a sailor working with some " +
            "sheets for the rig.";
    text += "\n";
    return text;
}

private string *snds = ({
	"A wailing sound fills your ears.\n",
	"    c r e a k   creak   c  r  e  a  k\n",
	"        Mu ah hah hah hah\n",
	"The ship keels sharply to port.\n",
	"Waves slam against the starboard side, spraying you with water.\n",
	"The ship rolls nauseatingly side-to-side.\n" ,
	"A sudden, eerie silence weights the air.\n",
});

public string
sounds(void)	{ return one_of_list(snds); } 

string
desc_sailor()
{
	object thief;
	string text;
	if (query_thief_called())
	{
		text = "What sailor?\n";
		return text;
	}
	else
	{
	text = "The sailor is a short tanned man that " +
	"looks quite muscular and tough. Perhaps because " +
	"of the hard work at sea.\n";
	thief = clone_object("/d/Avenir/common/port/mon/thief2");
	thief->arm_me();
	thief->move(TO, 1);
	thief_called = 1;
	tell_room(TO, "A sailor steps forward from his place " +
		"at the reel.\n");
	set_alarm(1.0, 0.0, &thief->command("say Hello landlubber!"));
	set_alarm(1.0, 0.0, &thief->command("emote flashes a toothless " +
		"smile in your direction!"));
	set_alarm(2.0, 0.0, &thief->command("aft"));
	}
	return text;
}

int
query_thief_called()
{
    return thief_called;
}

int
call_thief()
{
    thief_called = 0;
}
