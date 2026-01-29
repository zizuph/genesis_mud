/*
 * Useful way to alert domain menbers when NPCs are cloned and/or attacked
 * Copied over from Shire
 * -- Finwe July 2005
 */
#define GON_LIEGE    ("/secure/master"->query_domain_lord("gondor"))
#define GON_STEWARD    ("/secure/master"->query_domain_steward("gondor"))
#define GON_MEM1    find_player("")
#define GON_MEM2    find_player("")
#define GON_MEM3    find_player("")
#define GON_MEM4    find_player("")
#define GON_MEM5    find_player("")
#define GON_MEM6    find_player("")
#define GON_MEM7    find_player("")

#define TELL_LIEGE(x)  GON_LIEGE->catch_tell(x + "\n")

#define TELL_ADMIN(x) filter(map(("/secure/master"->query_domain_members("gondor")), find_living) \
    - ({ 0 }), not @ &->query_prop("_Gondor_i_no_admin_tells"))->catch_tell("Adm: " + x + "\n")

#define FIND_OBJECT(str)   {a = clone_object(str); \
                     b = object_clones(a) - ({a}); a->remove_object(); \
                     b = filter(b, &not() @ &->query_prop(OBJ_I_BROKEN)); \
                     b = map(b, environment); \
                     b = filter(b, &not() @ &->query_npc()); \
                     return b->short(); }


/*

    Include the following file:

#include "/d/Gondor/private/gondor_admin.h"

    add to npc creation, replace NPC_NAME with npc's name:

TELL_ADMIN("[NPC_NAME clone at " + ctime(time()) + "]");


    add following routine to be notified when attacked:

void
attacked_by(object ob)
{
    object *arr;

    ::attacked_by(ob);
    TELL_ADMIN("[NPC_NAME attacked by " + ob->query_cap_name() + "("+ob->query_average_stat()+") at " + ctime(time()) + "]");
}


*/
