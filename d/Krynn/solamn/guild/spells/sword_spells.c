/* This is the spell object for the sword knights */

#include "/d/Krynn/common/defs.h"
#include "local.h"
#include "../guild.h"

inherit KNIGHT_SPELLS_BASE

#include <macros.h>
#include <ss_types.h>
#include <comb_mag.h>
#include <stdproperties.h>
#include <tasks.h>
#include <cmdparse.h>


void
create_knight_spells()
{
    add_name("sword_knight_spell_obj");

    add_knight_spell(0, 0,"radiance",   "do_radiance",
		     "A simple light prayer.");
    add_knight_spell(0, 1000, "revive",     "do_revive",
		     "A cure prayer.           (@@spell_avail_string|revive@@)");
    add_knight_spell(0, 2000, "fortify",    "do_fortify",
		     "A protection prayer.     (@@spell_avail_string|fortify@@)");
    add_knight_spell(0, 1000, "perceive",   "do_perceive",
		     "Perceive hidden meanings.(@@spell_avail_string|perceive@@)");
    add_knight_spell(0, 1500, "encourage",  "do_encourage",
		     "Get spiritual support.   (@@spell_avail_string|encourage@@)");
    add_knight_spell(0, 4000, "storm",      "do_storm",
		     "Call a stormcloud and    (@@spell_avail_string|storm@@)" +
		     "\n                   lightning to drive evil away.");
    
}

#if 0
/* Return 1 if the spell should fail */
int
start_spell_fail(string verb, string arg)
{
    object pl = this_player();

    if (pl->query_knight_level() != 4)
      {
	  pl->catch_msg("Only Sword Knights may attempt this spell!\n");
	  return 1;
      }
    
    return ::start_spell_fail(verb, arg);
}
#endif

/* Spell code */
#include SPELL_RADIANCE
#include SPELL_FORTIFY
#include SPELL_REVIVE_SWORD
#include SPELL_PERCEIVE
#include SPELL_STORM
#include SPELL_ENCOURAGE
