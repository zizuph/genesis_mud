/* Sarr */
#include "defs.h"
inherit STD_UNDEAD;
inherit LIB_DIR + "despawn";
inherit "/std/combat/unarmed";

int ok_kill;

void
set_ok_kill()
{
   ok_kill = 1;
}

void
do_despawn()
{
    TELL_SEEN(TO, QCTNAME(TO) + " looks around and marches off, rattling as it goes.\n");
    remove_object();
}

void
create_monster()
{
    ::create_monster();
    set_name("skeleton");
    add_adj("bloody");
    set_short("bloody skeleton");
    set_long("This creature looks just like an animated skeleton, "+
    "only its bones are covered and dripping with blood. Small "+
    "fragments of flesh cling on some of its joints. Within one "+
    "of its eye sockets, you see a blood-shot eyeball, oozing "+
    "dark red liquid down its face. This is truly a gruesome "+
    "sight.\n");

    set_stats(STAT_ARRAY(110));
    set_skill(SS_UNARM_COMBAT,60);
    set_skill(SS_DEFENSE,70);

    add_prop(LIVE_I_NEVERKNOWN, 1);
    add_prop(LIVE_I_SEE_INVIS, 1);
    add_prop(LIVE_I_NO_CORPSE,1);

    remove_prop(LIVE_M_NO_ACCEPT_GIVE);

    set_cact_time(3);
    add_cact("emote burbles: Yooou cannot essscape meeee!");
    add_cact("emote burbles: Foooolish morrrtaaal, the grave reaches for you!");
    add_cact("emote moans loudly and blood gushes from its jaw.");
    add_cact("emote wails a hiddeous laughter, blood forthing at its jaw.");

    set_attack_unarmed(0, 40, 40, W_SLASH, 10, "right skeletal foot");
    set_attack_unarmed(1, 35, 35, W_SLASH, 40, "left skeletal claw");
    set_attack_unarmed(2, 35, 35, W_SLASH, 40, "right skeletal claw");
    set_attack_unarmed(3, 40, 40, W_SLASH, 10, "left skeletal foot");
    set_hitloc_unarmed(0, 45, 45, "rib cage");
    set_hitloc_unarmed(1, 45, 15, "skull");
    set_hitloc_unarmed(2, 34, 20, "legs");
    set_hitloc_unarmed(3, 34, 10, "left arm");
    set_hitloc_unarmed(4, 34, 10, "right arm");

    init_despawn();
}

string 
query_combat_file() 
{
    return "/d/Raumdor/common/std/chumanoid.c";
}

void
do_die(object killer)
{
    object bones;
    if(ok_kill == 1)
    {
        log_file("killed_bskeleton",
                killer->query_name()+" killed the skeleton.\n");
        ::do_die(killer);
    }
    else
    {
        command("emote collapses into a pile of bloody bones!");
        seteuid(getuid());
        bones = clone_object(COMMON_OBJ_DIR + "bbones");
        bones->add_prop(QUEST_BLOODY_SKELETON, killer);
        bones->move(E(TO));
        remove_object();
    }
}

void
enter_inv(object ob, object from)
{
    ::enter_inv(ob,from);
    if(MASTER_OB(ob) == QUEST_HORN_FILE)
        set_alarm(3.0,0.0,"response",ob,from);
}

void
response(object ob, object from)
{
    command("emote pauses.");
    if(query_attack())
    {
        query_enemy(-1)->stop_fight(TO);
        stop_fight(query_attack());
        command("emote stops fighting.");
    }
    command("emote grins with delight.");
    command("emote gurgles: Khiraaa, yesss, I know what ye ssseek.");
    set_alarm(5.0,0.0,"response2",ob,from);
}

void
response2(object ob, object from)
{
    command("emote gurgles: Go ssseeketh in the flatsss...");
    command("emote gurgles: There, you will find a sssymbol.");
    set_alarm(3.0,0.0,&command("emote gurgles: Remember thisss..."));
    set_alarm(6.0,0.0,&command("emote gurgles: The blood flowsss now in you, "+
    "but he who wishesss to ssserve must make a sssacrifice. You must " +
    "ssspill your blood. Take thisss. Pierce your veins over the sssymbol."));
    set_alarm(8.0,0.0,&command("emote hisses a bloody laugh."));
    set_alarm(8.0,0.0,&command("give horn to "+from->query_real_name()));
    set_alarm(9.0,0.0,&command("drop horn"));
}

void
init_living()
{
    ::init_living();
    if (interactive(TP))
        reset_despawn();
}
