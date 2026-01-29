/*
 * /d/Gondor/common/dwarf_guild/wep/axe.c
 *
 * Copyright (C) Stas van der Schaaf - January 25 1994
 *               Mercade @ Genesis
 *
 * This is the axe that is crafted by the smith at the dwarven race guild.
 * It is recoverable. It is configurable on several properties and those
 * properties have their impact on the penetration of the weapon, the
 * to-hit chance, the likeliness to break and whatever property else.
 *
 * Revision history:
 * 14-Feb-1997, Olorin: inherit "/lib/keep.c";
 */

#pragma save_binary
#pragma strict_types

inherit "/std/weapon.c";
inherit "/lib/keep.c";

#include <formulas.h>
#include <language.h>
#include <macros.h>
#include <stdproperties.h>
#include <wa_types.h>
#include "/d/Gondor/defs.h"
#include "../axe.h"
#include "../dwarf.h"

#define BASIC_HIT          30
#define BASIC_PEN          23
#define BASIC_LIKELY_BREAK  6
#define BASIC_LIKELY_CORR  10 /* unused with weapons... don't know why */
#define BASIC_LIKELY_DULL  15
#define BASIC_WEIGHT       80
#define BASIC_VOLUME       55
#define AXE_ID             (DWARVEN_RACE_GUILD_PREFIX + "borins_axe")

#define DEBUG(s) find_player("mercade")->catch_msg((s) + "\n")

/*
 * Global variables
 */
static mapping axe_descriptions = AXES_DEFINITION;
static string *axe_properties;
static int     weight; /* in 100ds of grammes */
static int     volume; /* in 100ds of grammes */

void
create_weapon()
{
    set_name("axe");
    add_name(AXE_ID);
    set_pname("axes");

    add_item( ({ "end", "rear end", "rear" }),
	BSN("There is a small metal tag nailed to the rear end of the haft."));
    add_item( ({ "tag", "metal tag", "small metal tag", "small tag" }),
	BSN("It is a small metal tag, nailed to the rear end of the haft. " +
	"One word is gracefully inscribed in it: 'Borin'! It is the name " +
	"of the craftsdwarf who skillfully crafted this axe."));

    set_wt(W_AXE);
    set_dt( (W_SLASH | W_BLUDGEON) );
    set_pen(BASIC_PEN);
    set_hit(BASIC_HIT);
    set_likely_break(BASIC_LIKELY_BREAK);
    set_likely_corr(BASIC_LIKELY_CORR);
    set_likely_dull(BASIC_LIKELY_DULL);

    weight = BASIC_WEIGHT;
    volume = BASIC_VOLUME;

    add_prop(OBJ_I_VALUE, F_VALUE_WEAPON(BASIC_HIT, BASIC_PEN));
    add_prop(OBJ_S_WIZINFO,
	BSN("This axe is a special axe, crafted and sold by Borin, the " +
	"smith of the " + DWARVEN_RACE_GUILD_NAME + ". It is configurable " +
	"on five properties: wood type, metal type, blade size, haft length " +
	"and the number of hands to use to wield it. /Mercade"));
}

/*
 * Function name: some_part
 * Description  : This function could be a macro, but that would make stuff
 *                very illegible and we wouldn't want that.
 *                In the axe_properties array is the simple description
 *                of the value. This value will be converted into a string
 *                that is better in the add_item or short/long description.
 * Arguments    : int     - index of the property in the array axe_properties
 *                string* - array of descriptions to match.
 * Returns      : string - the good string.
 */
string
some_part(int index, string *descs)
{
    return descs[member_array(axe_properties[index],
	axe_descriptions[AXE_PROPERTIES_ORDER[index]][INDEX_TYPES])];
}

/*
 * Function name: is_index
 * Description  : This function checks whether the value of a certain
 *                property is in a limited sublist.
 * Arguments    : int     - index of the property in the array axe_properties
 *                string* - the sublist
 * Returns      : int - 1 - the value is in the sublist
 */
int
is_index(int index, string *descs)
{
    return (member_array(axe_properties[index], descs) != -1);
}

void
set_axe_wood(int index)
{
    /* The type of wood has an impact on how likely it is that the haft
     * will break.
     */
    set_likely_break(query_likely_break() + WOOD_TYPE_BREAK[index]);

    /* Set the wood-type of the haft as adjective to the axe.
     */
    set_adj(WOOD_TYPE_DESC[index]);

    /* Adjust the weight and volume.
     */
    volume += WOOD_TYPE_VOLUME[index];
    weight += WOOD_TYPE_WEIGHT[index];
}

void
set_axe_metal(int index)
{
    /* The type of metal has an impact on how fast it will corrode and
     * how fast it will become dull.
     */
    set_likely_corr(query_likely_corr() + METAL_TYPE_CORR[index]);
    set_likely_dull(query_likely_dull() + METAL_TYPE_DULL[index]);

    /* The type of metal has an impact on the penetration of the blade.
     */
    set_pen(query_pen() + METAL_TYPE_PEN[index]);

    /* Set the metal-type of the blade as adjective to the axe.
     */
    add_adj(METAL_TYPE_DESC[index]);

    /* Adjust the weight and volume.
     */
    volume += METAL_TYPE_VOLUME[index];
    weight += METAL_TYPE_WEIGHT[index];
}

void
set_axe_blade(int index)
{
    /* The size of the blade has a positive impact on the penetration value
     * of the axe.
     */
    set_pen(query_pen() + BLADE_SIZE_PEN[index]);

    /* The size of the blade has a positive impact on the penetration value
     * of the axe;
     */
    set_hit(query_hit() + BLADE_SIZE_HIT[index]);

    /* Set the blade-type as adjective to the axe.
     */
    if ((index == 0) || (index == 3))
    {
	set_adj(BLADE_SIZE_DESC[index] + "-bladed");
	set_adj(BLADE_SIZE_DESC[index]);
	set_adj("bladed");
    }

    /* Adjust the weight and volume.
     */
    volume += BLADE_SIZE_VOLUME[index];
    weight += BLADE_SIZE_WEIGHT[index];
}

void
set_axe_haft(int index)
{
    /* The length of the haft has a negative impact on the to-hit-chance
     * of the axe.
     */
    set_hit(query_hit() + HAFT_LENGTH_HIT[index]);

    /* The length of the haft has a positive impact on the penetration of
     * the axe.
     */
    set_pen(query_pen() + HAFT_LENGTH_PEN[index]);

    /* The length of the haft has a negative impact on the chances of
     * breaking of the axe (i.e. higher change to break).
     */
    set_likely_break(query_likely_break() + HAFT_LENGTH_BREAK[index]);

    /* Set the haft-type as adjective to the axe.
     */
    if ((index == 0) || (index == 3))
    {
	set_adj(HAFT_LENGTH_DESC[index]);
	set_adj(HAFT_LENGTH_DESC[index] + "-hafted");
	set_adj("hafted");
    }

    /* Adjust the weight and volume.
     */
    volume += HAFT_LENGTH_VOLUME[index];
    weight += HAFT_LENGTH_WEIGHT[index];
}

void
set_axe_hands(int index)
{
    /* set the hands to be used with this axe
     */
    set_hands( ((index <= 0) ? W_ANYH : W_BOTH) );

    /* The number of hands to be used has a positive impact on the
     * penetration of the axe.
     */
    set_pen(query_pen() + NUM_HANDS_PEN[index]);

    /* The number of hands to be used has a negatice impact on the to-hit-
     * chance of the axe.
     */
    set_hit(query_hit() + NUM_HANDS_HIT[index]);

    /* Make it possible to use the number of hands as adjective.
     */
    set_adj(NUM_HANDS_ADJ[index]);
    set_adj(NUM_HANDS_ADJ[index] + "-handed");
    set_adj("handed");
}

void
set_properties(mapping props)
{
    string *indices = AXE_PROPERTIES_ORDER;
    string  desc;
    int     index;
    int     m_index;
    int     price = 0;

    axe_properties = allocate(5);

    for(index = 0; index < sizeof(indices); index++)
    {
	axe_properties[index] = props[indices[index]];
	m_index = member_array(axe_properties[index],
	    axe_descriptions[indices[index]][INDEX_TYPES]);

	price += axe_descriptions[indices[index]][INDEX_PRICES][m_index];

	call_other(TO, ("set_axe_" + indices[index]), m_index);
    }

    if (query_hit() > MAX_HIT_PEN)
    {
        set_hit(MAX_HIT_PEN);
    }

    if (query_pen() > MAX_HIT_PEN)
    {
        set_pen(MAX_HIT_PEN);
    }

    add_prop(OBJ_I_VALUE, (F_VALUE_WEAPON(query_hit(), query_pen()) + price));
    add_prop(OBJ_I_VOLUME, volume * 100);
    add_prop(OBJ_I_WEIGHT, weight * 100);

    /* After the necessary "properties" are set, we can set these add_items
     * with a nice description of the axe-parts.
     */
    add_item( ({ "haft", "helve", "handle", "hilt" }),
	BSN("The helve is " +
	LANG_ADDART(some_part(INDEX_HAFT_LENGTH, HAFT_LENGTH_ITEM)) +
	" haft with a small metal tag on its rear end. It is made of " +
	axe_properties[INDEX_WOOD_TYPE] + ", which is " +
	LANG_ADDART(some_part(INDEX_WOOD_TYPE, WOOD_TYPE_ITEM)) +
	" type of wood. There is a grip on the haft in order to wield it " +
	some_part(INDEX_NUM_HANDS, NUM_HANDS_ADJ) + "-handedly."));
    add_item( ({ "grip" }),
	BSN("The grip on the haft is designed for " +
	axe_properties[INDEX_NUM_HANDS] + " hand" +
	((axe_properties[INDEX_NUM_HANDS] == "one") ? "" : "s") + "."));
    add_item( ({ "blade" }),
	BSN("The blade is " +
	some_part(INDEX_BLADE_SIZE, BLADE_SIZE_ITEM) + " and made of " +
	some_part(INDEX_METAL_TYPE, METAL_TYPE_DESC) +
	". It is shiny and rather sharp."));

    /* Give it a nice long description based on the properties.
     */
    set_long(BSN("It is a quality axe, crafted by Borin, smith in the " +
	DWARVEN_RACE_GUILD_NAME + ". It was crafted on special order and " +
	"customized. Its " +
	(is_index(INDEX_HAFT_LENGTH, ({ "short", "long" })) ?
	    (axe_properties[INDEX_HAFT_LENGTH] + " ") : "") +
	"haft is made of " + axe_properties[INDEX_WOOD_TYPE] + " and has " +
	LANG_ADDART(some_part(INDEX_BLADE_SIZE, BLADE_SIZE_ITEM)) + " " +
	axe_properties[INDEX_METAL_TYPE] +
	" blade. The axe is designed to be wielded " +
	some_part(INDEX_NUM_HANDS, NUM_HANDS_ADJ) +
	"-handedly judging to the appropriate grip on the haft."));

    /* double-handed long-hafted oak broad-bladed mithril axe
     */
    set_short((is_index(INDEX_HAFT_LENGTH, ({ "short", "long" })) ?
	    (axe_properties[INDEX_HAFT_LENGTH] + "-hafted ") : "") +
	axe_properties[INDEX_WOOD_TYPE] + " " +
	(is_index(INDEX_BLADE_SIZE, ({ "small", "broad" })) ?
	    (axe_properties[INDEX_BLADE_SIZE] + "-bladed ") : "") +
	axe_properties[INDEX_METAL_TYPE] + " axe");
}

/*
 * Recovery functions.
 */

string
query_recover()
{
    return (MASTER + ":" + implode(axe_properties, "#") + "@axe@" +
	query_wep_recover());
}

void
init_recover(string arg)
{
    int     index;
    mapping props      = ([ ]);
    string *indices    = AXE_PROPERTIES_ORDER;
    string *properties = explode(explode(arg, "@axe@")[0], "#");

    init_wep_recover(arg);

    if (sizeof(properties) != sizeof(indices))
    {
	properties = ({ WOOD_TYPE_DEF, METAL_TYPE_DEF,
	    BLADE_SIZE_DEF, HAFT_LENGTH_DEF, NUM_HANDS_DEF });
    }

    for (index = 0; index < sizeof(indices); index++)
    {
	props[indices[index]] = properties[index];
    }

    set_properties(props);
}
