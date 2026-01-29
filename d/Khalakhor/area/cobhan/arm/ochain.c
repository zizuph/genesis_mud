/* File:          /d/Khalakhor/se_speir/forest/arm/ochain.c
 * Creator:       Teth
 * Date:          December 29, 1997
 * Modifications:
 * Purpose:       This shield has magical properties, but they
 *                will all be contained within the shadow,
 *                so that the magic can be dispelled!
 * Related Files: /d/Khalakhor/se_speir/forest/
 *                /d/Khalakhor/se_speir/forest/arm/ochain_sh.c
 * Comments:      This is the shield named Ochain, the "Moaner".
 *                It was the shield of Conchobhar Mac Nessa in Celtic
 *                myth, and it moaned whenever its owner was in danger.
 * TODO:          Add in the saving of whether it should still have
 *                the shadow or not over reboots.
 *                Make it fur-edged, but can remove the fur?
 */

#pragma save_binary
#pragma strict_types

inherit "/std/armour";
inherit "/lib/keep";

#include <wa_types.h>
#include <formulas.h>

#include "../forest.h"

public void
create_armour()
{
    set_name("shield");
    set_pname("shields");
    add_name(({"ochain","armour","sgiath"}));
    add_pname(({"sgiathan","armours"}));
    set_adj("bronze");
    add_adj(({"dull","metal"}));
    set_short("dull bronze shield");
    set_pshort("dull bronze shields");
    set_ac(19);
    set_at(A_SHIELD);
    set_am( ({0,0,0}) );
    set_long(("@@lore_long"));
    add_item(({"swirls","engraved swirls","design","Celtic design",
        "edgings","embossings"}),"They are a decoration " +
        "symbolizing the ever-changing patterns of life.\n");
    add_prop(OBJ_I_VOLUME, 2000);
    add_prop(OBJ_I_WEIGHT, 3000);
    add_prop(OBJ_I_VALUE, F_VALUE_ARMOUR(19) + (random(140)));
}

public string
lore_long()
{
    string lore;
    int loreskill = this_player()->query_skill(SS_KHALAKHOR_LORE);

    lore = "";

    switch(loreskill)
    {
    case 0..10:
    lore = "";
    break;

    case 11..20:
    lore = " The shield reminds you of a story you once " +
           "heard, but you cannot recall any details.";
    break;

    case 21..35:
    lore = " The shield bears a resemblance to some of the " +
           "magical shields in days of long ago. However, your " +
           "skill in the lore of Khalakhor does not allow you " +
           "to ascertain whether it is still magical.";
    break;

    case 36..65:
    lore = " You recognize the shield as the one worn by Conchobhar " +
           "Mac Nessa, whose life was blessed by uncanny fortune. " +
           "However, the magical properties of the shield are " +
           "unexplained in the lore you are aware of, and it is " +
           "probable that the magic of the shield died with the " +
           "owner.";
    break;

    case 66..85:
    lore = " This is the shield of Conchobhar Mac Nessa, known as " +
           "Ochain. Legend has it that Mac Nessa was able to use " +
           "the shield to determine if unseen danger was near, " +
           "and if any was found, the shield provided excellent " +
           "protection for its owner. Your lore skill can not " +
           "divine its current magical properties, if it has any.";
    break;

    case 86..100:
    lore = " This is the shield of Conchobhar Mac Nessa, known as " +
           "Ochain. Legend has it that Mac Nessa was able to use " +
           "the shield to determine if unseen danger was near, " +
           "and if any was found, the shield provided excellent " +
           "protection for its owner. Your lore skill can not " +
           "divine its current magical properties, if it has any. " +
           "However, your knowledge of the lore of Khalakhor " +
           "associates the word 'nochd' with the shield.";
    break;

    default:
    lore = "";
    break;
    }    

    return "The dull bronze shield is shaped to cover the body as " +
           "well as one arm. Engraved swirls edge the shield, " +
           "embossing it with a Celtic design." + lore + "\n";
}

public int *
query_shield_slots()
{
    return (::query_shield_slots() + ({A_BODY}));
}
