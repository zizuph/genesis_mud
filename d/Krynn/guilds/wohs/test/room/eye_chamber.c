/*
   Test of High Sorcery room
*/

#include "/d/Krynn/common/defs.h"
#include "/d/Krynn/wayreth/local.h"
#include "/d/Krynn/guilds/wohs/defs.h"
#include <ss_types.h>
#include <language.h>
#include <macros.h>

inherit WOHS_TEST_BASE;

#define SCRY_PROP       "_wohs_test_successful_scry"
#define OBSERVE_PROP    "_wohs_test_successful_observe"
#define AWARE_OF_PLAN   "_wohs_test_iriale_aware_of_plan"
#define HEARTROOM_ACTIVATED  "_wohs_test_heartroom_activated"

void
reset_tower_room()
{
    return;
}

void
create_tower_room()
{
   set_short("the Chamber of Eyes within the crimson tower of High " +
       "Sorcery.\nA crystal ball");
   set_long("You stand in the Chamber of Eyes on the upper level of the " +
       "crimson tower of High Sorcery, where wizards come to view the " +
       "realm with their crystal balls and even - for the most powerful " +
       "of diviners - seek to gaze into the past or even the future.\n" +
       "A crystal ball.\n");

   add_item(({"crystal ball","tripod of engraved silver","tripod",
       "engravings","ball"}), "Standing on a tripod of engraved silver " +
       "is a large crystal ball, misty with a swirling white fog. Those " +
       "trained in the arts of the Diviner will be able to 'scry' or " +
       "'divine' individuals and watch them surreptitiously.\n");
   add_item(({"white fog","fog","swirling white fog","swirling fog"}),
       "A white fog swirls lazily within the large crystal ball in the " +
       "middle of the room.\n");
   add_item(({"chamber","chamber of eyes"}), "You stand in the Chamber " +
       "of Eyes on the upper level of the crimson tower of High " +
       "Sorcery, where wizards come to view the realm with their " +
       "crystal balls and even - for the most powerful of diviners - " +
       "seek to gaze into the past or even the future.\n");

   set_tell_time(15);
   add_tell("The crystal ball rocks precariously as the walls of the " +
       "tower vibrate furiously!\n");
   add_tell("The tower rocks violently, as if it had been struck by a " +
       "wave of force!\n");
   add_tell("The stones of the tower begin to crack as spiderwebs of " +
       "energy spread across them.\n");
   add_tell("The tower begins to shake and rumble ominously!\n");
   add_tell("The walls of the tower groan, as if they were being " +
       "constricted by a powerful coil of force.\n");

   add_exit(WOHS_TEST + "room/daltigoth_tower6", "west", 0);

   reset_tower_room();
}

public void
init()
{
    ::init(); 
    add_action("scry_target", "scry"); 
    add_action("scry_target", "divine");
}

void
scry_message(object player)
{
    if(player->query_prop(SCRY_PROP) || player->query_prop(OBSERVE_PROP))
    {
        set_alarm(1.5,0.0, &write("You can find out nothing further " +
            "about Duke Serl Kar-Thon. The disruptive magic of the " +
            "black pine must be effecting any further divination " +
            "attempts.\n"));
        return;
    }

    set_alarm(1.5,0.0, &write("The white fog begins to swirl rapidly " +
        "within the crystal ball.\n\n"));
    set_alarm(2.5,0.0, &write("The white fog parts, and you find " +
        "yourself staring down from a great height upon a grand " +
        "city.\n\n"));
    set_alarm(7.5,0.0, &write("Your magical observation descends " +
        "towards the city to a grove of tall pine trees broken only " +
        "by a squat crimson tower - the tower of High Sorcery of " +
        "Daltigoth.\n\n"));
    set_alarm(15.5,0.0, &write("You notice the grove is completely " +
        "surrounded by soldiers in Imperial regalia. Your divination " +
        "suddenly moves to the entry of the grove, where it stops at a " +
        "tall warrior built like an ox, his open helm revealing " +
        "a hoary beard.\n\n"));
    set_alarm(21.5,0.0, &write("The tall hoary-bearded human bends " +
        "over and tends to the ground with his dirk.\n\n"));
    set_alarm(26.5,0.0, &write("The ground begins to bubble and rise, " +
        "like a boil or blister, then explodes - showering dirt " +
        "everywhere.\n\n"));
    set_alarm(30.5,0.0, &write("The tall hoary-bearded human curses and " +
        "wipes dirt from his face, as a tree begins to rise from the " +
        "spot... a tree of black needles, black bark and sticky black " +
        "sap oozing down its trunk.\n\n"));
    set_alarm(40.5,0.0, &write("The tall hoary-bearded human swears " +
        "reverently: 'Blood of a thousand wyrms!'\n\n"));
    set_alarm(45.5,0.0, &write("The pine trees of the grove closest to " +
        "the black pine suddenly groan, and begin twisting away from " +
        "it... even uprooting themselves in their eagerness to shy " +
        "away.\n\n"));
    set_alarm(50.5,0.0, &write("The tall hoary-bearded human whoops!\n\n"));
    set_alarm(53.5,0.0, &write("The tall hoary-bearded human shouts: " +
        "Men! Ready yourself! A path opens to the Tower!\n\n"));
    set_alarm(56.5,0.0, &write("Ergothian cavaliers and presbyters " +
        "cheer valiantly, and ready themselves to enter the grove!\n\n"));
    set_alarm(60.5,0.0, &write("The white fog within the crystal ball " +
        "suddenly fills your vision, and begins lazily swirling again. " +
        "Your divination has ended.\n\nYou should report back to Iriale " +
        "what you have observed.\n"));
    set_alarm(60.5,0.0, &player->add_prop(SCRY_PROP, 1));
    set_alarm(60.5,0.0, &WOHS_MANAGER->add_wohs_test_props(player, 
        SCRY_PROP, 1));
}

public int
scry_target(string str)
{
    if (!strlen(str))
    {
        return 0;
    }

    if(!WOHS_MANAGER->query_memorised_spell(TP,"ehtahxiekiv_memorised") &&
       !TP->query_wiz_level())
    {
        notify_fail("You will need to have the 'divine location' " +
            "spell - ehtahxiekiv - memorised to be able to use the " +
            "crystal ball.\n");
        return 0;
    }

    if(!TP->query_prop(AWARE_OF_PLAN))
    {
        notify_fail("You stare into the crystal ball, however the " +
            "white fog swirls lazily and shows you nothing.\n");
        return 0;
    }

    str = lower_case(str);

    if((str != "duke serl kar-thon") && (str != "serl kar-thon") && 
       (str != "serl") && (str != "duke") && (str != "duke serl"))
    {
        notify_fail("You stare into the crystal ball, however the " +
            "white fog swirls lazily and shows you nothing.\n");
        return 0;
    }

    write("You stare into the crystal ball and seek out Duke Serl " +
        "Kar-Thon...\n");
    set_alarm(1.5,0.0, &scry_message(TP));

    return 1;
}

void
enter_inv(object ob, object from)
{
    ::enter_inv(ob, from);
 
    if (interactive(ob) && TP->query_prop(HEARTROOM_ACTIVATED))
       start_room_tells();
}