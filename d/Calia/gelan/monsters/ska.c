/*
   A hobbit banker for the bank in Gelan 
   Coder: Maniac

   Revision history: 
        31/5/96         triggers removed                  Maniac
         2.5.95         improved number selection         Maniac
         8.3.95         forced save after quest           Maniac
         6.3.95         number choosing simplified        Maniac
         24.1.95        easy solutions taken out          Maniac
         20.12.94       Number game quest added           Maniac
         6.1.95         Only get easy chance after 
                        many guesses                      Maniac

*/


#pragma save_binary

inherit "/std/monster";
#include <ss_types.h>
#include <macros.h>
#include <stdproperties.h>
#include "monster.h"
inherit STD_AIDED;
#include HAUNT_CODE
#include NUMBER_QUEST


mixed trying_test = 0;
int test_alarm = 0;
int *current_numbers = ({ });
int target_number = 0;

void ska_chat1();
void ska_chat2();
void ska_chat3();
void ska_chat4();


/* reply to a number game query */ 
string
reply()
{
    if (trying_test) return "";
    else
        return "say I know a very good number game if you'd like to " +
         "play. I choose a target number and give you a set of smaller " +
         "numbers which you have to use to calculate the target number. " +
         "For example, say I gave you a target number 15 and said " +
         "you could use three numbers, 25, 5 and 2, a correct answer " +
         "would be 25-5*2. Of course this was a simple example and " +
         "I will give you a harder test if you want to play. Just " +
         "go 'play number game' if you want to try. You will be " +
         "rewarded if you get a right answer within the allotted " + 
         "time!";
}


void
create_monster() 
{
  if (!IS_CLONE)
    return;
  set_name("ska");
  add_name("owner");
  add_name("banker");
  add_name("shopkeeper");
  set_race_name("hobbit");
  set_adj(({"studious","bright-eyed"}));
  set_title("Muesli the Banker");
  set_long("Ska Muesli, whose name is a legacy from his childhood home " +
     "in the mountains, is the bank manager of Gelan. He rose to this " +
     "high position from a lowly clerk by sheer long hours and " +
     "dedication, plus his reputation for mathematics that would " +
     "put a gnome to shame. Despite what they say about bank managers, " +
     "you won't find any miserly traits " +
     "in this fellow. That role is left solely to Coiney.\n");
  default_config_npc(60);
  set_base_stat(SS_INT,75);
  set_hp(5000);
  set_skill(SS_UNARM_COMBAT, random(20) + 35);
  set_skill(SS_DEFENCE, random(10) + 50);
  set_skill(SS_AWARENESS, random(10) + 50);
  set_alignment(50 + random(100)); 

  add_act(VBFC_ME("ska_chat1"));
  add_act(VBFC_ME("ska_chat2"));
  add_act(VBFC_ME("ska_chat3")); 
  add_act(VBFC_ME("ska_chat4"));
  set_act_time(6);
  
  add_ask(({"number game", "number games", "numbers game", "game", "games",
            "mathematics", "play"}),
            VBFC_ME("reply"), 1);
}



object
query_testing()
{
    return trying_test;
}


void
ska_chat1()
{
    if (!trying_test)
        command("say I'm very fond of number games."); 
}

void
ska_chat2()
{
    if (!trying_test)
        command("say Would you like to play a number game with me?");
}

void
ska_chat3()
{
    if (!trying_test)
        command("say How are you at mathematics?");
}


void
ska_chat4()
{
    if (!trying_test)
        command("emote looks like he is thinking hard, " +
                "calculating something.");
}


void
reset_test()
{
    command("emote stops the current number game."); 
    trying_test = 0;
    remove_alarm(test_alarm);
    test_alarm = 0; 
}

void
attacked_by(object attacker)
{
  if (trying_test) 
      reset_test();
  ::attacked_by(attacker);
}


int *
choose_number_set()
{
    int i, num;
    int *ns = ({ });
    int *big = NQ_BIG_NUMBERS;
    int *small = NQ_SMALL_NUMBERS;
   
    for (i = 0; i < NQ_NUM_BIG_NUMBERS; i++) {
        num = big[random(sizeof(big))];
        big -= ({num});
        ns += ({num});
    }

    for (i = 0; i < NQ_NUM_SMALL_NUMBERS; i++) {
        num = small[random(sizeof(small))];
        small -= ({num});
        ns += ({num});
    }

    return ns;
}


/* Choose a target number to try to calculate, given a set of numbers */
int
choose_target_number(int *nums)
{
    int i, j, k, start_num;
    
    /* Calculate fine-grain number */
    i = random(30) + 10;
    if (i%5 == 0) 
       if (i == 35) 
           i -= (random(4)+1);
       else if (i == 10)
           i += (random(4)+1);
       else 
           if (random(2))
               i -= (random(4)+1);
           else
               i += (random(4)+1);

    /* Calculate coarse grain number */
    start_num = random(5)+2;
    j = start_num;
    j++;
    if (j > 6)
        j = 2;
    while ((member_array(j, nums) > -1) && (j != start_num)) {
        j++;
        if (j > 6)
            j = 2;
    }

    k = (j*100) + i;
    if (random(2) || (j == 2))
        k += 50;

    return k;
}


/* Give composite listing of numbers */
string
composite_int(int *numbers)
{
    int i;
    string str;

    if (sizeof(numbers) == 0) 
        return "";
    else if (sizeof(numbers) == 1)
        return ("" + numbers[0]);
    else if (sizeof(numbers) == 2)
        return ("" + numbers[0] + " and " + numbers[1] + ".");
    for (i = 0; i < (sizeof(numbers) - 2); i++)
        str = str + numbers[i] + ", ";
    str = str + numbers[sizeof(numbers)-2] + " and " + 
                numbers[sizeof(numbers)-1] + ".";    
    return str;
}



/* Register that the player has made another try at the game */
void
another_try(object tp)
{
    int i;
    i = tp->query_prop(NQ_GUESS_ATTEMPTS);
    i++;
    tp->add_prop(NQ_GUESS_ATTEMPTS, i); 
    tp->add_mana(-NQ_MANA_LOSS);
    tp->catch_msg("You feel more mentally drained after your " +
                  "latest number game attempt.\n");
}


/* Time is up, stop game, player has failed this time */ 
void
time_up(object tp)
{
    int i;

    if (present(trying_test, environment(this_object())))
        command("say You're out of time, " + 
                     trying_test->query_nonmet_name() + ".");
    reset_test();
    another_try(tp);
}



/* Start the game for a given player */
void
start_game(object tp)
{
   string nm;

   trying_test = tp;
   nm = tp->query_nonmet_name();
   current_numbers = choose_number_set();
   target_number = choose_target_number(current_numbers);
   command("say Ok, " + nm + ", here are the numbers you will have " +
           "to work with:");
   command("say " + composite_int(current_numbers));
   command("say Your target number is: " + target_number + ".");
   command("say You should answer with a legal arithmetic expression, " +
          "you may of course use brackets, and you needn't use all the " +
          "numbers that are available.");
   command("say Your time starts now, give me your answer with " +
           "'answer <arithmetic expression>'.");
   test_alarm = set_alarmv(itof(NQ_GAME_TIME), 0.0, "time_up", ({tp}));
}


/* A player tries to start playing the number game */
int
play_game(string str)
{
    object tp = this_player();
    if (str != "number game") return 0;

    if (environment()->attacked_town_check()) 
        return 1;

    if (trying_test && !present(trying_test, environment(this_object())))
       reset_test();

    if (this_object()->query_attack()) {
        notify_fail("Ska can't deal with a game now, he's fighting!\n"); 
        return 0;
    }
    if (trying_test == tp) {
        notify_fail("You are already playing the number game.\n");
        return 0;
    }
    else if (trying_test) {
        notify_fail("Someone else is playing the number game " +
                    "right now.\n"); 
        return 0;
   }
   else if (tp->query_stat(SS_INT) < NQ_MIN_INT) {
        notify_fail("Sorry, but your intelligence is not yet high " +
                    "enough to play the number game.\n");
        return 0;
   }
   else if (tp->query_mana() < NQ_MANA_LOSS) {
        notify_fail("You don't have enough mental energy right now " +
                    "to play the number game.\n");
        return 0;
   }
   start_game(tp);
   return 1;
} 
    


/* Check whether an invalid number was used, return 1 if yes */
int
invalid_numbers_used(int *allowed_nums, int *used_nums)
{
    int i;

    for (i = 0; i < sizeof(used_nums); i++)
        if (member_array(used_nums[i], allowed_nums) == -1)
             return 1;
    return 0;
}


/* Check whether a number was used more than once, return 1 if yes */
int
double_use(int *used_nums)
{
    int *used_once = ({ });
    int i;

    for (i = 0; i < sizeof(used_nums); i++) {
        if (member_array(used_nums[i], used_once) > -1)
             return 1;
        used_once += ({ used_nums[i] }); 
    }
    return 0;
}


/* Got an answer from a player */
int
got_an_answer(string str)
{
    object tp = this_player();
    mixed *results;
    mixed result; 
    int i, xp_amount;
    int *n_used, *nums;

    if (!str) return 0;
    
    if (trying_test != tp) {
        notify_fail("You aren't playing the game now!\n");
        return 0;
    }
    tell_room(environment(this_object()), QCTNAME(tp) + " answers: " +
              str + ".\n", tp);
    tp->catch_msg("You answer: " + str + ".\n"); 
    nums = current_numbers;
    reset_test();
    seteuid(getuid());
    results = (GELAN_SPECIALS + "eval_plus")->eval_plus(str);
    result = results[0];
    n_used = results[1]; 
    if (result == "fail") {
       command("say I did not understand your answer, " +
                tp->query_nonmet_name() + ".");
       another_try(tp);
       return 1;
    }
    else if (invalid_numbers_used(nums, n_used)) {
       command("say You used some numbers not chosen from those I gave " +
                    "you, " + tp->query_nonmet_name() + ".");
       another_try(tp);
       return 1;
    }
    else if (double_use(n_used)) {
       command("say You used a number more than once, " +
                    tp->query_nonmet_name() + ".");  
       another_try(tp);
       return 1;
    }
    else if (result != target_number) {
       command("say That comes to: " + result + 
                ", " + tp->query_nonmet_name() + ".");
       command("say Not the right answer I'm afraid!");
       if (((target_number - result) < 6) && 
            ((target_number - result) > -6))
           command("say You were pretty close though!");
       another_try(tp);
       return 1;
    }
    else {
       command("say Congratulations, you got the right answer, " +
                tp->query_nonmet_name() + "!"); 
       if (tp->test_bit(NQ_DOM, NQ_GROUP, NQ_BIT)) {
           command("say No rewards this time, you've done it before!");
           return 1;
       } 
       else {
           i = tp->query_prop(NQ_GUESS_ATTEMPTS);
           tp->remove_prop(NQ_GUESS_ATTEMPTS);
           xp_amount = NQ_MAX_XP - (i * NQ_LOSE_XP_IF_WRONG);
           if (xp_amount < NQ_MIN_XP) xp_amount = NQ_MIN_XP;
           tp->set_bit(NQ_GROUP, NQ_BIT);
           tp->add_exp(xp_amount);
           tp->catch_msg("You feel more experienced.\n");
           tp->command("save");
           log_file("number_quest", tp->query_name() + " gets " +
                     xp_amount + " experience.\n");
           log_file("number_quest", "Expression was: " + str + ".\n");
           return 1;
       }
   }
}


/* add action for players to answer Ska */
void
init_living()
{
    ::init_living();
    add_action(got_an_answer, "answer");
    add_action(play_game, "play");
}


void
emote_hook(string emote, object actor, string adverb)
{
    if ((emote == "bow") || (emote == "curtsey"))
        set_alarm(1.0, 0.0, &command("bow " + actor->query_real_name()));
}

