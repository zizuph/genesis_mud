/* Mortis 12.2005
 *
 * This is the base for packs and weapon holders Daronius
 * crafts in the Arms district of Palanthas.
 *
 * Emotes could use work and expansion.
 *
 * Mortis 09.2014
 * Syntax (if's), grammar, adjective updates.
 *
 * 313, 781 added check if (!art) to prevent wizards who foolishly clone
 * this base file without adjectives or names don't get bugged. Thanks Finwe!
 * -Mortis 03.2015
 *
 * Added a check to see if the object is held before putting it in pack.
 *
 * Cotillion 2019-03-15
 * - Fixed ::prevent_enter() call
 */
 
inherit "/d/Genesis/std/wearable_pack";
inherit "/lib/wearable_item";
inherit "/lib/keep";

#include <wa_types.h>
#include <formulas.h>
#include <stdproperties.h>
#include <macros.h>
#include <cmdparse.h>
#include <language.h>
#include <composite.h>
#include "../../local.h"

#define IM_PARSE_FILE        "/d/Shire/abandoned/healers/lib/parse"

inherit "/lib/commands.c";

int weight, volume, value, maxweight, maxvolume, reduce;
string recover_string, cus, col, mat, art, at, cusshort, cusmore, colmore,
    matmore, matlong, collong, artmore, soundmore, ndesc2, artplural;

int cont_alarm = 0;

/* Prototypes */

int adjust_weight(string which);
int what_slot();
void add_some_names();

mapping name_to_desc = (["backpack":"backpack", "belt-pouch":"belt pouch",
    "knapsack":"knapsack", "lootsack":"lootsack", "rucksack":"rucksack",
    "sack":"sack", "saddlebag":"saddlebag", "satchel":"satchel",
    "thigh-pouch":"thigh pouch", "bandeleria":"bandeleria",
    "back-holster":"back holster", "belt-sheath":"belt sheath", 
    "boot-sheath":"boot sheath", "forearm-sheath":"forearm sheath",
    "scabbard":"scabbard", "side-holster":"side holster",
    "thigh-sheath":"thigh sheath", "wrist-sheath":"wrist sheath"]);

mapping name_to_desc2 = (["backpack":"With a pair of padded shoulder straps "
    + "as well as a waist strap, this pack sits comfortably snug against "
    + "your back and is capable of carrying a great many items safely with "
    + "<fill> and <empty> for easy use",
    "belt-pouch":"Requiring a belt to be worn on, this flat rectangular "
    + "belt-pouch protects even delicate and arcane contents safely with an "
    + "additional inner layer of silk. You may <fill> and <empty> it",
    "knapsack":"With a pair of padded shoulder straps "
    + "as well as a waist strap, this pack sits comfortably snug against "
    + "your back and is capable of carrying a great many items safely with "
    + "<fill> and <empty> for easy use", 
    "lootsack":"The long lootsack has a wide, drawstringed mouth that is "
    + "easy to <sackloot> with allowing you to dump a corpse's contents "
    + "directly within and either <empty> them or <sackdump> them onto the "
    + "ground", 
    "rucksack":"With a pair of padded shoulder straps "
    + "as well as a waist strap, this pack sits comfortably snug against "
    + "your back and is capable of carrying a great many items safely with "
    + "<fill> and <empty> for easy use",
    "sack":"This quality sack has a sturdy leather drawstring and can hold "
    + "quite a bit with <fill> and <empty>", 
    "saddlebag":"Designed to allow you to <drape saddlebag on horse>, this "
    + "large pack is capable of carrying a great many items safely with "
    + "<fill/empty saddlebag on horse>", 
    "satchel":"Larger than a pouch, this flat rectangular satchel has a "
    + "padded strap for wearing over the shoulder and slung across the "
    + "chest to keep it in place at the hip. Its additional inner layer "
    + "of silk protects even delicate and arcane contents. You may <fill> "
    + "and <empty> it",
    "thigh-pouch":"A pair of comfortable straps buckle this flat rectangular "
    + "thigh-pouch snugly along the outside of the thigh where you may easily "
    + "<fill> and <empty> it. An additional inner layer of silk protects "
    + "even delicate and arcane contents safely", 
    "bandeleria":"A shoulder buckled strap keeps the bandeleria slung "
    + "across the chest where a dozen knives or more can be stored with "
    + "<dsheathe/fill> and retrieved easily with <ddraw/empty>",
    "back-holster":"The adjustable loop rests over the back where this back-"
    + "holster stores a large weapon such as an axe, club, or polearm with "
    + "<dholster> and keeps it within reach until ready for use with <ddraw>",
    "belt-sheath":"Requiring a belt to be worn on, this belt-sheath has been "
    + "designed to <dsheathe> a knife and <ddraw> back out easily", 
    "boot-sheath":"Slipped inside a boot, this boot-sheath conceals a knife "
    + "with <dsheathe> and can <ddraw> it back out",
    "forearm-sheath":"A pair of comfortable straps buckle this forearm-sheath "
    + "snugly along the outside of the forearm where it holds a knife "
    + "with <dsheathe> and can <ddraw> it back easily",
    "scabbard":"Requiring a belt to be worn on, it has been designed to "
    + "<dsheathe> a sword and <ddraw> it back out again", 
    "side-holster":"The adjustable loop rests over the hip where it can "
    + "store a large weapon such as an axe or a club with <dholster> "
    + "and keep it within reach until ready for use with <ddraw>",
    "thigh-sheath":"A pair of comfortable straps buckle this thigh-sheath "
    + "snugly along the outside of the thigh where you may <dsheathe> a knife "
    + "and <ddraw> it back out easily",
    "wrist-sheath":"A pair of comfortable straps buckle this wrist-sheath "
    + "snugly inside the forearm where it is difficult to spot. It "
    + "holds a knife with <dsheathe> and can <ddraw> it back out unseen "
    + "by a dextrous wearer"]);

mapping name_to_plural = (["backpack":"backpacks", "belt-pouch":"belt-pouches",
    "knapsack":"knapsacks", "lootsack":"lootsacks", "rucksack":"rucksacks",
    "sack":"sacks", "saddlebag":"saddlebags", "satchel":"satchels",
    "thigh-pouch":"thigh-pouches", "bandeleria":"bandelerias",
    "back-holster":"back-holsters", "belt-sheath":"belt-sheaths", 
    "boot-sheath":"boot-sheaths", "forearm-sheath":"forearm-sheaths",
    "scabbard":"scabbards", "side-holster":"side-holsters",
    "thigh-sheath":"thigh-sheaths", "wrist-sheath":"wrist-sheaths"]);

mapping mat_to_desc = (["hard":"leather boiled in oil, hardening it into "
    + "form fitting plates. ",
    "hide":"rhinocerous hide, a thick, nearly impenetrable hide that is "
    + "much lighter than metal armour. ",
    "soft":"leather, slow cured to be both soft to the touch "
    + "and protective. ",
    "leather":"leather that is firmer than slow cured soft leather but "
    + "more flexible than leather hardened in boiling oil. ",
    "soft":"This leather is slow cured to be both soft to the touch "
    + "and protective.",
    "studded":" leather, expertly cured for a soft feel while remaining "
    + "highly protective. Inch diameter studs, their two inch diameter "
    + "steel plates hidden beneath the leather, stick out every few inches "
    + "giving the armour strong protections without great weight. ",
    "suede":"suede, a very soft, textured leather. Suede must be "
    + "painstakingly cured and worked to not only be so desirable but "
    + "protective as well. As such it is expensive. "]);

mapping colour_to_desc = (["black":"black", "white":"white",
    "charcoal":"charcoal", "grey":"grey", "brown":"brown",
    "mottled-brown":"mottled brown", "crimson":"crimson", "maroon":"maroon",
    "yellow":"yellow", "forest-green":"forest green",
    "mottled-green":"mottled green", "olive-green":"olive green",
    "blue":"blue", "raven-blue":"raven blue", "purple":"purple",
    "silvery":"a lustrous silver hue"]);

mapping custom_to_desc = (["dark":"with texturing to be darker than usual",
    "flat":"with a sleeker, wider shape",
    "fur-trimmed":"with a soft, gray-black fur trimming its edges",
    "glistening":"with a glisteningly smooth surface that catches and "
    + "reflects the light",
    "heavy":"with an extra thick inner lining of swansdown",
    "light":"with experienced molding to be a little lighter than normal",
    "noble":"in a formal yet elegant style common among the nobility",
    "ornate":"with an ornate series of swirling, raised lines down its "
    + "length that curl into spirals at their ends",
    "plain":"to be simple and functional",
    "rich":"with an especially rich texture",
    "supple":"to be especially supple for its material, allowing its wielder "
    + "full grace in movement and practically no hinderance in "
    + "maneuverability", 
    "thin":"with a somewhat thinner material"]);

mapping custom_to_short = (["dark":"dark ",
    "flat":"flat ",
    "fur-trimmed":"fur-trimmed ",
    "glistening":"glistening ",
    "heavy":"heavy ",
    "light":"light ",
    "noble":"noble ",
    "ornate":"ornate ",
    "plain":"",
    "rich":"rich ",
    "supple":"supple ", 
    "thin":"thin "]);

mapping mat_to_sound = (["hard":"creaking tightly",
    "hide":"creaking stiffly",
    "soft":"creaking softly",
    "studded":"creaking menacingly",
    "suede":"rustling quietly"]);

mapping mat_to_full = (["hard":"hard leather",
    "hide":"hide",
    "leather":"leather",
    "soft":"soft leather",
    "studded":"studded leather",
    "suede":"suede"]);

mapping colour_to_full = (["black":"black", "white":"white",
    "charcoal":"charcoal", "grey":"grey", "brown":"brown",
    "mottled-brown":"mottled brown", "crimson":"crimson", "maroon":"maroon",
    "yellow":"yellow", "forest-green":"forest green",
    "mottled-green":"mottled green", "olive-green":"olive green",
    "blue":"blue", "raven-blue":"raven blue", "purple":"purple",
    "silvery":"silvery"]);


void
create_wearable_pack()
{
}

void
set_general_data(string data)
{
    seteuid(getuid());

    string* txt = explode(data,"&&");
    cus = txt[0];
    col = txt[1];
    mat = txt[2];
    art = txt[3];
    weight = adjust_weight("weight");
    volume = adjust_weight("volume");
    value = adjust_weight("value");
    maxweight = adjust_weight("maxweight");
    maxvolume = adjust_weight("maxvolume");
    reduce = adjust_weight("reduce");
    
    artmore = name_to_desc[art];
    ndesc2 = name_to_desc2[art];
    artplural = name_to_plural[art];
    matlong = mat_to_desc[mat];
    matmore = mat_to_full[mat];
    soundmore = mat_to_sound[mat];
    collong = colour_to_desc[col];
    colmore = colour_to_full[col];
    cusmore = custom_to_desc[cus];
    cusshort = custom_to_short[cus];
    
    int dslot = what_slot();
    set_slots(dslot);
    set_layers(1);   // I don't want layers and looseness to hinder so
    set_looseness(8); // check on these.

    add_prop(CONT_I_WEIGHT, weight);
    add_prop(CONT_I_VOLUME, volume);
    add_prop(OBJ_I_VALUE, value);
    add_prop(CONT_I_MAX_WEIGHT, maxweight);
    add_prop(CONT_I_MAX_VOLUME, maxvolume);
    add_prop(CONT_I_REDUCE_WEIGHT, reduce);

    
    set_name(art);
    set_pname(artplural);
    add_adj(cus);
    add_adj(col);
    add_adj(mat);
    add_adj("daronius");    // Generic to all items:

    add_some_names();
    set_keep(1);
    set_cf(TO);
    
    recover_string = data;
    
    set_short(cusshort + colmore + " " + matmore + " " + artmore);
    set_pshort(cusshort + colmore + " " + matmore + " " + artplural);
    
    if (parse_command(art, ({}), "'bandeleria' / 'belt-sheath' / 'boot-sheath' / 'forearm-sheath' / 'scabbard' / 'thigh-sheath' / 'wrist-sheath'"))
    {
    set_long("Finished with masterful precision and detailed attention, "
         + "this " + art + " has a core of rough silk with a thin outer layer "
         + "of " + matmore + " dyed " + collong + " and finished " + cusmore
         + ". " + ndesc2 + ". Pressure stamped into the " + art + "'s "
         + "outside is a circular seal.\n");
    
    if (art == "bandeleria")
    {
        set_mass_storage(1); // Turns on fill/empty commands.
    }
    }
    
    else if (parse_command(art, ({}), "'back-holster' / 'side-holster'"))
    {
    set_long("Finished with masterful precision and detailed attention, "
         + "this " + art + " has a buckled shoulder strap with an adjustable "
         + "loop of " + matmore + " dyed " + collong + " and finished " 
             + cusmore + ". " + ndesc2 + ". Pressure stamped into the " + art 
         + "'s strap is a circular seal.\n");
    }

    else // Remaining arts are packs.
    {
    set_long("Finished with masterful precision and detailed attention, "
         + "this " + art + " has a core of stiff silk with a reinforced outer "
         + "layer of " + matmore + " dyed " + collong + " and finished " 
         + cusmore + ". " + ndesc2 + ". Pressure stamped into the " + art 
         + "'s outside is a circular seal.\n");
    set_mass_storage(1); // Turns on fill/empty commands.
    }
}

/*
 * Function name: short
 * Description  : Add the status of the container to it.
 * Arguments    : for_obj - who wants to know the short
 * Returns      : The short description.
 */
public varargs string
short(object for_obj)
{
    if (!art)
    {
        return "This is a base file. You can't just clone it.\n";
    }

    /* This line is copied from object.c as we don't want the 
     * instance of short in receptacle to be used. Thanks, Mercade.
     */
    if (parse_command(art, ({}), "'wrist-sheath' / 'thigh-sheath' / 'boot-sheath' / 'belt-sheath' / 'forearm-sheath' / 'scabbard' / 'bandeleria' / 'side-holster' / 'back-holster'"))
    { return check_call(obj_short, for_obj); }

    return check_call(obj_short, for_obj)
    + ((query_prop(CONT_I_CLOSED)) ? "" : " (open)");
}

/*
 * Function name: pshort
 * Description  : Add the status of the container to it.
 * Arguments    : for_obj - who wants to know the pshort
 * Returns      : The plural short description.
 */
public varargs string
plural_short(object for_obj)
{
     /* This line is copied from object.c as we don't want the 
     * instance of short in receptacle to be used. Thanks, Mercade.
     */
   string plural_short_description = check_call(obj_pshort, for_obj);

    if (parse_command(art, ({}), "'wrist-sheath' / 'thigh-sheath' / 'boot-sheath' / 'belt-sheath' / 'forearm-sheath' / 'scabbard' / 'bandeleria' / 'side-holster' / 'back-holster'"))
    { return check_call(obj_pshort, for_obj); }

    return ((strlen(plural_short_description)) ? 
        (plural_short_description +
            ((query_prop(CONT_I_CLOSED)) ? "" : " (open)")) : 0);
}

int
close(object obj)
{
    string objname = obj->query_name();

    if (parse_command(objname, ({}), "'wrist-sheath' / 'thigh-sheath' / 'boot-sheath' / 'belt-sheath' / 'forearm-sheath' / 'scabbard' / 'bandeleria' / 'side-holster' / 'back-holster'"))
    {
        string arty = obj->short();
        object where = E(obj);
        write("There is no way to close the " + arty + ".\n");
        return 3;
    }

    return 0;
}

int
what_slot()
{
    int myslot = A_BACK;

    switch(art)
    {
        case "backpack":
        case "knapsack":
        case "rucksack":
        case "lootsack":  // Blocked from being worn in wear()
        case "sack":      // Blocked from being worn in wear()
        case "saddlebag": // Blocked from being worn in wear() Horses only.
            myslot = A_BACK;
            break;
        case "belt-pouch":
        case "belt-sheath":
            myslot = A_WAIST;
            break;
        case "satchel":
        case "bandeleria":
        case "back-holster":
            myslot = A_ANY_SHOULDER;
            break;
        case "boot-sheath":
            myslot = A_ANY_FOOT;
            break;
        case "forearm-sheath":
            myslot = A_ANY_ARM;
            break;
        case "scabbard":
        case "side-holster":
            myslot = A_ANY_HIP;
            break;
        case "thigh-pouch":
        case "thigh-sheath":
            myslot = A_LEGS;
            break;
        case "wrist-sheath":
            myslot = A_ANY_WRIST;
            break;
        default:
            myslot = A_BACK;
    }
    return myslot;
}

int
adjust_weight(string which)
{    
    int wei, vol, val, maxw, maxv, redu;

    switch(art)
    {
        case "backpack":
        case "knapsack":
        case "rucksack":
            wei = 450 + random(100);
            vol = 850 + random(100);
            val = 300;
            maxw = 145000; // was too high
            maxv = 160000; // was too high
            redu = 115;    // was too high
            break;
        case "lootsack":
            wei = 950 + random(100);
            vol = 1150 + random(100);
            val = 240;
            maxw = 135000; // was too high
            maxv = 125000; // was too high
            redu = 115;    // was too high
            break;
        case "sack":
            wei = 280 + random(40);
            vol = 450 + random(100);
            val = 180 + random(40);
            maxw = 165000;  // was too high
            maxv = 165000;  // was too high
            redu = 150;     // was too high
            break;
        case "saddlebag":
            wei = 1400 + random(150);
            vol = 2000 + random(200);
            val = 360;
            maxw = 175000; // was too high
            maxv = 190000; // was too high
            redu = 120;    // was too high
            break;
        case "belt-pouch":
            wei = 120 + random(10);
            vol = 140 + random(20);
            val = 72;
            maxw = 40000;
            maxv = 34000;
            redu = 115;  // was too high
            add_prop(CONT_I_HOLDS_COMPONENTS, 1);
            break;
        case "thigh-pouch":
            wei = 150 + random(10);
            vol = 180 + random(20);
            val = 144;
            maxw = 40000;
            maxv = 36000;
            redu = 115;  // was too high
            add_prop(CONT_I_HOLDS_COMPONENTS, 1);
            break;
        case "belt-sheath":
        case "boot-sheath":
        case "forearm-sheath":
        case "thigh-sheath":
        case "wrist-sheath":
            wei = 145 + random(10);
            vol = 120 + random(10);
            val = 144;
            maxw = 5000;
            maxv = 5000;
            redu = 166;
            add_prop(CONT_M_NO_INS, "Try <dsheathe> instead.\n");
            break;
        case "satchel":
            wei = 310 + random(10);
            vol = 390 + random(30);
            val = 180;
            maxw = 100000;
            maxv = 85000;
            redu = 130;  // was  too high
            add_prop(CONT_I_HOLDS_COMPONENTS, 1);
            break;
        case "bandeleria":
            wei = 775 + random(50);
            vol = 800 + random(150);
            val = 300;
            maxw = 40000;
            maxv = 40000;
            redu = 195;  // was way way too high 
            add_prop(CONT_M_NO_INS, "Try <dsheathe/fill> instead.\n");
            break;
        case "scabbard":
            wei = 700 + random(50);
            vol = 700 + random(50);
            val = 216;
            maxw = 15000;
            maxv = 15000;
            redu = 160; // was too high
            add_prop(CONT_M_NO_INS, "Try <dsheathe> instead.\n");
            break;
        case "back-holster":
        case "side-holster":
            wei = 700 + random(50);
            vol = 700 + random(50);
            val = 216;
            maxw = 15000;
            maxv = 15000;
            redu = 160;  // was too high
            add_prop(CONT_M_NO_INS, "Try <dholster> instead.\n");
            break;
        default:
            wei = 1000;
            vol = 1000;
            val = 72;
            maxw = 5000;
            maxv = 5000;
            redu = 115; // was too high
    }

    if (which == "volume")
    { return vol; }
    if (which == "value")
    { return val; }
    if (which == "weight")
    { return wei; }
    if (which == "maxweight")
    { return maxw; }
    if (which == "maxvolume")
    { return maxv; }
    if (which == "reduce")
    { return redu; }
}

void
add_some_names()
{
    switch(art)
    {
        case "lootsack":
            add_name("sack");
            add_adj("loot");
            break;
        case "saddlebag":
            add_name("bag");
            add_adj("saddle");
            break;
        case "belt-pouch":
            add_name(({"beltpouch", "pouch"}));
            add_pname(({"beltpouches", "pouches"}));
            remove_name("pack");
            add_adj("belt");
            break;
        case "thigh-pouch":
            add_name(({"thighpouch", "pouch"}));
            add_pname(({"thighpouches", "pouches"}));
            remove_name("pack");
            add_adj("thigh");
            break;
        case "belt-sheath":
            add_name(({"sheath", "_daronius_wep_holder"}));
            remove_name("pack");
            add_adj("belt");
            break;
        case "boot-sheath":
            add_name(({"sheath", "_daronius_wep_holder"}));
            remove_name("pack");
            add_adj("boot");
            break;
        case "forearm-sheath":
            add_name(({"sheath", "_daronius_wep_holder"}));
            remove_name("pack");
            add_adj("forearm");
            break;
        case "thigh-sheath":
            add_name(({"sheath", "_daronius_wep_holder"}));
            remove_name("pack");
            add_adj("thigh");
            break;
        case "wrist-sheath":
            add_name(({"sheath", "_daronius_wep_holder"}));
            remove_name("pack");
            add_adj("wrist");
            break;
        case "bandeleria":
            remove_name("pack");
            add_name(({"bandolier", "band", "_daronius_wep_holder",
                "_Shadow_Union_knifeholder"}));
            break;
        case "back-holster":
            add_name(({"holster", "_daronius_wep_holder"}));
            remove_name("pack");
            add_adj("back");
            break;
        case "side-holster":
            add_name(({"holster", "_daronius_wep_holder"}));
            remove_name("pack");
            add_adj("side");
            break;
        case "scabbard":
            add_name("_daronius_wep_holder");
            remove_name("pack");
            break;
        default:
    }
    return;
}

/*
 * Function name: wear_me
 * Description:   wear this item
 * Returns:       string - error message (failure)
 *                1 - success
 */
public mixed
wear_me()
{
    string what1 = TO->short();

    if (art == "lootsack" || art == "sack")
    { return C(what1) + "s are not for wearing, friend.\n"; }

    if (art == "saddlebag")
    { return "Saddlebags are for draping on pack animals, friend.\n"; }
    
    if (parse_command(art, ({}), "'belt-sheath' / 'belt-pouch' / 'scabbard'"))
    {
        object belt = TP->query_armour(A_WAIST);

        if (!belt)
        { return "You need to be wearing a belt to wear that, friend.\n"; }
    }

    if (parse_command(art, ({}), "'boot-sheath'"))
    {
        object boot = TP->query_armour(A_FEET);

        if (!boot)
        { return "You need to be wearing boots to wear that, friend.\n"; }
    }

    
    ::wear_me();
    return 1;
}

/* 
 * Reject containers of any sort. 
 */
int
prevent_enter(object ob)
{
    if (art == "bandeleria")
    {
        if(ob->query_wt() != W_KNIFE)
        {
            write("Only knives can fit in the bandeleria.\n");
            return 1;
        }
        if (ob->query_prop(OBJ_I_BROKEN))
        {
            write("The bandeleria cannot hold broken items.\n");
            return 1;
        }
    }
        
    return ::prevent_enter(ob);
}

int
restore_no_ins(string artme)
{
    if (artme == "bandeleria")
    {
    add_prop(CONT_M_NO_INS, "Try <dsheathe/fill> instead.\n");
    }
    else if (parse_command(artme, ({}), "'wrist-sheath' / 'thigh-sheath' / 'boot-sheath' / 'belt-sheath' / 'forearm-sheath' / 'scabbard'"))
    {
    add_prop(CONT_M_NO_INS, "Try <dsheathe> instead.\n");
    }
    else
    {
    add_prop(CONT_M_NO_INS, "Try <dholster> instead.\n");
    }
    cont_alarm = 0;
    return 1;
}

/* 
 * item_filter, used to filter out certain objects when shifting stuff 
 * in or out of pack, like non-sellables, non-droppables, 
 * containers etc. 
 */
int
item_filter(object ob)
{
    if (art == "bandeleria")
    {
        remove_prop(CONT_M_NO_INS);

        if (!cont_alarm)
        {
            cont_alarm = set_alarm(1.0, 0.0, &restore_no_ins(art));
        }
        
        return !((ob->query_wt() !=W_KNIFE) ||
                (ob->query_prop(OBJ_M_NO_GIVE)) ||
                (ob->query_prop(OBJ_M_NO_DROP)) ||
                (!(ob->query_prop(OBJ_I_VALUE))) ||
                (ob->query_prop(CONT_I_IN)) || /* containers */
                (ob->query_worn()) ||
                (ob->query_wielded()) ||
                (ob->query_held()) ||
                (ob->query_prop(LIVE_I_IS)) ||
                (ob->query_prop(OBJ_I_HAS_FIRE)) ||
                (ob->id("message")) ||
                (ob->id("note")) ||
                !CAN_SEE(TP, ob));
    }

    return !((ob->query_prop(OBJ_M_NO_SELL)) ||
         (ob->query_prop(OBJ_M_NO_GIVE)) ||
         (ob->query_prop(OBJ_M_NO_DROP)) ||
         (!(ob->query_prop(OBJ_I_VALUE))) ||
         (ob->query_prop(CONT_I_IN)) || /* containers */
         (ob->query_worn()) ||
         (ob->query_wielded()) ||
         (ob->query_held()) ||
         (ob->query_prop(LIVE_I_IS)) ||
         (ob->query_prop(OBJ_I_HAS_FIRE)) ||
         (ob->id("message")) ||
         (ob->id("note")) ||
         !CAN_SEE(TP, ob));
}

public void
pack_fill_hook(object *moved)
{
    if (art == "bandeleria")
    {
        write("You sheathe " + COMPOSITE_DEAD(moved) + " in your " + short()
        + ".\n");
        tell_room(E(TP), QCTNAME(TP) + " sheathes " + COMPOSITE_DEAD(moved)
        + " in " + HIS(TP) + " " + short() + ".\n", TP);
        return;
    }

    ::pack_fill_hook(moved);
    return;
}

public void
pack_empty_hook(object *moved)
{
    if (art == "bandeleria")
    {
        write("You draw " + COMPOSITE_DEAD(moved) + " from your " + short()
        + ".\n");
        tell_room(E(TP), QCTNAME(TP) + " draws " + COMPOSITE_DEAD(moved)
        + " from " + HIS(TP) + " " + short() + ".\n", TP);
        return;
    }

    ::pack_empty_hook(moved);
    return;
}


void
init()
{
    ::init();

    if (!art)
    {
        return;
    }

    if (parse_command(art, ({}), "'wrist-sheath' / 'thigh-sheath' / 'boot-sheath' / 'belt-sheath' / 'forearm-sheath' / 'scabbard' / 'bandeleria'"))
    {
        ADA("dsheathe");
        ADA("ddraw");
        ADA("bow");
        ADA("curtsey");
        ADA("pose");
        ADA("help");
    }

    if (parse_command(art, ({}), "'side-holster' / 'back-holster'"))
    {
        ADA("dholster");
        ADA("ddraw");
        ADA("bow");
        ADA("curtsey");
        ADA("pose");
        ADA("help");
    }

    if (art == "lootsack")
    {
        ADA("sackloot");
        ADA("sackdump");
    }

    ADD("exa_seal", "exa");
    ADD("exa_seal", "examine");
}

int
dsheathe(string str)
{
    string *strhold, holdername, wepstr;
    object wep, holder, *inme;

    NF("Sheathe what in what?\n");
    if (!str)
        return 0;

    if (!sscanf(str, "%s in %s", wepstr, holdername))
        return 0;

    if (!(wep = present(wepstr, TP)))
        return 0;

    NF("Sheathe your " + wepstr + " in what?\n");
    if (!(holder = present(holdername, TP)))
        return 0;

    strhold = holder->query_names();
    inme = all_inventory(holder);

    if (IN_ARRAY("scabbard", strhold))
    {
        string holdisplay = holder->short();
        string wepdisplay = wep->short();

        NF("Only swords may be sheathed in your " + holdisplay + ".\n");
        if (wep->query_wt() != W_SWORD)
            return 0;

        NF("There is already a sword in your " + holdisplay + ".\n");
        if (sizeof(inme) != 0)
            return 0;

        holder->remove_prop(CONT_M_NO_INS);
        if(wep->move(holder))
        {
            write("Your " + holdisplay + " is already full.\n");
            return 1;
        }

        holder->restore_no_ins(strhold[0]);
        write("You slide your " + wepdisplay + " into your " 
        + holdisplay + " quietly.\n");
        say(QCTNAME(TP) + " slides " + HIS(TP) + " " + wepdisplay
        + " into " + HIS(TP) + " " +holdisplay + " quietly.\n");
        return 1;
    }
    
    else if (IN_ARRAY("sheath", strhold) || IN_ARRAY("bandeleria", strhold))
    {
        string holdisplay = holder->short();
        string wepdisplay = wep->short();

        NF("Only knives may be sheathed in your " + holdisplay + ".\n");
        if (wep->query_wt() != W_KNIFE)
            return 0;

        NF("There is already a knife in your " + holdisplay + ".\n");
        if (sizeof(inme) != 0 && art != "bandeleria")
            return 0;

        holder->remove_prop(CONT_M_NO_INS);
        if(wep->move(holder))
        {
            write("Your " + holdisplay + " is already full.\n");
            return 1;
        }

        holder->restore_no_ins(strhold[0]);
        write("You sheathe your " + wepdisplay + " in your " 
        + holdisplay + " silently.\n");

        if (!IN_ARRAY("wrist-sheath", strhold))
        say(QCTNAME(TP) + " slides " + HIS(TP) + " " + wepdisplay
        + " into " + HIS(TP) + " " + holdisplay + " silently.\n");
        return 1;
    }

    else if (IN_ARRAY("side-holster", strhold) || IN_ARRAY("back-holster", strhold))
    {
        write("You cannot sheathe weapons in a " + holdername + " like "
        + "that.\n");
        return 1;
    }
    
    else
        write(C(holdername) + "s cannot be used like that.\n");
        return 1;
}

int
dholster(string str)
{
    string *strhold, holdername, wepstr;
    object wep, holder, *inme;

    NF("Holster what in what?\n");
    if (!str)
        return 0;

    if (!sscanf(str, "%s in %s", wepstr, holdername))
        return 0;

    if (!(wep = present(wepstr, TP)))
        return 0;

    NF("Holster your " + wepstr + " in what?\n");
    if (!(holder = present(holdername, TP)))
        return 0;

    strhold = holder->query_names();
    inme = all_inventory(holder);

    if (IN_ARRAY("scabbard", strhold) || IN_ARRAY("sheath", strhold))
    {
        write("You cannot holster weapons in a " + holdername + " like "
        + "that.\n");
        return 1;
    }
    

    else if (IN_ARRAY("side-holster", strhold))
    {
        string holdisplay = holder->short();
        string wepdisplay = wep->short();

        NF("Only axes and clubs may be sheathed in your " + holder->short()
        + ".\n");
        if (wep->query_wt() != W_CLUB && wep->query_wt() != W_AXE)
            return 0;

        NF("There is already a weapon in your " + holder->short() + ".\n");
        if (sizeof(inme) != 0)
            return 0;

        holder->remove_prop(CONT_M_NO_INS);
        if(wep->move(holder))
        {
            write("Your " + holdisplay + " is already full.\n");
            return 1;
        }

        holder->restore_no_ins(strhold[0]);
        write("You holster your " + wepdisplay + " in your "
        + holdisplay + ".\n");
        say(QCTNAME(TP) + " holsters " + HIS(TP) + " " + wepdisplay
        + " in " + HIS(TP) + " " + holdisplay + ".\n");
        return 1;
    }

    else if (IN_ARRAY("back-holster", strhold))
    {
        string holdisplay = holder->short();
        string wepdisplay = wep->short();

        NF("Only axes, clubs, polearms, and bows may be sheathed in your "
        + holder->short() + ".\n");
        if (wep->query_wt() != W_CLUB && wep->query_wt() != W_AXE
            && wep->query_wt() != W_POLEARM && wep->query_wt() != W_MISSILE)
            return 0;

        NF("There is already a weapon in your " + holdisplay + ".\n");
        if (sizeof(inme) != 0)
            return 0;

        holder->remove_prop(CONT_M_NO_INS);
        if(wep->move(holder) == 1)
        {
            write("Your " + holdisplay + " can't hold something that heavy.\n");
            return 1;
        }
        else if(wep->move(holder) == 8)
        {
            write("Your " + holdisplay + " can't hold something that big.\n");
            return 1;
        }
        else
        {
            write("Your " + holdisplay + " is already full.\n");
            return 1;
        }

        holder->restore_no_ins(strhold[0]);
        write("You holster your " + wepdisplay + " in your "
        + holdisplay + ".\n");
        say(QCTNAME(TP) + " holsters " + HIS(TP) + " " + wepdisplay
        + " in " + HIS(TP) + " " + holdisplay + ".\n");
        return 1;
    }

    else
        write(C(holdername) + "s can't be used like that.\n");
        return 1;
}

int
ddraw(string str)
{
    string *strhold, holdername, wepstr, holdstr;
    object wep, holder, *inme;
    mixed ddo;

    NF("Draw from what weapon holder?\n");
    if (!str)
        return 0;

    NF("Draw from what, friend?\n");
    if (!sscanf(str, "from %s", holdername))
        return 0;

    NF("Draw from what?\n");
    if (!(holder = present(holdername, TP)))
        return 0;

    strhold = holder->query_names();
    holdstr = holder->short();

    NF("Your " + holdstr + " is empty.\n");
    if (sizeof(inme = all_inventory(holder)) == 0)
        return 0;

    wep = inme[0];
    wepstr = wep->short();

    if (TP->query_tool(W_BOTH))
    {
        NF("Your hands are too full to draw from that.\n");
        return 0;
    }
    else
    {
        switch (wep->query_hands())
        {
            case W_LEFT:
                if (TP->query_tool(W_LEFT))
                {
                    NF("Your left hand is already occupied.\n");
                    return 0;
                }
                break;
            case W_RIGHT:
                if (TP->query_tool(W_RIGHT))
                {
                    NF("Your right hand is already occupied.\n");
                    return 0;
                }
                break;
            case W_BOTH:
                if ((TP->query_tool(W_RIGHT)) || (TP->query_tool(W_LEFT)))
                {
                    NF("You haven't enough space in your hands to draw "
                    + "from that.\n");
                    return 0;
                }
                break;
        }
    }
    
    if (strhold[0] == "scabbard")
    {
        TP->catch_msg("You slide your " + wepstr + " from your " + holdstr
        + ".\n");
        tell_room(E(TP), QCTNAME(TP)+ " slides " + HIS(TP) + " " + wepstr
        + " from " + HIS(TP) + " " + holdstr + ".\n", TP);
    }

    else if (strhold[0] == "wrist-sheath")
    {
        TP->catch_msg("You quietly slip your " + wepstr + " from your "
        + holdstr + ".\n");
    }

    else
    {
        TP->catch_msg("You draw your " + wepstr + " from your " + holdstr
        + ".\n");
        tell_room(E(TP), QCTNAME(TP)+ " draws " + HIS(TP) + " " + wepstr
        + " from " + HIS(TP) + " " + holdstr + ".\n", TP);
    }


    if (wep->move(TP))
        wep->move(TP, 1);
    
    if (stringp(ddo = wep->command_wield()))
        write(ddo);

    return 1;
}

/* This section is dedicated to the lootsack which is an inspired
 * descendant of the mighty orc sack of moria. Hail Gondor!
 */

int
is_corpse(object what)
{
    return !living(what) && what->query_prop(CONT_I_IN);
}

int
is_sack(object what)
{
    return what->id("lootsack");
}

int
sackloot(string arg)
{
    mixed  *obs;
    object *loot;
    string rest;
    object sack;

    NF("Usage: " + query_verb() +" <corpse> [with <sack>]\n");

    if (E(TO) != TP)
    return NF("You must hold the sack to loot corpses.\n");

    if (!strlen(arg))
        arg = "corpse";

    if (parse_command(arg, inventory(E(TP)),
               "%i 'in' / 'into' / 'with' / 'using' [the] %s", 
              obs, rest))
    {
        loot = VISIBLE_ACCESS(obs, "is_corpse", TO);
        if (!parse_command(rest, inventory(TP), "[the] %i", obs))
        return NF("Loot it into which sack?\n");
        obs = VISIBLE_ACCESS(obs, "is_sack", TO);
        if (!sizeof(obs))
        return NF("Which sack do you mean?\n");
        if (sizeof(obs) > 1)
        return NF("Only one sack at a time please..\n");
        sack = obs[0];
        return sack->do_loot_one(loot, rest);
    }
    else {
    loot = IM_PARSE_FILE->parse_environment_items(arg, "");
    if (!sizeof(loot))
        return 0;
    loot = filter(loot, "is_corpse", TO); 
    if (!sizeof(loot))
        return 0;
    return TO->do_loot_one(loot, "lootsack");
    }
}

int move_to(object what)
{
    if (!objectp(what))
      return 0;
    if( what->move(TO) != 0 )
      return 0;

    return 1;
}

int
do_loot_one(object *loot, string name)
{   
    int i, j;
    object *thing;
    object *got;

    if (query_prop(CONT_I_CLOSED))
    return NF("Perhaps open the " + name + " first?\n");

    i=sizeof(loot);

    if (!i)
    return 0;

    write("You loot " + COMPOSITE_DEAD(loot) + " using your "+name+".\n");
    say(QCTNAME(TP) + " starts looting " + QCOMPDEAD + ".\n");

    while (i--) {
    if (!objectp(loot[i]))
        continue;

    thing = all_inventory(loot[i]);
    j = sizeof(thing);

    if (!j) {
        write("The " + loot[i]->short() + " is empty.\n");
        continue;
    }

    got = filter(thing, "move_to", TO);

    if (!sizeof(got)) 
        write("You couldn't loot anything from the " + loot[i]->short()
        + ".\n");
    else {
        write("You dump " + COMPOSITE_DEAD(got) + " from the " + 
          loot[i]->short() + " into your " + name + ".\n");
        say(QCTNAME(TP) + " dumps " + QCOMPDEAD + " from the " +
        loot[i]->short() + " into " + HIS(TP) + " lootsack.\n");
    }
    }
    return 1;
}

int
sackdump(string arg)
{
    object *objs;
    mixed *sacks;
    int i, r=0;

    NF("Usage: " + query_verb() + " <sack>\n");
    
    if (!strlen(arg) || !arg)
        arg = "lootsack";
    
    if (!parse_command(arg, inventory(TP), "%i", sacks))
        return 0;

    sacks = VISIBLE_ACCESS(sacks, "is_sack", TO);
    if (!sacks)
        return NF(C(query_verb()) + " which sacks?\n");

    for (i=0; i<sizeof(sacks); i++)
    if (sacks[i]->do_empty_sack())
        r = 1;
    return r;
}

int
do_empty_sack()
{
    if (query_prop(CONT_I_CLOSED))
        return NF("Perhaps open the lootsack first?\n");

    if(!sizeof(all_inventory(TO)))
        return NF("The lootsack is already empty.\n");

    write("You dump out the sack and drop " + COMPOSITE_DEAD(all_inventory(TO)) + ".\n");
    say(QCTNAME(TP) + " drops " + QCOMPDEAD + " from a sack.\n");
    
    all_inventory(TO)->move(E(TP));
    return 1;
}
/*    ----------------------  END  SACKLOOT  ----------------------    */


int exa_seal(string arg)
{
    if (!strlen(arg) || !parse_command(arg, ({}), "[the] [circular] 'seal' "))
    {
        return 0; // the player used syntax we don't agree with 
    }
    
    write("Stamped into the tanned material with an indention press while "
    + "it was still fresh is a circular seal with a pair of fourteen point "
    + "antlers above \"Palanthas\" written in the old style. Try <help "
    + "daronius2>.\n");
    return 1;
}

/* Overriding emote 'bow' while wearing certain articles.
 */
int bow(string str)
{
    string *how;
    object *oblist;
    how = parse_adverb_with_space(str, "lithely", 0);
    oblist = parse_this(how[0], "[to] %l");

    if (TO->query_worn() && IN_ARRAY(art, ({"suit", "coat", "breastplate",
        "cuirasse", "vest"})))
    {
        if (!sizeof(oblist))
        { 
            write("You bow" + how[1] + ", the " + cus + " " + matmore
            + " of your " + colmore + " " + artmore + " " + soundmore
            + ".\n");
            allbb(" bows" + how[1] + ", the " + cus + " " + matmore
            + " of " + HIS(TP) + " " + colmore + " " + artmore + " "
            + soundmore + ".");
            return 1;
        }

        actor("You bow to", oblist, how[1] + ", the " + cus + " " + matmore
        + " of your " + colmore + " " + artmore + " " + soundmore + ".");
        target(" bows to you" + how[1] + ", the " + cus + " " + matmore
        + " of " + HIS(TP) + " " + colmore + " " + artmore + " " + soundmore
        + ".", oblist);
        all2act(" bows to", oblist, how[1] + ", the " + cus + " " + matmore
        + " of " + HIS(TP) + " " + colmore + " " + artmore + " " + soundmore
        + "."); 
        return 1;
    }
    return 0;
}

/* Overriding emote 'curtsey' for anyone wearing a certain article.
 */
int curtsey(string str)
{
    string *how;
    object *oblist;
    how = parse_adverb_with_space(str, "smoothly", 0);
    oblist = parse_this(how[0], "[to] %l");

    if (TO->query_worn() && IN_ARRAY(art, ({"suit", "coat", "breastplate",
        "cuirasse", "vest", "leggings", "tall-boots", "greaves"})))
    {
        if (!sizeof(oblist))
        { 
            write("You curtsey" + how[1] + ", the " + cus + " "
            + matmore + " of your " + colmore + " " + artmore + " "
            + soundmore + ".\n");
            allbb(" curtseys" + how[1] + ", the " + cus + " "
            + matmore + " of " + HIS(TP) + " " + colmore + " " + artmore
            + " " + soundmore + ".");
            return 1;
        }

        actor("You curtsey to", oblist, how[1] + ", the " + cus + " "
        + matmore + " of your " + colmore + " " + artmore + " " + soundmore
        + ".");
        target(" curtseys to you" + how[1] + ", the " + cus + " "
        + matmore + " of " + HIS(TP) + " " + colmore + " " + artmore + " "
        + soundmore + ".", oblist);
        all2act(" curtseys to", oblist, how[1] + ", the " + cus + " "
        + matmore + " of " + HIS(TP) + " " + colmore + " " + artmore + " "
        + soundmore + "."); 
        return 1;
    }
    return 0;
}

/* New emote 'pose' for anyone wearing one of these armours.
 */
int pose(string str)
{
    string *how;
    how = parse_adverb_with_space(str, "magnificently", 0);

    if (TO->query_worn())
    {
        write("With hands on hips you pose" + how[1] + " in your " + artmore
        + ", its " + cus + " " + colmore + " " + matmore + " " + soundmore
        + ".\n");
        say("With hands on hips " + QTNAME(TP) + " poses" + how[1] + " in "
        + HIS(TP) + " " + artmore + ", its " + cus + " " + colmore + " " 
        + matmore + " " + soundmore    + "\n.");
        return 1;
    }
    return 0;
}

int
help(string str)
{
    if (!str || str != "daronius2")
        return 0;

    write("You may do the following in certain Daronius crafted items:\n"
    + "bow <adj> to <person>      - Perform a bow in your item.\n"
    + "curtsey <adj> to <person>  - Curtsey in your item.\n"
    + "pose <adj>                 - Strike a pose in your Daronius item.\n"
    + "\n");
    return 1;
}

/* Ensure here that the player removes the pack first if 
 * it leaves his/her inventory. */
void
leave_env(object old, object dest)
{
    ::leave_env(old, dest);

    wearable_item_leave_env(old, dest);
}

// Ensure that the player can properly appraise this item. 
void
appraise_object(int num)
{
    ::appraise_object(num);

//    appraise_wearable_item();
}

string
query_recover()
{
    return MASTER + ":" + recover_string;
}

void
init_recover(string arg)
{
    ::init_keep_recover(arg);
    set_general_data(arg);
}
