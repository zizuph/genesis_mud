#define GUILD_NAME           "Blademasters of Khalakhor"
#define GUILD_STYLE          "fighter"
#define GUILD_TYPE           "layman"
#define GUILD_TAX            9

/* Conf. vet to remain. (changed temp while recode in progress) */
#define REMAIN_SWORD_SKILL   65
/* Sup. vet sword to join. (changed temp while recode in progress) */
#define JOIN_SWORD_SKILL     65
/* Sup. master for the 'High' prefix. */
#define HIGH_SWORD_SKILL     90
#define FORM_STR_MIN         50
#define FORM_DEX_MIN         50
#define FORM_2H_MIN          30

#define PATH                 "/d/Khalakhor/guilds/blademasters/"
#define SPECIAL              PATH + "special/"
#define WEP                  PATH + "weapons/"
#define ARM                  PATH + "armours/"
#define OBJ                  PATH + "objects/"
#define DOCS                 PATH + "docs_mortal/"
#define SHADOW               (SPECIAL + "blade_shadow")
#define SOUL                 (SPECIAL + "blade_soul")
#define TOKEN                (OBJ + "blade_chain")
#define JOIN_SCROLL          (OBJ + "scroll")

#define BLADEMASTER_CHAIN_NAME "_khalakhor_blademaster_chain"
#define BLADEMASTER_SWORD_NAME "_khalakhor_blademaster_sword"
#define BLADEMASTER_NO_DECAPITATE "_khalakhor_blademaster_no_decap"

#define IS_BLADEMASTER(x)    (x->query_guild_name_lay() == GUILD_NAME)
#define IS_BLADEMASTER_BIT   4, 0

#define OBJ_I_BLADEMASTER_ARM  "_obj_i_blademaster_arm"
#define OBJ_I_BLADEMASTER_GOBJ "_obj_i_blademaster_gobj"

#define TP this_player()
#define TO this_object()
#define NF(x) notify_fail(x)

#undef STAT_CAP
