/*
 *  /d/Genesis/imbuement/imbueroom.c
 *
 *  For looking at the big list
 *
 *  2010/11/13 Lavellan
 */

#pragma strict_types

inherit "/std/room";

#include <macros.h>
#include <std.h>
#include <wa_types.h>
#include "imbuement.h"
//#include "/d/Genesis/specials/debugger/debugger_tell.h"

/* Global Variables */
mapping             imbuements;

/* Prototypes */
public void             create_room();
public int              check_access();
public string           info();
public void             init();
public int              mod(string arg);
public int              list(string arg);
public int              filt(int type, int val, int id);
public int              details(int arg);
public int              go(string arg);
public int              imbue(string arg);

/*
 * Function name: create_room
 * Description:   Set up room basics
 */
public void
create_room()
{
    set_short("The Imbuement List Room");
    set_long(info);
    add_prop(ROOM_I_INSIDE, 1);
    add_prop(ROOM_I_LIGHT, 10);
    add_prop(ROOM_M_NO_SCRY, 1);
} /* create_room */


/*
 * Function name: check_access
 * Description:   Check if current player has access
 */
public int
check_access()
{
    if (SECURITY->query_wiz_rank(this_player()->query_real_name()) >
        WIZ_NORMAL)
        return 1;
    else
        return 0;
} /* check_access */


/*
 * Function name: info
 * Description:   get text for long
 */
public string
info()
{
    if (check_access())
    {
        return "The Imbuement List Room.\n" +
            "Here you can inspect in various ways the list of imbued" +
            " objects.\n" +
            "To view the list: <mod>\n" +
            "To view details for a particular item: <mod [ID]>\n" +
            "To go to a particular item: <go [ID]>\n" +
            "\n" +
            "To filter the list, add:\n" +
            "axe|club|sword|polearm|knife - weapon type\n" +
            "weapon|armour                - object type\n" +
            "num1|num2|num3               - # of mods\n" +
            "lev1|lev2|lev3               - mod power levels\n" +
            "players|npcs|rooms|racks     - mods in these places\n" +
            "playername                   - carried by this player\n" +
            "\n";
    }
    else
        return "The Imbuement List Room.\nHmmmmmmm....\n";
} /* info */


/*
 * Function name: init
 * Description:   add actions to player
 */
public void
init()
{
    if (check_access())
    {
        add_action(mod, "mod");
        add_action(go, "go");
        add_action(imbue, "imbue");
    }
} /* init */


/*
 * Function name: mod
 * Description:   parse mod command
 */
public int
mod(string arg)
{
    if (atoi(arg))
        return details(atoi(arg));
    else
        return list(arg);
} /* mod */



/*
 * Function name: list
 * Description:   list imbued items
 */
public int
list(string arg)
{
    string out;
//    string env = "";
    object ob, env;
    string ty, hit, pen, ac, loc, z = "";
    string *list;
    int num, x, f;
    mixed *rec;
    imbuements = IMBUE_MASTER->get_imbuements();
    list = m_indices(imbuements);
    if (!wildmatch("* all *", " " + arg + " "))
        list = filter(list, &filt(6,0,));
    if (arg)
        foreach (string arg1: explode(arg, " "))
        {
            x = member_array(arg1, W_NAMES);
            f = 0;
            if (x >= 0)
            {
                list = filter(list, &filt(1,x,));
                f = 1;
            }
            if (arg1 == "weapon" || arg1 == "wep")
            {
                list = filter(list, &filt(2,0,));
                f = 1;
            }
            if (arg1 == "armour" || arg1 == "arm")
            {
                list = filter(list, &filt(2,1,));
                f = 1;
            }
            x = member_array(arg1, ({"players", "npcs", "rooms", "racks"}));
            if (++x)
            {
                list = filter(list, &filt(3,x,));
                f = 1;
            }
            x = member_array(arg1, ({"lev1", "lev2", "lev3"}));
            if (++x)
            {
                list = filter(list, &filt(4,x,));
                f = 1;
            }
            x = member_array(arg1, ({"num1", "num2", "num3"}));
            if (++x)
            {
                list = filter(list, &filt(5,x,));
                f = 1;
            }
            ob = find_living(lower_case(arg1));
            if (ob)
            {
                x = member_array(ob, users());
                if (x >= 0)
                {
                    list = filter(list, &filt(7,x,));
                    f = 1;
                }
            }
            if (arg1 == "all")
                f = 1;
            if (!f)
                write("\nUnknown parameter \"" + arg1 + "\"!\n\n");
        }
    list = sort_array(list);
    out = "Ref. # | Object Type         |hit|pen|ac| Mod Type(s)         |Lv|Location\n" +
          "==============================================================================\n";
//         142523 | Armour(helmet)      |   |   |35| 3 | resist_electricity | 1    
//    foreach (int id, mixed *rec: imbuements)
    foreach (int id: list)
    {
        rec = imbuements[id];
        ty = "";
        hit = "";
        pen = "";
        ac = "";
        loc = "";
        
        ob = rec[COL_OBJ];
        if (ob)
            {
                ty = "???";
                if (ob->check_weapon())
                {
                    hit = ob->query_hit() + "";
                    pen = ob->query_pen() + "";
                    x = ob->query_wt();
                    ty = x <= 6 ? capitalize(W_NAMES[x][..6]) : "???";
                    ty += ob->query_hands() == W_BOTH ? " - 2H" : " - 1H";
                    ty = "Weapon(" + ty + ")";
                }
                if (ob->check_armour())
                {
                    ac = ob->query_ac() + "";
                    x = ob->query_at();
                    ty = "??";
                    if (x == A_SHIELD)
                        ty = "Shield";
                    else if (x & A_ROBE)
                        ty = (x == A_ROBE ? "Cloak" : "Cloak+");
                    else if (x & A_BODY)
                        ty = (x == A_BODY ? "Body" : "Body+");
                    else if (x & A_HEAD)
                        ty = (x == A_HEAD ? "Head" : "Head+");
                    else if (x & A_ARMS)
                        ty = (x == A_ARMS ? "Arms" : "Arms+");
                    else if (x & A_LEGS)
                        ty = (x == A_LEGS ? "Legs" : "Legs+");
                    else if (x & A_FEET)
                        ty = (x == A_FEET ? "Feet" : "Feet+");
                    else if (x & A_WAIST)
                        ty = (x == A_WAIST ? "Waist" : "Waist+");
                    else if (x & A_HANDS)
                        ty = (x == A_HANDS ? "Hands" : "Hands+");
                    ty = "Armour(" + ty + ")";
                }
                env = environment(ob);
                if (!env)
                    loc = "void";
                else if (function_exists("add_rack_entry", env))
                    loc = "rack";
                else if (IS_MOBILE_OBJECT(env))
                    loc = "npc";
                else if (IS_ROOM_OBJECT(env))
                    loc = "room";
                else if (IS_PLAYER_OBJECT(env))
                    loc = upper_case(env->query_real_name());
                else if (environment(env))
                {
                    env = environment(env);
                    if (function_exists("add_rack_entry", env))
                        loc = "rack";
                    else if (IS_MOBILE_OBJECT(env))
                        loc = "npc";
                    else if (IS_ROOM_OBJECT(env))
                        loc = "room";
                    else if (IS_PLAYER_OBJECT(env))
                        loc = upper_case(env->query_real_name());
                }

/*                x = ob->query_hit();
                hit = x ? x + "" : "";
                x = ob->query_pen();
                pen = x ? x + "" : "";
                x = ob->query_ac();
                ac = (x && ob->check_armour()) ? x + "" : "";*/
            }
        else
            hit = "";
        
        //num = rec[COL_TY3] ? 3 : (rec[COL_TY2] ? 2 : 1);
        out += sprintf("%-7d| %-20s|%3s|%3s|%2s| %-20s|%2d|%s\n",
        id, ty, hit, pen, ac, rec[COL_TY1], rec[COL_LV1], loc);
        if (rec[COL_TY2])
            out += sprintf("%7s|%21s|%3s|%3s|%2s| %-20s|%2d|\n",
                z, z, z, z, z, rec[COL_TY2], rec[COL_LV2]);
        if (rec[COL_TY3])
            out += sprintf("%7s|%21s|%3s|%3s|%2s| %-20s|%2d|\n",
                z, z, z, z, z, rec[COL_TY3], rec[COL_LV3]);
    }
    write(out);
    return 1;
} /* list */


/*
 * Function name: filt
 * Description:   for filtering mod list
 */
public int
filt(int type, int val, int id)
{
    mixed *rec = imbuements[id];
    object ob, env, env2;
    if (!rec)
        return 0;
    ob = rec[COL_OBJ];
    if ((type < 4 || type > 6) && !ob)
        return 0;
    if (type == 1)
        return (ob->query_wt() == val) && (ob->check_weapon());
    if (type == 2)
    {
        if (val == 0)
            return ob->check_weapon();
        if (val == 1)
            return ob->check_armour();
    }
    if (type == 3)
    {
        env = environment(ob);
        if (!env)
            return 0;
        env2 = environment(env);
        if (!env2)
            env2 = env;
        if (IS_PLAYER_OBJECT(env) || IS_PLAYER_OBJECT(env2))
            return val == 1;
        else if (IS_MOBILE_OBJECT(env) || IS_MOBILE_OBJECT(env2))
            return val == 2;
        else if (function_exists("add_rack_entry", env) || 
            function_exists("add_rack_entry", env2))
            return val == 4;
        else if (IS_ROOM_OBJECT(env) || IS_ROOM_OBJECT(env2))
            return val == 3;
        else
            return 0;
/*        switch (val)
        {
            case 1:
                return IS_PLAYER_OBJECT(env);
            case 2:
                return IS_MOBILE_OBJECT(env);
            case 3:
                return IS_ROOM_OBJECT(env);
            case 4:
                return (function_exists("add_rack_entry", env) != 0);
            default:
                return 0;
        }*/
    }
    if (type == 4)
        return (rec[COL_LV1] == val) || (rec[COL_LV2] == val) || 
            (rec[COL_LV3] == val);
    if (type == 5)
    {
        if (rec[COL_TY3])
            return val == 3;
        if (rec[COL_TY2])
            return val == 2;
        if (rec[COL_TY1])
            return val == 1;
    }
    if (type == 6)
        return rec[COL_STA] == 1;
    if (type == 7)
    {
        return member_array(ob, deep_inventory(users()[val])) >= 0;
    }

    return 0;
} /* filt */


/*
 * Function name: details
 * Description:   detailed info on an imbued object
 */
public int
details(int arg)
{
    mixed *rec;
    string out, pre = "";
    object ob, env;
    int num;

    imbuements = IMBUE_MASTER->get_imbuements();
    rec = imbuements[arg];
    if (!rec) {
        write("No such ID!\n");
        return 1;
        }
    ob = rec[COL_OBJ];
    if (ob)
    {
        env = ob;
        out =  "Item     : " + file_name(ob) + "\n";
        out += "Descript.: " + capitalize(ob->short()[strlen(ob->
            query_prop(IMBUE_SHORT))+ 1..]) + "\n"; // blargh
        if (!env)
            out += "Location : The great void\n";
        while (env = environment(env))
        {
            pre += " ";
            out += pre + "Location : " + file_name(env) + "\n";
            out += pre + "Loc. Type: ";
            if (IS_MOBILE_OBJECT(env))
                out += "NPC (" + capitalize(env->short()) + ")\n";
            else if (IS_PLAYER_OBJECT(env))
                out += "Player (" + capitalize(env->query_real_name()) + ")\n";
            else if (IS_ROOM_OBJECT(env))
                out += "Room (" + env->short()[..50] + ")\n";
            else if (IS_CONTAINER_OBJECT(env))
                out += "Container (" + capitalize(env->short()) + ")\n";
            else if (IS_OBJECT_OBJECT(env))
                out += "Object (" + capitalize(env->short()) + ")\n";
            else
                out += "?!?!\n";
        }

        if (ob->check_weapon())
            out += "Hit/Pen  : " + ob->query_hit() + " / " + ob->query_pen() +
                "\n";
        if (ob->check_armour())
            out += "AC       : " + ob->query_ac() + "\n";
    }
    else
        if (rec[COL_STA] == 1)
            out = "Item not found.\n";
        else
            out = "";

    num = rec[COL_TY3] ? 3 : (rec[COL_TY2] ? 2 : 1);
    out += "Rarity   : " + capitalize(POWER_SHORT[num]) + "\n";
    out += "Mod (pow): " + rec[COL_TY1] + " (" + rec[COL_LV1] + ")\n";
    if (rec[COL_TY2])
        out += "           " + rec[COL_TY2] + " (" + rec[COL_LV2] + ")\n";
    if (rec[COL_TY3])
        out += "           " + rec[COL_TY3] + " (" + rec[COL_LV3] + ")\n";
    out += "Status   : " + ({ "Destructed", "???", "Normal", "Recovery", 
            "Lost", "Lost at Armageddon" })[rec[COL_STA] + 1] + "\n";
    write(out);
    return 1;
} /* details */


/*
 * Function name: go
 * Description:   teleport to imbued object
 */
public int
go(string arg)
{
    mixed *rec;
    object ob, env;

    imbuements = IMBUE_MASTER->get_imbuements();
    rec = imbuements[atoi(arg)];
    if (!rec) {
        write("No such ID!\n");
        return 1;
        }
    ob = rec[COL_OBJ];
    if (!ob)
    {
        write("Item not found!\n");
        return 1;
    }
    env = environment(ob);
    if (!env)
    {
        write("Object in void!\n");
        return 1;
    }
    while (environment(env))
    {
        env = environment(env);
    }
    this_player()->move_living("X", env);
    return 1;
} /* go */

/*
 * Function name: imbue
 * Description:   imbue an object
 */
public int
imbue(string arg)
{
    object ob, env;
    int a, lev1, lev2, lev3;
    string item, mod1, mod2, mod3;

    if (!check_access)
    {
        write("No!\n");
        return 1;
    }

    if (arg)
        a = sscanf(arg, "%s %s %d %s %d %s %d", item, mod1, lev1, mod2, lev2,
            mod3, lev3);
    if ((a != 3) && (a != 5) && (a != 7)) {
        write("Usage: imbue [item] [mod 1] [lev 1] ([mod 2] [lev 2] ([mod3" +
        "] [lev 3]))\n");
        return 1;
        }
    ob = "/cmd/std/tracer_tool_base"->parse_list(item);
    if (!ob)
    {
        write("Item not found!\n");
        return 1;
    }
    env = environment(ob);
    if (env != this_player())
    {
        write("You don't have that!\n");
        return 1;
    }

    if (a = 7)
        IMBUE_GENERATOR->imbue(ob, mod1, lev1, mod2, lev2, mod3, lev3);
    else if (a = 5)
        IMBUE_GENERATOR->imbue(ob, mod1, lev1, mod2, lev2);
    else
        IMBUE_GENERATOR->imbue(ob, mod1, lev1);

    return 1;
} /* imbue */