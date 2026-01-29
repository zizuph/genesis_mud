/*
 *
 */
#pragma strict_types
#include "imbuement.h"

#include <macros.h>
#include <files.h>

#define IMBUEMENTS_HIDDEN   1

#include "/d/Genesis/specials/debugger/debugger_tell.h"


/* Prototypes */
public void             create();
public void             notify_new_object(object obj);
public mixed            roll(object obj);


/* Global Variables */
//string              imbuement = "r";

/*
 * Function name:        create
 * Description  :        set up
 */
public void
create()
{
    setuid();
    seteuid(getuid());
    
    LISTENER_ADD(this_object());
} /* create */

/*
 * Function name:        notify_new_object
 * Description  :        called when something is cloned
 */
public void
notify_new_object(object obj)
{
//    int pow1, pow2, pow3;
//    TELL_G("New object: " + file_name(obj));
    object env;

    if (calling_program() != "sys/global/listeners.c")
        if (!IMBUE_MASTER->check_access()) return;

//    send_debug_message("Imbuement", file_name(obj) + " " + file_name(environment(obj)));

    if (!obj)
        return;
    env = environment(obj);
    if (!env)
        return;

    if (!env->query_npc())
        return;

    if (!environment(env))
        return;

//    if (!wildmatch("/d/Sparkle/*", MASTER_OB(environment(environment(obj)))) &&
//        !wildmatch("/d/Genesis/*", MASTER_OB(environment(environment(obj)))))
    if (!wildmatch("/d/*", MASTER_OB(environment(env))))
        return;

    if (wildmatch("/d/Sparkle/area/tutorial/*", MASTER_OB(environment(env))))
        return;

    if (env->query_prop(IMBUE_PROP_ROLLED))
        return;

    if (!IS_WEAPON_OBJECT(obj) && !IS_ARMOUR_OBJECT(obj))
        return;

    //send_debug_message("Imbuement", file_name(obj) + " ready for imbuement.");

    env->add_prop(IMBUE_PROP_ROLLED, 1);

    if (!random(99))
    {
        send_debug_message("Imbuement", "Rolling");
//        set_alarm(0.1,0.0, &roll(env));
        roll(env);
        //IMBUE_GENERATOR->imbue_random(obj);
    }
    else
        send_debug_message("Imbuement", file_name(env) + " no imbuements.");
} /* notify_new_object */


/*
 * Function name:        roll
 * Description  :        give an imbuement to a random item carried by NPC
 */
public mixed
roll(object npc)
{
    object *inv, obj;

//    if (calling_program())
    if (!IMBUE_MASTER->check_access()) return;

    send_debug_message("Imbuement", "Imbuing for " + file_name(npc));
    
    inv = all_inventory(npc);
    if (!inv)
    {
        send_debug_message("Imbuement", "No items in " + file_name(npc) + "!");
        return;
    }
    
    inv = FILTER_WEAPON_OBJECTS(inv) + FILTER_ARMOUR_OBJECTS(inv);
    obj = one_of_list(inv);
    send_debug_message("Imbuement", "Chose " + file_name(obj) + " from " + 
        sizeof(inv) + " items.");

    IMBUE_GENERATOR->imbue_random(obj, IMBUEMENTS_HIDDEN);
} /* roll */
