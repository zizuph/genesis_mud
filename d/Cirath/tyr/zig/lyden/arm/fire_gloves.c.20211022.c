/* fire_gloves.c created by Shiva@Genesis. 
*
*   Recoded by Meton 2020.
*   removed the destruct on drop, as gloves were being
*   ignored.
*
*   added gloves working while wearing and wielding things
*   Flames spread from gloves to shields/weapons.
*
*   Changed function from flame on wearing, to player activated.
*/

inherit "/std/armour";

#include "../local.h"
#include <wa_types.h>
#include <files.h>

#define FLAMES_SHADOW (OBJ + "fire_glove_sh")
#define EQUIPPED_FLAMES_SHADOW (OBJ + "equipped_flames_sh")

#define MIN_FIRE_SKILL 15

string flame_short();
string flame_adj();
int fire_damage(object enemy);
mixed burn_description(int hurt);
mixed armed_hit(string with, object enemy);
mixed flame_shield_hit(object enemy);
mixed flame_items(object ob);
mixed start_mana_drain();

static int flames, flames_attack_id, hurt;
static object wearer;
static string burn;

int hurt,phurt;
object enemy;
string hdesc;

int flames = 0;

void
create_armour()
{
    set_name("gloves");
    set_pname("gloves");
  
    set_adj(flame_adj);
    add_adj("gold");
    add_adj("pair of");
  
    set_short(flame_short);
    set_pshort(flame_short);
  
    set_at(A_HANDS);
    set_ac(35);
    set_am(({ -2, 0, 2 }));
    set_af(this_object());
  
    set_long("A heavy pair of gloves with thin threads of real gold "
        + "woven into them.\n@@flame_long@@");
    add_item(({"threads", "thin threads", "thin golden threads",
        "golden threads", "woven threads", "thin golden woven threads",
        "thin woven threads", "golden woven threads"}),
        "The thin golden threads woven into the gloves gives off an aura "
        + "of magic.\n");

    add_prop(OBJ_I_IS_MAGIC_ARMOUR, 1);
    add_prop(MAGIC_AM_MAGIC, ({ 40, "fire" }));
    add_prop(MAGIC_AM_ID_INFO, ({
	    "The gloves are apparently enchanted with fire magic.\n", 5,
        "When worn by someone trained in Cirathian fire magic the "
        + "gloves can produce flames when the wearer is "
        + "attuned to their magic.\n", 15,
        "When the wearer attunes to the gloves, they create fire for a "
        + "preserver and dark fire for a defiler.\n", 30}));
    add_prop(OBJ_S_WIZINFO, "When worn, each glove can flames, " +
        "which cause extra MAGIC_DT damage and produce 1 level of " +
        "light or darkness for each hand and object in hand." +
        "Wearer must be defiler/preserver, chosen in Cirath, and have fire magic skills < 15, and 10 mana to activate gloves.\n");

    add_prop(OBJ_I_VALUE, 2000);
    add_prop(OBJ_I_WEIGHT, 400);
    add_prop(OBJ_I_VOLUME, 200);
}

init()
{
    ::init();
    add_action("attune","attune");
}

/* Give a special short desc when the gloves are flaming. */
string
flame_short()
{
    if (flames)
    {
        return "pair of flaming gold gloves";
    }
  
    return "pair of gold gloves";
}

/* add the "flaming" adj when they're flaming. */
string
flame_adj()
{
    if (flames)
    {
        return "flaming";
    }
  
    return "";
}

/* Special long when flaming. */
string
flame_long()
{
    if (!flames)
    {
        return "";
    }
    return "Flames surround the gloves.\n";
}

/*
*   function : attune
*   description : Checks status before lighting gloves.
*   
*/

int
attune(string s)
{
    NF("Attune yourself to what? The gloves?\n");
    // status worn, active, mana, skill, preserver/defiler
    if(!s || s != "gloves")
    {
        return 0;
    }

    if (!TO->query_worn())
    {
        write("You must wear the " + short() + " first.\n");
        return 1;
    }

    if(flames)
    {
        write("You are already attuned to the gloves.\n");
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
        write("The type of magic flowing through the gloves are too "
            + "unknown for you.\n");
       return 1;
    }

    // Remember.. If either should be true, use xand, not xor :-)
    if (!TP->query_prop(C_I_AM_DEFILER) && !TP->query_prop(C_I_AM_PRESERVER))
    {
        write("You are not focused on the Cirathian magic style like the "
            + "gloves.\n");
            return 1;
    }

    // Activates gloves, checks hand slots
    flames = 2;

    if (TP->query_tool(W_LEFT) && !(TP->query_tool(W_BOTH)))
    {
        flames +=1;
        object shl,shl2;

        setuid();
        seteuid(getuid());

        shl = clone_object(EQUIPPED_FLAMES_SHADOW);
        shl2 = (TP->query_tool(W_LEFT));
        if (shl->shadow_me(shl2))
        {
            shl2->set_flames_ob(shl2);
            shl2->set_gloves_ob(TO);
            flame_items(shl2);
        }
        else
        {
            shl2->remove_shadow();
        }

    }
    if (TP->query_tool(W_RIGHT) && !(TP->query_tool(W_BOTH)))
    {
        flames +=1;
        object shr,shr2;

        setuid();
        seteuid(getuid());

        shr = clone_object(EQUIPPED_FLAMES_SHADOW);
        shr2 = (TP->query_tool(W_RIGHT));
        if (shr->shadow_me(shr2))
        {
            shr2->set_flames_ob(shr2);
            shr2->set_gloves_ob(TO);
            flame_items(shr2);
        }
        else
        {
            shr->remove_shadow();
        }
    }

    if (TP->query_tool(W_BOTH))
    {
        flames +=2;
        object shb,shb2;

        setuid();
        seteuid(getuid());

        shb = clone_object(EQUIPPED_FLAMES_SHADOW);
        shb2 = (TP->query_tool(W_BOTH));
        if (shb->shadow_me(shb2))
        {
            shb2->set_flames_ob(shb2);
            shb2->set_gloves_ob(TO);
            flame_items(shb2);
           
        }
        else
        {
            shb->remove_shadow();
        }
    }
 
    write("You focus on the magical power emitting from the "
        + "golden threads, and find yourself attuned to the gloves. "
        + "Changing your equipment would break this mental bond to the "
        + "gloves.\n");
    TP->add_mana(-10);
    set_alarm(3.0, 0.0, &start_mana_drain());

// Creates the "fire". Dark fire if defiler, and regular if preserver.
// Can only reach if have either, so only checking if defiler.
    if (TP->query_prop(C_I_AM_DEFILER))
    {
        //reversing polarity of flames if defiler.
        flames = 0 - flames;
        say("A fiery darkness emerges around the gloves " + QNAME(TP)
        + " is wearing, and your surroundings grow dimmer.\n");
        write("Harsh hot black flames surrounds the gloves, as you "
            + "force the magic to absorb light around you.\n");
        // Set prop after msg, as people ought to see who it comes from.
        add_prop(OBJ_I_LIGHT, query_prop(OBJ_I_LIGHT) + flames);
        add_prop(OBJ_I_HAS_FIRE, 1);
        return 1;
    }

    add_prop(OBJ_I_LIGHT, query_prop(OBJ_I_LIGHT) + flames);
    add_prop(OBJ_I_HAS_FIRE, 1);
    say("Flames emerge around the gloves "+ QNAME(TP) + " is wearing.\n");
    write("Hot flames emerger from the gloves, enveloping your hands.\n");
    return 1;
}

/*
*   Function name: wear
*   Description  : Gives shadow when worn
*   Arguments    : 
*   Returns      : 
*/
int
wear()
{
    object sh;
  
    setuid();
    seteuid(getuid());
    if ((sh = clone_object(FLAMES_SHADOW)) &&
	 sh->shadow_me(this_player()))
    { 
        sh->set_gloves_ob(this_object());
        // added to set wearer obj here
        wearer = query_worn();
    }
    else
    {
        sh->remove_shadow();
    }
  
    return 0;
}    

/*
*   Function name: remove_flames
*   Description  : removes magic effect
*   Arguments    : 
*   Returns      : 
*/
int remove_flames()
{
    if (!(flames))
    {
        return 1;
    }

    if (TP->query_tool(W_BOTH))
    {
        TP->query_tool(W_BOTH)->remove_flames_shadow();
    }

    if (TP->query_tool(W_LEFT))
    {   
        TP->query_tool(W_LEFT)->remove_flames_shadow();
    }

    if (TP->query_tool(W_RIGHT))
    {
        TP->query_tool(W_RIGHT)->remove_flames_shadow();
    }

    /*   Removing negative or positive flames, can't check player prop as
        that could be changed after attuning gloves */
    if (flames < 0)
    {
        say("The black flames surrounding " + QNAME(TP) + "s gloves "
            + "disappears, and your surroundings seem less dark.\n");
        write("The black flames surrounding the gloves flickers and "
            + "disappears, and your surroundings seem less dark.\n");
        //Set props afterwards, so people can't see who ends the effect.
        add_prop(OBJ_I_LIGHT, query_prop(OBJ_I_LIGHT) - flames);
        add_prop(OBJ_I_HAS_FIRE, 1);
    }

    //if (TP->query_prop(C_I_AM_PRESERVER))
    if (flames > 0)
    {
        add_prop(OBJ_I_LIGHT, query_prop(OBJ_I_LIGHT) - flames);
        add_prop(OBJ_I_HAS_FIRE, 1);
        say("The hot flames surrounding " + QNAME(TP) + "s gloves "
            + "flickers and dies out.\n");
        write("The hot flames surrounding the gloves flickers and dies "
            + "out.\n");
    }

    flames = 0;

}

/*
*   Function name: remove
*   Description  : Calls to remove magic effect
*   Arguments    : 
*   Returns      : description
*/
int
remove()
{
    set_alarm(0.1, 0.0, &remove_flames());
    this_player()->remove_glove_shadow();

    return 0;
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
    string with, where, how, what, owhat;
  
    /* make sure we hit with a flaming glove */
    if (!flames)
    {
        return 0;
    }

    // Make sure we're wearing the gloves, and sets wearer.
    if (!(wearer = query_worn()))
    {
         return 0;
    }
 
    // If weapons wielded, handled in bothhands/left/right shadows.
    if (wearer->query_weapon(W_LEFT) ||
    wearer->query_weapon(W_RIGHT) ||
    wearer->query_weapon(W_BOTH))
    {
        return 0;
    }

    /* give an attack description */
    with = (aid == W_RIGHT ? " right hand" : " left hand");
  
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
    if (interactive(wearer))
    {
        wearer->catch_tell("You " + what + where + 
            enemy->query_the_name(wearer) + " with your" + with + how +
            ", your glove" + burn + enemy->query_objective() + ".\n");
    }

    if (interactive(enemy))
    {
        enemy->catch_tell(wearer->query_The_name(enemy) + " " + owhat + 
            " your " + hdesc + " with " + wearer->query_possessive() +
            with + how + ", " + wearer->query_possessive() + " glove" +
            burn + "you.\n");
    }

    wearer->tell_watcher(QCTNAME(wearer) + " " + 
    owhat + where + QTNAME(enemy) + " with " + 
    wearer->query_possessive() + with + how + ", " +
    wearer->query_possessive() + " glove" + burn + 
    enemy->query_objective() + ".\n", enemy);

    return 1;
}

string query_recover()
{
    return ::query_recover() + query_keep_recover();
}

void
init_recover(string arg)
{
    init_keep_recover(arg);
    ::init_recover(arg);
}

/*
*   Function name: burn_description
*   Description  : description based on values of hurt
*   Arguments    : hurt value
*   Returns      : string of description
*/
mixed
burn_description(int hurt)
{
    switch (hurt)
    {
        case 1..10:
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
mixed
fire_damage(object enemy)
{
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
    hurt = enemy->hit_me(fire_dam, MAGIC_DT, wearer, -1)[2];

    if (hurt > 0)
    {
        wearer->add_panic(-3 - phurt / 5);
    }

    return hurt;
}

/*
*   Function name: armed_hit
*   Description  : damage description for weapon hits
*   Arguments    : with, enemy
*   Returns      : 
*/
mixed
armed_hit(string with, object enemy)
{
    wearer = query_worn();

    if (interactive(wearer))
        {
            wearer->catch_tell("The flames around your " + with
                + " touches "+
            enemy->query_the_name(wearer) + "," + burn +
            enemy->query_objective() + ".\n");
        }

        if (interactive(enemy))
        {
            enemy->catch_tell("The flames surrounding " +
                wearer->query_The_name(enemy) + with + " touches you,"
                + burn + "you.\n");
        }
        wearer->tell_watcher("The flames surrounding " +QTNAME(wearer) +
            "s " + with + " touches " +  QTNAME(enemy) + "," + burn +
            enemy->query_objective() + ".\n", enemy);
    return;
}

/*
*   Function name: flame_shield_hit
*   Description  : damage description for shield hits
*   Arguments    : enemy
*   Returns      : 
*/
mixed
flame_shield_hit(object enemy)
{
    if (interactive(wearer))
    {
        wearer->catch_tell("The flames surrounding your shield lashes "
        + "out as "
        + enemy->query_the_name(wearer) + " strikes at you," + burn
        + enemy->query_objective() + ".\n");
    }

    if (interactive(enemy))
    {
        enemy->catch_tell("The flames surrounding "
        + wearer->query_The_name(enemy) +"s shield lashes out as you "
        + "strike,"  + burn + "you.\n");
    }
    wearer->tell_watcher("The flames surrounding " +QTNAME(wearer)
        + "s shield lashes out as " +  QTNAME(enemy) + " strikes,"+ burn
        + enemy->query_objective() + ".\n", enemy);
    return;
}


/*
*   Function name: removal_message
*   Description  : Message about flames retreating from items in hand
*   Arguments    : ob
*   Returns      : 
*/
mixed
removal_message(object ob)
{
    say("The flames retreat from " + QTNAME(TP) + "s "
        + ob->query_short() + " to " + TP->query_possessive()
        + " gloves.\n");
    write("The flames retreat from your " + ob->query_short()
        + " to your gloves.\n");
    return;
}

/*
*   Function name: flame_items
*   Description  : description for flames on items in hands
*   Arguments    : ob
*   Returns      : 
*/
mixed
flame_items(object ob)
{
    if (TP->query_prop(C_I_AM_DEFILER))
    {
        set_alarm(0.2, 0.0, &write("Focusing your knowledge of fire "
            + "magic, you will the dark flames to spread to your "
            + ob->query_short() + ".\n"));
        // Darkness doesnt mask the items, so viewers see full message.
        set_alarm(0.2, 0.0, &say("The darkness spreads to "
        + TP->query_possessive() + " "
        + ob->query_short() + ".\n")); 
    }
    else
    {
        set_alarm(0.2, 0.0, &write("Focusing your knowledge of fire "
            + "magic, you will the flames to spread to your "
            + ob->query_short() + ".\n"));
        set_alarm(0.2, 0.0, &say("The flames spread to "
        + TP->query_possessive() + " "
        + ob->query_short() + ".\n"));
    }
    return;
}

/*
*   Function name: start_mana_drain
*   Description  : drains mana every 60 seconds
*   Arguments    : 
*   Returns      : 
*/
mixed
start_mana_drain()
{
    if (!flames)
        return;

    int pskill = (TP->query_skill(SS_ELEMENT_FIRE) / 4);
    float interval = (35.0 + itof(pskill));

    if (flames > 2 || flames < -2)
        interval = (interval/2.0);

    TP->add_mana(-5);
    set_alarm(interval, 0.0, &start_mana_drain());
    return;
}