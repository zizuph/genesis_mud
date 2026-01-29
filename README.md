
This is the code base for the online LPMud Genesis, circa 2023.

This game has been around since the early 1990s, as one of
the earlier text-based games available on the Internet.  Most
of the code provided here was written 20+ years ago.  While
there are still contributions made to the game today, it has
a limited user base as people have moved on to other things.

For those interested in understanding how the game mechanics
work:

Standard weapon attack code is located in [cbase.c](std/combat/cbase.c).
Formulas for translating weapon pen and skill are located [here](sys/formulas.h).

Guild abilities are all based on the [specials library](d/Genesis/specials/new/ability.h).
Each guild ability inherits a core version maintained by the
balance team, swapping out the various messages for their own
guild-specific version.  Combat aid is specified within the
guild version, leading to each ability potentially having a
very different net effect depending on the combat aid given.

Guild code resides in various directories throughout the
game, most commonly in /d/<Domain>/guild or /d/<Domain>/guilds/.
Tax documents specify the skills and combat aid that each has
assigned to them.

A few examples are here:
[Fire Knives](d/Faerun/guilds/fire_knives/doc/tax_doc_new.txt)
[Mercenaries](d/Sparkle/guilds/new_merc/doc/tax_doc.txt)
[Neidar](d/Ansalon/guild/neidar/docs/docs.txt)
[POT](d/Ansalon/guild/new_pot/tax_doc.txt)
[Shadow Union](d/Avenir/union/doc/union_tax_.txt)
[WOHS](d/Krynn/guilds/wohs/doc/WoHS.txt)

Core rules for guild balance are here:
[tax](d/Genesis/doc/rules/wizard/guilds/tax)
[types](d/Genesis/doc/rules/wizard/guilds/types)
[skills](d/Genesis/doc/rules/wizard/guilds/skills)

Magical items tend to be another area of interest.  While
some domains tracked them in various files, this was not
necessarily consistent.

These details are often split across multiple files.  Some
can be found here:
[Ansalon](d/Ansalon/private/magic/weapons)
[Avenir](d/Avenir/private/MAGIC/weapons)
[Calia](d/Calia/open/MAGIC)
[Earthsea](d/Earthsea/private/MAGIC/unholy_halberd.txt)
[Emerald](d/Emerald/open/MAGIC)
[Faerun](d/Faerun/open/MAGIC)
[Kalad](d/Kalad/private/MAGIC/weapons)
[Khalakhor](d/Khalakhor/private/MAGIC)
[Krynn](d/Krynn/info/MAGIC)
[Raumdor](d/Raumdor/open/MAGIC)
[Shire](d/Shire/private/MAGIC)
[Terel](d/Terel/private/MAGIC_WEAPONS)

An interesting thing to note is that many domains would
hide the magic item details from other domains.  This was
due to wizards who would volunteer in order to get access
to this information to benefit their friends.

This core policy of secrecy historically led to some
major issues.  Perhaps one of the most well known is when
the liege Shinto created an explorers club, consisting
of many of his personal friends, with access to these
special items in Terel.  Shinto then threatened players
that were not a member of this club that happened to
find these items.

Threats of deletion and the like remain to this day, 
even as the vast majority of this code was written in
the 90s and naughts.






