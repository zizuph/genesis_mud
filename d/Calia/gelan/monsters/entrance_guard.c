
/* 
    this is a monster of the town Gelan
    An entrance guard, who is named Gamalus by the head_guard code,
    acts as a gatekeeper of the town and is also a quest npc for the
    polymorph quest. There must be only one entrance guard, Gamalus!!!

    coder(s):   Maniac and Merlin 

    history: 
         18/2/2003 toughened him up again (damned rising stats)  Jaacar
        24/2/2001 stats and see invisibility ability revised  Maniac 
         8/9/2000 mana cost for spells revised                Maniac 
        13/2/2000 added remark_invis and cease_combat_spell   Maniac 
        17/7/99   improved his SS_DIS to enable more attacks  Maniac 
        18/4/98   ask bug fixed
        27/2/98   helps with attacks in his environment       Maniac 
         7/11/96  typos                                       Maniac 
        21/9/95   Toughened him up, he's a quest npc          Maniac 
        19/9/95   made a quest npc for the polymorph quest    Maniac 
        26/7/95   major revision of old file 
                  (added fire and heal spells)                Maniac 

    armour:     magic cloak 

    special:    decides who enters the town (really made in the add_exit!)

*/

#include "monster.h"
#include POLYMORPH_QUEST
inherit STD_GUARD;
#include <ss_types.h>
#include <stdproperties.h>
#include <filter_funs.h>
#include <macros.h>

#define PQ_MIN_AVG_STAT 70

int cease_combat_alarm = 0; 

/*
 * Function name: arm_me
 * Description:   clones the magic cloak and forces Calmas to wear it
 * Arguments:     none
 * Returns:       none
 */

void
arm_me()
{
    object armour;

    seteuid(getuid(this_object()));

    armour = clone_object(GELAN_ARMOURS + "magic_cloak_guard_eye");
    armour->move(this_object());
    command("wear cloak");
}


/*
 * Function:      remark_invis
 * Description:   Remark on invisible players, who Gamalus can 
 *                see but most people won't be able to. 
 */ 
void
remark_invis(object living)
{
    if (objectp(living) && 
        present(living, environment())) {
        switch (random(4)) { 
            case 0 : 
                command("poke " + OB_NAME(living));
                break; 
            case 1 : 
                command("grumble " + OB_NAME(living)); 
                break; 
            case 2 : 
                command("peer " + OB_NAME(living)); 
                break; 
            default : 
                command("say " + living->query_The_name(this_object()) + 
                        ", it's rude to hang around invisible."); 
                break; 
        }
    } 
}


/* Says he has a task for powerful warrior and comments
   on invisible players when it's relevant. */
string
special_chat()
{
    object *pl;
    int i, p;
    string r; 

    pl = FILTER_PLAYERS(all_inventory(environment(this_object())));

    for (i = 0; i < sizeof(pl); i++) {
        p = pl[i]->query_prop(OBJ_I_INVIS); 
        if (p > 0 && p <= query_prop(LIVE_I_SEE_INVIS)) 
            set_alarm(itof(random(3) + 3), 0.0, &remark_invis(pl[i]));
 
        if (!stringp(r) &&
            (pl[i]->query_average_stat() >= PQ_MIN_AVG_STAT) &&
            (!pl[i]->test_bit(PQ_DOM, PQ_GROUP, PQ_BIT)))
            r = "I have a dangerous task for a powerful warrior."; 
    }

    if (stringp(r))
        return r;

    return "Hmm."; 
}



/*
 * Function name: create_monster
 * Description:   creates the guard
 * Arguments:     none
 * Returns:       none
 */

void
create_monster()
{
    /* descritpion */

    set_race_name("guard");

    set_adj(({"wise", "magical"}));

    set_long("He looks very wise and has an aura of powerful magic. " +
           "The white eye on his cloak identifies him an entrance " +
           "guard. He decides which people may enter Gelan and which " +
           "may not. You'd better be polite with him.\n");

    set_gender(G_MALE); 

    set_alignment(1000); 

    /* stats and skills */ 

    set_base_stat(SS_STR, 360); 
    set_base_stat(SS_DEX, 330); 
    set_base_stat(SS_INT, 200); 
    set_base_stat(SS_CON, 300); 
    set_base_stat(SS_WIS, 200); 
    set_base_stat(SS_DIS, 290); 

    set_skill(SS_SPELLCRAFT, 90);           /* it's a magical guard */
    set_skill(SS_DEFENCE, 100);
    set_skill(SS_AWARENESS, 100);

    set_hp(query_max_hp());	/* starts with full strength */
    set_mana(query_max_mana()); 

    /* properties */ 

    add_prop(CONT_I_WEIGHT, 55000); 
    add_prop(CONT_I_VOLUME, 55000); 
    add_prop(CONT_I_MAX_WEIGHT, 120000); 
    add_prop(CONT_I_MAX_VOLUME, 120000); 
    add_prop(LIVE_I_SEE_DARK, 5); 
    add_prop(LIVE_I_SEE_INVIS, 5); 
    add_prop(NPC_I_NO_RUN_AWAY, 1); 

    /* actions */
    set_act_time(20);
    add_act("smile");
    add_act("bow");
    add_act("twiddle");

    set_chat_time(20);
    add_chat(VBFC_ME("special_chat"));

    set_cchat_time(2);
    add_cchat("You will pay for your actions!");
    add_cchat("Deem yourself a match for my magic?");
    add_cchat("You are foolish indeed to challenge me.");
    add_cchat("Burn in hell as you deserve.");

    add_ask(({"task", "quest", "dangerous task", "for task", "for quest", 
              "for dangerous task", "about task", "about dangerous task",
              "about quest"}), 
            "@@task_response", 1);
}



/* Respond to request for task */
string
task_response()
{
    object tp = this_player();
    object c;

    if (!tp)
        return "";

    if (objectp(query_attack()))
        return "";

    if (tp->test_bit(PQ_DOM, PQ_GROUP, PQ_BIT)) 
         return "ponder wasting one's time.";

    if (tp->query_average_stat() < PQ_MIN_AVG_STAT) 
        return ("say I believe that the task I have is too dangerous for any " +
                "as inexperienced as you. It would be too much of a risk " +
                "to your young life.");

    if (present(CORPSE_NAME, tp)) 
        return ("say I see that you have the demon's corpse on you! " +
                "Please <report> to me what happened.");

    if (tp->query_prop(LIVE_I_FOUGHT_CALIA_PQ_DEMON)) 
        return ("say I see by your ragged appearance that you have " +
                "already fought the danger " +
                "that faces us on the Calian moors. You may " +
                "<report> to me about this if you wish.");

    return ("say Rumours from some folk who have ventured into the " +
            "wilderness lead us to believe " +
            "that there is a great peril on the Calian moors. We know " +
            "little about the nature of this threat, but we believe that " +
            "kroug has released some sort of demonic creature on us, " +
            "something devious and very powerful. I need the services of " +
            "an experienced warrior such as yourself to investigate the " +
            "threat and <report> back to me. I do not at this stage expect " +
            "you to try to kill it, only to bring back information.");
}



/* Player can report back after certain points in the quest */
int
report()
{
    object tp = this_player();
    object c;

    if (!tp)
        return 0;

    if (objectp(query_attack())) {
         notify_fail("Not now!\n");
         return 0;
    }

    if (tp->test_bit(PQ_DOM, PQ_GROUP, PQ_BIT)) {
         command("ponder wasting one's time.");
         return 1;
    }

    if (c = present(CORPSE_NAME, tp)) { 
        tell_object(tp, "You tell " + query_the_name(tp) + 
                    " of the death of the polymorph demon.\n");
        tell_room(environment(this_object()), QCTNAME(tp) + " tells " +
                  QTNAME(this_object()) + " of the death of the " +
                  "polymorph demon.\n", tp);

        command("say It is excellent that the creature is dead, " +
                "Calia must be protected from such terrors.");

        if (c->query_valid_slayer(tp->query_real_name())) {
            if (tp->test_bit(PQ_DOM, PQ_GROUP, PQ_BIT)) {
                command("say I see you have helped us in a previous " +
                        "incarnation of the demon, I an afraid I cannot " +
                        "reward you again.");
                command("emote makes a magical gesture with his left hand.");
                c->decompose();
                tp->remove_prop(LIVE_I_FOUGHT_CALIA_PQ_DEMON);
                return 1;
            }
            else {
                command("say You have done very well. I will reward " +
                        "you handsomely!");
                command("emote makes a magical gesture with his right " +
                        "hand.");
                seteuid(getuid());
                tp->set_bit(PQ_GROUP, PQ_BIT); 
                tp->add_exp(PQ_XP);
                tell_object(tp, "A great feeling of achievement and goodness " +
                            "rushes through you!\nYou feel more experienced!\n");
                tp->command("save");
                c->decompose();
                tp->remove_prop(LIVE_I_FOUGHT_CALIA_PQ_DEMON);
                log_file("polymorph_quest", tp->query_name() + " " +
                         ctime(time()) + ".\n");
                return 1;
            }
        }
        else {
            command("say You were not instrumental in " +
                    "the creature's death though, so I " +
                    "cannot reward you, other than to say " +
                    "thank you for bringing me the news."); 
            command("emote makes a magical gesture with his left hand.");
            c->decompose();
            tp->remove_prop(LIVE_I_FOUGHT_CALIA_PQ_DEMON);
            return 1;
       }
   }

   if (tp->query_prop(LIVE_I_FOUGHT_CALIA_PQ_DEMON)) {
        tell_object(tp, "You tell " + query_the_name(tp) + 
                    " about the polymorph demon.\n");
        tell_room(environment(this_object()), QCTNAME(tp) + " tells " +
                  QTNAME(this_object()) + " about the " +
                  "polymorph demon.\n", tp);
        command("emote looks worried.");
        command("say This creature is indeed fearsome and dangerous, it " +
            "may prove very difficult to kill. I believe you will " +
            "need to ask the advice of someone far wiser " +
            "than me if you want to discover a way of killing it. Return " +
            "and <report> to me again should you manage to slay the " +
            "demon, carrying with you evidence of the creature's death. " +
            "I wish you the best of luck.");
        return 1;
    }

    tell_object(tp, "You tell " + query_the_name(this_object()) + 
                " about nothing in particular.\n");
    tell_room(environment(this_object()), QCTNAME(tp) + " tells " +
              QTNAME(this_object()) + " about nothing " +
              "in particular.\n", tp);
    command("yawn");
    return 1;
}


void
init_living()
{
    ::init_living();
    add_action(report, "report");
}


/*
 * Function:    cease_combat_spell
 * Desciption:  stops all Gelan npcs in the room from fighting. 
 */ 
void
cease_combat_spell()
{
    object *inv = all_inventory(environment()); 
    object *enemies, curr; 
    int i; 

    if (query_mana() < 65) {
        command("emote sighs wearily."); 
        return; 
    } 

    add_mana(-65); 

    command("emote concentrates and snaps his fingers."); 

    if (!random(10)) {
        /* spell fails */ 
        command("emote steams slightly but nothing else happens."); 
        command("swear"); 
        cease_combat_alarm = 
            set_alarm(itof(random(3) + 3), 0.0, cease_combat_spell); 
        return; 
    }

    for (i = 0; i < sizeof(inv); i++) {
        curr = inv[i]; 
        if (curr->query_calia_gelan_npc() &&
            sizeof(enemies = curr->query_enemy(-1)) && 
            sizeof(enemies = 
                filter(enemies, &->query_calia_gelan_npc()))) {
            tell_room(environment(), QCTNAME(curr) + " looks like " + 
                curr->query_pronoun() + " has had a bucket of ice " +
                "cold water thrown over " + curr->query_objective() +
                ".\n", curr); 
            inv[i]->stop_fight(enemies); 
        } 
    } 
    cease_combat_alarm = 0; 
}


/*
 * Function name: help_other
 * Description:   react on help call from master guard (shadow original
                  function)
 * Arguments:     the nearest meeting room to the attacked guard,
                  the room the guard is attacked in,
                  the object pointer to the attacker
 * Returns:       none
 */
void
help_other(string room, object attacker)
{
    if (present(attacker, environment(this_object()))) {
        if (attacker->query_calia_gelan_npc()) {
            if (cease_combat_alarm)
                return; 
            cease_combat_alarm = 
                set_alarm(itof(random(3) + 3), 0.0, cease_combat_spell);
        }  
        else 
            command("kill " + OB_NAME(attacker)); 
    }
}


/* shouldn't go anywhere when an enemy leaves */
void
notify_enemy_gone(object attacked)
{
}


/* He's got special damage resistance */
void
heal_hp(int hp)
{
    if (hp < 0)
       ::heal_hp(hp / 4);
    else
       ::heal_hp(hp);
}


int
fire_spell(object me, object enemy)
{
    object fire;

    if (environment(enemy)->query_prop(ROOM_M_NO_MAGIC_ATTACK) ||
        enemy->query_prop(OBJ_M_NO_MAGIC) ||
        enemy->query_prop(OBJ_M_NO_MAGIC_ATTACK))    {
        tell_object(me, "You realise that your spell will have no effect " +
                    "on " + enemy->query_the_name(me) + ".\n"); 
        tell_room(environment(me), QCTNAME(me) + " seems to look rather " +
                "crestfallen about something.\n", me);
        return 0;
    }

    if (me->query_mana() < 65) {
        tell_object(me, "Uh oh, not enough mana to cast fire!\n");
        tell_room(environment(me), QCTNAME(me) + " looks mentally " +
                  "exhausted as he tries to summon the strength " + 
                  "to spellcast.\n", me);
      return 0;
    }

    if (!(random(10)))  {
        tell_object(me, "Your spell fails.\n"); 
        tell_room(environment(me), "Some smoke rises from " + QTNAME(me) +
                  "'s hands and then suddenly fizzles out.\n", me);   
        me->add_mana(-65);
        return 1;
    }

    if (fire = present("_gelan_magic_flame", enemy))  {
        fire->increase_strength();
        tell_object(me, "You increase the strength of the flames around " +
                    enemy->query_the_name(this_object()) + ".\n");
        tell_object(enemy, query_The_name(enemy) + " points in your direction " +
                    "and suddenly the flames grow even stronger!\n");
        tell_room(environment(me), QCTNAME(me) + " points in " + QTNAME(enemy)+
                  "'s direction and suddenly the flames around " +
                  enemy->query_objective() + " grow even stronger!\n",
                  ({me, enemy}) );
    } 
    else {
        fire = clone_object(GELAN_OBJECTS + "flame");
        tell_object(me, "You cast a fire spell on " + 
                  enemy->query_the_name(this_object()) + ".\n");
        tell_object(enemy, query_The_name(enemy) + "'s hands suddenly " +
                  "ignite with magical blue flames, which leap your " +
                  "direction!\n"); 
        tell_room(environment(me), QCTNAME(me) + "'s hands suddenly " +
                  "ignite with magical blue flames, which leap in the " +
                  "direction of " + QTNAME(enemy) + "!\n", 
                  ({me, enemy}) );

        fire->move(enemy);
    }
    me->add_mana(-65);
    return 1; 
}


int
heal_spell(object me)
{
    if (me->query_mana() < 65) {
        tell_object(me, "Uh oh, not enough mana to cast heal!\n");
        tell_room(environment(me), QCTNAME(me) + " looks mentally " +
              "exhausted as he tries to summon the strength " + 
              "to spellcast.\n", me);
        return 0;
    }

    if (!(random(10)))  {
        tell_object(me, "Your spell fails.\n"); 
        tell_room(environment(me), "Some smoke rises from " + QTNAME(me) +
              "'s hands and then suddenly fizzles out.\n", me);   
        me->add_mana(-65);
        return 1;
    }

    tell_object(me, "You heal yourself.\n"); 
    tell_room(environment(me), QCTNAME(me) + " makes an arcane gesture, "
        + "and his whole body seems to glow for a short while.\n", me); 
    me->heal_hp(300 + random(250));
    me->add_mana(-65);

    return 1;
}


/* 
 * Function name: special_attack
 * Description:   Called from the external combat object's heart_beat
 *                routine. By redefining this, monsters can easily attack
 *                with spells or take special actions when engaged
 *                in combat. Like this guy, who has a few spells up his
 *                sleeve. 
 * Arguments:     victim (the one we are fighting right now)
 * Returns:       0 - if we want the round to continue
 *                1 - if we are done with this round
 * Note:          By always returning 1 the mobile is unable
 *                to do an ordinary attack.
 */
int
special_attack(object enemy)
{
    object me;

    if (enemy->query_calia_gelan_npc()) {
        set_alarm(0.0, 0.0, cease_combat_spell); 
        return 1; 
    } 

    me = this_object();

    if (me->query_hp() < (me->query_max_hp() / 3))
        return heal_spell(me);

    if (random(5))
        return 0;

    return fire_spell(me, enemy);
}
