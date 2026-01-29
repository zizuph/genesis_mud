/* 
*   Half-Giants village in the pass overhauled.
*   /d/Kalad/common/wild/pass/giantpass/arm/
*   Eaten by wolves for loot.
*   Copied from : Kabal Docks.
*
* A trinket earring, quest item.
* 2004.09.13. by Dargoth
*
*/

#include <stdproperties.h>
#include <ss_types.h>
#include <wa_types.h>
#include <tasks.h>

inherit "/std/armour";
inherit "/lib/keep";

#define TO (this_object())
#define TP (this_player())
#define SK_EXTRA 20
#define MAX_INCREASABLE 80
#define D_NAME "G O L  D E K  R A H I"
#define RECOGNIZED_RING "_earring_recognized_dd"
#define E_NAME "_raumdor_quest_item_earring11"

int activated;
int noted;
int given_extra;
object tp;

string exa_marks();
int add_extra_skill(object player,int skill, int addition, int ceiling);
void remove_extra_skill(object player,int skill,int remove_amount);


void create_armour()
{
    ::create_armour();
    set_name("earring");
    add_name(E_NAME);
    set_adj(({"bronze", "round", "ornamented" }));
    set_short("bronze earring");
    set_long(
    "This item consists of a crescent moon shaped piece of bronze, its "
        + "horns tapering together, forming a circle with a small space "
        + "between them, which allows the earring to be attached to an "
        + "ear. The bronze is polished to rich lustrous sheen, and the "
        + "broadest part is engraved with some pattern.\n");
    add_item("pattern", exa_marks);

    add_prop(MAGIC_AM_MAGIC, ({ 10, "enchantment",
                                20, "divination" }));
    add_prop(MAGIC_I_RES_IDENTIFY, 10);

    add_prop(MAGIC_AM_ID_INFO,({
        "The earring seems to bear an enchantment.\n", 10,
        "It enhances and translates the sounds the wearer "
        + "hears, allowing to recognize them better.\n", 25,
        "It is of no use to those who are already "
        + "supremely masterful in that.\n", 40,
        "You sense the history of this minor artifact. "
        + "It was created for a trading lord of Raumdor, made "
        + "out of less noble metal to appear inconspicuous "
        + "and allow him to understand what the foreigners "
        + "speak.\n", 50,
        "Eventually, the lord was slain in a sea-battle with "
        + "pirates, and the amulet has been in possession of "
        + "the sea-faring people ever since; sometimes traded, "
        + "sometimes looted.\n", 60}));

    add_prop(OBJ_S_WIZINFO, "The earring is enchanted with "
        + "divining properties, allowing the wearer to understand "
        + "languages better (SS_LANGUAGE + 20, not to exceed 80 total)\n");

    add_prop(OBJ_I_VALUE, 8500);
    add_prop(OBJ_I_VOLUME, 50);
    add_prop(OBJ_I_WEIGHT, 100);

    add_prop(OBJ_M_NO_BUY, "The shopkeeper says: Hmm.. no. This trinket "
        + "interests me. I will stick to it for now.\n");

    config_wearable_item(A_L_EAR,1,1,TO);
    set_keep(1);
    activated=0;
    set_af(TO);
}

public mixed wear(object ob)
{

    tp=TP;
    if (objectp(tp) && activated == 0)
    {
        given_extra = add_extra_skill(tp,SS_LANGUAGE,SK_EXTRA,MAX_INCREASABLE);
        activated=1;
        noted=tp->resolve_task(TASK_DIFFICULT,
            ({ TS_INT, SKILL_WEIGHT, 70, SS_AWARENESS }));
        if (noted > 0)
            write("The surrounding sounds suddenly stop for a moment. "
                + "As they resume, you sense there is a different quality "
                + "to what you perceive.\n");
    }
    return 0;
}

public mixed remove(object ob)
{
    int rest_of_skill;

    if (objectp(tp) && activated == 1)
    {
        remove_extra_skill(tp,SS_LANGUAGE,given_extra);
        activated=0;
        if (noted > 0)
            tell_object(tp,"As you remove the "+short()+", the "
            + "surrounding sounds become bleaker and duller.\n");
    }
    return 0;
}


string exa_marks()
{
    int tperc;
    string str;

    str="The marks are etched into the surface, they "
        + "twine and twist into several wavy patterns.";

    if (tp->query_prop(RECOGNIZED_RING))
        tperc=500; // really big value to trigger the if below
    else
        tperc=tp->resolve_task(TASK_DIFFICULT,
            ({ TS_WIS, SKILL_WEIGHT, 50, SS_LANGUAGE }));

    if (tperc <= 0)
        return str+"\n";

    str+=" The etchings themselves do not form "
        + "any words, yet there is something familiar to them.";
    if (tperc > 30)
        str+=" You realize that the space between the "
            + "etched patterns is in itself a pattern of some "
            + "twisty words.";
    if (tperc > 50)
    {
        if (tperc < 500)
            tp->add_prop(RECOGNIZED_RING,1);
        str+=" The words spell: "+D_NAME;
    }

    return str+"\n";
}

// adds the player extra skill,
// checks on current extra_skill set as well
// as for the total skill not to exceed ceiling.
//
int add_extra_skill(object player,int skill, int addition, int ceiling)
{

    int curr_extra;
    int retval=0;
    int currskill=player->query_skill(skill);

    if (currskill < ceiling)
    {
        retval=min(ceiling - currskill, addition);
        curr_extra=player->query_skill_extra(skill);
        player->set_skill_extra(skill, curr_extra + retval);
    }
    return retval;
}

void remove_extra_skill(object player,int skill,int remove_amount)
{
    int rest_of_skill;
    rest_of_skill=player->query_skill_extra(skill) - remove_amount;
    player->set_skill_extra(skill, rest_of_skill);
}
