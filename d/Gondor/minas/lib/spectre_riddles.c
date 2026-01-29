/* 
 * /d/Gondor/minas/lib/spectre_riddles.c  
 *
 * Riddles for the spectres in the Hallows
 *
 * Information in riddles taken from books in the great
 * library at Minas Tirith
 *
 * Alto, 20 May 2001
 *
 */

#pragma strict_types

inherit "/d/Gondor/common/lib/binbit.c";

#include <macros.h>
#include <stdproperties.h>
#include "/d/Gondor/defs.h"
#include "/d/Gondor/bits.h"
#include "/d/Gondor/minas/lib/porter_defs.h"


string riddles_answer();
string Index, Value;
int answer_riddle(string str);
int first_riddle_attack();
int second_riddle_attack();
int third_riddle_attack();
void refresh_riddles();

object actor, *inv;

string *riddles =
/*1*/   ({"What island was given to the Edain in the beginning of the Second "
           + "Age as a reward for their valour and faithfulness in the Wars "
           + "of Beleriand?", 
/*2*/     "Which Numenorian King took Sauron as prisoner in SA 3262?", 
/*3*/     "Who was the father of Elendil?",
/*4*/     "What was the name of the White Tree in Numenor?",
/*5*/     "Which of Elendil's sons stole a sapling of the White Tree in Numenor?",
/*6*/     "In which city did Isildur first plant the White Tree in Middle Earth?",
/*7*/     "What did the Eldar of Beleriand name the Edain, which means 'Second "
           + "People'?",
/*8*/     "The three great families of the Edain were the houses of Beor, "
           + "Haladin, and which other?",
/*9*/     "In the beginning of the history of Men, there were two groups, the "
           + "Aravador and the Lintador. From which group are the folk of "
           + "Minas Tirith descended?",
/*10*/    "Of Beor, Haladin and Marach, who brought the first House of the "
           + "Edain over the Blue Mountains into Beleriand?",
/*11*/    "Which Noldor Elf first taught the Edain true knowledge?",
/*12*/    "Who died first, Elendil or Anarion?",
/*13*/    "By what other name was King Romendacil I known?",
/*14*/    "Which of the following was NOT one of the four Ship-Kings of "
           + "Gondor: Earnil I, Calmacil, Tarannon, Ciryandil?",
/*15*/    "Under the reign of which King did the Kin-Strife begin?",
/*16*/    "What man, known as The Usurper, deposed King Eldacar in 1437?",
/*17*/    "In 1636, the King and all his children perished in the Great "
           + "Plague. In that year also the White Tree of Minas Anor also "
           + "died. Who was this King?",
/*18*/    "In 1798, this King planted a seedling of the White Tree in the "
           + "Court of the Fountain, after the White Tree of Minas Anor died. "
           + "Who was this King?",
/*19*/    "On the death of King Ondoher and his sons in 1944, a man of the "
           + "North Kingdom claimed the crown as Isildur's heir. His claim "
           + "was rejected. Who was this man?",
/*20*/    "The last King of Gondor entered Minas Morgul and was never seen "
           + "again. Who was this King?",
/*21*/    "During which Age was the Isle of Numenor given to the Edain: First, "
           + "Second, or Third?",
/*22*/    "Which Steward of Gondor was known as 'The Hunter'?",
/*23*/    "Which Steward of Gondor gave Orthanc to Saruman?",
/*24*/    "True or false: the Stewards of Gondor bear a White Rod as their "
           + "token of office.",
/*25*/    "True or false: the Banner of the Stewards of Gondor is a golden "
           + "hunting horn on a green field."});


string *answers =
/*1*/     ({"numenor", 
/*2*/       "ar-pharazon", 
/*3*/       "amandil",
/*4*/       "nimloth",
/*5*/       "isildur",
/*6*/       "minas ithil",
/*7*/       "atani",
/*8*/       "marach",
/*9*/       "lintador",
/*10*/      "beor",
/*11*/      "finrod",
/*12*/      "anarion",
/*13*/      "tarostar",
/*14*/      "calmacil",
/*15*/      "valacar",
/*16*/      "castamir",
/*17*/      "telemnar",
/*18*/      "tarondor",
/*19*/      "arvedui",
/*20*/      "earnur",
/*21*/      "second",
/*22*/      "vorondil",
/*23*/      "beren",
/*24*/      "true",
/*25*/      "false"});


void
unlock_door()
{
    command("unlock door with key");
    command("open door");
}


string  
riddles_answer()
{
    int position;

    if ((!TP->query_prop(ANSWERED_ONE_RIDDLE))
        || (!TP->query_prop(ANSWERED_TWO_RIDDLES))
        || (!TP->query_prop(ANSWERED_ALL_RIDDLES)))
        {
         refresh_riddles();
        }

    Index = ONE_OF_LIST(riddles);

    position = member_array(Index, riddles);

    Value = answers[position];

    riddles -= ({ Index });

    answers -= ({ Value });

    inv = all_inventory(TP);
    actor = TP->query_real_name();


    if (!sizeof(filter(inv, &->id("_token_of_tombs_"))))
        {
        command("say You do not bear the token of the tombs. Now I "
            + "must kill you.");
        return "";
        }

    else
    {
    command("whisper to " + actor + " " + Index + "  \nAnswer me "
        + "with 'answer <answer>'");

    set_alarm(1.0, 0.0, &answer_riddle());

    return Value;
    }
}

int
answer_riddle(string str)
{
    string response = LOW(str);
    actor = TP->query_real_name();
    inv = all_inventory(TP);


    if (!sizeof(filter(inv, &->id("_token_of_tombs_"))))
        {
        command("peer " + actor);
        command("say to " + actor + " You do not bear the token!");
        return 1;
        }


    if (!strlen(str))
        {
        command("say Have you nothing to answer? Think quickly!");
        return 1;
        }

    if (response != Value)
        {
        command("say That is incorrect. You are no doubt an imposter. "
            + "Your life is forfeit for entering this hallowed place.");
        command("sigh");
        command("kill " + actor);
        return 1;
        }

    if (response = Value)
        {
        if (TP->query_prop(MISSED_A_RIDDLE))
            {
            command("say It is too late to answer, imposter.");

            return 1;
            }

        if (TP->query_prop(ANSWERED_TWO_RIDDLES))
            {
            command("say Correct! Now I am satisfied with your loyalty "
                + "to Gondor, and will leave you to your work.");
            TP->add_prop(ANSWERED_ALL_RIDDLES, 1);
            TP->remove_prop(ANSWERED_TWO_RIDDLES);
            TP->remove_prop(ANSWERED_ONE_RIDDLE);
            set_alarm(0.0, 0.0, &unlock_door());

            return 1;
            }

        if (TP->query_prop(ANSWERED_ONE_RIDDLE))
            {
            command("say Correct! However, even the spies of Mordor might know "
                + "the answer to that one. I have one more question.");
            TP->add_prop(ANSWERED_TWO_RIDDLES, 1);
            set_alarm(1.0, 0.0, &riddles_answer());
            set_alarm(120.0, 0.0, &third_riddle_attack());


            return 1;
            }

        if (!TP->query_prop(ANSWERED_ONE_RIDDLE))
            {
            command("say Correct! Still, I am not yet certain of your claim. "
                + "A true servant of the tombs would be able to answer the "
                + "following question with ease:");
            TP->add_prop(ANSWERED_ONE_RIDDLE, 1);
            set_alarm(1.0, 0.0, &riddles_answer());
            set_alarm(120.0, 0.0, &second_riddle_attack());


            return 1;
            }
        }

    else
        {
        command("say Something went wrong...Please make a bug report.\n");
        return 0;
        }

}

int
first_riddle_attack()
{
    if (!objectp(present(TP, ENV(TO))))
        {
        return 1;
        }


    if (TP->query_prop(ANSWERED_ALL_RIDDLES))
        {
        return 1;
        }

    if (!TP->query_prop(ANSWERED_ONE_RIDDLE))
        {
        command("say A true servant of the Tombs would have answered "
            + "the first question without hesitation. I see you are an "
            + "imposter. For daring "
            + "the Hallows unbidden, you shall die a slow and agonizing "
            + "death.");

        TP->add_prop(MISSED_A_RIDDLE, 1);

        command("kill " + TP->query_real_name());
        return 1;
        }
    else
        {
        return 1;
        }
}


int
second_riddle_attack()
{
    if (TP->query_prop(ANSWERED_ALL_RIDDLES))
        {
        return 1;
        }

    if (!TP->query_prop(ANSWERED_TWO_RIDDLES))
        {
        command("say A true servant of the Tombs would have answered "
            + "the second question without hesitation. I see you "
            + "are an imposter. For daring "
            + "the Hallows unbidden, you shall die a slow and agonizing "
            + "death.");

        TP->add_prop(MISSED_A_RIDDLE, 1);

        command("kill " + TP->query_real_name());
        return 1;
        }
    else
        {
        return 1;
        }
}

    

int
third_riddle_attack()
{
    if (!TP->query_prop(ANSWERED_ALL_RIDDLES))
        {
        command("say A true servant of the Tombs would have answered "
            + "the third question without hesitation. I see you "
            + "are an imposter. For daring "
            + "the Hallows unbidden, you shall die a slow and agonizing "
            + "death.");

        TP->add_prop(MISSED_A_RIDDLE, 1);

        command("kill " + TP->query_real_name());
        return 1;
        }
    else
        {
        return 1;
        }
}

void
refresh_riddles()
{
riddles =
/*1*/   ({"What island was given to the Edain in the beginning of the Second "
           + "Age as a reward for their valour and faithfulness in the Wars "
           + "of Beleriand?", 
/*2*/     "Which Numenorian King took Sauron as prisoner in SA 3262?", 
/*3*/     "Who was the father of Elendil?",
/*4*/     "What was the name of the White Tree in Numenor?",
/*5*/     "Which of Elendil's sons stole a sapling of the White Tree in Numenor?",
/*6*/     "In which city did Isildur first plant the White Tree in Middle Earth?",
/*7*/     "What did the Eldar of Beleriand name the Edain, which means 'Second "
           + "People'?",
/*8*/     "The three great families of the Edain were the houses of Beor, "
           + "Haladin, and which other?",
/*9*/     "In the beginning of the history of Men, there were two groups, the "
           + "Aravador and the Lintador. From which group are the folk of "
           + "Minas Tirith descended?",
/*10*/    "Of Beor, Haladin and Marach, who brought the first House of the "
           + "Edain over the Blue Mountains into Beleriand?",
/*11*/    "Which Noldor Elf first taught the Edain true knowledge?",
/*12*/    "Who died first, Elendil or Anarion?",
/*13*/    "By what other name was King Romendacil I known?",
/*14*/    "Which of the following was NOT one of the four Ship-Kings of "
           + "Gondor: Earnil I, Calmacil, Tarannon, Ciryandil?",
/*15*/    "Under the reign of which King did the Kin-Strife begin?",
/*16*/    "What man, known as The Usurper, deposed King Eldacar in 1437?",
/*17*/    "In 1636, the King and all his children perished in the Great "
           + "Plague. In that year also the White Tree of Minas Anor also "
           + "died. Who was this King?",
/*18*/    "In 1798, this King planted a seedling of the White Tree in the "
           + "Court of the Fountain, after the White Tree of Minas Anor died. "
           + "Who was this King?",
/*19*/    "On the death of King Ondoher and his sons in 1944, a man of the "
           + "North Kingdom claimed the crown as Isildur's heir. His claim "
           + "was rejected. Who was this man?",
/*20*/    "The last King of Gondor entered Minas Morgul and was never seen "
           + "again. Who was this King?",
/*21*/    "During which Age was the Isle of Numenor given to the Edain: First, "
           + "Second, or Third?",
/*22*/    "Which Steward of Gondor was known as 'The Hunter'?",
/*23*/    "Which Steward of Gondor gave Orthanc to Saruman?",
/*24*/    "True or false: the Stewards of Gondor bear a White Rod as their "
           + "token of office.",
/*25*/    "True or false: the Banner of the Stewards of Gondor is a golden "
           + "hunting horn on a green field."});


answers =
/*1*/     ({"numenor", 
/*2*/       "ar-pharazon", 
/*3*/       "amandil",
/*4*/       "nimloth",
/*5*/       "isildur",
/*6*/       "minas ithil",
/*7*/       "atani",
/*8*/       "marach",
/*9*/       "lintador",
/*10*/      "beor",
/*11*/      "finrod",
/*12*/      "anarion",
/*13*/      "tarostar",
/*14*/      "calmacil",
/*15*/      "valacar",
/*16*/      "castamir",
/*17*/      "telemnar",
/*18*/      "tarondor",
/*19*/      "arvedui",
/*20*/      "earnur",
/*21*/      "second",
/*22*/      "vorondil",
/*23*/      "beren",
/*24*/      "true",
/*25*/      "false"});
}



