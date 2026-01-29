// Street child #1 (/d/Avenir/common/bazaar/NPCS/ch1.c)
// creator(s):   Triana 1994
// last update:  Lilith, 6/97.
//               Tepisch Aug 94, Ilyian May 95 (added stuff, took out stick)
// purpose:      frightened/wary child, adds ambiance to bazaar
//
// note:
// bug(s):
// to-do:        make stick for child to play with

inherit "/d/Avenir/inherit/monster.c";

#include "/d/Avenir/common/bazaar/bazaar.h"
#include "/d/Avenir/include/guilds.h"
#include <language.h>
#include <money.h>

string randadj();
string randrace();
string randshort();

int alarm_id;

void
create_monster()
{
    if (!IS_CLONE)
        return;
  
    set_name("child");
    add_name(({"child","urchin","beggar", "slave", "waif"}));
    set_race_name(randrace());
    set_gender(random(2));
    add_adj(randadj());
	set_short(randadj() +" "+ randshort());

    set_long("This little person is warily watching the crowd."+
        " From the looks of the bruises covering it, you understand"+
        " why.\n");
    default_config_npc(25 + random(6));
    add_prop(LIVE_I_NEVERKNOWN, 1);
    set_alignment(0);
    set_knight_prestige(-1);
    set_pick_up(1);

    set_act_time(2);
    add_act("emote picks its nose.");
    add_act("emote eats a booger from its finger.");
    add_act("emote plays with a stick in the dirt.");
    add_act("emote eyes you warily.");
    add_act("emote skuttles out of your way.");
    add_act("emote rubs @@query_possessive@@ growling stomach.");
    add_act(({"emote holds a booger out to you.","say Want one?"}));
    add_act("emote whispers: Watch out for the Protectors.");
    add_act("emote looks up at you with soulful eyes.");
    add_act("kicks you hard in the shin!");

    set_cact_time(3);
    add_cact("emote sobs: What did I do to you?");
    add_cact("emote bursts into tears.");
    add_cact("say Why are you beating me?");
    add_cact("say My master beat me once already today!");
    add_cact("say Ouch!");
    add_cact("shout Please don't kill me! I'm too young to die!");
    
    add_ask("[about] 'water'",
            "say I'm dying from thirst. I need water.", 1);
}

void
arm_me()
{
   seteuid(geteuid(this_object()));
   refresh_living();
   MONEY_MAKE_CC(random(40))->move(this_object());

   clone_object(BAZAAR + "Obj/wield/pclub")->move(TO);
   command("wield all");

   clone_object(BAZAAR + "Obj/worn/ppants")->move(TO, 1);
   clone_object(BAZAAR + "Obj/worn/pshoes")->move(TO, 1);
   clone_object(BAZAAR + "Obj/worn/pbelt")->move(TO, 1);
   command("wear all");
}

string
randadj()
{
    string *randadj;
    randadj = ({"small", "green-eyed", "bruised", "sad", "bored", 
        "tired", "mischievious", "serious", "scrawny", "hopeful", 
        "very young", "ebon-haired", "hungry", "frightened" });
    return randadj[random(sizeof(randadj))];
}

string
randshort()
{
    string *randshort;
    randshort = ({"child", "urchin", "beggar", "slave", "waif"});
    return randshort[random(sizeof(randshort))];
}

string
randrace()
{
    string *randrace;
    randrace = ({"human", "gnome", "dwarf"});
    return randrace[random(sizeof(randrace))];
}
string
race_sound()
{
    return "pipes";
}    

/*
 * check_meet enables the npc to greet players it
 * comes into contact with, according to guild.
 */
void
check_meet(object tp)
{
    string  occ;
	 int     i;
	 i = random(10);

	 alarm_id = 0;

	 if (!present(tp, environment(TO)))
		  return;

	 if(tp->query_prop("_is_cat_"))
	 {
		if(i<3)
		{
			tp->catch_msg(QCTNAME(this_object())+" throws "
				+"a stone at you!\n", this_object());
			tell_room(environment(this_object()),
				QCTNAME(this_object())+" throws a stone "
				+"at "+QTNAME(tp)+".\n", tp, this_object());
			return;
		}

		if(i<6)
		{
			command("scratch " +tp->query_real_name()+" chin");
			return;
		}
		return;
	 }



	 occ = tp->query_guild_name_occ();
	 if (occ == OUNION)
	 {
		  if (i == 0)
				command("say to "+ tp->query_real_name() +" Celebrate "+
					 "the Source!");
		  if (i == 2)
				command("grovel "+ tp->query_real_name());
        if (i == 4)
            command("say to "+ tp->query_real_name() +" I want "+
                "to be like you when I grow up!");
        return;
    }
    else
    {
        if (i == 1)
           command("emote taunts you!");
        if (i == 3)
           command("beg "+ tp->query_real_name());
        if (i == 5)
           command("grin know "+ tp->query_real_name());
        return;
    }
}

void
init_living()
{
    ::init_living();

    if (interactive(TP) && CAN_SEE(TO, TP))
    {
        if (alarm_id)
            return;       
        alarm_id = set_alarm(2.0, 0.0, &check_meet(TP));
        return;
    }
}  
