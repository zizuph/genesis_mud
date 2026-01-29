/* Mortis 9.2014
 */

#include <macros.h>
#include <ss_types.h>
#include <living_desc.h>
#include <state_desc.h>
#include <composite.h>
#include <filter_funs.h>
#include "../../local.h"
#include CLOCKH

inherit TOA_ROOMBASE;

string
query_to_jail()
{
    return "enter portal";
}

void
reset_palan_room()
{
}

void
create_palan_room()
{
    SHORT("The Constable's portal room in the Tower of Arms");
    LONG("A marble walled office with an archway leading north. A green "
    + "stone ring nearly three meters in diameter stands before the south "
    + "wall.\n");

    add_prop(MAGIC_AM_MAGIC,({50,"conjuration"}));

    ITEM(({"green stone", "stone ring", "green ring", "ring", "portal"}),
      "Constructed of bricks of pale, green stone, the ring is set into the "
    + "floor in the south facing the archway in the north. Closer inspection "
    + "of the bricks reveal small, carved runes.\n");
    ITEM(({"brick", "bricks", "rune", "runes"}), "Each brick in the green "
    + "stone ring bears a small arcane rune carved into it. You sense they "
    + "are conjuration magic and possibly portal runes.\n");

    add_smell("vampire", "The air is stale and unvisited but with a spark of "
    + "arcane tang to it. Your fangs throb with anticipation as you sense hot "
    + "blood pumping through a great many hearts southeast.");
    add_smell("morgul", "The air is stale with the tang of air charged for "
    + "long periods with arcane magic, likely an abjuration.");
    add_smell("human", "The air is a little stale. You smell a little paper, "
    + "some polishes for armaments, but otherwise it's clean.");
    add_smell("elf", "The air is clean but stale. You smell papers southwest. All "
    + "about you smell the charge of magic in the air.");
    add_smell("goblin", "The air is good. Smells like weapons and armour "
    + "have been cleaned here.");
    add_smell("dwarf", "The air is good. Weapons and armour have been "
    + "tended to and polished here. Something in the air unnerves you, and "
    + "the hair on your back raises in response.");
    add_smell("hobbit", "The air is stuffy and could use a window opening. "
    + "Paper smells come from the southwest and bedding smells from the north.");
    add_smell("gnome", "The air is good but stale and unvisited. A human "
    + "must live to the north and write on papers to the southwest. The smells of "
    + "magically charged air are around you and strong to the south, also.");
    add_smell("minotaur", "The air is good. The smell of man is thick here "
    + "especially to the north.");
    add_smell("halfhuman", "The air is a little stale. You smell a little paper, "
    + "some polishes for armaments, but otherwise it's clean.");
    add_smell("halfelf", "The air is a little stale. You smell a little paper, "
    + "some polishes for armaments, but otherwise it's clean.");
    add_smell("orc", "There's so much scent of manflesh in this place, it's "
    + "hard to concentrate, but you also smell armaments.");
    add_smell("hobgoblin", "The clean air would indicate humans keep this "
    + "place well tended, but it's stale so they likely don't come here "
    + "much. However, you do smell polishes and oils for weapons and "
    + "armour used here recently.");
    add_smell("kender", "The air is fine, maybe dusty. You smell interesting "
    + "paper smells to the southwest, maybe blanks north, and oh what's that?!? "
    + "You sniff magic all around you! Maybe more south!");
    add_smell("drow", "The sterile air here would indicate the place is "
    + "clean by human standards. You detect the smells of human bedding "
    + "north and papers southwest. Your keen sense of smell detects magic "
    + "protecting the area. Tread with care, drow.");
    add_smell("noldor", "The air is stale and unpleasant. A human's stink "
    + "is north. The smell of papers and books waft from the southwest. The iron "
    + "door reeks of strong oils, and all around is the scent of strong "
    + "abjuration magic with even more magic coming from the south.");
    add_smell("uruk", "There's so much scent of manflesh in this place, it's "
    + "hard to concentrate, but you also smell armaments.");
    add_smell("presence", "You don't pick up much in your current state.");
    add_smell("unknown", "The air is a little stale with a hint of magic, "
    + "but what the heck race are you?!?  Why not <mail krynn> for fun?");

    CMD(({"ring", "portal"}), "enter", "@@enter_portal");

    EXIT(TOA + "toa67", "north", 0, 0);

    reset_palan_room();
}

// Teleport by the jail in the palace at city center.
int
enter_portal()
{
    write("There is a flash of green light, and you feel yourself travelling "
    + "through strange space.\n");
    say(QCTNAME(TP) + " enters the green stone ring.\nIn a flash of pale, "
    + "green light, " + HE(TP) + " is gone!\n");

    TP->move(PALACE + "hall10");
    TP->command("look");
    return 1;
}