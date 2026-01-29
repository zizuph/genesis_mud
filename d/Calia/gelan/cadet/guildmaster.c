
/* 
   ~Calia/gelan/cadet/guildmaster.c 

   The guildmaster of the Cadets of Gelan. 

   Coded by Maniac@Genesis, March 1997. 

   Revised by Maniac December 1997 

   History: 
   98/99/00/01    blah blah blah blah etc. etc. didn't 
                  keep history but a lot of changes          Maniac 
   10/6/01        dealt with broken shoes and sneaking       Maniac 
   6/8/01         fixed warning bug                          Maniac 
  25/11/01        updated enemy handling                     Maniac 
   7/5/02         Some can ask for list of cadets in realms  Maniac 
  19/5/02         Added pie for people who annoy him         Maniac
*/ 

#pragma save_binary

#include "cadet.h" 
#include "../gelan.h" 
#include <wa_types.h> 
#include <macros.h> 
#include <tasks.h> 
#include <options.h> 
#include <files.h> 
#include <cmdparse.h> 
#include <composite.h>

inherit STD_AIDED; 
inherit "/d/Calia/std/remember"; 

#include <ss_types.h>
#include <macros.h>
#include <stdproperties.h>
#include <language.h>
#include <formulas.h>

#define MIN_AVG_FOR_ENEMY 80
#define MIN_RACK_POINTS_FOR_CLIST 12000

#undef DEBUG_GUILDMASTER

#define OATH0 ("I swear upon my honour not to attack " + \
               "any citizen of Gelan, guard of Gelan or Cadet " + \
               "of Gelan throughout the time that I am a member " + \
               "of the Cadets of Gelan guild unless the character " + \
               "who I wish to attack has indicated clearly that he " + \
               "or she is willing to fight me")

#define OATH1 ("I swear upon my honour to treat with respect " + \
               "the Cadets of Gelan guild, the town of " + \
               "Gelan and the inhabitants of Gelan throughout " + \
               "the time that I am a member of the Cadets of Gelan " + \
               "guild")

#define OATH2 ("I swear upon my honour to treat with respect " + \
               "the Cadets of Gelan guild, the town of " + \
               "Gelan and the inhabitants of Gelan throughout " + \
               "the time that I am in possession of a graduation " + \
               "ring issued to me by the Cadets of Gelan guild")


/* 1 is slightly annoying, 2 is annoying, 3 is very annoying, 
   4 is infuriating, 5 is an instant attack */ 
mapping annoying_emotes = 
        ([ "slap" : 4, 
           "sneer" : 2, 
           "kick" : 4, 
           "spit" : 5, 
           "cimit" : 1, 
           "cfist" : 1, 
           "fondle" : 1, 
           "finger" : 3, 
           "french" : 2, 
           "caress" : 1, 
           "dance" : 1, 
           "cuddle" : 1, 
           "lick" : 1, 
           "knee" : 4, 
           "kiss" : 1, 
           "nibble" : 1, 
           "snarl" : 2, 
           "startle" : 1, 
           "spank" : 2, 
           "snuggle" : 1, 
           "scold" : 2, ]); 

string *flustered_emotes = ({ "cuddle", "caress", 
                              "kiss", "nibble", "lick", 
                              "fondle", "snuggle", "french" }); 

string *block_directions = ({ }); 
string *greeted = ({ }); 

/* He gets flustered before getting annoyed 
   with females for certain emotes */ 
mapping flustered = ([ ]); 

/* Annoyance level towards particular people */ 
mapping annoyance = ([ ]); 

string *warned = ({ }); 

int round_count; 
object pie; 


void 
create_monster() 
{
   if (!IS_CLONE) 
        return; 
   set_name(lower_case(GC_GM_NAME)); 
    set_living_name(lower_case(GC_GM_NAME));
   add_name("guildmaster"); 
   set_race_name("dwarf"); 
   set_adj(({"ancient", "powerful"})); 
   set_title("the Sergeant of the Cadets of Gelan"); 
   set_long(
      GC_GM_NAME + " is the founder and Sergeant of the Cadets of Gelan. " + 
      "Formerly a warrior in the army of Hucker the Warlord, " + 
      "he has long since retired and spends his time schooling " + 
      "youngsters who seek careers as fighters. Since a warrior's life " + 
      "is a hard one, or at least it was in his day, he specialises in " + 
      "bringing out the tough, clear-thinking warrior in his recruits. " + 
      "Cadets may <ask xorfin shoes> if they have lost or broken their " + 
      "guild item, or <ask xorfin notebook> if they want to take notes. " + 
      "Graduates who have lost their ring may <ask xorfin ring> to get " + 
      "it back. If you <donate> an item to the cadet racks he will " + 
      "see that it gets there provided it's appropriate, as well as remember " + 
      "your total contribution. Graduates and people who have donated " + 
      "much to the racks may <ask xorfin cadets> to find out which " +
      "cadets are in the realms.\n" + 
      "He has an old battle scar running down his right cheek.\n"); 

   set_stats(({182, 137, 182, 125, 125, 175 })); 
   set_hp(query_max_hp()); 
   set_skill(SS_WEP_AXE, 100); 
   set_skill(SS_WEP_SWORD, 100); 
   set_skill(SS_WEP_KNIFE, 100); 
   set_skill(SS_WEP_CLUB, 100); 
   set_skill(SS_WEP_POLEARM, 100); 
   set_skill(SS_PARRY, 100); 
   set_skill(SS_UNARM_COMBAT, 100); 
   set_skill(SS_DEFENCE, 100); 
   set_skill(SS_AWARENESS, 60); 
   set_skill(SS_BLIND_COMBAT, 100); 
   add_prop(NPC_I_NO_RUN_AWAY, 1); 
   add_prop(NPC_I_NO_LOOKS, 1); 
   add_prop(CONT_I_HEIGHT, 130); 
   add_prop(CONT_I_WEIGHT, 70000); 
   set_alignment(0); 
   set_gender(G_MALE); 

   add_ask(({ "shoes", "boots", "combat boots" }), 
           VBFC_ME("reply_shoes")); 
   add_ask("notebook", VBFC_ME("reply_notebook")); 
   add_ask("ring", VBFC_ME("reply_ring")); 
   add_ask("cadets", VBFC_ME("reply_cadets")); 
   round_count = 0; 
   enable_reset(); 
   pie = clone_object(GELAN_OBJECTS + "custard_pie"); 
   pie->move(this_object()); 
}


void 
reset_monster() 
{ 
    ::reset_monster(); 
    flustered = ([ ]); 
    annoyance = ([ ]); 
    greeted = ({ }); 
    warned = ({ }); 
    if (!objectp(pie)) 
    { 
        pie = clone_object(GELAN_OBJECTS + "custard_pie"); 
        pie->move(this_object()); 
    } 
} 


void
arm_me()
{
    clone_object(GC_SHOES)->move(this_object()); 
    clone_object(GC_GM_UNIFORM)->move(this_object()); 
    clone_object(GC_GM_WEAPON)->move(this_object()); 
    command("$wear all"); 
    command("$wield weapon"); 
    add_cmdsoul(GC_SOUL); 
    update_hooks(); 
}


public int 
query_option(int opt) 
{
    if (opt == OPT_UNARMED_OFF) 
        return 1; 

    return ::query_option(opt); 
}


/* 
 * Function:     heal_hp 
 * Description:  Heals the health, here it checks 
 *               that the cadet guildmaster can 
 *               start dodging if in serious danger. 
 */ 
void 
heal_hp(int hp) 
{
    ::heal_hp(hp); 
    // if (query_hp() < query_max_hp() / 2)
}


/* 
 * Function:    notify_enemy_gone 
 * Description: Called when the enemy left the the room. Guard 
 *              returns his/her post. 
 */ 
void 
notify_enemy_gone(object attacked) 
{
    if (objectp(attacked)) { 
       //  set_alarm(itof(random(3) + 2), 0.0, &chase_enemy
    } 
}


void 
notify_you_killed_me(object victim)
{
    log_file("cadet", ctime(time()) + ": Xorfin kills " + 
             victim->query_real_name() + ".\n"); 
}


/* 
 * Function:     check_pie 
 * Description:  If Xorfin has a custard pie on him, he'll 
 *               throw it at the specified target. 
 * Arguments:    object targ - the target. 
 */ 
private void 
check_pie(object targ) 
{ 
    if (objectp(pie) && objectp(present(pie, this_object()))) 
    { 
        command("throw pie at " + OB_NAME(targ)); 
    } 
} 


void 
damage_attack(object victim)
{
    string jump; 
    int relh; 

    relh = (query_prop(CONT_I_HEIGHT) * 100) / 
           victim->query_prop(CONT_I_HEIGHT); 

    if (relh <= 65) 
        jump = " leaps very high and"; 
    else if (relh >= 180)
        jump = ""; 
    else
        jump = " jumps and"; 

    if (resolve_task(TASK_ROUTINE, ({ TS_DIS, TS_DEX }), 
                     victim, ({ TS_DIS, TS_DEX })) < 0) { 
        tell_watcher(QCTNAME(this_object()) + jump + " misses " + 
                  QTNAME(victim) + "'s head " + 
                  "with a vicious kick!\n", victim);  
        tell_object(victim, query_The_name(victim) + jump +  
                    " misses your head with a vicious kick!\n"); 
        return; 
    } 

    victim->hit_me(F_PENMOD(80, 100), 
                   W_BLUDGEON, this_object(), -1); 
    tell_watcher(QCTNAME(this_object()) + jump + " gives " + 
              QTNAME(victim) + " a vicious boot to the head!\n", victim); 
    tell_object(victim, query_The_name(victim) + jump + 
                " gives you a vicious boot to the head!\n"); 

    /* This attack should not kill if enemy's hp is < 1! */ 
}


void
stun_attack(object victim)
{
    string jump; 
    int relh; 

    if (victim->query_prop(LIVE_I_ATTACK_DELAY) ||
        victim->query_prop(LIVE_I_STUNNED)) 
        return; 

    relh = (query_prop(CONT_I_HEIGHT) * 100) / 
           victim->query_prop(CONT_I_HEIGHT); 

    if (relh <= 65) 
        jump = " leaps high and"; 
    else if (relh >= 180)
        jump = " stoops and"; 
    else
        jump = ""; 

    if (resolve_task(TASK_ROUTINE, ({ TS_DIS, TS_DEX }), 
                     victim, ({ TS_DIS, TS_DEX })) < 0) {
        tell_watcher(QCTNAME(this_object()) + jump + " misses " + 
                  QTNAME(victim) + 
                  " with a vicious head-butt!\n", victim);  
        tell_object(victim, query_The_name(victim) +  
                    jump + " misses you with a vicious " +
                    "head-butt!\n"); 
        return; 
    } 

    victim->add_attack_delay(10 + random(3) * 5, 1); 
    tell_watcher(QCTNAME(this_object()) + jump + " head-butts " + 
              QTNAME(victim) + "!\n", victim);  
    tell_object(victim, query_The_name(victim) + 
                jump + " head-butts you!\n"); 
}


int 
is_potential_victim(object attacker) 
{
    return 
        (attacker->query_attack() == this_object() && 
         !attacker->query_prop(OBJ_M_NO_ATTACK) && 
         attacker->query_average_stat() >= MIN_AVG_FOR_ENEMY); 
}


/* 
 * Function:     query_appropriate_victim 
 * Description:  Returns the most appropriate victim to hit from 
 *               the current enemies, in order to redirect attack 
 *               if necessary. 
 */ 
object 
query_appropriate_victim(object *potential_victims) 
{
    int i, lowest_hp; 
    object victim; 

    if (!sizeof(potential_victims)) 
        return 0; 
    else if (sizeof(potential_victims) == 1) 
        return potential_victims[0]; 

    lowest_hp = (victim = potential_victims[0])->query_hp(); 

    for (i = 1; i < sizeof(potential_victims); i++) { 
       if (potential_victims[i]->query_hp() < lowest_hp) 
           lowest_hp = (victim = potential_victims[i])->query_hp(); 
    } 
    return victim; 
}


/* 
 * Function:     query_present_attackers 
 * Description:  Returns an object array of the present attackers 
 *               in the environment of this npc. 
 * 
 */ 
object * 
query_present_attackers() 
{
    return filter(all_inventory(environment(this_object())), 
                  &is_potential_victim()); 
}


/* 
 * Function:     special_attack 
 * Description:  Cadet guildmaster's special attacks, are managed 
 *               from here. It's called by the standard combat 
 *               system. 
 */ 
int 
special_attack(object victim) 
{ 
    object newvic; 

    if (++round_count % 2) 
    { 
        newvic = query_appropriate_victim(query_present_attackers()); 
        if (objectp(newvic) && newvic != victim) 
        { 
            command("kill " + OB_NAME(newvic)); 
            return 0; 
        } 

        if (objectp(victim) && 
            victim->query_average_stat() < MIN_AVG_FOR_ENEMY) 
        { 
            return 1; 
        } 

        return 0; 
    } 

    newvic = query_appropriate_victim(query_present_attackers()); 
    if (objectp(newvic) && newvic != victim) 
        command("kill " + OB_NAME(victim = newvic)); 
    else if (victim->query_average_stat() < MIN_AVG_FOR_ENEMY) 
    { 
        if (victim->query_prop(LIVE_I_ATTACK_DELAY) ||
            victim->query_prop(LIVE_I_STUNNED)) 
            damage_attack(victim); 
        else 
            stun_attack(victim); 
        return 1; 
    } 

    if (victim->query_prop(LIVE_I_ATTACK_DELAY) ||
        victim->query_prop(LIVE_I_STUNNED)) 
        damage_attack(victim); 
    else 
        stun_attack(victim); 

    return 0; 
}


void 
attack_object(object ob) 
{
    ::attack_object(ob); 

    if (!(query_prop(LIVE_I_ATTACK_DELAY) || 
          query_prop(LIVE_I_STUNNED))) 
    { 
        stun_attack(ob); 
    } 

    check_pie(ob); 

/*
    if (ob->query_average_stat() >= 100) 
        add_prop(LIVE_O_ENEMY_CLING, ob); 
 */ 
}


void 
attacked_by(object ob)
{
    ::attacked_by(ob); 

    if (!(query_prop(LIVE_I_ATTACK_DELAY) || 
          query_prop(LIVE_I_STUNNED))) 
    { 
        stun_attack(ob); 
    } 
 
    check_pie(ob); 

/* 
    if (ob->query_average_stat() >= 100) 
        add_prop(LIVE_O_ENEMY_CLING, ob); 
 */ 
}


public void 
do_die(object killer) 
{
    int i; 
    object *weapons; 

    weapons = filter(all_inventory(this_object()), 
                     &->check_weapon()); 
    for (i = 0; i < sizeof(weapons); i++) { 
        tell_room(environment(), QCTNAME(this_object()) + " breaks " + 
                      LANG_THESHORT(weapons[i]) + ".\n"); 
        weapons[i]->add_prop(OBJ_I_BROKEN, 1); 
    } 

    ::do_die(killer); 
} 


int
second_life(object killer)
{
    object ghost; 

    ::second_life(killer); 
    log_file("cadet", ctime(time()) + ": Xorfin killed by " + 
                      killer->query_real_name() + ".\n"); 
    seteuid(getuid()); 
    ghost = clone_object(GELAN_OBJECTS + "ghost"); 
    ghost->set_ghost_des("ancient powerful male dwarf"); 
    ghost->set_duration(800); 
    ghost->move(killer); 
    ghost->start_haunt(); 

    return 0; 
}


/* 
 * Function:      oath_stage 
 * Description:   Guildmaster asks the specified player to take an oath 
 *                of the specified number, which can vary from 0 to 2
 */
void
oath_stage(int stage, object tp)
{
    switch (stage) {
        case 0 : 
            command("say to " + tp->query_real_name() + 
                    " If you wish to join the cadets you " +
                    "will first have to swear three oaths upon " + 
                    "your honour."); 
            command("say to " + tp->query_real_name() + 
                    " Repeat: " + OATH0 + "."); 
            break;
         case 1 :
            command("say to " + tp->query_real_name() + 
                    " Repeat: " + OATH1 + "."); 
            break;
         case 2 : 
            command("say to " + tp->query_real_name() + 
                    " Repeat: " + OATH2 + "."); 
            break;
         default : 
            command("ponder bugs"); 
            break;      
    } 
}


int
is_unable_to_give(string item, object tp)
{
    if (!CAN_SEE_IN_ROOM(this_object())) { 
        command("say Whoever asked me for " + item + ", it's too dark for " +
                "me to see you!"); 
        return 1; 
    } 

    if (!CAN_SEE(this_object(), tp)) {  
        command("say Whoever asked me for " + item + ", I can't see " +
                "where you are!"); 
        return 1; 
    } 

    if (objectp(query_attack())) { 
        command("say to " + OB_NAME(tp) + " Not now, I'm busy!"); 
        return 1; 
    } 

    return 0; 
}


/* 
 * Function:      give_shoes 
 * Description:   Gives shoes to a cadet who has lost or broken 
 *                their old pair. 
 * Arguments:     object tp   - the cadet. 
 */ 
void 
give_shoes(object tp)
{
    object shoes; 

    if (is_unable_to_give("shoes", tp)) 
        return; 

    if (!IS_GELAN_CADET(tp)) { 
        command("say to " + OB_NAME(tp) + " You are not a cadet!"); 
        return; 
    } 

    if (objectp(shoes = present(GC_SHOES_ID, tp))) 
    { 
        if (shoes->query_prop(OBJ_I_BROKEN)) 
        { 
            tell_object(tp, query_The_name(tp) + " takes " + 
                LANG_THESHORT(shoes) + " from you.\n"); 
            tell_room(environment(tp), QCTNAME(this_object()) + 
                " takes " + LANG_THESHORT(shoes) + " from " + 
                QTNAME(tp) + ".\n", ({ tp })); 
            shoes->remove_object(); 
        } 
        else 
        { 
            command("say to " + OB_NAME(tp) + 
                    " You already have shoes, cadet!"); 
            return; 
        } 
    } 

    seteuid(getuid()); 
    shoes = clone_object(GC_SHOES); 
    shoes->move(this_object()); 
    shoes->remove_prop(OBJ_M_NO_DROP); 
    command("give " + OB_NAME(shoes) + " to " + OB_NAME(tp)); 
    shoes->add_prop(OBJ_M_NO_DROP, 1); 

    if (objectp(present(shoes, this_object()))) { 
        shoes->remove_object(); 
        command("sigh"); 
        command("say to " + OB_NAME(tp) + 
                " I can't seem to give these shoes to you!"); 
    } 
}


void
give_notebook(object tp)
{
    object nb; 

    if (is_unable_to_give("a notebook", tp)) 
        return; 

    if (!IS_GELAN_CADET(tp)) { 
        command("say to " + OB_NAME(tp) + " You are not a cadet!"); 
        return; 
    } 

    if (objectp(present(GC_NOTEBOOK_ID, tp))) { 
        command("say to " + OB_NAME(tp) + " You already have a notebook, " + 
                "cadet!"); 
        return; 
    } 

    seteuid(getuid()); 
    nb = clone_object(GC_DIR + "cadet_notebook"); 
    nb->move(this_object()); 
    command("give " + OB_NAME(nb) + " to " + OB_NAME(tp)); 

    if (objectp(present(nb, this_object()))) { 
        nb->remove_object(); 
        command("sigh"); 
        command("say to " + OB_NAME(tp) + 
                " I can't give this notebook to you!"); 
        return; 
    } 
}


void 
give_ring(object tp) 
{
    object r; 
    string n; 

    if (is_unable_to_give("a ring", tp)) 
        return; 

    n = tp->query_real_name(); 
    seteuid(getuid()); 
    if (!GC_TRAINROOM->is_registered_graduate(n)) { 
        command("say to " + OB_NAME(tp) + " You are not registered " + 
                "as a graduate!"); 
        return; 
    } 

    if (objectp(present(GC_RING_ID, tp))) { 
        command("say to " + OB_NAME(tp) + " You already have a " + 
                "graduation ring!"); 
        return; 
    } 

    seteuid(getuid()); 
    r = clone_object(GC_DIR + "graduation_ring"); 
    r->move(this_object()); 
    r->remove_prop(OBJ_M_NO_DROP); 
    command("give " + OB_NAME(r) + " to " + OB_NAME(tp)); 
    r->add_prop(OBJ_M_NO_DROP, 1); 

    if (objectp(present(r, this_object()))) { 
        r->remove_object(); 
        command("sigh"); 
        command("say to " + OB_NAME(tp) + 
                " I can't give this ring to you!"); 
        return; 
    } 
}


/* 
 * Function:      reply_shoes 
 * Description:   Reply to an ask about shoes. This just calls the 
 *                function give_shoes and return a blank string. 
 * Returns:       string - empty string. 
 */ 
string 
reply_shoes() 
{ 
    give_shoes(this_player()); 

    return ""; 
} 


string
reply_notebook()
{
    give_notebook(this_player()); 
 
    return ""; 
}


string 
reply_ring()
{
    give_ring(this_player()); 

    return ""; 
}


/* 
 * Function:      reply_cadets 
 * Description:   Reply to an ask about cadets. If the asking person 
 *                is a graduate or someone who has donated much 
 *                to the racks, Xorfin will whisper to them a list of 
 *                cadets who are currently in the realms. He will not 
 *                give this response to someone who has a bad reputation. 
 * Returns:       string - empty string. 
 */ 
string 
reply_cadets() 
{ 
    mixed list; 
    object tp = this_player(); 
    string rn = tp->query_real_name(); 

    if (annoyance[rn] > 3) 
    { 
        command("ignore " + OB_NAME(tp)); 
        return ""; 
    } 

    seteuid(getuid()); 
    if (GC_TRAINROOM->is_unworthy(rn)) 
    { 
        command("whisper " + OB_NAME(tp) + " Your reputation is bad " + 
                "here, so I won't tell you."); 
        return ""; 
    } 

    if (IS_GELAN_CADET(tp)) 
    { 
        command("chuckle"); 
        command("whisper " + OB_NAME(tp) + " You don't have to " + 
                "ask me to find that out!"); 
        return ""; 
    } 

    if (!IS_GRADUATE(tp) && 
        (tp->query_skill(SS_CADET_DROPROOM_POINTS) < 
         MIN_RACK_POINTS_FOR_CLIST)) 
    { 
        command("whisper " + OB_NAME(tp) + " If you <donate> " + 
                "many items to this guild, I could let you know."); 
        return ""; 
    } 

    list = filter(users(),&operator(==)(GC_GUILD_NAME) @ 
        &->query_guild_name_lay()); 
    list = filter(list, &operator(!=)(100) @ &->query_invis()); 

    if (!sizeof(list)) 
    { 
        command("whisper " + OB_NAME(tp) + " There are no cadets " + 
                "in the realms."); 
        return ""; 
    } 

    list = sort_array(map(list, &capitalize() @ &->query_real_name())); 

    command("whisper " + OB_NAME(tp) + " " + COMPOSITE_WORDS(list) + 
            ((sizeof(list) > 1) ? " are " : " is ") + "in the realms."); 
    return ""; 
} 


/* 
 * Function:     annoying_emote_hook 
 * Description:  Called when someone uses an annoying emote 
 *               on the guildmaster. 
 * Arguments:    string emote   - the emote 
 *               object actor   - the actor 
 *               string adverb  - the adverb 
 */ 
private int
annoying_emote_hook(string emote, object actor, string adverb)
{
   int current_annoy, tmp_annoy, tmp_flustered; 
   string nm; 

   nm = actor->query_real_name(); 

   current_annoy = tmp_annoy = annoying_emotes[emote]; 
   if (!tmp_annoy) { 
       if (annoyance[nm]) 
           return 1; 
       else 
           return 0; 
   } 

   tmp_flustered = 
          ((member_array(emote, flustered_emotes) > -1) && 
            (actor->query_gender() == G_FEMALE) && 
            !IS_GELAN_CADET(actor) && 
            !annoyance[nm]); 

   if (tmp_flustered) { 
        tmp_flustered += flustered[nm]; 
        flustered[nm] = tmp_flustered; 

        if (tmp_flustered == 1) { 
            command("chuckle"); 
            return 1; 
        }
        if (tmp_flustered == 2)  { 
            command("say Stop that please, I'm married!"); 
            return 1; 
        } 
        if (tmp_flustered == 3)  { 
            command("emote grumbles angrily."); 
            command("say Erm, enough of that " + 
                    "thanks, Miss, my wife would kill me."); 
            return 1; 
        } 
   } 

   tmp_annoy += annoyance[nm]; 
   annoyance[nm] = tmp_annoy; 

   if (!tmp_annoy) 
       return 0; 

   if (tmp_annoy == 1) { 
       command("poke " + nm); 
       return 1; 
   } 

   if (!random(2)) 
       check_pie(actor); 

   if (tmp_annoy == 2) { 
       command("grumble angrily"); 
       command("poke " + nm + " eye"); 
       return 1; 
   } 

   if (tmp_annoy == 3) { 
       command("scowl " + nm); 
       command("say to " + nm + " Watch it!"); 
       return 1; 
   } 

   if (tmp_annoy == 4) { 
       command("kick " + nm); 
       command("say to " + nm + " If you persist with your antics, " + 
               "I will make you regret them."); 
       return 1; 
   } 

   if (IS_GELAN_CADET(actor)) 
   { 
       if ((member_array(nm, warned) == -1) && tmp_annoy < 10) 
       { 
           if (current_annoy == 5) 
           { 
               actor->warn_for_misconduct(query_real_name(), 
                   "disgraceful conduct"); 
               warned += ({ nm }); 
           } 
           else 
           { 
               actor->warn_for_misconduct(query_real_name(), 
                   "annoying Xorfin"); 
               warned += ({ nm }); 
           } 
           command("say to " + nm + " Any more " + 
                   "disrespect from you, I'll kick your butt out of " + 
                   "this guild!"); 
           command("kick " + nm); 
           greeted -= ({ nm }); 
           return 1; 
       } 
       command("say to " + nm + " So long, ex-Cadet!"); 
       actor->kick_out_for_misconduct(query_real_name(), "annoying " + 
          actor->query_possessive() + " drill Sergeant"); 
       return 1; 
   } 

   if ((current_annoy == 5) || (tmp_annoy > 12)) 
   { 
       command("emote growls savagely."); 
       command("say You asked for it!"); 
       command("kill " + nm); 
       return 1; 
   } 

   command("kick " + nm); 
   if (current_annoy > 2) 
       command("kick " + nm); 
   if (tmp_annoy > 8) 
       command("kick " + nm); 

   if (random(2)) 
      set_alarm(1.0, 0.0, &command("kick " + nm)); 

   return 1; 
}


private int
friendly_emote_hook(string emote, object actor, string adverb)
{
    string nm = actor->query_real_name(); 

    switch (emote) {
        case "smile" : 
        case "grin" : command("smile . " + nm);
                      return 1; 
                      break; 
        case "wave" :
                      command("wave . " + nm); 
                      return 1;
                      break; 
        case "greet" : 
                      command("greet " + nm);
                      return 1; 
                      break; 
    } 
    return 0;
}


private int 
cadet_emote_hook(string emote, object actor, string adverb)
{
    string nm = actor->query_real_name(); 

    if (emote == "cplan" || emote == "cready" || 
        emote == "cobserve" || emote == "cstudy" || 
        emote == "cscrut") {
        switch (random(6)) {
            case 0 : command("smirk"); 
                     break;
            case 1 : command("tackle " + nm); 
                     break;
            case 2 : command("eyebrow " + nm); 
                     break;
            case 3 : command("pat " + nm); 
                     break;
            default : break;
        } 
        return 1;
    }

    if (emote == "csalute") {
        command("csalute " + nm); 
        return 1;
    }

    return 0;
}


void 
emote_hook(string emote, object actor, string adverb, 
           object *oblist, int cmd_attr, int targ) 
{
    if (!targ || !sizeof(oblist) || objectp(query_attack())) 
        return; 

    if (annoying_emote_hook(emote, actor, adverb)) 
        return; 

    if (friendly_emote_hook(emote, actor, adverb)) 
        return; 

    if (IS_GELAN_CADET(actor)) 
        cadet_emote_hook(emote, actor, adverb); 
}


/* 
 * Function:     do_block 
 * Description:  Xorfin can block people who are stunned from 
 *               leaving the room. Returns 1 if blocked, 0 
 *               otherwise. 
 * Arguments:    str, the direction to block in. 
 * 
 */ 
int 
do_block(string str) 
{
    object tp = this_player(); 

    if ((tp->query_average_stat() >= MIN_AVG_FOR_ENEMY) && 
        (member_array(tp, query_enemy(-1)) > -1)) 
    { 
        if (tp->query_prop(LIVE_I_STUNNED) || 
            tp->query_prop(LIVE_I_ATTACK_DELAY)) 
        { 
            if (resolve_task(TASK_SIMPLE, ({ TS_DEX }), tp, ({ TS_DEX })) > 0) 
            {  
                tell_object(tp, "As you are stunned, " + query_the_name(tp) + 
                            " is able to prevent you from leaving.\n"); 
                tell_room(environment(tp), "As " + QTNAME(tp) + 
                      " is stunned, " + QTNAME(this_object()) + 
                      " is able to prevent " + tp->query_objective() + 
                      " from leaving.\n", tp); 
                return 1; 
            } 
        } 
    } 
    return 0; 
} 


/* 
 *  Function:     add_greeted
 *  Description:  Add that the npc recently greeted someone. 
 */ 
void
add_greeted(string name) 
{
    if (member_array(name, greeted) == -1)
        greeted += ({ name }); 
}


/* 
 * Function:     do_greet
 * Description:  Xorfin greets someone he knows if he hasn't seen 
 *               them in a while. 
 */ 
void
do_greet(object tp, string name) 
{
    if (CAN_SEE(this_object(), tp) &&
        CAN_SEE_IN_ROOM(this_object())) {
        switch (random(4)) {
            case 0 : 
                command("say Hello, " + capitalize(name) + "."); 
                break;
            case 1 : 
                command("say Greetings, " + capitalize(name) + "."); 
                break; 
            case 2 :
                command("say Hi " + capitalize(name) + "."); 
                break; 
            case 3 : 
                command("greet " + name); 
                break;  
        } 
    } 
}


/* 
 * Function:     bad_reaction 
 * Description:  reacts angrily sometimes when someone who 
 *               insulted him passes. 
 */ 
void 
bad_reaction(object tp, string name)
{
    if (CAN_SEE(this_object(), tp) && 
        CAN_SEE_IN_ROOM(this_object())) { 
        switch (random(8)) { 
            case 0 : 
                command("glare " + name); 
                break; 
            case 1 : 
                command("growl " + name); 
                break; 
        } 
    } 
}


int
query_remember(object pl) 
{
    if (IS_GELAN_CADET(pl) || IS_GRADUATE(pl))
        return 1; 
    return ::query_remember(pl); 
}


/* 
 * Function:     do_donate 
 * Description:  Donate an item to the cadet racks. 
 * 
 */ 
int 
do_donate(string str) 
{ 
    object *oblist, donation, droproom, tp; 
    string sh; 
    int v; 

    tp = this_player(); 

    if (!stringp(str) || !strlen(str) || 
        !sizeof(oblist = FIND_STR_IN_ARR(str, all_inventory(tp)))) 
    { 
        notify_fail("Donate what to the cadet racks?\n"); 
        return 0; 
    } 

    if (sizeof(oblist) > 1) 
    { 
        notify_fail("You may only donate one item at once to " + 
                    "the cadet racks.\n"); 
        return 0; 
    } 

    donation = oblist[0]; 
    sh = LANG_ASHORT(donation); 
    write("You offer " + sh + " as a donation to " + 
          "the cadet racks.\n"); 
    say(QCTNAME(this_player()) + " offers " + sh + 
        " as a donation to the cadet racks.\n"); 

    if (tp->query_attack() == this_object()) 
    { 
        command("kick " + OB_NAME(tp)); 
        return 1; 
    } 

    if (objectp(query_attack())) 
    { 
        command("say Yeah right, try again later!"); 
        return 1; 
    } 

    if (IS_COINS_OBJECT(donation)) 
    { 
        v = donation->query_prop(OBJ_I_VALUE); 
        if (v > 500) 
            command("$emote smiles thankfully"); 
        else if (v > 1000) 
            command("$emote smiles appreciatively"); 
        else if (v > 4000) 
            command("$emote smiles very appreciatively"); 

        command("say Very generous of you, but there is " + 
                "no fund to add that to currently."); 
        return 1; 
    } 

    if (donation->id(GC_NOTEBOOK_ID)) 
    { 
        command("rolleyes"); 
        command("poke " + OB_NAME(tp)); 
        return 1; 
    } 

    if (IS_GELAN_CADET(tp) || IS_GRADUATE(tp)) 
    { 
        command("say Cadets and graduates can " + 
                "donate to the racks another way, " + 
                capitalize(tp->query_real_name()) + "!"); 
        return 1; 
    } 

    if (living(donation)) 
    { 
        command("boggle"); 
        command("say Thanks for the thought but we don't rack " + 
                "live animals!"); 
        return 1; 
    } 

    if (donation->query_prop(OBJ_I_BROKEN)) 
    { 
        command("chuckle"); 
        command("say Good of you to think of our armoury, but " + 
                "that " + donation->query_name() + " doesn't " + 
                "look much use at the moment."); 
        return 1; 
    } 

    if (donation->query_keep()) 
    { 
        command("say Are you sure you want to " + 
                "donate " + LANG_THESHORT(donation) + 
                "? If so, please unkeep the donation " + 
                "and try again."); 
        return 1; 
    } 

    seteuid(getuid()); 

#ifdef DEBUG_GUILDMASTER
    droproom = (GC_DIR + "cadet_droproom2")->get_this_object(); 
#else
    droproom = GC_DROPROOM->get_this_object(); 
#endif

    sh = LANG_THESHORT(donation); 

    if (!droproom->donate_one_object(tp, donation, 
         "A guard arrives and racks " + LANG_ASHORT(donation) + ".\n")) { 
         command("ack"); 
         command("say That " + donation->query_name() + " can't be racked."); 
         return 1; 
    } 

    tell_room(environment(this_object()), 
              QCTNAME(this_object()) + " gives " + sh + 
              " to a guard, who stores it in the racks.\n"); 
    command("$thank " + OB_NAME(tp)); 
    return 1; 
} 


void 
init_living()
{
    int i; 
    object tp = this_player(); 
    string name = tp->query_real_name(); 

    ::init_living(); 
    add_action(do_donate, "donate"); 
    if (objectp(tp) && (IS_GELAN_CADET(tp) || IS_GRADUATE(tp))) { 
        tp->add_introduced("xorfin"); 
        if (member_array(name, greeted) == -1) { 
            if ((i = annoyance[name]) > 4 || 
                tp->query_prop(ATTACKED_GELAN)) { 
                set_alarm(0.0, 0.0, &bad_reaction(tp, name)); 
                return; 
            } 
            greeted += ({ name }); 
            if (i || 
                tp->query_i_attacked_cadets() || 
                tp->query_skill(SS_CADET_DONK_BAN) > time() ||
                tp->query_prop(OBJ_I_HIDE)) 
                return; 
            set_alarm(0.0, 0.0, &do_greet(tp, name)); 
        } 
    } 
    for (i = 0; i < sizeof(block_directions); i++) 
        add_action(do_block, block_directions[i]); 
}


/* 
 * Function:     enter_env 
 * Description:  When the cadet guildmaster enters a new 
 *               environment, update the block directions. 
 */ 
void 
enter_env(object dest, object old) 
{ 
    ::enter_env(dest, old); 
    if (objectp(dest)) { 
        if (!pointerp(block_directions = dest->query_exit_cmds())) 
            block_directions = ({ }); 
    } 
} 


/* 
 * Function name: help_me 
 * Description:   send help request to the master guard. Currently 
 *                Xorfin doesn't want help so this function just 
 *                returns 0; 
 * Arguments:     meeting point, room, attacker 
 * Returns:       number of guards alarmed 
 */ 
int 
help_me(string room, object attacker)
{
    return 0; 
}

