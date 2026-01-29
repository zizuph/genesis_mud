/* Original by Percy
* New easier to handle Version of the dragon, by Aridor. */
/* Converted to GRIFFON by Macker (for icewall quest) */
#include "/d/Krynn/common/defs.h"
#include "local.h"
#include "/d/Krynn/icewall/local.h"
#include <ss_types.h>
#include <macros.h>
#define N        6

inherit ICEOUTROOM;

object griffon, ob;
mixed * answer_list = ({
    ({"hive", "beehive", "bee hive", "honeycomb", "honey comb"}),
    ({"fur", "leather", "mink", "hide"}),
    ({"comb", "brush"}),
    ({"snow", "snowflake", "snow flake"}),
    ({"feather", "down", "downe"}),
    ({"money", "coin", "coins"})
});
string *riddle_list =
({" Golden treasure I contain,\n" +
"   guarded by hundreds and thousands,\n" +
"   stored in a labyrinth where no man walks, \n" +
"   yet men come often to seize my gold,\n" +
"   by smoke I am overcome and robbed,\n" +
"   then left to build my treasure anew. \n",

"   My first master has four legs,\n" +
"   my second master has two legs,\n" +
"   my first I serve in life,\n" +
"   my second I serve in death,\n" +
"   cure me and I live beyond my death,\n" +
"   tough I am, yet soft beside,\n" +
"   'gainst ladies' cheeks I oft reside.\n",

"   Metal or bone I may be,\n" +
"   many teeth I have and always bared,\n" +
"   yet my bite harms no one,\n" +
"   and ladies delight in my touch.\n",

"   High born, my touch is gentle,\n" +
"   purest white is my lace,\n" +
"   silent, silent is my kingdom,\n" +
"   green is the color of my death.\n",

"   I am the outstretched fingers\n" +
"   that seize and hold the wind,\n" +
"   wisdom flows from me in other hands,\n" +
"   upon me are sweet dreams dreamt,\n" +
"   my nearest touch brings laughter.\n",

"   I am two-faced but bear only one face,\n" +
"   I have no legs but travel widely,\n" +
"   men spill much blood over me,\n" +
"   kings leave their imprint upon me,\n" +
"   I have the greatest power when given away,\n" +
"   yet lust for me keeps me locked away.\n" });

/*prototype*/
void randomize_lists();

void
create_icewall_room()
{
    set_short("Griffon's Nest");
    set_long("You are standing on a cliff in the Vingaard Mountains. " +
         "There is a large nest here. There are also quite a few big, " +
         "strange feathers scattered about the area. You begin to wonder" +
         " what kind of creature might live here" +
         "@@dependant_long@@" + " There is a sheet of paper embedded in " +
         "the cliff wall.\n");

    add_exit(VM_ROOMS + "road7.c", "down");

    add_item(({"paper", "sheet", "sign"}), "It is a sheet of white " +
        "paper mysteriously affixed to the cliff wall. Perhaps you should "+
         "read it?\n");
    add_item(({"nest", "bird nest", "feathers", "feather", "griffon nest"}),
         "@@nest");
    add_item(({"cliff", "wall", "cliff wall", "area"}), "You are " +
         "on a cliff which juts out from the mountainside. The wall, " +
         "formed by the mountainside, " +
         "is plain and grey, except for the white sheet of paper " +
         "mysteriously afixed to it.\n");
    (LANDING2)->load_me();
    add_prop(ROOM_I_NO_CLEANUP, 1);
    add_prop(NO_DRAGON_ATTACK, 1);
    add_prop(OBJ_S_WIZINFO, "Here one can try to earn the griffon's trust " +
         "so it will take him/her to the great icewall.\n"
         + "Don't update this room or the dragon unnecessary since it can " +
         "mess things up.\n");
    randomize_lists();
}

string
dependant_long()
{
    /*Checks to see if Griffon is here*/
    if(present("griffon", TO))
      return(", but your curiosity is satisfied when you see a large " +
         "griffon in the nest.");
    else
      return(", but the nest appears to be empty.");
}

void
init()
{
    ::init();
    add_action("get_feather", "get");
    add_action("get_feather", "take");
    ADA("read");
    ADA("answer");
    ADA("whistle");
}

int
get_feather(string str)
{
    object feather;
    NF("Get what?\n");
    if(!((str=="feather")||(str=="griffon feather")))
      return 0;
    (feather=clone_object(ICE_GRIFFON + "feather.c"))->move(TO);

    write("You bend down and pick up one of the griffon feathers.\n");
    say(QCTNAME(TP) + " bends down and gets a feather off the ground.\n");

    feather->move(TP);
    return 1;
}

int
read(string str)
{
    NF("Read what?\n");
    if(!((str=="paper") || (str=="sheet of paper") ||
     (str=="sign") || (str=="sheet")))
      return 0;
    write("You read the sheet of paper....\n");
    say(QCTNAME(TP) + " reads the sheet of paper.\n");
    if(TP->test_bit("Krynn", 2,11))
      {
      write("You have already proven yourself worthy.\n");
      write("Whistle for the griffon if you wish for him to come.\n");
      return 1;
      }
    if((TP->query_prop("_player_question_number")) == 0)
      TP->add_prop("_player_question_number", 1);
    if((TP->query_prop("_player_question_number")) ==
       (TP->query_prop("_player_question_number_correct")))
      {
      if(TP->query_prop("_player_question_number")==3)
        TP->add_prop("_player_question_number", 1);
      else
        TP->add_prop("_player_question_number", (TP->query_prop("_player_question_number") + 1));
      }
    TP->catch_msg("He who wishes to ride my wings must prove himself worthy." +
          " Answer my riddles printed upon this sheet, and I shall take you " +
          "to the great Icewall!\n");
    write("You must answer two out of three riddles correctly. You will have as many chances at each riddle as you like. If you answer a riddle incorrectly, I will give you one of the other two, and you can go back to ones you missed.\n");
    write("\n");
    write(riddle_list[(TP->query_prop("_player_question_number"))]);
    write("\n                       -Griffon\n");
    write("\np.s. This is a test of your own wisdom.\n"+
      " Relying on others for answers proves not wisdom,\n"+
      " but lack thereof.\n" +
      " Consequently if I, the Griffon, or any other beings who\n" +
      " sometimes watch from the skies, catch you cheating,\n"+
      " you will be punished rather than rewarded.\n" +
      " You have been warned, ground dweller.\n");

    write("\nThere is a place at the bottom of the paper for you to \"answer <your answer>\".\n");
    return 1;
}


void
randomize_lists()
{
    int i, randnum;
    string tempq;
    mixed tempa;

    for(i = 0; i < N; i++)
      {
      randnum=random(N);
      tempq= riddle_list[randnum];
      tempa= answer_list[randnum];
      riddle_list[randnum]= riddle_list[i];
      answer_list[randnum]= answer_list[i];
      riddle_list[i]= tempq;
      answer_list[i]= tempa;
      }
}
/* Handles summoning the griffon */
int
whistle(string str)
{
    /* code to check if the quest has been solved in here
     */
    if(!(TP->test_bit("Krynn", 2, 11)))
      return 0;
    NF("Whistle for who?\n");
    if((str == "for griffon")||(str == "for the griffon"))
      {
      write("You whistle with all your force.\n");
      say(QCTNAME(TP) + " whistles a shrill sound.\n");
      seteuid(getuid(TO));
      if ((DRAGON_ROOM)->call_dragon(3))
        write("You feel that the griffon has heard you. He ought to be here soon.\n");
      else
        write(BS("You wait a while and decide the griffon is not coming. " +
             "He is probably busy at the moment, but griffons move quickly. Why don't you just try again in a bit?", 70));
      return 1;
      }
    return 0;
}

void
quest_solved()
{
    int xp;

    write("The riddle erases itself and new words appear on the "
      + "paper. You find yourself reading them as they appear...\n");
    write("You have proven yourself worthy. From now on, you may " +
      "simply come to this cliff and \"whistle for griffon\". At this, I " +
      "will gladly come and carry you on my back to the great Icewall.\n");
    /*set quest bit here*/
    if(TP->query_exp() > 1100)
    xp = 1100;
    else
    xp = TP->query_exp();

    TP->add_exp(xp, 0);

    K_QUEST_LOG("quest", "Griffon quest", TP, xp);

    TP->set_bit(2, 11);
    TP->catch_msg("You feel more experienced!\n");
    randomize_lists();
    write("The words erase themselves and new text appears.\n");
}

int
answer(string str)
{
    if(TP->test_bit("Krynn", 2, 11))
      {
      NF("You have alreay proven yourself worthy. There is no " +
         "reason for you to answer any more questions.\n");
      return 0;
      }
    NF("But you have nothing to write with. You will need a pen of some kind. Perhaps you could find something to use as a pen?\n");
    if(!(present("feather", TP)))
      {
      say(QCTNAME(TP) + " tried to write something on the paper but had no pen.\n");
      return 0;
      }

    NF("Hmm...supposing you were to use the griffon feather as a pen...\n" +
       "You have no ink. In fact, you can't recall any way of acquiring real ink around here. " +
       "Perhaps you could find some sort of ink substitute?\n");
    if(!(P("feather",TP)->query_bloody()))
      {
      say(QCTNAME(TP) + " tried to write something on the paper but had no ink.\n");
      return 0;
      }

    if((member_array(str, answer_list[TP->query_prop("_player_question_number")])) != -1)
      {
      write("Congratulations! You answered the riddle correctly!\n");
      say(QCTNAME(TP) + " wrote something on the sheet of paper.\n");
      say(QCTNAME(TP) + " looks pleased.\n");
      if(TP->query_prop("_player_question_number_correct"))
        {
        quest_solved();
        return 1;
        }
      TP->add_prop("_player_question_number_correct", TP->query_prop("_player_question_number"));
      if((TP->query_prop("_player_question_number")) == 3)
        TP->add_prop("_player_question_number", 1);
      else
        TP->add_prop("_player_question_number", (TP->query_prop("_player_question_number") + 1));
      write("You still need to answer one more riddle to prove yourself worthy.\n");
      write("The riddle erases itself before your eyes, and is replaced by a different one.\n");
      return 1;
      }
    else
      {
      write("Sorry, that was not the right answer.\n");
      say(QCTNAME(TP) + " wrote something on the sheet of paper.\n");
      say(QCTNAME(TP) + " looks a bit upset.\n");
      TP->add_prop("_player_question_number", (TP->query_prop("_player_question_number") + 1));
      if(TP->query_prop("_player_question_number_correct"))
        write("You still need to answer one more riddle to prove yourself worthy.\n");
      write("The riddle erases itself before your eyes, and is replaced by a different one.\n");
      if(TP->query_prop("_player_question_number") == 4)
        TP->add_prop("_player_question_number", 1);
      return 1;
      }

}


/* add_item descriptions. */
string
nest()
{
    if(present("griffon", TO))
      write("You have trouble looking at anything other than the griffon, because it is staring directly at you.\n");
    else
      write(BS("Judging from the size of the nest and feathers, you decide this place is probably home to a rather large griffon.", 70));
    return "";
}

