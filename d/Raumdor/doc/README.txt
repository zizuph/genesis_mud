The year is 2018 and an abandoned Raumdor has undergone a good deal of
emendation. I, Lord Malus, hereby decree, with steadfast resolve and
indefatigable purpose, that, roughly speaking, some of following ideas might be,
if you're alright with them, not the worst:

-   Raumdor should continue with its rediculously excessive portrayal of good
    and evil. Maggot-covered zombies and auras of divine power are the norm.
    It pits the Holy against Unholy in a zealous battle of supernatural
    proportions. For what it's worth, I am reminded of and draw some
    inspiration from the Diablo series of video games, which weaves religious
    characters and themes with more generic fantasy. 

-   Immersion is important. NPCs shouldn't be saying things a character in a
    book wouldn't say. If you are in the dark, you should not be able to see
    things you wouldn't see in the dark. "Magical knowledge" shouldn't happen.
    For example, if "the zombie is hungry and wants to eat you," how did you
    come to know that, exactly? Much better if "the zombie looks at you, and
    looks hungry."

-   It can be better to enrich the existing world with detail than create a
    larger world. This is particular true at this moment, when we have a large
    forest that does little to reward explorers and a city with relatively
    little nuance.

-   This file and the other files in /d/Raumdor/doc/ should be kept updated
    with current principles and guidance for continuing efforts in the domain,
    with the exception of /d/Raumdor/doc/antiquated/. That directory should be
    used to keep documentation created previously that is not maintained. When
    it doesn't create a conflict or hindrance of some kind, one should still
    draw on the mythos, stories, designs, etc. provided there.

-   The bulk of the domain should be in /d/Raumdor/common/, with subdirectories
    corresponding to shared code or different areas. There are exceptions for
    special cases, like gsl_ships/, guilds/, lib/, std/, etc. in the top-
    level directory.

-   Files and code for a particular area should be kept in that area's
    subdirectory. If other code reference it, it should then be moved up to the
    minimum number of subdirectories necessary for it to share a defs.h file
    with all such code. For example, if there were an apple in the keep...
        /d/Raumdor/common/drakmere/keep/obj/apple.c
    ...and it became referenced in Drakmere proper, it would be moved to...
        /d/Raumdor/common/drakmere/obj/apple.c
    If instead it was referenced in the forest, it would be moved to...
        /d/Raumdor/common/obj/apple.c

-   Code that is under development should be placed in /d/Raumdor/development/.
    When it is a personal (i.e. non-collaborative) project, it should be placed
    in a subdirectory with your name, e.g. /d/Raumdor/development/malus/. The
    definitions structure of Raumdor should ensure you only have to redefine
    one path macro to make this work, e.g.
        #undef COMMON_DIR
        #define COMMON_DIR DEVELOPMENT_DIR + "malus/common" 

-   Inactive, inaccessible, deleted, unused, abandoned, etc. code
    should be put in /d/Raumdor/ARCHIVE/. It should also keep its relative
    directory structure, e.g. /d/Raumdor/lib/examples/example.c would go here:
    /d/Raumdor/ARCHIVE/lib/examples/example.c

-   Check the ARCHIVE before starting a new project. Just because it's not
    currently in the domain doesn't mean it it's useless!

Of course, one could go on endlessly about such things. While enduring such
beadledom, do please try to remember to have FUN!
