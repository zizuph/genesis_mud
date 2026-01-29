/*
 *  /d/Gondor/arnor/weapons/skull_club.c
 *  wielded by /d/Gondor/arnor/npc/massive_troll.c
 *  Coded by Tigerlily, July 2005
 *      Enhanced by Altrus, August 2005
 *  This is the weapon used by the massive mountain
 *     troll.  Due to the troll's size and difficulty
 *     in killing him, this is a larger weapon
 *     and it also has a bit of additional boost in
 *     pen due to the 'fangs' of the goblin head.
 *  Modifications log:
 *     Added a fix to keep the stats from upping when
 *         player goes ld and logs back in
 *         or player is disarmed
 *         Tigerlily, April 16, 2006
 *
 *     Fixed typo. Fixed MAGIC_AM_ID_INFO.
 *     Modified description a bit, was a bit brief before.
 *         Toby, March 01, 2007
 * 
 *     Fixed typo socktes, Toby, 2008.06.18
 *        
 *  Removed the failsafe unwield and stat reset from the leave_env
 *  function, for it's not necessary and caused the bonus to be 
 *  removed when a player holds two of this weapon. Additionally,
 *  replaced the this_player() calls in the unwield function with 
 *  query_wielded() because it's not guaranteed to be this_player()
 *  that causes the unwield.
 *  The try_hit function now returns 0 when the special fires, preventing
 *  the player from getting two hits in the same round.
 *     Eowul, Oktober 11th, 2008
 *
 *  Fixed a bug with "me->tell_watcher" only me was ignored, resulting in
 *  a double set of messages for the enemy.
 *     Znagsnuf, May 5th 2017
 */ 

inherit "/std/weapon";
inherit "/lib/keep.c";
#include "/sys/macros.h"
#include "/sys/stdproperties.h"
#include "/sys/wa_types.h"
#include "/sys/ss_types.h"
#include "/sys/formulas.h"
#include "/d/Gondor/defs.h"

#define MIN_SKILL 80
#define SPD 25
#define GOT_ADD "_got_skull_club_extra"

void
create_weapon()
{
    set_name("club");
    set_short("bloody skull club");
    set_adj( ({"bloody", "skull"}) );
    set_long("This large club has a bloody skull from a monster possibly " 
           + "a goblin. The eye sockets, hollow and utter black, seems to "
           + "be staring at you. The fangs of the skull function as spikes "
           + "to rip deeply into opponents in battle. The long handle is "
           + "made of a gnarled dark root of what must have been a very "
           + "large tree.\n");
    add_prop(OBJ_I_WEIGHT, 5800);
    add_prop(OBJ_M_NO_BUY, 1);
    add_prop(OBJ_I_IS_MAGIC_WEAPON, 1);
    add_prop(MAGIC_AM_ID_INFO, ({"This club appears to somehow be very "
                               + "special. ",1,
                                 "Its effectiveness seems to be dependant "
                               + "on the skill of the user. ", 25,
                                 "It works best in the hands of a user "
                               + "rumoured to have skills of a veteran. ", 55,
                                 "\n", 1 }) );
    set_default_weapon(30, 30, W_CLUB, W_BLUDGEON | W_IMPALE, W_RIGHT, 0);
    query_keepable();
    set_wf(this_object());
}

public mixed
wield(object obj)
{
    object tp = objectp(query_wielded()) ? query_wielded() : this_player();
    
    int mana = tp->query_mana();

/* don't add extra again */
    if(!tp->query_prop(GOT_ADD) && tp->query_skill(SS_WEP_CLUB) >= MIN_SKILL)
    {
        obj->set_default_weapon(50, 50, W_CLUB, W_BLUDGEON | W_IMPALE, 
                                W_RIGHT, 0);
        tp->set_stat_extra(0, (TP->query_stat_extra(SS_STR) + 10));
        tp->set_stat_extra(1, (TP->query_stat_extra(SS_DEX) + 10));
        tp->add_prop(LIVE_I_QUICKNESS, TP->query_prop(LIVE_I_QUICKNESS) + SPD);
        tp->set_mana(mana-(mana/2));
        tp->add_prop(GOT_ADD, 1);
        tp->catch_tell("As you grasp the club, the eyes of the skull " +
               "momentarily glow, eminating a dim red light. You feel " +
               "dizzy, but strangely empowered!\n");
        tell_room(environment(tp), 
            QCTNAME(tp) + " grasps the bloody skull club, looking " +
            "somewhat dazed.\n", ({ tp }));
        tp->update_weapon(obj);
        return 1;
    }
    
    // Give normal wield message
    return 0;
}

public mixed
unwield(object obj)
{
    object tp = objectp(query_wielded()) ? query_wielded() : this_player();

    if(tp->query_prop(GOT_ADD))
    {
        obj->set_default_weapon(30, 30, W_CLUB, W_BLUDGEON | W_IMPALE, 
                                W_RIGHT, 0);
        tp->set_stat_extra(0, (tp->query_stat_extra(SS_STR) - 10));
        tp->set_stat_extra(1, (tp->query_stat_extra(SS_DEX) - 10));
        tp->add_prop(LIVE_I_QUICKNESS, tp->query_prop(LIVE_I_QUICKNESS) - SPD);
        tp->remove_prop(GOT_ADD);
        tp->catch_tell("The bloodlust leaves you as you release the bloody " +
            "skull club.\n");
        tell_room(environment(tp), 
            QCTNAME(tp) + " releases the bloody skull club, looking " +
            "somewhat diminished.\n", ({ tp }));
        tp->update_weapon(obj);
        return 1;
    }
/* else */
    return 0;
}

void pulp_corpse(object person)
{
    object body = present("corpse", environment(person));
    body->remove_object();
    
    setuid();
    seteuid(getuid());
    clone_object("/d/Gondor/arnor/obj/pulped_corpse")->move(ENV(person));
}

int try_hit(object enemy)
{
    int skill, stat, skill_e, stat_e, pen, perf, pdam;
    mixed *hitresult;
    object me, enmy;
    string text, ptext;

    me = query_wielded();
    enmy = me->query_enemy();
    skill = me->query_skill(SS_WEP_CLUB);
    stat = me->query_stat(SS_STR);
    skill_e = enemy->query_skill(SS_DEFENCE);
    stat_e = enemy->query_stat(SS_DEX);
    
    if(!me->query_prop(GOT_ADD))  //Special hit wont work unless you have the skill
         return 1;
    // We want to cap the stat at around 100 if the stats get too
    // high (above 110)
    if (stat > 110)
        stat = 90 + random(20);
    if (stat_e > 110)
        stat_e = 90 + random(20);

    if ((random(100) < (skill/2)) 
       && (random(skill+stat) > random(skill_e+stat_e)))
    {
        pen = F_PENMOD(40+random(stat/4), skill);
        hitresult = enemy->hit_me(pen, W_BLUDGEON, me, -1);
        perf = hitresult[2] * 100 / pen;
        ptext = "weakly hitting";
        if (perf > 15)
            ptext = "buffet";
        if (perf > 30)
            ptext = "bludgeon";
        if (perf > 45)
            ptext = "hammer";
        if (perf > 60)
            ptext = "pummel";
        if (perf > 75)
            ptext = "pummel";
        if (perf > 90)
            ptext = "pulverize";

        if (enemy->query_hp() <= 0)
        {
            enemy->command("scream");
            me->catch_msg("You run at " + QTNAME(enemy) + ", swinging your " + 
                short() + " with wild abandon!\nYou bring the weapon down on " 
                + HIM_HER(enemy) + " again and again in a brutal series of " +
                "blows!\n" + CAP(HE_SHE(enemy)) + " seems to see death " +
                "coming.\n\nYou beat " + QTNAME(enemy) + " into an " +
                "unrecognizable pulp, showering yourself with blood " +
                "and gore!\n");
            enemy->catch_msg(QCTNAME(me) + " comes running at you, swinging " + 
                HIS_HER(me) + " " + short() + " with wild abandon!\n" + 
                HE_SHE(me) + " brings the weapon down on you again and again " 
                + "in a brutal series blows!\n\nYou can see your death "
                + "coming.\n\nYou are beat to a bloody pulp!\n");
            me->tell_watcher(QCTNAME(me) + " comes running at " + 
                QTNAME(enemy) + ", swinging " + HIS_HER(me) + " " + short() + 
                " with wild abandon!\n" + HE_SHE(me) + "brings the weapon " +
                "down on " + HIM_HER(enemy) + " again and again in a brutal " +
                "series of blows!\n" + CAP(HE_SHE(enemy)) + " seems to see "
                + "death coming.\n\n" + QCTNAME(me) + " beats " 
                + QTNAME(enemy) + " into an unrecognizable pulp, showering " 
                + HIM_HER(me) + "self with blood and gore!\n", 
                ({ me, enemy }));
            enemy->do_die(me);
            pulp_corpse(me);
            return 0;
        }

        me->catch_msg("Screaming like some mad beast, you lay into " + 
            QTNAME(enemy) + "!\nSwinging wildly, you " + ptext + " " + 
            HIM_HER(enemy) + " with your " + short() + "!\n");
        enemy->catch_msg("Screaming like some mad beast, " + QCTNAME(me) + 
            " lays into you!\nSwinging wildly, " + HE_SHE(me) + " " + 
            ptext + "s you with " + HIS_HER(me) + " " + short() + "!\n");
        me->tell_watcher("Screaming like some mad beast, " + QCTNAME(me) + 
            " lays into " + QTNAME(enemy) +"!\nSwinging wildly, " + 
            HE_SHE(me) + " " + ptext + "s " + QTNAME(enemy) + " with " + 
            HIS_HER(me) + " " + short() + "!\n", ({ me, enemy }));
            
        // If they use the special, they don't get to use the weapon this round
        return 0;
    }
    return 1; /* Try hit */
}

string
query_recover()
{
    return MASTER + ":" + query_wep_recover() + query_keep_recover();
}

void
init_recover(string arg)
{
    init_wep_recover(arg);
    init_keep_recover(arg);
}

