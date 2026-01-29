inherit "/std/monster";
#include "/d/Cirath/common/defs.h"
#include "../defs.h"
#include <std.h>
#include <stdproperties.h>
#include <ss_types.h>
#include <money.h>
#include "/d/Cirath/common/introfnc.h"
#include "/d/Cirath/quest_handler/quest_handler.h"
#define _QUEST_RING_ "_quest_ring_"

int ring;
string long;
object marek;

create_monster()
{
   set_name("marek");
   set_title("the Bartender");
   set_race_name("human");
   set_adj("large");
   add_adj("scowling");
   set_gender(0);
   set_short("large scowling human");
   set_long("Judging from both his stained apron and his place behind the "
	+"bar, you guess that this is the bartender of the Bard's Hand.  He "
	+"stands near a small nondescript door on the back wall near the bar "
	+"and seems to be monitoring who goes in it.  The people that do "
	+"don't look too savory.\n");
   set_alignment(-450);
   set_stats(({100,80,100,75,75,100}));
   set_skill(SS_WEP_CLUB,70);
   set_skill(SS_DEFENCE,70);
   set_skill(SS_PARRY,50);
   set_skill(SS_AWARENESS,50);
   set_act_time(3);
   add_act("say Do you wanna drink?");
   add_act("say I know a place where you can train certain skills.");
   add_act("say Watch out for the boys here, they can get rough.");
   add_act("emote grins evilly");
   set_cact_time(6);
   add_cact("say You shouldn't have done that!");
   add_cact("say Was that really the wizest thing you could've done?");
   add_cact("roar");
    add_ask(({"train", "training"}), "If you do a favor for me "
	+"I will let you know where you can get some additional "
	+"training.\n");
    add_ask(({"favor","help","task"}),"To get in here, you must "
	+"kill an important noble.  The noble I want you to kill "
	+"is well known for his skill with an impaler as well as "
	+"his determination.  Bring me the ring he wears and I "
   +"will let you into the training hall.\n");
    add_ask(({"members","membership","member"}),"To become a "
	+"member you have to do a task for me.\n");
   add_ask(({"murder","assassin","assassins","assassination"}),
   "Ahh...You want to get some one taken care of?  Well you've "
   +"come to the right place.  The guy you are looking for "
   +"is through the door to the north.\n");

   add_prop(LIVE_I_NEVERKNOWN,1);
   GIVE
 
}
void
arm_me()
{
   clone_object(TYR_WEP + "h_mace")->move(TO);
   command("wield all");
   clone_object(TYR_ARM+ "body_lth")->move(TO);
   clone_object(TYR_ARM + "head_lth")->move(TO);
    clone_object(TYR_ARM + "legs_lth")->move(TO);
   command("wear all");
   MONEY_MAKE_SC(random(50))->move(this_object(),1);
}

/*
public void
enter_inv(object ob, object from)
{
    if (MASTER_OB(ob) != "/d/Cirath/tyr/arm/a_ring")
    {
        ::enter_inv(ob, from);
        set_alarm(2.0,0.0,"drop_the_object",ob);
        return;
    }
    if (!interactive(from))
        return;
    else
        set_this_player(from);
    if (from->test_bit("Cirath", 1, 3))
    {
        write(query_The_name(from) + " thanks you again.\n");
        TP->catch_msg("You don't feel more experienced.\n");
    }
    else {
        write("Marek grins broadly and pats you on the back. "
	+"Well done lad, well done indeed.\n");
        TP->catch_msg("You feel more experienced.\n");
        TP->add_exp(1000);
        TP->set_bit(1,3);
    }
    ::enter_inv(ob,from);
    set_alarm(2.0,0.0,"remove_the_object",ob);
}
void
remove_the_object(object ob)
{
    command("emote holds the ring up to the light, examines it, "
	+"then disappears through a small door behind the bar.");
    if(marek = present("marek", environment(TP)))
    {
        marek -> remove_object();
    }
}
*/


ring_return()
{
    ring = 1;
}
public void
enter_inv(object ob, object from)
{
        ::enter_inv(ob,from);

        if (!from) return;

        if (ob->query_prop(_QUEST_RING_))
                set_alarm(1.0, 0.0, "got_ring", ob, from);
        else
                set_alarm(1.0, 0.0, "got_else", ob, from);
}

void
got_ring(object ob, object from)
{
        if (!interactive(from))
                return;

        set_this_player(from);
        if (QH_QUERY_QUEST_COMPLETED(from, "arman_ring"))
        {
                write(query_The_name(from) + " looks puzzled.\n");
                TP->catch_msg("You don't feel more experienced.\n");
                ob->remove_object();
        }
        else
        {
           write("Marek's eyes widen and he grins broadly.\n");
                TP->catch_msg("You feel more experienced.\n");
                QH_QUEST_COMPLETED(from,"arman_ring");
                ob->remove_object();
                set_alarm(2.0,0.0,"remove_the_object",ob);
        }
}

void
remove_the_object(object ob)
{
       command("emote holds the ring up to the light, smiles "
               +"and walks through a small door behind the bar.\n");
        if(marek = present("marek", environment(TP)))
        {
                marek -> remove_object();
        }
}

void
got_else(object ob, object from)
{
        command("say What is this?");
        command("drop "+ob->query_name());
}






