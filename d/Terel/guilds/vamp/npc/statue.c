/* Main guild npc, known as The Eldest.
 *
 * Creator: Novo, June 2008
 * 
 * Modified: 
 *  Lilith, Sept 24 2008
 *   -Added flowers to list of desired things.
 *  Lilith, Nov 10, 2008
 *   -Added notification to players when their guilds prevent
 *    them from being able to join the Bloodguards.
 *  Lilith Apr 2009
 *   -Per Elder Vamps, no more conversions from Emerald Vamps.
 *    Its been 9 months since the new guild opened and if someone
 *    has not logged in and converted already, they aren't active
 *    enough to be desirable members. Let them go through the 
 *    joining process again if they really want to be Vamps.
 *
 */


#include "../guild.h"

#include <ss_types.h>
#include <wa_types.h>
#include <stdproperties.h>
#include <macros.h>
#include <std.h>

inherit "/std/monster";

#define BG_ACCEPTED_OFFER  "_bg_accepted_offer"
#define BG_WARNED_LEAVE    "_bg_warned_leave"
#define BG_BROKE_OATH      "_bg_broke_oath"

#define LIVE_I_GAVE_BLOOD  "_live_i_gave_blood"

#define SCOP "Spirit Circle of Psuchae"

#define BLOCK "/w/Genesis/specials/std/block"

#define STATUE_KILLS       (LOG_DIR+"kills")

#define VISION_MIN_FAVOR ({ 0, 999999999 })

int Invite_alarmid;

int Wants_light;
int Wants_speech;
int Wants_flowers;

string * Wants_emotes=({ });

public void hook_drainer_released(object drainee);
public void desire_things();

public void arm_me()
{
}

public void create_monster()
{
    ::create_monster();
    
    set_short("stately imposing statue");

    set_long("There is a vitality to him which denies what "+
        "your eyes first told you, that this creature "+
        "is not living, but a statue. His skin is "+
        "impossibly smooth, the texture of carved "+ 
        "and polished stone with a dark olive colour. "+
        "His hair has been parted down the center "+ 
        "and pulled back into a thick queue.\n");
    
    
    set_name("katashi");
    add_name("statue");
    
    set_race_name("human");
    
    add_adj(({ "stately", "imposing" }) );
    
    default_config_npc(300);
    
    set_base_stat(SS_OCCUP,600);
    
    
    set_all_attack_unarmed(80,80);
    set_all_hitloc_unarmed(100);

    set_skill(VAMP_SKILL_BITE,100);
    set_skill(SS_DEFENCE,100);
    set_skill(SS_PARRY,100);
    set_skill(SS_UNARM_COMBAT,100);
    set_skill(SS_BLIND_COMBAT,100);
    set_skill(SS_AWARENESS,100);
    set_skill(SS_BLOCK,100);
    
    add_prop(CONT_I_HEIGHT, 220);  
    add_prop(LIVE_I_SEE_DARK,100);
    add_prop(LIVE_I_SEE_INVIS,100);

    add_prop(LIVE_I_QUICKNESS,200);
    
    add_prop(MAGIC_I_RES_POISON,100);
    add_prop(MAGIC_I_RES_MAGIC,50);
    add_prop(MAGIC_I_RES_FIRE,50);
    add_prop(MAGIC_I_RES_AIR,50);
        
    add_prop(NPC_I_NO_FEAR,1);
    add_prop(NPC_I_NO_RUN_AWAY,1);
    add_prop(LIVE_I_NEVERKNOWN,1);
    
    add_prop(OBJ_S_WIZINFO,"This is the guild master of the vampyr and "+
    "Bloodguard guilds.\n");
    
    object shadow=clone_object(SHADOW_DIR+"occ_shadow");
    if (shadow)
    {
        int result=shadow->shadow_me(TO, "occupational", OCC_GUILD_STYLE, 
        OCC_GUILD_NAME, "");
        TO->add_blood(TO->query_max_blood()*85/100);
        TO->set_incognito(1);
    }
    object celerity=clone_object(SPELLOBJ_DIR+"celerity_obj");
    celerity->move(TO,1);
    celerity->add_evade_effect(TO);
    set_alarm(0.1,0.0,arm_me);
    
    setuid();
    seteuid(getuid());
    
    set_alarm(180.0,3600.0,desire_things);
}

public int filter_valid_vampire(object player)
{
    if (!interactive(player))
    {
        return 0;
    }
    if (player->query_wiz_level())
    {
        return 0;
    }
    if (!IS_BG(player) && !IS_VAMP(player))
    {
        return 0;
    }
    if (player->is_emerald_vampire())
    {
        return 0;
    }
    return 1;
}

public int has_stun_shadow()
{
    return 1;
}

public void penalize_active(int amount,string reason)
{
    foreach(object player :  filter(users(),filter_valid_vampire))
    {
        player->set_skill(VAMP_FAVOR,
        player->query_skill(VAMP_FAVOR)-amount);

        if (!random(10))
        {
            player->catch_msg("You suddenly feel a strong sense of " +
            "urgency. The emotion grows in strength, as is pressed " +
            "upon you - for lack of a better word you feel that " +
            "you should be " + reason + ". The feeling slowly " +
            "subsides.\n");
        }            
    }
}

public void reward_active(int amt,object cause)
{
    if (living(cause))
    {
        cause->set_skill(VAMP_FAVOR,
        cause->query_skill(VAMP_FAVOR)+3*amt);
    }
    foreach(object player :  filter(users(),filter_valid_vampire))
    {
        player->set_skill(VAMP_FAVOR,
        player->query_skill(VAMP_FAVOR)+amt);

        if (!random(10))
        {
            player->catch_msg("You suddenly feel a strong sense of " +
            "satisfaction, though the emotion is not your own.  It "+
            "appears that the presence is content with you, but for "+
            "what reason you might not know.\n");
        }            
    }
}

public int will_kill(object drainee)
{
    if (drainee->query_npc())
    {
        return 1;
    }
    if (drainee->query_prop(BG_BROKE_OATH))
    {
        return 1;
    }
    if (drainee->query_guild_name_occ()==SCOP)
    {
        return 1;
    }
    return 0;
 }


public int break_oath(string str)
{
    if (!IS_BG(TP))
    {
        return 0;
    }
    notify_fail("Break your oath?\n");

    if (!strlen(str))
    {
        return 0;
    }
        
    if (!parse_command(str,({ }),"[my] 'oath'"))
    {
        return 0;
    }

    if (!TP->query_prop(BG_WARNED_LEAVE)) 
    {
        write("Are you certain you wish to break your oath? "+
        "Such is a life or death decision.\n");
        TP->add_prop(BG_WARNED_LEAVE,1);
        return 1;
    }
    
    TP->add_prop(LIVE_O_OFFERED_BLOOD,TO);
    TP->add_prop(BG_BROKE_OATH,1);
 
    TP->set_skill(VAMP_FAVOR,0);
    TP->catch_msg("A thought passes through your mind: So be it.\n");
    set_alarm(0.1,0.0,&command("vdrink "+TP->query_real_name()));
    return 1;   
}

public void hook_offered_blood(object player)
{
    if (TO->thirst()>10 || player->is_emerald_vampire())
    {
        TO->command("vdrink "+player->query_real_name());    
    }
    else
    {
        player->catch_msg("Your offer is met with silence, as if "+
        QTNAME(TO)+" is sated at this time.\n");
    }
}

public int offer(string str)
{

    notify_fail("Offer your blood to whom?\n");
    
    if (!strlen(str))
    {
        return 0;
    }
    
    if (!CAN_SEE_IN_ROOM(TP))
    {
        return 0;
    }
    
    mixed * oblist;
    if (!parse_command(str,all_inventory(environment(TO)),
        "[my] 'myself' / 'blood' 'to' %l",oblist))
    {
        return 0;
    }
    
    if (sizeof(oblist)!=2 || oblist[1]!=TO)
    {
         return 0;
    }      
    
    if (query_attack())
    {
        TP->catch_msg(QCTNAME(TO) + " is too occupied to drink your "+
        "blood at this moment.\n");
        return 1;
    }
    
    TP->catch_msg("You offer your blood to " + QTNAME(TO) + ".\n");
    
    tell_room(environment(TO),QCTNAME(TP) + " offers " + POSS(TP) +
     " blood to " + QTNAME(TO) + ".\n",({ TP }),TP);
    
    TP->add_prop(LIVE_O_OFFERED_BLOOD,TO);

    hook_offered_blood(TP);
    return 1;
}

public void accept_offer(int response,object player)
{
    player->catch_msg("A thought passes through your mind: So be it.\n");
    if (response>0)
    {
        player->add_prop(BG_ACCEPTED_OFFER,1);
    }
    if (!TO->query_vamp_drain())
    {
        hook_drainer_released(player);
    }
}

public void remove_stun()
{
    ::remove_stun();
    set_alarm(0.1,0.0,&command("vsavage"));
}

public int valid_attack_target(object ob)
{
    if (!living(ob))
    {
        return 0;
    }
    if (IS_WIZ(ob))
    {
        return 0;
    }
    if (ob==TO)
    {
        return 0;
    }
    if (IS_VAMP(ob))
    {
        return 1;
    }
    if (IS_BG(ob))
    {
        return 1;
    }
    if (ob->query_real_name() == "isabella")
    {
        return 1;
    }
    if (ob->query_prop(LIVE_I_UNDEAD))
    {
        return 0;
    }
    if (ob->query_npc() && ob->query_humanoid())
    {
        return 1;
    }
}

public void hook_torches_lit()
{
    int torches=sizeof(filter(all_inventory(ENV(TO)),
        &->has_torch()));
    if (torches==4)
    {
        if (Wants_light)
        {
            reward_active(1,0);
        }
        Wants_light=0;
    }
    if (torches==0)
    {
        Wants_light=1;
        penalize_active(1,"tending to the sconces");
    }
}


public void hook_vase_filled()
{
    int flowers=sizeof(filter(all_inventory(ENV(TO)),
        &->test_vase()));
    if (flowers>0)
    {
        if (Wants_flowers)
        {
            command("get item from vase");
            reward_active(1,0);
        }
        Wants_flowers=0;
    }
    if (flowers==0)
    {
        Wants_flowers=1;
        penalize_active(1,"filling the vase with flowers");
    }
}

public void desire_things()
{
    hook_torches_lit();
    hook_vase_filled();
    
    if (TO->thirst()<10)
    {    
        TO->add_blood(-TO->query_max_blood()/10);
    }
    if (TO->thirst()<50 && sizeof(filter(users(),filter_valid_vampire)))
    {
        TO->add_blood(-random(TO->query_max_blood()/20));
    }
    
    if (!random(5))
    {
        Wants_speech=1;
    }

    if (!random(4))
    {
        Wants_flowers=1;
    }

    if(!random(3))
    {
        Wants_light=1;
    }

    if (!random(2))
    {
        Wants_emotes+=({ one_of_list(({ "sing","dance","laugh","kneel",
        "smile","listen","worship" })) });
    }
    
    if (!TO->query_vamp_drain() && TO->thirst()>10)
    {
        object * targets=filter(all_inventory(environment(TO)),
                &valid_attack_target());

        if (!sizeof(targets) && TO->thirst()>30)
        {
            penalize_active(1,"bringing food");
        }
        
        if (sizeof(targets))
        {
            object target=one_of_list(targets);
            target->add_prop(LIVE_O_OFFERED_BLOOD,TO);
            target->catch_msg("You feel a force on your mind, pressing "+
            "deep into your soul. Your voilition is suddenly lost - you "+
            "feel like a spectator as you watch the events unfold in front "+
            "of you.\n");
            command("vdrink "+OB_NAME(target));
        }
    }

}

public void heal_hp(int hp)
{
    if (hp<0)
    {
        hp/=3;
    }
    else
    {
        hp*=3;
    }
    ::heal_hp(hp);
}

public void react_magic(object attacker)
{
    setuid();
    seteuid(getuid());
    object paralyze=clone_object(OBJ_DIR+"statue_paralysis");
    paralyze->move(attacker,1);
    attacker->catch_msg(QCTNAME(TO) + " gazes at you menacingly, "+
    "and you feel your mind under attack.\n");
    if (!query_attack() || !present("_statue_paralysis",query_attack()))
    {
        attack_object(attacker);
    }
    
}

public mixed hit_me(int wcpen, int dt, object attacker,int attack_id, 
                        int target_hitloc)
{
    if (dt & MAGIC_DT)
    {
        set_alarm(1.0,0.0,&react_magic(attacker));
    }
    
    return ::hit_me(wcpen,dt,attacker,attack_id,target_hitloc);
}


public void check_join_guild(object player)
{
    if (player->is_emerald_vampire())
    {
        if (player->query_guild_name_race())
        {
            player->catch_msg("A thought passes through your mind: "+
            "Leave the "+player->query_guild_name_race()+" and "+
            "I will let you drink of the source.\n");
            TO->release_vamp_drainee();
        }
        else
        {
            player->catch_msg("A thought passes through your mind: "+
            "You are mine and I am yours - drink of me, and "+
            "taste the fountain of your gift.\n");
            TO->release_vamp_drainee();
        }
        return;
    }
    if (player->query_guild_not_allow_join_lay(player,"layman",
        LAY_GUILD_STYLE,LAY_GUILD_NAME))
        return;        
    if (player->query_guild_not_allow_join_occ(player,"layman",
        LAY_GUILD_STYLE,LAY_GUILD_NAME))
        return;        
    if (player->query_guild_not_allow_join_race(player,"layman",
        LAY_GUILD_STYLE,LAY_GUILD_NAME))
        return;        

    object yn_ob = clone_object(YES_NO_OBJECT);
    if (!yn_ob->get_answer(player, 
        &accept_offer(, player), 45.0))
    {
        // something failed in yn_ob...remove it.
        yn_ob->remove_object();
    }
    else
    {
        player->catch_msg("A thought passes through your mind: " +
        "I can give you a taste of what it is to be one of us. " +
        "In exchange for your loyalty to my Coven" +
        ", I will give you a sample "+
        "of immortality. Be warned - to break your oath is to "+
        "die. Do you accept or refuse?\n");
        return;
    }
}

public int find_valid_vision(string name,int level)
{
    string prefix=""+level+"_";
    if (name[0..1]==prefix)
    {
        return 1;
    }
    return 0;
}

public void check_show_vision(object target)
{
    if (TO->query_active_vision())
    {
        return;    
    }
    if (!IS_VAMP(target))
    {
        return;
    }
    int potential_lvl=-1;
    for (int i=0;i<sizeof(VISION_MIN_FAVOR);i++)
    {
        if (target->query_skill(VAMP_FAVOR)>VISION_MIN_FAVOR[i])
        {
            potential_lvl=i;
        }
    }
    if (potential_lvl>=0 && !random(50))
    {
        setuid();
        seteuid(getuid());
        potential_lvl=random(potential_lvl)+1;
        LOAD_ERR(VISION_MANAGER);
        string * visions=filter(
            (VISION_MANAGER)->get_all_visions(TO),
            &find_valid_vision(,potential_lvl));
        if (sizeof(visions))
        {
            command("vvision play "+one_of_list(visions));
        }
    }
}

public string query_eyes_colour()
{
    return "deep brown";
}

public string query_eyes_type()
{
    return "mesmerizing";
}

public int query_eyes_number()
{
    return 2;
}

public string query_hair_length()
{
    return "long";
}

public string query_hair_style()
{
    return "braided";
}

public string query_hair_colour()
{
    return "black";
}

public string return_colour_desc()
{
    return "olive";
}

public void hook_blood_removed(object drainer)
{
    if (drainer->query_attack() || TO->query_attack())
    {
        drainer->release_vamp_drainee();
        return;
    }
    check_show_vision(drainer);
}

public void hook_blood_added(object drainee)
{
    if (drainee->query_attack() || TO->query_attack())
    {
        TO->release_vamp_drainee();
        return;
    }

    if (drainee->query_npc())
    {
        return;
    }

    check_show_vision(drainee);
    drainee->add_prop(LIVE_I_GAVE_BLOOD,1);
    if (!Invite_alarmid)
    {
        Invite_alarmid=set_alarm(30.0,0.0,&check_join_guild(drainee));
    }
    if (drainee->query_hp()<drainee->query_max_hp()/5 &&
        !will_kill(drainee))
    {
        TO->release_vamp_drainee();
    }
        
}

public void create_bloodguard3(object drainee)
{
    if (!drainee)
        return;
        
    drainee->catch_msg("Your mind once more feels penetrated, as an "+
    "alien thought presses into it: Find yourself a master, and they "+
    "can enhance your gifts even further. Remember your blood debt - "+
    "you belong now to the Coven and death is your only exit. You " +
    "will feel the thirst for blood - do not neglect it.\n\n\n" +
    "The image fades, and now your duty begins.\n");
    
}

public void create_bloodguard2(object drainee)
{
    if (!drainee)
        return;
        
    drainee->catch_msg("You feel your body undergoing changes - your "+
    "senses heightened, your focus appears more crisp. In your mouth "+
    "you can feel your canines grow in length, becoming sharp fangs.\n\n");
    
    set_alarm(20.0,0.0,&create_bloodguard3(drainee));
}

public void create_bloodguard1(object drainee)
{
    if (!drainee)
    {
        return;
    }
    if (query_attack() || environment(drainee)!=environment(TO))
    {
        return;
    }
    
    object * watchers = WATCHERS(TO) - ({ drainee });
    watchers->catch_msg(QCTNAME(TO) + " bites hard into " +
    "his wrist, causing a few red drops to bleed out.  He offers them to "+
    QTNAME(drainee) + " who drinks them quickly.\n");
    
    drainee->catch_msg(QCTNAME(TO) +" bites hard into his wrist, causing "+
    "a few red drops to bleed out. You recognize the gesture and drink "+
    "them. You feel their potency as they satisfy your thirst like no "+
    "liquid ever could.\n");
    
    object shadow=clone_object(SHADOW_DIR+"lay_shadow");

    int result=
    shadow->create_bloodguard(drainee);

    if (result==1)
    {
        set_alarm(20.0,0.0,&create_bloodguard2(drainee));
    }
    else
    {
        drainee->catch_msg("Something in you repels the effects of the "+
        "blood. The blood gift is wasted.\n");
    }
}

public void hook_asked_blood(object player)
{

    if (player->thirst()>70)
    {
        add_prop(LIVE_O_OFFERED_BLOOD,player);
    }
    if (player->query_skill(VAMP_FAVOR)/30>random(100))
    {
        add_prop(LIVE_O_OFFERED_BLOOD,player);
    }
}

public void convert_vampire4(object player)
{
    player->catch_msg("\n\n\nYou heed these ancient memories, listening "+
    "to their lessons, learning that which was once the way of the "+
    "Vampyr. As the blood cools in your veins, you feel yourself "+
    "changed, yet still the same.\n\n\n");
    
}

public void convert_vampire3(object player)
{
    player->catch_msg("\n\nYour darkvision recedes, yet you feel that it "+
    "is still within your calling. Visions of the past fill your mind, "+
    "Covens across distant lands and within ancient times. You can "+
    "feel their psychic energy opening up pathways in your mind once "+
    "lost.\n\n\n");
    
    set_alarm(20.0,0.0,&convert_vampire4(player));
}

public void convert_vampire2(object player)
{
    player->catch_msg("\n\nSuch purity - you have never tasted anything "+
    "of this strength in all your immortal years. You can feel the "+
    "effects deep within you, your inner being changes.\n\n\n");
    
    set_alarm(20.0,0.0,&convert_vampire3(player));
}

public void convert_vampire1(object player)
{
    player->catch_msg("\n\nThe blood of the source burns through your "+
    "veins, molten lava coursing through your body. Its intensity "+
    "is almost unbearable.\n\n\n");
    player->command("$wail");
    
    set_alarm(20.0,0.0,&convert_vampire2(player));
}

public void convert_vampire(object drainer)
{
   drainer->release_vamp_drainee();
   if (drainer->is_emerald_vampire() || !drainer->query_guild_name_race())
    {
        object shadow=clone_object(SHADOW_DIR+"occ_shadow");

        int result=
            shadow->convert_vamp(drainer);

        if (result==1)
        {
            set_alarm(10.0,0.0,&convert_vampire1(drainer));
        }
        else
        {
            drainer->catch_msg("Something in you repels the effects of "+
            "the blood. The blood gift is wasted.\n");
        }
    }
        
}


public void hook_drainer_released(object drainee)
{
    remove_alarm(Invite_alarmid);
    Invite_alarmid=0;
    
    if (drainee->query_prop(BG_ACCEPTED_OFFER) && !query_attack())
    {
        drainee->remove_prop(BG_ACCEPTED_OFFER);
        set_alarm(5.0,0.0,&create_bloodguard1(drainee));
    }
 
    reward_active(3,drainee);

    if (drainee->query_prop(BG_BROKE_OATH))
    {
        drainee->remove_bloodguard();
    }
        
    if (will_kill(drainee))
    {
        object * watchers = WATCHERS(TO) - ({ drainee });

        drainee->catch_msg(QCTNAME(TO) + " rips open your throat, "+
        "causing you to be drained of blood.\n");
        
        watchers->catch_msg(QCTNAME(TO) + " tears into the throat of "+
        QTNAME(drainee) + ", causing " + POSS(drainee) + " blood to "+
        "spill on the floor.\n");
        drainee->set_killed_by_bite(TO);
        drainee->set_hp(0);
        drainee->do_die(TO);
    }
}

public void enter_inv(object ob,object from)
{
    ::enter_inv(ob,from);
    
    if (MASTER_OB(ob)=="/d/Emerald/std/yes_no"
         && TP->is_emerald_vampire())
    {
        if (!TP->query_prop(LIVE_I_GAVE_BLOOD))
        {
            return;
        }
        if (TP->query_guild_name_race())
        {
            return;
        }
        set_alarm(0.1,0.0,&command("yes"));
        /* Per Elder Vamps, no more conversions from Emerald Vamps.
         * Its been 9 months since the new guild opened and if someone
         * has not logged in and converted already, they aren't active
         * enough to be desirable members. Let them go through the 
         * joining process again. --Lilith April 2009.  
        set_alarm(30.0,0.0,&convert_vampire(TP));
         */
        return;
    }
}

public int is_emerald_vampire()
{
    return 1;
}

public void warning_over(object player)
{
    if (environment(player)==environment(TO) &&
        !TO->query_attack())
    {
        player->catch_msg("A thought passes through your mind: So be "+
        "it.\n");
        command("stop vdrink");
        command("kill "+OB_NAME(player));
    }
    BLOCK->do_ability("down");
}

public int special_attack(object victim)
{
    if (!(ABILITY_DIR+"bite")->query_ability_active(TO))
    {
        command("vsavage");
    }
    return 0;
}


public void give_warning(object player)
{
    if (!player)
    {
        return;
    }
    if (player->query_guild_name_occ()==SCOP &&
        environment(player)==environment(TO))
    {
        player->catch_msg("A thought passes through your mind: "+
        "You have stumbled into the wrong lair. Offer me your "+
        "blood, run away screaming, or I will remove you the "+
        "hard way.\n");
        set_alarm(25.0,0.0,&warning_over(player));
        return;
    }
    if (!IS_BG(player) && !IS_VAMP(player) && 
            player->query_stat(SS_CON)>100 &&
            environment(player)==environment(TO))
    {
        //Probably need 100 con to survive long enough to be
        //offered the gift
        player->catch_msg("A thought passes through your mind: "+
        "Have you come to offer me your blood?\n");
    }
    if (player->is_emerald_vampire() && 
            environment(player)==environment(TO))
    {
        player->catch_msg("A thought passes through your mind: "+
        "Have you come to offer me your blood?\n");
    }
}

public void init_living()
{
    ::init_living();
    add_action(offer,"offer");
    add_action(break_oath,"break");
    set_alarm(2.0,0.0,&give_warning(TP));
}

public void react_attacked()
{
    command("stop drink");
    command("vsavage");
}

public void attacked_by(object enemy)
{
    int new_attack=member_array(enemy,TO->query_enemy(-1));
    ::attacked_by(enemy);

    if (new_attack==-1)
    {
        write_file(STATUE_KILLS,ctime(time())+" " + 
        CAP(enemy->query_real_name()) + " (" + enemy->query_average_stat() +
            ") attacked.\n");
    }
    set_alarm(0.1,0.0,react_attacked);
}


public void attack_object(object enemy)
{
    int new_attack=member_array(enemy,TO->query_enemy(-1));
    ::attack_object(enemy);
    
    if (new_attack==-1)
    {
        write_file(STATUE_KILLS,ctime(time())+" " + 
        CAP(enemy->query_real_name()) + " (" + enemy->query_average_stat() +
            ") was attacked.\n");
    }
    set_alarm(0.1,0.0,react_attacked);
}


void
do_die(object killer)
{
    if (query_hp()<=0)
    {
        object *team;
        int i, sz;
        string to_write;

        if (!objectp(killer) || !living(killer))
            return 0;
            
        team = killer->query_team_others();
        team = filter(team, &operator(==) (ENV(killer)) @ environment);
        sz = sizeof(team);
        to_write = ctime(time()) + " " + CAP(killer->query_real_name())+
        " ("+killer->query_average_stat()+") killed "+TO->query_name()+
        (sizeof(team) ? " with the help of:\n" : ".");
        for (i = 0; i < sz; i++)
        {
            to_write += CAP(team[i]->query_real_name())+" ("+
            team[i]->query_average_stat()+")     ";
        }
        to_write += "\n";
        write_file(STATUE_KILLS, to_write);
        TO->stop_fight(TO->query_enemy(-1));
        TO->move_living("X",ROOM_DIR+"death_room");
    }
    ::do_die(killer);
}


/*
 * Function name: notify_death
 * Description:   Notify onlookers of my death
 * Arguments:     object killer - the object that killed me
 */
public void
notify_death(object killer)
{
    /*
     * Lets make sure there isn't a corpse, else why go to all the
     * trouble to make this NPC defeatable rather than killable?
     */
    this_object()->add_prop(LIVE_I_NO_CORPSE, 1);

    tell_room(environment(),
        QCTNAME(this_object()) + " was defeated.\n", this_object());


    if (!living(killer))
    {
        return;
    }
 
    /*
     * Give specific information about who killed this poor soul.
     */
    tell_object(killer, 
        "You defeated " + this_object()->query_the_name(killer) + ".\n");
    tell_room(environment(this_object()),  QCTNAME(killer) + 
        " defeated "+ this_object()->query_objective() + 
        ".\n", ({ this_object(), killer }));
}

public void 
emote_hook(string emote, object actor, string adverb, object *oblist,     
        int cmd_attr, int target)
{
    if (IS_BG(actor) || IS_VAMP(actor))
    {
        if (member_array(emote,Wants_emotes)>=0)
        {
            reward_active(1,actor);
            Wants_emotes-=({ emote });
        }
    }
}

public void handle_ask(int result,object actor,string name)
{
    if (!actor)
    {
        return;
    }

    if (result<=0)
    {
        actor->catch_msg("A thought passes through your mind: "+
            "So be it.\n");
        return;
    }
    if (VOTE_MANAGER->start_vote(actor,name))
    {
        actor->catch_msg("A thought passes through your mind: "+
            "So be it. Your life is on the line for this vote.\n");
    }
    else
    {
        actor->catch_msg("A thought passes through your mind: "+
            "Your request is denied at this time.\n");
    }
}


public void inform_request(object actor,string name)
{
    if (!actor)
    {
        return;
    }
    if (actor->query_vamp_age()<MINIMUM_VOTE_AGE)
    {
        return;
    }
    object yn=clone_object(OBJ_DIR+"yes_no");
    if (yn->get_answer(actor,&handle_ask(,actor,name),60.0))
    {
    actor->catch_msg("A thought passes through your mind: "+
        "Are you asking me to remove my protection from "+
        CAP(name)+"? This is a serious request.  I can "+
        "put it to a vote, where at least three of the "+
        "Coven must agree, the majority vote in favor of it, "+
        "and I hold your Covenmaster's vote in high value. "+
        "If this vote fails, I will kill you for asking. "+
        "Do you accept these terms? (Accept/Refuse)\n");
    }
}

public void
speech_hook(string verb, object actor, string adverb, object *oblist,     
        string text, int target)
{
    if (IS_BG(actor) || IS_VAMP(actor))
    {
        if (Wants_speech && target==1)
        {
            reward_active(1,actor);
            Wants_speech=0;
        }

        string name;
        if (parse_command(text,({}),"'I' [want] / [wish] / [request] "+
            " 'to' [destroy] / [remove] %w",name))
        {
            if (OCC_MANAGER->load_data(name))
            {
                set_alarm(2.0,0.0,&inform_request(actor,name));
            }
        }
    }

}

public int add_prop_live_i_stunned()
{
    return 1;
}

public int add_prop_live_i_attack_delay()
{
    return 1;
}
