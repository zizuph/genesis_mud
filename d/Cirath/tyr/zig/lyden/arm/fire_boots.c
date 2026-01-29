/* fire_boots.c created by Meton.
*   Inspired by fire_gloves by Shiva
*
*   2021-10-31 Meton and Zizuph, upgraded to new unarmed_enhancer
*   2021-11-07 Meton Added keep function
*   2021-12-02 Ckrik Removed use of shadow since boots don't need it
*/

inherit "/std/unarmed_enhancer";

#include "../local.h"
#include <wa_types.h>
#include <files.h>

#define MIN_FIRE_SKILL 15
#define MANA_USED 5

string flame_short();
string flame_adj();
mixed start_bmana_drain();

int bflames = 0;

void
create_unarmed_enhancer()
{
    set_name("boots");
    set_pname("boots");
  
    set_adj(flame_adj);
    add_adj("gold");
    add_adj("pair of");
  
    set_short(flame_short);
    set_pshort(flame_short);
    
    set_default_enhancer(45, 47, W_BLUDGEON, 5, A_FEET, ({ -2, 0, 2 }), this_object());

    set_long("A heavy pair of boots with thin threads of real gold " +
	    "woven into them.\n@@flame_long@@");
    add_item(({"threads", "thin threads", "thin golden threads",
        "golden threads", "woven threads", "thin golden woven threads",
        "thin woven threads", "golden woven threads"}),
        "The thin golden threads woven into the boots gives off an aura "
        + "of magic.\n");

    add_prop(OBJ_I_IS_MAGIC_ARMOUR, 1);
    add_prop(MAGIC_AM_MAGIC, ({ 40, "enchantment", 40, "fire" }));
    add_prop(MAGIC_AM_ID_INFO, ({
	    "The boots are apparently enchanted with fire magic.\n", 5,
        "When worn by someone trained in Cirathian fire magic the "
        + "boots can produce flames when the wearer is "
        + "attuned to their magic.\n", 15,
        "When the wearer attunes to the boots, they create fire for a "
        + "preserver and dark fire for a defiler.\n", 30}));
    add_prop(OBJ_S_WIZINFO, "When worn, each boot can flames, " +
	    "which cause extra MAGIC_DT damage and produce 1 level of " +
        "light for each foot. " +
        "Wearer must be defiler/preserver, chosen in Cirath, and have fire magic skills < 15, and 10 mana to activate boots.\n");

    add_prop(OBJ_I_VALUE, 2000);
    add_prop(OBJ_I_WEIGHT, 400);
    add_prop(OBJ_I_VOLUME, 200);
    set_keep(1);
}

init()
{
    ::init();
    add_action("attune","attune");
}

/*
*   Function name: flame_short
*   Description  : Give a special short desc when the boots are flaming.
*   Returns      : description
*/
string
flame_short()
{
    if (bflames)
    {
        return "pair of flaming gold boots";
    }
  
    return "pair of gold boots";
}

/*
*   Function name: flame_adj
*   Description  : Adj if flaming
*   Returns      : description
*/
string
flame_adj()
{
    if (bflames)
    {
        return "flaming";
    }
  
    return "";
}

/*
*   Function name: flame_long
*   Description  : adds description when flaming
*   Arguments    : 
*   Returns      : description
*/
string
flame_long()
{
    if (!bflames)
    {
        return "";
    }
    return "Flames surround the boots.\n";
}

/*
*   Function name: attune
*   Description  : Activates the magical item
*   Arguments    : 
*   Returns      : 
*/
int
attune(string s)
{
    NF("Attune yourself to what? The boots?\n");
    // status worn, active, mana, skill, preserver/defiler
    if(!s || s != "boots")
    {
        return 0;
    }
    if (!TO->query_worn())
    {
        write("You must wear the " + short() + " first.\n");
        return 1;
    }
    if(bflames)
    {
        write("You are already attuned to the boots.\n");
        return 1;
    }
    if (TP->query_mana() < 10)
    {
        write("You focus on the magic, but lack the mana for "
            + "the task.\n");
        return 1;
    }
    if(TP->query_skill(SS_ELEMENT_FIRE) < MIN_FIRE_SKILL)
    {
        write("The type of magic flowing through the boots are too "
            + "unknown for you.\n");
       return 1;
    }

    if (!TP->query_prop(C_I_AM_DEFILER) && !TP->query_prop(C_I_AM_PRESERVER))
    {
        write("You are not focused on the Cirathian magic style like the "
            + "boots.\n");
            return 1;
    }
    // Activates boots
    
    bflames = 2;
    write("You focus on the magical power emitting from the "
        + "golden threads, and find yourself attuned to the boots. "
        + "Changing your equipment would break this mental bond to the "
        + "boots.\n");
    TP->add_mana(-10);
    
// Creates the "fire". Dark fire if defiler, and regular if preserver.
// Can only reach if have one prop, so only checking if defiler.
    if (TP->query_prop(C_I_AM_DEFILER))
    {
        //reversing polarity of bflames if defiler.
        bflames = 0 - bflames;
        add_prop(OBJ_I_LIGHT, query_prop(OBJ_I_LIGHT) + bflames);
        add_prop(OBJ_I_HAS_FIRE, 1);
        say("A fiery darkness emerges around the boots " + QNAME(TP)
            + " is wearing, and your surroundings grow dimmer.\n");
        write("Harsh hot fiery darkness surrounds the boots, as you "
            + "force the magic to suck in light around you.\n");
        return 1;
    }
    add_prop(OBJ_I_LIGHT, query_prop(OBJ_I_LIGHT) + bflames);
    add_prop(OBJ_I_HAS_FIRE, 1);
    say("Flames emerge around the boots "+ QNAME(TP) + " is wearing.\n");
    write("Hot flames emerger from the boots, covering them.\n");
    set_alarm(3.0, 0.0, &start_bmana_drain());
    return 1;
}

/*
*   Function name: remove_flames
*   Description  : removes magic effect
*   Arguments    : 
*   Returns      : 
*/
int remove_flames()
{
    /* Removing negative or positive bflames, can't check player prop as
        that could be changed after attuning boots */
    if (bflames < 0)
    {
        add_prop(OBJ_I_LIGHT, query_prop(OBJ_I_LIGHT) - bflames);
        add_prop(OBJ_I_HAS_FIRE, 1);
        say("The black flames surrounding " + QNAME(TP) + "s boots "
            + "disappears, and your surroundings seem less dark.\n");
        write("The black flames surrounding the boots flickers and "
            + "disappears, and your surroundings seem less dark.\n");
    }

    if (bflames > 0)
    {
        add_prop(OBJ_I_LIGHT, query_prop(OBJ_I_LIGHT) - bflames);
        add_prop(OBJ_I_HAS_FIRE, 1);
        say("The hot flames surrounding " + QNAME(TP) + "s boots "
            + " flickers and dies out.\n");
        write("The hot flames surrounding the boots flickers and dies "
            + "out.\n");
    }

    bflames = 0;
}

/*
*   Function name: remove
*   Description  : Calls to remove magic effect
*   Arguments    : 
*   Returns      : 
*/
int
remove()
{
    remove_flames();
    return 0;
}

/*
*   Function name: burn_description
*   Description  : description based on values of hurt
*   Arguments    : hurt value
*   Returns      : string of description
*/
string
burn_description(int hurt)
{
    string burn;
    switch (hurt)
    {
    case 0..10:
    burn = " singeing ";
    break;
    case 11..30:
    burn = " searing ";
    break;
    case 31..70:
    burn = " blistering ";
    break;
    default:
    burn = " charring ";
    break;
    }
    return burn;
}

/*
*   Function name: fire_damage
*   Description  : Calculates fire damage lvls
*   Arguments    : 
*   Returns      : hurt value
*/
int
fire_damage(object enemy)
{
    int hurt;
    wearer = query_worn();

    int res, fire_dam;
    // Is fire damage possible in our environment.
    if (environment(wearer)->query_prop(ROOM_M_NO_MAGIC) ||
        enemy->query_prop(OBJ_M_NO_MAGIC) ||
        (environment(wearer)->query_prop(ROOM_I_TYPE) == ROOM_UNDER_WATER))
    {
        return 0;
    }

    /* calculate damage, taking fire resistance into account */
    res = 100 - max(enemy->query_magic_res(MAGIC_I_RES_FIRE),
    enemy->query_magic_res(MAGIC_I_RES_MAGIC));
    
    if (wearer->query_weapon(W_LEFT) ||
        wearer->query_weapon(W_RIGHT) ||
        wearer->query_weapon(W_BOTH))
    {
        /*  AG is 20, merc can do 30, caster guilds got 100.
        *   so evaluated dmg for melee classes is 6-8 and caster up to 26
        */
        fire_dam = (wearer->query_skill(SS_ELEMENT_FIRE) / 4) + 1;
    }
    else
    {
        fire_dam = random(45 + wearer->query_skill(SS_ELEMENT_FIRE) / 10)
        + 1;
    }

    fire_dam = fire_dam * res / 100;
    hurt = enemy->hit_me(fire_dam, MAGIC_DT, wearer, -1)[0];

    if (hurt > 0)
    {
        wearer->add_panic(-3 - hurt / 5);
    }

    return hurt;
}

/*
*   Function name: special_damage
*   Description  : Adds fire damage to hits
*   Arguments    : 
*   Returns      : 
*/
int
special_damage(int aid, string hdesc, int phurt, object enemy, int phit,
    int dam)
{
    string with, where, how, what, owhat, burn;
    int hurt;
    object wearer;
  
    /* make sure we hit with a flaming boots */
    if (!bflames)
    {
        return 0;
    }

    // Make sure we're wearing the boot
    wearer = query_worn();
    if (!objectp(wearer) || environment(this_object()) != wearer)
    {
        remove_flames();
        return 0;
    }
 
    /* give an attack description */
    with = (random(1) ? " right foot" : " left foot");
  
    where = " the " + hdesc + " of ";

    switch (phurt)
    {
        case 0..4:
        how = "";
        what = "tickle";
        owhat = "tickles";
        break;
        case 5..9:
        how = "";
        what = "graze";
        owhat = "grazes";
        break;
        case 10..19:
        how = "";
        what = "hurt";
        owhat = "hurts";
        break;
        case 20..29:
        how = ", rather bad";
        what = "hurt";
        owhat = "hurts";
        break;
        case 30..49:
        how = ", very bad";
        what = "hurt";
        owhat = "hurts";
        break;
        case 50..69:
        how = ", very hard";
        what = "smash";
        owhat = "smashes";
        break;
        case 70..89:
        how = ", with a bone crushing sound";
        what = "smash";
        owhat = "smashes";
        where = " ";
        break;
        default:
        how = "";
        what = "massacre";
        owhat = "massacres";
        where = " ";
    }

    hurt = fire_damage(enemy);
    burn = burn_description(hurt);

    // unarmed descriptions
    wearer->catch_tell("You " + what + where + 
        enemy->query_the_name(wearer) + " with your" + with + how +
        ", your boot" + burn + enemy->query_objective() + ".\n");
    enemy->catch_tell(wearer->query_The_name(enemy) + " " + owhat + 
        " your " + hdesc + " with " + wearer->query_possessive() +
        with + how + ", " + wearer->query_possessive() + " boot" +
        burn + "you.\n");
    wearer->tell_watcher(QCTNAME(wearer) + " " + 
        owhat + where + QTNAME(enemy) + " with " + 
        wearer->query_possessive() + with + how + ", " +
        wearer->query_possessive() + " boot" + burn + 
        enemy->query_objective() + ".\n", enemy);

    return 1;
}

public varargs int
did_hit(int aid, string hdesc, int phurt, object enemy, int dt, int phit, int dam)
{
    /* Match behavior of glove shadows */
    if ((phurt < 0) && (dam <= 20))
    {
        return 0;
    }
    return special_damage(aid, hdesc, phurt, enemy, phit, dam);
}

/*
*   Function name: start_mana_drain
*   Description  : drains mana every 60 seconds
*   Arguments    : 
*   Returns      : 
*/
mixed
start_bmana_drain()
{
    if (TP->query_mana() < MANA_USED)
    {
        // Ran out of mana to sustain the flames
        remove_flames();
        return;
    }
    if (!bflames)
        return;

    TP->add_mana(-MANA_USED);
    set_alarm(60.0, 0.0, &start_bmana_drain());
    return;
}
