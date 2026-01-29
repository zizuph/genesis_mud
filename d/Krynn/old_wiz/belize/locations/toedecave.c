/* Forest coded by Lord Rastlin */
/* Modified by Teth, Feb.13,96  */

#include "/d/Krynn/common/defs.h"
#include "local.h"
#include <macros.h>

inherit FORINROOM;

object toede;

#define COMB    OBJ + "tcomb"

int comb_found;

void
reset_solace_room()
{
    {  comb_found = 0;
    }

    {

    if (toede)
      return;
    toede = clone_object(MONSTER + "toede");
    toede->move_living("xx", TO);
    toede->seq_new("do_thing");
    toede->seq_addfirst("do_thing",
                    ({"@@arm_me", "@@start_patrol"}));
    }
}

void
create_solace_room() 
{
    set_short("An impressive cave");
    set_long("This impressive cave is the home of something different, " +
             "definitely not a goblin. It's certainly not tidy, but the " +
             "scent is more along the lines of...hobgoblin...instead of " +
             "goblin. The amount of items here also suggests the owner " +
             "of this cave is someone mildly important. In one area " +
             "sits a table and chair, while a straw bed rests " +
             "haphazardly against the far wall. As you rest in the room, " +
             "you find that the smell does not get any better, it gets " +
             "worse. The walls are typically composed of greyish rock.\n");
    add_item("table", "This table might actually be worth something " +
             "if it wasn't missing a leg. Instead it is propped against " +
             "the wall. On the table lies old food and a piece of paper.\n");
    add_item(({"food", "old food"}), "Mould makes this an unattractive " +
             "meal. It's probably been sitting here for quite a while.\n");
    add_item(({"paper", "piece of paper"}), "The note reads:\n\n" +
             "Toede! You miserable fool!\n\n" +
             "I want you to triple your patrols in Solace! The blue " +
             "crystal staff must be retrieved at all costs!\n\n" +
             "Lord Verminaard\n");
    add_item("smell", "Cloying, it might be attractive to a fly. To " +
             "you, it is just plain nauseating.\n");
    add_item(({"bed", "straw bed"}), "Rotting straw makes up this bed, " +
             "so you can't understand how anyone would want to sleep in " +
             "it. Apparently, someone does though.\n");
    add_item(({"straw", "rotting straw"}), "The straw is most likely " +
             "from oats or wheat. Perhaps it is confiscated from " +
             "Northfields.\n");
    add_item(({"rock", "walls", "wall", "greyish rock", "grey rock"}),"The " +
             "walls of the cave are made out of some worn igneous rock. " +
             "It is most likely granite or andesite.\n");
    add_search(({"bed","straw bed"}),2,"find_comb",1);

    add_exit(TDIR + "hill3", "south");

    reset_room();

    DARK;
    
    set_alarm(1.0,0.0,"reset_room");
}

string
find_comb(object who, string what)
{
    if (comb_found)
    {
    return 0;
    }

    say(QCTNAME(who) + " discovers something on the bed!\n");
    clone_object(COMB)->move(TO, 1);
    comb_found = 1;

    return "You discover a toothless comb on the bed.\n";
}





