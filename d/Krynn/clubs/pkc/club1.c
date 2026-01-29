/* created by Aridor 12/01/93 */

inherit "/std/room";

#include "clubdefs.h"

create_room()
{
    set_short("Club Hall");
    set_long("You are standing in the entrance hall of the Prestigious " +
	     "Knights' Club. The floor is laid out with black marble, " +
	     "contrasting the white marble of the ceiling. Two rows of " +
	     "columns support the ceiling, and chandeliers hang in between. " +
	     "The top third of the walls has windows set into it, allowing " +
	     "plenty of light in to flood the room. Due to the stone floor " +
	     "every step can be heard echoing through the halls. Your " +
	     "attention is drawn towards the paintings that line the walls. " +
	     "A large open door leads into another room further west, and a " +
	     "smaller door, also opened, leads north. The Knights' Avenue, " +
	     "outside, can be seen to the east.\n");
    
    INSIDE;
    LIGHT;
    
    add_exit("/d/Krynn/solamn/palanthas/nobles/noble_tower1","northeast");
    add_exit(CLUB + "club2","west");
    add_exit(CLUB + "club3","north");
    
    
    add_item(({"hall"}),
	     "This is a very open spaced hall with a black marble floor and " +
	     "a white marble ceiling. The pillars supporting the ceiling " +
	     "are contrasting the black and white of the floor ceiling, " +
	     "being black at their bottom and gradually turning to grey and " +
	     "then white underneath the ceiling. Windows in the upper parts " +
	     "of the walls allow plenty of light into the room.\n");
    add_item(({"paintings","painting","picture","pictures"}),
	     "These paintings have been created by perfectionist artists. " +
	     "You almost get the feeling people and monsters displayed " +
	     "will come back to life any second and just jump to the floor " +
	     "to continue with whatever they were busy with. You can see " +
	     "landscapes on the paintings as well, providing a very natural " +
	     "background to the skirmish and battle scenes portrayed.\n");
    add_item(({"battle", "battle scene", "battle scenes", "skirmish",
		 "skirmishes"}),
	     "The first thing you notice as you look closer at the battle " +
	     "scenes is the different way of characterization of the two " +
	     "parties in the fights. The knights, of course, appear in " +
	     "gleaming platemails, carefully polished, in silverish, golden " +
	     "or white color. Opposing these knights are creatures, " +
	     "frightening the onlooker, YOU, to the very core. Some of " +
	     "these creatures look remotely human, and you recognize ogres, " +
	     "goblins, and several of these things, these draconians, with " +
	     "all the hatred they possibly could bear gleaming in their " +
	     "eyes. All of these evil creatures are kept in darker tones, " +
	     "casting shadows across the landscape.\n");
    add_item(({"monsters","monster","creature","creatures","draconian",
		 "draconians"}),
	     "The evil creatures you recognize as draconians seem to be the " +
	     "wildest lot of them all. Mercilessly, they seem to hack at " +
	     "the brave knights, and many a wound has been inflicted on " +
	     "both parties. Blood drips from these open wounds and crudely " +
	     "fastened bandages do little to prevent this. Looking closer " +
	     "you can make out several different types of draconians, all " +
	     "of them have a grim reptilian head: narrowfaced ones, which " +
	     "are by far the smallest of their kind; broadfaced draconians, " +
	     "with multicolored sparks of fire sprouting from their clawed " +
	     "hands; The meanfaced draconians, bloodlust gleaming in their " +
	     "eyes, eager to kill; The uglyfaced draconian, much bigger and " +
	     "more impressive than the above mentioned, ready for anything, " +
	     "with hate for everything different in its eyes; Last, but " +
	     "most definitely not least, the evilfaced draconian, biggest " +
	     "of them all, leaving even its uglyfaced companions appear " +
	     "tiny.\n");
    add_item(({"windows","window"}),
	     "There are windows high up just below the ceiling, allowing " +
	     "plenty of light into the hall.\n");
    add_item(({"marble"}),
	     "The floor of the hall, the columns supporting the ceiling, as " +
	     "well as the ceiling itself are made of marble. The marble " +
	     "itself is of exquisite quality. No crazes can be found and " +
	     "the coloring is very regular.\n");
    add_item(({"column","columns","row","rows"}),
	     "The columns are made of marble, and contrasting the floor and " +
	     "ceiling with their coloring, the columns are white at the " +
	     "bottom and black at top. There are two rows of six columns " +
	     "each, aligned in east-west direction. The columns itself are " +
	     "rather featureless, except a few ornaments at the floor and " +
	     "right under the ceiling.\n");
    add_item(({"ornaments","ornament"}),
	     "The ornaments at the columns are marble roses, black at the " +
	     "bottom of the column and white at the ceiling.\n");
    add_item(({"knight","knights","people"}),
	     "The knights, opposing these creatures of the dark, all wear " +
	     "gleaming platemails, carefully polished, in silver, golden or " +
	     "white colors. They all stand proud, selflessly devoting their " +
	     "lives to Paladine. You can see that some of these knights are " +
	     "wearing ornamented scabbards, they appear even more fierce " +
	     "and devoted than the others, if that is possible. This " +
	     "ornamented scabbard identifies them as supporters of the " +
	     "Prestigious Knights' Club, and if you believe that you " +
	     "should 'support the Prestigious Knights' Club' as well, do " +
	     "this in the representative chamber of the club.\n");
    add_item(({"door","doors", "opening"}),
	     "There is a large open door made from wood leading to another " +
	     "room in the west, and a small open door decorated with satin " +
	     "leading to the north. An opening, not a door, leads outside " +
	     "the Club onto Knights' Avenue.\n");
    add_item(({"floor"}),
	     "The floor is made of black marble.\n");
    add_item(({"ceiling"}),
	     "The ceiling is made of white marble.\n");
    add_item(({"landscapes","landscape","background"}),
	     "The landscapes on the pictures only provides the background " +
	     "for the battles taking place there. Every picture displays " +
	     "a different background, from mountainous areas with rocks and " +
	     "little green to forest glades, with plenty of greenery " +
	     "around, but also scenes in the snow and ice.\n");
    add_item(({"outside"}),
	     "Looking outside the opening to Knights' Avenue, you can see " +
	     "trees line the street, and grass growing everywhere.\n");
    add_item(({"grass","tree","trees"}),
	     "Unlike the landscapes displayed in the pictures, the trees " +
	     "and grass outside are real.\n");
    add_item(({"mountains","mountain","area","rocks","rock","green","greenery",
		 "glade","forest","snow","ice"}),
	     "With skilled hands, the painters have created something " +
	     "almost real.\n");
    add_item(({"chandelier","chandeliers"}),
	     "These are heavy gold plated chandeliers, you can count three " +
	     "of them, arranged in the middle between the two rows of " +
	     "columns. There are many candles on each of them, but unlit " +
	     "since it is light outside.\n");
    add_item(({"candle","candles"}),
	     "There are many candles on each of the three chandeliers.\n");
    add_item(({"walls","wall"}),
	     "There are four walls to this room, on each of them are many " +
	     "paintings which look interesting, there are also two doors, " +
	     "one to the north and one to the west, and an opening leading " +
	     "outside to the east.\n");
    add_cmd_item(({"columns","column"}),"climb",
		 "The column is too thick and slippery to do that.\n");
}

