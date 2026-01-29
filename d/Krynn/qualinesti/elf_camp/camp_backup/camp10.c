/* camp10.c
 * An elven encampment in the Qualinesti forest.
 *
 * Blizzard, 01/2003
 *
 *
 * Note by Navarre, November 22th 2005:
 *
 * This room was made so the super sword could be obtained through repeating
 * the quest. Accordingly to the original documentation of the quest.
 * It was not intended to be obtained more than when you solve the quest the
 * first time.
 */

#include <macros.h>
#include "/d/Krynn/common/defs.h"
#include "../local.h"

inherit "/lib/unique";

inherit CAMPBASE;

public void   final_sequence(string what, object who);
void          reset_seq();
void          reward_me(object who);

object leader, elf1, elf2, elf3;
int gSequence = 0;

#define FOUND_DEORL       "_found_deorl"
#define FOUND_SWORD       "_found_sword"
#define LOST_SCOUTS       "_lost_scouts"
#define BEAT_ELF          "_beat_elf"
#define WARN_QUALTHAS     "_warn_qualthas"
#define I_RELEASED_ELF    "_i_released_elf"
#define ELF_SAFE          "_elf_safe"
#define SPOKEN_WITH_DWARF "_spoken_with_dwarf"

void
reset_qualinesti_room()
{
    int i = random(10);

    if (!leader)
    {   
        leader = clone_object(NPC + "qualthas");
        leader->move(TO);
    }        
    if (!elf1)
    {
        elf1 = clone_object(STD + "elf_base");
        elf1->move(TO);
    }
    if (!elf2)
    {
        elf2 = clone_object(STD + "elf_base");
        elf2->move(TO);
    }
    if ( i > 4 )
    {
        if (!elf3)
        {
            elf3 = clone_object(STD + "elf_base");
            elf3->move(TO);
        }
    }

}

void
create_camp()
{
    
    OUTSIDE;
    
    add_exit(CDIR + "camp2.c", "west", 0, 1);
    add_exit(CDIR + "camp3.c", "northwest", 0, 1);
    add_exit(CDIR + "camp4.c", "north", 0, 1);
    add_exit(CDIR + "camp5.c", "northeast", 0, 1);
    add_exit(CDIR + "camp6.c", "east", 0, 1);
    add_exit(CDIR + "camp7.c", "southeast", 0, 1);
    add_exit(CDIR + "camp8.c", "south", 0, 1);
    add_exit(CDIR + "camp9.c", "southwest", 0, 1);
    
    reset_qualinesti_room();
    
}

public void 
final_sequence(string what, object who)
{   
    object elf, griffon, sword;
    
    if ( !objectp(who) || E(who) != TO || !present("qualthas",TO) )
    {
        return;   // We wont speak if the player is gone 
    }
    
    if ( leader = present("qualthas", TO) )
    {
        switch (what)
        {
        case "seq1":
            if ( !present("tull", TO) && gSequence == 0 )
            {
                leader->command("say What? You say you found Sarist and " +
                    "have helped him to escape? So where is he?");
                who->catch_msg(QCTNAME(leader) + " peers at you.\n");
                say(QCTNAME(leader) + " peers at " + QTNAME(who) + ".\n", who);

                gSequence = 1;
                set_alarm(2.0, 0.0, &final_sequence("seq2", who));
      // Reset the sequence if it was stopped for some reason
                set_alarm(40.0, 0.0, &reset_seq());
            }
            else if ( gSequence == 1 )
            {
                return;
            }
        break;
        case "seq2":
            leader->command("say I would like to belive this is true, but " +
                "can you prove it? It is not ...");
            tell_room(TO, "A strange whistling sound may be heard from " +
                "above. " + QCTNAME(leader) + " pauses and stares into " +
                "the sky, shielding his eyes with a hand.\n");
            tell_room(TO, "Elves, sitting at campfires, raise their heads " +
                "and smile. Intrigued, you look up.\n");
            set_alarm(5.0, 0.0, &final_sequence("seq3", who));
        break;
        case "seq3":
            tell_room(TO, "Suddenly, a large griffon lands in the middle " +
                "of the camp. You notice there is an elf sitting on " +
                "its back.\n");
        
            if ( !present("griffon", TO) )
            {
                griffon = clone_object(NPC + "griffon");
                griffon->move(TO);
            }
        
            if ( !present("tull", TO) )
            {
                elf = clone_object(NPC + "tull");
                elf->move(TO); 
                tell_room(TO, "A tall long-haired male elf jumps off " +
                    "the griffon's back.\n");
            }
    
            set_alarm(5.0, 0.0, &final_sequence("seq4", who));
        break;
        case "seq4":        
            tell_room(TO, "The tall long-haired male elf speaks with " + 
                QTNAME(leader) + " for a moment.\n");
            set_alarm(6.0, 0.0, &final_sequence("seq5", who));
        break;
        case "seq5":
            leader->command("emote smiles slightly.");
            tell_room(TO, "The tall long-haired male elf nods.\n");
            leader->command("say It seems we have a proof.");
            set_alarm(4.0, 0.0, &final_sequence("seq6", who));
        break;
        case "seq6":  
            who->catch_msg("The tall long-haired male elf says to you: " +
                "I am Tull Nightbreeze. I was asked to deliver this to " +
                "you. A gift from Sarist.\n");
            tell_room(TO, "The tall long-haired male elf says to " + 
                QTNAME(who) + 
                ": I am Tull Nightbreeze. I was asked to deliver " +
                "this to you. A gift from Sarist.\n", who); 
     
        // We give the sword to the player only for the first time.
            if ( !who->test_bit("krynn", 1, 19) )
            {
                sword = clone_object(WEP + "elven_blade");
                sword->move(who, 1);
                who->catch_msg("The tall long-haired male elf gives an " +
                    "azure rune-etched longsword to you.\n");
                 tell_room(TO, "The tall long-haired male elf gives an " +
                    "azure rune-etched longsword to " + QTNAME(who) + 
                    ".\n", who);
            }
            else
            {
         // Otherwise we give the crap sword
                sword = clone_object(WEP + "crap_sword");
                sword->move(who, 1);
                
                who->catch_msg("The tall long-haired male elf gives you " +
                    "a sword.\n");
                tell_room(TO, "The tall long-haired male elf gives " +
                    "something to " + QTNAME(who) + ".\n", who);    
            }
            
            tell_room(TO, "The tall long-haired male elf bows.\n");
   
   // set bit, give exp 
            gSequence = 0;        
            reward_me(who);
   // continue sequence...         
   
            set_alarm(3.0, 0.0, &final_sequence("seq7", who)); 
        break;
        case "seq7":
            tell_room(TO, "The tall long-haired male elf says to " + 
                QTNAME(leader) + ": I will depart now.\n");
            leader->command("emote nods.");
            leader->command("say Farewell, friend.");
            set_alarm(4.0, 0.0, &final_sequence("seq8", who));
        break;
        case "seq8":
            tell_room(TO, "The tall long-haired male elf mounts the " +
                "griffon. It takes off and after a moment dissapears " +
                "from your sight.\n");

            if ( elf = present("tull", TO) )
                elf->remove_object();
            if ( griffon = present("griffon", TO) )
                griffon->remove_object();
                
            set_alarm(3.0, 0.0, &final_sequence("seq9", who)); 
        break;
        case "seq9":                
            who->catch_msg(QCTNAME(leader) + " says to you: We are very " +
                "grateful for your help. The Speaker of the Suns also " +
                "has been notified about your actions.\n");
            tell_room(TO, QCTNAME(leader) + " says to " + QTNAME(who) + 
                ": We are " +
                "very grateful for your help. The Speaker of the Suns also " +
                "has been notified about your actions.\n", who);
            set_alarm(2.0, 0.0, &final_sequence("seq10", who));
        break;
        case "seq10":
            who->catch_msg(QCTNAME(leader) + " says to you: From now on, " +
                "you are welcome to Qualinost if your path leads you " +
                "there. But for now feel free to rest in our camp.\n\n");
            tell_room(TO, QCTNAME(leader) + " says something more to " + 
                QTNAME(who) + ".\n", who);
              
        break;        
        }

    }    

}

void 
reset_seq()
{
    if ( gSequence == 1 )
        gSequence = 0;
}

/* Function    : calculate_experience
 * Description : XP calculation function 
 */ 
void
calculate_experience(object who)
{
    int xp_base = 19000;

    if( who->test_bit("krynn", 1, 19) )
    {
        who->catch_msg("There is no experience second time you " +
            "solve this quest.\n");
        return;
    }

    xp_base -= (who->query_prop(FOUND_DEORL)       ? 0 : 3000);
    xp_base -= (who->query_prop(FOUND_SWORD)       ? 0 : 2000);
    xp_base -= (who->query_prop(WARN_QUALTHAS)     ? 0 : 2000);
    xp_base -= (who->query_prop(SPOKEN_WITH_DWARF) ? 0 : 2000);
    xp_base -= (who->query_prop(BEAT_ELF)          ? 2000 : 0);

    who->catch_msg("You feel more experienced.\n");
        tell_room(E(who), QCTNAME(who) + " looks more experienced.\n", who);

    who->add_exp_quest(xp_base);                         
 // set bit 
    who->set_bit(1, 19);

    K_QUEST_LOG("quest", "Lost scouts - good", who, xp_base);
}


void
remove_quest_props(object who)
{
    if (who->query_prop(LOST_SCOUTS))
        who->remove_prop(LOST_SCOUTS);

    if (who->query_prop(SPOKEN_WITH_DWARF))
        who->remove_prop(SPOKEN_WITH_DWARF);
        
    if (who->query_prop(WARN_QUALTHAS))
        who->remove_prop(WARN_QUALTHAS);

    if (who->query_prop(FOUND_DEORL))
        who->remove_prop(FOUND_DEORL);

    if (who->query_prop(FOUND_SWORD))
        who->remove_prop(FOUND_SWORD);

    if (who->query_prop(BEAT_ELF))
        who->remove_prop(BEAT_ELF);

    if (who->query_prop(I_RELEASED_ELF))
        who->remove_prop(I_RELEASED_ELF);

    if (who->query_prop(ELF_SAFE))
        who->remove_prop(ELF_SAFE);

}


void
reward_me(object who)
{
    calculate_experience(who);
    remove_quest_props(who);

}

        