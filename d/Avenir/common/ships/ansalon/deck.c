// -*-C++-*-
// file name: Deck   /d/Avenir/common/ships/ansalon/deck.c
// creator(s):       Lilith, 2/4/97
// last update:
// purpose:          Deck of the Odalisque
// note:             Will use statserv to track visitors.
// bug(s):
// to-do:

#pragma save_binary

inherit "/d/Genesis/ship/deck";
#include "/d/Avenir/common/ships/ship.h"
#include "/d/Avenir/smis/sys/statserv.h"

int thief_called = 0;
int query_thief_called();

void
create_deck()
{
    set_short("On the G.S. Odalisque");
    set_long("@@desc_long");
    add_item(({"sails", "lateen", "triangular sails", "sail"}),
        "The sails are lateen, or triangular shaped, and set on "+
        "long, sloping yards that are supported at the center. "+
        "The sails are made of heavy canvas dyed in brilliantly "+
        "coloured stripes.\n");
    add_item(({"colours", "brilliant colours", "stripes"}),
        "The stripes on the sails are alternating purple, scarlet "+
        "and green.\n");
    add_item(({"deck", "scar", "scars", "marks", "indentations"}),
        "The wood of the deck is scarred with dark marks and indent"+
        "ations most likely caused by fallen masts and grappling " +
        "hooks.\n");
    add_item("caravel", "A battered sailing vessel with two lateen-"+
         "rigged masts. On either side of the prow the letters 'G.S. "+
         "ODALISQUE' are printed in curling golden script.\n");
    add_item(({"mast", "masts", "yard", "yards", "rigging"}),
        "There are two masts, each supporting two yards rigged "+
        "with lateen sails.\n");
    add_item("bulkhead", "It is a box-like structure, covering the "+
        "entrance to the hold. It is locked.\n");
    add_item(({"rudder", "sternpost"}), "The rudder is hinged to the "+
        "sternpost. It is used to steer the ship.\n");
    add_item(({"oars"}), "The ship, though small, is too large to be "+
        "propelled by oars. You suspect that they are used for "+
        "maneuvering into and out of mooring.\n");
    add_item("sailor", "@@desc_sailor");
    add_exit("/d/Avenir/common/ships/ansalon/cabin", "down");
    set_deck_sound("@@sounds");
}


string
desc_long()
{
string text;
    text = "The deck of this small ship bears the scars of grappling "+
    "hooks and fallen masts. Its battered condition is evidence "+
    "of the quality of its crafting, for it has made the treach"+
    "erous journey across the Sea of Istar and through the Sybarus "+
    "Rift countless times. There is a bulkhead leading down into "+
    "the hold, and a pair of oars lie astern, near the rudder. "+
    "Two lateen-rigged masts jut up into the sky like defiant "+
    "fingers, the triangular sails on their long, sloping yards "+
        "billowing in the wind. ";
    if (!(query_thief_called()))
        text += "Close to the reel is a sailor working with some " +
            "sheets for the rig.";
    text += "\n";
    return text;
}

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
        set_alarm(1.0, 0.0, &thief->command("emote flashes a toothless smile " +
            "in your direction!"));
        set_alarm(2.0, 0.0, &thief->command("down"));
    }
    return text;
}

static string *snd =
({
  "Salt-spray stings your eyes.\n",
  "The wind caresses your cheek and leaves its salty flavour on your lips.\n",
  "The sails strain and creak in the fierce wind.\n",
  "The ship keels sharply to port.\n",
  "You notice a sudden eerie calm.\n",
  "Waves slam against the starboard side, spraying you with water.\n",
  "The ship rolls nauseatingly side-to-side.\n" ,
});

string
sounds()
{
return snd[random(6)];
}

public varargs int disembark(string what)
{
    int res;

    res = ::disembark(what);
    if(res && file_name(environment(this_player()))[0..8] == "/d/Avenir")
        STATSERV_LOG_EVENT("avisits", "Port13 through ship to Ansalon");
    return res;
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
