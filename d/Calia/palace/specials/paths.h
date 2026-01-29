/*  This file contains the pathes to all objects in the crystalline palaces.
    Please modify here.

    The id names have to be U N I Q U E  !!!!!
    The best is to choose ids which are the filename of the file without a
    path, for rooms using the guard system this is essential !


    coder(s):   Merlin, Glykron
    history:
                24.2.95     ommission dealt with            Maniac
                18. 9.93    created                         Glykron

*/

mapping rooms_path =
([
    "light_entrance":           GLYKRON_LIGHT_ROOMS + "entrance.c",
    "light_hall":               GLYKRON_LIGHT_ROOMS + "hall.c",
    "light_training":           GLYKRON_LIGHT_ROOMS + "training.c",
    "light_stairs":             GLYKRON_LIGHT_ROOMS + "stairs.c",
    "light_bronze":             GLYKRON_LIGHT_ROOMS + "bronze.c",
    "light_silver":             GLYKRON_LIGHT_ROOMS + "silver.c",
    "light_gold":               GLYKRON_LIGHT_ROOMS + "gold.c",
    "light_white":              GLYKRON_LIGHT_ROOMS + "white.c",
    "light_lightroom":          GLYKRON_LIGHT_ROOMS + "lightroom.c",
    "light_late":               GLYKRON_LIGHT_ROOMS + "late.c",
    "light_good":               GLYKRON_LIGHT_ROOMS + "good.c",
    "light_sleepless":          GLYKRON_LIGHT_ROOMS + "sleepless.c",
    "light_shop":               GLYKRON_LIGHT_ROOMS + "shop.c",
    "light_hardware_shop":      GLYKRON_LIGHT_ROOMS + "hardware_shop.c",
    "light_hardware_store":     GLYKRON_LIGHT_ROOMS + "hardware_store.c",
    "light_bank":               GLYKRON_LIGHT_ROOMS + "bank.c",
    "light_trainroom":          GLYKRON_LIGHT_ROOMS + "trainroom.c",
    "light_common":             GLYKRON_LIGHT_ROOMS + "common.c",
    "light_post":               GLYKRON_LIGHT_ROOMS + "post.c",
    "light_stairs2":            GLYKRON_LIGHT_ROOMS + "stairs2.c",
    "light_guild":              GLYKRON_LIGHT_ROOMS + "guild.c",
    "light_boardroom":          GLYKRON_LIGHT_ROOMS + "boardroom.c",
    "light_councilroom1":       GLYKRON_LIGHT_ROOMS + "councilroom1.c",
    "light_councilroom2":       GLYKRON_LIGHT_ROOMS + "councilroom2.c",
    "light_keyroom":            GLYKRON_LIGHT_ROOMS + "keyroom.c",
    "light_recruiter":          GLYKRON_LIGHT_ROOMS + "recruiter.c",
    "light_rack":               GLYKRON_LIGHT_ROOMS + "rack.c",
    "light_sanctuary":          GLYKRON_LIGHT_ROOMS + "sanctuary.c",
    "store":              	GLYKRON_ROOMS       + "store.c",
    "gear":			GLYKRON_ROOMS	    + "gear.c",
    "dark_entrance":            GLYKRON_DARK_ROOMS  + "entrance.c",
    "dark_hall":                GLYKRON_DARK_ROOMS  + "hall.c",
    "dark_training":            GLYKRON_DARK_ROOMS  + "training.c",
    "dark_stairs":              GLYKRON_DARK_ROOMS  + "stairs.c",
    "dark_bronze":              GLYKRON_DARK_ROOMS  + "bronze.c",
    "dark_silver":              GLYKRON_DARK_ROOMS  + "silver.c",
    "dark_gold":                GLYKRON_DARK_ROOMS  + "gold.c",
    "dark_black":               GLYKRON_DARK_ROOMS  + "black.c",
    "dark_darkroom":            GLYKRON_DARK_ROOMS  + "darkroom.c",
    "dark_lazy":                GLYKRON_DARK_ROOMS  + "lazy.c",
    "dark_silent":              GLYKRON_DARK_ROOMS  + "silent.c",
    "dark_sleepless":           GLYKRON_DARK_ROOMS  + "sleepless.c",
    "dark_evil":                GLYKRON_DARK_ROOMS  + "evil.c",
    "dark_shop":                GLYKRON_DARK_ROOMS  + "shop.c",
    "dark_stairs2":             GLYKRON_DARK_ROOMS  + "stairs2.c",
]);

mapping doors_path =
([
    "crystalline":		GLYKRON_LIGHT_DOORS + "crystalline.c",
]);

mapping objects_path =
([
    "warning_sign":             GLYKRON_OBJECTS     + "warning_sign.c",
    "calian_book":              GLYKRON_OBJECTS     + "calian_book.c",
    "calian_recruitment_poster":GLYKRON_OBJECTS     + "calian_recruitment_poster.c",
    "calian_medallion":		GLYKRON_OBJECTS     + "calian_medallion.c",
    "calian_public_board":      CRPALACE_OBJECTS     + "calian_public_board.c",
    "torch":                    GLYKRON_OBJECTS     + "torch.c",
    "torch_stand":              GLYKRON_OBJECTS     + "torch_stand.c",
    "standard_torch":           GLYKRON_OBJECTS     + "standard_torch.c",
    "quality_torch":            GLYKRON_OBJECTS     + "quality_torch.c",
    "sack":			GLYKRON_OBJECTS	    + "sack.c",
    "backpack":			GLYKRON_OBJECTS	    + "backpack.c",
    "rope":			GLYKRON_OBJECTS	    + "rope.c",
    "history_book":             GLYKRON_OBJECTS     + "history_book.c",
    "crystalline_orb":          GLYKRON_OBJECTS     + "crystalline_orb.c",
    "crystalline_key":          GLYKRON_OBJECTS     + "crystalline_key.c",
    "calian_private_board":     CRPALACE_OBJECTS     + "calian_private_board.c",
    "log_book":		        GLYKRON_OBJECTS	    + "log_book.c",
    "calian_members_poster":    GLYKRON_OBJECTS     + "calian_members_poster.c",
    "council_board":            CRPALACE_OBJECTS     + "council_board.c",
    "council_log_book":		GLYKRON_OBJECTS	    + "council_log_book.c",
    "council_guide_book":	GLYKRON_OBJECTS	    + "council_guide_book.c",
    "rack":			GLYKRON_OBJECTS	    + "rack.c",
    "weapon_rack":		GLYKRON_OBJECTS	    + "weapon_rack.c",
    "armour_rack":		GLYKRON_OBJECTS	    + "armour_rack.c",
    "misc_rack":		GLYKRON_OBJECTS	    + "misc_rack.c",
    "calian_list":              GLYKRON_OBJECTS     + "calian_list.c",
]);

mapping weapons_path =
([
    "small_sword":              GLYKRON_WEAPONS     + "small_sword.c",
    "iron_sword":               GLYKRON_WEAPONS     + "iron_sword.c",
    "glaive":                   GLYKRON_WEAPONS     + "glaive.c",
    "guisarme":			GLYKRON_WEAPONS     + "guisarme.c",
    "bronze_axe":               GLYKRON_WEAPONS     + "bronze_axe.c",
    "silver_sword":             GLYKRON_WEAPONS     + "silver_sword.c",
    "gold_halberd":             GLYKRON_WEAPONS     + "gold_halberd.c",
    "sword_of_light":           GLYKRON_WEAPONS     + "sword_of_light.c",
    "sword_of_darkness":        GLYKRON_WEAPONS     + "sword_of_darkness.c",
    "blue_sword":               GLYKRON_WEAPONS     + "blue_sword.c",
]);

mapping armours_path =
([
    "leather_cap":              GLYKRON_ARMOURS     + "leather/cap.c",
    "leather_shirt":            GLYKRON_ARMOURS     + "leather/shirt.c",
    "leather_shoes":            GLYKRON_ARMOURS     + "leather/shoes.c",
    "stone_shield":             GLYKRON_ARMOURS     + "stone/shield.c",
    "iron_boots":               GLYKRON_ARMOURS     + "iron/boots.c",
    "iron_cloak":               GLYKRON_ARMOURS     + "iron/cloak.c",
    "iron_gauntlets":           GLYKRON_ARMOURS     + "iron/gauntlets.c",
    "iron_helmet":              GLYKRON_ARMOURS     + "iron/helmet.c",
    "iron_lgauntlet":           GLYKRON_ARMOURS     + "iron/lgauntlet.c",
    "iron_chainmail":           GLYKRON_ARMOURS     + "iron/chainmail.c",
    "iron_rgauntlet":           GLYKRON_ARMOURS     + "iron/rgauntlet.c",
    "iron_shield":              GLYKRON_ARMOURS     + "iron/shield.c",
    "splint_boots":             GLYKRON_ARMOURS     + "splint/boots.c",
    "splint_cloak":             GLYKRON_ARMOURS     + "splint/cloak.c",
    "splint_gauntlets":         GLYKRON_ARMOURS     + "splint/gauntlets.c",
    "splint_helmet":            GLYKRON_ARMOURS     + "splint/helmet.c",
    "splint_lgauntlet":         GLYKRON_ARMOURS     + "splint/lgauntlet.c",
    "splint_mail":              GLYKRON_ARMOURS     + "splint/mail.c",
    "splint_rgauntlet":         GLYKRON_ARMOURS     + "splint/rgauntlet.c",
    "splint_shield":            GLYKRON_ARMOURS     + "splint/shield.c",
    "banded_boots":             GLYKRON_ARMOURS     + "banded/boots.c",
    "banded_cloak":             GLYKRON_ARMOURS     + "banded/cloak.c",
    "banded_gauntlets":         GLYKRON_ARMOURS     + "banded/gauntlets.c",
    "banded_helmet":            GLYKRON_ARMOURS     + "banded/helmet.c",
    "banded_lgauntlet":         GLYKRON_ARMOURS     + "banded/lgauntlet.c",
    "banded_mail":              GLYKRON_ARMOURS     + "banded/mail.c",
    "banded_rgauntlet":         GLYKRON_ARMOURS     + "banded/rgauntlet.c",
    "banded_shield":            GLYKRON_ARMOURS     + "banded/shield.c",
    "blue_platemail":           GLYKRON_ARMOURS     + "blue/armour.c",
    "bronze_boots":             GLYKRON_ARMOURS     + "bronze/boots.c",
    "bronze_cloak":             GLYKRON_ARMOURS     + "bronze/cloak.c",
    "bronze_gauntlets":         GLYKRON_ARMOURS     + "bronze/gauntlets.c",
    "bronze_helmet":            GLYKRON_ARMOURS     + "bronze/helmet.c",
    "bronze_lgauntlet":         GLYKRON_ARMOURS     + "bronze/lgauntlet.c",
    "bronze_chainmail":         GLYKRON_ARMOURS     + "bronze/chainmail.c",
    "bronze_rgauntlet":         GLYKRON_ARMOURS     + "bronze/rgauntlet.c",
    "bronze_shield":            GLYKRON_ARMOURS     + "bronze/shield.c",
    "silver_boots":             GLYKRON_ARMOURS     + "silver/boots.c",
    "silver_cloak":             GLYKRON_ARMOURS     + "silver/cloak.c",
    "silver_gloves":            GLYKRON_ARMOURS     + "silver/gloves.c",
    "silver_helmet":            GLYKRON_ARMOURS     + "silver/helmet.c",
    "silver_lglove":            GLYKRON_ARMOURS     + "silver/lglove.c",
    "silver_chainmail":         GLYKRON_ARMOURS     + "silver/chainmail.c",
    "silver_rglove":            GLYKRON_ARMOURS     + "silver/rglove.c",
    "silver_shield":            GLYKRON_ARMOURS     + "silver/shield.c",
    "gold_boots":               GLYKRON_ARMOURS     + "gold/boots.c",
    "gold_cloak":               GLYKRON_ARMOURS     + "gold/cloak.c",
    "gold_gauntlets":           GLYKRON_ARMOURS     + "gold/gauntlets.c",
    "gold_helmet":              GLYKRON_ARMOURS     + "gold/helmet.c",
    "gold_lgauntlet":           GLYKRON_ARMOURS     + "gold/lgauntlet.c",
    "gold_platemail":           GLYKRON_ARMOURS     + "gold/platemail.c",
    "gold_rgauntlet":           GLYKRON_ARMOURS     + "gold/rgauntlet.c",
    "gold_shield":              GLYKRON_ARMOURS     + "gold/shield.c",
    "mithril_boots":            GLYKRON_ARMOURS     + "mithril/boots.c",
    "mithril_gauntlets":        GLYKRON_ARMOURS     + "mithril/gauntlets.c",
    "mithril_helmet":           GLYKRON_ARMOURS     + "mithril/helmet.c",
    "mithril_lgauntlet":        GLYKRON_ARMOURS     + "mithril/lgauntlet.c",
    "mithril_platemail":        GLYKRON_ARMOURS     + "mithril/platemail.c",
    "mithril_rgauntlet":        GLYKRON_ARMOURS     + "mithril/rgauntlet.c",
    "mithril_shield":           GLYKRON_ARMOURS     + "mithril/shield.c",
    "white_cloak":              GLYKRON_ARMOURS     + "white/cloak.c",
    "black_cloak":              GLYKRON_ARMOURS     + "black/cloak.c",
]);

mapping specials_path =
([
    "path":			GLYKRON_SPECIALS    + "path.c",
    "calian_cmdsoul":		GLYKRON_SPECIALS    + "calian_cmdsoul.c",
    "calian_shadow":		GLYKRON_SPECIALS    + "calian_shadow.c",
]);

mapping monsters_path =
([
    "calia_npc":		GLYKRON_MONSTERS    + "calia_npc.c",
    "calian":			GLYKRON_MONSTERS    + "calian.c",
    "very_young_calian":	GLYKRON_MONSTERS    + "very_young_calian.c",
    "young_calian":		GLYKRON_MONSTERS    + "young_calian.c",
    "calian_guildmaster":	GLYKRON_MONSTERS    + "calian_guildmaster.c",
    "calian_in_training":	GLYKRON_MONSTERS    + "calian_in_training.c",
    "calian_guardian":		GLYKRON_MONSTERS    + "calian_guardian.c",
    "bronze_calian":		GLYKRON_MONSTERS    + "bronze_calian.c",
    "silver_calian":		GLYKRON_MONSTERS    + "silver_calian.c",
    "gold_calian":		GLYKRON_MONSTERS    + "gold_calian.c",
    "good_calian":		GLYKRON_MONSTERS    + "good_calian.c",
    "white_calian":		GLYKRON_MONSTERS    + "white_calian.c",
    "kroug":			GLYKRON_MONSTERS    + "kroug.c",
    "very_young_kroug":		GLYKRON_MONSTERS    + "very_young_kroug.c",
    "young_kroug":		GLYKRON_MONSTERS    + "young_kroug.c",
    "kroug_in_training":	GLYKRON_MONSTERS    + "kroug_in_training.c",
    "kroug_guardian":		GLYKRON_MONSTERS    + "kroug_guardian.c",
    "bronze_kroug":		GLYKRON_MONSTERS    + "bronze_kroug.c",
    "silver_kroug":		GLYKRON_MONSTERS    + "silver_kroug.c",
    "gold_kroug":		GLYKRON_MONSTERS    + "gold_kroug.c",
    "good_kroug":		GLYKRON_MONSTERS    + "good_kroug.c",
    "black_kroug":		GLYKRON_MONSTERS    + "black_kroug.c",
]);

mapping texts_path =
([
    "calian_abilities":		GLYKRON_TEXTS       + "calian_abilities",
    "Calia_history":		GLYKRON_TEXTS       + "Calia_history",
    "calian_board_msgs":	CRPALACE_TEXTS	    + "calian_board_msgs",
    "light_board_msgs":		CRPALACE_TEXTS	    + "light_board_msgs",
    "council_msgs":		"/d/Calia/private/calian_council/council_msgs",
    "council_guide":		GLYKRON_TEXTS	    + "council_guide",
    "calian_recruitment_text":  GLYKRON_TEXTS	    + "calian_recruitment_text",
]);

mapping logs_path =
([
    "council":		    	GLYKRON_LOGS	    + "council",
    "calian_recruitment":	GLYKRON_LOGS  	    + "calian_recruitment",
    "calian_shadow_added":	GLYKRON_LOGS  	    + "calian_shadow_added",
]);
