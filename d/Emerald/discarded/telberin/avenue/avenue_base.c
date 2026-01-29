/* Base file for avenues in Telberin
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
    set_short("A wide avenue");
    set_long(avenue_desc());

    add_item(({"hedge"}), "The hedge is neatly trimmed and borders the "+
        "avenue.\n");
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
        "The flowers are ablaze with color here. They are beautiful " +
        "and fill the air with a sweet fragrance. Annuals and " +
        "perennials are planted to in numerous pots here and "  +
        "create a symphony of colors here.\n");
    add_item(({"tree", "trees"}),
        "Tall trees grow here. They line the avenue like " +
        "elven sentinels looking over the city. Birds sing in the " +
        "branches, filling the air with beautiful music.\n");
    add_item("birds",
        "You see colorful birds in the trees. Some are flying " +
        "around while others are sitting on branches, filling the " +
        "air with music.\n");
    add_item("sky",
        "The azure sky can be seen through the branches of the " +
        "trees. It is clear without a hint of bad weather.\n");
    add_item("rail",
        "The rail is composed of a hedge that has been clipped " +
        "in the shape of an fence. The top third of the rail is a " +
        "solid band. Under the band, the hedge has been clipped into " +
        "a criss-crossing lattice fashion. On the very top of the " +
        "rail, parts of the hedges have been trimmed into the form " +
        "of dolphins, fish, and other aquatic animals. The hedge " +
        "provides a secure fence, preventing any elves from falling " +
        "off off the avenue and into the lake.\n");
 
    set_tell_time(35);
    add_tell( "Some elven merchants pass by.\n");
    add_tell( "A proud courtier ignores you on her way to the castle.\n");
    add_tell( "The leaves rustle in the breeze.\n");
    add_tell( "A gentle breeze caresses your face.\n");
    add_tell( "Some birds sing in the trees.\n");
    add_tell( "Elven children run past you, laughing on their way.\n");
    add_tell( "A resident of the city smiles, passing you.\n");
    add_tell( "The florist picks some flowers for his shop.\n");
    add_tell( "You hear some joyful laughing nearby.\n");
    add_tell( "Some elves wander by.\n");
    add_tell( "The flowers fill the air with their fragrance.\n");
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
    switch(random(6))
    {
        case 0:
        return "   You stand on an elegant avenue. This avenue " +
        "runs around the outer limits of the city and is kept " +
        "clean of debris. It is made of solid diamond-shaped " +
        "blocks of marble which sparkle in the sunlight. The " +
        "avenue is shaded by countless trees that grow on along " +
        "the inner edge of the avenue. On the outer edge, a lovely " +
        "hedge grows. In between the trees are gardens full of " +
        "flowering bushes and flowers. ";
        break;
        case 1:
        return "   The avenue is wide and beautiful. It runs " +
        "alongside the outer edge of the city, surrounding the " +
        "city like a wall and is very clean. Shade trees grow " +
        "alongside it with gardens full of fragrant flowers and " +
        "bushes. An elegant hedge grows on the outer edge of the " +
        "avenue. Large diamond shaped blocks of marble make " +
        "up the avenue. They sparkle in the sunlight. ";
        break;
        case 2:
        return "   This part of the avenue runs alongside the " +
        "outer edge of the city. It is quite busy. A hedge grows " +
        "on the outer edge. Large trees shade the avenue and " +
        "grow on the inside of the avenue. Fragrant bushes and " +
        "flowers have been planted in gardens between the trees. " +
        "The avenue is wide and constructed of diamond shaped " +
        "blocks of marble that sparkles in the sunlight. The " +
        "elves show pride in their city by keeping the avenue clean. ";
        break;
        case 3:
        return "   You stand on a busy avenue on the outskirts of " +
        "Telberin. Numerous elves pass by you as they go about " +
        "their business. Fragrant bushes and plants grow alongside " +
        "the avenue. Towering over the avenue are large shade " +
        "trees. On the outside of the avenue is a hedge. The " +
        "avenue is constructed of diamond-shaped blocks of marble " +
        "that glisten in the sun. ";
        break;
        case 4:
        return "   The busy avenue is alive with color and " +
        "activity. The trees that grow along here offer shade for " +
        "those who travel along here. Their great branches reach " +
        "to the sky, offering respite from the sun to elves who " +
        "pass underneath them. The flowers and bushes planted " +
        "here fill the air with a sweet fragrance. A cool breeze " +
        "blows off the lake, cooling the city down. Birds sing " +
        "in the trees above you. On the outer edge of the avenue " +
        "grows a hedge. ";
        break;
        case 5:
        return "   The air is refreshing and clean here. " +
        "Flowers fill the air with fragrance. The avenue seems " +
        "unusually busy here as the elves scurry about their " +
        "business. But then, it seems that elves are always busy. " +
        "They seem to be ignoring you. A breeze blows off the " +
        "lake shaking the leaves softly in the branches. A hedge " +
        "grows here, protecting elves from falling into the lake. ";
        break;
        default:
        return "   You're on the avenue that encircles Telberin. " +
        "This avenue has been constructed of diamond-shaped " +
        "marble blocks. They stones twinkle in the sunlight. Great " +
        "trees grow along the inner edge of the avenue. Growing " +
        "under the branches are great plantings of fragrant and " +
        "colorful bushes and flowers. A beautiful hedge grows " +
        "along the outer edge of the avenue. It protects unwary " +
        "elves from falling into the lake. ";
     }
}
