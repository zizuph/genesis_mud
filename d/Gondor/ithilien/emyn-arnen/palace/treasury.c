inherit "/d/Gondor/common/room";

#include <language.h>
#include <macros.h>
#include <stdproperties.h>

#include "/d/Gondor/defs.h"
#include "/d/Gondor/ithilien/emyn-arnen/arnen_defs.h"
#include "/d/Gondor/morgul/quest/bsw/bsw_defs.h"

#define SAVE	"/d/Gondor/ithilien/emyn-arnen/palace/treasury"
#define MAX_ENTER  4

varargs public mixed query_enter(string name);

static int     door_alarm = 0;
static object  gate,
               bstand;
string *enter = ({ });

void
create_room()
{
    set_short("the treasury of the House of Hurin");
    set_long(BSN("This is a large vaulted cellar in the House of the "
      + "Stewards in Emyn Arnen. Against the back wall stands a large "
      + "shelf. In the center of the room is a large block of stone "
      + "hewn from black rock serving as a table."));

    CELLAR_WALLS
    CELLAR_ROOF
    CELLAR_STONES
    CELLAR_FLOOR

    add_prop(ROOM_I_INSIDE, 1);
    add_prop(ROOM_I_LIGHT,  0);
    add_prop(ROOM_M_NO_TELEPORT, 
        "You don't seem to be able to focus on that location.\n");

    FIX_EUID
    restore_object(SAVE);
    gate = clone_object(ITH_DIR + "emyn-arnen/obj/trin_door");
    gate->move(TO);
    clone_object(ITH_DIR + "emyn-arnen/obj/trea_shelf")->move(TO);
    clone_object(ITH_DIR + "emyn-arnen/obj/trea_table")->move(TO);
}

void
enter_inv(object ob, object from)
{
    int     n_enter;
    object  scroll,
            table;
    string  log_msg,
            name;

    ::enter_inv(ob, from);

    if (!objectp(ob) || !objectp(from))
        return;

    if (!living(ob))
        return;

    enter += ({ name = ob->query_real_name() });
    n_enter = query_enter(name);
    log_msg = CAP(name) + " enters the treasury for the "+LANG_WORD(n_enter)
      + " time (" + ctime(time()) + ").";
    save_object(SAVE);

    if ( (ob->query_prop(BSW_I_OPENED_GATE)) && 
         (!ob->query_prop(BSW_I_FOUND_IT)))
    {
        if (objectp(scroll = present(BSW_YRCHOR_SCROLL, ob)))
            scroll->set_no_auto_load();

        // The first time, clone everything!
        if (n_enter == 1)
        {
            present("shelf", TO)->reset_container();
            log_msg += " Loot added!";
        }
        else if (objectp(table = present("shelf")))
        {
            all_inventory(table)->remove_object();
            log_msg += " Loot removed!";
        }

        // Give the player more than one chance to solve the quest!
        if (n_enter <= (MAX_ENTER + random(MAX_ENTER)))
        {
            table = present("table");
            if (!objectp(bstand))
                if (!objectp(bstand = present(BSW_BATTLE_STANDARD, TO)))
                    if (!objectp(bstand = present(BSW_BATTLE_STANDARD, table)))
                        bstand = clone_object(BSW_BATTLE_STANDARD_FILE);
            bstand->add_prop(BSW_S_RETRIEVED_BY, ob->query_real_name());
            ob->remove_prop(BSW_I_OPENED_GATE);
            ob->remove_prop(BSW_I_SENT_TO_YRCHOR);
            ob->add_prop(BSW_I_FOUND_IT, 1);
            bstand->move(table, 1);

            log_msg += " Standard added!";
        }
        else
        {
            if (objectp(bstand))
                bstand->remove_object();
            else if (objectp(bstand = present(BSW_BATTLE_STANDARD, TO)))
                bstand->remove_object();
            else if (objectp(table = present("table", TO)))
                if (objectp(bstand = present(BSW_BATTLE_STANDARD, table)))
                   bstand->remove_object();

            log_msg += " Standard removed!";
        }
    }
    log_file("treasury", log_msg + "\n");

}

void
leave_inv(object ob, object to)
{
    ::leave_inv(ob, to);

    if (!objectp(ob) || !objectp(to))
        return;

    if (living(ob) && !door_alarm)
        door_alarm = set_alarm(2.0, 0.0, "close_door");

    return;
}

void
close_door()
{
    door_alarm = 0;
    if (!gate->query_open())
        return;

    gate->do_close_door("The gate closes.\n");
    gate->query_other_door()->do_close_door("The gate closes.\n");
}

varargs public mixed
query_enter(string name)
{
    int     i,
            c,
            s;

    if (!strlen(name))
        return enter;

    if (member_array(name, enter) == -1)
        return 0;

    for (i = 0, c = 0, s = sizeof(enter); i < s; i++)
        if (enter[i] == name)
            c++;

    return c;
}

public int
remove_enter(string name)
{
    if (member_array(name, enter) == -1)
        return 0;

    enter -= ({ name });
    save_object(SAVE);

    log_file("treasury", CAP(name) + " has solved the quest. "
      + (TI->query_wiz_level() ? TI->query_name() :
        previous_object()->query_name()) + " ("
      + ctime(time()) + ").\n");
    return 1;
}


