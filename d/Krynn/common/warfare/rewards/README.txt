
    ================== KRYNN WARFARE REWARD SYSTEM ================== 

Conquering the Krynn warfare battlefields grant you steel coins
(/d/Krynn/common/warfare/rewards/krynn_steel_coins.c), which can be used 
to have items forged by Theros Ironforge in Solace
(/d/Krynn/solace/new_village/town_square/npcs/theros) who can be found at
(/d/Krynn/solace/new_village/town_square/rooms/smithy). These items are 
masterwork items, linked to the Genesis commerce system that requires
the item components available - otherwise they need to be collected and
sold to Theros before he can forge them.

Commodities used can be found in /d/Krynn/common/commerce/

On purchase they are high quality but non-magical. However magical crystals
can be inserted in to this equipment, making them magical but also 
customisable by the player. The base code for this equipment is at
/d/Krynn/common/warfare/rewards/ 

MASTERWORK ARMOURS:
===================
/d/Krynn/common/warfare/rewards/armours/
Armours can have up to three crystal slots of three different shapes,
tear shaped, oval shaped, and triangular shaped (helm only). Configuration
will be dependent on the armour type:

================= BODY ===================================================
* platemail - 3x tear; base AC 40 (cost: 100 steel, ~7 plat)
* chainmail - 2x tear; 1x oval; base AC 35 (cost: 80 steel, ~6 plat)
* leather   - 1x tear; 2x oval; base AC 30 (cost: 60 steel, ~5 plat)
* tunic     - 3x oval; base AC 25 (cost: 40 steel, ~4 plat)
================= HEAD ===================================================
* plate helm     - 2x tear; base AC 35 (60 steel, ~6 plat)
* chain hood     - 1x tear; 1x oval; base AC 30 (50 steel, ~5 plat)
* studded coif   - 1x oval; 1x triangular; base AC 25 (30 steel, ~4 plat)
================= SHIELD =================================================
* tower     - 2x tear; base AC 40 (body, legs; cost: 80 steel, ~7 plat)
* buckler   - 2x oval; base AC 25 (cost: 50 steel, ~3 plat) 
================= GAUNTLETS ==============================================
* plate     - 1x tear; base AC 40 (cost: 50 steel, ~7 plat)
* chain     - 1x tear; base AC 35 (cost: 40 steel, ~6 plat)
* leather   - 1x oval; base AC 30 (cost: 30 steel, ~5 plat)
================= LEGGINGS  ==============================================
* plate     - 1x tear; base AC 40 (cost: 50 steel, ~7 plat)
* chain     - 1x tear; base AC 35 (cost: 40 steel, ~6 plat)
* leather   - 1x oval; base AC 30 (cost: 30 steel, ~5 plat)

Suit configurations provide the following number of slots
===========================================================================
Full plate suit (& tower shield):  9 tear slots.
-                TOTAL SUIT COST:  340 steel, 36 platinum coins
Full chain suit (& tower shield):  7 tear, 2 oval.
-                TOTAL SUIT COST:  290 steel, 30 platinum coins
Full leather suit (& buckler):     1 tear, 7 oval, 1 triangular slot. 
-                TOTAL SUIT COST:  200 steel, 22 platinum coins
Cloth/leather suit (& buckler):    8 oval, 1 triangular slot.
-                TOTAL SUIT COST:  180 steel, 21 platinum coins
===========================================================================

MASTERWORK WEAPONS:
===================
/d/Krynn/common/warfare/rewards/weapons/
Masterwork weapons generally have two ellipse shaped crystal slots, with
the exception of the bow (x3) and the wand (x1). The weapon types are as
follows:

================= TWO-HANDED==============================================
* melee     - 2x ellipse; base hit/pen 40/40 (cost: 100 steel, ~14 plat).
  (greatsword, spear, staff, warhammer, greataxe, hoopak
* greatbow  - 3x ellipse; base hit/pen 40/40 (cost: 150 steel, ~14 plat).

================= ONE-HANDED==============================================
* melee     - 2x ellipse; base hit/pen 35/35 (cost: 80 steel, ~14 plat).
  (longsword, 1h spear, mace, axe)
* dagger    - 2x ellipse; base hit/pen 20/20 (cost: 80 steel, ~14 plat).

================= WAND ===================================================
* wand      - 1x ellipse (cost: 60 steel, ~4 plat).

===========================================================================

AUGMENTATION CRYSTALS:
======================
/d/Krynn/common/warfare/rewards/magic_gems/
There are four types of augmentation crystals that are random drops from
warfare npcs. Three fit crystal types fit masterwork armours, while one fits 
masterwork weapons/wands:

 ** Tear-shaped improves the AC of the armour (i.e iron ward diamonds)
    or resistances.

 ** Oval shaped improves certain skills 
    (defence/parry/two handed combat/pick locks/hide/
     sneak/disarm traps/magic form skills), or reduces armour weight.

 ** Triangular add spell effects to the object wearer (no scry, see invis, 
    see in dark, waterbreathe, quickness) at a high mana cost. 
    Triangular crystals only fit in helms, of which there are only ever 
    one crystal slot max. Crystal effects are in the
    /d/Krynn/common/warfare/rewards/magic_effects/ directory.

 ** Ellipse crystals are for weapons/wands, and either enhance the hit
    and/or pen of the weapon, spellpower of certain weapons (staves, wands,
    and daggers), or provide skill boosts.

The general theme of the gems is that those armours with higher AC benefits
(such as plate armours) tend to be able hold defensive teardrop crystals,
while those lower AC armours (leather and cloth) tend to hold more
skill enhancement oval crystals. Those willing to forgo AC using the 
lighter armours can potentially boost certain skills by up to 40 skill
levels.

The gem code is found in the /d/Krynn/common/warfare/rewards/magic_gems/
directory, however should be cloned from /d/Genesis/gems/obj/krynn/
directory to allow them to be stored in gem bank accounts.

If adding new gems, make sure you register them with the Genesis gem manager,
/d/Genesis/gems/gem_manager.c using the following function:

register_gem(string filename, string type, string ptype, string colour,
    int rarity, int value, int volume, int weight)

E.g Call gem_manager.c register_gem "/d/Genesis/gems/obj/krynn/ellipse_azure_diamond"%%"diamond"%%"diamonds"%%"ellipse-shaped azure"%%2%%6048%%1%%2

A number of the gem defines are in /d/Krynn/common/warfare/warfare.h

==========================================================================
Gem name           || Shape       || Benefit         
*rare glowing variant (dropped only from top tier mobs)    
==========================================================================
white diamond      || Ellipse     || +10 weapon hit (10 spellpower)
azure diamond      || Ellipse     || +5 weapon hit / +5 pen (10 spellpower)
blue diamond       || Ellipse     || +10 weapon pen (10 spellpower)
red tourmaline     || Ellipse     || + 5 skill boost (SS_ELEMENT_FIRE) 
blue tourmaline    || Ellipse     || + 5 skill boost (SS_ELEMENT_WATER) 
yellow tourmaline  || Ellipse     || + 5 skill boost (SS_ELEMENT_AIR) 
brown tourmaline   || Ellipse     || + 5 skill boost (SS_ELEMENT_EARTH)
black tourmaline   || Ellipse     || + 5 skill boost (SS_ELEMENT_DEATH)
violet tourmaline  || Ellipse     || + 5 skill boost (SS_ELEMENT_LIFE) 
==========================================================================
diamond *          || Teardrop    || +2 (*+5) armour ac
carnelian *        || Teardrop    || +3 (*+6) fire resistance 
blue topaz *       || Teardrop    || +3 (*+6) water resistance
bloodstone *       || Teardrop    || +3 (*+6) death resistance
opal *             || Teardrop    || +3 (*+6) life resistance
blue spinel *      || Teardrop    || +3 (*+6) air resistance
golden pyrite *    || Teardrop    || +3 (*+6) earth resistance
green jade *       || Teardrop    || +3 (*+6) poison resistance
beryl *            || Teardrop    || +3 (*+6) cold resistance
==========================================================================
yellow topaz       || Triangular  || scry protection
green peridot      || Triangular  || see invisible
blue agate         || Triangular  || breathe water
orange garnet      || Triangular  || +14 quickness boost
yellow amber       || Triangular  || see in darkness
==========================================================================
blue sapphire      || oval        || +5 skill boost (SS_DEFENCE)
green sapphire     || oval        || +5 skill boost (SS_PARRY)
azure sapphire     || oval        || +5 skill boost (SS_2H_COMBAT)
black sapphire     || oval        || +5 skill boost (SS_HIDE)
violet sapphire    || oval        || +5 skill boost (SS_SNEAK)
mauve sapphire     || oval        || +5 skill boost (SS_OPEN_LOCK)
magenta sapphire   || oval        || +5 skill boost (SS_FR_TRAP)
rose quartz        || oval        || +5 skill boost (SS_FORM_TRANSMUTATION)
milky quartz       || oval        || +5 skill boost (SS_FORM_ILLUSION)
smoky quartz       || oval        || +5 skill boost (SS_FORM_DIVINATION)
striped chalcedony || oval        || +5 skill boost (SS_FORM_ENCHANTMENT)
purple amethyst    || oval        || +5 skill boost (SS_FORM_CONJURATION)
brown agate        || oval        || +5 skill boost (SS_FORM_ABJURATION)
amber aragonite    || oval        || +5 skill boost (SS_HUNTING)
moonstone *        || oval        || armour weight reduction 25% (*75%)
==========================================================================


