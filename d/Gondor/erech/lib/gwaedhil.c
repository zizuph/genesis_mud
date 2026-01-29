/*
 * gwaedhil.c
 * By Skippern
 * November 20 (c) 00
 *
 * For the dreaming ability I used Gwyneths hallucination object as example.
 */
inherit "/std/weapon";

#include <formulas.h>
#include <macros.h>
#include <ss_types.h>
#include <stdproperties.h>
#include <wa_types.h>
#include "gwaedhil.h"
#include "../erech.h"

/* Prototypes */
string             translate_name();
string             translate_sword();
string             translate_spear();
string             quenya_name();
string             quenya_sword();
string             quenya_spear();

void               dreamer();
void               dream_all();
void               dream_inventory();
void               dream_wielder();

string
quenya_name()
{
    return "Gwaedhel.\n";
}

string
quenya_sword()
{
    return "Pedu ado dago, carmallo guormo.\n";
}

string
quenya_spear()
{
    return "Pedo ado dago, carmallo guormo.\n";
}

/*
 * Function name:    translate_name
 * Description  :    Returns the translation of ``Gwaedhil'' dempending on 
 *                   race/guild status.
 */
string
translate_name()
{
    int       lang = this_player()->query_skill(SS_LANGUAGE);
    string    race = this_player()->query_race_name();
    string    oguild = this_player()->query_guild_name_occ();
    string    rguild = this_player()->query_guild_name_race();
    string    lguild = this_player()->query_guild_name_lay();

    // Max lang from ADV_GUILDS = 30
    /*
    if (this_player()->query_wiz_level())
      return "Race/Guild dependent returns: Oath-sister.\n";
    */
    // Guilds who should have a bonus on translating:
    // Rangers, Dunedain, hobbit, heralds, 
    // Guilds who should suffer a penaltie on translating:
    // Mages, rockfriends,
    if (oguild == RANGER)
      lang = lang + 1;
    if (oguild == MM)
      lang = lang - 10;
    if (lguild == HERALD)
      lang = lang + 1;
    if (rguild == DUNEDAIN)
      {
	if (lang < 5)
	  return "Pondering over this text you realize that you should have " +
	    "paid more attention in class.\n";
	else if (lang < 10)
	  return "You can't remember the teacher telling you anything " +
	    "useful here, maybe you dozed off?\n";
	else if (lang < 20)
	  return "You translate it to \"Oath-sister\", but are not certain " +
	    "of your translation.\n";
	else
	  return "You translate it: Oath-sister.\n";
      }
    if (rguild == HOBBIT)
    {
	if (lang < 10 )
	  return "You have no clue what it means.\n";
	else if (lang > 25 )
	  return "You translate it: Oath-sister.\n";
	else
	  return "It has something to do with oaths and siblings.\n";
    }
    if (rguild == ROCKFRIEND)
      {
	if (lang < 10 )
	  return "You have no clue what it means.\n";
	else if (lang > 27 )
	  return "You translate it: Oath-sister.\n";
	else
	  return "It has something to do with oaths and siblings.\n";
      }
    // Races to suffer penalties:
    // Goblins
    if (race == "goblin")
      {
	if (lang < 5)
	  return "Huh, those marks look more like squeezed bugs than " +
	    "any words.\n";
	else if (lang < 10)
	  return "Stupid elves. Why can't they use any common languages?\n";
	else if (lang < 15)
	  return "Uhm, something to do with siblings maybe?\n";
	else if (lang > 25)
	  return "Oath-sister? What kind of word is that?\n";
	else
	  return "Uhm. What is the meaning of oaths and siblings?\n";
      }
    // Races to gain bonus:
    // Elves (try to exclude drow if possible)
    if (race == "elf")
      {
	if (rguild == DROW)
	  lang = lang - 5;
	else if (rguild == NOLDOR)
	  {
	    return "It translates: Oath-sister.\n";
	  }
	else
	  lang = lang + 10;
      }

    //Default
    if (lang < 15 )
      return "You have no clue what it means.\n";
    else if (lang > 25 )
      return "You translate it: Oath-sister.\n";
    else
      return "It has something to do with oaths and siblings.\n";

    // Translation is Oath-Sister.
    return "Error. No test done. Try again.\n";
}

string
translate_sword()
{
  int       lang = this_player()->query_skill(SS_LANGUAGE);
  string    race = this_player()->query_race_name();
  string    oguild = this_player()->query_guild_name_occ();
  string    rguild = this_player()->query_guild_name_race();
  string    lguild = this_player()->query_guild_name_lay();

  // Max lang from ADV_GUILDS = 30
  /*
  if (this_player()->query_wiz_level())
      return "Race/Guild dependent returns: Speak, refuse to fight, " +
          "conjure friendship not wrath.\n";
  */
  // Guilds who should have a bonus on translating:
  // Rangers, Dunedain, hobbit, heralds,
  // Guilds who should suffer a penaltie on translating:
  // Mages, rockfriends,
  if (oguild == RANGER)
    lang = lang + 1;
  if (oguild == MM)
    lang = lang - 10;
  if (lguild == HERALD)
    lang = lang + 1;
  if (rguild == DUNEDAIN)
    {
      if (lang < 5)
          return "Pondering over this text you realize that you should have " +
            "paid more attention in class.\n";
      else if (lang < 10)
          return "You can't remember the teacher telling you anything " +
            "useful here, maybe you dozed off?\n";
      else if (lang < 20)
          return "You translate it to \"Oath-sister\", but are not certain " +
            "of your translation.\n";
        else
          return "You translate it: Speak, refuse to fight, conjure " +
	  "friendship, not wrath.\n";
    }
  if (rguild == HOBBIT)
    {
      if (lang < 10 )
	return "You have no clue what it means.\n";
      else if (lang > 25 )
	return "You translate it: Speak, refuse to fight, conjure " +
	    "friendship, not wrath.\n";
        else
          return "It sounds much like a word of wisdom, like something " +
	  "about holding friendship high.\n";
    }
  if (rguild == ROCKFRIEND)
    {
      if (lang < 10 )
	return "You have no clue what it means.\n";
      else if (lang > 27 )
	return "You translate it: Speak, refuse to fight, conjure " +
	    "friendship, not wrath.\n";
        else
          return "It sounds much like a word of wisdom, like something " +
	  "about holding friendship high.\n";
    }
  // Races to suffer penalties:
  // Goblins
  if (race == "goblin")
    {
      if (lang < 5)
          return "Huh, those marks look more like squeezed bugs than " +
            "any words.\n";
      else if (lang < 10)
	return "Stupid elves. Why can't they use any common languages?\n";
      else if (lang < 15)
	return "Uhm, something to do with talking to friends maybe?\n";
      else if (lang > 25)
	return "Why conjure anything higher than wrath? And why should we " +
	"refuse to fight?\n";
        else
          return "Speak is fine, but refuse to fight?\n";
    }
  // Races to gain bonus:
  // Elves (try to exclude drow if possible)
  if (race == "elf")
    {
      if (rguild == DROW)
	lang = lang - 5;
      else if (rguild == NOLDOR)
	{
	  return "It translates: Speak, refuse to fight. Conjure " +
	  "friendship, not wrath.\n";
	}
        else
          lang = lang + 10;
    }

  //Default
  if (lang < 15 )
    return "You have no clue what it means.\n";
  else if (lang > 25 )
    return "You translate it: Speak, refuse to fight. Conjure " +
    "friendship, not wrath.\n";
    else
      return "It has something to do with oaths and siblings.\n";
}

string
translate_spear()
{
  int       lang = this_player()->query_skill(SS_LANGUAGE);
  string    race = this_player()->query_race_name();
  string    oguild = this_player()->query_guild_name_occ();
  string    rguild = this_player()->query_guild_name_race();
  string    lguild = this_player()->query_guild_name_lay();

  // Max lang from ADV_GUILDS = 30
  /*
    if (this_player()->query_wiz_level())
      return "Race/Guild dependent returns: Oath-sister.\n";
  */
  // Guilds who should have a bonus on translating:
  // Rangers, Dunedain, hobbit, heralds,
  // Guilds who should suffer a penaltie on translating:
  // Mages, rockfriends,
  /*
    if (oguild == RANGER)
      lang = lang + 1;
    if (oguild == MM)
      lang = lang - 10;
    if (lguild == HERALD)
      lang = lang + 1;
    if (rguild == DUNEDAIN)
      {
        if (lang < 5)
          return "Pondering over this text you realize that you should have " +
            "paid more attention in class.\n";
        else if (lang < 10)
          return "You can't remember the teacher telling you anything " +
            "useful here, maybe you dozed off?\n";
        else if (lang < 20)
          return "You translate it to \"Oath-sister\", but are not certain " +
            "of your translation.\n";
        else
          return "You translate it: Oath-sister.\n";
      }
    if (rguild == HOBBIT)
    {
        if (lang < 10 )
          return "You have no clue what it means.\n";
        else if (lang > 25 )
          return "You translate it: Oath-sister.\n";
        else
          return "It has something to do with oaths and siblings.\n";
    }
    if (rguild == ROCKFRIEND)
      {
        if (lang < 10 )
          return "You have no clue what it means.\n";
        else if (lang > 27 )
          return "You translate it: Oath-sister.\n";
        else
          return "It has something to do with oaths and siblings.\n";
      }
    // Races to suffer penalties:
    // Goblins
    if (race == "goblin")
      {
        if (lang < 5)
          return "Huh, those marks look more like squeezed bugs than " +
            "any words.\n";
        else if (lang < 10)
          return "Stupid elves. Why can't they use any common languages?\n";
        else if (lang < 15)
          return "Uhm, something to do with siblings maybe?\n";
        else if (lang > 25)
          return "Oath-sister? What kind of word is that?\n";
        else
          return "Uhm. What is the meaning of oaths and siblings?\n";
      }
    // Races to gain bonus:
    // Elves (try to exclude drow if possible)
    if (race == "elf")
      {
        if (rguild == DROW)
	lang = lang - 5;
        else if (rguild == NOLDOR)
          {
            return "It translates: Oath-sister.\n";
          }
        else
          lang = lang + 10;
      }

    //Default
    if (lang < 15 )
      return "You have no clue what it means.\n";
    else if (lang > 25 )
      return "You translate it: Oath-sister.\n";
    else
      return "It has something to do with oaths and siblings.\n";

   */
  translate_sword();
    return "";
}

int
frighten(int aid, string hdesc, int phurt, object enemy, int dt, int phit, int dam)
{
    object    wielder = query_wielded();
    string    w_msg, e_msg, o_msg;
    int       alter = 0;
    int       Secure = 0;

    if (wielder->query_prop(LIVE_I_UNDEAD) != 0)
        Secure = 1;

    if (enemy->query_prop(LIVE_I_UNDEAD) >= 1)
        return 1;

    if (dt == W_IMPALE)
    {
        if (phurt > ERECH_PHURT_MED)
        {
	    alter = ERECH_TROUBLED;
	    w_msg = "As you prepare to stab " + 
	        enemy->query_the_name(wielder) + ", you " +
	        "look deep into " + enemy->query_possessive() + " eyes.\n";
	    e_msg = "As " + wielder->query_The_name(enemy) + " stares into " +
                "your eyes, you feel a sense of horror.\n";
	    o_msg = QCTNAME(wielder) + " looks at " + QTNAME(enemy) +
	        " as " + wielder->query_pronoun() + " makes " +
	        wielder->query_objective() + "self ready to attack.\n";
        }
	else if (phurt > ERECH_PHURT_GOOD)
        {
	    alter = ERECH_SCARED;
	    w_msg = "You stare at " + enemy->query_the_name(wielder) + 
	        " as you aim our " + short() + " at " + 
	        enemy->query_possessive() + " " + hdesc + ".\n";
            e_msg = "You feel terror creep up your ankles as " +
                wielder->query_the_name(enemy) + "stares at you with " +
                "glowing eyes.\n";
            o_msg = QCTNAME(enemy) + " cringes in terror as " +
                QTNAME(wielder) + " looks at " + enemy->query_possessive() +
                " " + hdesc + ".\n";
        }
    }
    if (dt == W_SLASH)
    {
        if (phurt > ERECH_PHURT_MED)
        {
	    alter = ERECH_TROUBLED;
	    w_msg = enemy->query_The_name(wielder) + " gets a look of fear " +
	        "as " + enemy->query_pronoun() + " looks at your " + short() + 
	        ".\n";
	    e_msg = "The edge of " + wielder->query_the_possessive_name(enemy) +
                " " + short() + " looks VERY looks sharp.\n";
	    o_msg = QCTNAME(enemy) + " gets a look of fear as " +
	        enemy->query_pronoun() + " looks at " + QTPNAME(wielder) + 
	        " " + short() + ".\n";
        }
	else if (phurt > ERECH_PHURT_GOOD)
        {
	    alter = ERECH_SCARED;
	    w_msg = enemy->query_The_possessive_name(wielder) + 
	      " hair stands on end as you look at " +
	      enemy->query_possessive() + " " + hdesc + ".\n";
	    e_msg = "You can feel your hair stand on end as " + 
              wielder->query_the_name(enemy) + " looks at you.\n";
	    o_msg = QCTPNAME(enemy) + " hair stands on end as " +
	      QTNAME(wielder) + " looks at " + enemy->query_possessive() + 
	      " " + hdesc + ".\n";
        }

    }
    if (dt == W_BLUDGEON)
    {
        if (phurt > ERECH_PHURT_MED)
        {
	    alter = ERECH_TROUBLED;
	    w_msg = enemy->query_The_name(wielder) + " gasps for fresh air.\n";
	    e_msg = "You gasp for air as a pain strikes you in your " +
	      hdesc + ".\n";
	    o_msg = QCTNAME(enemy) + " gasps for fresh air.\n";
        }
	else if (phurt > ERECH_PHURT_GOOD)
        {
	    alter = ERECH_SCARED;
	    w_msg = enemy->query_The_name(wielder) + " screams in agony.\n";
	    e_msg = "You scream in agony as you feel a severe pain in your " +
	      hdesc + ".\n";
	    o_msg = QCTNAME(enemy) + " screams in agony.\n";
        }
    }
    if (dt == MAGIC_DT)
    {
        if (phurt > ERECH_PHURT_MED)
        {
	    alter = ERECH_TROUBLED;
	    w_msg = enemy->query_The_name(wielder) + " gets a look on " + 
	      enemy->query_possessive() + " face, like " +
	      enemy->query_pronoun() + " is going to explode.\n";
	    e_msg = "Your " + hdesc + " feels like it is going to explode.\n";
	    o_msg = QCTNAME(enemy) + "gets a look on " +
              enemy->query_possessive() + " face, like " +
              enemy->query_pronoun() + " is going to explode.\n";;
        }
	else if (phurt > ERECH_PHURT_GOOD)
        {
	    alter = ERECH_SCARED;
	    w_msg = enemy->query_The_name(wielder) + "gets a look on " +
              enemy->query_possessive() + " face, like " +
              enemy->query_pronoun() + " is going to explode.\n";
	    e_msg = "Your " + hdesc + " feels like it is going to explode.\n";
	    o_msg = QCTNAME(enemy) + "gets a look on " +
              enemy->query_possessive() + " face, like " +
              enemy->query_pronoun() + " is going to explode.\n";
        }
    }

    if (Secure == 1 && alter != 0)
        wielder->add_panic(-alter);

    if (wielder->query_prop(LIVE_I_UNDEAD) >= 1 && alter != 0)
        alter = alter * 2;
    else if (IS_DUNADAN(wielder) && alter != 0)
        alter = alter + (alter/2);

    if (strlen(w_msg))
        wielder->catch_tell(w_msg);
    if (strlen(e_msg))
        enemy->catch_tell(e_msg);
    if (strlen(o_msg))
        wielder->tell_watcher(o_msg, enemy);

    if (alter != 0)
        enemy->add_panic(alter);

    return 1;
}


int
hurt_extra(int aid, string hdesc, int phurt, object enemy, int dt, int phit, int dam)
{
    object    wielder = query_wielded();
    string    w_msg, e_msg, o_msg;
    int       xdam = 0;
    int       xdamB = 0;
    int       walign, ealign, hp_diff, Backfire;

    walign = wielder->query_alignment();
    ealign = enemy->query_alignment();

    hp_diff = enemy->query_hp() - dam;
    Backfire = 0;

    if (phurt > ERECH_PHURT_XDAM)
    {
	if (dt == W_IMPALE)
	{
	    w_msg = "Your " + short() + " glows for a brief moment.\n";
	    e_msg = wielder->query_The_possessive_name(enemy) + " " + short() +
                " glows for a moment.\n";
	    o_msg = QCTNAME(wielder) + "'s " + short() + " glows for a " +
	      "moment.\n";
	    xdam = dam / 2;
	}
	if (dt == W_SLASH)
	{
  	    w_msg = "You notice a blue spark run along the edge of your " +
	      short() + ".\n";
	    e_msg = "You notice a blue spark run along the edge of " +
	      wielder->query_the_possessive_name(enemy) + " " + short() + ".\n";
	    o_msg = "You notice a blue spark run along the edge of " +
	      QTPNAME(wielder) + " " + short() + ".\n";
	    xdam = dam / 3;
	}
	if (dt == W_BLUDGEON)
	{
	    w_msg = "You feel your power grow for a moment.\n";
	    e_msg = wielder->query_The_name(enemy) + " grows in front of " +
              "you.\n";
	    o_msg = QCTNAME(wielder) + " seems larger than " + QTNAME(enemy) + 
	      " for a moment.\n";
	    xdam = dam / 5;
	}
	if (dt == MAGIC_DT)
	{
	    if (walign > 750 && ealign < -750)
	    {
	        w_msg = "A holy aura glows from your " + short() + ".\n";
		e_msg = "A holy aura appears from " + 
                  wielder->query_the_possessive_name(enemy) + " " + 
                  short() + ".\n";
		o_msg = "For a brief moment you are able to se a holy aura " +
		  "from " + QTPNAME(wielder) + " " + short() + ".\n";
	    }
	    else if (walign < -750 && ealign > 750) 
	    {
	        w_msg = "A sphere of pure evil conceals your " + short() +
		  " for a moment.\n";
		e_msg = "A sphere of pure evil blurs your sight a moment.\n";
		o_msg = "Something to write here.\n";
	    }
	    else
	    {
	        w_msg = "A magical glow shines from your " + short() + ".\n";
		e_msg = "A magical glow shines from " + 
                  wielder->query_the_possessive_name(enemy) + " " + short() +
		  ".\n";
		o_msg = "A magical glow shines from " + QTPNAME(wielder) +
                  " " + short() + ".\n";
	    }
	    xdam = dam * 2;
	}
    }

    if (hp_diff < 0)
    {
        switch (random(100))
	{
	case 66:
	    Backfire = 1;
	    w_msg = "A pain like burning acid runs from your hands up " +
	      "to your shoulders.\nThe pain is unbearable.\n";
	    e_msg = wielder->query_The_name(enemy) + " screams out in pain.\n";
	    o_msg = QCTNAME(wielder) + " screams out in pain.\n";
	    xdamB = dam;
	    break;
	default:
	    Backfire = 0;
	    break;
	}
    }	


    if (strlen(w_msg))
      wielder->catch_tell(w_msg);
    if (strlen(e_msg))
      enemy->catch_tell(e_msg);
    if (strlen(o_msg))
      wielder->tell_watcher(o_msg, enemy);

    if (xdam != 0 && Backfire == 0)
      enemy->heal_hp(-xdam);
    if (xdam != 0 && Backfire == 1)
      wielder->heal_hp(-xdamB);

    return 1;
}

/*
 * Function name:    do_dream
 * Description  :    Controls the dreams and visions sent from the weapons.
 */
void
do_dream()
{
    float delay;
    int limit;

    limit = DREAM_MIN_DELAY + random(DREAM_MAX_DELAY - DREAM_MIN_DELAY);
    delay = itof(limit);

    set_alarm(delay, DREAM_FLOAT_REPEAT, &dreamer());
}

void
dreamer()
{
    switch(random(DREAMER_RANDOM_TEST))
    {
        case 0:
	    dream_all();
	    break; 
        case 1..5:
	    dream_inventory();
	    break; 
        default:
	    dream_wielder();
	    break;
    }

    do_dream();
}

void
dream_all()
{
    string dreams = one_of_list(A_DREAMS);

    //    write("dream_all()\n");

    // This is the problem, here I need to make all in the room see the dreams
    // both when the object is on the ground or in somebodys inventory.

    tell_room(ENV(TO), dreams, 0, 0);

    return;
}

void
dream_inventory()
{
    string dreams;

    //    write("dream_inventory()\n");

    dreams = one_of_list(I_DREAMS);

    if (living(environment(this_object())))
    {
	environment(this_object())->catch_tell(dreams + "\n");
    }

    return;

}

void
dream_wielder()
{
    object wielder = query_wielded();
    string dreams;

    //    write("dream_wielder()\n");

    if (!wielder)
        return;
    dreams = one_of_list(W_DREAMS);

    wielder->catch_tell(dreams + "\n");

    return;

}






