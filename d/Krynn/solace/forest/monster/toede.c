/*
 * Fewmaster Toede
 * modified from Jeremiah's Verminaard.
 * by Teth
 * Feb.12,'96 
 * modified March 9, 1996 - drops hints about Verminaard's task and add_ask
 * modified March 19, 1996 - patrols Solace now!
 * modified April 25, 1996 - teams with a few of his lackeys now
*/

#include <std.h>
#include <ss_types.h>
#include <wa_types.h>
#include <stdproperties.h>
#include <macros.h>
#include "/d/Krynn/common/defs.h";
inherit M_FILE
inherit AUTO_TEAM

inherit "/std/act/domove";     /* Allows Toede to move */
inherit "/std/act/action";     /* Allows Toede to act  */
inherit "/d/Krynn/std/patrol"; /*Toede wants to patrol Solace */

#define OBJ    "/d/Krynn/solace/forest/obj/"

void
create_krynn_monster()
{
    string str;

    set_name("toede");
    set_living_name("toede");
    set_race_name("hobgoblin");
    set_title("the Fewmaster of Solace");
    set_long("This hobgoblin is appropriately ugly. He has grey, mottled " +
             "skin that sags into folds about his face. Two pig-pink eyes " +
             "stare out at you from beneath his military-looking " +
             "helmet. His fat, flabby body leaks out between the pieces " + 
             "of his armour.\n"); 
    add_name("fewmaster");
    set_adj("flabby");
    add_adj("reeking"); 
    set_gender(G_MALE);
    add_prop(NPC_I_NO_LOOKS,1);
    set_introduce(1);

    set_pick_up_team(({"grum", "hepp"}));

    set_stats(({120,108,160,90,90,80}));
    set_skill(SS_DEFENCE,        90);
    set_skill(SS_PARRY,          75);
    set_skill(SS_WEP_SWORD,      90);
    set_skill(SS_UNARM_COMBAT,   50);
    set_skill(SS_BLIND_COMBAT,   50);
    set_skill(SS_AWARENESS,      50);

    set_alignment(-600);
    set_knight_prestige(500);
   
    set_default_answer("For some reason, you are ignored.\n");
    add_ask(" [about] 'verminaard'", "say Verminaard is a Cleric of the " +
            "Dark Queen! I wouldn't want to cross his path! I hope he " +
            "doesn't summon me for his next mission!",1);
    add_ask(" [about] 'work' / 'hire' / 'mission' / 'job'", "say " +
            "I don't know what Verminaard has planned, but he'd " + 
            "be an idiot to lower his standards and give you some sort of " +
            "work!",1);       
    set_act_time(4);
    add_act(({"say I doubt Verminaard will hire anyone from here " +
            "for a job, considering they're all useless rabble!" ,
            "emote snorts derisively."}));
    add_act(({"say That Verminaard can use his own lackeys to do his " +
            "dirty work for him! I need mine to protect me from those " +
            "damned upstart Solace villagers!", "emote spits a gob of " +
            "phlegm on the ground in disgust."}));
    add_act("emote watches you with a sneering, supercilious look on his " +
            "flat face.");
    add_act("say I am Fewmaster Toede, leader of the forces that are " +
            "keeping Solace protected from undesirable elements, like you!");
    add_act(({"say Where is that damn horse of mine? He's always " +
              "getting lost. I think I'll just eat him and be done with " +
              "it.", "grin hungrily"}));
    add_act("emote scratches himself under the armpit.");
    add_act("burp loudly");
    add_act("say Of all the races of Krynn, I hate kender the most!");
    add_act("emote rudely scratches himself where it itches.");
    add_act("emote grins connivingly.");

    set_cact_time(3);
    add_cact("say If I kill you and find a blue crystal staff, Verminaard " +
             "will be most pleased.");
    add_cact("say Die! You child of a kender and a gully dwarf!");
    add_cact("emote pauses for a moment to belch.");
    add_cact("say Come get some!");
    add_cact("emote flexes his muscles, causing his flab to ripple.");
    add_cact("emote laughs condescendingly at you.");	

    set_patrol_time(50);
    set_patrol_path(({"s", "sw", "sw", "sw", "sw", "sw", "s", "sw", "s",
        "s", "s", "s", "w", "w", "w", "w", "nw", "nw",
        "say Those who take baths in Crystalmir Lake are fops!",
        "se", "se", "ne", "e", "ne", "u", "se", "ne",
        "e", "enter", "say Tika is the hottest wench I know!", "cackle",
        "out", "e", "e", "n", "say Tarshir should only reward me.", "s",
        "sw", "w", "sw", "exa board", "say Stupid pitiful note-writers.",
        "spit", "se", "s", "say Bloody shop is closed at night!", "grumble",
        "say How inconvenient! I'll tar and feather the shopowner!", "se", 
        "sw", "s", "say Never any mail for me!", "spit", "n", "w", "nw", "n",
        "n", "n", "sw", "say Rumour has it that Elves are around here.",
        "s", "sw", "d", "n", "e", "e", "e", "e", "n", "n", "n", "n",
        "ne", "n", "ne", "ne", "ne", "ne", "ne", "n"}));
 
}

public void
init_living()
{
    init_team_pickup();

    ::init_living();
}

public void
arm_me()
{
    clone_object(OBJ + "tsword")->move(TO);
    clone_object(OBJ + "tarmour")->move(TO);
    clone_object(OBJ + "tshinguard")->move(TO);
    clone_object(OBJ + "tboots")->move(TO);
    clone_object(OBJ + "tgauntlets")->move(TO);
    clone_object(OBJ + "thelmet")->move(TO);
    command("wear all");
    command("wield all");
}

