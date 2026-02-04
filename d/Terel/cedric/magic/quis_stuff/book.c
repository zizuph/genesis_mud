inherit "/std/spells";
#include <stdproperties.h>
#include <macros.h>
#include <ss_types.h>

#define SPELL_DIR "/d/Liwitch/quis/open/new_spells/"

string spell_verb;

void
create_spells()
{
    ::create_spells();
      add_spell("bless", "cast_spell", "bestow blessing");
    add_spell("light", "cast_spell", "create light");
}

int
cast_spell(string str)
{
   string spell_file;
   
      seteuid(getuid(this_object()));
      spell_file = SPELL_DIR + spell_verb;
      return call_other(spell_file, "cast_spell", str);
}

int
query_spell_time(string str)
{
   spell_verb = str;
   return 0;
}
