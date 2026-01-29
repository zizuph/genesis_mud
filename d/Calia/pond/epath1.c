/* This is a room in the elemental area northeast of the
frog pond in Calia. By Bishop, 5.2.99 */

inherit "/std/room";

#include <stdproperties.h>
#include <ss_types.h>
#include <macros.h>
#include <files.h>
#include "pond.h"

public string path_blocked();
public void reset_room();
public void open_path();
public int do_pronounce(string str);

void
reset_room()
{
    if (TO->query_prop(CALIA_I_PATH_BLOCKED) == 0)
    {
        TO->add_prop(CALIA_I_PATH_BLOCKED, 1);
        tell_room(TO, "The path north is suddenly and violently" +
            " overgrown by a mass of bushes and brambles, making it"+
            " impassable!\n",0);
        TO->add_item(({"mass of bushes and brambles", "mass", "bushes",
            "brambles"}), "The mass of bushes and brambles makes it"+
            " impossible to travel further north!\n");
        TO->add_item(({"path", "route"}), "The path comes to a" +
            " complete stop here as it is blocked by a mass of" +
            " brambles and bushes.\n");
        TO->remove_exit("north");
    }  
}

create_room()
{
    set_short("Path through the forest");

    set_long("You are making your way through the forest on a" +
        " narrow path, avoiding the occasional thorny bush" +
        " and stepping over the odd log." +
        " @@path_blocked@@\n");

    add_item(({"forest", "trees"}), "The forest consists of" +
        " maple, oak and sassafras trees. They're not too densely" +
        " packed, allowing sunlight to filter in.\n");
    add_item("sunlight", "The light feels warm on your skin.\n");
    add_item("bush", "Few of the bushes obstruct the path, but you" +
        " have to step out of the way sometimes to avoid getting" +
        " prickled by thorns.\n");
    add_item("log", "The logs you see are from fallen trees.\n");
    add_item(({"path", "route"}), "This path seems unnaturally" +
        " smooth and free of vegetation given the lush" +
        " surroundings. It looks untravelled.\n");

    add_prop(ROOM_I_HIDE, 90);
    add_prop(ROOM_I_INSIDE, 0);

    add_exit(FPATH + "nearp", "southwest", 0, 1);
    add_exit(FPATH + "epath2", "north", 0, 1);

    reset_room();
}

void
enter_inv(object ob, object from)
{
    if (file_name(from) == FPATH + "epath2" &&
        TO->query_prop(CALIA_I_PATH_BLOCKED))
    {
        TP->catch_msg("The mass of brambles parts to let you" + 
            " through.\n");
        tell_room(TO, "The mass of brambles parts" +
            " to let someone through.\n", TP);
        set_alarm(0.1, 0.0, &tell_room(TO, "The brambles almost" +
            " instantly grow back.\n", 0));
    }
    ::enter_inv(ob, from);
}

string
path_blocked()
{
    if (TO->query_prop(CALIA_I_PATH_BLOCKED) == 0)
    {
        return "The path ahead seems unnaturally smooth and free" +
            " of vegetation.";
    }
    else
    {
        return "The path ends abruptly in a mass of bushes and" +
            " brambles.";
    }
}

void
open_path()
{
    if (TO->query_prop(CALIA_I_PATH_BLOCKED))
    {
        tell_room(TO, "The mass of bushes and brambles suddenly" +
            " withdraws into the ground, opening up the path to" +
            " the north.\n", 0);
        TO->add_item(({"path", "route"}), "This path seems" + 
        " unnaturally smooth and free of vegetation given the lush" +
        " surroundings. It looks untravelled.\n");
        TO->remove_item("mass of bushes and brambles");
        TO->remove_item("mass");
        TO->remove_item("bushes");
        TO->remove_item("brambles");
        TO->add_exit(FPATH + "epath2", "north", 0, 1);
        TO->add_prop(CALIA_I_PATH_BLOCKED, 0);
    }
    else
    {
        write("The path is already open!\n");
    }
}

int    
do_pronounce(string str)
{
    object obj;
    object * angeltears;
    
    if (str == "the klifsims incantation" || str == "klifsims" 
        || str == "klifsims incantation")
    {
        if (TO->query_prop(CALIA_I_PATH_BLOCKED))
        {
            if (TP->query_mana() > 49 && 
                TP->query_skill(SS_SPELLCRAFT) > 19)
            {
                angeltears = filter(FILTER_HERB_OBJECTS(all_inventory(TP)),
                        &operator(==)("angeltear") @ &->query_herb_name());
                
                if (sizeof(angeltears))
                {
                    write("You pronounce the Klifsims" +
                        " incantation.\n");
                    tell_room(TO, QCTNAME(TP) + " softly pronounces"+
                    " an incantation.\n", TP);

                    if (!TP->test_bit(GQ_DOMAIN, GQ_GROUP, GQ_BIT) &&
                        TP->query_prop(CALIA_I_TALK_WANDERER))
                    {
                        TP->add_mana(-50);

                        obj = angeltears[0];
                        obj->set_heap_size(obj->num_heap() -1);

                        TP->set_bit(GQ_GROUP, GQ_BIT);
                        TP->add_exp_quest(GQ_XP);
                        TP->command("save");
                        write("You feel a bit more experienced!\n");
                        TP->remove_prop(CALIA_I_TALK_WANDERER);
                        log_file("grotto_entrance_quest", 
                            capitalize(TP->query_real_name()) + 
                            " gets " + GQ_XP + " experience, " + 
                            ctime(time()) + ".\n");
                        open_path();
                        return 1;
                    }
                    else
                    {
                        TP->add_mana(-50);
                        obj = angeltears[0];
                        obj->set_heap_size(obj->num_heap() -1);
                        open_path();
                        return 1;
                    }
                }
                else
                {
                    notify_fail("You lack the ingredients necessary"+
                        " to complete the spell.\n");
                    return 0;
                }
            }
            else
            {
                notify_fail("You don't have the mental strength to" +
                    " complete the spell.\n");
                return 0;
            }
        }
        else
        {
            notify_fail("The path is already open!\n");
            return 0;
        }
    }
    else
    {
        notify_fail("Pronounce what?\n");
        return 0;
    }
}


void
init()
{
    add_action(do_pronounce, "pronounce");
    add_action(do_pronounce, "incant");
    ::init();
}
