inherit "/std/spells";
#include <stdproperties.h>
#include <macros.h>
#include <ss_types.h>

#define SPELL_DIR "/d/Liwitch/quis/open/new_spells/"

string spell_verb;
mapping stored_spells;

void
create_spells()
{
   set_name("wand");
   add_name("wand of lightening");
   set_adj("ivory");
   add_adj("runed");
   add_spell("charge", "cast_spell", "charge the wand");
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

add_stored_spell(string filename)
{
    stored_spells[filename]++;
}

int
query_number_charges(string spell)
{

return stored_spells[spell];
}
