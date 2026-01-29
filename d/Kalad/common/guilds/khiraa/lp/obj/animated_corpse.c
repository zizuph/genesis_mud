/* 
 * /d/Kalad/common/guilds/khiraa/lp/obj/animated_corpse.c
 * Purpose    : This is the monster that is created by the lichs spell 'lraise'. It takes on the likeness of the corpse its cast on.
 * Located    : Conjured by the spell 'lraise'
 * Created By : Sarr 12.Apr.97
 * Modified By: 
 */ 

inherit "/d/Kalad/common/raum/std/undead_std.c";
inherit "/std/combat/unarmed";
#include "/d/Kalad/defs.h"
#include "/d/Kalad/common/guilds/khiraa/khiraa_defs.h"
#include <tasks.h>

string exit_guarded;
object gMaster;

void
set_master(object ob)
{
    gMaster = ob;
}

void
create_monster() 
{
   ::create_monster();
   add_name("zombie");
   set_gender(G_NEUTER);
   set_stats(({65,65,65,1,1,50}));
   set_long("A foul looking zombie that looks fresh from the grave!\n");
   set_skill(SS_DEFENCE,60);
   set_skill(SS_UNARM_COMBAT,60);
   add_prop(UNDEAD_I_NO_AUTO,1);
   add_prop(LIVE_I_NEVERKNOWN, 1);
   add_prop(OBJ_I_WEIGHT, 6500);
   add_prop(OBJ_I_VOLUME, 3500);
   add_prop(LIVE_I_UNDEAD,40);
   set_alignment(-500);
   set_knight_prestige(500);
   set_act_time(3);
   add_act("moan");
   add_act("emote wants to tear your head open and eat your brains.");
   set_cact_time(3);
   add_cact("say I will eat your corpse when you die...");
   add_cact("say I can smellll youurrr braiinnsss!!");
   add_cact("emote lusts for your blood.");
   add_cact("emote licks its chops thinking about devouring your heart.");
   set_attack_unarmed(0, 35, 35, W_IMPALE, 10, "savage bite");
   set_attack_unarmed(1, 25, 30, W_SLASH, 45, "left claw");
   set_attack_unarmed(2, 25, 30, W_SLASH, 45, "right claw");
   set_hitloc_unarmed(0,10,15,"head");
   set_hitloc_unarmed(1,10,10,"left arm");
   set_hitloc_unarmed(2,10,10,"right arm");
   set_hitloc_unarmed(3,20,45,"body");
   set_hitloc_unarmed(4,10,20,"legs");
}

string
query_combat_file()
{ 
    return "/d/Kalad/common/raum/std/chumanoid.c"; 
}


void
notify_you_killed_me(object who)
{
    object *obj;
    command("emote silently hisses in satisfaction as its victim falls before it.");
    command("emote moans: Your corpse isss miinnnneeee.....");
    who->add_prop(LIVE_I_NO_CORPSE,1);
    command("emote eats the corpse of "+ who->query_name()+ ".");
}

void
do_die(object killer)
{
    command("emote falls to the ground, spewing black ooze out of its mouth.");
    command("emote moans: Yourrr tiiime will commme soooon, mortaaal.....");
    ::do_die(killer);
}

void
zombie_move()
{
    exit_guarded = "";
    set_random_move(5);
}

void
zombie_smove()
{
    TO->seq_delete("_mon_ranwalk");
}

int
guard_exit(string exit)
{
    string *exits;
    exits = E(TO)->query_exit_cmds();
    if(member_array(exit,exits) == -1)
        return 0;
    tell_room(E(TO),QCTNAME(TO)+"'s blaze with unholy light, and it "+
    "suddenly comes to rest.\n");
    exit_guarded = exit;
    return 1;
}

int
unguard_exit()
{
    if(strlen(exit_guarded))
    {
        exit_guarded = "";
        return 1;
    }
    return 0;
}

int
my_check(string str)
{
    if(IS_DK(TP) || IS_LP(TP))
        return 0;
    if(stringp(exit_guarded) && (query_verb() == exit_guarded))
    {
        if(TP->resolve_task(TASK_DIFFICULT,({TS_STR,TS_DEX}),gMaster,
           ({TS_INT,TS_WIS})) > 0)
        {
            write("You smash your way through the "+short()+" with "+
            "great speed and strength!\n");
            say(QCTNAME(TP)+" smashes "+HIS(TP)+" way through the "+
            short()+" with great speed and strength!\n");
            return 0;
        }
        write("The "+short()+" blocks you from going that way!\n");
        say(QCTNAME(TP)+" is blocked from going "+query_verb()+
        " by the "+short()+"!\n");
        return 1;
    }
    return 0;
}

void
init_living()
{
    ::init_living();
    set_alarm(1.5,0.0,"my_attack",TP);
    add_action(my_check,"",1);
}
