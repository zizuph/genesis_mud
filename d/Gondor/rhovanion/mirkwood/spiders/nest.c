#include "../defs.h"
#include <stdproperties.h>
#include <filter_funs.h>
#include <composite.h>

inherit "/std/object";

#include "/d/Genesis/specials/debugger/debugger_tell.h"

int nest_level = 1;
object *children = ({ });
object parent_nest;
mapping spider_spawns = ([ ]);
string *eligible_for_treasure = ({ });

void 
create_object()
{
    set_name(MIRKWOOD_SPIDER_NEST_ID);
    add_name("nest");
    set_no_show_composite(1);
    set_short("spider nest");
    set_long("The thick, gooey strands of spiderwebs are extremely thick " +
        "here, collecting in large lumps which form what appears to be " +
        "one large nest! It seems likely that this is where the spiders " +
        "have taken their prey over the years, but you would have to make " +
        "sure all of the spiders around here are dead before you could " +
        "take a closer look.\n");

    add_prop(OBJ_M_NO_GET, 1);
    add_prop(OBJ_S_SEARCH_FUN, "search_spider_nest");
}

string 
query_mirkwood_long()
{
return environment(this_object())->get_random_message(({

        "The thick, black trees have Mirkwood have been " +
        "absolutely covered in thick, grey spiderwebs! " +
        "You seem to have stumbled into the middle of " +
        "a spider nest, and you realize quite swiftly " +
        "that this is not exactly the safest place to " +
        "be right now, but the spiders do not seem " +
        "interested in letting you leave either. \n",

        "Thick, sticky strands of spiderweb cover absolutely " +
        "everything in sight. From the bushes to the trees " +
        "above your head, you suddenly understand that you " +
        "have been lured in and trapped! Your heart in " +
        "your mouth, you know that there will be no easy " +
        "escape. \n",

        "All around you, across the trees and undergrowth, " +
        "you can see thick clumps of webbing clinging to " +
        "every single branch and bush. The gooey strings " +
        "of spiderweb are even clustered just above your " +
        "head, it seems quite obvious that you have stumbled " +
        "right into the middle of a nest of spiders! \n",

        "The first thing you notice is your right foot sticking " +
        "to the ground, but as you free yourself and pause long " +
        "enough to look around, your heart starts beating " +
        "madly in your chest as you realize you have wandered " +
        "into the middle of a massive spider nest! Everything " +
        "here, from the undergrowth and bushes to the massive " +
        "black trees of Mirkwood have been covered in thick, " +
        "sticky strands of spiderweb! There does not appear " +
        "to be an easy way out from here. \n",

        "The first thing you notice is your right foot sticking " +
        "to the ground, but as you free yourself and pause long " +
        "enough to look around, your heart starts beating " +
        "madly in your chest as you realize you have wandered " +
        "into the middle of a massive spider nest! Everything " +
        "here, from the undergrowth and bushes to the massive " +
        "black trees of Mirkwood have been covered in thick, " +
        "sticky strands of spiderweb! There does not appear " +
        "to be an easy way out from here. \n",
      }));
}

public int 
item_id(string str) 
{   
    if (str == "test") return 1;
    return 0;
}

public string 
item_description(string str)
{
    return "test description from spider.\n";
}

public int
have_all_spiders_been_defeated()
{
    foreach(string name, object *spiders : spider_spawns) {
        if (sizeof(filter(spiders, objectp))) return 0;
    }

    return 1;
}

public string 
search_spider_nest(object searcher, string args)
{
    if (!have_all_spiders_been_defeated())
    {
        return "As you come close to the " + short() + ", you hear "
            + "a hissing sound not to far away. As it seems some "
            + "spiders are still guarding the nest, you decide not "
            + "to continue the search.\n";
    }

    if (member_array(searcher->query_real_name(), eligible_for_treasure) == -1)
        return 0;

    object *treasure = (MIRKWOOD_SPIDER_DIR + "treasure_table")
        ->create_treasure_for_player(searcher, nest_level);
    eligible_for_treasure -= ({ searcher->query_real_name() });

    if (!sizeof(treasure)) 
    {
        if (sizeof(eligible_for_treasure)) 
        {
            tell_room(environment(this_object()), QCTNAME(searcher) + " tears "
                + "through the spider webs.\n", ({ searcher }), searcher);

            return "You tear through the spider webs but uncover "
                + "nothing of value.\n";
        } else {
            tell_room(environment(this_object()), QCTNAME(searcher) + " tears "
                + "through the spider webs, destroying it in the process.\n", 
                ({ searcher }), searcher);

            set_alarm(0.0, 0.0, remove_object);

            return "You tear through the spider webs but uncover "
                + "nothing of value. Little remains of the nest now that "
                + "you are done.\n";
        }
    }

    object *moved = ({ });
    foreach(object ob : treasure) {
        if (!ob->move(searcher)) moved += ({ ob });
    }

    object *not_moved = treasure - moved;

    if(sizeof(eligible_for_treasure))
    {
        tell_room(environment(this_object()), QCTNAME(searcher) + " tears "
            + "through the spider webs" + (sizeof(not_moved) ? " leaving "
            + "something on the ground" : "") + ".\n", ({ searcher }), searcher);

        return "As you tear through the spider webs, you "
            + "uncover " + FO_COMPOSITE_DEAD(moved, searcher) + ".\n" 
            + (sizeof(not_moved) ? "You leave " 
                + FO_COMPOSITE_DEAD(not_moved, searcher) + " on the ground.\n"
                : "");
    } else {
        tell_room(environment(this_object()), QCTNAME(searcher) + " tears "
            + "through the spider webs, destroying it in the process.\n"
            + (sizeof(not_moved) ? "Something remains on the ground.\n" : ""),
            ({ searcher }), searcher);

        set_alarm(0.0, 0.0, remove_object);

        return "As you tear away the remainder of the spider webs, you "
            + "uncover " + FO_COMPOSITE_DEAD(moved, searcher) + ".\n" 
            + (sizeof(not_moved) ? "You leave " 
                + FO_COMPOSITE_DEAD(not_moved, searcher) + " on the ground.\n"
                : "");
    }
}

public void
display_message_for_entering_of_spider(object spider, object target) 
{
    tell_room(environment(this_object()), QCTNAME(spider) + " leaps "
        + "from the trees and lands in front of " + QTNAME(target)
        + ".\n", ({ spider, target }), spider);

    target->catch_tell(spider->query_The_name(target) + " leaps "
        + "from the trees and lands right in front of you!\n");
}

private void
spawn_spiders_for_player(object ob)
{
    if (member_array(ob->query_real_name(), m_indices(spider_spawns)) != -1)
        return;

    object *spiders = (MIRKWOOD_SPIDER_DIR + "coordinator")
        ->create_spiders_for_target(ob, nest_level);
    spider_spawns[ob->query_real_name()] = spiders;

    foreach(object spider: spiders) 
    {
        spider->set_origin_nest(this_object());
        spider->set_home(environment(this_object()));
        spider->set_restrain_path(environment(this_object())
            ->query_movement_base_directory());
        spider->move(environment(this_object()));

        display_message_for_entering_of_spider(spider, ob);
    }
}

/* This function is called by the mirkwood/std/room functions 
   when a player enters a room or changes visibility. */
public void 
notify_player_entered(object ob) 
{
    if (!interactive(ob)) return;
    if (ob->query_wiz_level()) return;

    set_alarm(0.0, 0.0, &spawn_spiders_for_player(ob));
}

public void
report_death(object spider)
{
    foreach(string player : m_indices(spider_spawns)) 
    {
        if (member_array(spider, spider_spawns[player]) != -1)
        {
            spider_spawns[player] -= ({ spider });
            if (sizeof(spider_spawns[player]) == 0)
            {
                eligible_for_treasure += ({ player });

                send_debug_message("mirkwood_spider_treasure", 
                    "Spiders for " + player + " destroyed, allowing "
                    + "treasure.");
            }

            return;
        }
    }
}

void 
enter_env(object to, object from)
{
    if (to->query_prop(ROOM_I_IS)) {
        MIRKWOOD_MASTER->nest_added(this_object());
    }

    ::enter_env(to, from);
}

void 
leave_env(object from, object to)
{
    if (to->query_prop(ROOM_I_IS)) {
        MIRKWOOD_MASTER->nest_removed(this_object());
    }

    ::leave_env(from, to);
}

void 
remove_object() 
{
    if (environment(this_object())->query_prop(ROOM_I_IS)) 
    {
        MIRKWOOD_MASTER->nest_removed(this_object());
    }
    ::remove_object();
}

private object 
find_room(string filename)
{
    if (filename[0] != '/') 
    {
        filename = environment()->query_movement_base_directory() + filename;
    }

    object room = find_object(filename);
    if (objectp(room)) return room;

    catch(filename->teleledningsanka());
    room = find_object(filename);

    return room;
} 

int 
expand()
{
    object *rooms = filter(filter(filter(map(m_values(environment()->query_mirkwood_exits()), 
        find_room), objectp), not @ &present(MIRKWOOD_SPIDER_NEST_ID)), &->query_spider_nest_chance());
    if (!sizeof(rooms)) return 0;

    object target = rooms[random(sizeof(rooms))];
    
    setuid();
    seteuid(getuid());

    object nest = clone_object(MIRKWOOD_SPIDER_DIR + "nest");

    if (objectp(parent_nest)) 
    {
        nest->set_parent_nest(parent_nest);
        parent_nest->add_child(nest);
    } else {
        nest->set_parent_nest(this_object());
        children += ({ nest });    
    }
    
    nest->move(target);
    return 1;
}

int 
grow()
{
    if (environment(this_object())->query_max_spider_nest_size() > nest_level)
    {
        nest_level++;

        send_debug_message("mirkwood_spider_spawn", sprintf("Nest in %O grown to level %d",
            environment(this_object()), nest_level));        
        return 1;
    }

    return 0;
}

int 
expand_or_grow()
{
    if (random(2) && grow()) return 1;
    return expand();
}

/* update_timer() is called by the mirkwood master on all the registered host
   spider nests, and is responsible for growing and expanding it's cluster of
   nests */
void 
update_timer()
{
    string area = MIRKWOOD_MASTER->find_area_for_room(environment(this_object()));
    if (!stringp(area)) return;

    int area_nest_limit = MIRKWOOD_MASTER->query_area_limit(area, SPIDER_LIMIT_NESTS);
    int max_cluster_size = area_nest_limit / 
        max(1, MIRKWOOD_MASTER->query_area_limit(area, SPIDER_LIMIT_HOSTS));

    children = filter(children, objectp);

    int number_of_updates = max(1, (sizeof(children) + 1) / 5);
    object *targets = children + ({ this_object() });

    while(number_of_updates && sizeof(targets)) {
        object target = targets[random(sizeof(targets))];
        targets -= ({ target });

        object *env = FILTER_IS_MORTAL(FILTER_LIVE(all_inventory(environment(target))));
        if (sizeof(env)) continue;

        int can_expand = (sizeof(children) + 1 < max_cluster_size) && 
            (MIRKWOOD_MASTER->query_number_of_nests_in_area(area) < area_nest_limit);

        if ((can_expand && target->expand_or_grow()) || target->grow())
        {
            number_of_updates--;
        }
    }
}

void 
set_parent_nest(object nest)
{
    parent_nest = nest;
}

object 
query_parent_nest()
{
    return parent_nest;
}

int 
query_nest_level()
{
    return nest_level;
}

void add_child(object nest)
{
    children += ({ nest });
}

object *query_children()
{
    return children;
}