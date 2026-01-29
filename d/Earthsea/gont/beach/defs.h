#ifndef _EARTHSEA_DEFS_

#define _EARTHSEA_DEFS_
 
#include <stdproperties.h>
#include <ss_types.h>
#include <std.h>
#include <macros.h>
#include "/sys/filter_funs.h" 

#define DOMAIN_NAME     "Earthsea"

/* File and Directory Definitions 
 *-----------------------
 */

#define EARTHSEA                "/d/Earthsea/"
#define BEACH                   EARTHSEA + "gont/beach/"
#define SPARKLE_SHIP_DIR	BEACH + "ships/sparkle/"

#define NPC_DIR       BEACH + "npc/"
#define WEP_DIR       BEACH + "weapons/"
#define OBJ_DIR       BEACH + "obj/"
#define HOME_DIR      "/d/" + DOMAIN_NAME + "/"
#define KARG_DIR      "/d/Earthsea/gont/tenalders/npc/"

#define BEACH_DIR "/d/Earthsea/gont/beach/beach_rooms/"
#define PATH_DIR  "/d/Earthsea/gont/beach/forest_path_rooms/"
#define CLIFF_DIR "/d/Earthsea/gont/beach/cliff_rooms/"
#define KARG_LANDING_DIR "/d/Earthsea/gont/beach/karg_landing/"
#define KARG_ISLAND_DIR "/d/Earthsea/karg/island/"

#define TELL_ROOM "/d/Earthsea/lib/room_tell.c"
#define CLONE_HANDLER "/d/Earthsea/gont/beach/clone_handler.c"
#define FIND_ROUTINE BEACH + "find_routine.c"
#define TIDE "/d/Earthsea/gont/beach/tides.c"

/* Base Standard File Locations
 *------------------------------
 */

#define ROCKY "/d/Earthsea/gont/beach/std/base_rooms/base_beach_rocky.c"
#define SANDY "/d/Earthsea/gont/beach/std/base_rooms/base_beach_sandy.c"
#define HERB  "/d/Earthsea/gont/beach/std/base_rooms/base_herb_room.c"
#define PATH  "/d/Earthsea/gont/beach/std/base_rooms/base_path.c"
#define CLIFFS_ROOM "/d/Earthsea/gont/beach/std/base_rooms/base_cliffs.c"

/* Other Definitions
 *-------------------
 */
 
#define DO_I_TELL_RUMOURS "_do_i_tell_rumours"
 
#define TP              this_player()
#define TO              this_object()
#define TI              this_interactive()
#define PO              previous_object()
#define BS(x, y)        break_string(x, y)
 
#define CAP(x)          capitalize(x)
 
#define NF(x)           notify_fail(x)
#define NFN(x)          NF(BSN(x))

#define QTN(obj,beholder) obj->query_The_name(beholder)
 
#define QP(x, y)        (x->query_prop(y))
#define AP(x, y, z)     (x->add_prop(y, z))
#define CP(x, y, z)     (x->change_prop(y, x->query_prop(y) + z))
#define RP(x, y)        (x->remove_prop(y))
 
#define HE_SHE(x)       x->query_pronoun()
#define HIM_HER(x)      x->query_objective()
#define HIS_HER(x)      x->query_possessive()
#define OBJ(x)          x->query_objective()
 
#define ENV(x)          environment(x)
 
#define IS_WIZ(x) (interactive(x) && \
   SECURITY->query_wiz_rank(x->query_real_name()))
#define EARTHSEA_WIZ(x) (interactive(x) && \
   SECURITY->query_wiz_dom(x->query_real_name()) == DOMAIN_NAME)

 
#define FIXEUID         { setuid(); seteuid(getuid()); }
 
#define WRITE_LOG(F, O, T)  write_file( F, sprintf("%-52s (%s)\n", \
      O->query_name()+" "+ T, ctime(time())))
 

#endif

