inherit "/std/room";
inherit "/d/Cirath/std/shiva_train.c";
inherit "/lib/guild_support";
#include "defs.h"

object meditate;

void
set_up_skills()
{
    create_skill_raise();
    sk_add_train(SS_APPR_MON, "appraise enemies", "appraise enemy", 0, 50);
    sk_add_train(SS_WEP_POLEARM, "fight with a polearm","polearm", 0, 50);
    sk_add_train(SS_PARRY, "parry blows", "parry", 0, 30);
    sk_add_train(SS_DEFENCE, "avoid attacks", "defence", 0, 40);
    sk_add_train(SS_BLIND_COMBAT, "fight in dark", "blind fighting", 0, 30);
    sk_add_train(SS_UNARM_COMBAT, "fight unarmed", "unarmed combat", 0, 40);
    sk_add_train(SS_AWARENESS, "be aware of your surroundings","awareness", 0,50);
    sk_add_train(SS_ACROBAT, "perform difficult task", "acrobat", 0, 20);
    sk_add_train(SS_LOC_SENSE, "locate yourself", "location sense", 0, 40);
    sk_add_train(SS_TRACKING, "track your enemies", "tracking", 0, 40);
    sk_add_train(SS_HUNTING, "hunt your enemies", "hunting", 0, 40);
    sk_add_train(SS_MIL_SHIELD, "use a shield more effectively", "shield", 100, 50);
    sk_add_train(SS_SPEAR, "injure enemies with a polearm", "spear", 100, 100);


}

void
create_room()
{
    set_short("Training room");
    set_long("Lined with racks of shields and spears, this training "
    	+"room is where new recruits of the Tyrian Militia can "
    	+"improve their skills.  Some of the pupils in the room "
    	+"are studying books, while others spin polearms through the "
    	+"air in a flurry of blurred motion.  Still others stand "
    	+"behind shields and take blows from other Militia members "
+"in preparation for battle.  You notice a bronze plaque "
+"hanging from the wall here.\n");
     add_item(({"plaque","bronze plaque"}),
"This bronze plaque looks extremely old and has "
+"something written on it in a strange script that "
+"looks readable.\n");
    add_item(({"rack","racks"}),"These simple wooden racks are "
    	+"bristling with training spears and shields for the "
    	+"recruits to hone their battle skills with.\n");
    add_item(({"shield","shields"}),"Simple chitin and wooden "
    	+"shields fill the training rack.  They are good enough "
    	+"for pratice, but woefully inadequate for war.\n");
    add_item(({"spears","spear"}),"Thin wooden spears protrude "
    	+"from the racks like spines on a porcupine.  These look "
    	+"to be flimsy training spears that would not be effective "
    	+"at all for real combat.\n");
    add_item("pupils","They are a mix of Militia members and new "
    	+"recruits who are training in some of the various things "
    	+"that can be learned here.\n");
    add_cmd_item("plaque","read","The dull bronze plaque "
+"has written on it in an ancient script:\n\n"
+"Members can use mhelp to obtain a full "
+"list of commands.\n");

    INSIDE;

    set_up_skills();
     add_exit(MILITIA_ROOM + "board","east");
    add_exit(MILITIA_ROOM + "m8","north");
    reset_room();
}

init()
{
    init_skill_raise();
    ::init();
    add_action("help","help");
     add_action(gs_meditate, "meditate");
     add_action(gs_list, "list");
}

