/*
 * The n,s,w archways must have oil (any) smeared over their runes before
 * they will let anyone other than the Constable or his guests pass.
 *
 * Mortis 9.2014
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

int nrstate, srstate, wrstate;
object tdoor;

/* prototypes */
string nrune_state();
string srune_state();
string wrune_state();

string
query_to_jail()
{
    return "south";
}

void
reset_palan_room()
{
    nrstate = 0;
    srstate = 0;
    wrstate = 0;
}

void
create_palan_room()
{
    SHORT("The Constable's chambers in the Tower of Arms");
    LONG("A high-ceilinged chamber with a mural on the floor, archways lead "
    + "from here, and an iron door is set into the east wall. The distant "
    + "chink of armour and clump of bootsteps can barely be heard from the "
    + "corridors outside.\n");

    add_prop(MAGIC_AM_MAGIC,({30,"abjuration"}));

    ITEM(({"arch", "arches", "archway", "archways"}), "There are three "
    + "marble archways, north, south, west. Each is marked with an arcane "
    + "rune and a carved symbol of an open eye. You can examine then "
    + "individually (e.g. exa 'n rune' or 'north rune').\n");
    ITEM(({"rune", "runes", "arcane rune", "arcane runes", "symbol",
        "symbols", "eye", "eyes", "carved symbol", "carved symbols"}), "The "
    + "archways north, south, and west are each carved with the symbol of "
    + "an eye looking down into the room and an arcane rune above the "
    + "eye.\nYou feel certain there is magic here.\nYou can examine each rune "
    + "individually (e.g. exa 'n rune' or 'north rune'), but be careful.\n");
    ITEM(({"mural", "murals"}), "Small tiles have been arranged ingeniously "
    + "to create the scene of a mailed warrior with a downward pointing "
    + "sword kneeling before the lords of Palanthas. The great palatial "
    + "tower is in the background behind them, and yellow tiles border "
    + "the mural in a circle.\n");
    ITEM(({"n rune", "north rune"}), "@@nrune_state@@");
    ITEM(({"s rune", "south rune"}), "@@srune_state@@");
    ITEM(({"w rune", "west rune"}), "@@wrune_state@@");

    add_smell("vampire", "The air is stale and unvisited but with a spark of "
    + "arcane tang to it. Your fangs throb with anticipation as you sense hot "
    + "blood pumping through a great many hearts east.");
    add_smell("morgul", "The air is stale with the tang of air charged for "
    + "long periods with arcane magic, likely an abjuration.");
    add_smell("human", "The air is a little stale. You smell a little paper, "
    + "some polishes for armaments, but otherwise it's clean.");
    add_smell("elf", "The air is clean but stale. You smell papers west. All "
    + "about you smell the charge of magic in the air.");
    add_smell("goblin", "The air is good. Smells like weapons and armour "
    + "have been cleaned here.");
    add_smell("dwarf", "The air is good. Weapons and armour have been "
    + "tended to and polished here. Something in the air unnerves you, and "
    + "the hair on your back raises in response.");
    add_smell("hobbit", "The air is stuffy and could use a window opening. "
    + "Paper smells come from the west and bedding smells from the north.");
    add_smell("gnome", "The air is good but stale and unvisited. A human "
    + "must live to the north and write on papers to the west. The smells of "
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
    + "paper smells to the west, maybe blanks north, and oh what's that?!? "
    + "You sniff magic all around you! Maybe more south!");
    add_smell("drow", "The sterile air here would indicate the place is "
    + "clean by human standards. You detect the smells of human bedding "
    + "north and papers west. Your keen sense of smell detects magic "
    + "protecting the area. Tread with care, drow.");
    add_smell("noldor", "The air is stale and unpleasant. A human's stink "
    + "is north. The smell of papers and books waft from the west. The iron "
    + "door reeks of strong oils, and all around is the scent of strong "
    + "abjuration magic with even more magic coming from the south.");
    add_smell("uruk", "There's so much scent of manflesh in this place, it's "
    + "hard to concentrate, but you also smell armaments.");
    add_smell("presence", "You don't pick up much in your current state.");
    add_smell("unknown", "The air is a little stale with a hint of magic, "
    + "but what the heck race are you?!?  Why not <mail krynn> for fun?");

    CMD(({"n rune", "north rune"}), "smear", "@@smear_north@@");
    CMD(({"s rune", "south rune"}), "smear", "@@smear_south@@");
    CMD(({"w rune", "west rune"}), "smear", "@@smear_west@@");

    EXIT(TOA + "toa67n", "north", "@@go_north@@", 0);
    EXIT(TOA + "toa67s", "south", "@@go_south@@", 0);
    EXIT(TOA + "toa67w", "west", "@@go_west@@", 0);
    EXIT(TOA + "toa71", "up", 0, 0);

    tdoor = clone_object(TOA + "doors/toa_constable_door44");
    tdoor->move(TO);

    reset_palan_room();
}

void
auto_door()
{
    tdoor->reset_door();
}

string
nrune_state()
{
    int spellskill = TP->query_skill(SS_SPELLCRAFT);
    string rdesc = "A mysterious rune.\n";

    if (spellskill < 20)
    {
        rdesc = "The rune over the north archway is menacing. You can't "
        + "make heads or tails of it, so you have absolutely no idea "
        + "what it might do to you if you try going north.\n";
    }
    else
    {
        rdesc = "The rune over the north archway is a Krynnish high "
        + "sorcery rune of passage protection. You've heard they can "
        + "sometimes be fooled by smearing their detection area with "
        + "something dark, but it can be dangerous. They probably "
        + "have tamper protection.\n";
    }

    if (nrstate != 0)
    {
        rdesc += "The rune's carved eye symbol has been smeared over with "
        + "something dark and oily.\n";
    }

    return rdesc;
}

string
srune_state()
{
    int spellskill = TP->query_skill(SS_SPELLCRAFT);
    string rdesc = "A mysterious rune.\n";

    if (spellskill < 20)
    {
        rdesc = "The rune over the south archway is menacing. You can't "
        + "make heads or tails of it, so you have absolutely no idea "
        + "what it might do to you if you try going south.\n";
    }
    else
    {
        rdesc = "The rune over the south archway is a Krynnish high "
        + "sorcery rune of passage protection. You've heard they can "
        + "sometimes be fooled by smearing their detection area with "
        + "something dark, but it can be dangerous. They probably "
        + "have tamper protection.\n";
    }

    if (srstate != 0)
    {
        rdesc += "The rune's carved eye symbol has been smeared over with "
        + "something dark and oily.\n";
    }

    return rdesc;
}

string
wrune_state()
{
    int spellskill = TP->query_skill(SS_SPELLCRAFT);
    string rdesc = "A mysterious rune.\n";

    if (spellskill < 20)
    {
        rdesc = "The rune over the west archway is menacing. You can't "
        + "make heads or tails of it, so you have absolutely no idea "
        + "what it might do to you if you try going west.\n";
    }
    else
    {
        rdesc = "The rune over the west archway is a Krynnish high "
        + "sorcery rune of passage protection. You've heard they can "
        + "sometimes be fooled by smearing their detection area with "
        + "something dark, but it can be dangerous. They probably "
        + "have tamper protection.\n";
    }

    if (nrstate != 0)
    {
        rdesc += "The rune's carved eye symbol has been smeared over with "
        + "something dark and oily.\n";
    }

    return rdesc;
}

int
smear_north()
{
    int trapskill = TP->query_skill(SS_FR_TRAP);
    int trap_difficulty = 10 + random(20); // Should give non-thieves 50/50
    int fire_damage = 500;
    
    if (!present("oil", TP))
    {
        TP->catch_msg("You don't have anything sufficiently dark or oily "
        + "with which to smear the rune.\n");
        return 1;
    }

    if (nrstate != 0)
    {
        TP->catch_msg("The carved eye beneath the rune over the north "
        + "archway is already smeared with oil.\n");
        return 1;
    }

    if (trapskill > trap_difficulty)
    {
        nrstate = 1;
        write("You deftly smear oil over the carved eye beneath the "
        + "rune over the north archway temporarily defeating the rune's "
        + "protections.\n");
        say(QCTNAME(TP) + " smears dark oil over the north archway.\n");
        return 1;
    }
    else
    {
        write("You accidentally touch the rune as you try to smear oil "
        + "over the carved eye below it.\n\nThe rune blasts you with a fiery "
        + "explosion!!!\n");
        say(QCTNAME(TP) + " touches the rune above the north archway and is "
        + "blown back by a fiery explosion!!!\n");

        fire_damage = fire_damage * (100 - TP->query_magic_res(MAGIC_I_RES_FIRE)) / 100;
        TP->heal_hp(-fire_damage);

        if (TP->query_hp() <= 0)
        {
            TP->do_die(E(TP));
        }
        
        return 1;
    }
}

int
smear_south()
{
    int trapskill = TP->query_skill(SS_FR_TRAP);
    int trap_difficulty = 10 + random(20); // Should give non-thieves 50/50
    int fire_damage = 500;
    
    if (!present("oil", TP))
    {
        TP->catch_msg("You don't have anything sufficiently dark or oily "
        + "with which to smear the rune.\n");
        return 1;
    }

    if (srstate != 0)
    {
        TP->catch_msg("The carved eye beneath the rune over the south "
        + "archway is already smeared with oil.\n");
        return 1;
    }

    if (trapskill > trap_difficulty)
    {
        srstate = 1;
        write("You deftly smear oil over the carved eye beneath the "
        + "rune over the south archway temporarily defeating the rune's "
        + "protections.\n");
        say(QCTNAME(TP) + " smears dark oil over the south archway.\n");
        return 1;
    }
    else
    {
        write("You accidentally touch the rune as you try to smear oil "
        + "over the carved eye below it.\n\nThe rune blasts you with a fiery "
        + "explosion!!!\n");
        say(QCTNAME(TP) + " touches the rune above the south archway and is "
        + "blown back by a fiery explosion!!!\n");

        fire_damage = fire_damage * (100 - TP->query_magic_res(MAGIC_I_RES_FIRE)) / 100;
        TP->heal_hp(-fire_damage);

        if (TP->query_hp() <= 0)
        { TP->do_die(E(TP)); }
        
        return 1;
    }
}

int
smear_west()
{
    int trapskill = TP->query_skill(SS_FR_TRAP);
    int trap_difficulty = 10 + random(20); // Should give non-thieves 50/50
    int fire_damage = 500;
    
    if (!present("oil", TP))
    {
        TP->catch_msg("You don't have anything sufficiently dark or oily "
        + "with which to smear the rune.\n");
        return 1;
    }

    if (wrstate != 0)
    {
        TP->catch_msg("The carved eye beneath the rune over the west "
        + "archway is already smeared with oil.\n");
        return 1;
    }

    if (trapskill > trap_difficulty)
    {
        wrstate = 1;
        write("You deftly smear oil over the carved eye beneath the "
        + "rune over the west archway temporarily defeating the rune's "
        + "protections.\n");
        say(QCTNAME(TP) + " smears dark oil over the west archway.\n");
        return 1;
    }
    else
    {
        write("You accidentally touch the rune as you try to smear oil "
        + "over the carved eye below it.\n\nThe rune blasts you with a fiery "
        + "explosion!!!\n");
        say(QCTNAME(TP) + " touches the rune above the west archway and is "
        + "blown back by a fiery explosion!!!\n");

        fire_damage = fire_damage * (100 - TP->query_magic_res(MAGIC_I_RES_FIRE)) / 100;
        TP->heal_hp(-fire_damage);

        if (TP->query_hp() <= 0)
        {
            TP->do_die(E(TP));
        }
        
        return 1;
    }
}

int
go_north()
{
    /* If the person is the Constable, let them pass. */
    if (present("iletter", TP))
    {
        return 0;
    }

    if (nrstate == 0)
    {
        write("A force across the archway bounces you back.\n");
        say(QCTNAME(TP) + " tries to go north but walks into an invisible "
        + "wall\n");
        return 1;
    }

    return 0;
}

int
go_south()
{
    /* If the person is being dragged by the Constable under arrest, let
     * them pass. */
    if (present("chief_para", TP))
    {
        return 0;
    }

    /* If the person is the Constable, let them pass. */
    if (present("iletter", TP))
    {
        return 0;
    }

    if (srstate == 0)
    {
        write("A force across the archway bounces you back.\n");
        say(QCTNAME(TP) + " tries to go south but walks into an invisible "
        + "wall\n");
        return 1;
    }

    return 0;
}

int
go_west()
{
    /* If the person is the Constable, let them pass. */
    if (present("iletter", TP))
    {
        return 0;
    }

    if (wrstate == 0)
    {
        write("A force across the archway bounces you back.\n");
        say(QCTNAME(TP) + " tries to go west but walks into an invisible "
        + "wall\n");
        return 1;
    }

    return 0;
}
