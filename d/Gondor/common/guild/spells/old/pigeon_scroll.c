inherit "/std/scroll";
#include "/sys/stdproperties.h"
#include "/sys/macros.h"

#include "/d/Gondor/defs.h"

create_scroll()
{
  ::create_scroll();
  set_short("old scroll");
  set_name("scroll");
  add_name("pigeonscroll");
  set_adj("old");
  add_adj("pigeon");
  set_long("@@long_func");
  set_file(RANGER_DIR+"spells/text/whistle.txt");
}

init()
{
  ::init();
  add_action("copy_scroll","copy");
}

long_func()
{
  string txt;
  txt = "The yellowed paper of this scroll indicates that it is quite old. "+
    "Below the title 'Ways of Communing' are some intelligible words, "+
    "followed by some rather unusual letters of ancient elven origin. ";
  if (present("ranger_spell_book",TP)) txt = txt + "You feel quite sure "+
    "that you can copy this scroll into your spellbook. ";
  else txt = txt + "You have a feeling it is impossible for you to use this scroll.";
  return BSN(txt);
}

copy_scroll(string str)
{
  object scroll, book;
  string dummy, scr_name;
  if (!str) { write("Copy what?\n"); return 1; }
  if (!parse_command(str,environment(),
		     "%o [into] / [in] / [to] %o", scroll, book))
  {
      write("Copy what into where?\n");
      return 1;
  }
  if (scroll != this_object())
  {
      write("Copy which scroll?\n");
      return 1;
  }
  if (book != present("ranger_spell_book",TP))
  {write("But you don't have the spellbook!\n"); return 1; }
  if (book->query_spell_known("sp")) {
    write("But you have already scribed that spell in your spellbook!\n");
    return 1;
    }
  book->scribe_spell("sp");
  book->setup_ranger_spells();
  write("You carefully copy the spell onto some blank pages of your spellbook.\n");
    write("Just as you are finished, the scroll crumbles to dust between your fingers!\n");
  say(QCTNAME(TP)+" scribes a spell in "+TP->query_possessive()+" little brown book.\n"+
    "Suddenly, the scroll "+TP->query_pronoun()+" was copying from, crumbles to dust!\n",TP);
  TO->remove_object();
  return 1;
}



