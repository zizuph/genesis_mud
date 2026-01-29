#pragma strict_types

inherit "/std/room";

#define OBJ "/w/clyptas/object/hawk"

object hawk;

public void

create_room()
{
    set_short("A ledge of a cliff outside a cave");

    set_long("On a rocky outcropping, behind you is an opening to a cave. " +
	"Thunderstorms have shaken up the serenity. Pink streaks of lightening  " +
	"sporadically flash and loud crashes of thunder can be heard. The sky is " +
	"gray and foreboding.\n");

	add_item( ({ "tree","trunk"}),
		"The trees are bare and dry.\n");

    add_item( ({ "bookshelf","bookshelves","books" }),
        "With all the soot on the walls, left from an obvious fire, " +
		"the books are clean and well taken care of.\n");
		
	add_item( ({ "desk"}),
		"The desk is dark, cherry wood, and almost black. The candles cast " +
		"circles of warm light on its shiny surface. Parchment, wax and " +
		"pots of ink lie out, as if someone was working on something and " +
		"was interrupted.\n");

    add_exit("/w/clyptas/workroom", "out");
	
	hawk = clone_object(OBJ);
    hawk->move (this_object() );
	
	}