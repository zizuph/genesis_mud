/*
 *  /d/Shire/guild/smiths/rooms/manager_room.c
 *
 *  Menu driven object that manages item list for the Smiths.
 *
 *  Glaurung, August 98
 *
 *  TODO:
 *
 *  - add 'remove' and 'modify' functionality to menu system
 *  - general clean up, remove obsolete functionality
 */

#pragma strict_types

inherit "/std/room.c";

#include <wa_types.h>
#include <formulas.h>
#include "/d/Shire/guild/smiths/smiths.h"
#include "/d/Shire/sys/defs.h"

#define DESC_LOG "/d/Shire/guild/smiths/log/desc_log"
#define INIT_LOG "/d/Shire/guild/smiths/log/init_log"

//********************** Global Variables ***************************//

private mapping Weapon_list = ([]); // only non-static variables are
private mapping Armour_list = ([]); // saved via save_object

static private int     gItemType = 0;
static private string *gItemName;
static private string *gAdjList;
static private int     gDif;
static private int     gAT = A_BODY;
static private string  gShortDesc;
static private string  gLongDesc;
static private string *gMaterials;
static private int    *gMod = ({ 0, 0, 0 });
static private int     gHands = W_NONE;
static private int     gDT = W_BLUDGEON;
static private int     gWT = W_FIRST;
static private int     gReviewItem = 0;
static private int     gHit = 0;
static private int     gPen = 0;
static private int     gAc = 0;

//********************** Prototypes ********************************//

private void ac_fun(string s);
private void ac_menu();
private void accept_fun(string s);
private void adj_fun(string s);
private void adj_menu();
private void at_fun(string s);
private void at_menu();
private void done_arm_menu();
private void done_wep_menu();
private void dif_menu();
private void dif_fun(string s);
private void dt_fun(string s);
private void dt_menu();
private void hands_fun(string s);
private void hands_menu();
private void hit_fun(string s);
private void hit_menu();
private string list_array(string *s);
private void long_fun(string s);
private void long_menu();
private void material_fun(string s);
private void material_menu();
private void mod_fun(string s);
private void mod_menu();
private void mod_arm_fun(string s);
private void mod_arm_menu();
private void mod_wep_fun(string s);
private void mod_wep_menu();
private void name_fun(string s);
private void name_menu();
private void option_fun(string s);
private void option_menu();
private void pen_fun(string s);
private void pen_menu();
private int query_vals();
private void reset_vals();
private void return_to_menu();
private void short_menu();
private void short_fun(string s);
private int smith_create();
private void wt_fun(string s);
private void wt_menu();
private int add_smith_armour(string forgeby,int dif,int ac,int loc,int *mod,
                string *name, string *adj, string shortd, string longd,
                string *materials);
private int add_smith_weapon(string forgeby,int dif,int wt,int dt,int hands,
                string *name, string *adj, string shortd, string longd,
                string *materials, int hit, int pen);
public object create_smith_armour(string s, int i);
public object create_smith_weapon(string s, int i);
public void init_smith_armour(int i, string s, object o, string t, string f);
public void init_smith_weapon(int hit, int pen, string name, object obj,
                string state, string forger);
public int modify_smith_armour(string s, int i, mixed m);
public void modify_smith_item_desc(object o, string s);
public int modify_smith_weapon(string s, int i, mixed m);
public mixed *query_armour_stats(string s);
public string *query_forgeable_items();
public int query_item_type(string s);
public void query_smith_armours();
public void query_smith_weapons();
public mixed *query_weapon_stats(string s);
public int remove_smith_armour(string s);
public int remove_smith_weapon(string s);
private int test_smith_item(string s);

//******************************************************************//

public void
create_room()
{
    setuid(); seteuid(getuid());

    set_short("A spacious office");
    set_long("You stand within a spacious office. There are no "+
        "windows or exits visible so you wonder what really "+
        "goes on in here. This is obviously not a place "+
        "for mere mortals. You may <create> new armours and weapons, <test> and list <vals>.\n");

    restore_object(SMITH_OBJECT_LOG);
}

public void
init()
{
    add_action(smith_create, "create");
//  add_action(smith_remove, "remove"); need to do functionality
//  add_action(smith_modify, "modify");
    add_action(query_vals, "vals");
    add_action(test_smith_item, "test");
}

private int
smith_create()
{
    option_menu();
    return 1;
}

private void
accept_fun(string s)
{
    if (s == "Y" || s == "y")
    {
        if (gItemType == 1)
        {
            add_smith_armour(gItemName[0], gDif, gAc, gAT, gMod, gItemName,
                gAdjList, gShortDesc, gLongDesc, gMaterials);
        }

        else if (gItemType == 2)
        {
            add_smith_weapon(gItemName[0], gDif, gWT, gDT, gHands, gItemName,
                gAdjList, gShortDesc, gLongDesc, gMaterials, gHit, gPen);
        }

        write("Item accepted.\n");
        reset_vals();
    }

    else if (s == "n" || s == "N")
        return_to_menu();

    else
        reset_vals();
}

private void
option_menu()
{
    write("\n********************\n"+
          "* Select an option *\n"+
          "********************\n"+
        "1 - Create an armour\n"+
        "2 - Create a weapon\n"+
        "3 - Exit\n\n"+
        ">");
    input_to(option_fun);
}

private void
wt_menu()
{
    write("\n************************\n"+
        "* Select a weapon type *\n"+
        "************************\n"+
        "1 - Sword\n"+
        "2 - Polearm\n"+
        "3 - Axe\n"+
        "4 - Knife\n"+
        "5 - Club\n"+
        "6 - Exit\n\n"+
        ">");
    input_to(wt_fun);
}

private void
dt_menu()
{
    write("\n************************\n"+
        "* Select a damage type *\n"+
        "************************\n"+
        "1 - Impale\n"+
        "2 - Slash\n"+
        "3 - Slash | Impale\n"+
        "4 - Bludgeon\n"+
        "5 - Impale | Bludgeon\n"+
        "6 - Slash | Bludgeon\n"+
        "7 - Impale | Slash | Bludgeon\n"+
        "8 - Exit\n\n"+
        ">");
    input_to(dt_fun);
}

private void
hands_menu()
{
    write("\n***********************\n"+
        "* Select a handedness *\n"+
        "***********************\n"+
        "1 - Either hand\n"+
        "2 - Right hand only\n"+
        "3 - Left hand only\n"+
        "4 - Both hands required\n"+
        "5 - Exit\n\n"+
        ">");
    input_to(hands_fun);
}

private string
list_array(mixed *s)
{
    int i, sz = sizeof(s);
    string res = "";

    for (i = 0; i < sz; i++)
    {
        if (intp(s[i]))
            res += val2str(s[i]);
        else
            res += s[i];

        if (i < (sz - 1))
            res += ", ";
    }

    return res;
}

private void
done_wep_menu()
{
    string wt = WT_AS[gWT],
           dt = DT_AS[gDT - 1],
           hands = HANDS_MAP[gHands];

    gReviewItem = 1;
    write("\nYou are about to make the following item forgeable by the Smith Guild.\n"+
        "Weapon type    -> "+wt+"\n"+
        "Damage type    -> "+dt+"\n"+
        "Handedness     -> "+hands+"\n"+
        "Name(s)        -> "+list_array(gItemName)+"\n"+
        "Adjectives     -> "+list_array(gAdjList)+"\n"+
        "Short desc     -> "+gShortDesc+"\n"+
        "Long desc file -> "+gLongDesc+"\n"+
        "Materials used -> "+list_array(gMaterials)+"\n\n"+
        "Accept item? [Y]es, [N]o, [E]xit\n\n"+
        ">");
     input_to(accept_fun);
}

private void
done_arm_menu()
{
    string at = AT_MAP[gAT];

    gReviewItem = 1;
    write("\nYou are about to make the following item forgeable by the Smith Guild.\n"+
        "Armour type    -> " + at + "\n"+
        "Armour mods    -> " + list_array(gMod) + "\n" +
        "Name(s)        -> " + list_array(gItemName) + "\n" +
        "Adjectives     -> " + list_array(gAdjList) + "\n" +
        "Short desc     -> " + gShortDesc + "\n" +
        "Long desc file -> " + gLongDesc + "\n" +
        "Materials used -> " + list_array(gMaterials) + "\n\n" +
        "Accept item? [Y]es, [N]o, [E]xit\n\n"+
        ">");
    input_to(accept_fun);
}

private void
reset_vals()
{
    gItemType = 0;
    gItemName = ({});
    gDif = 0;
    gAdjList = ({});
    gShortDesc = "";
    gLongDesc = "";
    gMaterials = ({});
    gMod = ({ 0, 0, 0 });
    gHands = W_NONE;
    gDT = W_BLUDGEON;
    gWT = W_FIRST;
    gAT = A_BODY;
    gHit = 0;
    gPen = 0;
    gAc = 0;
    gReviewItem = 0;
    write("Exiting.\n");
}

private void
mod_wep_menu()
{
    write("\n*********************************\n"+
        "* Select an attribute to change *\n"+
        "*********************************\n"+
        "1 - Weapon type\n"+
        "2 - Damage type\n"+
        "3 - Handedness\n"+
        "4 - Weapon name(s)\n"+
        "5 - Adjectives\n"+
        "6 - Short description\n"+
        "7 - Long description file\n"+
        "8 - Materials\n"+
        "9 - Accept weapon\n"+
        "0 - Exit\n\n"+
        ">");
     input_to(mod_wep_fun);
}

private void
mod_arm_menu()
{
    write("\n*********************************\n"+
        "* Select an attribute to change *\n"+
        "*********************************\n"+
        "1 - Armour type\n"+
        "2 - Amour mods\n"+
        "3 - Armour name(s)\n"+
        "4 - Adjectives\n"+
        "5 - Short description\n"+
        "6 - Long description file\n"+
        "7 - Materials\n"+
        "8 - Accept armour\n"+
        "9 - Exit\n\n"+
        ">");
    input_to(mod_arm_fun);
}

private void
mod_wep_fun(string s)
{
    int i = str2val(s);

    switch (i)
    {
        case 1:
            write("\nThe current weapon type -> "+WT_AS[gWT]+"\n");
            wt_menu();
            break;

        case 2:
            write("\nThe current damage type -> "+DT_AS[gDT - 1]+"\n");
            dt_menu();
            break;

        case 3:
            write("\nThe current handedness -> "+HANDS_MAP[gHands]+"\n");
            hands_menu();
            break;

        case 4:
            write("\nThe current name(s) -> "+list_array(gItemName)+"\n");
            name_menu();
            break;

        case 5:
            write("\nThe current adjectives -> "+list_array(gAdjList)+"\n");
            adj_menu();
            break;

        case 6:
            write("\nThe current short description -> "+gShortDesc+"\n");
            short_menu();
            break;

        case 7:
            write("\nThe current long description file -> "+gLongDesc+"\n");
            long_menu();
            break;

        case 8:
            write("\nThe current materials needed -> " + list_array(gMaterials)+"\n");
            material_menu();
            break;

        case 9:
            done_wep_menu();
            return;

        case 0:
            reset_vals();
            return;

        default:
            write("\nInvalid selection, try again.\n");
            mod_wep_menu();
            break;
    }
}

private void
mod_arm_fun(string s)
{
    int i = str2val(s);

    switch (i)
    {
        case 1:
            write("\nThe current armour type -> "+AT_MAP[gAT]+"\n");
            at_menu();
            break;

        case 2:
            write("\nThe current armour mods -> "+list_array(gMod)+"\n");
            mod_menu();
            break;

        case 3:
            write("\nThe current name(s) -> "+list_array(gItemName)+"\n");
            name_menu();
            break;

        case 4:
            write("\nThe current adjectives -> "+list_array(gAdjList)+"\n");
            adj_menu();
            break;

        case 5:
            write("\nThe current short description -> "+gShortDesc+"\n");
            short_menu();
            break;

        case 6:
            write("\nThe current long description file -> "+gLongDesc+"\n");
            long_menu();
            break;

        case 7:
            write("\nThe current materials needed -> "+list_array(gMaterials)+"\n");
            material_menu();
            break;

        case 8:
            done_arm_menu();
            return;

        case 9:
            reset_vals();
            return;

        default:
            write("\nInvalid selection, try again.\n");
            mod_arm_menu();
            break;
    }
}

private void
at_menu()
{
    write("\n*************************\n"+
        "* Select an armour type *\n"+
        "*************************\n"+
        "1 - Body armour\n"+
        "2 - Head armour\n"+
        "3 - Arm armour\n"+
        "4 - Leg armour\n"+
        "5 - Body and arm armour\n"+
        "6 - Body and leg armour\n"+
        "7 - Body, arm, and leg armour\n"+
        "8 - Shield\n"+
        "9 - Exit\n\n"+
        ">");
     input_to(at_fun);
}

private void
at_fun(string s)
{
    int i = str2val(s);

    switch (i)
    {
        case 1:
            gAT = A_BODY;
            break;

        case 2:
            gAT = A_HEAD;
            break;

        case 3:
            gAT = A_ARMS;
            break;

        case 4:
            gAT = A_LEGS;
            break;

        case 5:
            gAT = A_BODY | A_ARMS;
            break;

        case 6:
            gAT = A_BODY | A_LEGS;
            break;

        case 7:
            gAT = A_BODY | A_ARMS | A_LEGS;
            break;

        case 8:
            gAT = A_SHIELD;
            break;

        case 9:
            reset_vals();
            break;

        default:
            gAT = A_BODY;
            write("\nInvalid selection, try again.\n");
            at_menu();
            break;
    }

    if (!gReviewItem)
        ac_menu();
    else
    {
        write("\nArmour type changed to -> " + AT_MAP[gAT] + "\n");
        mod_arm_menu();
    }
}

private void
ac_menu()
{
    write("Give an armour class rating for this item (1-40)\n>");
    input_to(ac_fun);
}

private void
ac_fun(string s)
{
    int i = str2val(s);

    if (i < 1 || i > 40)
    {
        write("Invalid selection, try again.\n");
        ac_menu();
        return;
    }

    gAc = i;
    if (!gReviewItem)
        mod_menu();
    else
    {
        write("Armour class changed to -> "+gAc+"\n");
        mod_arm_menu();
    }
}

private void
mod_menu()
{
    write("\nSelect armour modification vs Impale/Slash/Bludgeon attacks.\n"+
        "Seperate numbers by commas.\n\n"+
        ">");
    input_to(mod_fun);
}

private void
mod_fun(string s)
{
    string *mod_s = explode(s, ",");

    gMod = ({ str2val(mod_s[0]), str2val(mod_s[1]), str2val(mod_s[2]) });
    if (!gReviewItem)
        dif_menu();
    else
    {
        write("\nArmour mods changed to -> "+list_array(gMod)+"\n");
        mod_arm_menu();
    }
}

private void
option_fun(string s)
{
    int i = str2val(s);

    switch (i)
    {
        case 1:
            gItemType = 1; // armour
            at_menu();
            break;

        case 2:
            gItemType = 2; // weapon
            wt_menu();
            break;

        case 3:
            reset_vals();
            return;

        default:
            write("\nInvalid selection, try again.\n");
            option_menu();
            return;
    }
}

private void
wt_fun(string s)
{
    int i = str2val(s);

    // we need i 0 relative so decrement the value passed by 1
    if (member_array(--i, ({ W_SWORD, W_POLEARM, W_AXE, W_KNIFE, W_CLUB })) > -1)
    {
        gWT = i;
        if (!gReviewItem)
            dt_menu();
        else
        {
            write("\nWeapon type changed to -> "+WT_AS[gWT]+"\n");
            mod_wep_menu();
        }
    }

    else if (i == 5)
        reset_vals();

    else
    {
        gWT = W_FIRST;
        write("\nInvalid selection, try again.\n");
        wt_menu();
    }

    return;
}

private void
dt_fun(string s)
{
    int i = str2val(s);

    if (member_array(i, ({ W_IMPALE, W_SLASH, (W_SLASH|W_IMPALE), W_BLUDGEON,
        (W_IMPALE|W_BLUDGEON), (W_SLASH|W_BLUDGEON), (W_IMPALE|W_SLASH|W_BLUDGEON) })) > -1)
    {
        gDT = i;
        if (!gReviewItem)
            hands_menu();
        else
        {
            write("\nDamage type changed to -> "+DT_AS[gDT - 1]+"\n");
            mod_wep_menu();
        }
    }
    else if (i == 8)
        reset_vals();
    else
    {
        gDT = W_BLUDGEON;
        write("\nInvalid selection, try again.\n");
        dt_menu();
    }

    return;
}

private void
hands_fun(string s)
{
    int i = str2val(s);

    switch (i)
    {
        case 1:
            gHands = W_ANYH;
            break;

        case 2:
            gHands = W_RIGHT;
            break;

        case 3:
            gHands = W_LEFT;
            break;

        case 4:
            gHands = W_BOTH;
            break;

        case 5:
            reset_vals();
            return;

        default:
            gHands = W_NONE;
            write("\nInvalid selection, try again.\n");
            hands_menu();
            return;
    }

    if (!gReviewItem)
        hit_menu();
    else
    {
        write("\nHandedness changed to -> "+HANDS_MAP[gHands]+"\n");
        mod_wep_menu();
    }
}

private void
hit_menu()
{
    write("Give a hit rating for this item (1-40)\n>");
    input_to(hit_fun);
}

private void
hit_fun(string s)
{
    int i = str2val(s);

    if (i < 1 || i > 40)
    {
        gHit = 0;
        write("Invalid selection, try again.\n");
        hit_menu();
        return;
    }

    gHit = i;
    if (!gReviewItem)
        pen_menu();
    else
    {
        write("Item hit changed to -> "+gHit+"\n");
        mod_wep_menu();
    }
}

private void
pen_menu()
{
    write("Give a pen rating for this item (1-40)\n>");
    input_to(pen_fun);
}

private void
pen_fun(string s)
{
    int i = str2val(s);

    if (i < 1 || i > 40)
    {
        gPen = 0;
        write("Invalid selection, try again.\n");
        pen_menu();
        return;
    }

    gPen = i;
    if (!gReviewItem)
        dif_menu();
    else
    {
        write("Item pen changed to -> "+gPen+"\n");
        mod_wep_menu();
    }
}

private void
dif_menu()
{
    write("\nGive a difficulty rating to this item (1-100)\n>");
    input_to(dif_fun);
}

private void
dif_fun(string s)
{
    int i = str2val(s);

    if (i < 1 || i > 100)
    {
        gDif = 0;
        write("Invalid selection, try again.\n");
        dif_menu();
        return;
    }

    gDif = i;
    if (!gReviewItem)
        name_menu();
    else
    {
        write("Item difficulty changed to -> "+gDif+"\n");
        return_to_menu();
    }
}

private void
name_menu()
{
    write("\nGive a name(s) for this item. Separate by a comma if more than one. These are the names armour is referred to (bracers,black bracers,etc).\n");
    input_to(name_fun);
}

private void
name_fun(string s)
{
    int i;
    string *names = explode(s, ",");

    gItemName = ({});
    if (sizeof(names) > 1)
    {
        for (i = 0; i < sizeof(names); i++)
            gItemName += ({ names[i] });
    }
    else
        gItemName = ({ names[0] });

    if (!gReviewItem)
        adj_menu();
    else
    {
        write("\nItem name(s) changed to -> "+list_array(gItemName)+"\n");
        return_to_menu();
    }
}

private void
adj_menu()
{
    write("\nSupply adjectives seperated by commas.\n");
    input_to(adj_fun);
}

private void
adj_fun(string s)
{
    int i;
    string *adjs = explode(s, ",");

    gAdjList = ({});
    if (sizeof(adjs) > 1)
    {
        for (i = 0; i < sizeof(adjs); i++)
            gAdjList += ({ adjs[i] });
    }
    else
        gAdjList = ({ adjs[0] });

    if (!gReviewItem)
        short_menu();
    else
    {
        write("\nAdjectives changed to -> "+list_array(gAdjList)+"\n");
        return_to_menu();
    }
}

private void
short_menu()
{
    write("\nSupply short description.\n");
    input_to(short_fun);
}

private void
short_fun(string s)
{
    gShortDesc = s;
    if (!gReviewItem)
        long_menu();
    else
    {
        write("\nShort description changed to -> "+gShortDesc+"\n");
        return_to_menu();
    }
}

private void
long_menu()
{
    write("\nSupply long description\n>");
    input_to(long_fun);
}

private void
long_fun(string s)
{
    if (!strlen(s))
    {
        gLongDesc = "";
        write("Invalid long description, try agian.\n");
        long_menu();
        return;
    }

    gLongDesc = s;
    if (!gReviewItem)
        material_menu();
    else
    {
        write("\nLong description file changed to -> "+gLongDesc+"\n");
        return_to_menu();
    }
}

private void
material_menu()
{
    write("\nSelect the materials needed to forge this item. If more than one\n"+
        "seperate materials by commas.\n"+
        "1 - An iron bar\n"+
        "2 - A piece of leather\n"+
        "3 - A piece of wood\n\n"+
        ">");
    input_to(material_fun);
}

private void
material_fun(string s)
{
    int i;
    string *materials = explode(s, ","),
            type;

    gMaterials = ({});
    if (sizeof(materials) > 1)
    {
        for (i = 0; i < sizeof(materials); i++)
            gMaterials += ({ SMITH_MATERIAL_LIST[str2val(materials[i])] });
    }
    else
        gMaterials = ({ SMITH_MATERIAL_LIST[str2val(materials[0])] });

    if (!gReviewItem)
    {
        if (gItemType == 1)
            done_arm_menu();

        else if (gItemType == 2)
            done_wep_menu();
    }

    else
    {
        write("\nMaterials needed changed to -> "+list_array(gMaterials)+"\n");
        return_to_menu();
    }
}

private int
query_vals()
{
    dump_array(({ gItemType, gItemName, gAdjList, gShortDesc, gLongDesc, gMaterials, gMod,
        gHands, gDT, gWT, gAT, gHit, gPen, gAc}));
    return 1;
}

private void
return_to_menu()
{
    if (gItemType == 1)
        mod_arm_menu();

    else if (gItemType == 2)
        mod_wep_menu();
}

private int
add_smith_armour(string forgeby,int dif,int ac,int loc,int *mod,
string *name, string *adj, string shortd, string longd, string *materials)
{

    if (!strlen(forgeby) || !dif)
    {
        NF("Failed to give either a name to forge item by "+
            "or an appropriate difficulty level.\n");
        return 0;
    }

    if (ac > 39 || ac < 0)
    {
        NF("Illegal value given for armour class: "+ac+"\n");
        return 0;
    }

    if (member_array(loc, ({ A_BODY, A_TORSO, A_ARMS, A_LEGS, A_HEAD,
        A_SHIELD, A_ROBE, A_BODY | A_ARMS, A_BODY | A_LEGS,
        A_BODY | A_ARMS | A_LEGS | A_SHIELD})) == -1)
    {
        NF("Illegal armour location given: "+loc+"\n");
        return 0;
    }

    if (!sizeof(name) || !strlen(shortd) || !strlen(longd))
    {
        NF("Failed to give either a name, a short description, "+
           " or a long description to the item.\n");
        return 0;
    }

    if (sizeof(mod) != 3)
        mod = ({0, 0, 0});

    if (!sizeof(materials))
        materials = ({"smiths_iron_bar", "smiths_leather"});

    Armour_list[forgeby]=({dif,ac,loc,mod,name,adj,shortd,longd,materials});
    write("Armour added.\n");
    save_object(SMITH_OBJECT_LOG);
    return 1;
}

private int
add_smith_weapon(string forgeby,int dif,int wt,int dt,int hands,
string *name, string *adj, string shortd, string longd,
string *materials, int hit, int pen)
{
    if (!strlen(forgeby) || !dif)
    {
        NF("Failed to give either a name to forge item by "+
            "or an appropriate difficulty level.\n");
        return 0;
    }

    if (member_array(wt, ({ W_SWORD, W_AXE, W_CLUB, W_POLEARM,
        W_KNIFE, W_JAVELIN })) == -1)
    {
        NF("Illegal weapon type given: "+wt+"\n");
        return 0;
    }

    if (member_array(dt, ({ W_SLASH, W_IMPALE, W_BLUDGEON, W_SLASH|W_IMPALE,
        W_SLASH|W_BLUDGEON, W_IMPALE|W_BLUDGEON })) == -1)
    {
        NF("Illegal damage type given: "+dt+"\n");
        return 0;
    }

    if (member_array(hands, ({ W_RIGHT, W_LEFT, W_BOTH, W_ANYH, W_FOOTR,
        W_FOOTL, W_NONE })) == -1)
    {
        NF("Illegal weapon location given: "+hands+"\n");
        return 0;
    }

    if (!sizeof(name) || !strlen(shortd) || !strlen(longd))
    {
        NF("Failed to give either a name, a short description, "+
           "or a long description to the item.\n");
        return 0;
    }

    if (hit > 39 || pen > 39 || hit < 0 || pen < 0)
    {
        NF("Illegal value given for hit: "+hit+" or pen: "+pen+"\n");
        return 0;
    }

    // a 0 can be passed to set default materials
    if (!pointerp(materials))
        materials = ({"smiths_iron_bar","smiths_leather"});

    Weapon_list[forgeby] = ({dif,wt,dt,hands,name,adj,shortd,longd,
        materials,hit,pen});
    write("Weapon added.\n");
    save_object(SMITH_OBJECT_LOG);
    return 1;
}

public object
create_smith_armour(string str, int mod)
{
    int ac = 0;
    mixed *armours = m_indexes(Armour_list);
    object obj;
    string rec_str;

    if (!strlen(str))
        return 0;

    if (member_array(str, armours) == -1)
        return 0;

    ac = MIN(40, (Armour_list[str][AC]+mod));

    if (Armour_list[str][SA_SHORT] == "heater shield")
        {
            obj = clone_object(SMITHSDIR_OBJ + "heater_shield");
            if (ac > 35)
                ac = 35;
        }
    else if (Armour_list[str][SA_SHORT] == "grand tower shield")
        {
            obj = clone_object(SMITHSDIR_OBJ + "tower_shield");
            if (ac > 35)
                ac = 35;
        }
    else
        obj = clone_object(SMITHSDIR_OBJ + "std_smith_armour");
    obj->set_forger(TP->query_real_name());
    obj->set_default_armour(
        ac,
        Armour_list[str][LOC],
        Armour_list[str][MOD],
        obj);
    obj->set_name(Armour_list[str][SA_NAME]);
    obj->set_adj(Armour_list[str][SA_ADJ]);
    obj->set_short(Armour_list[str][SA_SHORT]);
    obj->set_long(Armour_list[str][SA_LONG]+"\n");
    obj->add_prop(OBJ_I_WEIGHT,
        F_WEIGHT_DEFAULT_ARMOUR(obj->query_ac(), obj->query_at()) * 3 / 4);
    obj->add_prop(OBJ_I_VOLUME, obj->query_prop(OBJ_I_WEIGHT) / 7);
    obj->add_prop(OBJ_I_VALUE, F_VALUE_ARMOUR(obj->query_ac()) + 200);
    obj->set_forgeName(str);
    rec_str = "#SMA#"+obj->query_ac()+"#"+obj->query_forgeName()+"#";
    obj->set_recover_str(rec_str);
    return obj;
}

public object
create_smith_weapon(string str, int mod)
{
    int    hit = 0, pen = 0;
    mixed *weapons = m_indexes(Weapon_list);
    object obj;
    string rec_str;

    if (!strlen(str))
        return 0;

    if (member_array(str, weapons) == -1)
        return 0;

    obj = clone_object(SMITHSDIR_OBJ +"std_smith_weapon");
    obj->set_forger(TP->query_real_name());
    // temporary patch
    if (Weapon_list[str][WT] == W_KNIFE)
    {
        hit = MIN(20, (Weapon_list[str][HIT]+mod));
        pen = hit;
    }

    else
    {
        hit = MIN(40, (Weapon_list[str][HIT]+mod));
        pen = MIN(40, (Weapon_list[str][PEN]+mod));
    }

    obj->set_default_weapon(
        hit,
        pen,
        Weapon_list[str][WT],
        Weapon_list[str][DT],
        Weapon_list[str][HANDS],
        obj);
    obj->set_name(Weapon_list[str][NAME]);
    obj->set_adj(Weapon_list[str][ADJ]);
    obj->set_short(Weapon_list[str][SHORTD]);
    obj->set_long(Weapon_list[str][LONGD]+"\n");
    obj->add_prop(OBJ_I_WEIGHT,
        F_WEIGHT_DEFAULT_WEAPON(obj->query_pen(), obj->query_wt()) * 3 / 4);
    obj->add_prop(OBJ_I_VOLUME, obj->query_prop(OBJ_I_WEIGHT) / 10);
    obj->add_prop(OBJ_I_VALUE,
        F_VALUE_WEAPON(obj->query_hit(), obj->query_pen()));
    obj->set_forgeName(str);
    rec_str = "#SMW#"+obj->query_hit()+"#"+obj->query_pen()+
        "#"+obj->query_forgeName()+"#"+""+"#"+obj->query_forger()+"#";
    obj->set_recover_str(rec_str);
    return obj;
}

public void
init_smith_armour(int ac, string name, object obj, string state, string forger)
{
    int    adj_index = -1;
    object sh;
    mixed *armours = m_indexes(Armour_list);

    if (member_array(name, armours) == -1)
    {
        write("Something is wrong with your "+name+
            ". Please get in touch with a Shire wizard.\n");
        return;
    }

    obj->set_default_armour(
        ac,
        Armour_list[name][LOC],
        Armour_list[name][MOD],
        obj);
    obj->set_name(Armour_list[name][SA_NAME]);
    obj->set_adj(Armour_list[name][SA_ADJ]);
    obj->set_short(Armour_list[name][SA_SHORT]);
    obj->set_long(Armour_list[name][SA_LONG]+"\n");
    obj->add_prop(OBJ_I_WEIGHT,
        F_WEIGHT_DEFAULT_ARMOUR(obj->query_ac(), obj->query_at()) * 3 / 4);
    obj->add_prop(OBJ_I_VOLUME, obj->query_prop(OBJ_I_WEIGHT) / 7);
    obj->add_prop(OBJ_I_VALUE, F_VALUE_ARMOUR(obj->query_ac()) + 200);
    obj->set_forger(forger);
    obj->set_forgeName(name);
    obj->query_recover();  // sets recover string properly
    if (strlen(state))
        modify_smith_item_desc(obj, state);
}

public void
init_smith_weapon(int hit, int pen, string name, object obj,
string state, string forger)
{
    int    adj_index = -1;
    mixed *weapons = m_indexes(Weapon_list);
    object sh;

    write_file(INIT_LOG, "hit = "+hit+"\npen = "+pen+"\nname = "+name+"\nstate = "+state+"\nforger = "+forger+"\n#");
    if (strlen(state))
        write_file(INIT_LOG, "State exists\n");
    else
        write_file(INIT_LOG, "State does not exist\n");
    if (member_array(name, weapons) == -1)
    {
        write("Something is wrong with your "+name+".\n"+
            "Please get in touch with a Shire wizard.\n");
        return;
    }

    obj->set_default_weapon(
        hit,
        pen,
        Weapon_list[name][WT],
        Weapon_list[name][DT],
        Weapon_list[name][HANDS],
        obj);
    obj->set_name(Weapon_list[name][NAME]);
    obj->set_adj(Weapon_list[name][ADJ]);
    obj->set_short(Weapon_list[name][SHORTD]);
    obj->set_long(Weapon_list[name][LONGD]+"\n");
    obj->add_prop(OBJ_I_WEIGHT,
        F_WEIGHT_DEFAULT_WEAPON(obj->query_pen(), obj->query_wt()) * 3 / 4);
    obj->add_prop(OBJ_I_VOLUME, obj->query_prop(OBJ_I_WEIGHT) / 10);
    obj->add_prop(OBJ_I_VALUE,
        F_VALUE_WEAPON(obj->query_hit(), obj->query_pen()));
    obj->set_forger(forger);
    obj->set_forgeName(name);
    obj->query_recover();  // sets recover string properly
    if (strlen(state))
        modify_smith_item_desc(obj, state);
}

public int
modify_smith_armour(string name, int index, mixed value)
{
    string *armours = m_indexes(Armour_list);
    int     sz = 9;

    if ((!strlen(name)) || (index < 0) || (index >= sz))
        return 0;

    if (member_array(name, armours) == -1)
        return 0;

    Armour_list[name][index] = value;
    save_object(SMITH_OBJECT_LOG);
    write(name+" has been modified.\n");
    return 1;
}

void
modify_smith_item_desc(object ob, string adj)
{
    string long = ob->query_long();

//    write_file(DESC_LOG, "IN short = "+ob->query_short()+
//        " long = "+long+"#");
// new line of code
    ob->set_state(adj);
    ob->set_short(adj+" "+ob->query_short());
    ob->add_adj(adj);
    long += SMITH_ADJ_TEXT[adj];
    ob->set_long(long);
    ob->add_prop(OBJ_S_MODIFIED_BY_SMITH, adj);
//    write_file(DESC_LOG, "OUT short = "+ob->query_short()+
//        " long = "+ob->query_long()+"#");
}

public int
modify_smith_weapon(string name, int index, mixed value)
{
    string *weapons = m_indexes(Weapon_list);
    int     sz = 11;

    if ((!strlen(name)) || (index < 0) || (index >= sz))
        return 0;

    if (member_array(name, weapons) == -1)
        return 0;

    Weapon_list[name][index] = value;
    save_object(SMITH_OBJECT_LOG);
    write(name+" has been modified.\n");
    return 1;
}

public mixed *
query_armour_stats(string str)
{
    string *armours = m_indexes(Armour_list);

    if (!strlen(str))
        return ({});

    if (member_array(str, armours) == -1)
    {
        write(str+" is not a listed armour.\n");
        return ({});
    }

    return Armour_list[str];
}

public string *
query_forgeable_items()
{
    string *weapons = m_indexes(Weapon_list),
           *armours = m_indexes(Armour_list);


    return weapons + armours;
}

public int
query_item_type(string str)
{
    string *weapons = m_indexes(Weapon_list),
           *armours = m_indexes(Armour_list);


    if (!strlen(str))
        return 0;

    str = LOW(str);
    if (member_array(str, weapons) != -1)
        return 1;

    if (member_array(str, armours) != -1)
        return 2;

    return 0;
}

public void
query_smith_armours()
{
    mixed *armours = m_indexes(Armour_list);
    int   sz,
          i;

    sz = sizeof(armours);
    if (!sz)
    {
        write("No armours listed.\n");
        return;
    }

    write("Armour list\n"+
                  "-----------\n");
    for (i = 0; i < sz; i++)
        write(CAP(armours[i])+"\n");
}

public void
query_smith_weapons()
{
    mixed *weapons = m_indexes(Weapon_list);
    int   sz,
          i;

    sz = sizeof(weapons);
    if (!sz)
    {
        write("No weapons listed.\n");
        return;
    }

    write("Weapons list\n"+
          "------------\n");
    for (i = 0; i < sz; i++)
        write(CAP(weapons[i])+"\n");
}

public mixed *
query_weapon_stats(string str)
{
    string *weapons = m_indexes(Weapon_list);

    if (!strlen(str))
        return ({});

    if (member_array(str, weapons) == -1)
    {
        write(str+" is not a listed weapon.\n");
        return ({});
    }

    return Weapon_list[str];
}

public int
remove_smith_armour(string forgeby)
{
    mixed *armours = m_indexes(Armour_list);

    if (!strlen(forgeby))
        return 0;

    if (member_array(forgeby, armours) == -1)
    {
        NF(forgeby+" not found in armours list.\n");
        return 0;
    }

    Armour_list = m_delete(Armour_list, LOW(forgeby));
    write("Removed '"+forgeby+"' from armours list.\n");
    save_object(SMITH_OBJECT_LOG);
    return 1;
}

public int
remove_smith_weapon(string forgeby)
{
    mixed *weapons = m_indexes(Weapon_list);

    if (!strlen(forgeby))
        return 0;

    if (member_array(forgeby, weapons) == -1)
    {
        NF(forgeby+" not found in weapons list.\n");
        return 0;
    }

    Weapon_list = m_delete(Weapon_list, LOW(forgeby));
    write("Removed '"+forgeby+"' from weapons list.\n");
    save_object(SMITH_OBJECT_LOG);
    return 1;
}

private int
test_smith_item(string name)
{
    object  obj;
    string *items = query_forgeable_items();
    int     type, mod = 0;

    if (!strlen(name))
        return 0;

    if (member_array(name, items) == -1)
    {
        NF("No such thing can be forged.\n");
        return 0;
    }

    type = query_item_type(name);
    switch (type)
    {
        case 1:
            obj = create_smith_weapon(name, mod);
            break;

        case 2:
            obj = create_smith_armour(name, mod);
            break;

        default:
            write("Error: index out of bounds while cloning.\n");
            break;
    }

    if (obj->move(TP))
        obj->move(ENV(TP));

    TP->catch_tell("You have finished forging the "+
        name+".\n");
    return 1;
}
