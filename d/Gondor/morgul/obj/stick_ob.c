inherit "/std/object";

#include <cmdparse.h>
#include <macros.h>
#include <stdproperties.h>
#include <tasks.h>
#include "/d/Gondor/defs.h"

#define MAX_DAM    500     /* maximum damage when tearing from web  */
#define MIN_DAM     50     /* minimum damage when tearing from web  */
object stick_object;       /* the object that's sticking to the web 
                              can be the player him/her-self        */

create_object()
{
    set_no_show(1);
    set_name("_Morgul_stick_object");
    add_prop(OBJ_M_NO_GET,1);
    add_prop(OBJ_M_NO_GIVE,1);
    add_prop(OBJ_M_NO_DROP,1);
    add_prop(OBJ_M_NO_SELL,1);
    add_prop(OBJ_M_NO_STEAL,1);
}

init()
{
    ::init();
    add_action("catch_all","",1);
    add_action("do_tear","tear");
    add_action("do_tear","pull");
}

int set_stick_object(object x)
{
    if(!x->query_worn() && x != ENV(TO))
        return 0;
    stick_object = x;
    return 1;
}

object query_stick_object() { return stick_object; }

void free_player(object player)
{
    if(stick_object->query_worn() == ENV(TO))
        return;

    tell_room(ENV(player),"The "+stick_object->query_name()+" remains sticking to the web.\n");
    stick_object->move(ENV(player));
    stick_object->add_prop(OBJ_M_NO_GET,"You cannot take it, it is sticking to the web.\n");
    set_alarm(0.0, 0.0, remove_object);
}

int catch_all(string str)
{
    string vb = query_verb();
    string nf = "You cannot do that!\n";
    object *rmo;

    if(!objectp(stick_object))
        return 0;

    if(!stick_object->query_worn() && stick_object != TP)
    {
        free_player(TP);
        return 0;
    }

    if(stick_object == TP)
        nf = "You cannot do that, your body is sticking to the threads of the web!\n";
    else
        nf = BSN("You cannot do that, your "+stick_object->query_name()+ " is sticking to " +
            "the threads of the web! Remove it first if you want to free yourself!");

    switch(vb)
    {
        case "climb":
        case "down":
        case "southwest":
        case "kill":
            write(nf); return 1; break;
        case "remove":
            if( member_array(stick_object, FIND_STR_IN_OBJECT(str, TP)) > -1  )
                set_alarm(0.0, 0.0, &free_player(TP));
            return 0; break;
        default: return 0; break;
    }
}

int do_tear(string str)
{
    string vb = query_verb();
    string dummy;
    int    itask;
    int    damage;

    if(stick_object != TP)
        return 0;

    NF(CAP(vb) + " what?\n");
    if(!str || (str != "web" && sscanf(str,"%sweb%s",dummy, dummy) == 0))
        return 0;

    itask = TP->resolve_task(TASK_ROUTINE,({TS_DEX,TS_STR,TS_DIS}));
    damage = MAX(MIN_DAM, (MAX_DAM - itask));

    if(itask > 0 && damage < TP->query_hp())
    {
        write(BSN("In utter despair because you are trapped in the web, " +
            "you start "+vb+"ing at the web.")+
            BSN("Finally, you manage to "+vb+" yourself from the web, but you " +
            "hurt yourself."));
        SAY(" desperately "+vb+"s at the web to free "+TP->query_objective()+
            "self from the sticky thread of the cob-web. Finally, "
            +TP->query_pronoun()+ " succeeds!");
        TP->heal_hp(-damage);
            
        set_alarm(0.0, 0.0, remove_object);
    }
    else
    {
        write(BSN("In utter despair because you are trapped in the web, " +
             "you start "+vb+"ing at the web, but it hurts too much, so you " +
             "stop again."));
        SAY(" desperately "+vb+"s at the web to free "+TP->query_objective()+
            "self from the sticky thread of the cob-web.");
        TP->heal_hp(MIN_DAM);
    }
    return 1;

}
