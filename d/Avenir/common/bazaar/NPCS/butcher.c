// Drasbin the Butcher
// creator(s):	Lilith, Sept 1997
// last update:
// purpose:
// note:
// bug(s):
// to-do:

# pragma strict_types
# include "/d/Avenir/common/bazaar/bazaar.h"
# include <language.h>
# include <money.h>
# include <ss_types.h>
# include <stdproperties.h>
inherit "/d/Avenir/inherit/monster";
inherit "/d/Avenir/inherit/intro";

int alarm_id;

void
create_monster()
{
	 set_name("drasbin");
	 set_title("ini Or'miasl, Master Butcher");
	 add_name(({"shopkeeper","keeper", "butcher", "merchant"}));
	 set_race_name("dwarf");
	 set_gender(G_MALE);

	 add_adj(({"thick-armed", "barrel-chested"}));
	 set_long("This hard-working dwarf takes great pride in "+
		  "his work and reputation as one of the most capable "+
		  "butchers in the business.\n");

	 set_act_time(2);
	 add_act("emote hacks at a corpse.");
	 add_act("emote sharpens a butcher knife.");
	 add_act("emote tosses some thigh bones into a bin.");
	 add_act("emote suddenly smiles in a self-satisfied way.");
	 add_act("emote swiftly and expertly skins a corpse.");
	 add_act("emote gently cuts a thick steak from a corpse.");
	 add_act("emote gets busy packing some sausage.");
	 add_act("emote uses the apron to wipe his hands clean.");
	 add_act("stretch tired");
	 add_act("emote weighs some meat and nods to himself.");
	 add_act("@@do_fill");

	 set_default_answer(VBFC_ME("what_me"));

	 add_ask(({"intestine", "intestines", "organs"}),
		  "say There should be some in the barrel there.", 1);
	 add_ask(({"corpse", "dress", "dress corpse", "butcher" }),
		  "say I butcher corpses, for a fee. Read the sign if "+
		  "you want to know more. I'm busy.", 1);

	 set_all_hitloc_unarmed(50);

	 set_stats(({70,70,70,70,70}));

	 set_skill(SS_UNARM_COMBAT,50);
	 set_skill(SS_BLIND_COMBAT,50);
	 set_skill(SS_PARRY,50);
	 set_skill(SS_DEFENCE,85);
	 set_skill(SS_AWARENESS,50);
	 add_prop(NPC_I_NO_RUN_AWAY,1);

	 set_alignment(0);
	 set_knight_prestige(-1);

	 set_mm_in("arrives.");
}

public void
arm_me()
{
	 object apron, pants;

	 seteuid(geteuid(this_object()));
	 MONEY_MAKE_SC(random(20))->move(this_object());

	 apron = clone_object(BAZAAR + "Obj/worn/apron");
	 apron->move(TO, 1);

	 pants = clone_object(BAZAAR + "Obj/worn/menpants");
	 pants->create_tailored();
	 pants->move(TO, 1);

	 command("wear all");
}

void
do_fill()
{
	 object b;
	 b = present("barrel", environment(TO));

	 if (b)
	 {
		  b->fill_barrel();
		  command("emote scoops up some organs and puts them in the "+
				"pristine barrel.");
	 }
	 return;
}

string
what_me()
{
	 if (!CAN_SEE(TO, TP))
	 {
		  command("say I do not answer those whom I cannot see.");
		  return "";
	 }

	 switch(random(4))
	 {
		  case 0:
		  {
				command("shrug sadly");
				command("say I am a butcher, not a gossip.");
				break;
		  }
		  case 1:
		  {
				command("say What are you, an agent of the Inquisitor?");
				command("sneer");
				break;
		  }
		  case 2:
		  {
				command("emote suddenly looks fearful.");
				command("say Go away, please.");
				break;
		  }
    }
    return "";    
}

/*
 * check_meet enables the npc to greet players it
 * comes into contact with, according to guild.
 */
void
check_meet(object tp)
{
	 int i = random(3);
	 alarm_id = 0;

	 if (!present(tp, environment(TO)))
		  return;
	if(tp->query_prop("_is_cat_"))
	{
		if(i==0)
		{
			command("say to "+tp->query_real_name()+" I "
				+"have no scraps for you today.");
			command("pet "+tp->query_real_name());
			return;
		}

		if(i==1)
		{
			command("say to "+tp->query_real_name()
				+" Come back later, kitty. Maybe I'll "
				+"have some juicy intestines for you.");
			command("pat "+tp->query_real_name()+" head");
			return;
		}
		return;
	}

	 if (random(4))
		 command("say Hello! Are you here to have a corpse "+
					"butchered?");
}

void
init_living()
{
	 ::init_living();

	 if (interactive(TP) && CAN_SEE(TO, TP))
	 {
        if (alarm_id)
            return;
        else
            alarm_id = set_alarm(2.0, 0.0, &check_meet(TP));
        return;
    }
}  


