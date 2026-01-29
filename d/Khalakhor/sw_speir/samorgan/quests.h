#ifndef _KHALAKHOR_SAMORGAN_QUESTS
#define _KHALAKHOR_SAMORGAN_QUESTS

#define SAMORGAN_QUEST_GROUP 0
#define SAMORGAN_QUEST_GIRL_SHOPPING_BIT 7
#define SAMORGAN_QUEST_GIRL_SHOPPING_EXP 450
#define SAMORGAN_QUEST_GIRL_SHOPPING_GEM "sapphire"
#define SAMORGAN_QUEST_BOY_EQUIPMENT_BIT 8
#define SAMORGAN_QUEST_BOY_EQUIPMENT_EXP 450
#define SAMORGAN_QUEST_BOY_EQUIPMENT_GEM "emerald"
#define SAMORGAN_QUEST_FEED_GUARDS_BIT   9
#define SAMORGAN_QUEST_FEED_GUARDS_EXP   900

// Properties

#define QUEST_M_GIRL_SHOPPING_LIST "_quest_m_girl_list"
#define QUEST_M_BOY_EQUIPMENT_LIST "_quest_m_boy_list"
#define QUEST_M_GUARD_MENU_LIST    "_quest_m_guard_list"

#define GET_GEM(x) (clone_object("/d/Genesis/gems/obj/" + x)->move(TO))

#define QUEST_NPC "/d/Khalakhor/sw_speir/samorgan/npc/quest-npc"

#endif
