/* bounder_sh.c created by Jaypeg@Genesis
 *                thanks to Shiva@Genesis
 */

inherit "/std/guild/guild_lay_sh";

#include "../guild.h"
//#include "/d/Emerald/sys/skills.h"
#include <macros.h>
#include  <ss_types.h>
//#include <std.h>
#include <stdproperties.h>

//#define DEBUG_WHO shadow_who
//#define DEBUG_LEVEL 255
//#define DEBUG_ON
//#undef DEBUG_ON
//#include "/d/Emerald/sys/debug.h"

// prototypes are kept in shadow.h
//#include "shadow.h"

//#define SW shadow_who

//void kick_out_bounder();

/*
 * Function name: query_guild_name_lay
 * Description:   Return the guild's name
 * Returns:       The guild's name
 */
string query_guild_name_lay() { return GUILD_NAME; }

/*
 * Function name: query_guild_style_lay
 * Description:   Return the guild's style
 * Returns:       The guild's style
 */
string query_guild_style_lay() { return GUILD_STYLE; }

/*
 * Function name: query_guild_tax_lay
 * Description:   Returns the guild's tax
 * Returns:       The guild's tax
 */
int query_guild_tax_lay() { return GUILD_TAX; }

/*
 * Function name: delay_init_bounder
 * Description:   Called to add/initialize various things, including
 *                guild soul.
 */
nomask void delay_init_scout()
{
  setuid();
  seteuid(getuid());
/*
  if (QUERY_PUNISH(SW, EXPEL) > 0)
  {
    kick_out_bounder();
    return;
  }
*/
#ifdef BOUNDER_CMDSOUL
  if (SW->add_cmdsoul(BOUNDER_CMDSOUL))
  {
    SW->update_hooks();
  }
#endif

/*
#ifdef GUILD_EMBLEM
  COTO(GUILD_EMBLEM, SW);
#endif
*/
}

