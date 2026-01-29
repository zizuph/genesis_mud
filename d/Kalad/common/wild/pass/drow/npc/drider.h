// file name:        /d/Avenir/drow/npc/drider.h
// creator(s):       Nikklaus, March'97
// revision history:
// purpose:          Feel out the tool_slots, hitlocs and attacklocs the Drider
//                   will need and then base a combat extern on it.
// note(s):          Some swore it couldn't be done. I swore back at them.
// to-do:
// bug(s):           Give it time...

#include <wa_types.h>
#define QEXC (this_object()->query_combat_object())

/*  Humanoid tool slots:  Already defined in wa_types.
 * TS_TORSO  2
 * TS_HEAD 4
 * TS_NECK 16384
 * TS_RARM 16
 * TS_LARM 32
 *
 * TS_RHAND 128
 * TS_LHAND 256
 * TS_RWEAPON 512
 * TS_LWEAPOn 1024
 */

/*  Arachnid tool slots
 * TS_ABDOMEN = TS_WAIST 8129
 * TS_CARAPACE = TS_ROBE 64
 * TS_LEGS 8
 * TS_RFLEG = TS_RFOOT 2048
 * TS_LFLEG + TS_LFOOT 4096
 * TS_RMLEG = TS_RFINGER 65536
 * TS_LMLEG = TS_LFINGER 32768
 */
# define TS_ABDOMEN TS_WAIST
# define TS_CARAPACE TS_ROBE
# define TS_RFLEG TS_RFOOT
# define TS_LFLEG TS_LFOOT
# define TS_RFLEG TS_RFOOT
# define TS_LFLEG TS_LFOOT
# define TS_RMLEG TS_RFINGER
# define TS_LMLEG TS_LFINGER

/*  Arachnid hitlocs
 */
# define A_ABDOMEN A_WAIST
# define A_CARAPACE A_ROBE
# undef A_BODY
# define A_BODY (A_TORSO | A_ABDOMEN)
# define A_RFLEG TS_RFLEG
# define A_LFLEG TS_LFLEG
# define A_RMLEG TS_RMLEG
# define A_LMLEG TS_LMLEG
# undef A_LEGS
# define A_LEGS (A_RFLEG | A_RMLEG | A_LFLEG | A_LMLEG)

/*  Arachnid attacklocs
 */
# define W_RFLEG TS_RFLEG
# define W_LFLEG TS_LFLEG
# define W_RMLEG TS_RMLEG
# define W_LMLEG TS_LMLEG
# define W_FLEGS (W_RFLEG | W_LFLEG)
# define W_MLEGS (W_RMLEG | W_LMLEG)

