/* 
 * A scroll containing a magic spell
 *
 * The spell can be copied into a sohm spell book or cast immediately
 *
 * Britanica 20160403 
 */
 
inherit "/d/Krynn/common/scrolls/base_scroll";
#include <macros.h>
#include <cmdparse.h>
#include <tasks.h>
#include <ss_types.h>
#include <wa_types.h>

#define SPELL_DIR "/d/Krynn/guilds/sohm/spells/"
#define SOHM_MINOR_SPELL 2

#define SCROLL_I_FURLED "_scroll_i_furled"

/*
 * Function name: create_scroll
 * Description  : constructor.
 * Arguments    : n/a
 * Returns      : n/a
 */
void
create_scroll()
{
    ::create_scroll();
    set_name("dazzle scroll");
    add_name("_dazzle_scroll_");
    
    set_spell(SPELL_DIR + "dazzle");
    set_spell_level(SOHM_MINOR_SPELL);
    
    add_prop(OBJ_I_VALUE, 1000 + (random(440)));
}
