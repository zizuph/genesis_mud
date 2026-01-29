#include "/d/Ansalon/common/defs.h"
#include "/d/Ansalon/taman_busuk/sanction/local.h"
#include <macros.h>
#include <stdproperties.h>
#include <ss_types.h>
#include "/d/Krynn/guilds/OotS/defs.h"
#include DL_CLOCK

inherit SANCINROOM;

#define GOD_PATRON(x) (OOTS_MANAGER->query_oots_god(x))

object pool;

void
reset_sanction_room()
{
    if(!objectp(pool))
    {
        pool = clone_object(SOBJ + "solinari_pool");
        pool->move(TO, 1);
    }
}

string
warrior_string()
{
    string str;

    if(TP->query_skill(SS_LANGUAGE) > 40)
        if(IS_OOTS(TP) && (GOD_PATRON(TP) == "Paladine"))
            str = "Along the plinth are words carved in an archaic " +
                "language, which you translate to 'Skyblade'. This " +
                "statue is clearly of your divine patron, Paladine.";
        else
            str = "Along the plinth are words carved in an archaic " +
                "language, which you translate to 'Skyblade'.";
    else
        if(IS_OOTS(TP) && (GOD_PATRON(TP) == "Paladine"))
            str = "Along the plinth are words carved in an archaic " +
                "language you are unable to translate. Your skill " +
                "in ancient languages is too poor. However it is " +
                "clear this is a statue of your divine patron, Paladine.";
        else
            str = "Along the plinth are words carved in an archaic " +
                "language you are unable to translate. Your skill " +
                "in ancient languages is too poor."; 

    str += "\n";

    return str;
}

string
maiden_string()
{
    string str;

    if(TP->query_skill(SS_LANGUAGE) > 40)
        if(IS_OOTS(TP) && (GOD_PATRON(TP) == "Mishakal"))
            str = "Along the plinth are words carved in an archaic " +
                "language, which you translate to 'Skymistress'. This " +
                "statue is clearly of your divine patron, Mishakal.";
        else
            str = "Along the plinth are words carved in an archaic " +
                "language, which you translate to 'Skymistress'.";
    else
        if(IS_OOTS(TP) && (GOD_PATRON(TP) == "Mishakal"))
            str = "Along the plinth are words carved in an archaic " +
                "language you are unable to translate. Your skill " +
                "in ancient languages is too poor. However it is " +
                "clear this is a statue of your divine patron, Mishakal.";
        else
            str = "Along the plinth are words carved in an archaic " +
                "language you are unable to translate. Your skill " +
                "in ancient languages is too poor."; 

    str += "\n";

    return str;
}

string
bard_string()
{
    string str;

    if(TP->query_skill(SS_LANGUAGE) > 40)
        if(IS_OOTS(TP) && (GOD_PATRON(TP) == "Branchala"))
            str = "Along the plinth are words carved in an archaic " +
                "language, which you translate to 'Kensin the Sly'. This " +
                "statue is clearly of your divine patron, Branchala.";
        else
            str = "Along the plinth are words carved in an archaic " +
                "language, which you translate to 'Kensin the Sly'.";
    else
        if(IS_OOTS(TP) && (GOD_PATRON(TP) == "Branchala"))
            str = "Along the plinth are words carved in an archaic " +
                "language you are unable to translate. Your skill " +
                "in ancient languages is too poor. However it is " +
                "clear this is a statue of your divine patron, Branchala.";
        else
            str = "Along the plinth are words carved in an archaic " +
                "language you are unable to translate. Your skill " +
                "in ancient languages is too poor."; 

    str += "\n";

    return str;
}

string
minotaur_string()
{
    string str;

    if(TP->query_skill(SS_LANGUAGE) > 40)
        if(IS_OOTS(TP) && (GOD_PATRON(TP) == "Kiri-Jolith"))
            str = "Along the plinth are words carved in an archaic " +
                "language, which you translate to 'Corij'. This " +
                "statue is clearly of your divine patron, Kiri-Jolith.";
        else
            str = "Along the plinth are words carved in an archaic " +
                "language, which you translate to 'Corij'.";
    else
        if(IS_OOTS(TP) && (GOD_PATRON(TP) == "Kiri-Jolith"))
            str = "Along the plinth are words carved in an archaic " +
                "language you are unable to translate. Your skill " +
                "in ancient languages is too poor. However it is " +
                "clear this is a statue of your divine patron, Kiri-Jolith.";
        else
            str = "Along the plinth are words carved in an archaic " +
                "language you are unable to translate. Your skill " +
                "in ancient languages is too poor."; 

    str += "\n";

    return str;
}

string
scholar_string()
{
    string str;

    if(TP->query_skill(SS_LANGUAGE) > 40)
        if(IS_OOTS(TP) && (GOD_PATRON(TP) == "Majere"))
            str = "Along the plinth are words carved in an archaic " +
                "language, which you translate to 'Manthus'. This " +
                "statue is clearly of your divine patron, Majere.";
        else
            str = "Along the plinth are words carved in an archaic " +
                "language, which you translate to 'Manthus'.";
    else
        if(IS_OOTS(TP) && (GOD_PATRON(TP) == "Majere"))
            str = "Along the plinth are words carved in an archaic " +
                "language you are unable to translate. Your skill " +
                "in ancient languages is too poor. However it is " +
                "clear this is a statue of your divine patron, Majere.";
        else
            str = "Along the plinth are words carved in an archaic " +
                "language you are unable to translate. Your skill " +
                "in ancient languages is too poor."; 

    str += "\n";

    return str;
}

string
sorcerer_string()
{
    string str;

    if(TP->query_skill(SS_LANGUAGE) > 40)
        if(IS_OOTS(TP) && (GOD_PATRON(TP) == "Solinari"))
            str = "Along the plinth are words carved in an archaic " +
                "language, which you translate to 'God's Eye'. This " +
                "statue is clearly of your divine patron, Solinari.";
        else
            str = "Along the plinth are words carved in an archaic " +
                "language, which you translate to 'God's Eye'.";
    else
        if(IS_OOTS(TP) && (GOD_PATRON(TP) == "Solinari"))
            str = "Along the plinth are words carved in an archaic " +
                "language you are unable to translate. Your skill " +
                "in ancient languages is too poor. However it is " +
                "clear this is a statue of your divine patron, Solinari.";
        else
            str = "Along the plinth are words carved in an archaic " +
                "language you are unable to translate. Your skill " +
                "in ancient languages is too poor."; 

    str += "\n";

    return str;
}

string
hunter_string()
{
    string str;

    if(TP->query_skill(SS_LANGUAGE) > 40)
        if(IS_OOTS(TP) && (GOD_PATRON(TP) == "Habbakuk"))
            str = "Along the plinth are words carved in an archaic " +
                "language, which you translate to 'Fisher King'. This " +
                "statue is clearly of your divine patron, Habbakuk.";
        else
            str = "Along the plinth are words carved in an archaic " +
                "language, which you translate to 'Fisher King'.";
    else
        if(IS_OOTS(TP) && (GOD_PATRON(TP) == "Habbakuk"))
            str = "Along the plinth are words carved in an archaic " +
                "language you are unable to translate. Your skill " +
                "in ancient languages is too poor. However it is " +
                "clear this is a statue of your divine patron, Habbakuk.";
        else
            str = "Along the plinth are words carved in an archaic " +
                "language you are unable to translate. Your skill " +
                "in ancient languages is too poor."; 

    str += "\n";

    return str;
}

string
pool_desc()
{
    string str, desc;

    str = "";

    switch (GET_TIMEOFDAY)
    {
	case TOD_NIGHT:
	      str += "Through a high window in the north wall, the light " +
                  "from the moon " + C(SOLINARI) + " makes the water " +
                  "of the pool blaze silver and reflect the surroundings " +
                  "like a mirror!\n";
	      break;
        default:
	      str += "The water of the pool is dark, reflecting little.\n";
	      break;
    }

    return str;
}

void
create_sanction_room()
{
    set_short("within a dark abandoned temple");
    set_long("You stand within the unlit central altar room of an " +
        "abandoned temple. The room is bare, having seemingly not " +
        "been inhabited for centuries, however surprisingly untouched " +
        "by vandalism or damage. Standing in the middle of the room are " +
        "two dusty statues - one of a warrior and the other a maiden. " +
        "Around the walls of the room stand five other statues.\n");

    add_item(({"statue"}),"Which statue? There are seven.\n");
    add_item(({"plinth"}),"There is a plinth at the base of all seven " +
        "statues.\n");
    add_item(({"southern wall", "south wall"}),
        "Along the southern wall are two statues, one of a scholar and " +
        "the other of a sorcerer.\n");
    add_item(({"northern wall", "north wall"}),
        "Along the northern wall are two statues, one of a minotaur and " +
        "the other of a hunter.\n");
    add_item(({"statues"}),
        "There are two dusty statues standing in the middle of the room, " +
        "one a statue of a warrior, the other a statue of a maiden. " +
        "Around the walls of the temple stand five other statues - " +
        "a statue of a bard, a statue of a minotaur, a statue of a " +
        "scholar, a statue of a sorcerer, and a statue of a hunter.\n");
    add_item(({"other statues","five other statues","walls"}),
        "Around the walls of the temple are five statues - " +
        "a statue of a bard, a statue of a minotaur, a statue of a " +
        "scholar, a statue of a sorcerer, and a statue of a hunter.\n");
    add_item(({"two dusty statues","dusty statues"}),
        "In the middle of the room are two dusty statues. One a " +
        "statue of a warrior, the other a statue of a maiden.\n");
    add_item(({"warrior statue","statue of a warrior","warrior",
        "first statue","runed greatsword","greatsword"}),
        "In the middle of the temple stands a warrior in full armour, " +
        "leaning on a runed greatsword. @@warrior_string");
    add_item(({"maiden statue","statue of a maiden","maiden",
        "second statue","hooded maiden"}),
        "In the middle of the temple is the statue of a hooded " +
        "maiden, her face obscured. She is kneeling before the " +
        "statue of the warrior. @@maiden_string");
    add_item(({"bard statue","statue of a bard","bard",
        "royal harp", "harp",
        "third statue", "elven bard","statue of an elven bard"}),
        "Along the wall furthest from the other statues is a " +
        "statue of an elven bard, a royal harp in hand. He is " +
        "glancing sardonically in the direction of the statue " +
        "of a minotaur. @@bard_string");
    add_item(({"minotaur statue","statue of a minotaur","minotaur",
        "fourth statue"}),
        "Along the northern wall is a statue of a half-man half-bison " +
        "roaring silently towards the ceiling of the temple. " +
        "@@minotaur_string");
    add_item(({"scholar statue","statue of a scholar","scholar",
        "fifth statue"}),
        "Along the southern wall is a statue of an ancient scholar " +
        "staring contemplatively at a rose in his hand. " +
        "@@scholar_string");
    add_item(({"sorcerer statue","statue of a sorcerer","sorcerer",
        "sixth statue"}),
        "Along the southern wall is a statue of a sorcerer, " +
        "its plinth standing in a shallow reflection " +
        "pool. " +
        "@@sorcerer_string");
    add_item(({"hunter statue","statue of a hunter","hunter",
        "seventh statue","unstrung bow","bow"}),
        "Along the northern wall is a statue of a nomadic " +
        "hunter, with an unstrung bow in hand. " +
        "@@hunter_string");
    add_item(({"reflection pool","pool","shallow reflection pool",
        "half-moon reflection pool","water"}),
        "Surrounding the base of the statue of the sorcerer is " +
        "a shallow half-moon reflection pool. @@pool_desc");

    add_item(({"window","windows","high window"}),
        "Across the walls of the temple are high narrows windows.\n");

    add_cmd_item(({"statue","statues"}),"dust",
        "You futilely try and clean the statues of dust, but the " +
        "layers of centuries defeat you.\n");
    add_cmd_item(({"water","from pool"}),"drink",
        "You take a sip of the water from the pool. It tastes stale.\n"); 

    add_exit(SCITY + "street25","east", "@@exit_temple");

    reset_sanction_room();

}

int
exit_temple()
{
   write("You make your way out of the abandoned temple.\n");
   return 0;
}
