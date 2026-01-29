#include "../local.h"
#include CLOCKH
#include <ss_types.h>

inherit TDIR + "throtyl-v";

public void
create_throtyl_room()
{
    add_prop(ROOM_I_TYPE, ROOM_NORMAL);
    add_prop(ROOM_I_INSIDE, 0);
    add_prop(ROOM_I_LIGHT, 1);

    set_special_short("on the edge of the moorlands at the foot " +
        "of the Northern Dargaard Mountain Range");
    set_short("the edge of the moorlands");
    set_long("The moors spread out before you to your east, " +
        "a poorly drained plain covered in hardy purple heather " +
        "blooms. To your west at the foot of the ranges " +
        "you make out the sculpted entry of a dwarven tomb.\n");

    add_item(({"dwarven tomb","tomb","entry"}),
        "At the foot of the mountain range to your west is " +
        "a dwarven tomb. Great stone blocks carved with " +
        "runes mark the entry, which look like it has recently " +
        "been forced open. You could enter the tomb if you dared!\n");

    add_item(({"stone blocks","blocks"}),
        "Three great stone blocks form a great arch marking the " +
        "entry to a dwarven tomb, that looks like it has been " +
        "carved into the side of a hill at the foot of the " +
        "Dargaard Mountain Range. Dwarven runes have been carved " +
        "on either side of the entry.\n");

    add_item(({"dwarven runes","runes"}),
        "Carved on either side of the entry to the tomb are dwarven " +
        "runes. You may be able to read them.\n");

    add_item(({"northern dargaard mountain range","mountain range",
        "range","mountains","mountain","dargaard mountain range",
        "dargaard","sheer cliffs","cliffs","cliff","crags","crag",
        "steep crags","ranges"}),
        "To your northwest rises the Northern Dargaard Mountain " +
        "Range. Consisting of sheer cliffs and steep crags, " +
        "this range forms an unpassable barrier separating the plains " +
        "of Solamnia to your west from the moors of Throtyl.\n");

    add_item(({"heather", "purple heather","blooms",
        "heath", "heather blooms"}),
        "A hardy heather grows wild across the moors of Throtyl, its " +
        "vibrant purple blooms a stark constrast to the rest of the " +
        "barren lands and dreary weather.\n");

    add_item(({"grey rain clouds", "rain clouds", "clouds", "rain",
        "dark rain clouds" }),
        "Dark rain clouds seem to permanently hang over the lands " +
        "of Throtyl.\n");

    add_item(({"throtyl", "moors", "moorlands", "bogs", "boggy moors", 
        "plain"}),
        "Around you is Throtyl, a land of vast moorlands " +
        "filled with nomadic goblin races. Heath and peat bogs are common " +
        "here, and this poorly drained land is inundated with rain " +
        "throughout the year. Even when at its driest the moors are " +
        "exhausting to navigate, but during the wet season almost " +
        "impossible.\n");

    add_std_exits();

    add_cmd_item(({"dwarven tomb","tomb"}),
        "enter","@@enter_tomb");
    add_cmd_item(({"runes","dwarven runes"}), "read", "@@read_runes");

    herbs = HERB_MASTER->query_herbs( ({ "wetlands", }) );
}


/* Function name: query_map_fatigue
 * Description:	  Return fatigue value for leaving this room for this_player()
 *		  Redefine it in ROOM base file.
 * Returns:	  int fatigue value
 */
public int
query_map_fatigue()
{
    if(GET_SEASON == SPRING)
        return 8;
    else
        return 4;
}

string
read_runes()
{
    if(TP->query_race_name() == "dwarf" || 
       TP->query_skill(SS_LANGUAGE) > 40)
        return "You decipher the dwarven runes to read: Be warned! " +
            "Here lies the Mad Thane Ruul Curseforge. He rests " +
            "uneasily! Disturb at your own peril!\n";

    return "You do not have the skill in languages to decipher " +
        "the dwarven runes.\n";
}

string
enter_tomb()
{

    write("You enter the dwarven tomb.\n");
    TP->move_living("into the dwarven tomb",
        "/d/Krynn/throtyl/rooms/dragon_lair", 1, 0);
    return "";
}