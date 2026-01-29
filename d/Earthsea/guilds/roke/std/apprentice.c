#include <ss_types.h>
#include <filter_funs.h>
#include <language.h>
#include <macros.h>

#define APPRENTICE_DAGGER "/d/Earthsea/guilds/roke/std/wep/c_dagger"
#define APPRENTICE_SPEAR "/d/Earthsea/guilds/roke/std/wep/spear"
#define APPRENTICE_CLOAK "/d/Earthsea/guilds/roke/std/arm/cloak"
#define APPRENTICE_BOOTS "/d/Earthsea/guilds/roke/std/arm/g_boots"
#define APPRENTICE_JERKIN "/d/Earthsea/guilds/roke/std/arm/jerkin"
#define APPRENTICE_HELM "/d/Earthsea/guilds/roke/std/arm/leather_helm"

#define SPELLS "/d/Earthsea/guilds/roke/obj/roke_spells"
#define ROKE_I_HAS_ARMA "_roke_i_has_arma"

inherit "/d/Earthsea/std/monster";
#define RACE_NAMES ({"human", "elf", "gnome", "hobbit", "dwarf", \
                     "half-elf"})
#define ADJS1 ({"patronizing", "good-looking", "friendly", "helpful", \
                "serious-looking", "blue-eyed", "blond-haired", \
                "red-haired", "dark-haired", "dark-eyed", "jolly", \
                "arrogant", "cheerful", "pretentious", "wild-eyed", \
                "intelligent", "dark-haired", "bright-eyed", "dour"})
#define ADJS2 ({"robust", "calculating", "ambitious", \
                "absent-minded", "disheveled", "confident", \
                "young", "long-legged", "tall", "stout", \
                "irritating", "vivacious", "muscular", \
                "stone-faced"})
#define SP_DELAY (2+random(2))
int level = 0;
static int counter;

public void set_level(int n)
{
  level = n;
}

string show_apprentice_level()
{
  switch(level)
    {
    case 0:
      return "initiate";
    case 1:
      return "junior student";
    case 2:
      return "senior student";
    case 3:
      return "junior acolyte";
    case 4:
      return "senior acolyte";
    case 5:
      return "eminent acolyte";
    case 6:
      if (query_gender() == G_FEMALE)
	{
	  return "junior sorceress";
	}
      else
	{
	  return "junior sorcerer";
	}
    case 7:
      if (query_gender() == G_FEMALE)
	{
	  return "senior sorceress";
	}
      else
	{
	  return "senior sorcerer";
	}
    default:
      if (query_gender() == G_FEMALE)
	{
	  return "eminent sorceress";
	}
      else
	{
	  return "eminent sorcerer";
	} 
    }
}

void create_roke_apprentice()
{
}

nomask void create_earthsea_monster()
{
  create_roke_apprentice();
  set_name("apprentice");
  add_name("roke_apprentice");
  set_gender(random(2));
  add_adj(ADJS1[random(sizeof(ADJS1))]);
  add_adj(ADJS2[random(sizeof(ADJS2))]);
  set_race_name(RACE_NAMES[random(sizeof(RACE_NAMES))]);  
  set_long(capitalize(this_object()->query_pronoun()) + 
	   " is one of many apprentices that come from all " +
	   "over Earthsea to study at the Wizard's School of Roke. " +
	   capitalize(this_object()->query_pronoun()) + " looks like " +
	   this_object()->query_pronoun() + " is " +
	   LANG_ADDART(show_apprentice_level()) + ".\n"); 
  set_act_time(90);
  add_act("emote smiles.");
  add_act("emote whistles a merry song about the creation of Ea.");
  add_act("emote begins to sing the Deeds of Erreth-Akbe.");
  set_chat_time(90);
  add_chat("Infinite are the arguments of mages.");
  add_chat("It is light that defeats the dark.");
  add_chat("Only in silence the word, only in dark the light, " +
	   "only in dying life: bright the hawk's flight on " +
	   "the empty sky.");
  add_chat("Sunlight and starlight are time, and time is light.");
  add_chat("To hear, one must be silent.");
  add_chat("To light a candle is to cast a shadow.");
  add_chat("Some folk are wise, and some are otherwise.");
  add_chat("Knowledge comes, but wisdom lingers.");
  
  set_cchat_time(90);
  add_cchat("Why do you attack me?");
  add_cchat("I want only peace with you.  Please can't we talk?");
  
  set_cact_time(90);
  add_cact("emote tries to hex you!");
  add_cact("emote mumbles some strange words...");
  add_cact("frown");
  
  set_stats(({50 + level * 10 + random(20), 
	      60 + level * 10 + random(20), 
              50 + level * 10 + random(20),
	      70 + level * 10 + random(20), 
	      55 + level * 10 + random(20), 
	      50 + level * 10 + random(20)}));
  set_skill(SS_DEFENSE, MIN(20 + level * 7 + random(30), 70));
  set_skill(SS_PARRY, MIN(20 + level * 7 + random(30), 70));
  set_skill(SS_WEP_POLEARM, MIN(20 + level * 7 + random(30), 100));
  set_skill(SS_WEP_KNIFE, MIN(20 + level * 7 + random(30), 100));
  set_skill(SS_UNARM_COMBAT, MIN(20 + level * 7 + random(30), 100));
  set_skill(SS_AWARENESS, 75);
  set_skill(SS_BLIND_COMBAT, 80);
  set_skill(SS_ELEMENT_AIR, MIN(45 + level * 4, 90));
  set_skill(SS_FORM_CONJURATION, MIN(45 + level * 4, 90));
  set_skill(SS_SPELLCRAFT, MIN(60 + level * 4, 90));
  set_exp_factor(120);
  log_my_kills("/d/Earthsea/npc_logs/roke_apprentice_kills.log");
  add_equipment(({ random(2) ? APPRENTICE_DAGGER : APPRENTICE_SPEAR,
		   random(2) ? APPRENTICE_CLOAK : APPRENTICE_JERKIN,
		   APPRENTICE_HELM,
		   APPRENTICE_BOOTS}));
  clone_object(SPELLS)->move(this_object());
}

int
special_attack(object enemy)
{
  object *targets;

  if (++counter >= SP_DELAY)
    {
      counter = 0;
      if (!this_object()->query_prop(ROKE_I_HAS_ARMA))
	{
	  this_object()->command("cast arma");
	  return 1;
	}
      if (level > 4)
	{
	  if (random(3) > 1)
	    {
	      if (sizeof(enemy->query_team_other()))
		{
		  this_object()->command("cast bakuryuuha");
		  return 1;
		}
	    }
	}
      this_object()->command("cast fulmenati");
      return 1;
    }
  return 0;
}

void
attacked_by(object ob)
{
  object *arr;
  int i;
  
  ::attacked_by(ob);
  
  arr = FILTER_LIVE(all_inventory(environment(this_object())));
  for (i = 0; i < sizeof(arr); i++)
    {
      if (arr[i]->id("roke_apprentice") && arr[i] != this_object())
	{
	  arr[i]->command("say Hey! Stop fighting my buddy!");
	  arr[i]->command("kill " + ob->query_name());
	}
    }
  this_object()->command("cast arma");
}


