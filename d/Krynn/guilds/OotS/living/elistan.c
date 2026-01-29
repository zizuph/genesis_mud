#include <stdproperties.h>
#include <wa_types.h>
#include <ss_types.h>
#include <macros.h>
#include <composite.h>
#include "/d/Krynn/common/defs.h"
#include "/d/Krynn/tharkadan/local.h"
#include "/d/Krynn/guilds/OotS/defs.h"

inherit "/d/Krynn/std/monster";

#define WEP_STAFF "/d/Ansalon/balifor/flotsam_forest/obj/weapon/staff"
#define KIRIJOLITH      "_suitable_for_kirijolith"
#define MISHAKAL        "_suitable_for_mishakal"
#define BRANCHALA       "_suitable_for_branchala"
#define DIALOG_PROP     "_elistan_currently_dialoguing"
#define NEIDAR_MANAGER  ("/d/Ansalon/guild/neidar/lib/neidar_member_manager")
#define IS_DOOMSEEKER(p1)   NEIDAR_MANAGER->query_is_doomseeker(p1)

static int dialog_alarm;
public object dialog_target;
static mapping speak;

public varargs int
handle_timed_messages(object player, mapping messages, int cycle)
{
    if (objectp(dialog_target))
    {
        if (!present(dialog_target, environment(this_object())))
        {
            command("emote stops his teachings as " +QTNAME(dialog_target)+
               " leaves.");
            // Rude to leave like that while someone is lecturing.
            remove_alarm(dialog_alarm);
            dialog_target = 0;
        }
        
        if (objectp(dialog_target) && !cycle)
        {
            command("emote continues his teachings, ignoring the " +
                    "interruption.");
            // Interrupting conversation, thats not very nice.
            return 0;
        }
        
        if (!objectp(dialog_target))
            return 1;
    }
    
    if (!CAN_SEE(this_object(), player))
    {
        command("say If you reveal yourself so I can see you, I can " +
                "tell you more of my learnings.");
        remove_alarm(dialog_alarm);
        dialog_target = 0;
        return 0;
    }
    
    if (!mappingp(messages) || !m_sizeof(messages))
        return 1;
    
    // Deliver the message
    if (cycle)
        command(messages[cycle][1]);
    
    dialog_target = player;
    cycle++;
    
    if (member_array(cycle, m_indexes(messages)) < 0)
    {
        remove_alarm(dialog_alarm);
        dialog_target = 0;
        return 1;
    }
    
    dialog_alarm = set_alarm(messages[cycle][0], 0.0,
                     &handle_timed_messages(player, messages, cycle));
}

void
create_krynn_monster()
{
    if(!IS_CLONE)
	return;

    set_name("elistan");
    set_living_name("elistan");
    set_title("of Haven, True Believer of the Old Gods and Disciple " +
              "of Paladine");
    set_race_name("human");
    set_adj("philosophical");
    add_adj("white-bearded");
    set_gender("G_MALE");
    set_long("Before you stands a white-bearded human with thinning " +
         "brown-gray hair and striking ice-blue eyes. While gaunt and " +
         "thin from illness and poor treatment in the mines of Pax " +
         "Tharkas, he stands tall - radiating confidence and wisdom. " +
         "Around his neck you notice a platinum medallion with the " +
         "symbol of a Dragon, an ancient symbol of the Old Gods of " +
         "Krynn.\n");

    set_stats(({89,136,136,136,136,89,89}));
    set_hp(query_max_hp());

    set_skill(SS_WEP_CLUB, 50);
    set_skill(SS_DEFENCE, 100);
    set_skill(SS_PARRY, 100);
    set_skill(SS_AWARENESS, 80);
    set_skill(SS_FORM_ENCHANTMENT, 100);
    add_prop(CONT_I_HEIGHT, 185);
    add_prop(CONT_I_WEIGHT, 69000);
    add_prop(OBJ_I_RES_MAGIC, 100);

    set_alignment(1200);
    set_knight_prestige(-2000);
    set_act_time(20);
    add_act("emote looks at you with his striking ice-blue eyes.");
    add_act("emote ponders the teachings of the Old Gods in the Disks " +
        "of Mishakal."); 
    add_act("say The flight from Pax Tharkas has been hard on the people. " +
        "Here in the vale we can rest, but we will soon need to continue " +
        "our travels south.");
    add_prop(OBJ_M_NO_ATTACK,"This man radiates an aura of power that " +
         "stops you from attacking him.\n");
    add_prop(NPC_I_NO_RUN_AWAY,1);

    set_default_answer(VBFC_ME("default_answer"));

    add_ask(({"old gods","gods"}),VBFC_ME("gods_hint"));
    add_ask(({"disks","disks of mishakal"}),VBFC_ME("disks_hint"));
    add_ask(({"teach me","teach","teach me of the old gods","discovered",
              "recently discovered",
              "teach me of the holy order of the stars"}),
         VBFC_ME("teach_hint"));
    add_ask(({"'kiri-jolith' / 'kirijolith' / 'kirijolith\'s' 'test' [of] 'faith'","'test' [of] 'faith'"}), VBFC_ME("test_hint"));
    add_ask(({"holy order of the stars"}),VBFC_ME("oots_hint"));
    add_ask(({"branchala"}),VBFC_ME("branchala_hint"));
    add_ask(({"habbakuk"}),VBFC_ME("habbakuk_hint"));
    add_ask(({"kiri-jolith", "kiri jolith"}),VBFC_ME("kirijolith_hint"));
    add_ask(({"paladine"}),VBFC_ME("paladine_hint"));
    add_ask(({"mishakal"}),VBFC_ME("mishakal_hint"));
    add_ask(({"majere"}),VBFC_ME("majere_hint"));
    add_ask(({"join","join holy order of the stars","join old gods",
              "join guild"}),VBFC_ME("gods_hint"));

    add_ask(({"pax tharkas","flight","people","illness"}),
        VBFC_ME("paxtharkas_hint"));
    add_ask(({"heroes"}),
      "say Aye, a strange band of heroes came to the rescue of the " +
      "prisoners in Pax Tharkas! They have left to try and find safe " +
      "passage for the refugees through the mountains to the south.", 1);
    add_ask(({"task","quest"}),
      "say I have no grand quest for you, although if you want to learn " +
      "more I am happy to teach you what I have recently discovered if " +
      "you are interested?", 1);
    add_ask(({"medallion","platinum medallion"}),
        VBFC_ME("medallion_hint")); 

    trig_new("%w 'introduces' %s","react_to_intro");

    seteuid(getuid());
}

void
arm_me()
{
    seteuid(getuid(TO));
    // clone_object(WEP_STAFF)->move(TO,1);
    command("wield all");

}

void
react_to_intro(string who,string garbage)
{
    set_alarm(2.0,0.0,"return_intro",who);
}

void
return_intro(string who)
{
    who = L(who);
    if (P(who,E(TO)))
    {
        command("introduce myself");
    }
}

string
default_answer()
{
    if (!handle_timed_messages(this_player()))
        return C(COMPOSITE_LIVE(TO))+ " is currently conversing with " +
           "someone else. You should wait until he is finished.\n";

    if(random(2))
    {
        command("ponder");
        command("say I don't have an answer for you on that.");
        command("say There is still a lot I need to learn from the " +
                "Disks of Mishakal.");
        return "";
    }
    else if(random(2))
    {
        command("smile thought");
        command("say I think that is a question best answered through " +
           "your own deliberations.");
        return "";
    }

    command("emote contemplates the question.");
    command("say A good question...");
    command("say Although I have no answer to it for you.");
    return "";
}

string
test_hint()
{
    if (!handle_timed_messages(this_player()))
        return C(COMPOSITE_LIVE(TO))+ " is currently conversing with " +
           "someone else. You should wait until he is finished.\n";

    if(!TP->query_prop(KIRIJOLITH))
    {
        command("say Kiri-Jolith's Test of Faith? According to the " +
           "Disks of Mishakal it is the rite of passage for those who " +
           "wish to join his priesthood as a Cleric of the Sword of " +
           "Justice, or for those Knights of Solamnia who wish to join " +
           "his Order of Clerics.");
        return "";
    }

    speak = ([
        1 : ({ 0.5, "say Those who aspire to be accepted by Kiri-Jolith " +
                  "must undertake a Test of Faith that demonstrates " +
                  "both courage and divine trust."}),
        2 : ({ 1.0, "ponder"}),
        3 : ({ 3.0, "say At least that is what the Disks of Mishakal " +
                    "hint at. To be honest, I am not entirely sure what " +
                    "that actually means or what you need to do..."}),
        4 : ({ 3.0, "say Although there is an obscure passage that " +
                    "translates to 'Devotions at dawn at heavenly " +
                    "heights'... or something along those lines."}),
        5 : ({ 4.0, "smile sheepish"}),
        6 : ({ 2.0, "say I am afraid beyond those lines I am of little " +
                    "further assistance."}),
        7 : ({ 2.0, "say Gods can be quite obscure at times can't they?"}),
        8 : ({ 3.0, "chuckle"}),
        9 : ({ 3.0, "say Paladine's blessings in your Test of Faith!"}),
    ]);
    
    handle_timed_messages(this_player(), speak);

    TP->add_prop(KIRIJOLITH, 2);

    return "";
}

string
teach_hint()
{
    if (!handle_timed_messages(this_player()))
        return C(COMPOSITE_LIVE(TO))+ " is currently conversing with " +
           "someone else. You should wait until he is finished.\n";

    if (IS_OOTS(TP))
    {
        command("say Beyond what inspiration I have provided you already, " +
           "I can also teach you skills that you can <learn> or <improve>.");
        return "";
    }

    TP->catch_msg(QCTNAME(TO)+ " smiles warmly and begins teaching you " +
         "what he has learnt of the Old Gods...\n\n");
    tell_room(E(TO), QCTNAME(TO)+ " smiles warmly and begins teaching " +
         QTNAME(TP)+ " what he knows of the Old Gods...\n", ({ TP }), TO);

    if (TP->query_alignment() < 600)
    {
        TP->catch_msg("You listen to " +QTNAME(TO)+ " for a little while " +
          "but quickly lose interest. The teachings of the Old Gods of " +
          "Light do not align with your thinking.\n");
        return "";
    }

    if (strlen(TP->query_guild_name_lay()))
    {
        TP->catch_msg("You listen to " +QTNAME(TO)+ " for a little while " +
          "and find what he says interesting, however quickly realise " +
          "that to truly embrace the teachings of the Old Gods of Light " +
          "further you will need to leave your current layman guild.\n");
        return "";
    }

    if (TP->query_race_name() == "kender")
    {
        TP->catch_msg("You listen to " +QTNAME(TO)+ " talk about what " +
          "he has learnt of the pantheon of gods from the Disks of " +
          "Mishakal. You find the stories fascinating and listen with " +
          "rapt attention! One god in particular strikes an accord with " +
          "you - Branchala, the Songmaster.\n\nKender revere all the " +
          "gods, as well as a number of nature spirits, eldritch beings, " +
          "and potted plants, so as to not hurt any deity's or spirit's " +
          "feelings.\n\nBut Branchala represents the kender spirit... " +
          "a love of music and storytelling, and an enthusiasm for " +
          "life. You feel your heart beat in time with Branchala's " +
          "Song of Life!\n\n");

        speak = ([
            1 : ({ 1.5, "whisper to " +TP->query_real_name()+ 
                        " Kenderkin, the tales of Branchala seem to " +
                        "spark your interest!"}),
            2 : ({ 2.0, "whisper to " +TP->query_real_name()+ " I should " 
                      + "not be surprised... Kender have an enthusiasm "
                      + "for life and a wanderlust that seems to exemplify "
                      + "the teachings of the Bard King!"}),
            3 : ({ 3.0, "whisper to " +TP->query_real_name()+ " If you " +
                        "wish to become a follower of Branchala, I can "
                      + "ordain you. Simply <convert to holy order of the "
                      + "stars>."}),
        ]);
    
        handle_timed_messages(this_player(), speak);
        TP->add_prop(BRANCHALA, 1);

        return "";

    }

    if(TP->query_race_name() == "minotaur")
    {
        TP->catch_msg("You listen to " +QTNAME(TO)+ " talk about what " +
          "he has learnt of the pantheon of gods from the Disks of " +
          "Mishakal. One god in particular strikes an accord with you " +
          "- Kiri-Jolith, the god of honour, glory, courage, heroism, " +
          "and war.\n\nBeing an honour-bound race, the teachings of " +
          "the Great Bison align closely to the rigid code minotaurs " +
          "are brought up with.\n\n");

        if(!CAN_SEE(TO, TP))
        {
              TP->catch_msg("Being hidden " +QTNAME(TO)+ "  cannot give " +
                    "you any specific instruction.\n");
              return "";
        }

        
        speak = ([
            1 : ({ 1.5, "say Yes, I see the god of righteous war resonates "
                      + "with you."}),
            2 : ({ 2.0, "say From what I read in the disks, Kiri-Jolith is "
                      + "a far more aggressive god than that of my god, "
                      + "Paladine..."}),
            3 : ({ 6.0, "say But while a god of war, he is not one "
                      + "possessed by bloodlust or needless violence."}),
            4 : ({ 5.0, "say Kiri-Jolith has a strong sense of honour and "
                      + "fair play. He cannot tolerate tyranny, fighting "
                      + "it with tireless heroism and discipline."}),
            5 : ({ 5.0, "say His priests of old once sought out evil and "
                      + "brought the battle aggressively to them."}),
            6 : ({ 5.0, "say If this is a path you are interested in "
                      + "following, ask me about Kiri-Jolith's Test of "
                      + "Faith."})
        ]);
    
        handle_timed_messages(this_player(), speak);
        TP->add_prop(KIRIJOLITH, 1);

        return "";
    }

    if(IS_DOOMSEEKER(TP))
    {
        TP->catch_msg("You listen to " +QTNAME(TO)+ " talk about what " +
          "he has learnt of the pantheon of gods from the Disks of " +
          "Mishakal. One god in particular strikes an accord with you " +
          "- Kiri-Jolith, the god of honour, glory, courage, heroism, " +
          "and war.\n\nDesperately seeking such things yourself, the " +
          "teachings of Kijo the Blade align closely to your needs " +
          "as a Doomseeker of the Neidar Clan.\n\n");

        if(!CAN_SEE(TO, TP))
        {
              TP->catch_msg("Being hidden " +QTNAME(TO)+ "  cannot give " +
                    "you any specific instruction.\n");
              return "";
        }

        
        speak = ([
            1 : ({ 1.5, "say Yes, I see the god of righteous war resonates "
                      + "with you."}),
            2 : ({ 2.0, "say From what I read in the disks, Kiri-Jolith is "
                      + "a far more aggressive god than that of my god, "
                      + "Paladine..."}),
            3 : ({ 6.0, "say But while a god of war, he is not one "
                      + "possessed by bloodlust or needless violence."}),
            4 : ({ 5.0, "say Kiri-Jolith has a strong sense of honour and "
                      + "fair play. He cannot tolerate tyranny, fighting "
                      + "it with tireless heroism and discipline."}),
            5 : ({ 5.0, "say His priests of old once sought out evil and "
                      + "brought the battle aggressively to them."}),
            6 : ({ 5.0, "say If this is a path you are interested in "
                      + "following, ask me about Kiri-Jolith's Test of "
                      + "Faith."})
        ]);
    
        handle_timed_messages(this_player(), speak);
        TP->add_prop(KIRIJOLITH, 1);

        return "";
    }

    if(TP->query_guild_name_occ() == "Solamnian Knights")
    {
        TP->catch_msg("You listen to " +QTNAME(TO)+ " talk about what " +
          "he has learnt of the pantheon of gods from the Disks of " +
          "Mishakal. One god in particular strikes an accord with you " +
          "- Kiri-Jolith, the god of honour, glory, courage, heroism, " +
          "and war.\n\nBeing a knight of Solamnia, you are familiar " +
          "with this god as being historically the patron of the " +
          "Order of the Sword, and the god legends say once granted " +
          "them divine powers.\n\n");

        speak = ([
            1 : ({ 1.5, "whisper to " +TP->query_real_name()+ " Yes, I see "
                      + "the god of honourable war resonates with you."}),
            2 : ({ 2.0, "whisper to " +TP->query_real_name()+ " From what "
                      + "I read in the disks, Kiri-Jolith is a far more "
                      + "aggressive god than that of my god, Paladine..."}),
            3 : ({ 6.0, "whisper to " +TP->query_real_name()+ " But while "
                      + "a god of war, he is not one possessed by "
                      + "bloodlust or needless violence."}),
            4 : ({ 5.0, "whisper to " +TP->query_real_name()+ " Kiri-Jolith "
                      + "has a strong sense of honour and fair play. He "
                      + "cannot tolerate tyranny, fighting it with "
                      + "tireless heroism and discipline."}),
            5 : ({ 5.0, "whisper to " +TP->query_real_name()+ " While the "
                      + "knighthood has three patron gods of light - "
                      + "Habbakuk, Kiri-Jolith, and Paladine - only "
                      + "Kiri-Jolith directly provides access to divine "
                      + "blessings..."}),
            6 : ({ 5.0, "whisper to " +TP->query_real_name()+ " ... and "
                      + "only to those who aspire to the Measure "
                      + "of the Sword - Heroism, Courage, and "
                      + "Spiritualism."}),
        ]);

/*      Loosening restrictions on knights being able to join at any level.

        if (TP->query_knight_level() < 4)
        {
            
            speak += ([
                7 : ({ 4.0, "whisper to " +TP->query_real_name()+ " While a "
                          + "knight, you are yet to reach that level of "
                          + "understanding. Only then will Kiri-Jolith "
                          + "accept you in to his Order of Clerists."}),
            ]);
            
            handle_timed_messages(this_player(), speak);
            return "";
        }
*/

        speak += ([
            7 : ({ 4.0, "whisper to " +TP->query_real_name()+ " It seems you "
                      + "aspire to meet the Measure of the Sword, and would be "
                      + "well suited to join Kiri-Jolith's Order of " 
                      + "Clerists."}),
            8 : ({ 4.0, "whisper to " +TP->query_real_name()+ " If this is a "
                      + "path you are interested in following, ask me about "
                      + "Kiri-Jolith's Test of Faith."}),
        ]);
        
        handle_timed_messages(this_player(), speak);
        TP->add_prop(KIRIJOLITH, 1);
        return "";
    }

    TP->catch_msg("You listen to " +QTNAME(TO)+ " talk about what he has " +
          "learnt of the pantheon of gods from the Disks of Mishakal. One " +
          "goddess in particular strikes an accord with you - Mishakal, " +
          "the 'Light Bringer', the first of the good gods of light to " +
          "return to Krynn after the darkness of the Cataclysm.\n\n");

          
    speak = ([
        1 : ({ 1.5, "say Mishakal, a goddess of healing and compassion, the "
                  + "bringer of light to those who live in darkness and "
                  + "ignorance."}),
        2 : ({ 2.0, "say The scourge of disease, promoter of harmony and " 
                  + "peace, and also a fierce enemy of the unliving."}),
        3 : ({ 4.0, "say It was Mishakal who was the first of the true gods "
                  + "who revealed themselves to our world in its darkest "
                  + "hour."}),
        4 : ({ 4.0, "say And it was her first disciple since the Cataclysm "
                  + "who recovered the Disks of Mishakal and the knowledge of "
                  + "the gods of Light I now share with you."}),
        5 : ({ 3.0, "say Mishakal's return is a beacon to those who wish to "
                  + "play a part in driving back the darkness."}),
        6 : ({ 4.0, "whisper to " +TP->query_real_name()+ " If you wish to "
                  + "follow the path of Mishakal, I can ordain you as one of "
                  + "her followers."}),
        7 : ({ 4.0, "whisper to " +TP->query_real_name()+ " Simply <convert "
                  + "to holy order of the stars>."}),
    ]);
    
    handle_timed_messages(this_player(), speak);
    TP->add_prop(MISHAKAL, 1);
    
    return "";
}

string
gods_hint()
{
    if (!handle_timed_messages(this_player()))
        return C(COMPOSITE_LIVE(TO))+ " is currently conversing with " +
           "someone else. You should wait until he is finished.\n";

     command("smile warm");
     command("say I am new to the Old Gods myself, so have much still " +
             "to learn...");
     command("chuckle");
     command("say But since spending some time studying the Disks of " +
             "Mishakal, I have found my calling and have converted " +
             "to the faith of the Holy Order of the Stars.");
     command("say I am happy to teach you what I have recently " +
             "discovered if you are interested?");
     return "";
}

string
disks_hint()
{
    if (!handle_timed_messages(this_player()))
        return C(COMPOSITE_LIVE(TO))+ " is currently conversing with someone " +
           "else. You should wait until he is finished.\n";

     command("say The Disks of Mishakal are an ancient artifact containing " +
             "the teachings of the Old Gods, known as the Holy Order " +
             "of the Stars.");
     command("say I have only started studying them, and there is still " +
             "a lot for me to learn!");
     command("say Mindful of that, I am happy to teach you more of what " +
             "I have recently discovered if you are interested?");
     return "";
}

string
oots_hint()
{
    if (!handle_timed_messages(this_player()))
        return C(COMPOSITE_LIVE(TO))+ " is currently conversing with " +
           "someone else. You should wait until he is finished.\n";

     command("say The Holy Order of the Stars are the Old Gods. The " +
         "disks of Mishakal contain the teachings of the Gods of Light...");
     command("say Branchala, the Songmaster...");
     command("say Habbakuk, the Fisher King...");
     command("say Kiri-Jolith, the Sword of Justice...");
     command("say Majere, the Dreamsender...");
     command("say Mishakal, the Light Bringer...");
     command("say and Paladine, the Valiant Warrior.");
     command("say After the Cataclysm and the world was cast into very " +
          "dark times it was commonly thought they had abandoned us.");
     command("say But it seems it was the other way around.");
     command("nod thoughtfully");
     command("say I am happy to teach you more of what I have " +
             "recently discovered if you are interested?");
     return "";
}

string
branchala_hint()
{
    if (!handle_timed_messages(this_player()))
        return C(COMPOSITE_LIVE(TO))+ " is currently conversing with " +
           "someone else. You should wait until he is finished.\n";

     command("emote strokes his white beard thoughtfully.");
     command("say Branchala I don't know much about.");
     command("say I am yet to study in detail his teachings in the " +
             "Disks of Mishakal.");
     command("say However I do know he is known as the Bard King, and " +
             "the god of music.");
     command("say I am happy to teach you more of what I have recently " +
             "discovered if you are interested?");
     return "";
}

string
habbakuk_hint()
{
    if (!handle_timed_messages(this_player()))
        return C(COMPOSITE_LIVE(TO))+ " is currently conversing with " +
           "someone else. You should wait until he is finished.\n";

     command("say Habbakuk the Fisher King!");
     command("say The creator and ruler of all creatures of land and sea.");
     command("say I am yet to study his teachings in the Disks of Mishakal.");
     command("say However I do know he is the youngest son of the " +
             "gods Mishakal and Paladine.");
     command("say Also a fierce protector of nature.");
     command("say I am happy to teach you more of what I have recently " +
             "discovered if you are interested?");
     return "";
}


string
kirijolith_hint()
{
    if (!handle_timed_messages(this_player()))
        return C(COMPOSITE_LIVE(TO))+ " is currently conversing with " +
           "someone else. You should wait until he is finished.\n";

     command("say Ah Kiri-Jolith, the Sword of Justice!");
     command("say He is the god of righteous warfare.");
     command("say A patron of the knights of Solamnia and minotaurs, he " +
           "espouses courage, honour, and spiritualism.");
     command("say I am happy to teach you more of what I have recently " +
             "discovered if you are interested?");
     return "";
}

string
paladine_hint()
{
    if (!handle_timed_messages(this_player()))
        return C(COMPOSITE_LIVE(TO))+ " is currently conversing with " +
           "someone else. You should wait until he is finished.\n";

     command("say Paladine, Father of Good and Master of Law!");
     command("say He is my patron, and has been known in times " +
           "past as the Dragon's Lord or the Valiant Warrior.");
     command("say He is one who subtly pushes and prods, arms " +
           "and inspires his followers, but never overrides their " +
           "free will.");

     if(IS_OOTS(TP))
     {
        if(!OOTS_QUERY_REV(TP, "paladine"))
        {
            TP->catch_msg("\n\nYou find your mind suddenly filled with " +
                          "divine clarity as a revelation on the aspect " +
                          "of Paladine manifests to you!\n\n\n");
            OOTS_ADD_REV(TP,"paladine","the aspect of paladine");  
        }
     }
     else
     {
        command("say I am happy to teach you more of what I have " +
             "recently discovered if you are interested?");
     }

     return "";
}

string
mishakal_hint()
{
    if (!handle_timed_messages(this_player()))
        return C(COMPOSITE_LIVE(TO))+ " is currently conversing with " +
           "someone else. You should wait until he is finished.\n";

     command("say Mishakal, sometimes know as the Healer or the " +
             "Bearer of Light.");
     command("say Before the Cataclysm she was the most revered of the " +
           "ministering gods, with many temples across the land.");
     command("say And she is the first of the Gods of Light to return " +
           "to us, her teachings illuminating and enlightening. A " +
           "force to drive back the darkness!");
     command("say I am happy to teach you more of what I have recently " +
             "discovered if you are interested?");
     return "";
}

string
majere_hint()
{
    if (!handle_timed_messages(this_player()))
        return C(COMPOSITE_LIVE(TO))+ " is currently conversing with " +
           "someone else. You should wait until he is finished.\n";

     command("say Majere, the Master of Mind.");
     command("say Of all my learnings I know least of this god...");
     command("say ... except that he promotes faith, mercy and loyalty " +
             "through example.");
     command("say I am happy to teach you more of what I have recently " +
             "discovered if you are interested?");
     return "";
}

string
paxtharkas_hint()
{
    if (!handle_timed_messages(this_player()))
        return C(COMPOSITE_LIVE(TO))+ " is currently conversing with " +
           "someone else. You should wait until he is finished.\n";

     command("say When the Red Dragonarmy invaded Abanasinia, Verminaard " +
          "took captive the townsfolk and plainsmen of the region, " +
          "taking them to work the mines of Pax Tharkas.");
     command("shiver");
     command("say For a time I labored there, until I contracted a " +
          "wasting disease and became too ill to work.");
     command("say By rights, the illness should have killed me. But " +
          "as fate would have it, I was miraculously healed by one " +
          "of the heroes who rescued the captives, a cleric of Mishakal.");
     command("say I became a true believer and disciple of Paladine " +
          "at that point. The Disks of Mishakal, recovered by the " +
          "heroes, were entrusted to me.");
     command("say And I now work at bringing the teachings of the " +
          "Gods of Light to the people of Krynn.");
     command("say I am happy to teach you more of what I have recently " +
             "discovered if you are interested?");
     return "";
}

string
medallion_hint()
{
    if (!handle_timed_messages(this_player()))
        return C(COMPOSITE_LIVE(TO))+ " is currently conversing with " +
           "someone else. You should wait until he is finished.\n";

     command("emote traces the carvings on his platinum medallion fondly.");
     command("say This is my medallion of faith, the symbol identifying " +
          "me as a follower of the god Paladine.");

     return "";
}
