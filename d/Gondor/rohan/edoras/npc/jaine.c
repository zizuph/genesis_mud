/*
 * Gwyneth 4 November 2000 - Replaced ~elessar/lib/goodkill.h with
 *                           /d/Gondor/common/lib/logkill.c
 */
inherit "/std/monster";

#include <ss_types.h>
#include <macros.h>
#include <stdproperties.h>
#include <living_desc.h>

#include "/d/Gondor/rohan/farm/farm/camp/defs.h"
#include "/d/Gondor/common/lib/logkill.c"
#include "/d/Gondor/bits.h"

int intro_alarm;

void
create_monster() 
{
  set_living_name("jaine");
  set_name(({"jaine","woman", "lady"}));
  set_gender(G_FEMALE);
  set_title("of Edoras");
  set_race_name("human");
  set_adj(({"petite", "refined"}));
  set_long("She is very petite, as if she eats in a disciplined manner, "
    + "just enough to stay alive, but not so much as to enjoy it. Her "
    + "mannerisms and style of dress suggest that she is refined, "
    + "and comes from a good family. She looks attractive, but not "
    + "overly appetitive.\n");
  default_config_npc(52);
  set_base_stat(SS_CON,95);
  set_base_stat(SS_STR,95);
  set_skill(SS_WEP_SWORD, random(10)+90);
  set_skill(SS_DEFENCE, random(10)+90);
  set_skill(SS_PARRY, random(10)+90);
  set_alignment(100+random(200));
  set_chat_time(12);
  add_chat("I need the sword.");
  add_chat("It's a family heirloom. I must have it.");
  add_chat("My father fell in battle with the Dunlendings.");
  add_chat("I miss daddy.");
  add_chat("They just left him there, on the battlefield.");
  add_chat("The sword... where is the sword?");
  
  add_ask( ({"dad", "daddy", "father"}), "@@ask_dad@@");
  add_ask( ({"sword", "heriloom"}), "@@ask_sword@@");
  add_ask( ({"return", "returned"}), "@@ask_returned@@");
  add_ask( ({"quest", "task", "help"}), "@@ask_quest@@");
  add_ask( ({"dunlending", "dunlendings", "battle"}), "@@ask_dunlending@@");
  add_ask( ({"reward"}), "@@ask_reward@@");
  set_default_answer("@@ask_default@@");
  
  remove_prop(NPC_M_NO_ACCEPT_GIVE);
  
  equip( ({EDORAS_DIR + "obj/jaine_sword", EDORAS_DIR + "obj/jaine_dress", EDORAS_DIR + "obj/jaine_handkerchief"}));
}

void
ask_default()
{
    command("say I miss my father.");
    command("emote wipes a tear from her eye with a handkercheif.");
}

void
ask_quest()
{
    if(TP->query_prop(QUEST))
    {
        command("say You've already helped me enough.");
        return;
    }
    if(TP->query_prop(QUESTING))
    {
        command("say I need the sword.");
        command("say Please.");
        return;
    }
    if(!TP->test_bit("gondor", JAINE_QUEST_GROUP, JAINE_QUEST_BIT))
    {
    command("say I need help. My father's sword...");
    command("emote bursts into tears.");
    TP->add_prop(QUESTING, 1);
    
    return;
    }
    else
    {
        command("say You've already returned the sword! Thank you!");
    }
}

void
ask_dad()
{
    command("say My dad was a Rider of Rohan.");
    command("say Dunlendings were causing trouble in the forest "
        + "over by the White Mountains.");
    command("emote cries a little.");
    command("say So the Riders went to put them in their place...");
    command("say Except daddy never returned.");
    command("sigh");
    command("say And when he fell, we lost his sword.");
}

void
ask_sword()
{
    command("say It's an old sword. You'll know it when you see it.");
    command("say It has gold inlays.");
    command("say I need it returned.");
}

void
ask_returned()
{
    command("say Returned. Repatriated. You know...");
    command("say I need the sword back in my hands.");
    command("say I want my children to have it one day.");
}

void
ask_dunlending()
{
    command("say The battle took place in the foothills of the White "
        + "Mountains.");
    command("emote wipes a tear from her eye.");
    command("say The Dunlendings had just pillaged a farmstead, "
        + "murdered everyone.");
    command("say Daddy said it was hard to find... ");
    command("say Anyway, one of the soldiers overheard the Dunlendings "
        + "talking and laughing after they grabbed the sword.");
    command("glare");
    command("They said they were going to put the sword in a crate and "
        + "keep it as a trophy.");
    command("emote punches her fist into the opposing palm.");
    command("say I want that sword back!");
}

void
ask_reward()
{
    command("say You have the sword? Give it to me then!");
}

/* solemnian prestige */
query_knight_prestige() {return (-5);}

public void
add_introduced(string str)
{
    object  pl;

    if (!objectp(pl = find_player(str)))
        return;

    if (pl->query_met(query_real_name()))
        return;

    if (intro_alarm && sizeof(get_alarm(intro_alarm)))
        return;

    intro_alarm = set_alarm(2.0, 0.0, &command("introduce me to "+str));
}

public void
enter_inv(object obj, object from)
{
	::enter_inv(obj, from);
    if(TP->test_bit("gondor", JAINE_QUEST_GROUP, JAINE_QUEST_BIT) && obj->id("_dunlending_quest_sword"))
    {
        command("say No, this isn't the right sword.");
        command("say You've already returned my father's sword.");
        command("thank " + TP->query_real_name());
        command("drop " + obj->query_short());
        return;
    }
    if(TP->query_prop(QUEST))
    {
        command("say You've helped me enough already. I don't need this.");
        command("drop " + obj->query_short());
        return;
    }
    if(obj->id("_dunlending_quest_sword"))
    {
        command("say Thank you so much!");
        command("say This is my father's sword. Thank you!");
        command("say I can't believe I will be able to pass this on to "
            + "my children some day.");
        command("hug " + TP->query_real_name());
        TP->set_bit(JAINE_QUEST_GROUP, JAINE_QUEST_BIT);
        TP->add_exp_quest(JAINE_QUEST_EXP);
        write("You feel a much more experienced!\n");
        LOG_QUEST(TP, JAINE_QUEST_EXP, "Return Jaine's Sword");
        obj->remove_object();
        return;
    }
    else
    {
        command("say This isn't what I wanted you to get.");
        command("emote ignores you.");
        command("emote drops the item.");
        obj->move(environment(TO));
        return;
    }
}