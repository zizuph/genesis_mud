/*
 * File Name        : local.h
 * By               : Elmore and Boron
 * Inspiration from : Pirates by Elmore
 *                    The Neidar Guild by Arman.
 *                    Occ_fighter Guild by Unknow.
 * Date             : Nov. 2000.
 *
 */

#define GUILD_NAME             "Sentries of Palanthas"
#define GUILD_STYLE            "fighter"
#define GUILD_TAX              20
#define GUILD_WIZARD           "Boron"
#define GUILD_LEADER           "Noone!"
#define I_CAN_BECOME_KNIGHT    "_i_can_become_a_knight"

#define GUILD_DIR              "/d/Krynn/solamn/palan/guild/"
#define GUILD_SHADOW           GUILD_DIR + "shadow/shadow"
#define GUILD_CMDSOUL          GUILD_DIR + "soul/soul"
#define GUILD_ROOM             GUILD_DIR + "room/"
#define GUILD_OBJ              GUILD_DIR + "obj/"
#define GUILD_EMBLEM           GUILD_OBJ + "sword"
#define GUILD_NPC              GUILD_DIR + "npc/"
#define GUILD_LOG              GUILD_DIR + "log/"
#define KNIGHT_BOARD           GUILD_LOG + "boards/normal/"

/* A unique id for the guild's emblem */
#define GUILD_EMBLEM_ID GUILD_NAME + " emblem"

/* The skill number for the guild's special skill.
 * Check with the liege of your domain to get your own skills.
 */
#define SS_GUILD_SPECIAL_SKILL 132341

#define GUILD_STARTLOC GUILD_ROOM + "start"


