/* Mortis 11.2005
 * Alleys ne-ish?
 */

#include "../local.h"
#include CLOCKH
#include <macros.h>

inherit MONKS_BASE;

int door_open = 0;

void
reset_palan_room()
{
    if(door_open)
        door_open = 0;
}

string
query_to_jail()
{
  return "south";
}

nomask public string
get_time_desc()
{
    string desc = "";
	string road = "  Muest street curves east through a somewhat dense area "
	+ "of shops, homes, and buildings and south towards Old Circle and the "
	+ "city wall.  To the southeast an alley leads to a modest, one-story, "
	+ "marble shop wedged in between larger buildings.\n";
    switch(GET_TIMEOFDAY)
    {
    case TOD_DAWN:
	desc += "The worn marble of Muest street and its buildings "
	+ "glows in " + one_of_list(({"pale purple ", "soft pink ",
	  "pale orange ", "grey and pink "})) + "hues as the sun peeks above the "
	+ "mountains in the east.  The air is rich with the smells of morning "
	+ "cooking and " + one_of_list(({"tea", "coffee"})) + " borne on a cool, "
	+ "misty breeze." + road;
	break;

    case TOD_DAY:
	desc += "The worn marble of Muest street and its buildings lights up "
	+ "in the midday sun as people and maroon robed aesthetics travel "
	+ "throughout the Aesthetics quarter filling the street with the "
	+ "murmurings of their daily business." + road;
	break;

    case TOD_TWILIGHT:
	desc += "The worn marble of Muest street catches the "
	+ "last rays of the sun appearing to glow of its own accord "
	+ "as travellers and maroon robed aesthetics make their way about the "
	+ "street." + road;
    break;

    case TOD_NIGHT:
	desc += "The moon and stars shed pale light across the translucent marble "
	+ "of Muest street amplifying the yellow glow of the street lamps.  "
	+ "A few people and maroon robed aesthetics still make their way about at "
	+ "this hour." + road;
    break;

    default:
	break;
    }
    return desc;
}

void
create_palan_room()
{
    SHORT("On Muest street in the southeast of the city");
    LONG("@@get_time_desc@@");

	ITEM(({"wall", "city wall", "great wall"}), "The city wall of "
	+ "Palanthas towers high above to the south.\n");
	ITEM(({"shop", "one-story shop", "abandoned shop"}),
        "This one-story shop to the southeast hides in the shadow "
	+ "of the large buildings in between which it is wedged.  There are "
        + "no signs of activity inside, and it looks like it has been "
        + "abandoned for some time. From above "
	+ "its darkened doorway swings a wooden sign from a dark iron rod.\n");
	ITEM("rod", "A dark iron rod bolted above the doorway of a shop to the "
	+ "southeast from which hangs a wooden sign.\n");
	ITEM("sign", "A thin, wooden sign swaying on short chains beneath an "
	+ "iron rod bolted above the doorway of the shadowed building to the "
	+ "southwest, it reads, \"Zeb's Unlooked for Tomes\".\n");
        ITEM(({"door","darkened door","doorway","darkened doorway"}),
        "The doorway is darkened by shadows, however inspecting it more "
        + "closely you notice its lock has been forced, @@door_open");
        ITEM("lock", "It looks like the lock on the door was smashed open "
        + "some time ago.\n"); 

	CMD("sign", "read", "@@read_sign");
	
	EXIT(MONKS + "a23", "east", 0, 0);
	EXIT(MONKS + "rarebooks", "southeast", "@@book_closed", 0);
	EXIT(MONKS + "w14", "south", 0, 0);

    reset_palan_room();
}

string
door_open()
{
    if(door_open)
        return "and the door is ajar allowing easy entry to the southeast.\n";
    else
        return "and the door jammed closed from the other side. You may " +
            "be able to push the door open with enough effort.\n";
}

read_sign()
{
	write("It reads:  \"Zeb's Unlooked for Tomes\".\n");
	return 1;
}

int
book_closed()
{
    if(door_open)
    {
	write("You push past the ajar door and enter the abandoned " +
            "bookstore, \"Zeb's Unlooked for Tomes\".\n");
	return 0;
    }

    write("The door seems to be jammed shut.\n");
    return 1;
}

void
init()
{
    ::init();
    ADA("push");
}

int
push(string str)
{
    string door;

    if(!str)
    {
        notify_fail("Push what?\n");
        return 0;
    }

    if (parse_command(str, environment(TP), "[the] %w [open]", door))
    {
        if(door_open)
        {
            write("The door is already ajar! No need to force it open.\n");
            return 1;
        }

        if(door == "door")
        {
            write("You push hard against the door, forcing it open.\n");
            say(QCTNAME(TP)+ " approaches the darkened doorway to your " +
                "southeast and forces the door to the store open.\n");
            door_open = 1;
            return 1;
        }

        write("Push what? The door open?\n");
        return 1;
    }

    write("What do you want to push?\n");
    return 1;
}