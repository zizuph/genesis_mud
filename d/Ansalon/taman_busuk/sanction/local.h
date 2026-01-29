/*
 *
 *    local.h - For the city of Sanction and the surrounding areas.
 *
 */

#ifndef SANCTION_DEF
#define SANCTION_DEF

#define DA_BOARD            "/d/Ansalon/taman_busuk/sanction/obj/da_board"

#define SANCTION            "/d/Ansalon/taman_busuk/sanction/"
#define SSTD                SANCTION + "std/"
#define SNPC                SANCTION + "npc/"
#define SOBJ                SANCTION + "obj/"
#define SROOM               SANCTION + "room/"
#define SCITY               SROOM + "city/"
#define DGUILD              "/d/Ansalon/guild/dragonarmy/room/"
#define SRED                SROOM + "red/"
#define SBLUE               SROOM + "blue/"
#define LUERK               SROOM + "luerkhisis/"
#define SLOG                SANCTION + "log/"
#define SLIB                SANCTION + "lib/"
#define SBOOK               SLIB + "book/"

#define NORMAL_BOARD       SLOG + "normal_board"
#define OFFICER_BOARD      SLOG + "officer_board"
#define BLUE_DARMY_BOARD   SLOG + "blue_board"
#define RED_DARMY_BOARD    SLOG + "red_board"
#define BLUE_O_BOARD       SLOG + "blue_o_board"
#define RED_O_BOARD        SLOG + "red_o_board"

/* Base files */

#define SANCINROOM          SSTD + "i_room_base"
#define SANCOUTROOM         SSTD + "o_room_base"
#define SANCTION_OUT    SANCOUTROOM
#define SANCTION_IN     SANCINROOM

#define KICKED_BAKARIS "_player_i_kicked_bakaris"
#define BAKARIS_BLOCKS "_bakaris_i_blocks_exit"

#endif SANCTION_DEF
