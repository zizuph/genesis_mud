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

#define GRANTED_ACCESS ("_wohs_test_granted_daltigoth_tower_access")
#define DIALOG_PROP     "_iriale_currently_dialoguing"

#define THIRD_TASK     "_wohs_test_given_third_task"
#define BATTLE_PROP    "_wohs_test_protected_tower"
#define FOURTH_TASK    "_wohs_test_given_fourth_task"

#define FLEE_WARNING   "_wohs_test_flee_warning"
#define DMG_TAKEN      "_wohs_test_damage_taken"
#define WOHS_NPC           "/d/Krynn/guilds/wohs/test/living/"
#define WOHS_TELL_ROOM(y, x)    tell_room(TO, x, 0, y)

object wizard;

void
reset_tower_room()
{
    if(!objectp(wizard))
    {
	wizard = clone_object(WOHS_TEST + "living/iriale");
	wizard->arm_me();
	wizard->move(TO,1);
    }
}

void
create_tower_room()
{
    set_short("on a path before the crimson tower of High Sorcery");
    set_long("You stand upon a path before the entry to the Rathfast - " +
        "the Tower of High Sorcery in the city of Daltigoth. Around you " +
        "stretches a wide lawn of emerald green covered with a maze of " +
        "white stone paths, the broadest of which leads west up a " +
        "flight of twenty-one steps to the tower where a double door " +
        "of black oak provides the only access to the tower. To your " +
        "east is a gateless barbican allowing exit through the walls " +
        "of the tower to the grove surrounding the tower.\n");

    add_item(({"steps", "twenty-one steps"}), "A flight of twenty-one " +
        "steps lead up to a double door of black oak, inlaid with " +
        "copper runes - the entry to the Tower.\n");

    add_item(({"door","double door","black oak","double door of black oak",
        "copper runes","runes"}), "The entry to the crimson tower is " +
        "a double door of black oak, inlaid with copper runes. There " +
        "is no door handle or obvious way this door can be opened.\n");

    add_item(({"grove","grove of tall pine trees","peaceful grove",
        "forest","kadothan grove"}),
        "Through the barbican to your east is a grove of tall pine " +
        "trees - the magical Kadothan Grove. The pine trees sway " +
        "serenely to a gentle highland breeze, almost hypnotically.\n");

    add_item(({"pine trees","trees","tree","pine tree","trunks"}),
        "You can see tall pine trees rise from the grove surrounding " +
        "the tower on the other side of the wall, swaying serenely " +
        "to a gentle highland breeze, almost hypnotically.\n");

    add_item(({"tower","crimson tower","squat tower","short tower",
        "rathfast","crimson keep","keep","tower of high sorcery",
        "square tower"}), "To your west rises a stout, square tower " +
        "with walls of brillant red supported by massive buttresses. " +
        "Gargoyles adorn crenelated battlements, making it look more " +
        "like a nobleman's castle than a sanctuary for wizards.\n");

    add_item(({"massive buttresses","buttresses"}),
        "Massive buttresses reinforce the walls of the tower.\n");

    add_item(({"walls","crimson walls","wall","stout wall","whorls",
        "silver lightning","lightning","stormclouds","inky black","black",
        "red stone","stone"}), "Surrounding the tower is a stout wall " +
        "of red stone, mottled and marked here and there with whorls of " +
        "inky black, forever twisting and turning like stormclouds that " +
        "occasionally flare with silver lightning. Atop the wall " +
        "are crenelated battlements and gargoyles, at odds with the " +
        "welcoming gateless opening to your east allowing easy entry " +
        "to the tower grounds.\n");

    add_item(({"battlements","gargoyles","gargoyle","crenelated " +
        "battlements"}), "Gargoyles stare down from the crenelated " +
        "battlements of the tower.\n");

    add_item(({"gate","passage","gateless passage","barbican","opening",
        "gateless opening"}), "To your east is a gateless passage " +
        "through the tower's barbican, leading to a grove of pine trees.\n");

    add_item(({"grass","emerald grass","tower proper","proper","lawn",
        "wide lawn"}), "Surrounding the tower is a wide lawn of " +
        "brilliant emerald-green grass, criss-crossed by a maze of " +
        "paths.\n");

    add_item(({"paths","path","maze","white stone paths",
        "maze of white stone paths","maze of paths","stone paths",
        "white stone","white stone paths"}), 
        "Criss-crossing the wide lawn is a maze of paths that wind " +
        "around the crimson tower before you.\n");

    add_item("broad path","You stand on a broad path that runs west " +
        "up to the entry of the tower and east through the barbican " +
        "out into the grove surrounding the tower.\n");

    add_item(({"city","great city","daltigoth"}), "The tower stands " +
        "upon a high hill within a grove of pines overlooking a city " +
        "clearly of Ergothic design. To your east you can make out a " +
        "great imperial palace, its tall minarets rising high above " +
        "the height of the crimson tower.\n");

    add_item(({"imperial palace","palace","minaret","minarets"}),
        "To your east rises a great imperial palace, the seat of power " +
        "of the emperor of Ergoth.\n");

    OUTSIDE;

    add_exit(WOHS_TEST + "room/daltigoth_tower1", "east", 
        "@@enter_barbican");
    add_exit(WOHS_TEST + "room/daltigoth_tower3", "west", 
        "@@granted_access");

    reset_tower_room();
}

int
enter_barbican()
{
    if(TP->query_prop(THIRD_TASK) && TP->query_prop(FLEE_WARNING))
    {
	write("Legions of Ergothian forces have flooded the barbican, " +
            "blocking any passage out of the Tower to your east! There " +
            "is no escape that way!\n");
	return 1;
    }

    if(TP->query_prop(THIRD_TASK) && TP->query_prop(BATTLE_PROP))
    {
	write("A battle rages between the magical gargoyle guardians " +
            "and a legion of Ergothian soldiers, cavaliers and " +
            "clerical presbyters! There is too much chaos to pass back " +
            "through that way!\n");
	return 1;
    }

    return 0;
}

int
granted_access()
{
    if(!objectp(wizard))
    {
	write("There is no Master of the Tower! The black oak doors " +
            "remain solidly closed.\n");
	return 1;
    }

    if(TP->query_prop(FLEE_WARNING))
    {
	write("With the Master of the Tower focusing on other matters, " +
            "the doors of the Tower remain closed.\n");
	return 1;
    }

    if(TP->query_prop(GRANTED_ACCESS) || TP->query_wiz_level())
    {
	write("As you walk up the twenty-one steps the copper runes " +
            "of the black oak double door glow, and it silently opens " +
            "allowing you entry to the Tower of High Sorcery of " +
            "Daltigoth.\n");
	return 0;
    }

    write("You walk up the twenty-one steps to the black oak double " +
        "doors, but you cannot open them. You likely need the " +
        "permission of the Master of the Tower to gain entry.\n");
    return 1;          

}

void
first_wave(object player)
{
    setuid();
    seteuid(getuid());

    object s1, s2, s3, s4, c1, c2, c3, c4, c5, c6, p1, p2, p3;
    int stat = 260;   
    string name = player->query_real_name();

    s1 = clone_object(WOHS_NPC + "scout");
    s1->arm_me();
    s1->move(TO);
    s1->set_stats(({stat, stat, stat, stat, stat, stat}));
    s1->heal_hp(10000);
    s1->command("kill iriale");

    s2 = clone_object(WOHS_NPC + "scout");
    s2->arm_me();
    s2->move(TO);
    s2->set_stats(({stat, stat, stat, stat, stat, stat}));
    s2->heal_hp(10000);
    s2->command("kill iriale");

    s3 = clone_object(WOHS_NPC + "scout");
    s3->arm_me();
    s3->move(TO);
    s3->set_stats(({stat, stat, stat, stat, stat, stat}));
    s3->heal_hp(10000);
    s3->command("kill " +name);

    s4 = clone_object(WOHS_NPC + "scout");
    s4->arm_me();
    s4->set_stats(({stat, stat, stat, stat, stat, stat}));
    s4->heal_hp(10000);
    s4->move(TO);

    c1 = clone_object(WOHS_NPC + "cavalier");
    c1->arm_me();
    c1->move(TO);
    c1->set_stats(({stat, stat, stat, stat, stat, stat}));
    c1->heal_hp(10000);
    c1->command("kill iriale");

    c2 = clone_object(WOHS_NPC + "cavalier");
    c2->arm_me();
    c2->move(TO);
    c2->set_stats(({stat, stat, stat, stat, stat, stat}));
    c2->heal_hp(10000);

    c3 = clone_object(WOHS_NPC + "cavalier");
    c3->arm_me();
    c3->move(TO);
    c3->set_stats(({stat, stat, stat, stat, stat, stat}));
    c3->heal_hp(10000);
    c3->command("kill iriale");

    c4 = clone_object(WOHS_NPC + "cavalier");
    c4->arm_me();
    c4->move(TO);
    c4->set_stats(({stat, stat, stat, stat, stat, stat}));
    c4->heal_hp(10000);
    c4->command("kill iriale");

    c5 = clone_object(WOHS_NPC + "cavalier");
    c5->arm_me();
    c5->move(TO);
    c5->set_stats(({stat, stat, stat, stat, stat, stat}));
    c5->heal_hp(10000);
    c5->command("kill " +name);

    c6 = clone_object(WOHS_NPC + "cavalier");
    c6->arm_me();
    c6->move(TO);
    c6->set_stats(({stat, stat, stat, stat, stat, stat}));
    c6->heal_hp(10000);
    c6->command("kill iriale");

    p1 = clone_object(WOHS_NPC + "presbyter");
    p1->arm_me();
    p1->set_stats(({stat, stat, stat, stat, stat, stat}));
    p1->heal_hp(10000);
    p1->move(TO);
    p1->command("kill " +name);

    p2 = clone_object(WOHS_NPC + "presbyter");
    p2->arm_me();
    p2->move(TO);
    p2->set_stats(({stat, stat, stat, stat, stat, stat}));
    p2->heal_hp(10000);

    p3 = clone_object(WOHS_NPC + "presbyter");
    p3->arm_me();
    p3->move(TO);
    p3->set_stats(({stat, stat, stat, stat, stat, stat}));
    p3->heal_hp(10000);
    p3->command("kill iriale");

    return;
}

void
serl_wave(object player)
{
    setuid();
    seteuid(getuid());

    object serl;

    serl = clone_object(WOHS_NPC + "duke");
    serl->arm_me();
    serl->move(TO);
    serl->command("shout Foul dogs! Know the name of death as it " +
        "approaches you!");
    serl->command("introduce myself");
    serl->command("say Vengeance shall be mine!");
    serl->command("kill iriale"); 
}

void
enter_inv(object ob, object from)
{
    ::enter_inv(ob, from);

    if(interactive(ob))
    {
	if(ob->query_prop(FLEE_WARNING))
	{
	    if(objectp(wizard))
	    {
		set_alarm(1.5,0.0, &wizard->command("emote slumps in " +
                    "exhaustion, her attempts to awaken the magical " +
                    "guardians of the Tower disrupted by your abrupt " +
                    "return."));
		set_alarm(2.5,0.0, &wizard->command("emote gasps: " +
                    "Cowardly fool! You have doomed us all!"));
	    }

	    set_alarm(5.0,0.0, &WOHS_TELL_ROOM(ob, "\nYou here the " +
                "victorious clarion call of an Ergothian war horn!\n\n"));
	    set_alarm(7.0,0.0, &WOHS_TELL_ROOM(ob, "A tall hoary-bearded " +
                "human storms into the tower proper, a heavy runed " +
                "greatsword wielded menacingly in both hands!\n\n"));
	    set_alarm(7.5,0.0, &serl_wave(ob));
	    set_alarm(12.0,0.0, &WOHS_TELL_ROOM(ob, "\nAn Ergothian " +
                "legion swarms into the the tower proper!\n\n"));
	    set_alarm(12.5,0.0, &first_wave(ob));
	    return;
	} 

	if(ob->query_prop(BATTLE_PROP) && !(ob->query_prop(FOURTH_TASK)))
	{
	    if(objectp(wizard))
	    {
		int dmg_taken = ob->query_prop(DMG_TAKEN);

		wizard->add_prop(DIALOG_PROP, 1);
		WOHS_MANAGER->add_wohs_test_props(ob, DMG_TAKEN, dmg_taken);

		set_alarm(1.5,0.0, &wizard->command("emote slumps in " +
                    "exhaustion, her attempts to awaken the magical " +
                    "guardians of the Tower leaving her mentally " +
                    "exhausted."));
		set_alarm(2.5,0.0, &wizard->command("emote gasps: Well " +
                    "done Aspirant... however I fear the gargoyle " +
                    "guardians will not last long against " +
		    "the legion it must defend against."));
		set_alarm(5.5,0.0, &wizard->command("say They will buy " +
                    "us some much needed time."));
		set_alarm(8.5,0.0, &wizard->command("say We are not " +
                    "going to be able to hold the Tower, however we " +
                    "can't let it fall into the hands of " +
		    "the ignorant and untrained."));
		set_alarm(12.5,0.0, &wizard->command("say I will remain " +
                    "here as the last bastion of defence. I will need " +
                    "you to get they shadow key that opens the door to " +
                    "the Heartroom of the Tower, enter the Heartroom, and " +
		    "undo the magic that holds the Tower together."));
		set_alarm(16.5,0.0, &wizard->command("say This will " +
                    "quickly destroy the Tower in an explosion this " +
                    "world has not seen before."));
		set_alarm(18.5,0.0, &wizard->command("smile rue"));
		set_alarm(22.5,0.0, &wizard->command("say So if you " +
                    "get the opportunity after setting the Tower's " +
                    "destruction in motion, I suggest using " +
		    "whatever magic you can to flee the Tower."));
		set_alarm(25.5,0.0, &wizard->command("say We are " +
                    "running out of time. If you have any questions, " +
                    "ask them now. You may not get another chance."));
		set_alarm(25.5,0.0, &wizard->remove_prop(DIALOG_PROP));
		set_alarm(26.0,0.0, &ob->add_prop(FOURTH_TASK, 1));
		set_alarm(26.0,0.0, &WOHS_MANAGER->add_wohs_test_props(ob, 
                    FOURTH_TASK, 1));
	    }  
	}
    }

}
