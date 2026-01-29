// -*-C++-*-
// file name: Deck   /d/Avenir/common/ships/sparkle/deck.c
// creator(s):       Tepsich   Oct 1994
// last update:         Boriska, Mar 23 1995
//			Jan, 96, Added the usage of statserv to track visitors.
// purpose:          Deck of the Melancholy
// note:
// bug(s):
// to-do:            Add crew stuff

#pragma save_binary

inherit "/d/Genesis/ship/deck";

# include "/d/Avenir/common/ships/ship.h"
# include "/d/Avenir/smis/sys/statserv.h"

private int no_crew=0;

void
create_deck()
{
  set_short("On the G.S. Melancholy");
  set_long("The air is deathly still.  The deck of this ghostly barque " +
	   "is dry and pale as dead men's bones.  Shroud-like sails, "   +
	   "stained with blood-red streaks, creak and groan in the "     +
      "non-existent wind.  The mainmast thrusts up from the deck, " +
	   "ominously resembling a gibbet.\n");

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
  
  add_exit(SPAR_DIR + "cabin", "aft", "@@do_crew");
  
  set_deck_sound("@@sounds");
}

static string *snd =
({
  "A wailing sound fills your ears.\n", 
  "    c r e a k   creak   c  r  e  a  k\n",
  "        Mu ah hah hah hah\n",
  "The ship keels sharply to port.\n",
  "Waves slam against the starboard side, spraying you with water.\n",
  "The ship rolls nauseatingly side-to-side.\n" ,
  "A sudden, eerie silence weights the air.\n",

});

string
sounds() { return snd[random(6)];}

int
do_crew()
{
#if 0
  // get it back when the CREW object is there
  // should it go here or in cabin ??? --Boris
  object crew;
  if (no_crew <= 5)
    {
      seteuid(getuid(TO));
      (crew = clone_object(CREW))->move_living(0,TO);
      crew->command("say You shouldn't go in there.");
      no_crew++;
    }
#endif
  return 0; 
}

public varargs int disembark(string what)
{
    int res;

    res = ::disembark(what);
    if(res && file_name(environment(this_player()))[0..8] == "/d/Avenir")
        STATSERV_LOG_EVENT("avisits", "Port11 through ship from Sparkle");
    return res;
}
