/*
 * spellpaper.c
 *
 * Used in obj/spellp.c
 *
 * This was once a part of the domain Roke.
 * Cleaned up and moved into Khalakhor by Glindor, Nov 2001.
 * Patched eggs to be edible only; added multiple
 * power-descending casting; added property cleanup upon getting rid;
 * fixed egg heap behaviour -- TAPAKAH, 10/2005.
 * Spell also ate inedible eggs. Mercade, May 2007.
 */

#pragma save_binary
#pragma strict_types

inherit "/std/spells";

#include "defs.h"
#include <files.h>
#include <formulas.h>
#include <macros.h>
#include <ss_types.h>

int allofit, nummer;

#define LOCATIONHANDLER (ROKEDIR + "obj/locationhandler")

#define MANALIMIT 10
#define CASTLIMIT 10
#define ROKE_I_USED_SPELLPAPER "_roke_i_used_spellpaper"

string
query_auto_load ()
{
  return MASTER + ":" + allofit + "#" + nummer;
}

void
init_arg (string arg)
{
  sscanf(arg, "%d#%d", allofit, nummer);
}

void
fix_it ()
{
  allofit = 1;
}


string
mylong ()
{
  seteuid(getuid(TO));

  if (nummer < 0)
      return "On the top of the paper are some runes and the word " +
        "'strength'. There is also a picture of an egg. " +
        "Some powerful magic force has made the paper all " +
        "fluffy and has also created a picture of a blue " +
        "dragon on it.\n";

  if (!allofit) {
    if (present("ppapp", TP))
      return "On the top of the paper are some runes and the word " +
        "'strength'. There is also a picture of an egg. " +
        "On the back side of the paper someone has written " +
        "an old legend. It looks a little similar to the other paper " +
        "you are carrying. It looks like it just might be possible " +
        "to append this one to it.\n";
    else
      return "On the top of the paper are some runes and the word " +
        "'strength'. There is also a picture of an egg. " +
        "On the back side of the paper someone has written " +
        "an old legend. Unfortunately the paper has been torn " +
        "apart, so you can't read it. You really wish that " +
        "you had that second part...\n";
  }
  return "On the top of the paper are some runes and the word " +
    "'strength'. There is also a picture of an egg. " +
    "On the back side of the paper someone has written " +
    "an old legend. It tells a tale about an old " +
    "treasure, hidden on a place that fits the " +
    "description in the tale:\n" +
    LOCATIONHANDLER->give_location(nummer);

}

static void
expire_spell (object tp)
{
  int satur;

  satur = tp->query_prop(ROKE_I_USED_SPELLPAPER);
  if(satur)
    if(satur == 1)
      tp->remove_prop(ROKE_I_USED_SPELLPAPER);
    else
      tp->add_prop(ROKE_I_USED_SPELLPAPER,satur/2);
}

string
cast_spell (string str)
{
  int i;
  object egg = present("egg", TP);
  int skill, difficulty, eggval, satur;
  string saturation;
    
  if (!objectp(egg))
    return "You need an egg to cast that spell!\n";

  if (IS_FOOD_OBJECT(egg))
    eggval = egg->query_amount();
  else
    return "Somehow this egg doesn't look like a suitable one.\n";
    
  if (TP->query_mana() < MANALIMIT) 
    return "You don't have enough mental powers to cast that spell.\n";

  TP->add_mana(-MANALIMIT);
  saturation = "";
    
  if (TP->query_prop(ROKE_I_USED_SPELLPAPER)) {
    satur = TP->query_prop(ROKE_I_USED_SPELLPAPER) * 2;
    saturation = ", but not as stronger as the previous time";
  }
  else
    satur = 1;

  skill = TP->query_skill(SS_SPELLCRAFT) + TP->query_stat(SS_WIS);
  skill /= 2;
  difficulty = CASTLIMIT;

  if (skill < random(difficulty))
    return "Your skills were not sufficient to cast that spell.\n";

  i = (skill + eggval) / satur;
     
  TP->add_tmp_stat(SS_STR, random(i / 5), random(i));
  TP->add_prop(ROKE_I_USED_SPELLPAPER, satur);

  set_alarm(itof(i * F_INTERVAL_BETWEEN_HP_HEALING), 0.0,
            &expire_spell(TP));

  egg->split_heap(1);
  egg->move(environment(TP),1);
  egg->remove_object();

  say(QCTNAME(TP) + " smashes an egg in " + TP->query_possessive() +
      " face.\n");
  return "You smash the egg in your face and feel stronger" + saturation + ".\n";
}

int
append (string s)
{
  object ob;

  if (s != "papers")
    NF0("Append what? The papers?\n");

  if (!(ob = present("ppapp", TP)))
    NF0("Too bad that you don't have more papers.\n");

  if (allofit)
    NF0("Don't be silly... You've already done that.\n");

  ob->remove_object();

  allofit = 1;

  TP->catch_msg("You append the papers. Suddenly they become readable.\n");

  return 1;
}

void
create_spells()
{
  seteuid(getuid());
  set_name("paper");          /* A name for the object. */
  set_adj("magic");           /* It's a spell book. */
  add_name("sppapp");

  set_long(mylong);

  add_prop(OBJ_I_NO_DROP,
           "If you want to get rid of the paper, just swallow it.\n");
  add_prop(OBJ_M_NO_STEAL, 1);

  add_spell("strength", "cast_spell", "get better strength");
  nummer = LOCATIONHANDLER->assign_nummer();
}

int
query_nummer()
{
  if (!allofit)
    return -1;

  return nummer;
}

int
remove_object()
{
  TP->remove_prop(ROKE_I_USED_SPELLPAPER);
  
  ::remove_object();
}

int
swallow (string s)
{
  NF("Swallow what? The magic paper?\n");
  if (s != "magic paper")
    return 0;
  write("You swallow the paper.\n");
  remove_object();
  return 1;
}

int
read (string s)
{
  if (! s)
    return 0;

  if (s == "paper" || s == "the paper") {
    write(mylong());
    return 1;
  }
  return 0;
}

void
init ()
{
  ::init();
  add_action(read, "read");
  add_action(swallow, "swallow");
  add_action(append, "append");
}

void
transform_me()
{
  nummer = -1;

  write("Your paper glows briefly.\n");
}

