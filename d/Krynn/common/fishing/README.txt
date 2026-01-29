*** How you can add fishing to your own domain areas ***

In rooms where you can fish, you simply need to add the property "_live_i_can_fish" to your room, either as:

add_prop("_live_i_can_fish", 1);

This will essentially result in a key word room check that will determine a default fishing biome.

Preferably, the fishing biome is set in the room property.

The current biome options are "freshwater", "saltwater", "subterranean", and "alpine lake" and can be added as an alternative to an integer, such as:

add_prop("_live_i_can_fish", "freshwater");

If a domain wants custom fish and catching chances for a fishing area, such as "balifor", "bloodsea", "raumdor_corrupted", "fresh_salmon_heavy" or "shire_rivers" etc they can be added to /d/Krynn/common/fishing/fish_file.h and the custom fishing biome added to /d/Krynn/common/fishing/fish_object.c

Likewise, if a domain wants to create unique custom bait types these can be easily created by inheriting the /d/Krynn/common/fishing/fishing_bait.c object.  /d/Krynn/common/fishing/bardee_grub.c or /d/Krynn/common/fishing/earthworm.c are examples of how that works.

If you don't want a room to be fishable, you can add the "_live_i_no_fish" property to your room. Either a non-zero integer for a default no-fishing message, or a string for a custom no-fish message.
