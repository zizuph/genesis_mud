inherit "/std/monster";

#include "/sys/ss_types.h"
#include "/sys/macros.h"
#include "/sys/stdproperties.h"
#include "/d/Gondor/defs.h"
#include "/d/Gondor/rohan/horn/hd_defs.h"

create_monster()
{
    if (!IS_CLONE)
        return;
    set_name("_spy_orc");
    add_name("orc");
    set_race_name("orc");
     set_adj("sneaky");
    add_adj("long-armed");
    set_long(BSN("An orc with a sneaky look. He is hiding close to the "+
    "battlement, trying to stay unseen. He appears to be clutching "+
    "something."));
    set_base_stat(SS_STR,random(5)+40);
    set_base_stat(SS_DEX,random(5)+40);
    set_base_stat(SS_CON,random(5)+40);
    set_base_stat(SS_INT,random(5)+30);
    set_base_stat(SS_WIS,random(5)+30);
    set_base_stat(SS_DIS,random(5)+55);
    set_alignment(-(150+random(150)));
    set_skill(SS_WEP_KNIFE, random(5)+40);
    set_skill(SS_DEFENCE,30);
    set_skill(SS_PARRY,30);
    set_skill(SS_AWARENESS,60);
    set_skill(SS_SNEAK,30);
    set_skill(SS_HIDE,30);
    add_prop(LIVE_I_NEVERKNOWN, 1);
    add_prop(NPC_I_NO_LOOKS, 1);

    trig_new("%w 'reveals' 'a' '_spy_orc.\n'", "react_found"); 
    trig_new("%w 'reveals' %s '_spy_orc' %s", "react_found");
    trig_new("%w 'attacks' 'you!\n'", "react_runaway");
    trig_new("%w 'are' 'no' 'longer' 'hidden.\n'", "react_runaway"); 
    trig_new("%w 'reveals' 'you!\n'", "react_found");
    trig_new("%w 'finds' 'you.\n'", "react_found");
    trig_new("%w 'finds' 'a' '_spy_orc.\n'", "react_found");
    trig_new("%w 'finds' %s '_spy_orc' %s", "react_found");

    add_notify_meet_interactive("check_attack");
}

arm_me()
{
    object wep, arm, map;

    FIX_EUID

    wep = clone_object(WEP_DIR + "orc_wep/saw_knife");
    wep->move(TO);
/*
    arm = clone_object(ROH_DIR + "horn/obj/orc_jerkin");
    arm->move(TO); 
 */
    command("wield all");
    command("wear all"); 
}

int check_attack()
{
    object enemy;

    if(TP->query_attack() != 0)
    {
        set_alarm(1.0, 0.0, "run_away");
        return 0;
    }
    return 1;
}

int react_found(string who)
{
     set_alarm(1.0, 0.0, "found_orc", who);
     return 1;
}

int found_orc(string who)
{
    object discoverer = find_player(lower_case(who)),
            map;

    if (!objectp(discoverer))
        return 0;
    if (discoverer = present(discoverer,environment()))
         discoverer->add_prop(FOUND_ORC, 1);

    if (discoverer->test_bit("Gondor", 1, 11))
    {
        discoverer->catch_msg("The sneaky long-armed orc kicks your butt!\n");
        discoverer->remve_prop(FOUND_ORC);
        run_away();
        return 0;
    }

    command("eeks");
    command("say I'm discovered!");
    tell_room(ENV(TO), "The sneaky long-armed orc drops a map.\n");
    TO->move_living("over the battlement", HIDE_OUT);
    TO->add_prop(SCARED_ORC, 1);
    map = clone_object(ROH_DIR + "horn/obj/spy_map");
    map->add_name("_helmsdeep_map");
    map->move(WALL_ROOM);
    set_alarm(1.0, 0.0, "thud");
    return 1;
}

int react_runaway(string dummy)
{
     set_alarm(2.0, 0.0, "run_away");
     return 1;
}

int run_away()
{
    command("say You can never catch me!");
    TO->move_living("over the battlement", HIDE_OUT);
    return 1;
}

int thud()
{
    tell_room(WALL_ROOM, "You hear a soft 'thud'.\n");
    return 1;
}

/* Solamnian knight prestige */
int query_knight_prestige() {return (300);}

public void
emote_hook(string emote, object actor, string adverb = 0, int cmd_attr = 0, 
    int target = 0)
{
    if (!objectp(actor) || actor->query_npc())
        return;

    if (!target)
        return;

    switch (emote)
    {
	case "tickle":
        case "poke":
        case "startle":
        case "reveal":
            react_found(actor->query_real_name());
           break;
        default:
            break;
    }
}
