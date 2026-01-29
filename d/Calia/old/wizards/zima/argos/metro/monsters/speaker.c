/* ARGOS City - Speaker in the Aeropagus
**
**   Coder         Date                Action
** -------------- -------- ----------------------------------------------
** Zima           8/11/95  Created
**
*/
inherit "/std/monster";
#include <ss_types.h>
#include <stdproperties.h>
#include <money.h>
#include <macros.h>
#include <cmdparse.h>
string *intro_resp_cmd=(({"introduce myself"}));
#include "defs.h"
#include "citizen.h"
#include "names.c"
int loyal;
 
void equip_me() {
    /* this function should be called in the room which clones the npc */
    object this=this_object();
    clone_object(WEAPON_DIR+"czsword")->move(this);
    clone_object(ARMOUR_DIR+"nobtunic")->move(this);
    clone_object(ARMOUR_DIR+"nobcloak")->move(this);
    command("wear all");
    command("wield all");
    MONEY_MAKE_SC(random(6))->move(this);
    MONEY_MAKE_CC(random(30))->move(this);
}
 
void create_monster() {
    string Name=random_name();
    string Adj1=(MaleAdj[(random(sizeof(MaleAdj)))]);
    string Adj2=(NeuterAdj[(random(sizeof(NeuterAdj)))]);
 
    if (!IS_CLONE) return;
    loyal=random(3);
    set_name(Name);
    add_name(({(lower_case(Name)),"speaker","argosian"}));
    set_title("Nobleman of Argos");
    set_adj(({Adj1,Adj2}));
    set_race_name("human");
    set_long(
        "He is a "+Adj1+" "+Adj2+" nobleman of Argos, here in the "+
        "Aeropagus to speak his views on the current political situation "+
        "in the city.\n");
 
    set_act_time(5);
    if (loyal) {
       /* loyal speaker */
       add_prop(ATTACK_TEAM,LOYAL_TEAM);
       set_alignment(200);
       intro_resp_cmd=(({"shout See! Here is a friendly foreigner now!",
          "introduce myself","emote bows deeply.","say Welcome to Argos!"}));
       add_act("shout Opening our city will bring new business to us!");
       add_act("shout We should trust the wisdom of our monarch!");
       add_act("shout We can only become stronger by contact with outsiders!");
       add_act("shout Support the king and bring peace to the city!");
       add_act("shout Of course there will be some problems, but think "+
               "of all the benefits!");
       add_act("shout Look at all we have already gotten from outside the "+
               "valley!");
       add_act("emote paces on the dias.");
       }
    else { /* rebel speaker */
       add_prop(ATTACK_TEAM,REBEL_TEAM);
       intro_resp_cmd=(({"shout See how brash they are! Disrupting our "+
          "congregation!","say Begone foreigner! You bring ruin to our "+
          "city!","scowl"}));
       set_alignment(-200);
       add_act("shout Opening our city will destroy our culture!");
       add_act("shout We should not trust the thinking of the king!");
       add_act("shout We can only become overcome by contact with outsiders!");
       add_act("shout Oppose the king and bring security to the city!");
       add_act("shout We will rue the day we opened the gates!");
       add_act("shout Look at all murders we have already had since the "+
               "gates opened!");
       add_act("emote paces on the dias.");
    }
 
    set_cact_time(3);
    add_cact("say its outlanders like you who cause our problems!");
    add_cact("say may your head be chopped off!");
    add_cact("emote curses loudly in a foreign tounge.");
    add_cact("say may the Tritheon curse you and all your kind!");
 
    set_stats(({40,50,40,20,20,40}));
    set_skill(SS_PARRY, 40);
    set_skill(SS_WEP_SWORD, 40);
    set_skill(SS_DEFENCE, 40);
    set_hp(query_max_hp());
    add_prop(CONT_I_WEIGHT, 105000);
    add_prop(CONT_I_VOLUME, 105000);
    set_all_hitloc_unarmed(query_average_stat() / 4);
}
