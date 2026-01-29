
/*  
 
   the Cadets of Gelan training room 

   Coded by Maniac@Genesis, March 1997

   Copyright (c) Miguel Leith 1997 
   
*/

#include <ss_types.h>
#include <stdproperties.h>
#include <macros.h>
#include <language.h>
#include <money.h>
#include <composite.h>
#include <std.h>

#include "/d/Calia/gelan/gelan.h"
#include "cadet.h"

#pragma save_binary

inherit "/std/room"; 
inherit "/lib/skill_raise";

string *allowed_back = ({ }); 

static object guildmaster;

static mapping gc_name_selected_map = GC_NAME_SELECTED_MAP; 

void
set_up_skills()
{
    string me, ot;

    me = "fight unarmed"; ot = me;
    sk_add_train(SS_UNARM_COMBAT,  ({ me, ot }), 0, 0, 50 );

    me = "use a sword"; ot = me;
    sk_add_train(SS_WEP_SWORD,  ({ me, ot }), 0, 0, 50 );

    me = "use a polearm"; ot = me;
    sk_add_train(SS_WEP_POLEARM,({ me, ot }), 0, 0, 50 );

    me = "use a knife"; ot = me;
    sk_add_train(SS_WEP_KNIFE,({ me, ot }), 0, 0, 50 );

    me = "use an axe"; ot = me;
    sk_add_train(SS_WEP_AXE,({ me, ot }), 0, 0, 50 );

    me = "use a club"; ot = me;
    sk_add_train(SS_WEP_CLUB,({ me, ot }), 0, 0, 50 );

    me = "fight with both hands"; ot = me; 
    sk_add_train(SS_2H_COMBAT,  ({ me, ot }), 0, 0, 37 );

    me = "fight in the dark"; ot = me;
    sk_add_train(SS_BLIND_COMBAT,  ({ me, ot }), 0, 0, 50 );

    me = "parry"; ot = me;
    sk_add_train(SS_PARRY,      ({ me, ot }), 0, 0, 37 );

    me = "defend yourself"; ot = "use defence skill";
    sk_add_train(SS_DEFENCE,    ({ me, ot }), 0, 0, 50 );

    me = "remember what continent it is"; ot = me;
    sk_add_train(SS_LOC_SENSE,    ({ me, ot }), 0, 0, 30 );

    me = "be sneaky"; ot = me;
    sk_add_train(SS_SNEAK,    ({ me, ot }), 0, 0, 20 );

    me = "play hide and seek"; ot = me;
    sk_add_train(SS_HIDE,    ({ me, ot }), 0, 0, 20 );
}


/* Bring guildmaster back in if he's missing */
void
reset_room()
{
     if (!objectp(guildmaster)) { 
         guildmaster = clone_object(GC_GUILDMASTER); 
         guildmaster->arm_me(); 
         guildmaster->move_living("into the training room", this_object()); 
     } 
     restore_object(GC_SAVE); 
     if (!allowed_back) 
         allowed_back = ({ }); 
}


void
enter_inv(object ob, object from)
{
    int i;

    ::enter_inv(ob, from); 

    if (interactive(ob)) { 
        if ((i = member_array(ob->query_real_name(), allowed_back)) > -1) { 
            ob->clear_bit(GC_GROUP, GC_BIT);  
            allowed_back = exclude_array(allowed_back, i, i);  
            save_object(GC_SAVE); 
        } 
    } 
}


int
cadet_check()
{
    object tp = this_player(); 

    if (IS_GELAN_CADET(tp)) 
        return 0;

    tell_object(tp, "Only cadets may go in there.\n");  
    return 1;
}


void
create_room()
{ 
    set_short(GC_GUILD_NAME);
    set_long("This is the training room of the " + GC_GUILD_NAME + ". " +
         "Youngsters who want to learn something about self-discipline " +
         "and fighting in preparation for an occupation as a warrior " + 
         "often spend time as a cadet here under the watchful eye " +
         "of " + GC_GM_NAME + ", the guild's founder. The guild tax is " +
         GC_GUILD_TAX + "%. If you wish to join you may <csign on>, but " +
         "you should <help csign> first. Cadets can <learn> and <improve> " +
         "various skills here, and can also <choose> a primary and " +
         "secondary offensive skill. Cadet titles may be listed here using " +
         "the <ctitles> command.\n");  

    add_prop(ROOM_I_INSIDE, 1);
    add_prop(OBJ_S_WIZINFO, "Wizards with write access in Calia " +  
                            "may use the <cpermit> command here " +
                            "to allow a cadet who left the guild " + 
                            "back in if they lost guild membership " +
                            "due to a bug.\n"); 

    create_skill_raise();
    set_up_skills();

    add_exit(GC_STARTROOM, "south", "@@cadet_check");  
    add_exit(GELAN_SCHOOL_CONNECT, "north"); 

    reset_room();
}




/* 
 * Kick out a cadet. 
 * The messages should be written elsewhere. 
 */ 
int
kick_out_cadet(object player)
{
    object shoes;

    if (!player->remove_guild_lay()) {  
        tell_object(player, 
                 "Ack, could not remove you from the guild.\n");
        log_file("cadet", "Could not kick out " + 
                          player->query_real_name() + 
                          " from the guild.\n"); 
        return 0;
    } 

    player->clear_guild_stat(SS_LAYMAN); 
    player->remove_prop(CADET_I_CONFIRM_LEAVE); 
    player->remove_skill(GC_SKILL_PRIMARY_WEAPON); 
    player->remove_skill(GC_SKILL_SECONDARY_WEAPON); 
    player->setup_skill_decay(); 
    if (player->query_default_start_location() == GC_STARTROOM) 
        player->set_default_start_location(player->query_def_start()); 
    if (objectp(shoes = present(GC_SHOES_ID, player))) 
        shoes->remove_object(); 
    if (environment(player)->gc_query_private_room())  
        player->move_living("to the cadet training room", this_object());  
    log_file("cadet", ctime(time()) + " " + 
             player->query_real_name() + " left.\n"); 
    return 1;
}


/*
 * Kick a cadet out if he's too big.
 */ 
void
too_big_check(object player)
{
     if (!objectp(player) || 
         !IS_GELAN_CADET(player) ||
         player->query_wiz_level()) 
         return;

     if (GC_AVG_STAT_EXPEL(player)) {  
         if (!kick_out_cadet(player)) 
             return;

         tell_object(player, 
             "You are now an adult and have hence outgrown the cadets. " +
             "The guild thanks you for your efforts and wishes you " +
             "every success in your future occupation.\n"); 

         log_file("cadet", player->query_real_name() + 
             " kicked out for being too big.\n"); 
    } 
}


/* 
   This is called from the shadow on initialisation, we break it up 
   with an alarm to ensure everything works ok when it removes the 
   guild member, this produced bugs before for some reason. 
 */ 
void
kick_out_if_too_big(object player)
{
     set_alarm(1.0, 0.0, &too_big_check(player)); 
}


/* 
 * Kick a player out for misconduct, this may be called 
 * from the cadet shadow or from a Gelan npc. 
 */
void
kick_out_for_misconduct(object player)
{
     if (!objectp(player) || !IS_GELAN_CADET(player)) 
         return;

     if (!kick_out_cadet(player)) 
         return;

     tell_object(player, 
          "You are guilty of misconduct in the cadets and have " +
          "therefore been expelled.\n"); 

     log_file("cadet", player->query_real_name() + 
              " kicked out for misconduct.\n"); 
}


int
offensive_skill(int snum)
{
     if ((snum == SS_WEP_SWORD) ||   
         (snum == SS_WEP_AXE) || 
         (snum == SS_WEP_POLEARM) || 
         (snum == SS_WEP_KNIFE) || 
         (snum == SS_WEP_CLUB) || 
         (snum == SS_UNARM_COMBAT)) 
         return 1;

    return 0;
}


int
sk_improve(string str)
{
    object tp;
    int ofsk, max, steps, *guild_sk, *known_sk, snum, level, cost, sub, sw, pa;
    string skill, verb, *tmp;

    if (!str || sscanf(str, "%d", steps))
        return sk_list(steps);

    tp = this_player();
    if (!IS_GELAN_CADET(tp))
    {
        write("You are not a member of this guild.\n");
        return 1;
    }

    if (!objectp(guildmaster) || !present(guildmaster, this_object()))
    {
        write("You cannot improve skills while " + GC_GM_NAME + 
              " is not here.\n");
        return 1;
    }

    tmp = explode(str, " ");
    if (sscanf(tmp[sizeof(tmp) - 1], "%d", steps) == 1 && sizeof(tmp) > 1)
        skill = implode(tmp[0 .. sizeof(tmp) - 2], " ");
    else
    {
        skill = str;
        steps = 1;
    }

    guild_sk = sk_query_train();
    known_sk = this_player()->query_all_skill_types();
    if (!known_sk)
        known_sk = ({});

    verb = query_verb();
    if ((snum = sk_find_skill(skill)) < 0)
        return sk_hook_unknown_skill(skill, verb);

    level = this_player()->query_base_skill(snum);

    max = sk_query_max(snum); 

    ofsk = 0;
    if (offensive_skill(snum)) { 
        if (tp->gc_query_primary_skill_num() == snum) 
            max = GC_MAX_LEVEL_PRIMARY_WEAPON; 
        else if (tp->gc_query_secondary_skill_num() == snum) { 
            ofsk = GC_MAX_LEVEL_SECONDARY_WEAPON;
            max = GC_MAX_LEVEL_SECONDARY_WEAPON; 
        } 
        else {  
            ofsk = 30; 
            max = 30; 
        } 
    } 

    if (!level && verb == "improve")
        return sk_hook_improve_unknown(skill);
    if (level && verb == "learn")
        return sk_hook_learn_known(skill);
    if (level + steps > max) { 
        if (ofsk == GC_MAX_LEVEL_SECONDARY_WEAPON) { 
            notify_fail("You cannot train your secondary offensive skill " +
                        "any higher.\n"); 
            return 0;
        } 
        else if (ofsk == 30) {  
            notify_fail("That would have to be your primary or secondary " +
                        "offensive skill for you to train it any higher.\n"); 
            return 0;
        } 
        else
            return sk_hook_improved_max(skill);
    } 
    if (!sk_do_train(snum, this_player(), level + steps))
        return sk_hook_cant_train(skill, level + steps);

    cost = sk_cost(snum, level, level + steps);

    if (!MONEY_ADD(this_player(), -cost))
    {
        this_player()->set_skill(snum, level);
        return sk_hook_cant_pay(skill, level + steps, cost);
    }

    sk_hook_raise_rank(snum, level + steps, cost);

    return 1;
}



int 
setsk(int skill, object tp, mapping sk)
{
    tp->set_skill(skill, sk[skill]); 
    return 0; 
}


int
csign(string str)
{
    object tp, shadow;
    mapping sk, tmp; 
    int i, m;

    tp = this_player(); 

    if (!objectp(tp))  
         return 0;

    if (!objectp(guildmaster) || !present(guildmaster, this_object()))
    {
        notify_fail(GC_GM_NAME + " is not here.\n");
        return 0;
    }

    if ((str != "on") && (str != "again")) { 
        notify_fail("Did you want to <csign on>?\n"); 
        return 0;
    } 

    if (!GC_AVG_STAT_CAN_JOIN(tp)) { 
        notify_fail("You're a bit too big to be joining the cadets!\n"); 
        return 0;
    } 

    if (IS_GELAN_CADET(tp))
    {
        notify_fail("You are already a member of this guild!\n");
        return 0;
    }

    if (tp->query_guild_member(GC_GUILD_TYPE)) {  
        notify_fail("You are already a member of another " + 
                    GC_GUILD_TYPE + " guild.\n"); 
        return 0;
    } 

    if (tp->query_guild_member_occ()) {  
        if (!tp->query_wiz_level()) { 
            notify_fail("You cannot join if you have an occupation!\n");  
            return 0;
        } 
        write("Since you are a wizard, the fact you have an occupation " +
              "will not stop you joining.\n"); 
    } 

    if (tp->test_bit(GC_DOM, GC_GROUP, GC_BIT)) { 
        if (tp->test_bit(GC_DOM, GC_GROUP, GC_BIT2)) { 
            notify_fail("You may not re-join more than once.\n"); 
            return 0;
        } 
        else if (str != "again") { 
            notify_fail("You will have to <csign again>, but remember " +
                       "to check <help csign> first.\n");  
            return 0;
        } 
        else { 
            sk = 
                ([ 
                    SS_UNARM_COMBAT : tp->query_skill(SS_UNARM_COMBAT),  
                    SS_WEP_SWORD : tp->query_skill(SS_WEP_SWORD), 
                    SS_WEP_POLEARM : tp->query_skill(SS_WEP_POLEARM), 
                    SS_WEP_AXE : tp->query_skill(SS_WEP_AXE), 
                    SS_WEP_KNIFE : tp->query_skill(SS_WEP_KNIFE), 
                    SS_WEP_CLUB : tp->query_skill(SS_WEP_CLUB), 
                    SS_PARRY : tp->query_skill(SS_PARRY), 
                    SS_DEFENCE : tp->query_skill(SS_DEFENCE),  
                    SS_2H_COMBAT : tp->query_skill(SS_2H_COMBAT) 
                 ]); 
            i = 20; 
            while (i > 0) { 
                m = applyv(max, m_values(sk));  
                if (m == 0) { 
                    notify_fail("You didn't have twenty levels of " +
                                "combat skills to lose!\n"); 
                    return 0;
                } 
                tmp = filter(sk, &operator(==)(,m)); 
                sk[m_indexes(tmp)[0]]--; 
                i--;
            } 
            map(m_indexes(sk), &setsk(, tp, sk));  
            write("Ok, you lost twenty levels of combat skills.\n"); 
        } 
    } 

    notify_fail("For some unknown reason you cannot join the cadets.\n"); 
    shadow = clone_object(GC_SHADOW);
    if (shadow->shadow_me(tp, GC_GUILD_TYPE, 
                              GC_GUILD_STYLE, 
                              GC_GUILD_NAME) != 1)
    {
        shadow->remove_shadow();
        return 0;
    }

    tp->setup_skill_decay(); 
    tp->clear_guild_stat(SS_LAYMAN);
    tp->set_guild_pref(SS_LAYMAN, GC_GUILD_TAX);

    if (str == "on") 
        tp->set_bit(GC_GROUP, GC_BIT); 
    else 
        tp->set_bit(GC_GROUP, GC_BIT2); 

    write("You sign on.\n"); 
    write("You are now a Cadet of Gelan!\n"); 
    say(QCTNAME(tp) + " signs on.\n"); 
    log_file("cadet", ctime(time()) + " " + tp->query_real_name() + " " + 
         (str == "again" ? "re-" : "") + "joined.\n"); 
    guildmaster->give_shoes(tp); 
    return 1;
}


int
choose(string str)
{
     string *sel, pri, sec;
     int prisel, secsel, old_prisel, 
         old_secsel, old_prinum, old_secnum, 
         pri_reset, sec_reset;
     object tp = this_player(); 

     if (!IS_GELAN_CADET(tp)) { 
         notify_fail("You are not a member of this guild.\n"); 
         return 0;
     } 

     notify_fail("Syntax: choose <primary> <secondary>\n" +
                 "Choose from: " +  
                 COMPOSITE_WORDS(m_indexes(gc_name_selected_map)) + ".\n"); 

     if (!stringp(str) || !strlen(str))  
         return 0;

     sel = explode(str, " "); 
     if (sizeof(sel) != 2) 
         return 0;

     pri = sel[0]; 
     sec = sel[1];

     if (pri == sec) { 
         notify_fail("You may not have the same primary and secondary " + 
                     "offensive skill.\n"); 
         return 0;
     } 

     prisel = gc_name_selected_map[pri];
     if (!prisel) {
          notify_fail("The offensive skill: " + pri + " is unrecognised.\n"); 
          return 0;
     } 

     secsel = gc_name_selected_map[sec];
     if (!secsel) { 
          notify_fail("The offensive skill: " + sec + " is unrecognised.\n"); 
          return 0;
     } 

     old_prisel = tp->query_skill(GC_SKILL_PRIMARY_WEAPON); 
     old_secsel = tp->query_skill(GC_SKILL_SECONDARY_WEAPON); 

     old_prinum = tp->gc_query_primary_skill_num();  
     old_secnum = tp->gc_query_secondary_skill_num(); 

     if (old_prisel) { 
         /* If the old primary selection is now the secondary 
            selection, it may be up to 45, otherwise 30. */ 
         if (old_prisel == secsel) 
             pri_reset = min(tp->query_skill(old_prinum), 45);  
         else 
             pri_reset = 30;  
         /* If the player gets a new primary selection, 
            reset the old one if necesssary */ 
         if ((old_prisel != prisel) && 
             (tp->query_skill(old_prinum) > pri_reset)) {  
             tell_object(tp, "Your " + tp->gc_query_primary_skill_name() + 
                             " skill is reset.\n"); 
             tp->set_skill(old_prinum, pri_reset); 
         } 
      } 

     if (old_secsel) { 
         /* If the old secondary selection is now the primary 
            selection, it may be up to 50, otherwise 30 */ 
         if (old_secsel == prisel) 
             sec_reset = 50;  
         else 
             sec_reset = 30; 
         /* If the player gets a new secondary selection, 
            reset the old one if necesssary */ 
         if ((old_secsel != secsel) && 
              (tp->query_skill(old_secnum) > sec_reset)) {   
              tell_object(tp, "Your " + tp->gc_query_secondary_skill_name() + 
                              " skill is reset.\n"); 
              tp->set_skill(old_secnum, sec_reset); 
         } 
     } 

     tp->set_skill(GC_SKILL_PRIMARY_WEAPON, prisel);  
     tp->set_skill(GC_SKILL_SECONDARY_WEAPON, secsel);  
     write("Your primary offensive skill is now: " + pri + ".\n" + 
           "Your secondary offensive skill is now: " + sec + ".\n");  
     tp->gc_init_title(); 
     return 1;
}


int
help(string str)
{
    if (str != "csign") 
        return 0;
 
    this_player()->more(read_file(GC_JOIN_INFO));  
    return 1;
}


int
ctitles(string str)
{
     string r;

     if (stringp(str)) { 
         notify_fail("Ctitles requires no argument.\n"); 
         return 0;
     } 

     write("Cadet titles are made of two parts: cadet type " +
          "and cadet level. Possible cadet types, depending on one's "+
          "primary offensive weapon are: " + 
          COMPOSITE_WORDS(m_values(GC_SELECTED_TITLE_MAP) - ({ "" })) + 
          ". Possible level titles, depending on a number of factors, " +
          "are, in ascending order: " + 
          COMPOSITE_WORDS(GC_LEVEL_TITLE_ARR) + ". " + 
          "Resulting full titles take forms such as `Senior Fistfighter " +
          "Cadet of Gelan.'\n"); 

    return 1;
}


int
cpermit(string str)
{
    if (!this_player()->query_wiz_level())  
        return 0;

    if (!stringp(str)) { 
        notify_fail("Syntax: cpermit <player>\n");  
        return 0;
    } 

    str = lower_case(str); 
    if (member_array(str, allowed_back) > -1) { 
        notify_fail("That player is already allowed back.\n"); 
        return 0;
    } 

    if (!SECURITY->exist_player(str)) { 
        notify_fail("No such player!\n"); 
        return 0;
    } 

    if (!SECURITY->valid_write(MASTER, this_player(), write_file)) { 
        notify_fail("You are not allowed to do that!\n"); 
        return 0;
    } 

    allowed_back += ({ str }); 
    log_file("cadet", capitalize(this_player()->query_real_name()) + 
                      " allowed " + str + " back.\n"); 
    save_object(GC_SAVE); 
    write("Ok.\n"); 
    return 1;
}


void
init()
{
    ::init();
    init_skill_raise();
    add_action(choose, "choose");
    add_action(csign, "csign");
    add_action(ctitles, "ctitles"); 
    add_action(help, "help"); 
    add_action(cpermit, "cpermit"); 
}

