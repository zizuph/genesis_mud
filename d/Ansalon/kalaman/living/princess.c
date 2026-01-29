/*
 * Princess of Kalaman
 *
 * Modified by Lunatari for the lovers quest 2011-06-27
 * Navarre December 15th 2011: Fixed bug with parameter value 1 being passed to calculate_experience for handkerchief quest.
 *                             This is wrong as it makes the handkerchief quest unsolveable.
 */
#include <stdproperties.h>
#include <wa_types.h>
#include <ss_types.h>
#include <macros.h>
#include "/d/Ansalon/common/defs.h"
#include "../local.h"

inherit AM_FILE

#define HANDKERCHIEF_QUEST 0
#define LOVERS_QUEST 1

void
create_krynn_monster()
{
    if(!IS_CLONE)
	return;

    set_name("kirsten");
    add_name("princess");
    set_title("the Beautiful, Princess of Kalaman");
    set_gender(1);
    set_race_name("human");
    set_adj("weeping");
    add_adj("young");
    set_long("Before you sits a princess of amazing beauty. " +
      "She seems extremely upset, and is crying into her hands.\n");

    set_stats(({45, 119, 89, 45, 45, 60}));
    set_hp(query_max_hp());

    set_skill(SS_DEFENCE, 60);

    set_alignment(450);
    set_knight_prestige(-40);
    add_prop(CONT_I_HEIGHT, 185);
    add_prop(CONT_I_WEIGHT, 49000);

    set_act_time(6);
    add_act("emote weeps pitifully into her hands.");
    add_act("say Oh my Wesley! What have they done to you?");
    add_act("emote sniffs.");
    add_act("emote sobs sadly.");
    add_act("say Oh where is a handkerchief when I need one!");

    set_cact_time(0);
    add_cact("shout Guards! Guards! I am being attacked!");
    add_cact("cower");

    add_ask("wesley",
      "say Oh my Wesley! He was thrown into the dungeons when my father " +
      "caught him trespassing. What am I to do? My one true love is rotting " +
      "in the dungeons when his only crime was to visit a lonely princess.",1);
    add_ask(({"quest","task"}),
      "say Oh my Wesley! What am I to do?",1);
    add_ask(({"father","calof","lord calof"}),
      "say My father is Lord Calof, the ruler of Kalaman.",1);
    add_ask(({"help","handkerchief"}),
      "say Would you find me a handkerchief? I seem to have lost mine, and "+
      "I must look quite a mess.",1);

    remove_prop(NPC_M_NO_ACCEPT_GIVE);

    setuid();
    seteuid(getuid());
}

/*
 * calling guards moved to the room (garden) 
 */
void
call_guards(object ob)
{
    E(TO)->princess_attacked(ob);
}

void
attacked_by(object ob)
{
    ::attacked_by(ob);
    command("shout Help! Help! Guards!");
    set_alarm(1.0, 0.0, &call_guards(ob));
}

void
init_living()
{
    ::init_living();
}

void
arm_me()
{
    clone_object(KOBJ + "armour/princess_dress")->move(TO,1);
    command("wear all");
}

void
return_intro(string who)
{
    who = L(who);
    if (P(who,E(TO)))
    {
	command("introduce myself");
    }
}

void
add_introduced(string who)
{
    set_alarm(2.0, 0.0, &return_intro(who));
}

void
calculate_experience(object who, int quest)
{
    switch (quest)
    {
      case LOVERS_QUEST:
        /* LOVE AND HATE QUEST */
      break;
	  case HANDKERCHIEF_QUEST:
        /* THE HANDKERCHEIF QUEST */
        int xp_base = 500;

        if(who->test_bit("ansalon", 0, 13))
        {
            who->catch_msg("You don't get a prize for doing this " +
              "quest twice!\n");
            return;
        }

        who->catch_msg("You feel more experienced!\n");
        if(who->query_wiz_level())
        {
            who->catch_msg("xp : " + xp_base + "\n");
        }

        who->add_exp_quest(xp_base);
        who->set_bit(0, 13);

        A_QUEST_LOG("quest","Princess Task", who, xp_base);
		break;
	  default:
		  break;
    } 
    return;
}

void
return_give_handkerchief(object from)
{
    command("smile thank");
    command("say Why thank you... this is just what I needed.");
    command("emote blows her nose daintily on the handkerchief.");
    command("say You had best leave... I don't think my father would have " +
      "the guards treat you any differently than my Wesley if he " +
      "found you out here.");

    calculate_experience(from, HANDKERCHIEF_QUEST);
}

void
give_it_back(object ob, object from)
{
    if (ob->query_no_show())
	return;

    command("emote bursts into tears.");
    command("say Wesley had something just like this.. please, " +
      "take it away.");
    command("drop " +OB_NAME(ob));
}


void
enter_inv(object ob, object from)
{
    ::enter_inv(ob, from);

    if(ob->id("_ansalon_kender_handkerchief_") || ob->id("handkerchief"))
    {
	set_alarm(1.0, 0.0, &return_give_handkerchief(from));
	return;
    }

    if(ob->id("_dress_"))
	return;

    set_alarm(1.0, 0.0, &give_it_back(ob, from));
    return;
}
