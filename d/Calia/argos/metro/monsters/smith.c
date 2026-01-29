/* ARGOS - metro - smith - in the forge
**
**   Coder         Date                Action
** -------------- -------- ----------------------------------------------
** Zima           3/5/95   Created
** Jaacar         5/09/03  Added routines for the create staff quest of
**                         Thalassia
*/
inherit "/std/monster";
#include <ss_types.h>
#include <stdproperties.h>
#include <money.h>
#include <macros.h>
#include <cmdparse.h>
string *intro_resp_cmd=(({"emote wipes the sweat from his brow.",
   "introduce myself","emote smiles heartily."}));
#include "defs.h"

#define LIVE_I_GOT_BLOCK   "_live_i_got_block"
#define LIVE_I_GOT_SHEET   "_live_i_got_sheet"

void equip_me() {
    object this=this_object();
    clone_object(ARMOUR_DIR+"cztunic")->move(this);
    clone_object(ARMOUR_DIR+"czcloak")->move(this);
    clone_object(WEAPON_DIR+"czsword")->move(this);
    clone_object(WEAPON_DIR+"fohammer")->move(this);
    command("wield all");
    command("wear all");
}
 
void create_monster() {
    if (!IS_CLONE) return;
    set_name("Sideras");
    set_name(({"sideras","smith","citizen","blacksmith"}));
    set_title("Blacksmith of Argos");
    set_adj(({"sweaty","muscular"}));
    set_race_name("human");
    set_long(
        "He is the the smith who works in the forge, his well-built "+
        "body covered in sweat from the heat.\n");
 
    add_prop(ATTACK_TEAM,LOYAL_TEAM);
    set_act_time(5);
    add_act("emote places the sword in the hot coals.");
    add_act("emote dips the sword in the barrel of water.");
    add_act("emote beats the sword with his hammer.");
    add_act("emote beats the sword with this hammer.");
    add_act("say I can make sheets of metal out of blocks of metal.");
    add_act("say Do you have anything you would like waxed or sharpened?");
 
    set_cact_time(3);
    add_cact("shout Thief!! I am being robbed!");
    add_cact("say its outlanders like you who cause our problems!");
    add_cact("say you may kill me, but you will not get one cent!");
    add_cact("say may the Kretans chop off your head!");
    add_cact("emote curses loudly in a foreign tounge.");
    add_cact("say may the Tritheon curse you and all your kind!");
 
    set_stats(({50,50,50,50,50,50}));
    set_skill(SS_PARRY, 60);
    set_skill(SS_DEFENCE, 60);
    set_skill(SS_WEP_CLUB, 60);
    set_skill(SS_WEP_SWORD, 60);
    set_hp(15000);
    set_alignment(20);
    add_prop(CONT_I_WEIGHT, 105000);
    add_prop(CONT_I_VOLUME, 105000);
    add_prop(NPC_M_NO_ACCEPT_GIVE, 0);
    set_all_hitloc_unarmed(query_average_stat() / 4);
}

void
accept_block(object block, object tp)
{
    object sheet;
    string name;

    name = tp->query_real_name();

    command("smile");
    command("emote says: Yes, I can do something with this!");
    block->add_prop(OBJ_M_NO_STEAL,1);
    if (tp->query_prop(LIVE_I_GOT_SHEET))
    {
        command("emote says: I already gave you a sheet.");
        return;
    }
    command("emote says: This would take some time to flatten.");
    command("emote says: I will just give you this sheet instead.");
    sheet = clone_object(OBJ_DIR+"metal_sheet");
    sheet->move(TO);
    command("give sheet to "+name);
    command("emote says: Perhaps another smithy might have a use for that.");
    tp->add_prop(LIVE_I_GOT_SHEET,1);
    tp->remove_prop(LIVE_I_GOT_BLOCK);
}

void
drop_stuff(object ob)
{
     if (!objectp(ob))
         return;

     command("emote looks curiously at " + LANG_THESHORT(ob) + "."); 
     command("shrug");
     command("emote says: What would I want this for?");
     command("drop " + OB_NAME(ob));
}

void
do_smile()
{
    command("smile");
}

void
enter_inv(object ob, object from)
{
    ::enter_inv(ob, from); 

    if (ob->id("_block_of_silver_"))  
        set_alarm(1.0, 0.0, &accept_block(ob,from));

    else if (ob->id("_sheet_of_silver_"))
        set_alarm(1.0, 0.0, &do_smile());

    else if (ob->id("tunic"))
        set_alarm(1.0, 0.0, &do_smile());

    else if (ob->id("cloak"))
        set_alarm(1.0, 0.0, &do_smile());

    else if (ob->id("sword"))
        set_alarm(1.0, 0.0, &do_smile());

    else if (ob->id("hammer"))
        set_alarm(1.0, 0.0, &do_smile());

    else 
        set_alarm(1.0, 0.0, &drop_stuff(ob));
}

 
