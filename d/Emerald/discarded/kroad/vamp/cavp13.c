/*	This room was created by Jaypeg : 02/09/97
*/

inherit "/d/Emerald/kroad/vamp/cave_base";

#include "/d/Emerald/defs.h"
#include "/d/Emerald/kroad/vamp/vchasm.h"

int block_south();

void create_cave_room()
{

    set_noshow_obvious(1);

    set_short( "In a lightless, unnatural tunnel" );
    set_long( "   An eerie disquiet falls over you in this tunnel, "+ 
      "your skin crawls in warning. You sense an unnatural "+ 
      "darkness around you, a hungry thirst for the life that "+ 
      "beats within you.\n   The walls "+ 
      "around you are seeping some dark ichor, you think "+ 
      "the better of investigating further. Light seems to be "+ 
      "sucked into the darkness here, and you find yourself "+
      "unable to see any escape, nor tell what direction you "+
      "are heading.\n   Parts of the ceiling have " +
        "collapsed, making it difficult to walk around, and impossible " +
        "to venture any farther into the cave.\n\n" );


    add_prop( ROOM_I_LIGHT, -2 );
    add_prop(ROOM_I_INSIDE,1);

    add_item(({ "ceiling" }), "Parts of the ceiling have collapsed, " +
        "distributing large amounts of rubble throughout the cave, and " +
        "blocking progress farther south into the cave.\n");

    add_item(({ "rubble" }), "Chunks of rock from the ceiling litter " +
        "the cave floor, and completely block the southern portion of " +
        "the cave, except for a few small holes.\n");

    add_item(({ "north" }), "Rubble completely blocks the southern portion " +
        "of the cave, except for a few small holes.\n");

    add_item( ({"tunnel", "passage", "floor"}),
      "This narrow tunnel of unnatural silence and "+ 
      "darkness presses in apon you leaving you "+ 
      "feeling clammy and disoriented. The walls "+ 
      "drip some unspeakable ichor, and the floor "+ 
      "you cannot even see by lowering your light "+ 
      "source to it.\n" );
    add_item( ({"disquiet", "feeling"}),
      "There is a feeling of terror brewing within "+ 
      "you, the aura of unlife and chaos unspeakable "+ 
      "here makes you feel nauseous and panicky.\n" );
    add_item( ({"ichor", "moisture", "walls"}),
      "An undiscribable ichor seeps from the walls, "+ 
      "its moist surface being one of the few things "+ 
      "you can make out here in this tunnel amongst "+ 
      "the unnatural darkness.\n" );


    add_exit("cavp12", "north");
    add_exit("/d/Emerald/lake/beach/cave", "south", block_south, 5, 1);
}

int
block_south()
{
    string str;

    if (this_player()->query_guild_member_occ("Vampires of Emerald"))
    {
        str = " somehow manages to squeeze through a tiny hole in " +
              "the rubble.\n";

        write("You manage to squeeze through a hole.\n");
        tell_room(this_object(), ({ METNAME + str, NONMETNAME + str, "" }),
            this_player());

        return 0;
     }

     write("You can't possibly manage to squeeze through the wall of rubble.\n");
     return 1;
}

int
do_climb(string str)
{
    if (!parse_command(str, ({}), "'through' 'hole' / 'holes' / 'rubble'"))
    {
        notify_fail(capitalize(query_verb()) + " where?\n");
        return 0;
    }

    this_player()->command("$south");
    return 1;
}

void
init()
{
    ::init();
    add_action(do_climb, "climb");
    add_action(do_climb, "squeeze");
}
