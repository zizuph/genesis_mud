/* File : deorl.c
 *
 * A wounded elf. Part of the quest.
 *
 * Blizzard, 02/2003
 *
 */

#pragma strict_types

#include "/d/Krynn/common/defs.h"
#include <ss_types.h>
#include <wa_types.h>
#include <stdproperties.h>
#include <macros.h>
#include <options.h>
#include "../local.h"

inherit M_FILE
inherit "/d/Krynn/std/equip";

public string ask_help();
public string ask_companion();
public string ask_trap();
public string ask_qualthas();
public void   do_answer(string what, object who);

#define FOUND_DEORL      "_found_deorl"

object weapon;

void
create_krynn_monster()
{
    
    set_name("deorl");
    add_name("_wounded_elf_");
    set_race_name("elf");
    set_adj("wounded");
    set_short("wounded elf");
    set_pshort("wounded elves");
    set_long("This elf is probably one of the lost elven scouts. " +
        "He seems to be seriously wounded.\n");
    set_gender(0);
    set_alignment(400);
    set_knight_prestige(-100);
    
    set_stats(({ 50, 75, 60, 70, 65, 70 }));

    set_skill(SS_WEP_SWORD, 40);
    set_skill(SS_PARRY, 30);
    set_skill(SS_DEFENCE, 30);
    set_skill(SS_AWARENESS, 80);
    set_skill(SS_BLIND_COMBAT, 30);
    set_skill(SS_HIDE, 100);
    
    add_prop(CONT_I_WEIGHT, 40000);
    add_prop(CONT_I_HEIGHT, 175);
    add_prop(NPC_I_NO_RUN_AWAY, 1);
    add_prop(LIVE_M_NO_ACCEPT_GIVE, 1);
    add_prop(LIVE_I_ATTACK_THIEF, 0);
    add_prop(LIVE_I_NEVERKNOWN, 1);
    add_prop(LIVE_I_SEE_DARK, 1);
    add_prop(LIVE_S_EXTRA_SHORT, " laying in the bushes");

    set_hp(400);

    set_default_answer(VBFC_ME("def_answer"));
    add_ask(({ "companion", "about companion", "sarist", "about sarist",
        "Sarist", "about Sarist", "draconian", "draconians" }), 
        VBFC_ME("ask_companion"), 1);
    add_ask(({ "poison", "aid", "heal", "cure" }), VBFC_ME("ask_help"), 1);
    add_ask(({ "help", "task", "about task"}), VBFC_ME("ask_help"), 1);
    add_ask(({ "trap", "ambush", "about trap" }), VBFC_ME("ask_trap"), 1);
    add_ask(({ "fight", "about fight" }), VBFC_ME("ask_trap"), 1);
    add_ask(({ "battle", "about battle" }), VBFC_ME("ask_trap"), 1);
    add_ask(({ "qualthas", "about qualthas" }), VBFC_ME("ask_qualthas"), 1);
    add_ask(({ "deorl", "Deorl", "about deorl", "about Deorl" }),
        "say Yes, that is my name.", 1);
    add_ask("name", "say Does it matter now? I will die soon... " +
        "I am Deorl.", 1);
         
    seteuid(getuid(TO));
    equip(({ WEP + "elongsword", ARM + "lchain", ARM + "elven_boots" }));
}

string
def_answer()
{
    command("emote tries to catch a breath.");
    return "";
}

int 
query_option(int opt)
{
    if ( opt == OPT_UNARMED_OFF )
       return 1;
}

/*  
 * Function:    react_attack  
 * Description: React to an attack. This called by alarm from  
 *              the function "attacked_by" below.  
 * Arguments:   object attacker  -  the attacker.  
 */
void 
react_attack(object attacker)
{
    if (!CAN_SEE_IN_ROOM(TO) || !CAN_SEE((TO), attacker))
    {
        command("say I pity you, even now you do not dare to face me...");
        command("choke"); 
    }
    else
    {
        command("emote laughs silently, and then chokes...");
        command("say You, bastard.");
    }
    
}

/*  
 *   Function:     attacked_by  
 *   Description:  Called by the combat system when a living is  
 *                 attacked. See "sman attacked_by" for documentation.  
 *   Arguments:    object attacker  -  the attacking living.  
 */
public void
attacked_by(object attacker)
{     
    remove_prop(LIVE_S_EXTRA_SHORT);
    
    ::attacked_by(attacker);
    set_alarm(1.0, 0.0, &react_attack(attacker));
}

/* Function name: notify_death
 * Description  : Notify onlookers of my death
 * Arguments    : object killer - the object that killed me
 */
void
notify_death(object killer)
{
    if ( killer == this_object() )
    {
        tell_room(E(TO), "The wounded elf died.\n");
        return;
    }
    
    ::notify_death(killer);
}

/* Function name   : ask_help
 * Description     : answer to question about help
 */
public string
ask_help()
{
    set_alarm(1.0, 0.0, &do_answer("help", TP));
    return "";
}

/* Function name   : ask_trap
 * Description     : answer to question about trap
 */
public string
ask_trap()
{
    set_alarm(1.0, 0.0, &do_answer("trap", TP));
    return "";
}

/* Function name   : ask_companion
 * Description     : answer to question about companion
 */
public string
ask_companion()
{
    set_alarm(1.0, 0.0, &do_answer("companion", TP));
    return "";
}

/* Function name   : ask_qualthas 
 * Description     : answer to question about qualthas
 */
public string
ask_qualthas()
{
    set_alarm(1.0, 0.0, &do_answer("qualthas", TP));
    return "";
}
    
/* Function name   : do_answer
 * Description     : answers to the questions
 * Arguments       : string what  - topic
 *                   object who   - the player who asked
 */
public void
do_answer(string what, object who)
{
    if ( !objectp(who) || E(who) != E(TO))
    {
        return;   /* We wont speak if the player is gone */
    }
    
    switch (what)
    {
    case "help":
        command("choke");
        command("say No... Do not worry about me, but...");
        command("say But maybe you could help my companion.");

    break;
    case "companion":
        command("say Me and Sarist were following a group of draconians, " +
            "watching them from the forest.");
        command("say But they were aware of that... and set a trap.");
    break;
    case "trap":
        command("say They stopped at the edge of the forest for some reason. " +
            "There were only a few of them... We decided to put an end to " +
            "their lives... We could do it quickly...");
        command("choke");
        set_alarm(4.0, 0.0, &do_answer("trap1", who));            
    break;
    case "trap1":
        command("say Two of them died quickly, turning into stones, as our " +
            "arrows reached them.");
        command("say It seemed to be an easy task, even when the rest " +
            "rushed in our direction...");
        set_alarm(3.0, 0.0, &do_answer("trap2", who));
    break;        
    case "trap2":
        command("say Before they reached the trees, another few fell, " +
            "dissolving into pools of acid or turning into " +
            "stones...");
        command("say Then we moved to finish off the remaining ones... " +
            "That was a mistake.");
        command("emote tries to catch a breath.");
        set_alarm(4.0, 0.0, &do_answer("trap3", who));
    break;
    case "trap3":
        command("say In the moment we crossed our swords... Something " +
            "happened. There was one more...");
        set_alarm(2.0, 0.0, &do_answer("trap4", who));
    break;
    case "trap4":
        command("say The hooded one... but we did not see him before. That " +
            "was an aurak. He remained invisible when we attacked and " +
            "probably he was the reason those dracs knew about us.");
        command("emote curses.");
        set_alarm(4.0, 0.0, &do_answer("trap5", who));
    break;
    case "trap5":
        command("say The aurak pointed his clawed hand at Sarist, who fell " +
            "to the ground.");
        command("say I paused for a moment... and it was enough for one of " +
            "draconians to slash at me with a poisoned blade.");
        set_alarm(3.0, 0.0, &do_answer("trap6", who));
    break;
    case "trap6":
        command("say I managed to reach the trees and lose the hunters.");
        command("say I have to warn Qualthas... but this poison makes " +
            "me unable to move.");
        set_alarm(3.0, 0.0, &do_answer("trap7", who));
    break;
    case "trap7":
        command("say Please, go and report this to our leader... That aurak " +
            "seems to be very powerful. We have to prepare...");
        command("emote chokes.");
        set_alarm(3.0, 0.0, &do_answer("trap8", who));
    break;
    case "trap8":
        command("say And Sarist... They probably took him to Pax Tharkas. " +
            "Maybe we... Qualthas still can help him.");
        command("caugh");
        set_alarm(3.0, 0.0, &do_answer("trap9", who));
    break;
    case "trap9":
        command("say Otherwise they can ..");
        command("emote suddenly chokes and his eyes become empty.");
        TO->set_hp(0);
        who->add_prop(FOUND_DEORL, 1);
        TO->do_die(TO);
    break;
    case "qualthas":
        command("say Qualthas has sent you? We still might need help.");
    break;
    default:
        command("say I do not quite understand...");
    break;
    
    }
    
}

int query_hp()
{
    int my_hp = ::query_hp();
    if ( my_hp > 200 )
        heal_hp(200 - my_hp);
    return ::query_hp();
}

