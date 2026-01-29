/* Mortis 9.2014
 */

#include "../../local.h"
#include CLOCKH

inherit TOA_ROOMBASE;

string
query_to_jail()
{
    return "south";
}

void
reset_palan_room()
{
}

void
create_palan_room()
{
    SHORT("The Constable's bedchambers in the Tower of Arms");
    LONG("A marble walled bedchamber with an archway leading south, it is "
    + "hardly furnished with only a low bed.\n");

    ITEM(({"bed", "low bed", "furnishing", "furnishings", "bedchamber",
        "bedchambers"}), "The bedchamber is small and practically empty. It "
    + "contains only a low bed, little more than a cot with a thick mattress "
    + "and blanket.\n");

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

    EXIT(TOA + "toa67", "south", 0, 0);

    reset_palan_room();
}
