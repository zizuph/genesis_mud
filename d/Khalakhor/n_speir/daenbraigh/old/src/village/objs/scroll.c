/*
 * Goblin elder's scroll
 * The spell on the scroll is of 'confusion'
 *
 * Scroll mangling acquired from
 * /d/Gondor/morgul/quest/bsw/scroll.c by Olorin with slight modification
 */

#pragma strict_types

inherit "/d/Khalakhor/std/scroll";

#include <stdproperties.h>
#include <macros.h>
#include <ss_types.h>
#include <filter_funs.h>
#include <math.h>

#include "/d/Khalakhor/sys/defs.h";

#include "../../daenbraigh.h"
#include "../../village/village.h"
#include "../magi/magi.h"

inherit V_MAGI + "confuse";

int chant_me(string str);
     
void
create_khalakhor_scroll()
{
  set_name(V_OBJID + "scroll");
  add_name("scroll");
  set_adj(({"wrinkled","parchment"}));
  set_short("wrinkled parchment scroll");
  set_long("This scroll has been dearly guarded by the village elder. "+
	   "You can probably read it.\n");
  set_scroll_file(V_SCROLL_TEXT);
}

void
init()
{
  ::init();

  add_action(chant_me,"chant");
}

int
chant_me(string str)
{
  string word,enemy;
  object target;
  
  if(!str) {
    notify_fail("Chant what?\n");
    return 0;
  }

  if(TP->query_stat(SS_INT) < CONFUSION_INTELLIGENCE) {
    notify_fail("You don't seem to understand the spell.\n");
    return 0;
  }
    
  if(TP->query_skill(SS_LANGUAGE) < CONFUSION_LANGUAGE) {
    notify_fail("You don't seem to be able to speak the language of the spell"+
		".\n");
    return 0;
  }

  if(sscanf(str,"%s at %s",word,enemy) == 1)
    if(word == "mearbhall") {
      write("You chant: glaoigh ar mearbhall mo namhaid.\n");
      tell_room(ENV(TP),
		QCTNAME(TP) + " chants something incomprehensible.\n",
		TP);
      if(target = present(enemy,FILTER_LIVE(({ENV(TP)})))) 
	confuse_spell(TP,target);
      else
	write("But your target is not present!\n");
      TP->set_mana(-CONFUSION_MANA);
      return 1;
    }
  notify_fail("Chant what?\n");
  return 0;
}

mixed
command_read(int more_flag)
{
  string cont;
  int seed,i;
  int charnum, lang_ability, lack;

  setuid();
  seteuid(getuid());
  charnum = 0;
  seed = 18041975;
  lang_ability = TP->query_skill(SS_LANGUAGE) + 1;
  while(cont = read_bytes(V_SCROLL_TEXT,charnum,1)) {
    if (cont == " " ||
	cont == "\n" ||
	cont == "\t" ||
	TP->query_wiz_level() ||
	lang_ability > CONFUSION_LANGUAGE)
      write(cont);
    else {
      if (NAME_TO_RANDOM(
			 TP->query_name(),
			 seed++,
			 CONFUSION_LANGUAGE
			 ) > TP->query_skill(SS_LANGUAGE))
	write("#");
      else
	write(cont);
    }
    charnum++;
  }
  seed = 18041975;
  return 1;
}
