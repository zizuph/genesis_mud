/*
 * Definitions for Isengard.
 */
 
#ifndef ISENGARD_DEFINITIONS
#define ISENGARD_DEFINITIONS
 
/* To guard against redefinitions, do not add definitions before this line.
 */
 

/* Directories.
 */
 
#define IGARD_DIR            "/d/Gondor/rohan/isengard/igard/"

#define IGARD_WALL           IGARD_DIR          + "wall/"
#define IGARD_WALL_OBJ       IGARD_WALL         + "obj/"
#define WALL_FLOOR_ONE       IGARD_WALL         + "floor1/"
#define WALL_TUNNEL_ONE      WALL_FLOOR_ONE     + "tunnel/"
#define WALL_FLOOR_TWO       IGARD_WALL         + "floor2/"
#define WALL_TUNNEL_TWO      WALL_FLOOR_TWO     + "tunnel/"
#define WALL_FLOOR_THREE     IGARD_WALL         + "floor3/"
#define WALL_TUNNEL_THREE    WALL_FLOOR_THREE   + "tunnel/"
#define WALL_FLOOR_FOUR      IGARD_WALL         + "floor4/"

#define IGARD_PLAIN          IGARD_DIR    + "plain/"
#define IGARD_PLAIN_OBJ      IGARD_PLAIN  + "obj/"
#define IGARD_PLAIN_PATHS    IGARD_PLAIN  + "paths/"

#define IGARD_DEEP           IGARD_DIR    + "deep/"
#define IGARD_DEEP_OBJ       IGARD_DEEP   + "obj/"
#define IGARD_DEEP_ORC       IGARD_DEEP   + "orc/"
#define IGARD_DEEP_FURNACE   IGARD_DEEP   + "furnace/"
#define IGARD_DEEP_WARG      IGARD_DEEP   + "warg/"
#define IGARD_DEEP_PRISON    IGARD_DEEP   + "prison/"
#define IGARD_DEEP_ARMOURY   IGARD_DEEP   + "armoury/"

#define ORTHANC              IGARD_DIR    + "orthanc/"
#define ORTHANC_OBJ          ORTHANC      + "obj/"

#define IGARD_QUEST          IGARD_DIR    + "quest/"
#define IGARD_QUEST_OBJ      IGARD_QUEST  + "obj/"

#define IGARD_OBJ            IGARD_DIR    + "obj/"
#define IGARD_NPC            IGARD_DIR    + "npc/"
#define IGARD_WEP            IGARD_DIR    + "wep/"
#define IGARD_ARM            IGARD_DIR    + "arm/"
#define IGARD_ROOM           IGARD_DIR    + "room/"
#define IGARD_TEXT           IGARD_DIR    + "text/"
#define IGARD_LIB            IGARD_DIR    + "lib/"
#define IGARD_EXTERIOR       IGARD_DIR    + "exterior/"

#define IGARD_LOG            IGARD_LIB    + "log/"
#define IGARD_KILL_LOG       IGARD_LOG    + "igardkills"


/* Properties.
 */

#define ENEMY_OF_IGARD          "_enemy_of_igard"
#define FRIEND_OF_IGARD         "_friend_of_igard"
#define IGARD_ARMOUR            "_igard_armour"
#define IGARD_WEAPON            "_igard_weapon"
#define MTIRITH_ARMOUR          "_mtirith_armour"
#define IGARD_AMBUSHED          "_igard_ambushed"
#define ENEMY_OF_PRISONERS      "_enemy_of_prisoners"
#define FRIEND_OF_MTIRITH       "_friend_of_mtirith"
#define GOODIE_IGARD_QUEST      "_goodie_igard_quest"
#define BADDIE_IGARD_QUEST      "_baddie_igard_quest"
#define SENT_IGARD_WALL1        "_sent_igard_wall1"
#define SENT_IGARD_WALL2        "_sent_igard_wall2"
#define SENT_IGARD_WALL3        "_sent_igard_wall3"
#define SENT_IGARD_WALL4        "_sent_igard_wall4"
#define SENT_IGARD_WALL5        "_sent_igard_wall5"
#define SENT_IGARD_WALL6        "_sent_igard_wall6"
#define SENT_IGARD_WALL7        "_sent_igard_wall7"
#define FINISHED_IGARD_WALL     "_finished_igard_wall"
#define SENT_FURNACE_IGARD1     "_sent_furnace_igard1"
#define SENT_FURNACE_IGARD2     "_sent_furnace_igard2"
#define SENT_FURNACE_IGARD3     "_sent_furnace_igard3"
#define FINISHED_FURNACE_IGARD  "_finished_furnace_igard"
#define SENT_ORCWARG_IGARD1     "_sent_orcwarg_igard1"
#define SENT_ORCWARG_IGARD2     "_sent_orcwarg_igard2"
#define FINISHED_ORCWARG_IGARD  "_finished_orcwarg_igard"
#define SENT_IGARD_CAVERNS      "_sent_igard_caverns"
#define FINISHED_IGARD_CAVERNS  "_finished_igard_caverns"
#define SENT_IGARD_ORTHANC      "_sent_igard_orthanc"
#define FURNACE_KILLED_ME       "_furnace_killed_me"
#define IGARD_EVIDENCE_TOURING  "_igard_evidence_touring"


/* Macros.
 */

#define WIZARD               this_player()->query_wiz_level()
#define GOODIE               this_player()->query_alignment() >= 0
#define BADDIE               this_player()->query_alignment() < 0
#define ENEMY                this_player()->query_prop(ENEMY_OF_IGARD)
#define FRIEND               this_player()->query_prop(FRIEND_OF_IGARD)
#define AMBUSHED             this_player()->query_prop(IGARD_AMBUSHED)
#define PRISONER_ENEMY       this_player()->query_prop(ENEMY_OF_PRISONERS)
#define MODIFY_PROP(who, prop, val)  who->add_prop(prop, \
                           who->query_prop(prop) + val)
#define ADD_SKILL(who,skill,val) who->set_skill_extra(skill, \
                           who->query_skill_extra(skill) + val)
#define GIQ         this_player()->query_prop(GOODIE_IGARD_QUEST)
#define BIQ         this_player()->query_prop(BADDIE_IGARD_QUEST)
#define SIW1        this_player()->query_prop(SENT_IGARD_WALL1)
#define SIW2        this_player()->query_prop(SENT_IGARD_WALL2)
#define SIW3        this_player()->query_prop(SENT_IGARD_WALL3)
#define SIW4        this_player()->query_prop(SENT_IGARD_WALL4)
#define SIW5        this_player()->query_prop(SENT_IGARD_WALL5)
#define SIW6        this_player()->query_prop(SENT_IGARD_WALL6)
#define SIW7        this_player()->query_prop(SENT_IGARD_WALL7)
#define FIW         this_player()->query_prop(FINISHED_IGARD_WALL)
#define SFI1        this_player()->query_prop(SENT_FURNACE_IGARD1)
#define SFI2        this_player()->query_prop(SENT_FURNACE_IGARD2)
#define SFI3        this_player()->query_prop(SENT_FURNACE_IGARD3)
#define FFI         this_player()->query_prop(FINISHED_FURNACE_IGARD)
#define SOI1        this_player()->query_prop(SENT_ORCWARG_IGARD1)
#define SOI2        this_player()->query_prop(SENT_ORCWARG_IGARD2)
#define FOI         this_player()->query_prop(FINISHED_ORCWARG_IGARD)
#define SIC         this_player()->query_prop(SENT_IGARD_CAVERNS)
#define FIC         this_player()->query_prop(FINISHED_IGARD_CAVERNS)
#define SIO         this_player()->query_prop(SENT_IGARD_ORTHANC)


/* To guard against redefinition, put all defs above this line.
 */
#endif ISENGARD_DEFINITIONS
