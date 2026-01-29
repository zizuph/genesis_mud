inherit "/std/room";
#include "/d/Calia/abbrev.h"
 
 
void
create_room()
{
    set_short("Zima's private chambers");
 
    set_long(break_string(
        "This triangular chamber of black marble is a meeting room where " +
        "discussions " +
        "can be held free of the snooping eyes of others.  Tall silver " +
        "candlesticks sit in northwestern and southern corners of the "  +
        "chamber, each holding red columned candles, their flames " +
        "giving a secretive aura to the room.  A massive oak table sits " +
        "in the center of the chamber, around which Zima and his guests " +
        "discuss matters of importance and frivolity.  Crafted of white " +
        "ivory into the black marble floor is a mysterious symbol.  " +
        "An arched passageway leads back to the central chamber through " +
        "the northeastern corner.\n",70));
 
    add_item("candlesticks", break_string(
        "Tall silver candlesticks, crafted by the finest silversmiths of " +
        "Argos, each rises up from a fanned base, twisting to a " +
        "pedastal atop each, where thick red candles are resting.\n",70));
 
    add_item("candles", break_string(
        "Thick columned candles sitting atop silver candlesticks in " +
        "the corners of the chamber, their crimson wax giving life "  +
        "to dancing flames which seem to exude a mysterious seclusion.\n",70));
 
    add_item("table", break_string(
        "Made of thick polished oak, its legs carved in the shape of lions " +
        "paws, this table sits in the center of the room and provides " +
        "a focal point for the discussions held here.\n",70));
 
    add_item("symbol", break_string(
        "Crafted into the black marble floor with white ivory, this " +
        "mysterious symbol is the greek letter KAPPA.\n",70));
 
    add_item("passageway", break_string(
        "An arched passageway, framed with shining silver, it leads " +
        "into the central chamber through the northeastern corner.\n",70));
 
    add_exit("/d/Calia/zima/workroom","northeast",0);
 
}
query_prevent_snoop() { return 1; } 
 
