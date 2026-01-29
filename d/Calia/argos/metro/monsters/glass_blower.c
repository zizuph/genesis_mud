/* ARGOS City - Glass Blower
**
**   Coder         Date                Action
** -------------- -------- ----------------------------------------------
** Zima           8/11/95  Created
** Jaacar         5/09/03  Added routines for the create staff quest of
**                         Thalassia
**
*/
inherit "/std/monster";
#include <ss_types.h>
#include <stdproperties.h>
#include <money.h>
#include <macros.h>
#include <cmdparse.h>
string *intro_resp_cmd=(({"introduce myself",
                          "say Careful not to break anything.",
                          "emote eyes you carefully."}));
#include "defs.h"

#define LIVE_I_GAVE_MIRROR "_live_i_gave_mirror"
#define LIVE_I_GAVE_FRAME  "_live_i_gave_frame"
 
void equip_me() {
    /* this function should be called in the room which clones the npc */
    object this=this_object();
    clone_object(ARMOUR_DIR+"cztunic")->move(this);
    clone_object(ARMOUR_DIR+"czcloak")->move(this);
    command("wield all");
}
 
void create_monster() {
    if (!IS_CLONE) return;
    set_name("Gaulios");
    add_name(({"gaulios","keeper","argosian"}));
    set_title("Crystal Artisan of Argos");
    set_adj("tall");
    set_adj("tanned");
    set_race_name("human");
    set_long("He is a tall tanned human, one of the gifted artisans of the "+
        "city. He creates both beautiful and useful objects from glass "+
        "and crystal.\n");
 
    set_act_time(10);
    add_act("greet all");
    add_act("smile happily");
    add_act("say Would you like to buy a hand made bottle?");
    add_act("say Be careful not to break anything.");
    add_act("say I can make glass out of sand.");
    add_act("emote eyes you worriedly.");
    add_act("say My finer works are not for sale to visitors.");
 
    set_cact_time(3);
    add_cact("shout Thief!! I am being robbed!");
    add_cact("say Its outlanders like you who cause our problems!");
    add_cact("say You may kill me, but you will not get one cent!");
    add_cact("say May the Kretans chop off your head!");
    add_cact("emote curses loudly in a foreign tounge.");
    add_cact("say May the Tritheon curse you and all your kind!");
 
    set_stats(({40,50,40,20,20,40}));
    set_skill(SS_UNARM_COMBAT, 40);
    set_skill(SS_DEFENCE, 40);
    set_hp(query_max_hp());
    set_alignment(100);
    add_prop(CONT_I_WEIGHT, 105000);
    add_prop(CONT_I_VOLUME, 105000);
    add_prop(NPC_M_NO_ACCEPT_GIVE, 0);
    set_all_hitloc_unarmed(query_average_stat() / 4);
}

void
accept_sand(object sand, object tp)
{
    string name;
    object glass;

   name = tp->query_real_name();
   command("smile");
   command("emote says: Yes, I can do something with this!");
   sand->add_prop(OBJ_M_NO_STEAL,1);
   command("emote takes a metal bowl out of the cabinet.");
   command("emote puts the sand into the metal bowl.");
   command("emote opens the second side of the cabinet, revealing "+
        "a forge. He places the metal bowl into the forge and closes "+
        "the door. After a few moments he opens the door and pulls out "+
        "the metal bowl with a glove.");
   command("emote pours the contents of the bowl into a metal mold.");
   command("tap");
   command("tap");
   command("emote says: Hmm, this might take some time.");
   command("think");
   command("emote says: Ah! I know! I shall give you this sheet of glass "+
        "instead. It is the finest work I have ever done.");
   glass = clone_object(OBJ_DIR+"glass_sheet");
   glass->move(TO);
   command("give glass to "+name);
   command("emote says: If you had this made into mirrored glass, and you "+
        "had a nice frame to put it in, I could make you a nice mirror.");
}

void
accept_mirror(object mirror, object tp)
{
    object fancy_mirror;
    string name;

    name = tp->query_real_name();

    command("smile");
    command("emote says: Yes, I can do something with this!");
    mirror->add_prop(OBJ_M_NO_STEAL,1);
    if(TP->query_prop(LIVE_I_GAVE_FRAME))
    {
        command("emote says: Most excellent! I shall get to work "+
            "immediately!");
        fancy_mirror = clone_object(OBJ_DIR+"fancy_mirror");
        fancy_mirror->move(TO);
        command("emote delicately turns the frame over onto its front.");
        command("emote gently places the mirrored glass onto the frame "+
            "and cuts it so that it will fit into the frame.");
        command("emote glues the mirrored glass into the frame, then "+
            "reinforces it with some very tiny nails.");
        command("emote places a beautiful silver backing onto the frame.");
        command("emote says: All finished! Here you are!");
        command("give fancy mirror to "+name);
        tp->remove_prop(LIVE_I_GAVE_FRAME);
        tp->remove_prop(LIVE_I_GAVE_MIRROR);
        return;
    }

    command("emote says: Most excellent. Now if I had a frame to put it "+
        "in, I could make a beautiful mirror. I have heard a rumour that "+
        "the mermaid that sits upon the rock in the sea makes frames.");
    tp->add_prop(LIVE_I_GAVE_MIRROR,1);
}

void
accept_frame(object frame, object tp)
{
    object fancy_mirror;
    string name;

    name = tp->query_real_name();

    command("smile");
    command("emote says: Yes, I can do something with this!");
    frame->add_prop(OBJ_M_NO_STEAL,1);
    if(TP->query_prop(LIVE_I_GAVE_MIRROR))
    {
        command("emote says: Most excellent! I shall get to work "+
            "immediately!");
        fancy_mirror = clone_object(OBJ_DIR+"fancy_mirror");
        fancy_mirror->move(TO);
        command("emote delicately turns the frame over onto its front.");
        command("emote gently places the mirrored glass onto the frame "+
            "and cuts it so that it will fit into the frame.");
        command("emote glues the mirrored glass into the frame, then "+
            "reinforces it with some very tiny nails.");
        command("emote places a beautiful silver backing onto the frame.");
        command("emote says: All finished! Here you are!");
        command("give fancy mirror to "+name);
        tp->remove_prop(LIVE_I_GAVE_FRAME);
        tp->remove_prop(LIVE_I_GAVE_MIRROR);
        return;
    }

    command("emote says: Most excellent. Now if I had a piece of mirrored "+
        "glass to put in it, I could make a beautiful mirror.");
    tp->add_prop(LIVE_I_GAVE_FRAME,1);
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

    if (ob->id("_handful_of_sand_"))  
        set_alarm(1.0, 0.0, &accept_sand(ob,from));

    else if (ob->id("_seashell_frame_"))
        set_alarm(1.0, 0.0, &accept_frame(ob,from));

    else if (ob->id("_sheet_of_mirrored_glass_"))
        set_alarm(1.0, 0.0, &accept_mirror(ob,from));

    else if (ob->id("_sheet_of_glass_"))
        set_alarm(1.0, 0.0, &do_smile());

    else if (ob->id("_fancy_mirror_"))
        set_alarm(1.0, 0.0, &do_smile());

    else if (ob->id("cloak"))
        set_alarm(1.0, 0.0, &do_smile());

    else if (ob->id("tunic"))
        set_alarm(1.0, 0.0, &do_smile());

    else 
        set_alarm(1.0, 0.0, &drop_stuff(ob));
}
 
 
