/* File:          /d/Khalakhor/common/herbs/beatha.c
 * Creator:       Teth
 * Date:          January 22, 1998
 * Modifications:  
 * Added consistent singular and plural names - Tapakah, 04/2021
 * Purpose:       This herb will be found in plains, and it 
 *                gives a poison to undeads.
 * Related Files: /d/Khalakhor/common/poisons/beathap.c
 * Comments:      Beatha means "life". It is an herb that
 *                is infused with life energy, and thus 
 *                damaging to undeads.
 */

#pragma save_binary
#pragma strict_types

inherit "/std/herb";

#include <composite.h>
#include <herb.h>
#include <macros.h>
#include <ss_types.h>
#include <stdproperties.h>
#include "/d/Khalakhor/sys/paths.h"

public void
create_herb()
{
    set_name("berry");
    add_name("beatha");
    set_adj("red");
    set_herb_name("beatha");
    set_short("red berry");
    set_pshort("red berries");
    set_pname("berries");
    add_pname(({"fruits", "herbs", "beathas"}));
    set_ingest_verb("eat");
    set_unid_long("This is a red berry. You could probably eat it.\n");
    // Up to this point, the herb looks exactly like Suranie.
    set_id_long("This red berry is the fruit of a plant which is " +
      "a member of the family Rosaceae. It is extremely " +
      "akin to other species of the same genus, and thus " +
      "only a skilled herbalist would notice the subtle change " +
      "of hue across the skin of the berry which distinguishes it. " +
      "The plant it was picked from is a thorny low-lying shrub, " +
      "found only in plains and bush country. It is known to the " +
      "common folk as beatha, although it is often improperly " +
      "identified.\n");
    /* I want to add this below, but need a mudlib change.
       This is the herb known to those in Khalakhor as beatha. It radiates
       an aura of life energy. It is poisonous to the undead, as it 
       infuses the ingester with life, anethema to those who are not alive.
    */
    set_herb_value(2215);
    set_id_diff(85);
    set_find_diff(9);
    set_decay_time(2400); /* 40 minutes */
    set_dryable();
    set_amount(1);
    set_effect(HERB_SPECIAL, "hp", 0);
    add_prop(OBJ_I_WEIGHT, 5);
    add_prop(OBJ_I_VOLUME, 4);
    add_prop(MAGIC_AM_MAGIC, ({ 85, "life" }));
    add_prop(MAGIC_AM_ID_INFO, ({
        "The herb radiates a strong element of life magic.\n", 15,
        "It will infuse the ingester with life energy.\n", 30,
        "However, if the ingester is undead, it will wreak havoc " +
        "upon them, as the life magic burns them from inside.\n", 50,
        "Its magical healing relies somewhat on the ingester's " +
        "familiarity with life magic.\n", 75})); 
    add_prop(OBJ_S_WIZINFO, "This is the herb known as beatha, " +
      "which means 'life' in Gaelic. It is a Khalakhor only herb. " +
      "It gives its ingester magical healing dependent somewhat " +
      "on the ingester's life spells skill. However, if the ingester " +
      "is undead, it does not heal, but rather clones a strong " +
      "poison that would kill most small undead. I feel that this " +
      "is justified, as I _have_ included magic id info on the herb, " +
      "something which is not normally done. The poison file " +
      "is /d/Khalakhor/common/poisons/beathap.c. I have also " +
      "given extra tags on the long description of the herb that " +
      "show that the herb radiates life energy, and as such, that " +
      "should give most undead mortals a big hint not to ingest it.\n");
}

void
special_effect()
{
    int lifeskill = this_player()->query_skill(SS_ELEMENT_LIFE);
    object poison;

    if (this_player()->query_prop(LIVE_I_UNDEAD))
    {
        seteuid(getuid());
        poison = clone_object(COM_POISONS + "beathap");
        poison->move(this_player());
        this_player()->command("$groan incoherently");
        write("You feel the warmth of life spread throughout " +
          "your shell, a pain that is beyond description. " +
          "Life energy pulsates within you, reminding you " +
          "of what once was, and what has been lost.\n");
        poison->start_poison();
        return;        
    }

    if (this_player()->query_max_hp() != this_player()->query_hp())
    {
        write("You feel the warmth spread throughout your body, a " +
          "sensation that is beyond description. Wounds heal and " +
          "scars fade as the life energy mends that which was once " +
          "whole.\n");
        this_player()->heal_hp(100 + (2*lifeskill));
        return;
    }
    write("You feel no direct effect.\n");
    return;

}

void
consume_text(object *arr, string vb)
{
    string str;

    write("You " + vb + " " + (str = COMPOSITE_DEAD(arr)) + ". You " +
      "sense a warm infusion of living energy in your body.\n");

    say(QCTNAME(this_player()) + " " + vb + "s " + str + ".\n");
}


public string
query_recover() 
{
    return MASTER+":"+query_herb_recover();
}

public void
init_recover(string arg) 
{ 
    init_herb_recover(arg); 
}


