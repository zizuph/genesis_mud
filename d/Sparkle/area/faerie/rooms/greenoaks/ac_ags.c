/*
 * Basic indoor room of Green Oaks
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
    set_short("Defense Skills Training of the " + ACADEMY_NAME);
    set_long("This is the " + short() + ". The room is large and open, " +
        "and it is here that elves learn how to protect themselves while " +
        "visiting the " + ACADEMY_NAME + ". Mats are spread around the " +
        "room. They are there protect particpants from hurting themselves " +
        "from all the excercising. Medallions are set in the room in " +
        "various locations. A sign is posted on the wall.\n");

    set_add_ceiling_flat("The ceiling is white and undecorated.");
    add_item("sign", "It is square and posted on the wall. " +
        "Important information can be read from it.\n");
    add_cmd_item("sign", "read", "@@read_sign@@");

    add_item(({"medallions", "ornate medallion", "ornate medallions", 
            "medallion"}),
        "The medallions are large and round. They are fashioned from " +
        "white gold and set in the floor in random locations. They are " +
        "decorated with stylized flowers and seem to glow with a silver " +
        "light.\n");
    add_item(({"mats"}),
        "They are long, rectangular, and scattered around the room. " +
        "Each one is designed to protect anyone who lands on them " +
        "during training sessions.\n");
    add_item(({"white gold"}),
        "This is a type of gold with a pale, silvery color. The medallions " +
        "are made from it, and the gold is fashioned into stylized " +
        "flowers. It seems to glow with a silver light.\n");
    add_item(({"light", "silver light"}),
        "It is a silver brightness that radiates from each medallion.\n");
    add_item(({"flowers", "stylized flowers", "stylized flower"}),
        "They are fancy looking flowers twining around each other in " +
        "the medallions.\n");
    
    

    add_exit(GO_DIR + "ac_boardrm", "north");

    reset_room();
    create_skill_raise();
    set_up_skills();
 
}

init() 
{
    init_skill_raise();
    ::init();
    add_action("sit_down","sit");
    add_action("sit_down","meditate");

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
    sk_add_train(SS_WEP_KNIFE,"fight with a knife","knife",100,30);
    sk_add_train(SS_WEP_SWORD,"fight with a sword","sword",100,30);
    sk_add_train(SS_WEP_POLEARM,"fight with a polearm","polearm",100,30);
    sk_add_train(SS_BLIND_COMBAT,"fight while blinded","blind combat",100,20);
    sk_add_train(SS_DEFENCE,"fight defensively","defence",100,20);
    sk_add_train(SS_UNARM_COMBAT,"fight without weapons", "unarmed combat",100,30);
    sk_add_train(SS_AWARENESS,"become more aware of the surroundings","awareness",100,30);
    sk_add_train(SS_FR_TRAP,"find and remove traps","find and remove traps",100,20);
    sk_add_train(SS_LOC_SENSE, ({ "know where you are", "know where " + 
        HE_SHE(TP) + " is" }) , "location sense", 100, 30);

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
    write("You choose a vacant medallion and sit down on it. As you close " +
        "your eyes, peace and self control fill you, and a faint silver " +
        "light surrounds you. Your mind is set at " +
        "ease as you concentrate on other things. You find yourself " +
        "able to <set> your different preferences, and you can estimate " +
        "your stats and their progress. When you are finished, you " + 
        "may <rise> at anytime.\n");
    say(QCTNAME(this_player()) + " chooses a vacant medallion, sits " +
        "down on it, is suddenly lost in thought, and surrounded by a " +
        "faint silver light.\n");
}

void
gs_hook_rise()
{
    write("With a bit of control, you open your eyes and stand up from " +
        "the medallion. The faint silver light fades away.\n");
    say(QCTNAME(TP)+" suddenly stands up from a medallion and looks " +
        "around. The faint silver light fades away.\n");
}

string read_sign()
{
    return "You may learn or improve your skills here. Below are the skills " +
        "available here:\n\n" +
        "\tSkill                     Max Level\n" +
        "\t------------------------------------------\n" +
        "\tAwareness . . . . . . . . Superior Layman\n" +
        "\tBlindfighting . . . . . . Superior Amateur\n" +
        "\tDefence . . . . . . . . . Superior Amateur\n" +
        "\tFind and Remove Traps . . Superior Amateur\n" +
        "\tKnife . . . . . . . . . . Superior Layman\n" +
        "\tLocation Sense. . . . . . Superior Layman\n" +
        "\tPolearm . . . . . . . . . Superior Layman\n" +
        "\tSword . . . . . . . . . . Superior Layman\n" +
        "\tUnarmed Combat. . . . . . Superior Layman\n\n" +
        "You may also <sit down> on a medallion and change your stats.\n";
}
