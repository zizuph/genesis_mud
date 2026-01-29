/* Child of Argos - a randomized NPC
**
**   Coder         Date                Action
** -------------- -------- ----------------------------------------------
** Zima           8/12/95    Created
** ??             6/06/98    Last update??          DD/MM/YY
** Lavellan       2/09/10    Typo here and in .h    DD/MM/YY
*/
inherit "/std/monster";
#include <ss_types.h>
#include <stdproperties.h>
#include <money.h>
#include <macros.h>
#include <cmdparse.h>
#define RESP ({"giggle","snicker","emote shies away."})
string *intro_resp_cmd=(({(RESP[(random(sizeof(RESP)))])}));
#include "defs.h"
#include "child.h"
 
void equip_me() {
    /* this function should be called in the room which clones the npc */
    object this=this_object();
    clone_object(OBJ_DIR+toy[(random(sizeof(toy)))])->move(this);
    clone_object(ARMOUR_DIR+"chtunic")->move(this);
    command("wield all");
    command("wear all");
}
 
void create_monster() {
    int    male=random(3);
    int    StatLevel=(5+(random(6)));
    string Adj1,Adj2,Pro,MyName,race;
 
    if (!IS_CLONE) return;
    Adj1   = ChildAdj[(random(sizeof(ChildAdj)))];
    Adj2   = NeuterAdj[(random(sizeof(NeuterAdj)))];
    if (male) {
       MyName = MaleName[(random(sizeof(MaleName)))];
       Pro    = "his";
       set_gender(G_MALE);
       set_long("He is a "+Adj1+" "+Adj2+" boy, dressed in a short "+
                "tunic suitable for play in the warm weather of the "+
                "valley.\n");
       }
    else {
       MyName = FemaleName[(random(sizeof(FemaleName)))];
       Pro    = "her";
       set_gender(G_FEMALE);
       set_long("She is a "+Adj1+" "+Adj2+" girl, dressed in a short "+
                "tunic suitable for play in the warm weather of the "+
                "valley.\n");
    }
 
    set_name(MyName);
   set_race_name("human");
    add_name(({lower_case(MyName),"child","argosian","child"}));
    set_adj(({Adj1,Adj2}));
    set_alignment(0);
 
    set_act_time(10);
    add_prop(ATTACK_TEAM,LOYAL_TEAM);
    add_prop(ATTACK_PASSIVE,1); /* won't help a loyal friend, but gets help */
    add_act("snicker");
    add_act("giggle");
    add_act("emote skips around.");
    add_act("emote sticks "+Pro+" tongue out at you.");
    add_act("say How did you get so ugly?");
    add_act("say Where did you get all those scars?");
    add_act("say I love bachlava!");
    add_act("say I can't play with you. You're a stranger.");
 
   /* let children roam around the city */
    set_restrain_path(ROOM_DIR);
    set_monster_home(ROOM_DIR+"park2"); /* city park is home */
    set_random_move(60);
 
    set_cact_time(5);
    add_cact("emote screams with a high pitch.");
    add_cact("emote wails pitifully");
    add_cact("shout Help me! Mama!");
 
    set_stats(({StatLevel,StatLevel,StatLevel,StatLevel,StatLevel,StatLevel}));
    set_hp(query_max_hp());
    add_prop(CONT_I_WEIGHT,50000);
    add_prop(CONT_I_VOLUME, 50000);
    set_all_hitloc_unarmed(query_average_stat() / 4);
}
 
