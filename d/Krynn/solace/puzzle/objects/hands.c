/* Hands - limit your ability to carry objects and holds pre-puzzle objects.
 *
 * ~solace/puzzle/objects/hands
 */

inherit "/std/container";

#include "../defs.h"
#include "/sys/macros.h"
#include "/sys/language.h"
#include "/sys/cmdparse.h"
#include "/sys/wa_types.h"
#include "/sys/composite.h"
#include "/sys/stdproperties.h"
#include "../../../mucalytic/sys/language.h"

void create_container()
{
    set_name("hands");
    set_adj("pair of");
    add_adj("controlling");
    set_long("The hands only allow the holder to carry one item at a time.\n");

    set_no_show();

    add_prop(OBJ_M_NO_DROP,1);

    add_prop(OBJ_I_VOLUME,      0);
    add_prop(OBJ_I_WEIGHT,      0);

    change_prop(CONT_I_CLOSED,  0);             /* Open the damn thing */

    add_prop(CONT_I_TRANSP,     0);
    add_prop(CONT_I_VOLUME,     0);
    add_prop(CONT_I_WEIGHT,     0);
    add_prop(CONT_I_MAX_VOLUME, 10000);
    add_prop(CONT_I_MAX_WEIGHT, 10000);
}

void init()
{
    ::init();

    add_action("get", "get");
    add_action("get", "take");
    add_action("get", "pick");
}

/* Stop weight additions and subtractions to/from this object. */

void enter_inv(object obj, object old) { }
void leave_inv(object obj, object new) { }

void enter_env(object new, object old)
{
    int i;
    object *obj;

    if(LIVING(new))
    { 
        obj = filter(I(new), "not_wanted", TO);

        for(i = 0; i < sizeof(obj); i++)
        {
            obj[i]->move(TO, 1);	/* Move objs to inv of TO */
            obj[i]->move(TO, 0);	/* Move to default subloc */
        }
    }

    ::enter_env(new, old);

    change_prop(CONT_I_CLOSED, 1);
}

void leave_env(object old, object new)
{
    int i;
    object *obj;

    change_prop(CONT_I_CLOSED, 0);

    if(LIVING(old))
    {
        obj = filter(I(old), "not_wanted", TO);

        for(i = 0; i < sizeof(obj); i++)
            obj[i]->remove_object();		/* Remove quest objects. */

        obj = I(TO);

        for(i = 0; i < sizeof(obj); i++)
        {
            obj[i]->move(old, 1);	/* Replace old objs */
            obj[i]->move(old, 0);	/* Move to default */
        }

        set_alarm(1.0, 0.0, "remove_object");
    }

    ::leave_env(old, new);
}

int manip_drop_get(object player, object obj, string verb, string action)
{
    int result, i, silent = 0;
    string reason = "", tmp = "";
    object *rem, *inv = filter(I(player), "not_wanted_or_worn_on_hands", TO);

    if(verb == "pick")
        verb = "pick up";

    if(strlen(action))
        tmp = " " + action;

    if(result = obj->move(player))
    {
        switch(result)
        {
            case 1:
                reason = " It is too heavy for you to carry."; break;
            case 3:
                reason = " It can't be taken from there."; break;
            case 8:
                reason = " It's too big for you to carry."; break;
        }
    }

    if(MASTER_OB(E(obj)) == OBJECTS + "window")
        if(E(obj)->query_broken())
            if(!sizeof(filter(I(player), "is_worn_on_hands", TO)))
                silent = 1;

    if(result)
    {
        if(!silent)
        {
            player->catch_msg("You cannot "+verb+" "+LANG_THESHORT(obj)+
                "."+reason+"\n");
        }
    }
    else
    {
        if(!sizeof(inv))
        {
            player->catch_msg("You "+verb+" "+LANG_THESHORT(obj)+tmp+".\n");

            tell_room(E(player), QCTNAME(player)+" "+LANG_TVERB(verb)+" "+
                LANG_THESHORT(obj)+tmp+".\n", player);
        }
        else
        {
            for(i = 0; i < sizeof(inv); i++)
                inv[i]->move(E(player));

            player->catch_msg("You drop "+COMPOSITE_DEAD(inv)+" and "+verb+
                " "+LANG_THESHORT(obj)+tmp+".\n");

            tell_room(E(player), QCTNAME(player)+" drops "+COMPOSITE_DEAD(inv)+
                " and "+LANG_TVERB(verb)+" "+LANG_THESHORT(obj)+tmp+".\n",
                player);
        }
    }

    return result;
}

int get(string str)
{
    int i;
    object *inv, *obj, cont, player = E(TO);
    string what, parse_str = "%s 'in' / 'inside' / 'from' %o";

    if(!strlen(str))
    {
        notify_fail(C(query_verb())+" what?\n");
        return 0;
    }

    if(!CAN_SEE_IN_ROOM(player))
    {
        notify_fail("You are unable to see well enough to do that.\n");
        return 0;
    }

    cont = E(TP);

    if(parse_command(str, E(player), parse_str, what, cont))
        str = what;

    if(str == "all")
    {
        write("Please specify one item to get.\n");
        return 1;
    }

    obj = FIND_STR_IN_OBJECT(str, cont);

    if(!sizeof(obj))
    {
        write("There doesn't seem to be "+LANG_ADDART(str)+" here.\n");
        return 1;
    }

    if(sizeof(obj) > 1)
    {
        write("Please choose one object to "+query_verb()+" only.\n");
        return 1;
    }

    manip_drop_get(player, obj[0], query_verb(), "");
    return 1;
}

int not_wanted(object obj)
{
    if((obj == TO) || (MASTER_OB(obj) == OBJECTS + "bag_holding")) return 0;
    else if(function_exists("create_object", obj) == "/std/container") return 1;
    else
        return(!obj->query_no_show() & !obj->query_prop(OBJ_M_NO_DROP));
}

int is_worn_on_hands(object obj)
{
    return((E(TO)->query_armour(A_R_HAND) == obj |
            E(TO)->query_armour(A_L_HAND) == obj) & obj->query_worn() == E(TO));
}

int not_wanted_or_worn_on_hands(object obj)
{
    return(not_wanted(obj) & !is_worn_on_hands(obj));
}
