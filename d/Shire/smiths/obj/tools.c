// take into account special weapons and armours when checking
// for materials
/*
 *   Forge tools for Smiths Guild.
 *   /d/Shire/smiths/rooms/forge_r
 *   to give players the ability to forge items
 *
 *   Modified and updated 12/96
 *   Glaurung
 *
 *  Removed prepare phase of forging. Glaurung 2/97
 *
 * 01/11/15 Arandir	Placed the forging log in an external object.
 * Jan 6, 2003 - fixed tools so only smiths can forge items except for necklace.
 *
 * Set check in tools so players < 55 can't forge necklaces and join.
 * -- Finwe, July 2004
 *
 */

#pragma save_binary;

inherit "/std/object.c";

#include "/d/Shire/common/defs.h"
#include <stdproperties.h>
#include "/d/Shire/smiths/smiths.h"
#include "/d/Shire/skills.h"
#include <cmdparse.h>
#include <wa_types.h>
#include <formulas.h>
#include <language.h>
#include <ss_types.h>

#define FORGING "_live_o_forge_"

//** Global Variables (Capitilize them!) **/
static int Suc = 0, Dif = 0; // debug purposes
static int Difficulty = 0;
static object *obAr = ({});

//** Prototypes **//
int  forge(string str);
int  cancel(string s);
int  drop(string s);
int  give(string s);
int  material_present(string str, int itemtype);
void remove_forge_alarms();
void remove_forging_material();
void abort_forging(string s);
void forge_messages(int stage, string itemname);
void forge_sounds();
string query_dif();
float query_bellow();


string
query_dif()
{
    return "Success = "+Suc+" Difficulty = "+Dif+"\n";
}

void
create_object()
{
    setuid(); seteuid(getuid());
    set_name("tools");
    add_name("smiths_forging_tools");
    add_name("set");
    set_adj("forging");
    set_adj("set of");
    set_short("set of forging tools");
    set_long("These forge tools are all one needs in order to forge smaller"+
        " items such as weapons and armours. There are several sizes of"+
        " hammers and files and other strange tools. Please remember to leave"+
        " them in this room when you leave. The tools all bear the mark of"+
        " the Blacksmiths Guild.\n");

    add_prop(OBJ_I_VALUE,0);
    add_prop(OBJ_I_WEIGHT,3000);
    add_prop(OBJ_I_VOLUME,1500);
    add_prop(OBJ_M_NO_INS,1);
}

void
init()
{
    ::init();

    add_action(cancel,"stop"); // cancel a forging process
    add_action(forge,"forge");   // forge an item
    add_action(drop,"drop");
    add_action(drop,"put");
    add_action(give,"give");
}

int
drop(string s)
{
    object tools;

    if ((s=="tools" || s=="forging tools"))
    {
        if (objectp(tools = present("smiths_forging_tools",TP)))
        {
            if (TP->query_prop(FORGING))
            {
            remove_forge_alarms();
            write("You ruin what you were forging.\n");
            tell_room(ENV(TP), QCTNAME(TP)+" ruins what "+HE_SHE(TP)+
                " was forging.\n",TP);
//            return 1;
            }
            tools->move(ENV(TP), 1);
            write("You drop the forging tools.\n");
            tell_room(ENV(TP), QCTNAME(TP)+" drops the forging tools.\n",TP);

        }
    return 1;
    }



    return 0;
}

int
give(string s)
{
    if (TP->query_prop(FORGING) && (s=="tools" || s=="forging tools"))
    {
        remove_forge_alarms();
        write("You ruined what you were trying to make when you "+
            "gave the tools away.\n");
        tell_room(ENV(TP), QCTNAME(TP)+" ruins what "+HE_SHE(TP)+
            " was trying to make by giving away the tools.\n",TP);
        return 1;
    }

    return 0;
}

void
remove_forge_alarms()
{
    mixed *alarms = get_all_alarms();
    int    i,
           alarm_id = 0,
           sz = sizeof(alarms);

    for (i = 0; i < sz; i++)
    {
        alarm_id = alarms[i][0];
        remove_alarm(alarm_id);
    }

    if (TP->query_prop(FORGING))
        TP->remove_prop(FORGING);
}

int
cancel(string s)
{
    if (!strlen(s) || s != "forging")
        return 0;

    remove_forge_alarms();
    write("You decide to stop forging your current item.\n");
    say(QCTNAME(TP)+" seems to change "+HIS_HER(TP)+" mind about"+
        " something.\n");
    return 1;
}

void
abort_forging(string itemname)
{
	object  item;
	int amt = 0, mod = 0, itemtype, reward = 0;

    remove_forge_alarms();
    write("You seem to have ruined the item you were working on! "+
        "You probably just need more practice at it.\n");
    say(QCTNAME(TP)+" seems to have ruined what "+HE_SHE(TP)+
        " was working on!\n");

    itemname = query_prop("_s_itemname");

    // give them credit for trying if they have previously forged one successfully

    if (SMITHS_MASTER_OBJ->sm_query_forged_item (TP, itemname))
		SMITHS_MASTER_OBJ->sm_increment_forged_item (TP, itemname);

	itemtype = MANAGER->query_item_type(itemname);

	// You only get benefit for 10 items created
	amt = MIN(SMITHS_MASTER_OBJ->sm_query_forged_item (TP, itemname), 10);

	// The item is a broken created, so we give it a low modifier
	mod = 5;

	switch (itemtype)
	{
		case 1:
			item = MANAGER->create_smith_weapon(itemname, mod);
			break;

		case 2:

			item = MANAGER->create_smith_armour(itemname, mod);
			break;

		default:
			write("Error: index out of bounds while cloning: " + itemname +
			      "\nIndex: " + itemtype + "\n");
			break;
	}

	// Reward the creation of the item with Gen xp
	reward = F_FORGE_FAIL_GENEXP(itof(item->query_value()));
	this_player()->add_exp_general(reward);

	item->add_prop(OBJ_I_BROKEN, 1);
	item->add_prop_obj_i_broken();
	item->remove_broken(); // just to be safe

	if (item->move(TP))
		item->move(ENV(TP));
}

int
forge(string str)
{
    int     i        = 0,
            bonus    = 0,
            success  = 0,
            itemtype = 0;
    mixed  *itemstats = ({});
    string *forgeable_items = ({});
    object  bar;
    object tools;


    FIXEUID

    add_prop("_s_itemname", str);

    // take out wiz level check later
//    if (!IS_MEMBER(TP) && !TP->query_prop(LIVE_I_SMITH_ENTRANCE_QUEST))


    if(!TP->query_prop(LIVE_I_SMITH_ENTRANCE_QUEST) && !IS_MEMBER(TP))
    {
        if (TP->query_wiz_level())
            write("Lucky wiz.\n");
        else
        {
        NF("You lack the skills to for that!\n");
        return 0;
        }
    }
/*
    if (!IS_MEMBER(TP))

    {
        if (TP->query_wiz_level())
            write("Lucky wiz.\n");
        else
        {
        NF("Only a Blacksmith may do that!\n");
        return 0;
        }
    }
*/

//are we holding the forging tools?
    if (!objectp(tools = present("smiths_forging_tools",TP)))
        {
            NF("You need to be holding the tools before you can forge.\n");
            return 0;
        }

        if (TP->query_average_stat() < 55 && !IS_MEMBER(TP))
        {
            NF("You are too young to join the Blacksmiths. " +
            "Try again when you are older.\n");
            return 0;
        }

/*
    if (ENV(TO) == ENV(TP))
    {
        NF("You lack the experience or understanding to do that. Perhaps you need to ask someone about how to do that.\n");
        return 0;
    }
*/

    if (TP->query_prop(FORGING))
    {
        NF("You cannot start forging a new object while forging!\n");
        return 0;
    }

    if (TP->query_fatigue() < (TP->query_max_fatigue() / 2))
    {
        NF("You feel too tired to forge anything right now.\n");
        return 0;
    }

    if (!objectp(find_object(MANAGER)))
        MANAGER->load_object();

    if (str == "necklace")
    {
        TP->add_prop(FORGING, 1);
        if (!objectp(bar = present("iron_smith_bar", TP)))
        {
            NF("You don't have the materials to do that!\n");
            return 0;
        }
        bar->remove_object();
        forge_messages(1, str);
        if (TP->query_stat(SS_DEX) < (random(40)+10))
            set_alarm(itof(random(40)+20), 0.0, &abort_forging(str));
        return 1;
    }

    forgeable_items = MANAGER->query_forgeable_items();
    if ((member_array(str, forgeable_items)) == -1)
    {
        NF("You can forge no such thing.\n");
        return 0;
    }

    TP->add_prop(FORGING, 1);
    bonus = SMITHS_MASTER_OBJ->sm_query_forged_item (TP, str);

    success = (TP->query_skill(SS_FORGING) / 2) + (TP->query_stat(SS_LAYMAN) / 10) +
        random(TP->query_stat(SS_LAYMAN / 5)) + (bonus/2) + random(bonus/2);
    itemtype = MANAGER->query_item_type(str);
    switch (itemtype)
    {
        case 1:
            if (!material_present(str, 1))
            {
                TP->remove_prop(FORGING);
                NF("You do not have the proper materials to forge "+
                    "a "+str+".\n");
                return 0;
            }

            remove_forging_material();
            // We need to know how difficult this weapon is to forge
            itemstats = MANAGER->query_weapon_stats(str);

            /* Are we skilled enough to forge this weapon?
             * If not then abort the forging after some time
             * and work has gone by
             */
            if (success < itemstats[DIF])
                set_alarm(itof(random(90) + 20), 0.0, &abort_forging(str));

            // If leather is involved call leather work message
            if (member_array("smiths_leather",itemstats[MATERIALS]) >-1)
                forge_messages(0, str);

            else
                forge_messages(1, str);

            break;

        case 2:
            if (!material_present(str, 2))
            {
                TP->remove_prop(FORGING);
                NF("You do not have the proper materials to forge "+
                    "a "+str+".\n");
                return 0;
            }


            remove_forging_material();
            itemstats = MANAGER->query_armour_stats(str);
            if (success < itemstats[DIF])
                set_alarm(itof(random(90) + 20), 0.0, abort_forging);

            if (member_array("smiths_leather",itemstats[SA_MATERIALS])==1)
                forge_messages(0, str);

            else
                forge_messages(1, str);

            break;

        default:
            TP->catch_tell("An error has occured, make a bug report.\n");
    }

    return 1;
}

int
material_present(string str, int itemtype)
{
    int    i, sz;
    mixed *wepstats,
          *armstats;
    object ob;


    switch (itemtype)
    {
        case 1:
            // We need to know what materials this weapon requires
            wepstats = MANAGER->query_weapon_stats(str);
            sz = sizeof(wepstats[MATERIALS]);
            for (i = 0; i < sz; i++)
            {
                // See if we have what we need to forge this weapon
                if (!objectp(ob = present(wepstats[MATERIALS][i],TP)))
                {
                    obAr = ({});
                    return 0;
                }

                obAr += ({ ob });
            }

            return 1;

        case 2:
            armstats = MANAGER->query_armour_stats(str);
            sz = sizeof(armstats[SA_MATERIALS]);
            for (i = 0; i < sz; i++)
            {
                if (!objectp(ob = present(armstats[SA_MATERIALS][i],TP)))
                {
                    obAr = ({});
                    return 0;
                }

                obAr += ({ ob });
            }

            return 1;

        default:
            return 0;
    }
}

void
remove_forging_material()
{
    int i;

    for (i=0;i<sizeof(obAr);i++)
        obAr[i]->remove_object();

    obAr = ({});
}

int
query_bellow()
{
    object forge;

    if (!objectp(forge = present("_great_smith_forge",ENV(TP))))
    {
        NF("The Great Forge of theBlacksmiths seems to be missing.\n");
        return 0;
    }


    if (forge->query_prop(OBJ_I_BELLOW_USED))
    {
        TP->set_fatigue(TP->query_fatigue()-(TP->query_max_fatigue()/20));
        return 10+random(10);
    }

    TP->set_fatigue(TP->query_fatigue()-(TP->query_max_fatigue()/10));
    return 15+random(20);
}

void
forge_messages(int stage, string itemname)
{
    int     amt = 0, mod = 0, itemtype, reward = 0;
    mapping forgeInfo = ([]);
    object  item;
	object g = find_player("finwe");

    if (!TP->query_prop(FORGING))
    {
        write("Contact a Shire wizard, something is wrong.\n");
        return;
    }

    forge_sounds();
    switch (stage)
    {
        case 0:
            TP->catch_tell("You start doing the leatherwork "+
                "for the "+itemname+".\n");
            tell_room(ENV(TP),QCTNAME(TP)+" starts doing the "+
                "leatherwork for the "+itemname+".\n", TP);
            set_alarm(itof(query_bellow()),0.0,&forge_messages(++stage,itemname));
            break;

        case 1:
            TP->catch_tell("You heat the metal in the "+
                "forge until it is red-hot.\n");
            tell_room(ENV(TP),QCTNAME(TP)+" heats the metal "+
                "in the forge until it is red-hot.\n", TP);
            set_alarm(itof(query_bellow()),0.0,&forge_messages(++stage,itemname));
            break;

        case 2:
            TP->catch_tell("You start hammering on the "+
                "red-hot metal.\n");
            tell_room(ENV(TP),QCTNAME(TP)+" starts hammering "+
                "on the red-hot metal.\n", TP);
            set_alarm(itof(query_bellow()),0.0,&forge_messages(++stage,itemname));
            break;

        case 3:
            TP->catch_tell("The "+itemname+" you are working on "+
                "begins to take shape.\n");
            tell_room(ENV(TP),"The "+itemname+" "+QTNAME(TP)+" is "+
                "working on begins to take shape.\n", TP);
            set_alarm(itof(query_bellow()),0.0,&forge_messages(++stage,itemname));
            break;

        case 4:
            TP->catch_tell("You give the "+itemname+" a final finish.\n");
            tell_room(ENV(TP),QCTNAME(TP)+" gives the "+itemname+" "+
                HE_SHE(TP)+" is working on a final finish.\n", TP);
            set_alarm(itof(query_bellow()),0.0,&forge_messages(++stage,itemname));
            break;

        case 5:
            if (itemname == "necklace")
            {
                item = clone_object("/d/Shire/smiths/obj/apr_neck");
                item->set_forger(TP->query_name());
                item->move(TP,1);
                TP->catch_tell("You have finished forging a necklace.\n");
                tell_room(ENV(TP), QCTNAME(TP)+" finishes forging a "+
                    "necklace.\n", TP);
                stage = 0;
                remove_forge_alarms();
                return;
            }


            SMITHS_MASTER_OBJ->sm_increment_forged_item (TP, itemname);
            itemtype = MANAGER->query_item_type(itemname);
            amt = SMITHS_MASTER_OBJ->sm_query_forged_item (TP, itemname);
            mod = MIN((amt/30) + TP->query_stat(SS_LAYMAN)/30, 20);
            switch (itemtype)
            {
                case 1:
                    item = MANAGER->create_smith_weapon(itemname, mod);
                    break;

                case 2:

                    item = MANAGER->create_smith_armour(itemname, mod);
                    break;

                default:
                    write("Error: index out of bounds while cloning.\n");
                    break;
            }

            // Reward the creation of the item with Gen xp

			reward = F_FORGE_GENEXP(itof(item->query_value()));
			this_player()->add_exp_general(reward);

            if (item->move(TP))
                item->move(ENV(TP));

            TP->catch_tell("You have finished forging the "+
                itemname+".\n");
            tell_room(ENV(TP),QCTNAME(TP)+" has finished "+
                "forging the "+itemname+".\n", TP);

//write ("DEBUG: You have forged this item " + SMITHS_MASTER_OBJ->sm_query_forged_item (TP, itemname) + " times.\n");
//write ("DEBUG: You have forged in all " + SMITHS_MASTER_OBJ->sm_query_forged_total (TP) + " times.\n");

//write ("\nYou have forged this item "+ SMITHS_MASTER_OBJ->sm_query_forged_item (TP, itemname) + " times successfully.\n");
//write ("You have forged a total of " + SMITHS_MASTER_OBJ->sm_query_forged_total (TP) + " items.\n\n");


            stage = 0; // reset stage flag
            remove_forge_alarms(); // make sure we dont leave any alarms
            break;

        default:
            write("Contact a Shire wizard, stage limit out of bounds.\n");
            break;
    }
}

void
forge_sounds()
{
    int     x;
    object  room,bree_room;
    string *exits;
    string hammer_msg = "You hear faint hammering sounds from the forge nearby.\n";
//    string bree_room;

    exits = ENV(TP)->query_exit();
    for (x = 0; x < (sizeof(exits)/3); x += 3)
    {
        room = find_object(exits[x]);
        if (objectp(room))
            tell_room(room,hammer_msg);
    }
    bree_room = find_object(BREE_DIR + "smith_temp");
    if (objectp(bree_room))
        tell_room(bree_room,hammer_msg);
    bree_room = find_object(BREE_DIR + "entrance");
    if (objectp(bree_room))
        tell_room(bree_room,hammer_msg);
    bree_room = find_object(BREE_DIR + "ncross");
    if (objectp(bree_room))
        tell_room(bree_room,hammer_msg);
    bree_room = find_object(BREE_DIR + "middle");
    if (objectp(bree_room))
        tell_room(bree_room,hammer_msg);
    bree_room = find_object(BREE_DIR + "crossing");
    if (objectp(bree_room))
        tell_room(bree_room,hammer_msg);
    bree_room = find_object(BREE_DIR + "townr1");
    if (objectp(bree_room))
        tell_room(bree_room,hammer_msg);


}
