
/* 
    the guildmaster mobile in the crystalline palace

    coder(s):   Glykron & Maniac

    history:
                16/07/97   Added reply_hand() question
                           to support the Calian Sup. 
                           Guru Quest                            Khail
                26/2/97    applicants ask removed, since  
                           capp does the job now.                Maniac 
                21/3/96    deal with given dark objects          Maniac
                28/9/95    can now be attacked by smart krougs   Maniac
                11/8/95    recruiters can now query krom
                           as to whether applicants are 
                           logged in.                      Maniac
                17.11.94   Name constant and more descr    Maniac
                4. 5.93    created                         Glykron
                29. 8.93    calian object inherited        Glykron

*/

#include <stdproperties.h>
#include <macros.h>
#include <ss_types.h>
#include <composite.h>

/* Include defines for the sup. guru quest. */
#include "/d/Calia/eldoral/guru_quest.h"

#define NO_ATTACK_MSG "Caliana will not allow anyone to attack " \
                      + "her Guildmaster.\n"

#include "defs.h"
#include RECRUITER_HEADER
#include COUNCIL_HEADER
#pragma save_binary

inherit CALIAN;


/* Called from vbfc. Let smart krougs attack him only */
mixed
no_attack()
{
    object tp = this_player();

    if (!objectp(tp))
        return NO_ATTACK_MSG;

    if (tp->query_smart_kroug())
        return 0;

     return NO_ATTACK_MSG;
}


/* If people want to give stuff to him, fine unless they are
   trying to make the room dark permanently. */
void
give_check(object ob, object from)
{
     if (ob->query_prop(OBJ_I_LIGHT) < 0) { 
         command("emote swallows the " + ob->short() + ".");
         command("burp"); 
         command("emote goes `Yum!'");
         command("grin " + OB_NAME(from)); 
         ob->remove_object();
     }
}


void
enter_inv(object ob, object from)
{
    ::enter_inv(ob, from);
    set_alarm(1.0, 0.0, &give_check(ob, from)); 
}


/*
 * Function name: reply_hand
 * Description  : Handles responses when asked about the hand of a
 *                king for the sup. guru quest.
 *                Uses sup. guru quest defines
 *                    LIVE_I_GURU_QUESTING
 *                    C_GURU_DRAGON
 *                    C_GURU_KROM
 * Arguments    : n/a
 * Returns      : A string that will be his response as a command.
 */
public string
reply_hand()
{
    object who;
    string name,
           king;
    int state;

    seteuid(getuid());

    who = this_player();
    name = lower_case(who->query_real_name());

  /*Do nothing if the player isn't a calian. */
    if (!IS_GURU_CALIAN(who))
        return "";

  /* If no state, player hasn't been to the dragon who gives */
  /* the quest yet, so don't say anything, other than a hint */
  /* that there is something to say. */
    if (!(state = who->query_prop(LIVE_I_GURU_QUESTING)))
    {
        command("smile mysteriously");
        return ("whisper " + name + " That is a " +
            "story for another time.");
    }

  /* Has the player talked to Krom before? */
    if (state & C_GURU_KROM)
    {
        return ("whisper " + name + " Sorry, I've " +
            "already told you all I can.");
    }

  /* State of C_GURU_DRAGON means the player's talked to the dragon, */
  /* nothing else. */
    if (state & C_GURU_DRAGON)
    {
        command("ponder");
        king = GURU_BRAIN->query_king();
        command("whisper " + name + " I've heard stories " +
            "about something called the King's Hand. Some sort of " +
            "gauntlet that held magic powers, if you believe that " +
            "kind of stuff.");
        command("hmm");
        command("whisper " + name + " So far as I can " +
            "recall, it was never really owned by a king, I don't " +
            "know where the name originated, but it was supposed " +
            "to have last been held by someone named " + king + 
            ". I believe...the story goes that he died when he " +
            "tried using the King's Hand, but discovered at a " +
            "bad time that its powers had been used up.");
        command("chuckle");
        who->add_prop(LIVE_I_GURU_QUESTING, state | C_GURU_KROM); 
        return ("whisper " + name + " If that's true, " +
            "you should think about finding a way to recharge it " +
            "if you're going searching for it.");
    }
    return "";
}


public string
reply_recharge()
{
    object who;
    string name;
    int state;

    who = this_player();
    name = lower_case(who->query_real_name());

  /*Do nothing if the player isn't a calian. */
    if (!IS_GURU_CALIAN(who))
        return "";

  /* If no state, player hasn't been to the dragon who gives */
  /* the quest yet, so don't say anything, other than a hint */
  /* that there is something to say. */
    if (!(state = who->query_prop(LIVE_I_GURU_QUESTING)))
    {
        command("smile mysteriously");
        return ("whisper " + name + " That is a " +
            "story for another time.");
    }

  /* State of C_GURU_DRAGON means the player's talked to the dragon, */
  /* nothing else. */
    if (state & C_GURU_DRAGON)
    {
        return "whisper " + name + " Unfortunately, I don't know " +
            "anything about recharging the King's Hand, nor who " +
            "might know, off the top of my head.";
    }
    return "";
}


void
create_calian()
{
    string *old_adjs = ({ });

    if (!IS_CLONE)
        return;

    set_name("krom");
    add_name("guildmaster");
    set_race_name("human");
    set_gender(G_MALE);
    old_adjs = query_adjs();
    if (sizeof(old_adjs))
        remove_adj(old_adjs); 
    set_adj(({"grim-faced", "tall"}));
    set_long("He is a grim-faced human dressed in blue. This man " +
             "is an old, battle-hardened and wise veteran of " +
             "many wars, and was one of the greatest heroes " +
             "to survive the Battle with Kroug.\n"); 
    set_base_stat(SS_INT, 200);
    set_base_stat(SS_WIS, 200);
    set_base_stat(SS_DIS, 200);
    set_base_stat(SS_STR, 200);
    set_base_stat(SS_DEX, 200);
    set_base_stat(SS_CON, 200);
    set_base_stat(SS_OCCUP, 200);
    set_skill(SS_WEP_SWORD, 100);
    set_skill(SS_WEP_POLEARM, 100);
    set_skill(SS_PARRY, 100);
    set_skill(SS_DEFENCE, 100);
    set_skill(REWARD, 6); 
    set_hp(100000);
    set_all_hitloc_unarmed(query_average_stat() / 4);
    set_calian_title("Guildmaster");
    add_prop(CONT_I_HEIGHT, 190); 
    add_prop(CONT_I_WEIGHT, 80000); 
    add_prop(CONT_I_VOLUME, 80000); 
    remove_prop(NPC_M_NO_ACCEPT_GIVE);
    add_prop(OBJ_M_NO_ATTACK, VBFC_ME("no_attack"));
    add_prop(OBJ_M_NO_MAGIC_ATTACK, NO_ATTACK_MSG);

#ifdef GURU_OPEN
    add_ask(({"hand of a king", "about the hand of a king",
        "about hand of a king", "king's hand",
        "about king's hand", "about the king's hand",
        "hand of the king", "about the hand of the king",
        "about hand of the king"}), VBFC_ME("reply_hand"), 1);
    add_ask(({"recharge", "about recharging","recharge gauntlet",
        "recharging gauntlet", "about recharging gauntlet"}),
        VBFC_ME("reply_recharge"), 1);
#endif

}
