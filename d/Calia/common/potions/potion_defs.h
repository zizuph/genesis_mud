
 /* Mapping Ingredients:
  * potion name : ({min alco, min soft, ({ herb1, herb2, ...,}),
  * ({ heap1, heap2, ..., }), ({ other1, other2, ..., }), potion file name
  */

#define CALIA_POTION_INGREDIENTS ([ \
    "nero" :           ({ 0, 0, ({"/d/Krynn/common/herbs/poison_ivy",}), \
                       ({"/d/Calia/worshippers/objects/water_vial"}), \
                       ({ }), \
                       "/d/Calia/walkers/potions/nero"}), \
\
    "aulaki" :         ({ 0, 0, ({"/d/Krynn/common/herbs/sargassum",}), \
                       ({"/d/Calia/worshippers/objects/water_vial"}), \
                       ({ }), \
                       "/d/Calia/walkers/potions/aulaki"}), \
\
    "bradu" :          ({ 0, 0, ({"/d/Krynn/common/herbs/elkhorn_kelp",}), \
                       ({"/d/Calia/worshippers/objects/water_vial"}), \
                       ({ }), \
                       "/d/Calia/walkers/potions/bradu"}), \
\
    "aertrophia" :     ({ 0, 0, ({"/d/Krynn/common/herbs/elkhorn_kelp",}), \
                       ({"/d/Calia/worshippers/objects/water_vial"}), \
                       ({ }), \
                       "/d/Calia/walkers/potions/aertrophia"}), \
\
    "akoutari" :       ({ 0, 0, ({"/d/Krynn/common/herbs/fucus",}), \
                       ({"/d/Calia/worshippers/objects/water_vial", \
                       "/d/Calia/walkers/fire/objects/sulphur"}), \
                       ({ }), \
                       "/d/Calia/walkers/potions/akoutari"}), \
\
    "pichno" :         ({ 0, 0, ({"/d/Krynn/common/herbs/fucus",}), \
                       ({"/d/Calia/worshippers/objects/water_vial", \
                       "/d/Calia/walkers/wind/objects/ice_crystal"}), \
                       ({ }), \
                       "/d/Calia/walkers/potions/pichno"}), \
\
    "aspida" :         ({ 0, 0, ({"/d/Krynn/common/herbs/bull_kelp",}), \
                       ({"/d/Calia/worshippers/objects/water_vial", \
                       "/d/Calia/walkers/fire/objects/sulphur"}), \
                       ({ }), \
                       "/d/Calia/walkers/potions/aspida"}), \
\
    "ochetos" :        ({ 0, 0, ({"/d/Krynn/common/herbs/bull_kelp",}), \
                       ({"/d/Calia/worshippers/objects/water_vial"}), \
                       ({ }), \
                       "/d/Calia/walkers/potions/ochetos"}), \
\
    "saita" :          ({ 50, 70, ({ }), \
                       ({"/d/Calia/walkers/fire/objects/sulphur", \
                       "/d/Calia/walkers/fire/objects/salt"}), \
                       ({ }), \
                       "/d/Calia/walkers/potions/saita"}), \
\
    "upala" :          ({ 50, 70, ({ }), \
                       ({"/d/Calia/walkers/wind/objects/ice_crystal"}), \
                       ({ }), \
                       "/d/Calia/walkers/potions/upala"}), \
\
    "purkagia" :       ({ 50, 70, ({"/d/Krynn/common/herbs/coral_alga",}), \
                       ({ }), \
                       ({ }), \
                       "/d/Calia/walkers/potions/purkagia"}), \
\
    "topi" :           ({ 50, 70, ({"/d/Krynn/common/herbs/coral_alga",}), \
                       ({ }), \
                       ({ }), \
                       "/d/Calia/walkers/potions/topi"}), \
\
    "optasia" :        ({ 0, 0, ({"/d/Krynn/common/herbs/sea_lettuce",}), \
                       ({"/d/Calia/worshippers/objects/water_vial", \
                       "/d/Calia/walkers/fire/objects/ash"}), \
                       ({ }), \
                       "/d/Calia/walkers/potions/optasia"}), \
\
    "aeras" :          ({ 50, 70, ({"/d/Krynn/common/herbs/salt_wort",}), \
                       ({ }), \
                       ({ }), \
                       "/d/Calia/walkers/potions/aeras"}), \
\
    "pleko" :          ({ 50, 70, ({"/d/Krynn/common/herbs/sea_lettuce",}), \
                       ({ }), \
                       ({ }), \
                       "/d/Calia/walkers/potions/pleko"}), \
\
    "photostepsanos" : ({ 50, 70, ({"/d/Krynn/common/herbs/sea_bubble",}), \
                       ({ }), \
                       ({ }), \
                       "/d/Calia/walkers/potions/photostepsanos"}), \
\
    "anthisto" :       ({ 0, 0, ({"/d/Krynn/common/herbs/sargassum",}), \
                       ({"/d/Calia/worshippers/objects/water_vial", \
                       "/d/Calia/walkers/fire/objects/sulphur"}), \
                       ({ }), \
                       "/d/Calia/walkers/potions/anthisto"}), \
\
    "antidroaera" :    ({ 0, 0, ({"/d/Krynn/common/herbs/sargassum",}), \
                       ({"/d/Calia/worshippers/objects/water_vial", \
                       "/d/Calia/walkers/wind/objects/ice_crystal"}), \
                       ({ }), \
                       "/d/Calia/walkers/potions/antidroaera"}), \
\
    "stoiecheio" :     ({ 50, 70, ({"/d/Krynn/common/herbs/fireweed",}), \
                       ({"/d/Calia/walkers/fire/objects/ash"}), \
                       ({ }), \
                       "/d/Calia/walkers/potions/stoiecheio"}), \
\
    "diarroae" :       ({ 50, 70, ({"/d/Krynn/common/herbs/cord_grass",}), \
                       ({"/d/Calia/walkers/wind/objects/ice_crystal"}), \
                       ({ }), \
                       "/d/Calia/walkers/potions/diarroae"}), \
\
    "lepida" :         ({ 50, 70, ({"/d/Krynn/common/herbs/fireweed",}), \
                       ({"/d/Calia/walkers/wind/objects/ice_crystal", \
                       "/d/Calia/worshippers/objects/water_vial"}), \
                       ({ }), \
                       "/d/Calia/walkers/potions/lepida"}), \
\
    "hagiospyro" :     ({ 50, 70, ({"/d/Krynn/common/herbs/poison_ivy", \
                       "/d/Krynn/common/herbs/sargassum",}), \
                       ({"/d/Calia/walkers/fire/objects/ash"}), \
                       ({ }), \
                       "/d/Calia/walkers/potions/hagiospyro"}), \
\
    "phlogaphulo" :    ({ 0, 0, ({"/d/Krynn/common/herbs/fireweed", \
                       "/d/Krynn/common/herbs/laminaria",}), \
                       ({"/d/Calia/worshippers/objects/water_vial", \
                       "/d/Calia/walkers/fire/objects/obsidian", \
                       "/d/Calia/walkers/fire/objects/salt"}), \
                       ({ }), \
                       "/d/Calia/walkers/potions/phlogaphulo"}), \
\
    "kausae" :         ({ 50, 70, ({"/d/Krynn/common/herbs/surf_grass", \
                       "/d/Krynn/common/herbs/laminaria",}), \
                       ({"/d/Calia/walkers/fire/objects/salt", \
                       "/d/Calia/walkers/fire/objects/ash"}), \
                       ({ }), \
                       "/d/Calia/walkers/potions/kausae"}), \
\
    "epikanomai" :     ({ 50, 70, ({"/d/Krynn/common/herbs/sargassum", \
                       "/d/Krynn/common/herbs/sea_bubble",}), \
                       ({"/d/Calia/walkers/fire/objects/ash"}), \
                       ({ }), \
                       "/d/Calia/walkers/potions/epikanomai"}), \
\
    ])

