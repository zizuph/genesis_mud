
#define VAMP_DIR "/d/Terel/guilds/vamp/"

#define CORELIB_DIR  ("/d/Genesis/specials/")

#define SOUL_DIR     (VAMP_DIR+"soul/")
#define SHADOW_DIR   (VAMP_DIR+"shadow/")
#define OBJ_DIR      (VAMP_DIR+"obj/")
#define SPELL_DIR    (VAMP_DIR+"spells/")
#define ABILITY_DIR  (VAMP_DIR+"abilities/")
#define SPELLOBJ_DIR (SPELL_DIR+"obj/")
#define DATA_DIR     (VAMP_DIR+"data/")
#define LOG_DIR      (VAMP_DIR+"log/")
#define LIB_DIR      (VAMP_DIR+"lib/")
#define ROOM_DIR     (VAMP_DIR+"room/")
#define NPC_DIR      (VAMP_DIR+"npc/")
#define HELP_DIR     (VAMP_DIR+"help/")
#define VISION_DIR   (VAMP_DIR+"visions/")
#define BOOK_DIR     (VAMP_DIR+"books/")


#define OCC_MANAGER      (LIB_DIR+"vamp_manager")
#define LAY_MANAGER      (LIB_DIR+"bg_manager")
#define COFFIN_MANAGER   (LIB_DIR+"coffin_manager")
#define VISION_MANAGER   (LIB_DIR+"vision_manager")
#define VOTE_MANAGER     (LIB_DIR+"vote_manager")

#define TP            this_player()
#define TO            this_object()
#define CAP(obj)      capitalize(obj)
#define ENV(obj)      environment(obj)

#define QSW           query_shadow_who()

#define POSS(obj)     obj->query_possessive()
#define PRO(obj)      obj->query_pronoun()
#define OBJ(obj)      obj->query_objective()

#define SHORT(obj)    obj->short()

#define ISVAMP(obj)   obj->query_vampire()

#define IS_WIZ(x) (interactive(x) && \
    SECURITY->query_wiz_rank(x->query_real_name()))

#define IS_JR(x)  (interactive(x) && \
                    x->query_real_name()[-2..]=="jr")


#define ROOM_S_BLOOD_DIR   "_room_s_blood_dir"

#define MENTAL_SKILLS  ({SS_AWARENESS, TS_INT, TS_WIS, SS_FORM_ILLUSION })


