/*
 * This file contains some handy defs for the
 * Shadow Walkers guild.
 * Created By : Rico 7.01.97
 * First Modif: 
 */

#pragma strict_types

#include "/d/Kalad/defs.h"

/*
#define   GUILD_NAME   "Shadow Walkers"
#define   GUILD_TYPE   "layman"
#define   GUILD_STYLE  "thief"
*/

#define   SW_SHADOW    "specials/shadow"
#define   SW_SOUL      "specials/soul"

#define   TAX          7

#define   SOULDESC(ob)   (this_player()->add_prop(LIVE_S_SOULEXTRA, (ob)))
#define   TEST_GUILD_NAME(ob)   (ob->query_guild_name_lay())

#include "/d/Kalad/defs.h"
#include <stdproperties.h>
#include <macros.h>
#include <filter_funs.h>

#define SHADOW          "/d/Kalad/common/guilds/sh_walkers/"
/*
#define SOULDESC(s)     (this_player()->add_prop(LIVE_S_SOULEXTRA, (s)))
#define GUILD_TYPE      "layman"
#define GUILD_STYLE     "thief"
*/
#define BOX             "shadow_box" /* Can change.. just for now. */
#define GUILD_LAY_TAX   8
#define SHADOW_SUB      "shadow_subloc"

#define NEVERKNOWN      add_prop(LIVE_I_NEVERKNOWN, 1)
#define ALWAYSKNOWN     add_prop(LIVE_I_ALWAYSKNOWN, 1)

