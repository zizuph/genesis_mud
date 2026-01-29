/*
 * I think this is Armans code orignially
 *
 * Cotillion removed a trigger 2004-02-1X
 */

#pragma strict_types

#include "/d/Ansalon/common/defs.h"
#include <ss_types.h>
#include <wa_types.h>
#include <stdproperties.h>
#include <macros.h>
#include <options.h>
#include <money.h>
#include "../local.h"

inherit "/lib/unique";

inherit AM_FILE
inherit "/d/Krynn/std/equip";

#define WEP "/d/Krynn/qualinesti/wep/"
#define OBJ "/d/Krynn/qualinesti/obj/"
#define ARM "/d/Krynn/qualinesti/arm/"

object        weapon, quiver;

void
create_krynn_monster()
{
    
    set_name("ealanus");
    add_name("archer");
    set_living_name("Ealanus");
    set_race_name("half-elf");
    set_adj("shifty");
    add_adj("grim");
    set_title("the Exile, Half-Elven Mercenary");
    set_long("This tall and surprisingly muscular half-elf looks upon you " +
       "from the shadows with an appraising glance, quickly measuring how much " +
       "of a potential threat you are to him. By the way he amusedly returns "+
       "to his drink it obviously wasn't a flattering appraisal, however " +
       "considering how comfortably he rests a hand upon his bow and how well " +
        "worn his armour is, his confidence may be warranted.\n");
    
    set_gender(0);
    set_alignment(0);
    set_knight_prestige(0);
    
    set_stats(({ 170, 200, 170, 150, 150, 140 }));

    set_skill(SS_WEP_KNIFE, 150);
    set_skill(SS_WEP_MISSILE, 150);
    set_skill(SS_WEP_SWORD, 150);
    set_skill(SS_UNARM_COMBAT, 100);
    set_skill(SS_2H_COMBAT, 150);
    set_skill(SS_PARRY, 150);
    set_skill(SS_DEFENCE, 150);
    set_skill(SS_AWARENESS, 70);
    set_skill(SS_BLIND_COMBAT, 100);
     
   
    add_prop(CONT_I_WEIGHT, 40000);
    add_prop(CONT_I_HEIGHT, 185);
    add_prop(NPC_I_NO_RUN_AWAY, 1);
    add_prop(LIVE_I_ATTACK_THIEF, 0);
    add_prop(LIVE_I_SEE_DARK, 2);
    add_prop(LIVE_I_QUICKNESS, 200);    
    add_prop(LIVE_S_EXTRA_SHORT, " sitting in a shadowy corner of the room");

    set_hp(query_max_hp());

    set_act_time(10 + random(2));
    add_act("emote looks at you distrustfully.");
    add_act("emote smiles sardonically in your direction.");
    add_act("emote runs a finger along one of his pointed ears, pondering " +
      "his elven heritage.");
    add_act("emote silently gestures to the barmaid for another drink.");
    add_act("@@check_for_arrows");

        
    add_cact("emote scowls at you.");
    add_cact("say You really think you can stand against me?!");
    add_cact("say Defend yourself!");
    add_cact("take arrows");
    
    set_default_answer(VBFC_ME("def_answer"));
    set_introduce(1);
    
    
    /* Equipment */

    add_prop(OBJ_M_HAS_MONEY, ({ 0, random(10), random(10)}));

    setuid();
    seteuid(getuid());
    
    equip(({
        clone_unique(WEP + "silver_bow", 10, WEP + "elven_bow"),
            clone_unique(KARMOUR + "circlet", 10, ARM + "hard_helm"),
            clone_unique(ARM + "ashchain", 5, ARM + "chain"),
            clone_unique(ARM + "firebane_cloak", 5, ARM + "cloak"),
            
            ARM + "elven_boots",
            ARM + "elven_sleeves",
            }));

    quiver = clone_object(OBJ + "quiver");
    quiver->move(TO);
    
    clone_object(WEP + "leaf_arrow")->move(quiver);
    clone_object(WEP + "elven_arrow")->move(quiver);
    clone_object(WEP + "leaf_arrow")->move(quiver);
    clone_object(WEP + "piercing_arrow")->move(quiver);
    clone_object(WEP + "piercing_arrow")->move(quiver);
    quiver->wear_me();
    
}

string
def_answer()
{
    command("emote looks at you haughtily.");
    command("say I am not interested in your questions, stranger.");
    
    return "";
}

void
check_for_arrows()
{
    object weapon, *wp;
    object *items;
    int    i, arrow, size;
    
    wp = query_weapon(-1);
    
    if ( sizeof(wp) )
        weapon = wp[0];
    if (!objectp(weapon))
        return;
        
    if ( weapon->query_wt() == W_MISSILE )
    {
        items = deep_inventory(TO);
        size = sizeof(items);
        
        for ( i = 0; i < size; i++ )
        {
            if ( (items[i])->id("arrow") )
                arrow++;
        }
        
        if ( arrow <= 10 )
        {
            command("emote puts some more arrows into his quiver.");
            clone_object("/d/Krynn/qualinesti/wep/elven_arrow")->move(quiver, 1);
            arrow += 12;
        }    
        else
        {
            command("emote inspects his quiver for arrows.");        
            command("take arrows");
            command("put arrows in quiver");
        }
    }    
}

int 
query_option(int opt)
{
    if ( opt == OPT_UNARMED_OFF )
       return 1;
}

/* If he is sitting, get up when attacking/attacked */
public void
hook_attacked(object enemy)
{
    if (query_prop(LIVE_S_EXTRA_SHORT))
    {
        command("emote swiftly rises from his chair and eagerly " +
            "enters battle!");
        remove_prop(LIVE_S_EXTRA_SHORT);
    }
}

public void
hook_attack(object enemy)
{
    hook_attacked(enemy);
}


/*
 * He's not so nice, he'll snicker before introing
 */
public varargs void
action_introduce(object target = 0)
{
    command("snicker");
    ::action_introduce();
}
