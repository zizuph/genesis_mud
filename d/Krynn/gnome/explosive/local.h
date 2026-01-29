/* Local defs for the gnome area */
/* Louie - March 2004 */

#include "/d/Krynn/common/defs.h"

#define GNOME "/d/Krynn/gnome/explosive/"
#define GNOME_STD GNOME + "std/"
#define GNOME_NPC GNOME + "npc/"
#define GNOME_ROOM GNOME + "room/"
#define GNOME_OBJ GNOME + "obj/"
#define GNOME_IR GNOME_STD + "i_room_base.c"
#define GNOME_BASE GNOME_STD+"gnome_base.c"
#define GNOME_EXPL_CONTROL (GNOME_ROOM +"explosive_control")
#define OLD_GNOME "/d/Krynn/gnome/"
#define OLD_GNOME_OBJ OLD_GNOME+"obj/"
#define OLD_GNOME_MON OLD_GNOME+"monster/"
#define SHORT(x) set_short(x)
#define LONG(x) set_long(x)
#define EXIT(w,x,y,z) add_exit(w,x,y,z)
#define ITEM(x,y) add_item(x,y)
#define CMD(x,y,z) add_cmd_item(x,y,z)

#define IS_EXPL     GNOME_EXPL_CONTROL->query_state_destroyed()
#define DOOR1_STATE GNOME_EXPL_CONTROL->query_door1()
#define DOOR1_CLOSE GNOME_EXPL_CONTROL->close_door1()
#define DOOR2_STATE GNOME_EXPL_CONTROL->query_door2()
#define DOOR2_CLOSE GNOME_EXPL_CONTROL->close_door2()

#define LIVE_I_DESIGN_APPROVED "_live_i_design_approved"
#define LIVE_I_WAIVER_APPROVED "_live_i_waiver_approved"

#define GNOME_BOMB_QUEST_XP          400
#define GNOME_BOMB_QUEST_BONUS_XP    200

#define GNOME_DOM  "krynn"
#define GNOME_GRP  3
#define GNOME_BIT  0
