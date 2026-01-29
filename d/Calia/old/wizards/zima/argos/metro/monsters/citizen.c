/* Citizen of Argos - a randomized NPC
**
** The citizens are cloned in various places throughout the city. The
** parameters of the citizens are randomized to make each a little
** unique. Of major importance is the random fidelity of the citizens.
** Approximately 1/3 of the citizens support the rebels, and have evil
** alignments. They treat visitors with disdain via the add_acts. 2/3
** of the citizens support the king, and are nice to visitors. Thus
** players can detect the alignment of citizens by seeing how they
** react to visitors. They are also on different "attack teams", so
** a "rebel" citizen will not assist a "loyal" citizen when attacked,etc.
**
**
**   Coder         Date                Action
** -------------- -------- ----------------------------------------------
** Zima           1/30/95    Created
** Zima           9/17/95    Added use of Name Server for random names
*/
inherit "/std/monster";
#include <ss_types.h>
#include <stdproperties.h>
#include <money.h>
#include <macros.h>
#include <cmdparse.h>
string *intro_resp_cmd=(({"sniff"}));  /* real values set later */
#include "defs.h"
#include "citizen.h"
#include "names.c"
 
int loyal;
 
void equip_me() {
    /* this function should be called in the room which clones the npc */
    object this=this_object();
    clone_object(WEAPON_DIR+czweapon[(random(sizeof(czweapon)))])->move(this);
    clone_object(ARMOUR_DIR+"cztunic")->move(this);
    clone_object(ARMOUR_DIR+"czcloak")->move(this);
    command("wear all");
    command("wield all");
    MONEY_MAKE_SC(random(3))->move(this);
    MONEY_MAKE_CC(random(15))->move(this);
}
 
void create_monster() {
    int    male=random(3);
    int    StatLevel=(30+(random(41)));
    string Adj1,Adj2,Pro,MyName;
 
    if (!IS_CLONE) return;
    loyal=random(3);
    if (male) {
       Adj1   = MaleAdj[(random(sizeof(MaleAdj)))];
       Adj2   = NeuterAdj[(random(sizeof(NeuterAdj)))];
       Pro    = "his";
       set_gender(0);
       set_long(
          "He is a "+Adj1+" "+Adj2+" citizen of Argos, dressed "+
          "casually in the traditional garb of the inhabitants "+
          "of the city.\n");
 
       }
    else {
       Adj1   = FemaleAdj[(random(sizeof(FemaleAdj)))];
       Adj2   = NeuterAdj[(random(sizeof(NeuterAdj)))];
       Pro    = "her";
       set_gender(1);
       set_long(
          "She is a "+Adj1+" "+Adj2+" citizen of Argos, out on her "+
          "normal daily business in the city.\n");
       }
 
    set_title("Citizen of Argos");
    MyName=random_name();
    set_name(MyName);
    add_name(({lower_case(MyName),"citizen","argosian"}));
    set_adj(({Adj1,Adj2}));
    set_race_name("human");
 
    set_act_time(10);
    if (loyal) {
       add_prop(ATTACK_TEAM,LOYAL_TEAM);
       add_act("emote glances down the streets.");
       add_act("emote nods "+Pro+" head slightly at you.");
       add_act("say greetings stranger.");
       add_act("emote smiles warmly.");
       add_act("say I hope you enjoy visiting our city.");
       add_act("say you should visit Alexis in the park.");
       add_act("say you should try our local cuisine, it is quite good.");
       add_act("say may the Tritheon bless you.");
       add_act("emote looks at you with a friendly smile.");
       set_alignment(StatLevel*4);
       intro_resp_cmd=(({"introduce myself","say Greetings stranger!"}));
       }
    else {
       add_prop(ATTACK_TEAM,REBEL_TEAM);
       add_act("emote glances down the streets.");
       add_act("emote gives you a hateful look.");
       add_act("say you are not welcome here stranger.");
       add_act("emote scowls angrily.");
       add_act("say leave town before dark, or you will not see tomorrow.");
       add_act("say the Kretans will take care of your kind soon.");
       add_act("emote turns "+Pro+" back on you.");
       add_act("say may the Tritheon curse you.");
       add_act("emote looks at you with a death wish.");
       set_alignment(-(StatLevel*4));
       intro_resp_cmd=(({"say Who cares what your name is stranger",
                         "scowl angrily"}));
       }
 
    /* let citizens roam around the city */
    set_restrain_path(ROOM_DIR);
    set_monster_home(ROOM_DIR+"aeropagus"); /* city pavillion */
    set_random_move(60);
 
    set_cact_time(5);
    add_cact("say its foreigners like you who cause all this trouble!");
    add_cact("say you'll never make it out of the city alive!");
    add_cact("emote glares at you murderingly.");
    add_cact("say if you are lucky, you will live and become a slave!");
    add_cact("say pray to your false gods that your death will be swift!");
 
    set_stats(({StatLevel,StatLevel,StatLevel,StatLevel,StatLevel,StatLevel}));
    set_skill(SS_WEP_POLEARM, StatLevel);
    set_skill(SS_WEP_SWORD,   StatLevel);
    set_skill(SS_WEP_KNIFE,   StatLevel);
    set_skill(SS_WEP_AXE,     StatLevel);
    set_skill(SS_PARRY,       StatLevel);
    set_skill(SS_DEFENCE,     StatLevel);
    set_hp(query_max_hp());
    add_prop(CONT_I_WEIGHT, 100000);
    add_prop(CONT_I_VOLUME, 100000);
    set_all_hitloc_unarmed(query_average_stat() / 4);
}
