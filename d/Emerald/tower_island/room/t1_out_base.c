#include "../defs.h"

inherit TOWERISL_BASE;

void
create_t1_room()
{
}

nomask void
create_towerisl_room()
{
    add_item(({"tower", "stone tower", "prison"}),
        "This dark stone structure rises out of the earth high into " +
	"the sky. Ravens circle the top of the tower, dancing in and " +
        "out of the clouds.");
    add_item(({"path", "cobblestone path", "cobblestones"}),
        "The stones that make up the path fit tightly against one" +
        "another. This path looks well used, but also well maintained." +
        "None of the blocks are broken or cracked and the path is " +
        "extremely clean.\n");
    add_item(({"raven", "ravens", "birds"}),
        "They are too far away to get a really good look at, though " +
        "their black feathers and loud call clearly identify them as " +
        "ravens.\n");
    add_item(({"bushes", "brambles", "brush"}),
        "Bushes and brambles line the side of the walkway. As you look " +
        "over those nearest you, you see row upon row of sharp, thorny " +
        "plants. These plants get so thick that you cannot see past a " +
        "few feet into the brush.\n");
    add_item(({"sharp plants", "thorny plants", "thorns", "plants"}),
        "They look as though it would really hurt to walk through them. " +
        "You realize that they were probably planted to keep people from " +
        "straying off the path.\n");

    create_t1_room();
}

void
add_shore()
{
    set_short("Shore of Lake Telberin");
    set_em_long("The crystal clear water of Lake Telberin gently laps " +
                "against the rocky shore below your feet. You stand on " +
                "a cobblestone path that runs along the shore and further " +
                "into land. Bushes and brambles grow thickly just off the " +
                "path which leads towards the tower.\n"); 
    add_item(({"beach", "shore", "rocky shore", "rocks"}),
        "Rocks of varying sizes and shapes sit along the shoreline. It " +
        "looks as though many large, jagged stones were placed deliberately " +
        "just below the waterline.\n");
    add_item(({"stones", "stone", "jagged stones", "jagged rocks"}),
        "These large, jagged stones sit just below the waterline. You imagine " +
        "that it would be very hard to successfully land a ship on this island " +
        "without knowing exactly how the rocks were layed out.\n");
}

void
add_walkway()
{
    set_short("On path");
    set_em_long("You are traveling along a cobblestone path between the " +
                "tower and the shoreline. You notice the tower rising up " +
                "from the earth a little ways to the north. Bushes and " +
                "brambles line the path, ensuring that you do not stray " +
                "off the marked path.\n");
}

void
add_bramble_room()
{
    set_short("In brambles");
    set_em_long("You are standing in the middle of a thick patch of brambles " +
                "The grey tower rises up above you, but you cannot see the " +
                "hole that you fell from.\n");
    add_item("hole",
        "You know that it must be up there somewhere, but you cannot see it from " +
        "where you are standing.\n");
}    