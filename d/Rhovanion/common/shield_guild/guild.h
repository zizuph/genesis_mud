#define GUILD_STYLE "fighter"
/*
#define GUILD_NAME  "Shield and Club Warriors"
*/
#define GUILD_NAME  "Angmar Army"
#define SS_SMASH    138000
#define SMASH_NAME  "smash"
#define SHIELD_NAME "shield"
#define THIS_DIR    "/d/Rhovanion/common/shield_guild/"
#define OCC_SHADOW  THIS_DIR+"s_c_sh_occ"
#define LAY_SHADOW  THIS_DIR+"s_c_sh_lay"
#define SOUL        THIS_DIR+"s_c_soul"
#define SOUL_E_NEW  THIS_DIR+"soul_cmd"
#define SOUL_E_OLD  "/d/Genesis/cmd/soul_cmd_"
#define SOUL_RUMOUR THIS_DIR+"rumour_soul"

#define ADJ_LIST ({"Fresh","Insecure","Young","Training","Legionary", \
                   "Proud","Elder","Experienced","Dangerous","Notorious", \
                   "Cruel","Infamous","Bestial","Feared","Legendary",  \
                   "Mythical"})

#define SPEC_ATTACK_IS    "_s_c_spec_attack_is_"

#define TIME_TO_RELAX(who)  2+random(MAX(4, 30-(who->query_stat(SS_WIS)/10)))
#define TIME_TO_SMASH(who)  2+random(MAX(4, 30-(who->query_stat(SS_DEX)/10)))
#define RELAX    1
#define FOCUS    2
#define SMASH    3
#define DEFEND   4

#define S_C_PUN  "_s_c_punishment_"
