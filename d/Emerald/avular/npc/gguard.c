#include "../defs.h"
#include "/d/Emerald/sys/macros.h"
#include "/d/Emerald/sys/faction.h"
#include <ss_types.h>
#include <stdproperties.h>
#include <cmdparse.h>

inherit STDDARKLING;

void annoy_guard(object ob);

void
create_darkling()
{
    set_name("guard");
    add_name(CREATURE_OF_VS_ID);

    set_short("darkling guard");

    set_long("Getting a closer look at this darkling, you notice that "+
       "he appears to have an unusually muscular build for his kind. "+
       "Despite his extremely short stature, the rest of his body is "+
       "well-proportioned. The characteristic pale skin is so pale it "+
       "looks to be devoid of color. He has the cold, dark stare of a "+
       "veteran of many battles.\n");

    set_base_stat(SS_STR, 60, 10);
    set_base_stat(SS_DEX, 100, 10);
    set_base_stat(SS_CON, 75, 10);
    set_base_stat(SS_INT, 85, 10);
    set_base_stat(SS_DIS, 70, 0);
    set_base_stat(SS_WIS, 95, 5);

    add_prop(LIVE_I_NEVERKNOWN, 1);
    add_prop(OBJ_M_HAS_MONEY, 10+random(30));

    set_skill(SS_WEP_SWORD, 45);
    set_skill(SS_DEFENCE, 30);
    set_skill(SS_PARRY, 40);

    add_equipment( ({ AV_WEP+"bonyxsword",
                      AV_ARM+"gblackrobe" }) );
}

/*public void
emote_hook(string verb, object actor, string adverb, int attrs)
{
    if (cmd_attr & ACTION_CONTACT)
    {
       annoy_guard(actor);
    }
}
*/
public void
emote_hook(string emote, object actor, string adverb,object *oblist, int cmd_attr,int target)
{
   if (!target) return;

    if ( cmd_attr & ACTION_CONTACT )
    {
       annoy_guard(actor);
    }
}

void
annoy_guard(object ob)
{
    set_this_player(ob);

    ADD_FACTION(ob, FG_AVULAR_GUARDS, FACACTION_SMALLANNOY);
    if (QUERY_FACTION(ob, FG_AVULAR_GUARDS) <= FACRANK_SILENTALERT)
    {
       command("say to " + ob->query_real_name() + " You've worn out "+
            "what little welcome you had! I'll not suffer through any more of your "+
            "lightdweller antics!");
       attack_object(ob);
    }
    else
    {
        command("say to " + ob->query_real_name() + " You had best watch it, else "+
                "you may find yourself admiring the sharp end of my blade.");
    }
}
