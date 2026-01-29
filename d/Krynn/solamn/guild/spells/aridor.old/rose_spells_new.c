/* This is the spell object for the rose knights */

#include "/d/Krynn/common/defs.h"
#include "local.h"
#include "../../guild.h"

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
    add_name("rose_knight_spell_obj");

    add_knight_spell(0, 0,"radiance",   "do_radiance",
		     "A simple light prayer.");
    add_knight_spell(0, 1000, "revive",     "do_revive",
		     "A cure prayer (@@spell_avail_string|revive@@).");
    add_knight_spell(0, 2000, "fortify",    "do_fortify",
		     "A protection prayer (@@spell_avail_string|fortify@@).");
    add_knight_spell(0,10000, "speed",      "do_speed",
		       "A prayer to call Paladine's speed (@@spell_avail_string|speed@@).");
    add_knight_spell(0, 1000, "perceive",   "do_perceive",
		       "Perceive hidden meanings (@@spell_avail_string|perceive@@).");
    add_knight_spell(0, 1000, "compare",    "do_compare",
		     "Compare weapons or armours (@@spell_avail_string|compare@@).");
    add_knight_spell(0, 5000, "cure",       "do_cure",
		     "Cure for normal poisons (@@spell_avail_string|cure@@).");
    add_knight_spell(0, 5000, "tell",       "do_tell",
		     "Tell to members of your order (@@spell_avail_string|tell@@).");
    add_knight_spell(0, 10000, "bless",     "do_bless",
		     "Bless an item (@@spell_avail_string|bless@@).\n");
}

/* Return 1 if the spell should fail */
int
start_spell_fail(string verb, string arg)
{
    object pl = this_player();

    if (pl->query_knight_level() != 5)
      {
	  pl->catch_msg("Only Rose Knights may attempt this spell!\n");
	  return 1;
      }
    
    return ::start_spell_fail(verb, arg);
}


/* Spell code */
#include SPELL_RADIANCE
#include SPELL_FORTIFY
#include SPELL_SPEED
#include SPELL_PERCEIVE
#include SPELL_REVIVE_ROSE
#include SPELL_COMPARE
#include SPELL_CURE_ROSE
#include SPELL_TELL
#include SPELL_BLESS
