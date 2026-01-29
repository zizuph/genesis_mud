#ifndef _SHIRE_ADMIN_DEFS
#define _SHIRE_ADMIN_DEFS

//#include "/d/Shire/sys/defs.h"
/* These defs are handy defines for the admin of the Shire */

/* QUEST_MASTER defines */
#define ADD_QUEST(short_name, group, bit, exp, long_name) \
          (int)QUEST_MASTER->add_quest(short_name,group,bit,exp,long_name)
#define CLOSE_QUEST(short_name)  (int)QUEST_MASTER->close_quest(short_name)
#define LIST_QUESTS              (int)QUEST_MASTER->list("quests")
#define LIST_BITS                (int)QUEST_MASTER->list("bits") 
#define OPEN_QUEST(short_name)   (int)QUEST_MASTER->open_quest(short_name)
#define REMOVE_QUEST(short_name) (int)QUEST_MASTER->remove_quest(short_name)


/*  Liege and Steward Defines */
#define SHIRE_LIEGE    find_player("/secure/master"->query_domain_lord("gondor"))
#define SHIRE_STEWARD  find_player("/secure/master"->query_domain_steward("gondor"))
#define SHIRE_FRIEND   find_player("")
#define SHIRE_MEM1    find_player("")
#define SHIRE_MEM2    find_player("")
#define SHIRE_MEM3    find_player("")
#define SHIRE_MEM4    find_player("")
#define SHIRE_MEM5    find_player("")
#define SHIRE_MEM6    find_player("")
#define SHIRE_MEM7    find_player("")


#define TELL_LIEGE(x)  SHIRE_LIEGE->catch_tell(x + "\n")
/*
#define TELL_ADMIN(x) filter(({SHIRE_LIEGE,SHIRE_FRIEND,SHIRE_STEWARD})  \
          - ({0}), not @ &->query_prop("_Shire_i_no_admin_tells")) \
          ->catch_tell(x +"\n")
*/

#define TELL_ADMIN(x) filter(map(("/secure/master"->query_domain_members("gondor")), find_living) \
    - ({ 0 }), not @ &->query_prop("_Shire_i_no_admin_tells"))->catch_tell("Adm: " + x + "\n")


/*  Object searching defines, useful for finding how many
    of an object is in the game and what players have them. */

#define FIND_OBJECT(str)   {a = clone_object(str); \
                     b = object_clones(a) - ({a}); a->remove_object(); \
                     b = filter(b, &not() @ &->query_prop(OBJ_I_BROKEN)); \
                     b = map(b, environment); \
                     b = filter(b, &not() @ &->query_npc()); \
                     return b->short(); }
#endif
