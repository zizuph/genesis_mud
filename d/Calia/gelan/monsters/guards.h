/* this is the includefile for the guards in Gelan

    history:     3.11.92    created                         Merlin

*/

/* ranks of the guards */

#define ENTRANCE_GUARD      0
#define ENTRANCE_LEADER     0
#define ENTRANCE_CHIEF      0
#define HON_ENTRANCE_1      0
#define HON_ENTRANCE_2      0
#define HON_ENTRANCE_3      0
#define EXP_ENTRANCE_1      34
#define EXP_ENTRANCE_2      0
#define EXP_ENTRANCE_3      36
#define FIGHTER_ENTRANCE_1  9
#define FIGHTER_ENTRANCE_2  14
#define FIGHTER_ENTRANCE_3  19
#define RECRUIT_ENTRANCE_1  1
#define RECRUIT_ENTRANCE_2  3
#define RECRUIT_ENTRANCE_3  5
#define BARRACKS_CHIEF      0
#define SQUARE_CHIEF        0
#define HON_SQUARE_1        0
#define HON_SQUARE_2        0
#define EXP_SQUARE_1        0
#define EXP_SQUARE_2        37
#define FIGHTER_SQUARE_1    24
#define FIGHTER_SQUARE_2    29
#define RECRUIT_SQUARE_1    7
#define RECRUIT_SQUARE_2    8

/* functions */

#define RESET_GUARD(rank)                   (GELAN_MONSTERS + "guards")->reset_guard(rank)
#define HELP_ME(meeting, room, attacker)    (GELAN_MONSTERS + "guards")->help_me(meeting, room, attacker)

/* meeting points */

#define MP_SOUTH            0                   /* standby guards */
#define MP_WEST             1                   /* town square west end */
#define MP_EAST             2                   /* town square east end */
#define MP_NORTH            3                   /* town square norht end center e */

