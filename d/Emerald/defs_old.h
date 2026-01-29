/*  The following defines have been either: created by myself, created
*  by the good Arch Quetzl, or borrowed from the Shire (hey, I used
   *  to code there), who borrowed them from Gondor (hey, someone used
   *  to work there too... funny how these things get passed along)
*  Addition of defines should always be tested, because if this
   *  file is buggy, so will be all files including it.
*  /Mayhem   14 October, 1994
*/
/* Heh...if you're gonna give credit, give it where it's due...
   * A lot of these were here before you joined Emerald, Mayhem!
* In fact, I even recall writing some!!!!!
* And some where here even before *I* joined!
*
* Napture.
*
* Dec 17, 1995 changed BS(x) to break_string((x), 75)
* also WROAD_DIR to the appropriate path. was temp dir, now in permanent
*/

#ifndef _EMERALD_DEFS_
#define _EMERALD_DEFS_

#include <stdproperties.h>
#include <ss_types.h>
#include <std.h>
#include <macros.h>

#define DOMAIN_NAME  "Emerald"

#define VOL             "/d/Emerald/mountains/volcano/"
#define VNPC    "/d/Emerald/mountains/volcano/npc/"
#define VOBJ            "/d/Emerald/mountains/volcano/obj/"

#define HOME_DIR     "/d/" + DOMAIN_NAME + "/"

#define COMMON_DIR   HOME_DIR + "common/"

#define VOLCANO_DIR HOME_DIR + "mountains/volcano/"
#define GUILD_DIR    COMMON_DIR + "guild/"
#define PIRATES_DIR  GUILD_DIR + "pirates/"

#define HELP_DIR     HOME_DIR + "help/"

#define SANC_DIR   HOME_DIR + "sanctuary/"
#define MARSH_DIR HOME_DIR + "forest/south/marsh/"

#define CENTER_DIR    SANC_DIR + "center/"
#define CAVE_DIR      "/d/Emerald/mountains/mtblack/cave/"
#define CHAPEL_DIR    HOME_DIR + "leah/chapel/"
#define ECLIPSIA_DIR HOME_DIR + "eclipsia/"
#define CORAL_REQ ECLIPSIA_DIR + "coral_requiem/"
#define FOREST_DIR   HOME_DIR + "forest/"
#define FARM_DIR   HOME_DIR + "farm/"
#define HHOUSE_DIR  HOME_DIR + "house/"
#define LAKE_DIR      HOME_DIR + "lake/"
#define MINE_DIR     HOME_DIR + "mountains/mines/"
#define N_SWAMP_DIR   HOME_DIR + "bog/"
#define PATH_DIR    HOME_DIR + "path/"
#define MBLACK_DIR "/d/Emerald/mountains/mtblack/"
#define TELSERON_DIR HOME_DIR + "telseron/"
#define TOWNSHIP_DIR  TELSERON_DIR
#define TELBERIN_DIR  HOME_DIR + "telberin/"
#define LEAH_DIR  HOME_DIR + "leah/"
#define KROAD_DIR   HOME_DIR + "kroad/"
#define WROAD_DIR     HOME_DIR + "wroad/"
#define CAVERNS_DIR   HOME_DIR + "mountains/caverns/"
#define ISLAND_DIR    "/d/Emerald/island/"
#define WELL_DIR      CAVE_DIR + "well/"
#define QUARRY_DIR    "/d/Emerald/mountains/quarry/"

#define CTOWER_DIR    HOME_DIR + "ctower/"
#define GRAVEYARD_DIR "/d/Emerald/kroad/graveyard/"
#define MINE_LOW_DIR "/d/Emerald/mountains/mine_low/"
#define MONKRUIN_DIR KROAD_DIR + "monkruins/"
#define TEMPLE_DIR   MONKRUIN_DIR + "temple/"
#define VILLAGE_DIR HOME_DIR + "leah/"

#define GRUNTS_DIR    GUILD_DIR + "grunts/"
#define KOT_DIR      GUILD_DIR + "kot/"
#define VAMP_DIR      GUILD_DIR + "vamp/"
#define VAMP_AREA_DIR KROAD_DIR + "vamp/"
#define ESMIRIN_DIR HOME_DIR + "geraden/esmirin/"

#define HERB_DIR COMMON_DIR + "herbs/"

#define TELSERON_ARM "_emerald_telseron_royal_eq"
#define TELSERON_WEP "_emerald_telseron_royal_eq"
#define TELBERIN_ARM "_emerald_telberin_royal_eq"
#define TELBERIN_WEP "_emerald_telberin_royal_eq"

/* These are the KROAD rooms up to the gates of each city or into
   areas off the beaten path
   */

#define ROAD_ROOMS ({ KROAD_DIR, TELBERIN_DIR + "outskirts/", \
			TELBERIN_DIR + "road/", TELBERIN_DIR + \
			"landing", TELBERIN_DIR + "bridge1", \
			TELBERIN_DIR + "bridge2", TELBERIN_DIR + \
  			"bridge3", TELBERIN_DIR + "bridge4" })

#define SHIP_ROOM_BASE "/d/Emerald/lake/ship_room"
#define INTRO_FILE        INHERIT_DIR + "intro_trig"
#define DEBUGFILE "/d/Emerald/sys/debug.h"
#define EMERALD_MONSTER "/d/Emerald/std/emerald_monster.c"


#define DO_I_TELL_RUMOURS "_do_i_tell_rumours"

#define TP this_player()
#define TO this_object()
#define TI this_interactive()
#define PO previous_object()
#define CAP(x) capitalize(x)
#define C(x)   capitalize(x)
#define LC(x)  lower_case(x)
#define L(x)   lower_case(x)

#define NF(x)    notify_fail(x)
#define NFN(x)   NF(BSN(x))
#define NFN0(x)  { NFN(x); return 0; }

#define QP(x, y)	(x->query_prop(y))
#define AP(x, y, z)	(x->add_prop(y, z))
#define CP(x, y, z) (x->change_prop(y, x->query_prop(y) + z))
#define RP(x, y)	(x->remove_prop(y))

#define LOAD_CLONE_HANDLER(x) \
    if (interactive(this_player())) catch(call_other(x, "??"));

#define HE_SHE(x)  x->query_pronoun()
#define PRON(x)    HE_SHE(x)
#define HIM_HER(x) x->query_objective()
#define OBJ(x)     x->query_objective()
#define HIS_HER(x) x->query_possessive()
#define POS(x)     HIS_HER(x)

#define ENV(x) environment(x)
#define E(x)   environment(x)
#define EO     environment(this_object())
#define ETO    environment()
#define ETP    environment(this_player())
#define EP     environment(this_player())

#define IS_WIZ(x) (interactive(x) && \
   SECURITY->query_wiz_rank(x->query_real_name()))
#define EMRLD_WIZ(x) (interactive(x) && \
   SECURITY->query_wiz_dom(x->query_real_name()) == DOMAIN_NAME)

#define CLIMB(x) x->query_skill(SS_CLIMB)

#define MAKE_MONEY set_alarm(1.0,0.0,"get_money")

#define INSIDE   add_prop(ROOM_I_INSIDE, 1)
#define LIGHT(x) add_prop(ROOM_I_LIGHT, x)
#define FEARLESS_NPC "_emerald_fearless_npc"

#define FIXEUID { setuid(); seteuid(getuid()); }

#define ADD_SKIN \
add_leftover("/d/Roke/common/carisca/obj/skin","skin",1,"",1,1);

#define WRITE_LOG(F, O, T)  write_file( F, sprintf("%-52s (%s)\n", \
      O->query_name()+" "+ T, ctime(time())))

#endif
