// file name:        /d/Avenir/common/bazaar/infidel/rilkin.c
// creator(s):       Cirion, December 1996
// revision history: Denis, Jan'97: Misc changes.
// purpose:          A thief in the Infidel hideout. He will teach
//		     thief skills to a good player, and has a set
//		     of thief tools and some blue globes.
// note:	     
// bug(s):	     
// to-do: 	     

#include "../infidel.h"
inherit MON + "guard";
inherit "/lib/skill_raise";

#define MAX_OPEN_LOCK     20
#define MAX_PICK_POCKET   20
#define MAX_HIDE          50
#define MAX_SNEAK         50

void create_monster()
{
    ::create_monster();
    set_name("rilkin");
    set_race_name("human");
    set_adj(({"lean","hungry"}));

    set_long("A suspcious glint shines from his eyes, as he " +
             "looks around." + VBFC_ME("tools") +
             " He is lean and slender, and has a long white " +
             "scar that runs from his neck to just below his " +
             "left eye.\n");

    add_prop(CONT_I_HEIGHT, 280);

    set_stats(({ 50, 120, 100, 90, 70, 45 }));
    set_whimpy(20);

    set_title("the Silent Hand of the Infidels");
    set_alignment(0);

    set_skill(SS_WEP_SWORD, 50);
    set_skill(SS_WEP_KNIFE, 90);
    set_skill(SS_DEFENCE, 80);
    set_skill(SS_BLIND_COMBAT, 90);
    set_skill(SS_HIDE, 99);
    set_skill(SS_SNEAK, 99);
    set_skill(SS_PARRY, 80);

    KILL_THIEF;

    create_skill_raise();
    sk_add_train(SS_OPEN_LOCK, "pick open doors and chests", 0, 5,
		 MAX_OPEN_LOCK, SS_DEX, 100 );
    sk_add_train(SS_PICK_POCKET, "pick pockets", 0, 5, 
                 MAX_PICK_POCKET, SS_DEX, 100 );
    sk_add_train(SS_HIDE, "hide", 0, 5, MAX_HIDE, SS_DEX, 100 );
    sk_add_train(SS_SNEAK, "sneak about", 0, 5, MAX_SNEAK, SS_DEX, 100 );

    set_chat_time(8);
    add_chat("I can teach the skills of a master thief.");

  MAKE_INFIDEL;
}

string
tools()
{
    if (present("tools"))
        return " At his belt is a small ring of strange-looking metal tools.";
    else
        return "";
}

int
sk_improve(string str)
{
    if (query_attack())
    {
         command("emote appears to be busy with other things right now.");
         return 1;
    }

    if (TP->query_prop("_live_i_attacked_infidel_guard"))
    {
        command("shout Intruder! You will die!");
        command("kill " + TP->query_real_name());
        return 1;
    }

    if (TP->query_prop("_live_i_killed_infidel_guard"))
    {
        command("shout Murderer! You will make you pay!");
        command("kill " + TP->query_real_name());
        return 1;
    }

    if (TP->query_alignment() < 0)
    {
        command("say I will teach nothing to scum like yourself.");
        return 1;
    }

    return ::sk_improve(str);
}

void
init_living()
{
    ::init_living();
    init_skill_raise();
}

string
get_name()
{
    return "rilkin";
}

void
arm_me()
{
    int i = 2 + random(4);

    ::arm_me();
    clone_object(OBJ + "thief_tools")->move(TO);
    clone_object(OBJ + "phial")->move(TO);

    while (i--)
        clone_object(OBJ + "globe")->move(TO);
}

int
special_attack(object enemy)
{
    string *dirs;

    if (query_hp() > query_max_hp() / 2)
        return 0;

    if (!present("globe") || random(3))
        return 0;

    command("break globe");
    dirs = ENV(TO)->query_exit_cmds();
    if (sizeof(dirs))
    {
        command(ONEOF(dirs));
        command("hide");
    }
    return 1;
}
