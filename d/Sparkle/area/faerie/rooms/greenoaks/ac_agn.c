/*
 * Northern Adventurer's Guild of Green Oaks
 * By Finwe, August 2004
 */
 
#include "defs.h"
#include <macros.h>
#include <ss_types.h>
#include <stdproperties.h>

inherit INDOORS_BASE;
inherit "/lib/skill_raise";
inherit "/lib/guild_support"; 

void set_up_skills();
 
void
create_indoor_room()
{
    add_prop(ROOM_S_MAP_FILE, "faerie_map.txt");
    set_short("General Skills Training of the " + ACADEMY_NAME);
    set_long("This is the " + short() + ". It is one of the public " +
        "training areas. The room is spacious and " + 
        "well used. Here, elves learn skills to prepare them for travels. " +
        "A plush rug covers the floor on which many elves may sit and " +
        "learn their new skills.\n");

    set_add_ceiling_flat("The ceiling is white and undecorated.");
    
    add_item(({"floor", "ground"}),
        "The floor made from white blocks of stone. They are smooth " +
        "and plain. A large rug is spread across the floor.\n");
    add_item(({"large rug", "large carpet", "large plush carpet", 
            "large plush rug", "rug", "carpet"}),
        "It is large and plush, and fills the room. The rug is emerald " +
        "green and so closely resembles a grassy meadow, it seems " +
        "to move in an unseen breeze.\n");

    reset_room();
    create_skill_raise();
    set_up_skills();
    add_item("sign", "It is square and posted on the wall. " +
        "Important information can be read from it.\n");
    add_cmd_item("sign", "read", "@@read_sign@@");

    add_item(({"medallions", "ornate medallion", "ornate medallions", 
            "medallion"}),
        "The medallions are large and oval shaped. They are fashioned " +
        "from yellow gold and set in the floor in random locations. " +
        "They are decorated with stylized vines and trees, and seem to " +
        "glow with a golden light.\n");

    add_exit(GO_DIR + "ac_boardrm", "southeast");
 
}

init() 
{
    init_skill_raise();
    add_action("sit_down","sit");
    add_action("sit_down","meditate");
    ::init();
}

int
sit_down(string str)
{
   if ((str=="down on medallion") || (str=="down") || !str) 
   {
      gs_meditate("test");
      return 1;
   }
   return 0;
}


void reset_room() 
{ 
}

set_up_skills() 
{
    sk_add_train(SS_ANI_HANDL,"handle animals","animal handling",100,20);
    sk_add_train(SS_TRACKING,"find tracks","tracking",100,30);
    sk_add_train(SS_ALCHEMY, "mix magic potions","alchemy", 100, 10);
    sk_add_train(SS_ELEMENT_EARTH, "use earth spells", "earth spells", 100, 15);
    sk_add_train(SS_ELEMENT_LIFE, "use life spells", "life spells", 100, 20);
    sk_add_train(SS_HERBALISM,"search for herbs","herbalism",100,20);
    sk_add_train(SS_LANGUAGE, "understand various languages", "language", 100, 30);
    sk_add_train(SS_SWIM,"swim","swimming",100,30);
    sk_add_train(SS_SPELLCRAFT, "perform magic and spells", "spellcraft", 100, 20);
    sk_add_train(SS_SNEAK,"sneak into rooms","sneak",100,20);
    sk_add_train(SS_HIDE,"hide inside rooms","hide",100,20);
}

int
sk_improve(string str) 
{
    return ::sk_improve(str);
}

/*
 * Function name: gs_hook_start_meditate
 * Description  : This hook is called when player starts to meditate. You can
 *                mask this function to give a different message.
 */
void
gs_hook_start_meditate()
{
    write("You choose a vacant medallion and sit down on it. As you " +
        "close your eyes, peace and self control fill, and a faint " +
        "golden light surrounds you. Your mind is set at " +
        "ease as you concentrate on other things. You find yourself " +
        "able to <set> your different preferences, and you can estimate " +
        "your stats and their progress. When you are finished, you " + 
        "may <rise> at anytime.\n");
    say(QCTNAME(this_player()) + " chooses a vacant medallion, sits " +
        "down on it, and is suddenly lost in thought. " + CAP(HE_SHE(TP)) + 
        " is surrounded by a faint golden light.\n");
}

void
gs_hook_rise()
{
    write("With a bit of control, you open your eyes and stand up from " +
        "the medallion. The faint golden light fades from you.\n");
    say(QCTNAME(TP)+" suddenly stands up from a medallion and looks " +
        "around. The faint gold light fades away.\n");
}

string read_sign()
{
    return "You may learn or improve your skills here. Below are the skills " +
        "available here:\n\n" +
        "\tSkill                   Max Level\n"+
        "\t-----------------------------------------\n" +
        "\tAlchemy . . . . . . . . Superior Student\n" +
        "\tAnimal Handling . . . . Superior Amateur\n" +
        "\tEarth Spells. . . . . . Confident Amateur\n" +
        "\tHerbalism . . . . . . . Superior Amateur\n" +
        "\tHide. . . . . . . . . . Superior Amateur\n" +
        "\tLanguage. . . . . . . . Superior Layman\n" +
        "\tLife Spells . . . . . . Superior Amateur\n" +
        "\tSneak . . . . . . . . . Superior Amateur\n" +
        "\tSpellcraft. . . . . . . Superior Amateur\n" +
        "\tSwim. . . . . . . . . . Superior Layman\n" +
        "\tTracking. . . . . . . . Superior Layman\n\n" +
        "You may also <sit down> on a medallion and change your stats.\n";
}
