/*
   Test of High Sorcery room
*/

#include "/d/Krynn/common/defs.h"
#include "/d/Krynn/wayreth/local.h"
#include "/d/Krynn/guilds/wohs/defs.h"
#include <ss_types.h>
#include <language.h>
#include <macros.h>

inherit WOHS_TEST_OUT;

#define THIRD_TASK            "_wohs_test_given_third_task"
#define BATTLE_PROP           "_wohs_test_protected_tower"
#define FLEE_WARNING          "_wohs_test_flee_warning"

#define INVADING_SOLDIER      "_wohs_test_invading_soldier"

#define WOHS_NPC              "/d/Krynn/guilds/wohs/test/living/"
#define WOHS_TELL_ROOM(y, x)  tell_room(TO, x, 0, y)
#define KILL_TARGET(x, y)     (x)->command("kill " + (y)->query_real_name())

object g1, g2, g3, g4, g5, g6, presbyter, scout, cavalier, cavalier2;

void
create_tower_room()
{
    set_short("within the barbican of the crimson tower");
    set_long("You stand within the barbican passing through the thick " +
        "crimson walls of the Rathfast - the Tower of High Sorcery in " +
        "the city of Daltigoth. The barbican is gateless and open to " +
        "the sky, with rows of lifeless gargoyles staring down at you " +
        "from up high on top of the walls. To your east the barbican " +
        "opens to a grove of tall pine trees, while to your west " +
        "the grounds of the tower open up before you.\n");

    add_item(({"grove","grove of tall pine trees","peaceful grove",
        "forest","kadothan grove"}), "Through the barbican to your east " +
        "is a grove of tall pine trees - the magical Kadothan Grove. " +
        "The pine trees sway serenely to a gentle highland breeze, " +
        "almost hypnotically.\n");

    add_item(({"pine trees","trees","tree","pine tree","trunks"}),
        "Tall pine trees rise from the grove to your east, swaying " +
        "serenely to a gentle highland breeze, almost hypnotically. " +
        "You feel a sense of sleepiness pass over you as you watch " +
        "the trees move.\n");

    add_item(({"tower","crimson tower","squat tower","short tower",
        "rathfast","crimson keep","keep","tower of high sorcery"}),
        "Built atop a tall hill within a grove of pine trees, this " +
        "tower is both shorter and broader than towers you are familiar " +
        "with. Its design is based on an early Ergothic style you have " +
        "only ever read about, although the deep, brilliant red colour " +
        "of its walls is unique to one building only - Rathfast, the " +
        "Crimson Keep, the Tower of High Sorcery in the city of " +
        "Daltigoth that was destroyed during the Lost Battles over 360 " +
        "years ago!\n");

    add_item(({"walls","crimson walls","wall","stout wall","whorls",
        "silver lightning","lightning","stormclouds","inky black","black",
        "red stone","stone"}), "Surrounding the tower is a stout wall " +
        "of red stone, mottled and marked here and there with whorls " +
        "of inky black, forever twisting and turning like stormclouds " +
        "that occasionally flare with silver lightning. Atop the wall " +
        "are crenelated battlements and gargoyles, at odds with the " +
        "welcoming gateless opening you currently stand within allowing " +
        "easy entry to the tower grounds.\n");

    add_item(({"battlements","gargoyles","gargoyle","crenelated " +
        "battlements"}), "Gargoyles stare down upon the entry of the " +
        "tower from the battlements of the wall, frozen guardians of " +
        "the tower.\n");

    add_item(({"gate","passage","gateless passage","barbican","opening",
        "gateless opening"}), "You stand within a gateless passage " +
        "through the tower's barbican, leading to a wide lawn of " +
        "emerald grass within the tower proper to your west and into a " +
        "grove of pine trees to your east.\n");

    add_item(({"grass","emerald grass","tower proper","proper","lawn",
        "wide lawn"}), "To your west you can see a wide lawn of emerald " +
        "grass within the tower proper, and the tower rising beyond it.\n");

    add_item(({"city","great city","daltigoth"}), "The tower stands upon " +
        "a high hill within a grove of pines overlooking a city clearly " +
        "of Ergothic design. To your east you can make out a great " +
        "imperial palace, its tall minarets rising high above the " +
        "height of the crimson tower.\n");

    add_item(({"imperial palace","palace","minaret","minarets"}),
        "To your east rises a great imperial palace, the seat of power " +
        "of the emperor of Ergoth.\n");

    OUTSIDE;

    add_exit(WOHS_TEST + "room/daltigoth_tower2", "west", 
        "@@enter_daltigoth_tower");
    add_exit(WOHS_TEST + "room/kadothan_grove2", "east", 
        "@@leave_daltigoth_tower");

}

int
enter_daltigoth_tower()
{
    if(TP->query_prop(THIRD_TASK) && !(TP->query_prop(BATTLE_PROP)))
    {
	if(TP->query_prop(FLEE_WARNING))
	{
	    write("You flee from your post, leaving the gates to the " +
                "Tower unguarded!\n");
	    return 0;
	}

	write("\n\nIf you leave west now, you leave the gates to the " +
            "Tower unguarded! Certain doom for Iriale and yourself!\n\n\n");
	TP->add_prop(FLEE_WARNING, 1);
	return 1;
    }

    if(TP->query_prop(THIRD_TASK) && TP->query_prop(BATTLE_PROP) && 
       TP->query_prop(FLEE_WARNING))
    {
	TP->remove_prop(FLEE_WARNING);
    }

    return 0;
}

int
leave_daltigoth_tower()
{
    if(TP->query_prop(THIRD_TASK) && !(TP->query_prop(BATTLE_PROP)))
    {
	if(TP->query_prop(FLEE_WARNING))
	{
	    write("You try and flee from your post, however legions of " +
                "Ergothian forces block the path to your east! There is " +
                "no escape that way!\n");
	    return 1;
	}

	write("\n\nIf you leave east now, you leave the gates to the " +
            "Tower unguarded!\n\n\n");
	TP->add_prop(FLEE_WARNING, 1);
	return 1;
    }

    return 0;
}

void
final_wave(object player)
{
    setuid();
    seteuid(getuid());

    int stat = player->query_average_stat();       

    return;
}

void
gargoyle_wave(object player)
{
    setuid();
    seteuid(getuid());

    int stat = player->query_average_stat();       

    WOHS_TELL_ROOM(player, "\n\nThe gargoyles lining the walls " +
        "awaken!\n\nWith a gravelly groan, stony wings extend and the " +
        "magical guardians glide down into the barbican before you.\n\n");

    if(present(player, TO))
    {
	player->add_prop(BATTLE_PROP, 1);
	WOHS_MANAGER->add_wohs_test_props(player, BATTLE_PROP, 1);
    }

    g1 = clone_object(WOHS_NPC + "wohs_test_gargoyle");
    g1->set_stats(({stat, stat, stat, stat, stat, stat}));
    g1->move(TO);
    g2 = clone_object(WOHS_NPC + "wohs_test_gargoyle");
    g2->set_stats(({stat, stat, stat, stat, stat, stat}));
    g2->move(TO);
    g3 = clone_object(WOHS_NPC + "wohs_test_gargoyle");
    g3->set_stats(({stat, stat, stat, stat, stat, stat}));
    g3->move(TO);
    g4 = clone_object(WOHS_NPC + "wohs_test_gargoyle");
    g4->set_stats(({stat, stat, stat, stat, stat, stat}));
    g4->move(TO);
    g5 = clone_object(WOHS_NPC + "wohs_test_gargoyle");
    g5->set_stats(({stat, stat, stat, stat, stat, stat}));
    g5->move(TO);
    g6 = clone_object(WOHS_NPC + "wohs_test_gargoyle");
    g6->set_stats(({stat, stat, stat, stat, stat, stat}));
    g6->move(TO);

    g1->command("emote folds its stony wings back and crouches " +
        "defensively facing east.");
    g2->command("emote raises its claws threateningly.");
    g3->command("emote roars silently!");
    g4->command("emote roars silently!");
    g5->command("emote stares at you with fiery red eyes.");
    g6->command("emote stretches its wings threateningly, looking " +
        "eagerly for invaders.");

    if(objectp(presbyter))
    {
	KILL_TARGET(g1, presbyter);
	KILL_TARGET(g2, presbyter);
	KILL_TARGET(g3, presbyter);
	KILL_TARGET(g4, presbyter);
	KILL_TARGET(g5, presbyter);
	KILL_TARGET(g6, presbyter);
    }
    if(objectp(scout))
    {
	KILL_TARGET(g1, scout);
	KILL_TARGET(g2, scout);
	KILL_TARGET(g3, scout);
	KILL_TARGET(g4, scout);
	KILL_TARGET(g5, scout);
	KILL_TARGET(g6, scout);
    }
    if(objectp(cavalier))
    {
	KILL_TARGET(g1, cavalier);
	KILL_TARGET(g2, cavalier);
	KILL_TARGET(g3, cavalier);
	KILL_TARGET(g4, cavalier);
	KILL_TARGET(g5, cavalier);
	KILL_TARGET(g6, cavalier);
    }
    if(objectp(cavalier2))
    {
	KILL_TARGET(g1, cavalier2);
	KILL_TARGET(g2, cavalier2);
	KILL_TARGET(g3, cavalier2);
	KILL_TARGET(g4, cavalier2);
	KILL_TARGET(g5, cavalier2);
	KILL_TARGET(g6, cavalier2);
    }

    set_alarm(5.0,0.0, &WOHS_TELL_ROOM(player, "\n\nYou have protected " +
        "the entry to the Tower while the gargoyles were being " +
        "awakened. You should return swiftly to Iriale before the " +
        "legion of Ergothians arrive!\n\n"));

    // set_alarm(20.0,0.0, &final_wave(player));

    return;
}


third_wave(object player)
{
    setuid();
    seteuid(getuid());

    int stat = player->query_average_stat();       

    presbyter = clone_object(WOHS_NPC + "presbyter");
    presbyter->arm_me();
    presbyter->set_stats(({stat, stat, stat, stat, stat, stat}));
    presbyter->move(TO);
    presbyter->heal_hp(10000);
    presbyter->add_prop(INVADING_SOLDIER, 1);

    if(!CAN_SEE_IN_ROOM(presbyter))
    {
	object torch;
	torch = clone_object("/d/Krynn/guilds/wohs/test/obj/wohs_test_torch");
	torch->move(presbyter, 1);
	torch->set_strength(30);
	presbyter->command("light all");
    }

    presbyter->command("shout In the name of the Kingpriest of Istar! " +
        "Begone vile foe!");
    presbyter->command("kill " +player->query_real_name());

    set_alarm(100.0,0.0, &WOHS_TELL_ROOM(player, "\n\nYou notice a " +
        "massive force of six Ergothian cavaliers, four scouts, and " +
        "two presbyters approaching from the east in force! Prepare " +
        "yourself!\n\n"));

    set_alarm(120.0,0.0, &gargoyle_wave(player));

    return;
}

void
second_wave(object player)
{
    setuid();
    seteuid(getuid());

    int stat = player->query_average_stat();       

    cavalier = clone_object(WOHS_NPC + "cavalier");
    cavalier->arm_me();
    cavalier->set_stats(({stat, stat, stat, stat, stat, stat}));
    cavalier->move(TO);
    cavalier->heal_hp(10000);
    cavalier->add_prop(INVADING_SOLDIER, 1);

    cavalier2 = clone_object(WOHS_NPC + "cavalier");
    cavalier2->arm_me();
    cavalier2->set_stats(({stat, stat, stat, stat, stat, stat}));
    cavalier2->move(TO);
    cavalier2->heal_hp(10000);
    cavalier2->add_prop(INVADING_SOLDIER, 1);

    if(!CAN_SEE_IN_ROOM(cavalier))
    {
	object torch;
	torch = clone_object("/d/Krynn/guilds/wohs/test/obj/wohs_test_torch");
	torch->move(cavalier, 1);
	torch->set_strength(30);
	cavalier->command("light all");
    }

    cavalier->command("shout Death to you foul wizards!");
    cavalier2->command("shout For Duke Serl and the Emperor!");
    cavalier->command("kill " +player->query_real_name());
    cavalier2->command("kill " +player->query_real_name());

    set_alarm(100.0,0.0, &WOHS_TELL_ROOM(player, "\n\nYou notice an " +
        "Istarian presbyter approaching!\n\n"));
    set_alarm(120.0,0.0, &third_wave(player));

    return;
}

void
first_wave(object player)
{
    setuid();
    seteuid(getuid());

    int stat = player->query_average_stat();       

    scout = clone_object(WOHS_NPC + "scout");
    scout->arm_me();
    scout->set_stats(({stat, stat, stat, stat, stat, stat}));
    scout->move(TO);
    scout->heal_hp(10000);
    scout->add_prop(INVADING_SOLDIER, 1);

    if(!CAN_SEE_IN_ROOM(scout))
    {
	scout->command("shout Magical darkness!");
	object torch;
	torch = clone_object("/d/Krynn/guilds/wohs/test/obj/wohs_test_torch");
	torch->move(scout, 1);
	torch->set_strength(30);
	scout->command("light all");
    }

    scout->command("shout For Emperor Gwynned and the Ergothian Empire!");
    scout->command("kill " +player->query_real_name());

    set_alarm(100.0, 0.0, &WOHS_TELL_ROOM(player, "\n\nYou notice two " +
        "Ergothian cavaliers approaching from the east! Prepare " +
        "yourself!\n\n"));
    set_alarm(120.0,0.0, &second_wave(player));
    return;
}

void
enter_inv(object ob, object from)
{
    ::enter_inv(ob, from);

    if(interactive(ob))
    {
	if(ob->query_prop(THIRD_TASK) && !ob->query_prop(FLEE_WARNING))
	{
	    set_alarm(3.0,0.0, &WOHS_TELL_ROOM(ob, "\n\nYou position " +
                "yourself in the middle of the path leading through " +
                "the barbican, preparing yourself to defend the Tower " +
                "against the Ergothian forces approaching you through " +
                "the grove.\n\n\nAbove you, the stone guardian " +
                "gargoyles slowly begin to stir as they are awakened " +
                "from magical slumber... too slowly to be awake before " +
                "the first wave of soldiers arrives from the east! You " +
                "will need to hold the forces back until then!\n\n\n"));

	    set_alarm(10.0,0.0, &WOHS_TELL_ROOM(ob, "You notice an " +
                "Ergothian scout approaching from the east! Prepare " +
                "yourself!\n\n"));
	    set_alarm(20.0,0.0, &first_wave(ob));
	}   
    }

}
