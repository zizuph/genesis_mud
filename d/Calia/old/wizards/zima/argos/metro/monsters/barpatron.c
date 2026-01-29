/* ARGOS City - Bar Patron - a randomized NPC
**
**   Coder         Date                Action
** -------------- -------- ----------------------------------------------
** Zima           5/5/95     Created
*/
inherit "/std/monster";
#include <ss_types.h>
#include <stdproperties.h>
#include <money.h>
#include <macros.h>
#include <cmdparse.h>
string *intro_resp_cmd=(({"sniff"})); /* changed below */
#include "defs.h"
#include "citizen.h"
#include "names.c"
 
#define DrunkAdj    ({"buzzed","tipsy","drunken","drunk","stoned"})
 
int loyal;
 
void equip_me() {
    /* this function should be called in the room which clones the npc */
    object this=this_object();
    clone_object(WEAPON_DIR+czweapon[(random(sizeof(czweapon)))])->move(this);
    clone_object(ARMOUR_DIR+"cztunic")->move(this);
    clone_object(ARMOUR_DIR+"czcloak")->move(this);
    clone_object(OBJ_DIR+"ouzo")->move(this);
    command("wear all");
    command("wield all");
    MONEY_MAKE_SC(random(3))->move(this);
    MONEY_MAKE_CC(random(15))->move(this);
}
 
void create_monster() {
    int    StatLevel=(30+(random(41)));
    string Adj1,Adj2,MyName;
 
    if (!IS_CLONE) return;
    loyal=random(3);
    MyName = random_name();
    Adj1   = DrunkAdj[(random(sizeof(DrunkAdj)))];
    Adj2   = MaleAdj[(random(sizeof(MaleAdj)))];
    set_gender(0);
    set_long(
       "He is a one of the regulars at the pub, a "+Adj1+" "+Adj2+
       " man dressed in a customary casual tunic. He has an ouzo in "+
       "his hand and smells like he's already finished a few.\n");
 
    set_title("Citizen of Argos");
    set_name(MyName);
    add_name(({lower_case(MyName),"citizen","argosian","human"}));
    set_adj(({Adj1,Adj2}));
    set_race_name("human");
 
    set_act_time(10);
    if (loyal)
       {
       add_prop(ATTACK_TEAM,LOYAL_TEAM);
       add_act("emote gulps some ouzo.");
       add_act("emote nods his head slightly at you.");
       add_act("say greetings stranger.");
       add_act("emote grins drunkenly.");
       add_act("say Have some ouzo *hiccup* its the greatest!");
       add_act("say If you're tough enough, try the Ouisku.");
       add_act("emote looks at you in a drunken stupor.");
       set_alignment(StatLevel*4);
       intro_resp_cmd=(({"introduce myself","say A toast to the foreigner!",
                         "emote takes a gulp of ouzo.","hiccup"}));
       }
    else
       {
       add_prop(ATTACK_TEAM,REBEL_TEAM);
       add_act("emote glances out the door.");
       add_act("emote gives you a hateful look.");
       add_act("say Why don't you go back where you came from, stranger.");
       add_act("emote scowls angrily.");
       add_act("say Leave town before dark, or you will not see tomorrow.");
       add_act("say What's your poison, stranger? I have some for you.");
       add_act("emote turns his back on you.");
       add_act("emote looks at you with a death wish.");
       set_alignment(-(StatLevel*4));
       intro_resp_cmd=(({"say Get out foreigner, you are not welcome here!",
                         "spit","emote sips on an ouzo."}));
       }
 
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
 
