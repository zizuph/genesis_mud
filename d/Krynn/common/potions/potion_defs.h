/* Mapping Ingredients:
 * potion name : ({min alco, min soft, ({ herb1, ..., }),
 * ({ heap1, ..., }), ({ other1, ..., }), potion file name
 */

#define KRYNN_POTION_INGREDIENTS ([ \
    "shochraos" : ({ 40,  40, ({"/d/Krynn/common/herbs/bur_reed",}), \
               ({}), ({}), \
               "/d/Krynn/guilds/sohm/objs/potions/lightning_potion"}), \
    "ixenner" : ({ 40,  40, ({"/d/Krynn/common/herbs/hawthorn",}), \
               ({}), ({}), \
               "/d/Krynn/guilds/sohm/objs/potions/f_lance_potion"}), \
    "tonash" : ({ 40,  40, ({"/d/Krynn/common/herbs/bkd_sedge",}), \
               ({}), ({}), \
               "/d/Krynn/guilds/sohm/objs/potions/meteor_potion"}), \
    "vistoma" : ({ 40,  40, ({"/d/Krynn/common/herbs/crocus",}), \
               ({}), ({}), \
               "/d/Krynn/guilds/sohm/objs/potions/truesight_potion"}), \
    "xarzithnar" : ({ 40,  40, ({"/d/Krynn/common/herbs/salt_wort",}), \
               ({}), ({}), \
               "/d/Krynn/guilds/sohm/objs/potions/icestrike_potion"}), \
    "ricindenthanus" : ({ 40,  40, ({"/d/Krynn/common/herbs/locoweed",}), \
               ({}), ({}), \
               "/d/Krynn/guilds/sohm/objs/potions/psychic_blast_potion"}), \
    "hexlith" : ({ 40,  40, ({"/d/Krynn/common/herbs/skullcap",}), \
               ({}), ({}), \
               "/d/Krynn/guilds/sohm/objs/potions/tbreath_potion"}), \
    "reelojawa" : ({ 40,  40, ({"/d/Gondor/common/herbs/hemlock", \
                                 "/d/Krynn/common/herbs/lady_slipper", }), \
               ({}), ({}), \
               "/d/Krynn/guilds/sohm/objs/potions/dominate_potion"}), \
    "solina" : ({ 40,  40, ({"/d/Krynn/common/herbs/solinaith",}), \
               ({}), ({}), \
               "/d/Krynn/guilds/sohm/objs/potions/arcane_vulnerability_potion"}), \
    "skaer" : ({ 40,  40, ({"/d/Krynn/common/herbs/sargassum",}), \
               ({}), ({}), \
               "/d/Krynn/guilds/sohm/objs/potions/geyser_potion"}), \
    "suaco" : ({ 40,  40, ({"/d/Krynn/common/herbs/ss_grass",}), \
               ({}), ({}), \
               "/d/Krynn/guilds/sohm/objs/potions/wind_potion"}), \
    "potion of swimming" : ({ 0,  50, ({}), \
               ({"/d/Krynn/south_courrain/obj/sealion_heart",}), ({}), \
               "/d/Ansalon/goodlund/bloodsea/obj/swim_potion"}), \
    ])

/* defines for each of the special potions powers */

#define STEEL_POTION_COST                      (100000)
#define STEEL_POTION_TIME       (1800 + (random(1200)))
#define STEEL_POTION_AC                            (20)
#define STEEL_OBJ               "/d/Krynn/common/potions/steelskin_obj"

#define STONE_POTION_COST                       (55000)
#define STONE_POTION_TIME       (1800 + (random(1200)))
#define STONE_POTION_AC                            (15)
#define STONE_OBJ               "/d/Krynn/common/potions/stoneskin_obj"

#define SPEED_POTION_COST                       (45000)
#define SPEED_POTION_TIME        (1200 + (random(900)))
#define SPEED_POTION_SPEED                         (40)
#define SPEED_POTION_WIS                           (10)
#define SPEED_OBJ               "/d/Krynn/common/potions/speed_obj"

#define POTION_EFFECT_LOG   "potioneffect"
