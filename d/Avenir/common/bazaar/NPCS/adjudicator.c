//-*-C++-*-
// file name:     /d/Avenir/common/bazaar/NPCS/adjudicator  
// creator(s):    Lilith    9/17/97
// purpose:       Shadow-elf judges in the Tribunal.
// note:          
// last update:             
// bug(s):
// to-do:

#pragma strict_types

inherit "/d/Avenir/inherit/sybarite";
inherit "/d/Avenir/inherit/helper";
inherit "/d/Avenir/inherit/death_crier";
inherit "/d/Avenir/inherit/intro";
inherit "/d/Avenir/inherit/log_asks";

#include "/d/Avenir/include/defs.h"
#include "/d/Avenir/include/paths.h"
#include "/d/Avenir/include/guilds.h"
#include "/d/Avenir/include/relation.h"

#include <composite.h>
#include <macros.h>
#include <stdproperties.h>
#include <money.h>
#include <language.h>
#include <ss_types.h>

mixed *everyone = ({
    ({ "hermara", "icu", "Ra'let", ({ "solemn", "attentive" }),
       "intense and cyan blue", "deep auburn",  
       "fire lizard on a field of black, bordered in green"}),
    ({ "damus", "icu", "Llin", ({ "impassive", "upright" }), 
       "suspicious and dark brown", "soot-black",
       "black lily on a field of yellow, bordered in crimson" }),
    ({ "shadran", "ini", "Sisaer", ({ "grave", "thoughtful" }), 
       "indifferent and steely gray", "black",
       "wand and scourge on a field of blue, bordered in purple" }),
    ({ "ijis", "ini", "Imsa-sa", ({ "sombre", "gaunt" }), 
       "cryptic and cinnamon-brown", "dark brown",
       "white and blue diagonal stripes, bordered in crimson" }),
    ({ "paxit", "dei", "F'niel", ({ "shrewd", "gentlemanly" }), 
       "alert and deep gray", "soot-black",
       "gold cup on a field of orange, bordered in green" }),
    ({ "bithael", "dei", "Atrei", ({ "solemn", "soft-spoken" }), 
       "keen and black", "chocolate-brown",
       "blue and yellow chequers, bordered in crimson" }),
	 ({ "klonca", "ini", "Qasz", ({ "pensive",  "frowning" }),
       "somber and cinnamon-brown", "deep auburn", 
       "white crescent on a field of black, bordered in purple" }),
    ({ "hanji", "icu", "Wer'a", ({ "serious", "fine-boned" }),
       "stony and black", "brown", 
       "blue flame on a field of white, bordered in green" }),
    ({ "quist", "dei", "Vyis", ({ "grim", "scrupulous" }),
       "incredulous and very blue", "black",
       "gold cat on a field of brown, bordered in green" }),
    ({ "traecil", "dei", "Cimron", ({ "somber", "distinguished" }), 
       "yellow, with an unnerving glint", "black",
       "white cygnet on a field of blue, bordered in crimson" }),
    ({ "fynsig", "icu", "Primdel", ({ "dignified", "thoughtful" }), 
       "wistful and gray-green", "black",
       "brown quarterstaff on a field of orange, bordered in green" }),
    ({ "kimiel", "dei", "Ummus", ({ "philosophical", "old" }), 
       "reflective blue-black windows", "golden brown",
       "white pentacle on a field of black, bordered in crimson" }),
    ({ "boras", "ini", "Abun'ana", ({ "lovely", "grave" }), 
       "smiling and grayish", "coal-black",
		 "gold brazier on a field of blue, bordered in purple" }),
});

object sword;
int who, me, herb, alarm_id1, alarm_id2;
string attrib, eyes, hair, house, prefix, sigil;

string query_eyes()   {    return eyes;      }
string query_hair()   {    return hair;      }
string query_house()  {    return house;     }  
string query_prefix() {    return prefix;    }  
string query_sigil()  {    return sigil;     }
int    query_who()    {    return me;        }

void set_eyes(string str)   {    eyes = str;      }
void set_hair(string str)   {    hair = str;      }
void set_house(string str)  {    house = str;     }  
void set_prefix(string str) {    prefix = str;    }
void set_sigil(string str)  {    sigil = str;     }
void set_who(int who)       {    me = who;        } 

void set_helper();
string my_long();

/* 
 * set_morph sets the various attributes of the 
 * npc, making it unique in 10 different ways.
 */
void
set_morph(int who)
{
    mixed someone;

    if (who < 0 || who >= sizeof(everyone))
       who = (random(sizeof(everyone)));

    someone = everyone[who];
    set_name(someone[0]);
    set_prefix(someone[1]);
    set_house(someone[2]);
	 set_adj(someone[3]);
    set_eyes(someone[4]);
    set_hair(someone[5]);
    set_sigil(someone[6]);
    set_who(who);
}

string
my_title()
{
    return ""+ query_prefix() +" "+ query_house() +", Adjudicator";
}

/* Create the npc */
void
create_monster()
{
    /* If I'm not a clone, don't proceed */
    if (!IS_CLONE)
        return;

    /* Lets make sure the sybarite stuff is initialized */
    ::create_sybarite();

    /* You're all individuals! */
    set_morph(random(sizeof(everyone)));

    set_race_name("shadow-elf");
    set_gender(G_FEMALE);
    set_long(my_long);
    add_name(({"adjudicator","elf","shadow elf","judge","noble",
               "noble woman", "female"}));
    set_title(my_title());
    set_alignment(0);
    set_appearance_offset(-10); // always the 'handsome' devils ;)
    set_knight_prestige(500);  
    default_config_npc(random(70) + 50);

    set_skill(SS_DEFENCE, 85);
    set_skill(SS_AWARENESS, 40 + random(25));
	 set_skill(SS_WEP_KNIFE, 80);
    set_skill(SS_BLIND_COMBAT, 80);
    set_skill(SS_PARRY, 85);
    set_all_attack_unarmed(30, 30);
    set_all_hitloc_unarmed(35);

    if (random(3))
        add_leftover("/d/Avenir/inherit/leftover", "heart",1, "", 0,0);

    add_prop(LIVE_I_SEE_INVIS, 1 + random(8));
    add_prop(LIVE_I_QUICKNESS, 50 + random(25));
    add_prop(NPC_I_NO_RUN_AWAY,1);
    add_prop(NPC_I_NO_FEAR, 1);
    MAKE_SYBARITE; 

    set_act_time(1);
      add_act("sigh .");
      add_act("smile grim");
      add_act("emote looks pointedly at you.");
      add_act("emote clenches the arms of her chair.");
		add_act("say We will wait until our uninvited guest leaves "+
          "before proceeding with this case.");
      add_act("emote impales you with a contemptuous glare.");
      add_act("adjust stole");
      add_act("shuffles some papers.");
      add_act("say I must insist that you leave immediately.");
      add_act("emote says to you: These proceedings are not open to "+
          "the public.");
    set_cact_time(4);
      add_cact("laugh contempt enemy");
      add_cact("shout Plalgus smite you!");
      add_cact("You'll writhe on the pillory for this.");
      add_cact("say I'll see you hung by your thumbs for this.");
      add_cact("say You are a fool!");
      add_cact("emote smiles the chilling smile of one who has near "+
          "absolute power.");
      add_cact("emote dances swiftly and gracefully around you.");
      add_cact("slaugh");

    set_default_answer(VBFC_ME("what_me"));
		add_ask(({"holm", "park"}), "say That's where the Hunt takes "+
          "place, and where I often consign prisoners to spend the "+
          "rest of their lives.", 1);
      add_ask(({"bath", "melchior's bath", "bathhouse"}),
          "say There is a bathhouse in the City. I'll be "+
          "soaking myself there when I've finished today.",1);
      add_ask(({"bazaar"}),
          "say Its north and west of here.",1);
      add_ask("city", "smile myst",1);
      add_ask(({"task", "job", "quest", "help"}),  VBFC_ME("give_task"));
      add_ask(({"infidel","infidels", "prisoner", "prisoners", 
          "criminals"}),
          "say Criminals don't live long in Sybarus",1);
      add_ask(({"faithful","faithfuls","Faithful", "sybarite", "sybarites"}),
          "say We of Sybarus are the Faithful. We live to serve and "+
          "uphold the Pact, that the Source will always cast its illum"+
          "ination upon us.",1);
      add_ask(({"reckoning", "Reckoning","trial", "judgement"}),
          "say Those who are unable to prove their innocence to the "+
          "Inquisitors are brought to me for Reckoning, or judgement. "+     
			 "It is I who decides what the punishment is to be.", 1);

    /* So she helps others under attack. See set_helper() below. */
    set_helper(); 
}

/*
 * equip_me is called in the npc when it is cloned by the 
 * placer module.
 */
void 
equip_me()
{
    // add object stole, later
    object dagger, boots, robe;
    int i;

    seteuid(getuid());

    i = random(10);
	 MONEY_MAKE_SC(i)->move(TO);
    MONEY_MAKE_PC(1)->move(TO);

    dagger = clone_object(COM +"obj/knife");
    dagger->move(TO);
   
    boots = clone_object(HOLM +"obj/boots");
    boots->move(TO);

    robe = clone_object(HOLM +"obj/burnous");
    robe->move(TO);

//    stole = clone_object(BAZ_OBJ +"worn/a_stole"); 
//    stole->set_sigil(sigil);
//    stole->move(TO);     
    
    command("wear all");
}

string 
query_exp_title()
{
    return "sybarite";
}

string
my_long()
{
    string  str;

    str = "She is "+ LANG_ADDART(implode(query_adjs(), " ")) +" "+
           query_race_name()+".\n";

    if (TP->query_met(query_real_name()))
    {
        str = query_name() +" is "+ LANG_ADDART(implode(query_adjs()," ")) 
            + " "+ query_race_name() +", presenting herself as:\n" 
            + query_name();
        if (strlen(query_title()))
            str += " "+ query_title() +",";
		  str += " "+ query_exp_title() +", female "+ query_race_name() +".\n";
    }

    str += "She has the grace and dignity of bearing "+
         "characteristic of shadow-elves. Her skin is so pale and "+
         "translucent it is tinted blue in some places by her veins.\n"+
         "She is wearing an ermine stole marked with the escutcheon of "+
         "her House: a "+ query_sigil() +".\n"+
         "Her long "+ query_hair() +" hair is elaborately braided.\n"+
         "Her eyes are "+ query_eyes() +".\n";
    return str;
}

/* 
 * set_helper() is from the Avenir/inherit/helper
 * It does some nifty things I want done here ;)
 */
void
set_helper()
{
	 string *actions = ({ "shout Plalgus smite you with the Hammer of Judgement!",
                         "say One of my peers is in danger!",
                         "say Pray to your gods, sin'ur, for Death stares at "+
                         "you through mine eyes.",
                         "say Fool! You bring the wrath of the Gods upon "+
                         "your head!"  });

    set_helper_friends( ({"adjudicator", "inquisitor"}) );
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
    i = random(6);

    if (!present(tp, environment(TO)))
		  return;

	 if(tp->query_prop("_is_cat_"))
	 {
		if(i<5)
		{
			command("say Get this filthy beast out of here!");
			return;
		}
		return;
	 }

	 if (tp->query_met(query_real_name()))
	 {
		  if (IS_SYBARITE(tp) && (i == 3 || i == 5))
		  {
				command("say to "+ tp->query_real_name() +
					 " Again, I point out that you are not invited to "+
					 "this prisoner's Reckoning. Please leave.");
				return;
		  }
		  else
		  {
				command("say to "+ tp->query_real_name() +" You again!");
				command("say I told you to leave!");
				command("shout Guards!");
				return;
		  }
		  return;
	 }
	 if (IS_SYBARITE(tp))
	 {
		  command("say to "+ tp->query_real_name() +
				" This is a Reckoning to which you are not invited.");
		  command("say to "+ tp->query_real_name() +
				" Your business will have to wait. Please leave.");
		  return;
	 }
	 else
	 {
		  if (i == 2 || i == 4)
		  {
				command("say to "+ tp->query_real_name() +
					 " You don't belong here. Leave.");
				command("emote gestures in your direction with her left hand.\n");
				return;
		  }
	 }
}

void
init_living()
{
	 ::init_living();

	 if (interactive(TP) && CAN_SEE(TO, TP))
	 {
		  if (alarm_id1)
				return;
		  alarm_id1 = set_alarm(4.0, 0.0, &check_meet(TP));
		  return;
	 }
	 if (IS_SYBARITE(TP) && (!interactive(TP)))
	 {
		  team_join(TP);
		  TP->set_leader(TO);
		  return;
	 }
}


string
what_me()
{
	 if (!CAN_SEE(TO, TP))
	 {
		  command("say Interesting, indeed, that the air asks "+
				"questions without the voice of a God.");
		  command("say Reveal yourself, coward!");
		  return "";
	 }
	 command("say I'm presiding over a Reckoning. I don't have time "+
		  "for questions!");
	 return "";
}

string
give_task()
{
	 if (!CAN_SEE(TO, TP))
	 {
		  command("emote looks around suspiciously");
		  command("say The air speaks not in the voice of a "+
				"God.");
		  command("say You are the spawn of a coward and a thief!");
		  return "";
	 }
	 if (IS_SYBARITE(TP))
	 {
		  command("say to "+ TP->query_real_name() +
				" I require no assistance.");
		  return "";
	 }
	 else
	 {
		  command("say What are you doing here?");
		  command("say Leave!");
		  return "";
	 }
}

/* *************** What we do when attacked ****************** */
void
attacked_by(object ob)
{
	 ::attacked_by(ob);

	 heal_hp(query_max_hp());
	 if (alarm_id2)
		  return;
	 alarm_id2 = set_alarm(2.0, 0.0, &command("wield all"));
}

int
special_attack(object victim)
{
	 switch (random(10))
	 {
		  case 0: command("cdisarm");
				return 1;
		  case 2: command("heal");
				return 0;
		  case 3: command("punch");
				return 1;
		  case 5: command("heal");
				return 0;
		  case 7: command("pluck");
				return 1;
		  case 9: command("cure");
				return 0;
		  default:
	 }
	 return 0;
}

string race_sound() {   return "speaks with quiet authority";   }
