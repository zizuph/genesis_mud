/* created by Arman May 2021
 * 
 * This is a container that can be attached to a boat
 * and can hold bait.
 *
 */
inherit "/std/receptacle";
inherit "/lib/keep";

#include <macros.h>
#include <stdproperties.h>
#include <composite.h>
#include <language.h>
#include <cmdparse.h>
#include <state_desc.h>
#include <wa_types.h>
#include "/d/Krynn/common/defs.h"

string owner;

string 
query_auto_load() 
{
    return MASTER_OB(TO);
}

void
set_box_owner(string str)
{
    owner = str;
}

string
query_box_owner()
{
    return owner;
}

public void
create_receptacle()
{
    set_keep();
    set_name("box");
    add_name("_gnomish_bait_box");
    set_adj("bait");
    add_adj("gnomish");

    set_short("gnomish bait box");
    set_long("A large gnomish-designed box for the fresh " +
        "storage of fishing bait. An interesting thumb-print " +
        "contraption seems to be in place of a traditional " +
        "lock, that the owner of the box can press to lock or " +
        "unlock.\n");
    set_pick(85);

    add_prop(CONT_I_WEIGHT, 50000);
    add_prop(CONT_I_MAX_WEIGHT, 500000);
    add_prop(CONT_I_MAX_VOLUME, 500000);
    add_prop(CONT_I_RIGID, 1);
    add_prop(CONT_I_CLOSED, 0);
    add_prop(CONT_I_TRANSP, 0);
    add_prop(CONT_I_LIGHT, 0);
    add_prop(OBJ_I_VALUE, 200);
    add_prop(CONT_I_HOLDS_COMPONENTS, 1);
    add_prop(CONT_I_CLOSED, 1);
    add_prop(CONT_I_LOCK, 1);
    add_prop(OBJ_M_NO_GET, "The gnomish bait box is bolted to the " +
        "deck of the ship and cannot be removed.\n");

    set_key(7111999);  // There is no key for this box
    set_pick(85);

    add_cmd_item(({ "contraption", "lock", "thumb print",
        "thumb-print","thumb-print contraption"}),
        "press","@@unlock_box");


    setuid();
    seteuid(getuid());
}

string
unlock_box()
{
    if(query_box_owner() != TP->query_real_name())
    {
        say(QCTNAME(TP)+ " presses " +HIS(TP)+ " thumb " +
            "on the " +TO->short()+ ". Nothing happens.\n");
        return "You press your thumb against the " +TO->short()+ ". " +
            "Nothing happens.\n";
    }

    if(!TO->query_prop(CONT_I_LOCK))
    {
        say(QCTNAME(TP)+ " presses " +HIS(TP)+ " thumb " +
            "on the " +TO->short()+ ". A whistle blows loudly " +
            "and it rattles alarmingly, before slamming closed " +
            "and locking.\n");
        write("You press your thumb against the " +TO->short()+ ". " +
            "A whistle blows loudly and it rattles alarmingly, before " +
            "slamming closed and locking.\n");
        TO->add_prop(CONT_I_CLOSED, 1);
        TO->add_prop(CONT_I_LOCK, 1);
        return "";
    }


    say(QCTNAME(TP)+ " presses " +HIS(TP)+ " thumb " +
        "on the " +TO->short()+ ". A whistle blows loudly " +
        "and it rattles alarmingly, before its lock clicks " +
        "and the box pops open.\n");
    write("You press your thumb against the " +TO->short()+ ". " +
        "A whistle blows loudly and it rattles alarmingly, before " +
        "its lock clicks and the box pops open.\n");
    TO->add_prop(CONT_I_CLOSED, 0);
    TO->add_prop(CONT_I_LOCK, 0);
    return "";
    
}

public string
query_recover()
{
    return MASTER + ":" + query_container_recover();
}

public void
init_recover(string arg)
{
    init_container_recover(arg);
}

public int
prevent_enter(object ob)
{
    if(!ob->id("_fishing_bait"))
    {
        write("The box is for fishing bait only.\n");
        return 1;
    }
    return 0;
}

public string
query_bait_quality_description(object ob)
{
    string str;
    int val = ob->query_bait_value();

    switch(val)
    {
        case 0:
            str = "very poor";
        break;
        case 1..5:
            str = "basic";
        break;
        case 6..10:
            str = "good";
        break;
        case 11..19:
            str = "excellent";
        case 20:
            str = "fantastic";
        break;
        default:
            str = "unknown";
        break;
    }

    return str;
}

void 
describe_contents(object fo, object *obarr)
{
    if (sizeof(obarr) == 0)
    {
        fo->catch_tell("  " + "The " + this_object()->short() +
            " is empty.\n");
        return;
    }

    if (sizeof(obarr) > 0)
    {
        fo->catch_tell("\n");
        fo->catch_tell(
            "                    Bait                                    Quality       Qty  \n" +
            "+-----------------------------------------------------+-----------------+-----+\n");
        foreach(object bait : obarr) 
        {
            int quantity = 0;
            string quality = query_bait_quality_description(bait);
            quantity += bait->num_heap() || 1;
            string bait_name = bait->query_short();
            fo->catch_tell(sprintf("| %-:51s | %-:15s | %3d |\n",
                bait_name, quality, quantity));
        }
        fo->catch_tell(
            "+-----------------------------------------------------+-----------------+-----+\n");
    }
}
