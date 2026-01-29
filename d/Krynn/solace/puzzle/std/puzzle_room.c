/* The inheritable file for indoor rooms. ~puzzle/std/puzzle_room */

inherit "/std/room";

#include "../defs.h"
#include "/secure/std.h"
#include "/sys/macros.h"
#include "/sys/language.h"
#include "/config/sys/local.h"
#include "/sys/stdproperties.h"
#include "../../../mucalytic/sys/language.h"

int found, except;
string *item, verb1, prep, verb2, filename;

void create_puzzle_room() { }

mixed add_search(string *a, string b, string c, string d, string e);

void clear_room()
{
    int i;
    object *contents = I(TO);

    found = 0;

    for(i = 0; i < sizeof(contents); i++)
    {
        if(!stringp(contents[i]->query_door_id()) && !LIVING(contents[i]))
        {
            tell_room(TO, C(LANG_THESHORT(contents[i]))+" disintegrates!\n");

            contents[i]->remove_object();
        }
    }
}

void create_room()
{
    set_short("A room in the puzzle quest area");
    set_long("You see an unconfigured room in the puzzle quest area here.\n");

    add_prop(ROOM_I_INSIDE, 1);
    add_prop(ROOM_I_TYPE, ROOM_NORMAL);
    add_prop(ROOM_I_LIGHT, 50 + random(50));
    add_prop(OBJ_S_SEARCH_FUN, "search_obj");

    create_puzzle_room();
}

void let_them_enter(object obj, object from)
{
    ::enter_inv(obj, from);
}

void let_them_leave(object obj, object to)
{
    ::leave_inv(obj, to);
}

void enter_inv(object obj, object from)
{
    object hands;

    if(MASTER_OB(TO) == LOCATIONS + "entrance")
    {
        if(objectp(hands = present("hands", obj))) hands->move(TO);
        let_them_enter(obj, from);
    }
    else if(LIVING(obj))
    {
        if(MASTER_OB(from) == OWN_STATUE)
        {
            except = 1;
            obj->move(LOCATIONS + "entrance");
        }

        else if(member_array(query_verb(), EXIT_CMDS) == -1)
        {
            if(!except)
            {
                write("\nYou find that as you try to enter the puzzle "+
                    "area, a field of power deforms your spacial energies "+
                    "and forces you to return to your previous location.\n\n");

                except = 1;
                obj->move(from);
            }
            else
                let_them_enter(obj, from);

            except = 0;
        }
        else
        {
            if((MASTER_OB(TO) == LOCATIONS + "gilean") &&
              !(obj->query_prop(PLAYER_I_COMPLETED_PUZZLE_QUEST)))
                obj->add_prop(PLAYER_I_COMPLETED_PUZZLE_QUEST, 1);

            let_them_enter(obj, from);
        }
    }
    else
        let_them_enter(obj, from);
}

void leave_inv(object obj, object to)
{
    object c, t, domain = SECURITY->query_wiz_dom(geteuid(TO));

    if(MASTER_OB(TO) == LOCATIONS + "entrance")
        let_them_leave(obj, to);

    else if(LIVING(obj))
    {
        if(MASTER_OB(TO) == LOCATIONS + "morgoin")
        {
            if(c = obj->query_prop("_live_i_sit"))
            {
                t = TP;
                set_this_player(obj);
                c->stand_up("");
                set_this_player(t);
            }
        }

        if(!objectp(to) || obj->query_ghost() || !query_ip_number(obj))
        {
            if(obj->query_prop(PLAYER_I_COMPLETED_PUZZLE_QUEST))
                obj->remove_prop(PLAYER_I_COMPLETED_PUZZLE_QUEST);

            find_object(LOCATIONS + "entrance")->set_occupied(0);
            let_them_leave(obj, to);
        }
        else if(member_array(query_verb(), EXIT_CMDS) == -1)
        {
            if(!except)
            {
                write("\nYou find that as you try to leave the puzzle "+
                    "area, a field of power deforms your spacial energies "+
                    "and forces you to stay at your current location.\n\n");

                except = 1;
                obj->move(TO);
            }
            else
                let_them_leave(obj, to);

            except = 0;
        }
        else
            let_them_leave(obj, to);
    }
    else
        let_them_leave(obj, to);
}

mixed add_search(string *a, string b, string c, string d, string e)
{
    if(pointerp(a))
    {
        if(!sizeof(a))
            return("No items to search for.\n");
        else
            item = a;
    }
    else
        item = ({ a });

    if(!strlen(b))
        return("First verb not given.\n");
    else
        verb1 = b;

    if(strlen(c))
        prep = c;

    if(!strlen(d))
        return("Second verb not given.\n");
    else
        verb2 = d;

    if(!strlen(e))
        return("No filename for search object given.\n");
    else
        filename = e;

    return 1;
}

mixed search_obj(object player, string str)
{
    object obj;

    if(!strlen(str))
    {
        notify_fail("Search what?\n");
        return 0;
    }

    if(found)
        return 0;

    if(member_array(str, item) == -1)
        return 0;

    found = 1;

    seteuid(getuid(TO));
    obj = clone_object(filename);

    obj->move(TO);

    tell_room(TO, QCTNAME(player)+" "+LANG_TVERB(verb1)+
        (strlen(prep) ? (" " + prep) : "")+" the "+item[0]+" and "+
        LANG_TVERB(verb2)+" "+LANG_ASHORT(obj)+"!\n", player);

    return "You "+verb1+(strlen(prep) ? (" "+prep) : "")+" the "+item[0]+" "+
        "and "+verb2+" "+LANG_ASHORT(obj)+"!\n";
}
