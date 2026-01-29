/* 
   Obelisk control object to handle the obelisk quest out on the
   western Calia moorland. 

   Coded by Maniac.

   History:
         13/2/97     tidied up                            Maniac
         25/8/95     visions added                        Maniac
          5/7/95     messages changed                     Maniac
          21/5/95    Age desc changed                     Maniac
           3/5/95                  Created                Maniac
*/

inherit "/std/object";

#include <macros.h>
#include <composite.h>
#include <ss_types.h>
#include <state_desc.h>
#include "/d/Calia/mountain/defs.h"
#include OBELISK_QUEST

#define STATE_OBJ "/cmd/live/state"
#define AGE_MAX 100

object *players_at_obelisks = ({ }); 
string *players_mind_des = ({ }); 
string *ov = ({ });
int vision_alarm = 0;


void
init_obelisk_visions()
{
    ov = ({ ("You see a large group of official " +
           "looking men, who appear to be architects, " +
           "gathered around a large and peculiar town " +
           "plan. They seem to be having a loud and frantic argument " +
           "about it. One of them tries to tear the plan up, and is " +
           "promptly set upon by three others. A mass brawl ensues.\n"),

           ("You see a dark, far off dimension, where a hideous demonic " +
           "creature lurks. The creature's shape appears to be " +
           "shifting all the time, into various nightmarish forms. " +
           "Suddenly, the white line of a rift appears in the black " +
           "background, and the creature moves eagerly towards it, " +
           "grinning satanically.\n"),

           ("You see a large amphitheatre containing a noisy crowd. " +
            "The crowd is cheering a sporting event that is going on " +
            "below on a wide circular pitch. Groups of heavy, powerful " +
            "players are running around beating each other up and " +
            "occasionally booting or hurling a ball to their team " +
            "members. The odd thing is the ball seems to have a life " +
            "of its own, as you noticed it just scored by itself.\n"), 

           ("You see something that has the indistinct feeling of " +
           "distant future. The sun rises, and its rays glitter on the " +
           "Crystalline Palace. The mist on top of the mountain " +
           "grows thinner as the blue sky is revealed, clear as " +
           "far as the eye can see. A great and ancient shadow " +
           "seems to have departed, its weight lifted from the " +
           "land, and you get a strong sense that it will not return.\n"),

           ("You see a young warrior talking to a man in dark robes. " +
           "The darkly robed man has his gaze fixed intently on the " +
           "other, who is looking somewhat troubled, but engrossed. " +
           "Suddenly the light shifts as you see the spirit world " +
           "that underlies our reality. Where the young warrior's " +
           "head and heart are, you see a growing blackness, slowly " +
           "consuming him. Where the darkly robed man stands, " +
           "you see something so monstrous, hideous and twisted " +
           "that you have to look quickly away from it to preserve " +
           "your sanity.\n"),

           ("You see two islands in the sea, each with a great " +
           "city on it. A great turbulence begins, first in the air, " +
           "then the waters become wild, and the islands shake on their " +
           "foundations. The elemental storm picks up, becoming " +
           "a raging cataclysm, and the islands sink slowly beneath " +
           "the waves, until their last towers are gone from sight.\n"),

           ("You see the aftermath of a great battle atop Mount Kyrus. " +
           "Corpses lie everywhere in a grisly sight, most of them " +
           "krougs, but a great many are wearing the colours of " +
           "Caliana and other Calian insignia. A tall, athletic woman " +
           "is standing by the gate with a group of powerful looking " +
           "warriors. You notice that they " +
           "are looking very apprehensive about something. There appears " +
           "to be a huge, dark shape in the sky baring down on them.\n"),

           ("You see a stone fortress in the middle of a great wood. " +
           "It appears to be well hidden, but you get the impression " +
           "that there is strength inside it so great that hiding it " +
           "has become pretty unnecessary. Occasionally, groups of " +
           "well armed warriors issue forth, heading northwards.\n"),

           ("You see a young man walking through some foothills, " +
           "when suddenly the hill he is on seems to start moving. At first " +
           "guess you think it is an earthquake, but the movements seem " +
           "to actually be coordinated in a strange sort of way. The lad " +
           "looks petrified, hopping from foot to foot and running around " +
           "like a headless chicken, but before he is hurt, the shaking " +
           "slowly stops and ground regains its normality. The young man " +
           "then creeps off warily, on tip-toes.\n"),

           ("You see yourself walking through some foothills, when suddenly " +
           "a group of nasty charred black-skinned creatures surprises you " +
           "and begins hurling blows and abuse at you. You appear somewhat " +
           "taken aback, but at the same time relieved that you brought " +
           "some friends with you.\n") });

}


object 
*query_players_at_obelisks()
{
    return players_at_obelisks;
}

int
query_num_players_at_obelisks()
{
    return sizeof(players_at_obelisks);
}


int
query_connected(object tp)
{
    if ((member_array(tp, players_at_obelisks) > -1) &&
        (query_num_players_at_obelisks() == 4))
        return 1;
    else
        return 0;
}


string
query_age_des(int a)
{
    if (a <= 2)
        return "babyish";
    if (a <= 4)
        return "toddler";
    if (a <= 8)
        return "youngster";    
    if (a <= 15)
        return "youthful";
    if (a <= 28)
        return "prime";
    if (a <= 40)
        return "mature";
    if (a <= 60)
        return "old";
    if (a <= 84)
        return "very old";
    return "ancient";
}


string
query_mind_des(object tp)
{
    int i, intel, age;
    string int_des, align_des, age_des, mind_des;

    intel = tp->query_stat(SS_INT);
    age = (tp->query_age() * 2) / 86400; /* age in days */
    if (age > AGE_MAX) 
        age = AGE_MAX;

    int_des = GET_STAT_LEVEL_DESC(SS_INT, intel);
    align_des = tp->query_align_text();
    age_des = query_age_des(age);
    mind_des = age_des + ", " + align_des + ", " + int_des + " ";

    return mind_des; 
}


/* Send a random vision to the players at the obelisks */
private void
do_vision()
{
    int i, n, np;
    string s;

    if (!sizeof(ov))
        init_obelisk_visions();

    np = query_num_players_at_obelisks();
    if (np != 4)
        return;

    n = random(sizeof(ov));

    s = ov[n];

    ov = exclude_array(ov, n, n);

    for (i = 0; i < 4; i++) {
            tell_object(players_at_obelisks[i], "A vision appears..\n");
            tell_object(players_at_obelisks[i], s);
            tell_object(players_at_obelisks[i], "The vision fades..\n");
   }
   vision_alarm = set_alarm(50.0, 0.0, do_vision);  
}


/* Player thinks thoughts to the multi-mind */
void
do_think(object tp, string str)
{
    int i, j;
    string mind_des;

    j = member_array(tp, players_at_obelisks); 
    if (j == -1) 
        return;
    mind_des = players_mind_des[j]; 

    for (i = 0; i < query_num_players_at_obelisks(); i++) {
         if (i == j) 
             tell_object(tp, "Your " + mind_des + 
                             "part of the multi-mind thinks: " + str + 
                             "\n");
         else
            tell_object(players_at_obelisks[i], tp->query_name() + "'s " +
               mind_des + "part of the multi-mind thinks: " + str + "\n");
         players_at_obelisks[i]->add_mana(-2);          
   }
}



/* Returns 1 if results in multi-mind connection */
int
add_player_at_obelisk(object tp)
{
    int i, j;
    object o;
    string s;
    string *names;

    if (member_array(tp, players_at_obelisks) > -1)
        return 0;

    players_at_obelisks += ({ tp });
    players_mind_des += ({ query_mind_des(tp) }); 

    j = query_num_players_at_obelisks();


    if (j == 4) {

        names = ({ players_at_obelisks[0]->query_name(),
                   players_at_obelisks[1]->query_name(),
                   players_at_obelisks[2]->query_name(),
                   players_at_obelisks[3]->query_name() });

        for (i = 0; i < j; i++) {
            o = players_at_obelisks[i];
            tell_object(o, "You feel a very strange " +
               "sensation, your mind is becoming part of a greater " +
               "whole, a union of free wills comprising yours and " +
               "those of " + 
               COMPOSITE_WORDS(names - 
                             ({players_at_obelisks[i]->query_name() })) +
                             ".\n");
            if (!o->test_bit(OBQ_DOM, OBQ_GROUP, OBQ_BIT))
            {
               tell_object(o, "The obelisks were raised by Caliana so that " +
                   "her warriors, through the power of their united " +
                   "minds, might look into the spirit world of Calia, " +
                   "where past and future collide.\n");
               o->set_bit(OBQ_GROUP, OBQ_BIT);
               o->add_exp(OBQ_XP);
               tell_object(o, "You feel more experienced.\n");
               log_file("obelisk_quest", o->query_name() + " solved " + 
                        "obelisk quest: " + ctime(time()) + ".\n");
           }
           tell_object(o, "The Spirit of the Stones thinks: Welcome! " +
                  "Here you will receive visions of the past, present " +
                  "and future of Calia, through the power of your united " +
                  "mind! Feel free to `think' thoughts to the multi-mind " +
                  "and `disconnect' when you wish.\n");
           if (vision_alarm)
               remove_alarm(vision_alarm);
           vision_alarm = set_alarm(10.0, 0.0, do_vision);
           init_obelisk_visions();
       }
       return 1;
    }
    else {
        switch (j) {
            case 1: s = "A feeling of empty void comes from the stone. " +
                        "You feel very alone, like a piece in a jigsaw " +
                        "with three parts still missing..\n";
                    break;
            case 2: s = "You feel a vague presence of another mind " +
                        "through the stone, and an urge to join with it, " +
                        "yet you feel that just the two of you are not " +
                        "enough..\n";
                    break;
            case 3: s = "You feel the presence of two other minds through " +
                        "the stone, and an urge to join with them, yet " +
                        "you feel that the three of you are not quite " +
                        "enough..\n";
                    break;
        }
        for (i = 0; i < j; i++) 
             tell_object(players_at_obelisks[i], s);
        return 0;
   }
}


void
remove_player_at_obelisk(object tp)
{
    int i, j;
    string s;

    i = member_array(tp, players_at_obelisks); 
    if (i == -1)
        return;

    players_at_obelisks = exclude_array(players_at_obelisks, i, i);
    players_mind_des = exclude_array(players_mind_des, i, i); 

    j = query_num_players_at_obelisks(); 
    if (j != 3) {
        switch (j) {
            case 1: s = "A feeling of empty void comes from the stone. " +
                        "You feel very alone, like a piece in a jigsaw " +
                        "with three parts still missing..\n";
                    break;
            case 2: s = "You feel a vague presence of another mind " +
                        "through the stone, and an urge to join with it, " +
                        "yet you feel that just the two of you are not " +
                        "enough..\n";
                    break;
        }
        for (i = 0; i < j; i++) 
             tell_object(players_at_obelisks[i], s);
        return;
   }

    tell_object(tp, "Your senses reel for a moment as your mind " +
                  "withdraws from the multi-mind and becomes " +
                  "wholly individual again, and your thoughts return " +
                  "to their normal patterns.\n");

    remove_alarm(vision_alarm);
    vision_alarm = 0;

    for (i = 0; i < sizeof(players_at_obelisks); i++) 
        tell_object(players_at_obelisks[i], "Your senses reel for a " +
          "moment as " + tp->query_name() + "'s mind withdraws from the " +
         "multi-mind. You feel your mind becoming wholly individual " +
         "again, and your thoughts are returning to their normal " +
         "patterns.\n"); 
}


void
create_object()
{
    seteuid(getuid());
}

