/*
 * Eastern gate in Moria
 * /d/Shire/moria/eastgate/gate.c
 *
 * Varian - May, 2020
 */

#pragma strict_types

#include "../defs.h"
#include <stdproperties.h>
#include <macros.h>

inherit EG_STD + "base";

int do_study(string str);

#define RUNE_MSG \
    "'Welcome to the First Hall in the mansion of Khazad-dum'"
#define PLAYER_STUDIED_THIS_ROOM 0x00000001

/*
 * Function name:        create_eg_room
 * Description  :        Creates a room in Moria
 */
nomask void 
create_eg_room() 
{    
    set_items_chamber();
    set_items_firsthall();
    set_items_window();

    set_short("@@short@@");
    set_long("@@desc@@"); 

    add_item( ({"rune", "runes", "faint rune", "faint runes",
            "silvery rune", "silvery runes", "faint silvery rune",
            "faint silvery runes"}),
        "These runes are hard to make out as not only were they " +
        "badly damaged at some point, they are also covered in dust " +
        "and grime. However, you believe that if you were to take " +
        "some time and study the runes, you could make out what they " +
        "say.\n");
    add_item( ({"gate", "gates", "eastern gate", "eastern gates",
            "great gates", "dimrill gate", "broken gate",
            "broken gates", "opening", "eastern opening"}),
        "The gates here lead out of these dusty halls and into " +
        "a green mountain valley. The doors themselves lay upon " +
        "the ground, smashed and broken long ago. Two great columns " +
        "of polished black basalt still stand, reaching out to each " +
        "other at the top to form an arch. Great door-posts of once " +
        "proud and mighty gates. Above the arch, you notice some " +
        "faint silvery runes etched into the stone.\n");
    add_item( ({"dale", "dimrill dale", "valley", "mountain valley",
            "vale", "mountain vale", "green mountain valley",
            "green mountain vale", "green valley", "green vale"}),
        "A winding road of broken stone stairs leads away from " +
        "the broken gates before you, tumbling down into a deep " +
        "mountain valley filled with tall, slender birch trees and " +
        "wide, green fir-trees.\n");
    add_item( ({"door-post", "door-posts", "post", "posts", "column",
            "columns", "black column", "black columns", "stone columns",
            "stone column", "black stone column", "black stone columns",
            "arch", "black arch", "black stone arch", "stone arch"}),
        "These columns here clearly served as door-posts to the once " +
        "mighty gates, whose stone doors lay broken and smashed upon " +
        "the floor. The columns rise up, curving into an arch where " +
        "you can see silvery runes, faint and dusty, etched into the " +
        "stone.\n");
    add_item( ({"door", "doors", "broken door", "broken doors", "slab",
            "stone door", "stone doors", "smashed door", "broken slab",
            "smashed doors", "slabs", "broken slabs"}),
        "Large slabs of dark grey stone lay smashed and broken upon " +
        "the floor nearby. Still polished black in patches, these " +
        "slabs were clearly once the doors of the proud and mighty " +
        "gates which would have once protected these mountain halls " +
        "and granted entry from the green vale visible to the east.\n");
    add_item( ({" ", " "}),
        " \n");
    add_item( ({" ", " "}),
        " \n");
    add_item( ({" ", " "}),
        " \n");
    add_item( ({" ", " "}),
        " \n");

    set_no_exit_msg( ({"northeast", "southeast"}),
        "The walls appear to be solid in that direction, you " +
        "will need to try a different direction.\n");

    add_exit(EG_ROOM + "first1", "south", 0, 0, 0);
    add_exit(EG_ROOM + "first2", "southwest", 0, 0, 0);
    add_exit(EG_ROOM + "first3", "west", 0, 0, 0);
    add_exit(EG_ROOM + "first4", "northwest", 0, 0, 0);
    add_exit(EG_ROOM + "first5", "north", 0, 0, 0);

    reset_room();
}
/*create_eg_room*/

/*
 * Function name:        desc
 * Description  :        Long description of the room
 */
string
desc()
{
    string long_desc = "You are currently standing in ";

    if (this_player()->query_skill(SS_MORIA_FIRST) > 0 )
        long_desc += "the First Hall of Khazad-dum,";
    else
        long_desc += "an ancient and broken hall,";

    long_desc += " ";

    if (this_player()->query_skill(SS_MORIA_LORE) > 0 )
        long_desc += "ruins of the legendary Dwarven city " +
        "now known as Moria. ";
    else
        long_desc += "once grand but now long forgotten. ";

    long_desc += "Large slabs of stone lay smashed on the floor here " +
        "before a wide open arch in the eastern wall, where wafting " +
        "breaths of cool mountain air drift in from the green valley ";

    if (this_player()->query_skill(SS_MORIA_LORE) > 0 )
        long_desc += "of Dimrill Dale ";
    else
        long_desc += "";

    long_desc += "which lays just beyond. ";

    if (this_player()->query_skill(SS_MORIA_FIRST) > 0 )
        long_desc += "The rest of the First Hall ";
    else
        long_desc += "The hall you are in ";

    long_desc += "sprawls out before you, illuminated by long " +
        "shafts of light which spill in from the windows carved high " +
        "up in the eastern wall. Tall pillars of polished black " +
        "basalt line the hall, with broken remains of statues and " +
        "carved relief left behind from a forgotten age still " +
        "lining the walls. The dry, dusty scent of death seems to " +
        "linger in ";

    if (this_player()->query_skill(SS_MORIA_LORE) > 0 )
        long_desc += "the halls of Moria, ";
    else
        long_desc += "this hall, ";

    long_desc += "a mute warning to all who would enter.";

    return (long_desc + "\n");
}
/*desc*/

/*
 * Function name:        short
 * Description  :        Short description of the room
 */
string
short()
{
    string short_desc = "Inside ";

    if (this_player()->query_skill(SS_MORIA_FIRST) > 0 )
        short_desc += "the First Hall of Moria";
    else
        short_desc += "an ancient hall";

    return (short_desc + "");
}
/*short*/

/*init*/
void
init()
{
    ::init();
    add_action("do_study", "study");
}
/*init*/

/*
 * Function name:        do_study
 * Description  :        When players study this, they get a skill
 *                       bit set in SS_MORIA_FIRST
 */
public int
do_study(string str)

{
    if(!strlen(str))
    {
        notify_fail("Study what? The runes?\n");
        return 0;
    }

    if (!parse_command(str, ({}),
        " [the] [faint] [etched] [stone]" +
        " [silvery] [silver] 'rune' / 'runes'"))
    {
        notify_fail("Study what? The runes?\n");
        return 0;
    }

    int moriaSkill = this_player()->query_base_skill(SS_MORIA_FIRST);
    if (moriaSkill & PLAYER_STUDIED_THIS_ROOM != 0)
    {
        notify_fail("You study the runes again, deciphering the " +
            "inscription which reads: " + RUNE_MSG + ".\n");
        SAYBB(" goes over to study the runes above the arch in the " +
        "eastern wall.\n");
        return 0;
    }

    this_player()->set_skill(SS_MORIA_FIRST, moriaSkill | 
        PLAYER_STUDIED_THIS_ROOM);
    write("You look up to study the silvery runes etched into the " +
        "stone above the arch. They read: " + RUNE_MSG + ". It " +
        "appears you have entered the ancient dwarven halls of " +
        "Khazad-dum, better known now as Moria.\n");
    SAYBB(" goes over to study the runes above the arch in the " +
        "eastern wall.\n");

    return 1;
}
/*do_study*/

/*
 * Function name:        check_rooms_studied
 * Description  :        This will check how many Moria items have
 *                       been studied by the player from different rooms
 */
public int
check_rooms_studied() {
    int roomsStudied = 0;
    int moriaSkill = this_player()->query_base_skill(SS_MORIA_LORE);
    for (int i = 0; i < 128; i++) {
        if (moriaSkill & 1) {
            roomsStudied += 1;
        }
        moriaSkill = moriaSkill >> 1;
    }
    return roomsStudied;
}
/*check_rooms_studied*/