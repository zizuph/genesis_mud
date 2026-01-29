/* A simple sheepish sheep
*
* Credit to: Quetzl, Erane.
*            Mercade, Napture
* 
* Normal task system implemented
*
* Segoy 950127           
* Revision log
*
* Jakob 950712  Changed from monster to creature.
* Amelia 4/30/97--set_pname -> "sheep"
* Ckrik 9/2003 Adapted to Earthsea domain 
*/ 

#pragma strict_types

inherit "/std/creature";
inherit "/std/combat/unarmed";
inherit "/std/act/domove"; 
inherit "/std/act/action"; 

#include <macros.h>
#include <stdproperties.h>
#include <wa_types.h>
#include <ss_types.h>
#include <tasks.h>

#define TYPES ({ "furry", "fluffy", "soiled" })
#define DESCS ({ "stupid", "tired", "well-fed" })

private int key = 0;
private string type = TYPES[random(3)], desc = DESCS[random(3)];

public void
create_creature()
{ 
    set_name("sheep");
    set_pname("sheep");
    set_adj(({ type, desc }));
    set_long("The sheep is slowly chewing some grass. \n");
    set_race_name("sheep");
    set_stats(({ 20, 20, 20, 10, 10, 15}));
    set_act_time(5);
    add_act("emote chews some grass.");
    add_act("emote grins sheepishly at you. ");
    add_act("emote goes: Baeh! baeh! baeh!");
    set_attack_unarmed(1, 40, 20, W_SLASH,  30, "left paw");
    set_attack_unarmed(2, 40, 20, W_SLASH,  30, "right paw");
    set_hitloc_unarmed(0, ({ 15, 25, 20, 20 }), 20, "head");
    set_hitloc_unarmed(1, ({ 10, 15, 30, 20 }), 80, "body");
    /* Fix me: Add new left overs (Ckrik)*/
    //add_leftover(CARISCA + "obj/skin", "fur", 1, "", 1, 1);
    set_random_move(10);
    set_alignment(0);
//  add_prop(OBJ_I_SEARCH_TIME, 3);
//  add_prop(OBJ_S_SEARCH_FUN, "to_find");
}

public string
to_find(object tp, string str)
{
    if(type == "soiled")
    {
        if((tp->resolve_task(TASK_ROUTINE, SS_AWARENESS) > 0) &&
            (key == 0) && (!tp->query_prop("_es_thwil_searched_sheep")))
        {
            setuid();
            seteuid(getuid());
            clone_object("/d/Earthsea/roke/thwil/obj/key")->move(tp, 1);
            key = 1;
            tp->add_prop("_es_thwil_searched_sheep", 1);
            return "Thorough inspection of the sheep " +
                "reveals a key stuck into the fur! " +
                "You carefully untie the key and pick " +
                "it up.\n";
        }

        return "You search the soiled sheep, " +
            "but your eyes are not " +
            "skilled enough to discover anything.\n";
    }

    return 0;
}

public int
push(string arg)
{
    if(!strlen(arg))
    {
        return notify_fail("Push what?\n");
    }

    if(sscanf(arg, "sheep %s", arg) != 1)
    {
        return notify_fail("Push what?\n");
    }

    if(member_array(arg, (environment(this_object())->query_exit_cmds())) < 0)
    {
        return notify_fail("Push the sheep where?\n");
    }

    write("The sheep bleats reluctantly! \n");
    say(QCTNAME(this_player()) + " pushes the sheep " + arg + ".\n");
    command(arg);
    return 1;
}

public void
init_living()
{
    ::init_living();
    add_action("push", "push");
}
