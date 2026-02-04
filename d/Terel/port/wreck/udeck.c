inherit "/std/room";

#include <stdproperties.h>
#include <macros.h>
#include <ss_types.h>
#include <wa_types.h>
#include <money.h>
#include <language.h>

#include "/d/Terel/common/terel_defs.h"

#define TP           this_player()
#define TO           this_object()

#define WRECK        "/d/Terel/port/wreck/"
#define BEACH        "/d/Terel/port/beach/"

#define DECK         WRECK + "deck"
#define WATER        WRECK + "water"

public void    reset_udeck();
public void    init_udeck();
public void    create_udeck();
public void    set_vol_limit(int lim);
public int     query_vol_limit();
public object  query_water();
public void    add_monster(string m);
public string *query_monster();

static string *smon;
static object water, *mon;
static int vol_limit=1000;

public void
reset_room()
{
    int i;
    object ob;
    
    if (!sizeof(mon)) {
        for (i=0; i<sizeof(smon); i++) {
            ob = clone_object(smon[i]);
            ob->move_living(0, water);
            if (i==0)
                mon = ({ ob });
            else
                mon += ({ ob });
        }
    } else {
        for (i=0; i<sizeof(smon); i++) {
            if (i >= sizeof(mon)) {
                ob = clone_object(smon[i]);
                ob->move_living(0, water);
                if (i==0)
                    mon = ({ ob });
                else
                    mon += ({ ob });
            } else if (!mon[i]) {
                mon[i] = clone_object(smon[i]);
                mon[i]->move_living(0, water);
            }
        }
    }

    reset_udeck();
}

public void
init()
{
    ::init();
    init_udeck();
}

public void
create_room()
{
    set_short("under deck");
    
    create_udeck();
   
    add_prop(ROOM_I_INSIDE, 1);
    add_prop(ROOM_I_LIGHT,  0);
    add_prop(OBJ_S_SEARCH_FUN, "do_search");
    
    seteuid(getuid());
    water = clone_object(WATER);
    
    if (query_vol_limit() >= 4000)
      MONEY_MAKE_GC(query_vol_limit()/4000)->move(water);

    set_alarm(1.0, -1.0, "reset_room");
}

public void
reset_udeck()
{
}

public void
init_udeck()
{
}

public void
create_udeck()
{
}

public void
set_vol_limit(int lim)
{
    vol_limit = lim;
}

public int
query_vol_limit()
{
    return vol_limit;
}

public object
query_water()
{
    return water;
}

public void
enter_inv(object ob, object from)
{
    int i;
    object *all;
    
    ::enter_inv(ob, from);
    if (!ob) return;
    if (ob->query_npc()) return;
    if (living(ob)) {
        if (random(4)) return;
        all = all_inventory(water);
        if (!sizeof(all)) return;
        i = random(sizeof(all));
        if (!living(all[i])) return;
        set_alarmv(4.0, -1.0, "do_kill", ({all[i], ob}));
        return;
    }
    
    if (ob->query_prop(OBJ_I_VOLUME) > vol_limit) return;
    
    set_alarm(1.0, -1.0, "disappear", ob);
}

public void
disppear(object ob)
{
    tell_room(TO, "The " + ob->short() + " disappears into the water.\n");
    ob->move(water);
}

public string
do_search(object searcher, string str)
{
    int i;
    object *all;
    string s="";
    
    if (str != "water" && str != "here") return "";
    
    all = all_inventory(water);
    
    if (!sizeof(all) || random(2) == 1)
        return "You do not find anything in the water.\n";
        
    i = random(sizeof(all));
    
    if (living(all[i])) {
        s = "You feel " + LANG_ASHORT(all[i]) + "!\n";
        set_alarmv(2.0, -1.0, "do_kill", ({all[i], searcher}));
    } else {
        s = "You find " + LANG_ASHORT(all[i]) + ".\n";
        if (all[i]->move(searcher)) {
            all[i]->move(TO);
        }
    }
    return s;
}

public void
do_kill(object monster, object victim)
{
    if (!monster || !victim) return;
    if (!present(victim)) return;
    monster->move_living(0, TO);
    monster->command("kill " + victim->query_real_name());
}

public void
add_monster(string m)
{
    if (file_size(m + ".c") <= 0) return;
    
    if (!sizeof(smon)) {
        smon = ({ m });
    } else {
        smon += ({ m });
    }
}

public string *
query_monster()
{
    return smon;
}
