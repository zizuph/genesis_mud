inherit "/d/Genesis/lib/intro.c";
inherit "/std/monster";
/* Karath's creation(well Nap said we hadda do it ;) */
 
#include "/d/Emerald/defs.h"
#define PATH     "/d/Emerald/leah/"
 
void arm_me();

void
create_monster()
{
    set_name("santos");
    set_living_name("_santos_");
    set_title("the Cassanova of Emerald");
    set_race_name("human");
    add_name("gardener");
    add_adj("muscular");
    add_adj("tanned");
    set_long("@@my_long");
 
    set_stats( ({ 60, 60, 60, 20, 20, 30}) );
 
    set_skill(SS_DEFENCE, 40);
    set_skill(SS_HERBALISM, 90);
    set_skill(SS_UNARM_COMBAT, 30);
    set_skill(SS_WEP_KNIFE, 60);
    heal_hp(10000);
 
    set_alignment(150);
 
    set_random_move(12);
    set_restrain_path(({ PATH+"g2", PATH+"g3", PATH+"g4", PATH+"g5", PATH+"g6", PATH+"g8", PATH+"g9"}));
 
    set_chat_time(8);
    add_chat("Oh Sybille...there aren't many like you...well maybe "+
       "that one girl down the street or that...");
    add_chat("My love for women is endless.");
    set_cchat_time(4);
    add_cchat("Oh...just try and get away with this punk!");
    add_cchat("I'll destroy you like a mere elf.");
    set_act_time(6);
    add_act("spit elf");
    add_act("emote checks you out.");
    add_act("ponder");
    add_act("think");
    add_chat("She just isn't faithful like I am...Elves!");
    set_alarm(1.0, 0.0, arm_me);
    trig_new("%w 'introduces' %s", "react_introduce");
}
 
void
arm_me()
{
    object wep, ov, rg, lg;
 
    seteuid(getuid());
 
    wep=clone_object(VILLAGE_DIR+"wep/knife");
    wep->move(this_object());
 
    ov=clone_object(VILLAGE_DIR+"obj/overalls");
    ov->move(this_object());
 
    rg=clone_object(VILLAGE_DIR+"obj/r_glove");
    rg->move(this_object());
 
    lg=clone_object(VILLAGE_DIR+"obj/l_glove");
    lg->move(this_object());
 
    command("wield all");
    command("wear all");
}
 
 
string
my_long()
{
    if(this_player()->query_gender()==0)
    return"This fellow looks like a rival for any woman's affections.\n"+
       "You think he may be heartsick and is gardening his sorrows away.\n";
    if(this_player()->query_gender()==1)
    return"This fellow seems to be all your heart has ever wanted. He's\n"+
    "tall, tanned, and confident as he works in the flowerbeds.\n";
    return"He's a gardener...what more do you want to know?";
}
 
void
init_living()
{
    if(this_player()->query_gender()==G_FEMALE)
    call_out("do_flirt", 4, this_player());
    ::init_living();
}
 
void
do_flirt(object ob)
{
    object her;
    her=ob->query_real_name();
    command("french "+her);
    command("wink "+her);
    command("whisper "+her+" My darling...won't you be with me forever?");
}
