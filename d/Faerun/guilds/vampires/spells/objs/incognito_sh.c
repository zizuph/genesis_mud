/*
 * Support Shadow for the Vampires Incognito spell
 *
 * Originally created by Petros, modified by Arman (8/2016)
 * and refitted to be used for the Vampires, Nerull 2021
 */
 
#include "/d/Genesis/specials/local.h"
inherit SPELL_DIR + "objs/propchange_base_sh";

#include <stdproperties.h>
#include <ss_types.h>
#include <macros.h>
#include <wa_types.h>
#include <files.h>
#include "../../guild.h"

#ifndef LIVE_I_NEVERKNOWN
#define LIVE_I_NEVERKNOWN     ("_live_i_neverknown")
#endif

int neverknown_boost;

string adj1 = 0;
string adj2 = 0;
string adjes;

string * s_adj1x = ({"blue-bearded",
                  "brown-eyed",
                  "noble"});

string * s_adj2x = ({"barrel-chested",
                  "young",
                  "crook-nosed"});

string
s_adj1()
{
    int i;
    i = random(153);

    switch (i)
    {
        case 0:
        return "adolescent";
        break;
        case 1:
        return "ageless";
        break;
        case 2:
        return "ancient";
        break;
        case 3:
        return "childish";
        break;
        case 4:
        return "child-like";
        break;
        case 5:
        return "decrepit";
        break;
        case 6:
        return "elderly";
        break;
        case 7:
        return "mature";
        break;
        case 8:
        return "middle-aged";
        break;
        case 9:
        return "old";
        break;
        case 10:
        return "senile";
        break;
        case 11:
        return "timeworn";
        break;
        case 12:
        return "venerable";
        break;
        case 13:
        return "young";
        break;
        case 14:
        return "dirty";
        break;
        case 15:
        return "disheveled";
        break;
        case 16:
        return "disfigured";
        break;
        case 17:
        return "distinguished";
        break;
        case 18:
        return "dusty";
        break;
        case 19:
        return "foul-looking";
        break;
        case 20:
        return "furry";
        break;
        case 21:
        return "mud-splattered";
        break;
        case 22:
        return "noble";
        break;
        case 23:
        return "pock-marked";
        break;
        case 24:
        return "prim";
        break;
        case 25:
        return "savage";
        break;
        case 26:
        return "scarred";
        break;
        case 27:
        return "scruffy";
        break;
        case 28:
        return "slouchy";
        break;
        case 29:
        return "slovenly";
        break;
        case 30:
        return "sweaty";
        break;
        case 31:
        return "tidy-looking";
        break;
        case 32:
        return "travel-worn";
        break;
        case 33:
        return "unkempt";
        break;
        case 34:
        return "well-groomed";
        break;
        case 35:
        return "bony-armed";
        break;
        case 36:
        return "gangly-armed";
        break;
        case 37:
        return "long-armed";
        break;
        case 38:
        return "pudgy-armed";
        break;
        case 39:
        return "short-armed";
        break;
        case 40:
        return "strong-armed";
        break;
        case 41:
        return "thick-armed";
        break;
        case 42:
        return "thin-armed";
        break;
        case 43:
        return "weak-armed";
        break;
        case 44:
        return "beardless";
        break;
        case 45:
        return "black-bearded";
        break;
        case 46:
        return "blond-bearded";
        break;
        case 47:
        return "blue-bearded";
        break;
        case 48:
        return "bristly-bearded";
        break;
        case 49:
        return "brown-bearded";
        break;
        case 50:
        return "clean-shaven";
        break;
        case 51:
        return "fork-bearded";
        break;
        case 52:
        return "goateed";
        break;
        case 53:
        return "gray-bearded";
        break;
        case 54:
        return "green-bearded";
        break;
        case 55:
        return "grizzly-bearded";
        break;
        case 56:
        return "long-bearded";
        break;
        case 57:
        return "mustachioed";
        break;
        case 58:
        return "orange-bearded";
        break;
        case 59:
        return "purple-bearded";
        break;
        case 60:
        return "sideburned";
        break;
        case 61:
        return "red-bearded";
        break;
        case 62:
        return "silver-whiskered";
        break;
        case 63:
        return "thick-bearded";
        break;
        case 63:
        return "thinly-bearded";
        break;
        case 64:
        return "whiskered";
        break;
        case 65:
        return "white-bearded";
        break;
        case 66:
        return "barrel-chested";
        break;
        case 67:
        return "broad-chested";
        break;
        case 68:
        return "broad-shouldered";
        break;
        case 69:
        return "big";
        break;
        case 70:
        return "chubby";
        break;
        case 71:
        return "curvaceous";
        break;
        case 72:
        return "delicate";
        break;
        case 73:
        return "flabby";
        break;
        case 74:
        return "flat-chested";
        break;
        case 75:
        return "heavy";
        break;
        case 76:
        return "hunchbacked";
        break;
        case 77:
        return "hulking";
        break;
        case 78:
        return "impressive";
        break;
        case 79:
        return "lanky";
        break;
        case 80:
        return "lean";
        break;
        case 81:
        return "light";
        break;
        case 82:
        return "lithe";
        break;
        case 83:
        return "massive";
        break;
        case 84:
        return "muscular";
        break;
        case 85:
        return "petite";
        break;
        case 86:
        return "portly";
        break;
        case 87:
        return "pot-bellied";
        break;
        case 88:
        return "reedy";
        break;
        case 89:
        return "shrug-shouldered";
        break;
        case 90:
        return "sinewy";
        break;
        case 91:
        return "skinny";
        break;
        case 92:
        return "slender";
        break;
        case 93:
        return "slight";
        break;
        case 94:
        return "slim";
        break;
        case 95:
        return "small";
        break;
        case 96:
        return "spindly";
        break;
        case 97:
        return "squat";
        break;
        case 98:
        return "stocky";
        break;
        case 99:
        return "stout";
        break;
        case 100:
        return "sunken-chested";
        break;
        case 101:
        return "thin";
        break;
        case 102:
        return "tiny";
        break;
        case 103:
        return "voluptuous";
        break;
        case 104:
        return "wide-hipped";
        break;
        case 105:
        return "willowy";
        break;
        case 106:
        return "wizened";
        break;
        case 107:
        return "beige-skinned";
        break;
        case 108:
        return "black";
        break;
        case 109:
        return "black-skinned";
        break;
        case 110:
        return "blemished";
        break;
        case 111:
        return "bronze-skinned";
        break;
        case 112:
        return "brown-skinned";
        break;
        case 113:
        return "copper-skinned";
        break;
        case 114:
        return "dark-skinned";
        break;
        case 115:
        return "dusky";
        break;
        case 116:
        return "ebony-skinned";
        break;
        case 117:
        return "green-skinned";
        break;
        case 118:
        return "ivory-skinned";
        break;
        case 119:
        return "leathery";
        break;
        case 120:
        return "light-skinned";
        break;
        case 121:
        return "olive-skinned";
        break;
        case 122:
        return "pale";
        break;
        case 123:
        return "pallid";
        break;
        case 124:
        return "peach-skinned";
        break;
        case 125:
        return "pink-skinned";
        break;
        case 126:
        return "red-skinned";
        break;
        case 127:
        return "smooth-skinned";
        break;
        case 128:
        return "swarthy";
        break;
        case 129:
        return "tanned";
        break;
        case 130:
        return "tawny";
        break;
        case 131:
        return "white-skinned";
        break;
        case 132:
        return "wrinkled";
        break;
        case 133:
        return "yellow-skinned";
        break;
        case 134:
        return "bony-cheeked";
        break;
        case 135:
        return "bony-faced";
        break;
        case 136:
        return "chinless";
        break;
        case 137:
        return "double-chinned";
        break;
        case 138:
        return "dimpled";
        break;
        case 139:
        return "flat-chinned";
        break;
        case 140:
        return "freckle-faced";
        break;
        case 141:
        return "furry-eared";
        break;
        case 142:
        return "grim-faced";
        break;
        case 143:
        return "jug-eared";
        break;
        case 144:
        return "long-faced";
        break;
        case 145:
        return "oval-faced";
        break;
        case 146:
        return "pointy-eared";
        break;
        case 147:
        return "red-cheeked";
        break;
        case 148:
        return "round-faced";
        break;
        case 149:
        return "slope-browed";
        break;
        case 150:
        return "square-faced";
        break;
        case 151:
        return "stone-faced";
        break;
        case 152:
        return "thin-faced";
        break;
    }
}


string
s_adj2()
{
    int i;
    i = random(124);

    switch (i)
    {
        case 0:
        return "bony-fingered";
        break;
        case 1:
        return "flat-fingered";
        break;
        case 2:
        return "gaunt-fingered";
        break;
        case 3:
        return "grimy-fingered";
        break;
        case 4:
        return "lean-fingered";
        break;
        case 5:
        return "long-fingered";
        break;
        case 6:
        return "narrow-fingered";
        break;
        case 7:
        return "nimble-fingered";
        break;
        case 8:
        return "pudgy-fingered";
        break;
        case 9:
        return "quick-fingered";
        break;
        case 10:
        return "round-fingered";
        break;
        case 11:
        return "short-fingered";
        break;
        case 12:
        return "skeletal-fingered";
        break;
        case 13:
        return "slimy-fingered";
        break;
        case 14:
        return "stubby-fingered";
        break;
        case 15:
        return "thin-fingered";
        break;
        case 16:
        return "tight-fisted";
        break;
        case 17:
        return "adventurous";
        break;
        case 18:
        return "aggravated";
        break;
        case 19:
        return "blood-craving";
        break;
        case 20:
        return "brooding";
        break;
        case 21:
        return "captivating";
        break;
        case 22:
        return "corrupt";
        break;
        case 23:
        return "dangerous";
        break;
        case 24:
        return "demented";
        break;
        case 25:
        return "determined";
        break;
        case 26:
        return "devious";
        break;
        case 27:
        return "diabolic";
        break;
        case 28:
        return "eerie";
        break;
        case 29:
        return "elusive";
        break;
        case 30:
        return "fiendish";
        break;
        case 31:
        return "foul-smelling";
        break;
        case 32:
        return "friendly";
        break;
        case 33:
        return "frightened";
        break;
        case 34:
        return "furtive";
        break;
        case 35:
        return "ghoulish";
        break;
        case 36:
        return "gloomy";
        break;
        case 37:
        return "grim";
        break;
        case 38:
        return "honest";
        break;
        case 39:
        return "humble";
        break;
        case 40:
        return "hypnotic";
        break;
        case 41:
        return "innocent";
        break;
        case 42:
        return "innovative";
        break;
        case 43:
        return "inquisitive";
        break;
        case 44:
        return "irritable";
        break;
        case 45:
        return "lucky";
        break;
        case 46:
        return "magnetic";
        break;
        case 47:
        return "meek";
        break;
        case 48:
        return "musky";
        break;
        case 49:
        return "mysterious";
        break;
        case 50:
        return "odd-smelling";
        break;
        case 51:
        return "quiet";
        break;
        case 52:
        return "squalid";
        break;
        case 53:
        return "stoic";
        break;
        case 54:
        return "strange";
        break;
        case 55:
        return "suave";
        break;
        case 56:
        return "thoughtful";
        break;
        case 57:
        return "wheezy";
        break;
        case 58:
        return "auburn-haired";
        break;
        case 59:
        return "bald";
        break;
        case 60:
        return "balding";
        break;
        case 61:
        return "black-haired";
        break;
        case 62:
        return "blond-haired";
        break;
        case 63:
        return "blue-haired";
        break;
        case 64:
        return "brown-haired";
        break;
        case 65:
        return "chestnut-haired";
        break;
        case 66:
        return "dark-haired";
        break;
        case 67:
        return "gray-haired";
        break;
        case 68:
        return "green-haired";
        break;
        case 69:
        return "flaxen-haired";
        break;
        case 70:
        return "light-haired";
        break;
        case 71:
        return "long-haired";
        break;
        case 72:
        return "mohawk-haired";
        break;
        case 73:
        return "orange-haired";
        break;
        case 74:
        return "purple-haired";
        break;
        case 75:
        return "raven-haired";
        break;
        case 76:
        return "red-haired";
        break;
        case 77:
        return "short-haired";
        break;
        case 78:
        return "silver-haired";
        break;
        case 79:
        return "thick-haired";
        break;
        case 80:
        return "thin-haired";
        break;
        case 81:
        return "tonsure-haired";
        break;
        case 82:
        return "white-haired";
        break;
        case 83:
        return "wispy-haired";
        break;
        case 84:
        return "bandy-legged";
        break;
        case 85:
        return "bony-legged";
        break;
        case 86:
        return "bow-legged";
        break;
        case 87:
        return "gangly-legged";
        break;
        case 88:
        return "knob-kneed";
        break;
        case 89:
        return "knock-kneed";
        break;
        case 90:
        return "long-legged";
        break;
        case 91:
        return "short-legged";
        break;
        case 92:
        return "skinny-legged";
        break;
        case 93:
        return "spindle-legged";
        break;
        case 94:
        return "thin-legged";
        break;
        case 95:
        return "thick-legged";
        break;
        case 96:
        return "weak-kneed";
        break;
        case 97:
        return "big-lipped";
        break;
        case 98:
        return "bloody-toothed";
        break;
        case 99:
        return "buck-toothed";
        break;
        case 100:
        return "chip-toothed";
        break;
        case 101:
        return "gap-toothed";
        break;
        case 102:
        return "jut-jawed";
        break;
        case 103:
        return "pouty-lipped";
        break;
        case 104:
        return "purse-lipped";
        break;
        case 105:
        return "sharp-toothed";
        break;
        case 106:
        return "slack-jawed";
        break;
        case 107:
        return "square-jawed";
        break;
        case 108:
        return "tight-jawed";
        break;
        case 109:
        return "toothless";
        break;
        case 110:
        return "wide-mouthed";
        break;
        case 111:
        return "bent-nosed";
        break;
        case 112:
        return "big-nosed";
        break;
        case 113:
        return "bulbous-nosed";
        break;
        case 114:
        return "flat-nosed";
        break;
        case 115:
        return "hawkish-nosed";
        break;
        case 116:
        return "hook-nosed";
        break;
        case 117:
        return "knob-nosed";
        break;
        case 118:
        return "potato-nosed";
        break;
        case 119:
        return "pointy-nosed";
        break;
        case 120:
        return "pug-nosed";
        break;
        case 121:
        return "red-nosed";
        break;
        case 122:
        return "upnosed";
        break;
        case 123:
        return "wart-nosed";
        break;
    }
}


/*
 * Function:    initialize_shadow
 * Description: Called after first cloned. Should do all the initialization
 *              effects for this particular shadow.
 */
public void
initialize_shadow(object spell_object, mapping spell_input)
{
    ::initialize_shadow(spell_object, spell_input);

    spell_object->set_spell_effect_desc("Incognito");
    spell_object->set_short("incognito spell object");

    int power = spell_object->query_spell_effect_power();

    neverknown_boost = max(1, min(100, power / 3));
}


/*
 * Function:    query_prop
 * Description: This is the primary function that you should override to
 *              implement the propchange shadow. Make sure to return
 *              the shadow_who->query_prop(prop) result if you don't
 *              want to handle that particular prop.
 */
public mixed
query_prop(string prop)
{
    mixed result = shadow_who->query_prop(prop);

    if (adj1 == 0)
    {
        adj1 = s_adj1();
    }

    if (adj2 == 0)
    {
        adj2 = s_adj2();
    }

    if (prop != LIVE_I_NEVERKNOWN)
    {
        return result;
    }

    if (intp(result))
    {
        return max(1, result + neverknown_boost);
    }
    else
    {
        return 1;
    }
}


/*
 * Function:    hook_spell_effect_started
 * Description: Override this to customize the message when this spell effect
 *              is added to th target.
 */
public void
hook_spell_effect_started(object spell_object)
{
    object target = spell_object->query_effect_target();

    if (objectp(target))
    {
        object enemy;

        enemy = target->query_attack();

        // If cast after 120 seconds, combat is also stopped.
        if (target->query_relaxed_from_combat() == 1)
        {
            enemy->stop_fight(target);
            target->stop_fight(enemy);
        }

        target->catch_tell("Your appearance changes. You look like "
        +"somebody else.\n");

        /*tell_room(environment(target), QCTNAME(target)
        + " suddenly looks like someone else.\n",
        ({ target }));*/
    }
}


/*
 * Function:    hook_spell_effect_ended
 * Description: Override this to customize the message when this spell effect
 *              is dispelled.
 */
public void
hook_spell_effect_ended(object spell_object)
{
    object target = spell_object->query_effect_target();

    if (objectp(target))
    {
        target->catch_tell("You return to your normal "
        +"appearance.\n");

        tell_room(environment(target), QCTNAME(target)
        + " returns to "+target->query_possessive()
        +" normal appearance.\n", ({ target }));
    }

}


/*
* Function:    hook_spell_effect_warn_fading
* Description: Override this to customize the message for when
*              the effect has only a minute left.
*/
public void
hook_spell_effect_warn_fading(object spell_object)
{
    object target = spell_object->query_effect_target();

    if (objectp(target))
    {
        target->catch_tell("You sense your incognito spell "
        +"begins to fade.\n");
    }
}


/*
* Function:    hook_spell_effect_not_maintained
* Description: Override this to describe the effect when the caster
*              cannot maintain the effect.
*/
public void
hook_spell_effect_not_maintained(object spell_object)
{
    object caster = spell_object->query_effect_caster();


    if (objectp(caster))
    {
        caster->catch_tell("You are mentally unable to maintain "
        + "the incognito spell.\n");
    }
}


private mixed
query_list(mixed list, int arg)
{
    if (!pointerp(list))
        return 0;
    if (!arg && sizeof(list))
        return list[0];
    else
        return list + ({});
}


varargs public mixed
query_adj(int arg)
{
    return query_list(({adj1, adj2}), arg);
}


public string *
query_adjs()
{
    return query_list(({adj1, adj2}), 1);
}


public int
adjectiv_id(string str)
{
    return (member_array(str, ({adj1, adj2})) >= 0);
}


public string *
parse_command_adjectiv_id_list()
{
    return ({adj1, adj2}) + ({ query_shadow_who()->query_gender_string() });
}


