
/* 
    the guildmaster mobile in the crystalline palace

    coder(s):   Glykron & Maniac

    history:
                20/1/03    fixed name reference bug              Maniac
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
//    name = lower_case(who->query_real_name());
    name = OB_NAME(who); 

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
    set_living_name("krom");
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
set_base_stat(SS_OCCUP, 300);
    set_skill(SS_WEP_SWORD, 100);
    set_skill(SS_WEP_POLEARM, 100);
    set_skill(SS_PARRY, 100);
    set_skill(SS_DEFENCE, 100);
    set_skill(REWARD, 6); 
    set_hp(100000);
    set_alignment(1000); 
    set_all_hitloc_unarmed(query_average_stat() / 4);
    set_calian_title("Guildmaster");
    add_prop(CONT_I_HEIGHT, 190); 
    add_prop(CONT_I_WEIGHT, 80000); 
    add_prop(CONT_I_VOLUME, 80000); 
    remove_prop(NPC_M_NO_ACCEPT_GIVE);
    add_prop(OBJ_M_NO_ATTACK, VBFC_ME("no_attack"));

    add_ask(({"weapon", "weapon of light", "transform", "light weapon"}),
              "say Ah, you must be asking about the Weapon of Light? Such a weapon " +
              "can be created here in our crystalline palace. The ancient magic of " +
              "our palace is strong enough to suppress and convert the dark magic that " +
              "the evil Kroug has invested into the weapons of his kroug commanders. Slay " +
              "a kroug command and bring his weapon of darkness to the Room of Light and " +
              "you will witness for yourself the power of that room.\n", 1);
              
    add_ask(({"weapon of darkness", "dark weapon"}),
              "say They are magical weapons that Kroug created and given to some of his " +
              "most elite warriors.\n", 1);
              
    add_ask(({"room","room of light","light room"}),
              "say You're looking for the Room of Light? Go walk around the palace. " +
              "You can't miss it - it's really bright!\n", 1);

    add_ask(({"palace","magic","ancient magic","crystalline palace"}),
              "say This palace is full of ancient magic. It is the home of " +
              "the Calian Warriors. Go read the Calian Chronicles in " +
              "the Tower of Realms of Sparkle if you want to know more " +
              "about the Palace. If you want to learn about the " +
              "Calian Warriors, simply take a good <look> " +
              "here in this room.\n", 1);

    add_ask(({"kroug", "krougs"}),
              "say Kroug was a dreadful sorcerer who used foul magic to " +
              "corrupt everyone and everything around him. Our Lady Caliana " +
              "fought and defeated him, together with Hurn. You can <look> around " +
              "to learn more.\n",1);
              
    add_ask(({"caliana","lady caliana"}),
              "say She was our leader. By her virtues do we live today. " +
              "You can <look> here in this room to learn more about her.\n", 1);
    
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
