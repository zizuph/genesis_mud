/* Base file for inner avenue of Telberin
 * Based on the Master room for the forest of Rohim
 * Created 19 April, 1995 by Mayhem, Liege of Emerald
 */
inherit "/std/room";
inherit "/d/Emerald/lib/room_tell";
#include "/d/Emerald/defs.h"
#include "default.h"
 
void create_avenue();
string avenue_desc();
 
void create_room()
{
    set_short("A wide avenue in Telberin");
    set_long(avenue_desc());
 
    add_item(({"house", "houses"}),
        "The house are exquisitely crafted of different " +
        "colored marble blocks. The houses are large and beautiful. " +
        "Visitors and dwelles of the houses come and go from many " +
        "of the houses.\n");
    add_item(({"ground", "road", "avenue"}),
        "The avenue is constructed of red and white marble " +
        "blocks. They are laid into the ground in a horizontal " +
        "pattern. The road is very clean of any leaves or old " +
        "blossoms.\n");
    add_item(({"bushes", "shrubs"}),
        "Many fragrant and colorful bushes grow here. They grow in " +
        "groups between the trees. Some have been expertly clipped " +
        "into topiaries.\n");
    add_item("flowers",
        "The flowers are bright and colorful. Their beautiful " +
        "fragrance fills the air. They hang from graceful poles " +
        "which have be set into the ground under the trees. "  +
        "Their bright colors create a living symphony here.\n");
    add_item(({"tree", "trees"}),
        "Tall trees grow on either side of the avenue. The are " +
        "ancient and well cared for. Numerous birds sing in the " +
        "branches, filling the air with beautiful music.\n");
    add_item("birds",
        "many colorful birds fill the trees. Some fly " +
        "around while others are sitt on branches, filling the " +
        "air with music. Some of the seabirds rest in the bushes, " +
        "watching from their perches everything that goes on below " +
        "them. Occaisonally, they dive from the trees and head out " +
        "to the lake.\n");
    add_item("sky",
        "The azure sky can be seen through the branches of the " +
        "trees. It is clear without a hint of bad weather.\n");
 
    set_tell_time(35);
    add_tell( "Some elven merchants pass by.\n");
    add_tell( "A proud courtier ignores you on her way to the castle.\n");
    add_tell( "The leaves rustle in the breeze.\n");
    add_tell( "A gentle breeze caresses your face.\n");
    add_tell( "Some birds sing in the trees.\n");
    add_tell( "Elven children run past you, laughing on their way.\n");
    add_tell( "A chipmunk chatters at you from the branches.\n");
    add_tell( "Butterflies land gently on the flowers.\n");
    add_tell( "A hummingbird darts in and out of the flowers.\n");
    add_tell( "A bumblebee visits each flower here.\n");
    create_avenue();
}
 
create_avenue()
{
}
 
string
avenue_desc()
{
    switch(random(3))
    {
        case 0:
        return "   You stand on an elegant avenue. It runs " +
        "through the center of Telberin. The road is very " +
        "clean. Crowds of elves jostle past you as they " +
        "travel to the castle. Lovely trees grow up and over " +
        "the avenue here. Hanging baskets of blossoms swing " +
        "from poles here. They swing gently in the breeze. ";
        break;
        case 1:
        return "   The avenue is wide and beautiful. As it " +
        "runs through the center of the city, it winds its way " +
        "through a tunnel of trees and hanging baskets of " +
        "flowers. The flowers are suspended at the end of " +
        "graceful poles. The throng of elves is unusually strong " +
        "here. ";
        break;
        case 2:
        return "   This part of the avenue runs alongside the " +
        "outer edge of the city. It is quite busy. Large trees " +
        "shade the avenue and grow on both sides of the avenue. " +
        "Fragrant bushes and flowers have been planted in gardens " +
        "between the trees. Many visitors push and shove past you " +
        "as they gawk at the city. You see houses along the avenues " +
        "with people. They are beautiful as they reflect individual " +
        "tastes of their owners. ";
        break;
        default:
        return "   You notice that the avenue here is unusually " +
        "peaceful. How wonderful. Trees add to the serene " +
        "feeling here. The branches barely move in the breeze that " +
        "blows off the lake. Birds quietly sing in the branches, " +
        "and seabirds fly overhead. Hanging baskets of flowers " +
        "sway gently above you. All seems quiet and relaxing here ";
     }
}
